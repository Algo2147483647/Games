class FlappyBird {
public:
	int windowWidth = 400, 
		windowHeight = 600;
	Graphics g{ windowWidth, windowHeight };
	int birdY = windowHeight / 2, 
		birdX = 100, 
		pillarsWidth = 80,
		holeHeight = 100,
		pillarsX = windowWidth,
		pillarsY = 0;
	int pillarsSpeed = 10,
		BirdSpeed = 20;
	QLearning q{ (windowWidth + pillarsWidth) / (2 * pillarsSpeed) * (windowHeight * 2) / BirdSpeed, 2 };

	void play() {
		init();
		bool flag = 0;
		long long time = 0;
		while (true) {
			//pillars &  boid
			pillarsX -= pillarsSpeed;
			birdY -= BirdSpeed;
			if (flag) {
				int dx = pillarsX - birdX + birdX + pillarsWidth;
				int dy = pillarsY - birdY + windowHeight;
				int state = dy / BirdSpeed * windowWidth / (2 * pillarsSpeed) + dx / (2 * pillarsSpeed);
				int action = q.chooseAction(state);

				if (action)
					birdY += 3 * BirdSpeed;

				// Q-learning
				double R = 1;
				if (judgeLose()) { R = -100; init(); }
				else if (pillarsX <= -pillarsWidth) { R = 15; initPillars(); }
				q.feedback(state, action, R);
			}
			flag = !flag;

			// draw
			if (time % 100000000 == 0 && q.greedy > 0)q.greedy -= 0.1;
			if (time++ > 1e9) {
				q.greedy = 0;
				drawPillars(pillarsX, windowHeight - pillarsY, &g);
				drawBird(birdX, windowHeight - birdY, &g);
				Delay(40);
				g.PicWrite("D:/LIGU.ppm");
				g.clear(0);
			}
		}
	}

	void drawBird(int x, int y, Graphics* g) {
		g->PaintSize = 10; g->PaintColor = 0xFFFF00;
		g->drawPoint(x, y);
		g->PaintSize = 0; g->PaintColor = 0xFFFFFF;
	}

	void drawPillars(int x, int y, Graphics* g) {
		g->PaintColor = 0x00FF00;
		g->drawRectangle(x, 0, x + pillarsWidth, y - holeHeight);
		g->drawRectangle(x, y, x + pillarsWidth, windowHeight);
		g->PaintColor = 0xFFFFFF;
	}
};

int main() {
	FlappyBird fb;
	fb.play();
}
