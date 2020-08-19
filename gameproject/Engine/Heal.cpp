#include "stdafx.h"
#include "Heal.h"

Heal::Heal() {
	heal = new Sprite("Resources/Image/heal.png");
	heal->setScale(1,1);
	AddChild(heal);

	rect = heal->getRect();
}

Heal::~Heal() {

}

void Heal::Update(float dTime) {
	Object::Update(dTime);
	setPos(getPosX() - RUNNING_SPEED * dTime, getPosY());
}

void Heal::Render() {
	Object::Render();
	heal->Render();
}