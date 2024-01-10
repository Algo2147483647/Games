#ifndef BOIDS_H
#define BOIDS_H
#include "LiGu_Graphics/Graphics3D.h"
#include "LiGu_AlgorithmLib/ComputationalGeometry.h"
#include <ctime> 

void Delay(int time){  //time*1000为秒数 
	clock_t now = clock(); 
	while (clock() - now < time); 
}


void main() {
	Graphics3D g{ 1000, 1000 };

	// set Graphics3D
	Mat<> Axis(3); Axis[0] = 0.7; Axis[1] = 0.4; Axis[2] = 0.59;
	Mat<> center(3); center[0] = 500; center[1] = 500; center[2] = 500;
	double theta = 1;
	// 
	Mat<> zero(3), CuboidL(3), CuboidR(3);
	CuboidR[0] = size; CuboidR[1] = size; CuboidR[2] = size; CuboidL[0] = -size; CuboidL[1] = -size; CuboidL[2] = -size;
	// set Boids_cell
	int N = 200;
	Boids_cell cell[200];
	for (int i = 0; i < N; i++) {
		cell[i].r.rands(3, 1, -size / 2, size / 2);
		cell[i].v.rands(3, 1, 0, 1);
		cell[i].v.normalization();
	}
	Mat<> temp;
	while (1) {
		theta += 0.01; if (theta >= 2 * 3.1415926) theta = 0;
		g.TransformMat.E(4);
		g.rotate(Axis, theta, zero);
		g.translation(center);

		play(cell, N);
		for (int i = 0; i < N; i++)
			g.drawLine(cell[i].r, temp.add(temp.mul(10, cell[i].v), cell[i].r));

		Delay(20);
		g.g->PicWrite("D:/LIGU.ppm");
		g.g->clear(0);
		g.drawCuboid(CuboidL, CuboidR);
	}
}
#endif
