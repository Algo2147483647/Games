#ifndef QLEARNING_H
#define QLEARNING_H

#include <vector>
#include <cfloat>
#include "./core/FlappyBird.h"

using namespace std;

class QLearning {
public:
	double learn_rate = 0.6;
	double gamma = 0.8;
	double greedy = 0.5;
	int num_action;
	int num_state;
	int preState = 0;
	vector<vector<double>> QTable;

    std::random_device rd;
    std::uniform_real_distribution<double> dis;
	
    QLearning(int _num_state, int _num_action);
    double randDouble_01();
    int chooseAction(int state);
	void feedback(int state, int action, double R);
};
#endif // !QLEARNING