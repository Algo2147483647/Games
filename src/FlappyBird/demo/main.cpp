#include <QtWidgets/QApplication>
#include "FlappyBirdDemo.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	FlappyBirdDemo w;
	w.show();
	return a.exec();
}
