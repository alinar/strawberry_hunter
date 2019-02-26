#pragma once
#include "projectile.h"
#include "object.h"
#include "tools.h"
#include <iostream>
#include "lockylist.h"
#include <mutex>

LockyList<Projectile*> Projectile::projectiles;
uint32_t Projectile::last_projectile_time = 0;

Projectile::Projectile(float angle_in):Object("images/Projectile.png",512,140){
	p_angle = angle_in;
	start_time = currentTimeInMs();
	Projectile::last_projectile_time = start_time;
	Projectile::projectiles.lock();
	Projectile::projectiles.push_back(this);
	Projectile::projectiles.unlock();
}

Projectile::~Projectile(){
	Projectile::projectiles.remove(this);
}

bool Projectile::Draw(){
	if (PointDistance(x,y,512,512)>390) return false;        
	uint32_t dt = currentTimeInMs() - start_time;
	int travel_distance=dt * speed;
	drawSpriteWithRotation(sprite, 512 , 140+travel_distance, p_angle, 0 ,512 - 140-travel_distance );
	struct vector_i vec = RotatePointCircle(p_angle,512,140+travel_distance, 0 , 512 - 140-travel_distance);
	x=vec.x;
	y=vec.y;
	drawSprite(sprite,x,y);
	return true;
}

void Projectile::DrawAll(){
	LockyList<Projectile*>::iterator projectile_it;
	Projectile::projectiles.lock();
	for (projectile_it = Projectile::projectiles.begin(); projectile_it != Projectile::projectiles.end() ; ){
		if ( !((*projectile_it)->Draw()) ) {
			Projectile* aux = *projectile_it;
			projectile_it++;
			delete aux;
		}
		else projectile_it++;
	}
	Projectile::projectiles.unlock();
}

void Projectile::DeleteAll(){
	LockyList<Projectile*>::iterator projectile_it;
	Projectile::projectiles.lock();
	for (projectile_it = Projectile::projectiles.begin(); projectile_it != Projectile::projectiles.end() ; ){
		Projectile* aux = *projectile_it;
		projectile_it++;
		delete aux;
	}
	Projectile::projectiles.unlock();
}
