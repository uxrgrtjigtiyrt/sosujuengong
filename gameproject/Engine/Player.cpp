#include "stdafx.h"
#include "Player.h"


Player::Player() {
	isJump = false;
	notHole = true;
	doubleJump = false;
	slide = false;
	isDead = false;

	sl = 0;
	gravity = 0;
	
	playerAnimation = new Animation(10);
	playerAnimation->AddFrame("Resources/Image/player1.png");
	playerAnimation->AddFrame("Resources/Image/player2.png");
	playerAnimation->AddFrame("Resources/Image/player3.png");

	AddChild(playerAnimation);

	rect = playerAnimation->getRect();

	playerAnimationS = new Sprite("Resources/Image/player-slide.png");

	AddChild(playerAnimationS);
	setPos(200, 450);
	
	playerAnimationSJ = new Sprite("Resources/Image/jump3.png");

	AddChild(playerAnimationSJ);

	playerAnimationJ = new Animation(10);
	playerAnimationJ->AddFrame("Resources/Image/jump5.png");
	playerAnimationJ->AddFrame("Resources/Image/jump4.png");
	playerAnimationJ->AddFrame("Resources/Image/jump1.png");
	playerAnimationJ->AddFrame("Resources/Image/jump2.png");
	playerAnimationJ->AddFrame("Resources/Image/jump6.png");

	AddChild(playerAnimationJ);




}

Player::~Player() {

}

void Player::Render() {
	Object::Render();
	if(isJump) {
		if (doubleJump) {
			playerAnimationJ->Render();
		}
		else {
			playerAnimationSJ->Render();
		}
	}
	else if (!slide) {
		playerAnimation->Render();
	}
	else {
		playerAnimationS->Render();
	}
}

void Player::Update(float dTime) {
	if (!isDead) {
		gravity += 70;

		setPos(getPosX(), getPosY() + gravity * dTime);

		if (isJump) {

			rect = playerAnimationJ->getRect();
			Object::Render();

			setPos(getPosX(), getPosY() - 1700 * dTime);
			playerAnimationJ->Update(dTime);
			if (doubleJump) {
				setPos(getPosX(), getPosY() - 1700 * dTime * dTime);
			}
			else {
			}

		}
		if (getPosY() > 450 + sl && !notHole) {

			setPos(getPosX(), 450 + sl);
			doubleJump = false;
			isJump = false;
			setScale(1, 1);
			gravity = 0;
		}

		if (isJump) {
			if (inputManager->GetKeyState(VK_UP) == KEY_DOWN && !doubleJump) {
				doubleJump = true;
				gravity = 15;

			}
		}
		if (inputManager->GetKeyState(VK_UP) == KEY_DOWN && !isJump) {
			if (getPosY() == 450 + sl) {
				isJump = true;
				gravity = 0;

			}
		}
		if (!isJump) {
			if (inputManager->GetKeyState(VK_DOWN) == KEY_DOWN) {
				slide = true;
				rect = playerAnimationS->getRect();
				sl = 50;
				setPos(getPosX(), getPosY() + sl);
			}
		}

		if (slide) {
			Object::Render();

			if (inputManager->GetKeyState(VK_DOWN) == KEY_UP || getPosY() < 450) {
				slide = false;
				rect = playerAnimation->getRect();

				if (getPosY() >= 450 + sl) {
					setPos(getPosX(), 450);
				}
				sl = 0;
			}
		}
		else {

			playerAnimation->Update(dTime);
		}
	}
}

void Player::ifHole() {
	notHole = true;
}

void Player::ifNotHole() {
	notHole = false;
}
void Player::Dead() {
	isDead = true;
}