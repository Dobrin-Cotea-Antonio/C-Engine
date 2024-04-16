#include "MyGame.h";
#include "../Base/SceneManager.h";
#include "../Game/TestScene.h";
#include "../Base/AnimatedSpriteRenderer.h";
#include "../Base/GameObject.h";
#include "../Base/Transform.h";
#include "../Base/SpriteRenderer.h";
#include <iostream>
#include "../Base/AnimationData.h"

#pragma region Constructor/Destructor
MyGame::MyGame(const Vec2 pWindowSize) :Game(pWindowSize) {
	CreateGame();
}

MyGame::~MyGame(){
}
#pragma endregion

#pragma region Game

void MyGame::CreateGame() {

	std::weak_ptr<Scene> scene = sceneManager->AddScene<Scene>("IWantToDie");
	std::weak_ptr<GameObject> g = scene.lock()->InstantiateGameObject<GameObject>();
	//std::weak_ptr<SpriteRenderer> s = g.lock()->AddComponent(scene.lock()->InstantiateComponent<SpriteRenderer>());
	//s.lock()->LoadSprite("sprite_targetdummy04.png");
	g.lock()->transform.lock()->localPosition = Vec2(100, 100);
	g.lock()->transform.lock()->localScale = Vec2(2, 2);

	std::weak_ptr<AnimatedSpriteRenderer> anim = g.lock()->AddComponent(scene.lock()->InstantiateComponent<AnimatedSpriteRenderer>());


	AnimationData data(4, 1, 4, 0.25f, "Game/Assets/TankRun.png");
	anim.lock()->SetAnimationData(data);

}
#pragma endregion
