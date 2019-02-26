#pragma once
#include "object.h"
#include "strawberry.h"
#include "tools.h"
#include <iostream>
#include <mutex>
#include "lockylist.h"

LockyList<Strawberry*> Strawberry::strawberrys;

Strawberry::Strawberry(int x_in,int y_in,float vx,float vy):Object("images/Strawberry.png",x_in,y_in){
	//std::lock_guard<std::mutex> lock(mtx);
	speed_x = vx;
	speed_y = vy;
	start_time = currentTimeInMs();
	strawberrys.push_back(this);
	}

Strawberry::~Strawberry(){
	//std::lock_guard<std::mutex> lock(mtx);
	Strawberry::strawberrys.remove(this);
}

void Strawberry::GotShot(){
	/*atomic*/
	active = false;
}	

bool Strawberry::Draw(){
	//std::lock_guard<std::mutex> lock(mtx);
	if (!active) return false; 
	else if (PointDistance(x,y,512,512)>390  ) {
		// touch the wall and bounce back.
		struct vector_f vec = BounceFromCircle(speed_x,speed_y,x,y);
		speed_x = vec.x;
		speed_y = vec.y;
	}                
	uint32_t dt = currentTimeInMs() - start_time;
	x+=speed_x*dt;
	y+=speed_y*dt;
	drawSprite(sprite , x-sprite.width/2 , y-sprite.height/2);
	return true;
}


void Strawberry::DrawAll(){
        LockyList<Strawberry*>::iterator strawberry_it;
	Strawberry::strawberrys.lock();
        for (strawberry_it = Strawberry::strawberrys.begin(); strawberry_it != Strawberry::strawberrys.end() ; ++strawberry_it){
		if (!((*strawberry_it)->Draw()) ){
			// delete non active strawberrys.
			Strawberry* aux = *strawberry_it;
			strawberry_it++;
			delete aux;
		}
        }
	Strawberry::strawberrys.unlock();
}

void Strawberry::DeleteAll(){
	LockyList<Strawberry*>::iterator strawberry_it;
	Strawberry::strawberrys.lock();
	for (strawberry_it = Strawberry::strawberrys.begin(); strawberry_it != Strawberry::strawberrys.end() ; ++strawberry_it){
		Strawberry* aux = *strawberry_it;
		strawberry_it++;
		delete aux;
	}
	Strawberry::strawberrys.unlock();
}


