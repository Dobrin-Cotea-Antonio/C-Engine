#include "CollisionTest.h"
#include "../Base/GameObject.h"
#include "../Physics/Collider.h"
#include "../Base/InputManager.h"
#include "../Physics/CollisionManager.h"
#include "../Base/TimeClass.h"
#include "../Base/Transform.h"
#include "../Base/TimeClass.h"

#pragma region Constructor/Destructor
CollisionTest::CollisionTest() {

}

CollisionTest::~CollisionTest() {
}
#pragma endregion

#pragma region runtime
void CollisionTest::Update() {

	if (collider.lock().get() == nullptr)
		collider = owner.lock()->GetComponentOfType<Collider>();

	Vec2 direction;

	if (InputManager::IsKeyPressed(Key::W))
		direction += Vec2(0, -1);
	if (InputManager::IsKeyPressed(Key::A))
		direction += Vec2(-1, 0);
	if (InputManager::IsKeyPressed(Key::S))
		direction += Vec2(0, 1);
	if (InputManager::IsKeyPressed(Key::D))
		direction += Vec2(1, 0);

	direction.Normalize();

	direction = Vec2(1, 0);

	CollisionManager::GetInstance()->Move(collider, speed * TimeClass::deltaTime * direction);

	//if (TimeClass::time < 3)
	//	return;


	

	if (timePassed < timeToStop) {
		timePassed += TimeClass::deltaTime;
		timeSinceLastData += TimeClass::deltaTime;

		if (!wasFirstFrameSkipped) {
			timePassed = 0;
			timeSinceLastData = 0;
			wasFirstFrameSkipped = true;
		}

		if (timeSinceLastData >= intervalBetweenNewData) {
			
			fpsData.push_back(1.0f / TimeClass::deltaTime);
			timeSinceLastData = 0;
		}
	}
	else {
		if (averageFps == 0) {
			for (int i = 0; i < fpsData.size(); i++)
				averageFps += fpsData[i];
			averageFps /= fpsData.size();
			std::cout << averageFps << "\n";
			fpsData.clear();
		}
	}

	//std::cout << 1.0f / TimeClass::deltaTime<<"\n";
}
#pragma endregion
