#include "QLearning.h"

QLearning::QLearning(int _num_state, int _num_action) : dis(0.0, 1.0), num_state(_num_state), num_action(_num_action), QTable(_num_state, std::vector<double>(_num_action, 0)) {}

double QLearning::randDouble_01() {
	std::mt19937_64 gen(rd());
	return dis(gen);
}

int QLearning::chooseAction(int state) {
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

void QLearning::feedback(int state, int action, double R) {
    double t = -DBL_MAX;
    for (int i = 0; i < num_action; i++)
        t = QTable[state][i] > t ? QTable[state][i] : t;

    QTable[preState][action] = (1 - learn_rate) * QTable[preState][action] + learn_rate * (R + gamma * t);
    preState = state;
}