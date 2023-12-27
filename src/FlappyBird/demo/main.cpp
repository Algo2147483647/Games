#include <QtWidgets/QApplication>
#include "FlappyBirdDemo.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	FlappyBirdDemo flappyBirdDemo;
	flappyBirdDemo.show();

	return a.exec();
}
