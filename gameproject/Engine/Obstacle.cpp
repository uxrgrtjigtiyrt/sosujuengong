#include "stdafx.h"
#include "Obstacle.h"

Obstacle::Obstacle() {
	obstacle = new Sprite("Resources/Image/obj1.png");
	AddChild(obstacle);

	rect = obstacle->getRect();
}

Obstacle::Obstacle(int kind) {
	switch (kind) {
	case 0:
		obstacle = new Sprite("Resources/Image/obj1.png");
		break;
	case 1:
		obstacle = new Sprite("Resources/Image/obj2.png");
		break;
	case 2:
		obstacle = new Sprite("Resources/Image/obj3.png");
		break;
	case 3:
		obstacle = new Sprite("Resources/Image/obj5.png");
		break;
	case 4:
		obstacle = new Sprite("Resources/Image/obj6.png");
		break;
	default:
		obstacle = new Sprite("Resources/Image/obj8.png");
		break;
	}
	AddChild(obstacle);

	rect = obstacle->getRect();
}

Obstacle::~Obstacle() {

}

void Obstacle::Update(float dTime) {
	Object::Update(dTime);
	if (getPosY() == 430) {
		setPos(getPosX() - RUNNING_SPEED * dTime*2, getPosY());
	}
	else {
		setPos(getPosX() - RUNNING_SPEED * dTime, getPosY());
	}
}

void Obstacle::Render() {
	Object::Render();
	obstacle->Render();
}