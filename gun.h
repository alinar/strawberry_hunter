#pragma once
#include "object.h"
#include <math.h>
#include "game_engine.h"

class Gun:public Object{
	public:
		float angle = 0;
		bool active = true;
		Gun();
		void Rotate(float d);
		void GetKeyInput();
		virtual bool Draw();
		void Shoot();
		void FinishGame();
};

