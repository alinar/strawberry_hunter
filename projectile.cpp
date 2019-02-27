#pragma once
#include "projectile.h"
#include "object.h"
#include "tools.h"
#include <iostream>
#include "lockylist.h"
#include <mutex>

Sprite Projectile::projectile_sprite;
bool Projectile::has_sprite = false;
LockyList<Projectile*> Projectile::projectiles;
uint32_t Projectile::last_projectile_time = 0;

Projectile::Projectile(float angle_in):Object(512,140){
	//std::lock_guard<std::mutex> lock(mtx);
	LoadSprite("images/Projectile.png");
	p_angle = angle_in;
	start_time = currentTimeInMs();
	Projectile::last_projectile_time = start_time;
	Projectile::projectiles.lock();
	Projectile::projectiles.push_back(this);
	Projectile::projectiles.unlock();
}

void Projectile::LoadSprite(const char* file_name){
        if (!Projectile::has_sprite){
                Projectile::projectile_sprite = loadSprite(file_name);
                Projectile::has_sprite = true;
        }	
}

Projectile::~Projectile(){
	//std::lock_guard<std::mutex> lock(mtx);
	Projectile::projectiles.remove(this);
}

bool Projectile::Draw(){
	//std::lock_guard<std::mutex> lock(mtx);
	if (PointDistance(x,y,512,512)>390) return false;        
	uint32_t dt = currentTimeInMs() - start_time;
	int travel_distance=dt * speed;
	struct vector_i vec = RotatePointCircle(p_angle,512,140+travel_distance, 0 , 512 - 140-travel_distance);
	x=vec.x;
	y=vec.y;
	drawSprite(Projectile::projectile_sprite,x,y);
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
