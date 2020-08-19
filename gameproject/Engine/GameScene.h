#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Animation.h"
#include "MainScene.h"
#include <list>
//Object Headers
#include "Number.h"
#include "Player.h"
#include "Background.h"
#include "Bridge.h"
#include "Coin.h"
#include "Obstacle.h"
#include "Object.h"
#include "Heal.h"

class GameScene : public Scene
{
private :
	int score, coinCounter;
	bool isDead;
	bool backgroundInstatiate, bridgeInstantiate, obstacleInstantiate,healInstantiate;
	float coinInstDelayTimer,obstacleInstDelayTimer,healInstDelayTimer;
	float time;
	float width;
	std::list<Background *> backgroundList;
	std::list<Bridge *> bridgeList;
	std::list<Coin*> coinList;
	std::list<Obstacle*> obstacleList;
	std::list<Heal*> healList;
	Sprite* healthIcon;
	Sprite* bar;
	Number *numArray[4];
	Player* player;
public :
	GameScene();
	~GameScene();

	void Damage(float dTime);
	void Render();
	void Update(float dTime);

	void CollisionCheck();
	void OptimizationObject();
	void InstantiateObject();
	
	void TimerSetting(float dTime);
	void UISetting();
};