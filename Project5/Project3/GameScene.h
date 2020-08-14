#pragma once
#include "Scene.h"
#include"Sprite.h"
#include"Animation.h"
#include"MainScene.h"
#include"Number.h"
#include<list>

class GameScene : public Scene
{
private:
	float gravity;
	bool doubleJump, isJump;
	int score;

	std::list<Sprite*> backgroundList;
	std::list<Sprite*> bridgeList;
	std::list<Sprite*> obstacleList;
	std::list<Sprite*> coinList;
	
	Number numArray[4];

	Animation* player;
public:
	GameScene();
	~GameScene();

	void Render();
	void Update(float dTime);
};

