#ifndef QLEARNING
#define QLEARNING

#include <vector>
#include <cfloat>
#include "./core/FlappyBird.h"

using namespace std;

class QLearning {
public:
	double learn_rate = 0.6;
	double gamma = 0.8;
	double greedy = 0.9;
	int num_action = 0;
	int num_state = 0;
	double preState = 0;
	vector<vector<double>> QTable;
	
	QLearning(int _num_state, int _num_action) : num_state(_num_state), num_action(_num_action), QTable(_num_state, std::vector<double>(_num_action, 0)) {}

	double randDouble_01() {
		std::random_device rd;
		std::mt19937_64 gen(rd());
		std::uniform_real_distribution<double> dis(0.0, 1.0);
		return dis(gen);
	}

    int chooseAction(int state) {
        if (randDouble_01() < greedy)
            return static_cast<int>(randDouble_01() * num_action);

        int action = 0;
        double t = -DBL_MAX;
        for (int i = 0; i < num_action; i++) {
            if (QTable[state][i] > t) {
                t = QTable[state][i];
                action = i;
            }
        }
        return action;
    }

    void feedback(int state, int action, double R) {
        double t = -DBL_MAX;
        for (int i = 0; i < num_action; i++)
            t = QTable[state][i] > t ? QTable[state][i] : t;

        QTable[preState][action] = (1 - learn_rate) * QTable[preState][action] + learn_rate * (R + gamma * t);
        preState = state;
    }
};
#endif // !QLEARNING