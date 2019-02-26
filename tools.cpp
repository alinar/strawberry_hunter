#pragma once
#include <cmath>
#include "tools.h"
#include <iostream>

struct vector_i RotatePointCircle(float angle_deg,float x,float y, float cx, float cy){
        float s = sin(angle_deg*M_PI/180);
        float c = cos(angle_deg*M_PI/180);
        float cxnew = (-1*cx) * c - (-1*cy) * s;
        float cynew = (-1*cx) * s + (-1*cy) * c;
        x = cxnew + x + cx;
        y = cynew + y + cy;
	struct vector_i vec;
	vec.x = (int)round(x);
	vec.y = (int)round(y);
	return vec;
}

float PointDistance(float ax,float ay,float bx,float by){
  return sqrt(pow(ax-bx,2) + pow(ay - by,2));
}

struct vector_f RotateVector(float angle_rad,float x,float y){
	float s = sin(angle_rad);
        float c = cos(angle_rad);
        float xnew = (x) * c - (y) * s;
        float ynew = (x) * s + (y) * c;
	struct vector_f vec;
        vec.x = xnew;
        vec.y = ynew;
	return vec;
}

struct vector_f BounceFromCircle(float vx, float vy,float x,float y){
	/*speed vector after incident*/	
	float angle; 
	// angle of incident using cross product	
	angle = asin( (vx*(y-512) - vy*(x-512)) / (PointDistance(vx,vy,0,0)*PointDistance(x,y,512,512))  );
	//
	return RotateVector(2*angle,-1*vx,-1*vy);	
}


