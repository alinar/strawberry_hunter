#include "game_engine.h"
#include "object.h"
#include "gun.h"
#include "projectile.h"
#include "strawberry.h"
#include <iostream>
#include <list>
#include <math.h>
#include "tools.h"
#include <thread>

bool CollisionDetection(Gun &gun){
	while(true){
	if (!gun.active) break;	
	std::list<Strawberry*>::iterator strawberry_it;
	std::list<Projectile*>::iterator projectile_it;
	float dist;
	for (strawberry_it = Strawberry::strawberrys.begin(); strawberry_it != Strawberry::strawberrys.end() ; ++strawberry_it){
		(*strawberry_it)->mtx.lock();
		for (projectile_it = Projectile::projectiles.begin(); projectile_it != Projectile::projectiles.end() ; ++projectile_it){
			(*projectile_it)->mtx.lock();
			dist = PointDistance((*strawberry_it)->x,(*strawberry_it)->y,(*projectile_it)->x,(*projectile_it)->y);	
			if (dist<10.0) (*strawberry_it)->GotShot(); 
			(*projectile_it)->mtx.unlock();
		}
		dist = PointDistance((*strawberry_it)->x,(*strawberry_it)->y,gun.x,gun.y);
		if (dist<40.0) gun.FinishGame();
		(*strawberry_it)->mtx.unlock();
	}
	sleep(100);	
	}
}

void InitScene(){
	Strawberry *strawberry1 = new Strawberry(550,500,0.0005,0.0001);
	Strawberry *strawberry2 = new Strawberry(450,500,0.0005,0.0001);
	Strawberry *strawberry3 = new Strawberry(500,550,0.0005,0.0001);
	Strawberry *strawberry4 = new Strawberry(400,550,0.0005,0.0001);
	Strawberry *strawberry5 = new Strawberry(450,550,0.0005,0.0001);
	Strawberry *strawberry6 = new Strawberry(450,550,0.0005,0.0001);
}

int main() {
  initEngine(1024, 1024);
  Sprite background = loadSprite("images/BackGround.png"); 
  Sprite frame    = loadSprite("images/Frame.png");
  InitScene();
  Gun gun = Gun();
  std::thread collision_detector (CollisionDetection,std::ref(gun));
  while (startFrame()){
	drawSprite(background,0,0);
	/***/
	Projectile::DrawAll();
	Strawberry::DrawAll();
	bool r = gun.Draw();
	/***/
	drawSprite(frame,0,0);
	presentFrame();
	if (Strawberry::strawberrys.size()==0 || !r) {
		std::cout <<"Game Finished!\n"<<std::flush; 
		break;
	}
       	sleep(50);
  }
  // Clean up gmae_game_engine
  collision_detector.join();
  Projectile::DeleteAll();
  Strawberry::DeleteAll();
  destroyEngine();
  return 0;
}
