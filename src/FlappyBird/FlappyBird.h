#ifndef FLAPPY_BIRD_H
#define FLAPPY_BIRD_H

#include <cstdlib>
#include <ctime>

/******************************************************************************
*                    FlappyBird
******************************************************************************/
class FlappyBird {
public:
    const int pillarsW = 80;
    const int holeH = 100;
    const int pillarsSpeed = 10;
    const int birdSpeed = 20;

    int W, H, birdX, birdY, pillarsX, pillarsY;

    FlappyBird(int _W = 400, int _H = 600) : W(_W), H(_H) {
        srand(time(NULL)); // �����������
        init();
    }

    void init() {
        birdY = H / 2;
        birdX = 100;
        pillarsX = W;
        pillarsY = rand() % (H - 200) + 100; // ȷ����������Ļ��Χ��
    }

    void initPillars() {
        pillarsX = windowWidth;
        pillarsY = rand() / double(RAND_MAX) * (windowHeight - 100 - 100) + 100;	//[st,ed)
    }

    bool play(bool action) {
        pillarsX -= pillarsSpeed;
        birdY += -birdSpeed + (action ? 3 * birdSpeed : 0);

        if (pillarsX < 0) {
            pillarsX = W;
            pillarsY = rand() % (H - 200) + 100;
        }

        // �ж���Ϸ�Ƿ����
        if (birdY <= 0 || birdY >= H ||
            ((birdX > pillarsX && birdX < pillarsX + pillarsW) &&
                (birdY < pillarsY || birdY > pillarsY + holeH))) {
            return true; // ��Ϸ����
        }

        return false; // ��Ϸ����
    }

    bool judgeLose() {
        if (birdY <= 0 || birdY >= windowHeight)return true;
        if (pillarsX < birdX && pillarsX + pillarsWidth > birdX && (birdY < pillarsY || birdY > pillarsY + holeHeight))
            return true;
        return false;
    }
};

#endif // FLAPPY_BIRD_H
