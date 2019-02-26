#include "game_engine.h"
#include "object.h"
#include "gun.h"
#include "projectile.h"
#include "strawberry.h"
#include <iostream>
#include <math.h>
#include "tools.h"
#include "lockylist.h"
#include <list>
#include <thread>

bool CollisionDetection(Gun &gun){
	while(true){
	if (!gun.active) break;	
	LockyList<Strawberry*>::iterator strawberry_it;
	LockyList<Projectile*>::iterator projectile_it;
	float dist;
	Strawberry::strawberrys.lock();
	for (strawberry_it = Strawberry::strawberrys.begin(); strawberry_it != Strawberry::strawberrys.end() ; ++strawberry_it){
		Projectile::projectiles.lock();
		for (projectile_it = Projectile::projectiles.begin(); projectile_it != Projectile::projectiles.end() ; ++projectile_it){
			dist = PointDistance((*strawberry_it)->x,(*strawberry_it)->y,(*projectile_it)->x,(*projectile_it)->y);	
			if (dist<10.0) (*strawberry_it)->GotShot(); 
		}
		dist = PointDistance((*strawberry_it)->x,(*strawberry_it)->y,gun.x,gun.y);
		Projectile::projectiles.unlock();
		if (dist<40.0) gun.FinishGame();
	}
	Strawberry::strawberrys.unlock();
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
  initEngine("Strawberry Hunter",1024, 1024);
  Sprite background = loadSprite("images/BackGround.png"); 
  Sprite frame    = loadSprite("images/Frame.png");
  InitScene();
  Gun gun = Gun();
  while(true){
	if (!startFrame()){
		sleep(100);
		continue;
	}
	drawSprite(background,0,0);
	/***/
	Projectile::DrawAll();
	Strawberry::DrawAll();
	bool r = gun.Draw();
	/***/
	drawSprite(frame,0,0);
	presentFrame();
	Strawberry::strawberrys.lock();
	if (Strawberry::strawberrys.size()==0 || !r) {
		Strawberry::strawberrys.unlock();
		std::cout <<"Game Finished!\n"<<std::flush; 
		break;
	}
	Strawberry::strawberrys.unlock();
       	sleep(50);
  }
  // Wait for the thread to finish. 
  //collision_detector.join();
  // Clean up gmae_game_engine
  Projectile::DeleteAll();
  Strawberry::DeleteAll();
  destroyEngine();
  return 0;
}
