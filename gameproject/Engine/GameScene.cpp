#include "stdafx.h"
#include "GameScene.h"
GameScene::GameScene() {
	score = 0;
	coinCounter = 0;
	time = 0;
	backgroundInstatiate = false;
	bridgeInstantiate = false;
	obstacleInstantiate = true;
	healInstantiate = false;
	isDead = false;

	obstacleInstDelayTimer = 0;
	coinInstDelayTimer = 0;
	healInstDelayTimer = 0;

	Background* background = new Background();
	background->setScale(3, 3);
	background->setPos(0, 0);
	
	backgroundList.push_back(background);
	AddObject(background);

	Bridge* bridge = new Bridge();
	bridge->setPos(-100, 630);
	bridgeList.push_back(bridge);
	AddObject(bridge);
	for (int i = 1; i <= 2; i++) {
		Bridge* bridge = new Bridge();
		bridge->setPos(i*740-100, 630);
		bridgeList.push_back(bridge);
		AddObject(bridge);
	}

	for (int i = 0; i < 4; i++) {
		numArray[i] = new Number();
		numArray[i]->setScale(1, 1);
		numArray[i]->setPos(700 + 60 * i, 5);
		AddUI(numArray[i]);
	}

	healthIcon = new Sprite("Resources/Image/health.png");
	AddObject(healthIcon);
	healthIcon->setPos(-20, 0);
	healthIcon->setScale(1, 1);

	bar = new Sprite("Resources/Image/bar.png");
	AddObject(bar);
	bar->setScale(1.7, 1.5);
	bar->setPos(83, 54);
	width = bar->getRect().right - bar->getRect().left;
	player = new Player();
	AddObject(player);
	
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
	for (auto& heal : healList) {
		heal->Render();
	}
	player->Render();
	for (int i = 0; i < 4; i++) {
		numArray[i]->Render();
	}
	bar->Render();
	healthIcon->Render();
	
}

void GameScene::Update(float dTime) {
	if (!isDead) {
		Scene::Update(dTime);

		UISetting();
		Damage(dTime);
		TimerSetting(dTime);
		OptimizationObject();
		InstantiateObject();
		CollisionCheck();
	}
}

void GameScene::Damage(float dTime) {
	time++;
	bar->setPos(bar->getPosX()-(time/8000), bar->getPosY());
	if (bar->getPosX() <= -780) {
		player->Dead();
		isDead = true;
	}
}

void GameScene::TimerSetting(float dTime) {
	coinInstDelayTimer += dTime;
	obstacleInstDelayTimer += dTime;
	healInstDelayTimer += dTime;
}

void GameScene::UISetting() {
	numArray[0]->setNum(score / 1000);
	numArray[1]->setNum(score / 100 % 10);
	numArray[2]->setNum(score / 10 % 10);
	numArray[3]->setNum(score % 10);
}

void GameScene::OptimizationObject() {
	for (auto iter = backgroundList.begin(); iter != backgroundList.end(); iter++) {
		if ((*iter)->getPosX() < -3267) {
			RemoveObject((*iter));
			SAFE_DELETE(*iter);
			iter = backgroundList.erase(iter);
			backgroundInstatiate = false;
			obstacleInstantiate = false;
			if (iter == backgroundList.end()) {
				break;
			}
		}
	}


	for (auto iter = bridgeList.begin(); iter != bridgeList.end(); iter++) {
		if ((*iter)->getPosX() < -800) {
			RemoveObject((*iter));
			SAFE_DELETE(*iter);
			iter = bridgeList.erase(iter);
			bridgeInstantiate = false;
			
		}
	}

	for (auto iter = coinList.begin(); iter != coinList.end(); iter++) {
		if ((*iter)->getPosX() < -SCREEN_WIDTH) {
			RemoveObject((*iter));
			SAFE_DELETE(*iter);
			iter = coinList.erase(iter);
			if (iter == coinList.end()) {
				break;
			}
		}
	}

	for (auto iter = obstacleList.begin(); iter != obstacleList.end(); iter++) {
		if ((*iter)->getPosX() < -SCREEN_WIDTH) {
			RemoveObject((*iter));
			SAFE_DELETE(*iter);
			iter = obstacleList.erase(iter);

			if (iter == obstacleList.end()) {
				break;

			}
		}
	}
	for (auto iter = healList.begin(); iter != healList.end(); iter++) {
		if ((*iter)->getPosX() < -SCREEN_WIDTH) {
			RemoveObject((*iter));
			SAFE_DELETE(*iter);
			iter = healList.erase(iter);

			if (iter == healList.end()) {
				break;

			}
		}
	}
}

void GameScene::CollisionCheck() {
	for (auto iter = coinList.begin(); iter != coinList.end(); iter++) {
		if (player->IsCollisionRect((*iter))) {
			RemoveObject((*iter));
			SAFE_DELETE(*iter);
			iter = coinList.erase(iter);

			if ((*iter)->getIsRed()) {
				score += 10;
			}
			else {
				score += 1;
			}

			score %= 10000;

			if (iter == coinList.end()) {
				break;
			}
		}
	}
	
	for (auto iter = healList.begin(); iter != healList.end(); iter++) {
		if (player->IsCollisionRect((*iter))) {
			RemoveObject((*iter));
			SAFE_DELETE(*iter);
			iter = healList.erase(iter);

			bar->setPos(bar->getPosX() + 100, bar->getPosY());
			if (bar->getPosX() > 83) {
				bar->setPos(83,bar->getPosY());
			}
			if (iter == healList.end()) {
				break;
			}
		}
	}

	for (auto iter = obstacleList.begin(); iter != obstacleList.end(); iter++) {
		if (player->IsCollisionRect((*iter))) {
			if ((*iter)->getPosY() == 430) {
				bar->setPos(bar->getPosX() - 13, bar->getPosY());
			}
			else {
				bar->setPos(bar->getPosX() - 3, bar->getPosY());
			}
			
		}
	}

	for (auto iter = bridgeList.begin(); iter != bridgeList.end(); iter++) {
		if (player->IsCollisionRectX((*iter))) {
			player->ifNotHole();
			return;
		}
		else {
			player->ifHole();
		}
	}
	

	if (player->getPosY() > 600) {
		bar->setPos(healthIcon->getPosX()-1000 , bar->getPosY());
		return;
	}
}

void GameScene::InstantiateObject() {
	if (!backgroundInstatiate) {
		Background* background = new Background();
		background->setScale(3, 3);
		background->setPos(3267-25, 0);
		backgroundList.push_back(background);
		AddObject(background);
		backgroundInstatiate = true;
	}

	if (!bridgeInstantiate) {
		Bridge* bridge = new Bridge(rand() % 20);
		bridge->setPos(SCREEN_WIDTH+1000 , 630);
		bridgeList.push_back(bridge);
		AddObject(bridge);
		bridgeInstantiate = true;
	}

	if (!obstacleInstantiate) {
		int ran = rand() % 7;
		if (obstacleInstDelayTimer > 3.f) {
			obstacleInstDelayTimer = rand()%2;
			coinCounter = 3;
			Obstacle* obstacle = new Obstacle(ran);
			switch (ran) {
			case 0:
			case 1:
				obstacle->setPos(SCREEN_WIDTH - 20, -480);
				break;
			case 2:
			case 3:
				obstacle->setPos(SCREEN_WIDTH - 20, 220);
				break;
			case 4:
				obstacle->setPos(SCREEN_WIDTH - 20, 430);
				break;
			default:
				obstacle->setPos(SCREEN_WIDTH - 20, 440);
				break;
			}
			AddObject(obstacle);
			obstacleList.push_back(obstacle);
			obstacleInstantiate = true;
			if (rand() % 2) {
				healInstantiate = false;
			}
		}
	}

	if (coinCounter > 0) {
		if (coinInstDelayTimer > 0.2f) {
			coinCounter--;
			coinInstDelayTimer = 0;
			Coin* coin = new Coin(true);
			coin->setPos(SCREEN_WIDTH, 345);
			AddObject(coin);
			coinList.push_back(coin);
		}
	}
	else {
		if (coinInstDelayTimer > 0.2f) {
			coinInstDelayTimer = 0;
			Coin* coin = new Coin(false);
			coin->setPos(SCREEN_WIDTH, 450);
			AddObject(coin);
			coinList.push_back(coin);
		}
	}

	if (!healInstantiate) {
		if (healInstDelayTimer > 6.f) {
			healInstDelayTimer = rand() % 3;
			Heal* heal = new Heal();
			std::cout << 1;
			heal->setPos(SCREEN_WIDTH - 20,416);
			AddObject(heal);
			healList.push_back(heal);
			healInstantiate = false;
		}
	}
}