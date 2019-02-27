#pragma once
#include "game_engine.h"
#include <cstdint>
#include <list>

class Object{
	public:
		volatile float x, y;
		explicit Object( float x, float y);
		virtual ~Object();
		bool operator==(Object const& b);
		/***********************/
		virtual bool Draw();
};
