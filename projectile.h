#pragma once
#include "object.h"
#include <math.h>
#include "gun.h"
#include <iostream>
#include <list>
#include <mutex>
class Projectile:public Object{
	public:
		mutable std::mutex mtx;
		static std::list<Projectile*> projectiles;
		std::list<Projectile*>::iterator it;
		float p_angle;
		uint32_t start_time;
                static uint32_t last_projectile_time ;
                float speed = 0.2;
		Projectile(float);
		~Projectile();
		virtual bool Draw();
		static void DrawAll();
		static void DeleteAll();
};

