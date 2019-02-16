#pragma once
#include "game_engine.h"
#include "object.h"
#include <cstdint>
#include <math.h>
#include <iostream>

Object::Object(const char *sprite_file, float x_in, float y_in){
	sprite = loadSprite(sprite_file);
	x = x_in;
	y = y_in;
}


Object::~Object(){
}

bool Object::operator==(Object const& b){
	if (this == &b) return true;
	else return false;
}

bool Object::Draw(){
}

