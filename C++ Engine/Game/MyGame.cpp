#include "MyGame.h";
#include "../Base/SceneManager.h";
#include "../Game/TestScene.h";
#include "../Base/AnimatedSpriteRenderer.h";
#include "../Base/GameObject.h";
#include "../Base/Transform.h";
#include "../Base/SpriteRenderer.h";
#include <iostream>
#include "../Base/AnimationData.h"
#include "../Game/CollisionTest.h"
#include "../Physics/CircleCollider.h"
#include "../Physics/CollisionManager.h"

#pragma region Constructor/Destructor
MyGame::MyGame(const Vec2 pWindowSize) :Game(pWindowSize) {
	CreateGame();
}

MyGame::~MyGame() {
}
#pragma endregion

#pragma region Game

void MyGame::CreateGame() {

	CollisionManager::GetInstance()->EnableSpacePartitioning(true);

	std::weak_ptr<Scene> scene = sceneManager->AddScene<Scene>("test");

	std::weak_ptr<GameObject> g = scene.lock()->InstantiateGameObject<GameObject>();
	std::weak_ptr<SpriteRenderer> s = g.lock()->AddComponent(scene.lock()->InstantiateComponent<SpriteRenderer>());
	s.lock()->LoadSprite("Game/Assets/circle.png");

	g.lock()->transform.lock()->localPosition = Vec2(100, 100);
	std::weak_ptr<CircleCollider> collider = g.lock()->AddComponent(scene.lock()->InstantiateComponent<CircleCollider>());
	collider.lock()->radius = 32;
	collider.lock()->SetCollisionType(false);

	std::weak_ptr<CollisionTest> collisionTest = g.lock()->AddComponent(scene.lock()->InstantiateComponent<CollisionTest>());

	//int collidersInEachCell = 100;

	//for (int i = 0; i < 4; i++)
	//	for (int j = 0; j < 4; j++) {
	//		for (int t = 0; t < collidersInEachCell; t++) {
	//			std::weak_ptr<GameObject> g1 = scene.lock()->InstantiateGameObject<GameObject>();
	//			//std::weak_ptr<SpriteRenderer> s1 = g1.lock()->AddComponent(scene.lock()->InstantiateComponent<SpriteRenderer>());
	//			//s1.lock()->LoadSprite("Game/Assets/circle.png");

	//			g1.lock()->transform.lock()->localPosition = Vec2(80 + i * 160, 80 + j * 160);
	//			std::weak_ptr<CircleCollider> collider1 = g1.lock()->AddComponent(scene.lock()->InstantiateComponent<CircleCollider>());
	//			collider1.lock()->radius = 32;
	//			collider1.lock()->SetCollisionType(false);
	//		}
	//	}

	int collidersInEachCell = 64;

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {
			for (int t = 0; t < collidersInEachCell; t++) {
				std::weak_ptr<GameObject> g1 = scene.lock()->InstantiateGameObject<GameObject>();
				//std::weak_ptr<SpriteRenderer> s1 = g1.lock()->AddComponent(scene.lock()->InstantiateComponent<SpriteRenderer>());
				//s1.lock()->LoadSprite("Game/Assets/circle.png");

				g1.lock()->transform.lock()->localPosition = Vec2(32 + i * 64, 32 + j * 64);
				std::weak_ptr<CircleCollider> collider1 = g1.lock()->AddComponent(scene.lock()->InstantiateComponent<CircleCollider>());
				collider1.lock()->radius = 32;
				collider1.lock()->SetCollisionType(false);
			}
		}
}
#pragma endregion
