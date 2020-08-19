#include "stdafx.h"
#include "MainScene.h"

MainScene::MainScene() {
	background = new Sprite("Resources/Image/mainbackground.png");
	AddObject(background);
	background->setPos(-130, 0);

	startButton = new Sprite("Resources/Image/start.png");
	AddObject(startButton);
	startButton->setPos(330, 600);

	
}

MainScene::~MainScene() {

}

void MainScene::Render() {
	background->Render();
	startButton->Render();

}

void MainScene::Update(float dTime) {
	Scene::Update(dTime);

	if (inputManager->GetKeyState(VK_LBUTTON) == KEY_DOWN) {

		if (startButton->IsPointInRect(inputManager->GetMousePos())) {
			sceneManager->ChangeScene(new GameScene());
			return;
		}

	}
}