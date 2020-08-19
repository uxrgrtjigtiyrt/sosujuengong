#include "stdafx.h"
#include "Coin.h"

Coin::Coin() {
	isRed = false;
	coin = new Sprite("Resources/Image/jelly.png");
	
	AddChild(coin);
	
	rect = coin->getRect();
}

Coin::Coin(bool isRed) {
	this->isRed = isRed;

	if (isRed) {
		coin = new Sprite("Resources/Image/bearjelly.png");
	}
	else {
		coin = new Sprite("Resources/Image/jelly.png");
	}
	coin->setScale(1.5, 1.5);
	AddChild(coin);

	rect = coin->getRect();
}

Coin::~Coin() {

}

void Coin::Update(float dTime) {
	Object::Update(dTime);
	setPos(getPosX() - RUNNING_SPEED * dTime, getPosY());
}

void Coin::Render() {
	Object::Render();
	coin->Render();
}

bool Coin::getIsRed() {
	return isRed;
}