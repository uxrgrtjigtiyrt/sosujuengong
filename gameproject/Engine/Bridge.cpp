#include "stdafx.h"
#include "Bridge.h"

Bridge::Bridge() {
	bridge = new Sprite("Resources/Image/LoopMap.png");
	AddChild(bridge);

	rect = bridge->getRect();
}

Bridge::Bridge(int kind) {
	switch (kind) {
	case 1:
		bridge = new Sprite("Resources/Image/LoopMap2.png");
		AddChild(bridge);
		rect = bridge->getRect();
		break;
	default:
		bridge = new Sprite("Resources/Image/LoopMap.png");
		AddChild(bridge);
		rect = bridge->getRect();
		break;
}
}

Bridge::~Bridge() {

}

void Bridge::Render() {
	Object::Render();
	bridge->Render();
}

void Bridge::Update(float dTime) {
	Object::Update(dTime);
	setPos(getPosX() - RUNNING_SPEED *dTime, getPosY());
}