#include "stdafx.h"
#include "Background.h"

Background::Background() {
	background = new Sprite("Resources/Image/Background.jpg");
	AddChild(background);
}

Background::~Background() {

}

void Background::Render() {
	Object::Render();
	background->Render();
}

void Background::Update(float dTime) {
	Object::Update(dTime);
	setPos(getPosX() - RUNNING_SPEED * dTime, getPosY());
}