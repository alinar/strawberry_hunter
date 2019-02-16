#pragma once
#include "game_engine.h"
#include <cstdint>
#include <list>
class Object{

	public:
		Sprite sprite;
		volatile float x, y;
		explicit Object(const char *sprite_file, float x, float y);
		virtual ~Object();
		bool operator==(Object const& b);
		/***********************/
		virtual bool Draw();
		
};
