#pragma once
#include "Object.h"
#include "Animation.h"

class Player : public Object
{
private :
	Animation* playerAnimationJ;
	Animation* playerAnimationD;
	Sprite* playerAnimationSJ;
	bool notHole;
	bool isDead;
	Animation* playerAnimation;
	Sprite* playerAnimationS;
	float gravity;
	float sl;
	bool doubleJump, isJump, slide;
	float gravitytmp;
public :
	Player();
	~Player();
	void Dead();
	void Render();
	void Update(float dTime);
	void setGravity();
	void onGravity();
	void ifHole();
	void ifNotHole();
};