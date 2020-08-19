#pragma once
#include "Object.h"
#include "Sprite.h"

class Heal : public Object
{
private:
	Sprite* heal;
public:
	Heal();
	~Heal();

	void Update(float dTime);
	void Render();
};

