#pragma once
#include "../Base/Component.h"
#include "../Base/Vec2.h"
#include "../Physics/CollisionInfo.h"

class Collider :public Component {
protected:
	bool isTrigger = true;

#pragma region Constructor/Destructor
public:
	Collider();
	virtual ~Collider();
#pragma endregion

#pragma region Collider type
public:
	void SetCollisionType(bool pIsTrigger);
#pragma endregion

#pragma region Collision Detection
public:
	virtual CollisionInfo GetEarliestCollision(std::weak_ptr<Collider> pOther, Vec2 pVelocity) = 0;
	virtual bool Overlaps(std::weak_ptr<Collider> pOther) = 0;
#pragma endregion 

#pragma region Helper Methods
	bool IsTrigger()const;
#pragma endregion
};