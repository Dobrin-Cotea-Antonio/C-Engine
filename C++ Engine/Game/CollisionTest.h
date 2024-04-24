#pragma once
#include "../Base/Component.h"
#include <vector>

class Collider;

class CollisionTest :public Component {
private:
	std::weak_ptr<Collider> collider;
	float speed = 150;;//pixels per sec

	double timePassed=0;
	double timeToStop=2;
	std::vector<double> fpsData;
	double intervalBetweenNewData=0.05;
	double timeSinceLastData = 0;
	double averageFps;
	bool wasFirstFrameSkipped = false;

#pragma region Constructor/Destructor
public:
	CollisionTest();
	virtual ~CollisionTest();
#pragma endregion

#pragma region runtime
public:
	virtual void Update()override;
#pragma endregion

};

