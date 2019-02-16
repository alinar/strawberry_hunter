#pragma once
#include "gun.h"
#include "game_engine.h"
#include "object.h"
#include "projectile.h"
#include "tools.h"
#include <iostream>
Gun::Gun():Object("images/Gun.png",512,140){}

bool Gun::Draw(){
	if (!active) return false;
	GetKeyInput();
	drawSpriteWithRotation(sprite,  512-sprite.width/2 , 140-sprite.height/2, angle, sprite.width/2, 512-140+sprite.height/2);
	struct vector_i vec = RotatePointCircle(angle,512,140, 0 , 512 - 140);
	x = vec.x;
	y = vec.y;
	return true;
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
