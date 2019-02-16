#pragma once
#include <math.h>

struct vector_i{
	int x;
	int y;
};

struct vector_f{
	float x;
	float y;
};

struct vector_i RotatePointCircle(float angle,float x,float y, float cx, float cy);

struct vector_i RotatePoint(float angle_rad,float x,float y);

struct vector_f BounceFromCircle(float x, float y, float vx, float vy);

float PointDistance(float ax,float ay,float bx,float by);
