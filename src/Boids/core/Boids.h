#ifndef BOIDS_H
#define BOIDS_H

#include <array> 

using namespace std;

class Boids {
public:
	struct Boids_cell { 
        array<double, 3> r, v, a;
    };

	double size = 300;
	double visualField = 20, visualAngle = -0.5; // 能见范围 // 能见角度cosθ
	double deltaT = 1, speed = 3;
	double weight[4] = { 1,1,1,4 }; // 各规则的权值
	array<double, 3>* obstacleAvoidance_direction;
 
	inline void play(Boids_cell cell[], int n) {
		for (int i = 0; i < n; i++) {
			rule(cell, n, i);
			obstacleAvoidance(cell[i]);
		}
		array<double, 3> temp(3);
		for (int i = 0; i < n; i++) {
			cell[i].v.add(cell[i].v, temp.mul(deltaT, cell[i].a));
			cell[i].v.normalization();
			cell[i].r.add(cell[i].r, temp.mul(deltaT * speed, cell[i].v));
		}
	}

	inline void rule(Boids_cell cell[], int n, int index) {
		array<double, 3> distance(3);
		array<double, 3> avoidDirection(3), groupVelocity(3), groupCenter(3), temp;
		int groupNum = 0;
		for (int i = 0; i < n; i++) {
			if (i == index)
                continue;

			// 能见范围
			distance.add(cell[i].r, cell[index].r.negative(distance));

			if (distance.norm() > visualField)
                continue;

			// 能见角度
			double angle = distance.dot(distance, cell[index].v) / (distance.norm() * cell[index].v.norm()); // cosθ = a * b / (|a| * |b|)

			if (angle < visualAngle)
                continue;
			groupNum++;
            
			//[Rule 1]: collisionAvoid  [Rule 2]: velocityMatching  [Rule 3]: flockCentering
			avoidDirection.add(avoidDirection, temp.mul(1 / distance.norm(), distance));
			groupVelocity.add(groupVelocity, cell[i].v);
			groupCenter.add(groupCenter, distance);
		}
		avoidDirection.negative(avoidDirection);

		// Update Acceleration
		cell[index].a.clean();
		if (groupNum == 0) return;
		cell[index].a.add(cell[index].a, avoidDirection.mul(weight[0], avoidDirection.normalization()));
		cell[index].a.add(cell[index].a, groupVelocity.mul(weight[1], groupVelocity.normalization()));
		cell[index].a.add(cell[index].a, groupCenter.mul(weight[2], groupCenter.normalization()));
	}
 
	inline void obstacleAvoidance(Boids_cell& cell) {
		static array<double, 3>* obstacleAvoidance_direction;
		static bool o = true;

		if (o) {
            o = false; 
            obstacleAvoidance_direction = Geometry::getSphereFibonacciPoint(200);
        }
           
		// 确定坐标变换矩阵
		array<double, 3> rorateAxis(3), rotateMat, tmp(3);
		GraphicsND::rotate(
			rorateAxis.cross(cell.v, obstacleAvoidance_direction[0]).normalization(),
			-acos(tmp.dot(cell.v, obstacleAvoidance_direction[0])), 
			tmp, rotateMat.E(4)
		); rotateMat.block(1, 3, 1, 3, rotateMat);

		// 碰撞检测
		array<double, 3> derection;
		for (int k = 0; k < 200; k++) {
			derection.mul(rotateMat, obstacleAvoidance_direction[k]);
			bool flag = 1; int distance = visualField;
			while (--distance > 0) {
				tmp.add(tmp.mul(distance, derection), cell.r);
				if (obstacleFunction(tmp)) { flag = 0; break; }
			}
			if (flag)break;
		}
		cell.a += (derection *= weight[3]);
	}

	inline bool obstacleFunction(array<double, 3>& point) {
		for (int i = 0; i < 3; i++) {
			if (fabs(point[i]) >= size)return true;
		}
		return false;
	}
}

#endif