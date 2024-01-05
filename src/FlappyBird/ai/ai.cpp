#include "ai.h"

int toState(Bird& b, Pillars& p) {
    int dx = p.pillarHoles[0].first + p.pillar_width;
    int dy = b.position.second - p.pillarHoles[0].second + (p.windows_size.second - p.hole_size_half);
    return dx / 10 * 2 * (p.windows_size.second - p.hole_size_half) / 10 + dy / 10;
}

QLearning* training(FlappyBird& game) {
    int x = game.windows_size.first + game.pillars->pillar_width;
    int y = 2 * (game.windows_size.second - game.pillars->hole_size_half);
    QLearning* ai = new QLearning((x / 10 + 5) * (y / 10 + 5), 2);

    int max_i = 0;
    while (true) {
        int i = 0;
        game.init();
        while (true) {
            // play
            int state = toState(*game.bird, *game.pillars);
            int action = ai->chooseAction(state);
            int isSuccess = game.play(action);

            // feedback ai
            double R = 10;
            if (!isSuccess)
                R = -100;
            else if (game.pillars->pillarHoles[0].first + game.pillars->pillar_width <= game.bird->position.first)
                R = 50;
            ai->feedback(state, action, R);

            if (!isSuccess)
                break;
            i++;
        }
        if (i > max_i) {
            max_i = i;
            printf("%d ", i);
        }
        
        if (i > 10000)
            break;
    }
    return ai;
}