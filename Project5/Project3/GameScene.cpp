#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene() {
	gravity = 0;
	doubleJump = false;
	isJump = false;
	score = 0;



	backgroundList.push_back(new Sprite("Resources/Image/Background.png"));
	Sprite* tmpBackground = new Sprite("Resources/Image/Background.png");
	tmpBackground->setPos(SCREEN_WIDTH, 0);
	backgroundList.push_back(tmpBackground);


	Sprite* tempBridge = new Sprite("Resources/Image/LoopMap.png");
	tempBridge->setPos(0, 500);
	bridgeList.push_back(tempBridge);

	Sprite* tmpBridge = new Sprite("Resources/Image/LoopMap.png");
	tmpBridge->setPos(SCREEN_WIDTH, 500);
	bridgeList.push_back(tmpBridge);

	Sprite* tmpCoin = new Sprite("Resources/Image/coin-yellow.png");
	tmpCoin->setPos(SCREEN_WIDTH+70, 400);
	coinList.push_back(tmpCoin);

	Sprite* tmpObstacle = new Sprite("Resources/Image/Drop.png");
	tmpObstacle->setPos(SCREEN_WIDTH, 400);
	obstacleList.push_back(tmpObstacle);

	player = new Animation(2);
	player->AddFrame("Resources/Image/player-stop.png");
	player->AddFrame("Resources/Image/player-run.png");
	player->setPos(50, 100);

	for (int i = 0; i < 4; i++) {
		numArray[i].setPos(0 + 60 * i, 10);
	}
}

GameScene::~GameScene() {

}

void GameScene::Render() {
	for (auto& background : backgroundList) {
		background->Render();
	}

	for (auto& bridge : bridgeList) {
		bridge->Render();
	}

	for (auto& obstacle : obstacleList) {
		obstacle->Render();
	}

	for (auto& coin : coinList) {
		coin->Render();
	}

	for (int i = 0; i < 4; i++) {
		numArray[i].Render();
	}

	player->Render();
}
void GameScene::Update(float dTime) {
	Scene::Update(dTime);

	int randNum = rand() % 10 + 1;
	if (randNum == 1) {
		Sprite* tmpCoin = new Sprite("Resources/Image/coin-yellow.png");
		tmpCoin->setPos(SCREEN_WIDTH + 100, 400);
		coinList.push_back(tmpCoin);
	}

	numArray[0].setNum(score / 1000);
	numArray[1].setNum(score % 1000/100);
	numArray[2].setNum(score % 100/10);
	numArray[3].setNum(score % 10);

	gravity += 9.8f;

	player->setPos(player->getPosX(), player->getPosY() + gravity * dTime);

	if (isJump) {
		player->setPos(player->getPosX(), player->getPosY() - 300 * dTime);
		if (doubleJump) {
			player->setPos(player->getPosX(), player->getPosY() - 300 * dTime);
		}
		if (inputManager->GetKeyState(VK_UP) == KEY_DOWN) {
			doubleJump = true;
		}
	}

	if (player->getPosY() > 340) {
		player->setPos(player->getPosX(), 340);
		doubleJump = false;
		isJump = false;
	}

	if (inputManager->GetKeyState(VK_UP) == KEY_DOWN) {
		if (player->getPosY() == 340) {
			isJump = true;
			gravity = 0;
		}
	}

	player->Update(dTime);

	int backgroundDiff = 500 * dTime;

	for (auto iter = backgroundList.begin(); iter != backgroundList.end(); iter++) {
		(*iter)->setPos((*iter)->getPosX() - backgroundDiff, (*iter)->getPosY());

		if ((*iter)->getPosX() < -SCREEN_WIDTH) {
			SAFE_DELETE(*iter);
			iter = backgroundList.erase(iter);
			if (iter == backgroundList.end()) {
				break;
			}
			Sprite* tmpBackground = new Sprite("Resources/Image/Background.png");
			tmpBackground->setPos(SCREEN_WIDTH-10, 0);
			backgroundList.push_back(tmpBackground);
		}
	}

	for (auto iter = bridgeList.begin(); iter != bridgeList.end(); iter++) {
		(*iter)->setPos((*iter)->getPosX() - backgroundDiff, (*iter)->getPosY());

		if ((*iter)->getPosX() < -SCREEN_WIDTH) {
			SAFE_DELETE(*iter);
			iter = bridgeList.erase(iter);
			
			Sprite* tmpBridge = new Sprite("Resources/Image/LoopMap.png");
			tmpBridge->setPos(SCREEN_WIDTH, 500);
			bridgeList.push_back(tmpBridge);

			if (iter == bridgeList.end()) {
				break;
			}
		}
	}

	for (auto iter = obstacleList.begin(); iter != obstacleList.end(); iter++) {
		
		(*iter)->setPos((*iter)->getPosX() - backgroundDiff, (*iter)->getPosY());

		if (player->IsCollisionRect((*iter))) {
			sceneManager->ChangeScene(new MainScene());
			return;
		}

		if ((*iter)->getPosX() < -SCREEN_WIDTH) {
			SAFE_DELETE(*iter);
			iter = obstacleList.erase(iter);

			Sprite* tmpObstacle = new Sprite("Resources/Image/Drop.png");
			tmpObstacle->setPos(SCREEN_WIDTH, 400);
			obstacleList.push_back(tmpObstacle);

			if (iter == obstacleList.end()) {
				break;
			}
		}
	}

	for (auto iter = coinList.begin();
		iter != coinList.end(); iter++) {

		(*iter)->setPos((*iter)->getPosX() - backgroundDiff, (*iter)->getPosY());


		if ((*iter)->getPosX() < -SCREEN_WIDTH) {
			SAFE_DELETE(*iter);
			iter = coinList.erase(iter);

			if (iter == coinList.end()) {
				break;
			}
		}
	}

	for (auto iter = coinList.begin(); iter != coinList.end(); iter++) {
		if (player->IsCollisionRect((*iter))) {
			score += 1;
			SAFE_DELETE(*iter);
			iter = coinList.erase(iter);

			if (iter == coinList.end()) {
				break;
			}
		}
	}
}