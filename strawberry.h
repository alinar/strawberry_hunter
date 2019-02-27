#pragma once
#include "object.h"
#include <mutex>
#include "lockylist.h"

class Strawberry:public Object{
	public:
		mutable std::mutex mtx;
		static Sprite strawberry_sprite;
		static bool has_sprite;
		static LockyList<Strawberry*> strawberrys;
		bool active = true;
		float speed_x  ;
		float speed_y  ;
		uint32_t start_time;
		Strawberry(int x_in,int y_in,float vx=0.0,float vy=0.0006);
		~Strawberry();
		void LoadSprite(const char*);
		bool Draw();
		static void DrawAll();
		static void DeleteAll();
		void GotShot();
};

