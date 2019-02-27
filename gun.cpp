#pragma once
#include "gun.h"
#include "game_engine.h"
#include "object.h"
#include "projectile.h"
#include "tools.h"
#include <iostream>

Sprite Gun::gun_sprite;
bool Gun::has_sprite = false;

Gun::Gun():Object(512,140){
	LoadSprite("images/Gun.png");
}

bool Gun::Draw(){
	if (!active) return false;
	GetKeyInput();
	drawSpriteWithRotation(Gun::gun_sprite,  512-Gun::gun_sprite.width/2 , 140-Gun::gun_sprite.height/2, angle, Gun::gun_sprite.width/2, 512-140+Gun::gun_sprite.height/2);
	struct vector_i vec = RotatePointCircle(angle,512,140, 0 , 512 - 140);
	x = vec.x;
	y = vec.y;
	return true;
}

void Gun::LoadSprite(const char * file_name){
	if (!Gun::has_sprite){
		Gun::gun_sprite = loadSprite(file_name);
		Gun::has_sprite = true;
	}
}

void Gun::Rotate(float d){
	angle = angle + d;
}

void Gun::FinishGame(){
	active = false;
}

void Gun::GetKeyInput(){
	if (isKeydown(LEFT)) Rotate(2);
	else if (isKeydown(RIGHT)) Rotate(-2);
	else if (isKeydown(SPACE)) {
		Shoot();
	}
}

void Gun::Shoot(){
	if  (currentTimeInMs() - Projectile::last_projectile_time > 300 ){	
		new Projectile(angle);
		}
}
