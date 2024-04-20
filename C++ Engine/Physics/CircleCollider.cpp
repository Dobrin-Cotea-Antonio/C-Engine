#include "CircleCollider.h"
#include "../Base/GameObject.h"
#include "../Base/Transform.h"
#include <cmath>

#pragma region Constructor/Destructor
CircleCollider::CircleCollider() {
}

CircleCollider::~CircleCollider() {
}
#pragma endregion

#pragma region Collision Detection
CollisionInfo CircleCollider::GetEarliestCollision(std::weak_ptr<Collider> pOther,const Vec2 pVelocity) {
	std::shared_ptr<CircleCollider> circle = std::dynamic_pointer_cast<CircleCollider>(pOther.lock());

	if (circle.get() != nullptr)
		return GetEarliestCollision(circle, pVelocity);

	return CollisionInfo();
}

bool CircleCollider::Overlaps(std::weak_ptr<Collider> pOther) {
	std::shared_ptr<CircleCollider> circle = std::dynamic_pointer_cast<CircleCollider>(pOther.lock());

	if (circle.get() != nullptr)
		return Overlaps(circle);

	return false;
}

CollisionInfo CircleCollider::GetEarliestCollision(CircleCollider* pOther, const Vec2 pVelocity) {
	Vec2 relativePosition = owner.lock()->transform.lock()->GetGlobalPosition() - pOther->owner.lock()->transform.lock()->GetGlobalPosition();
	if (relativePosition.Length() < radius + pOther->radius) {

		Vec2 oldPosition = owner.lock()->transform.lock()->GetGlobalPosition() - pVelocity;
		float timeOfImpact = CalculateCircleTimeOfImpact(pOther, pVelocity);

		if (timeOfImpact < 0 || timeOfImpact > 1)
			return CollisionInfo();

		Vec2 POI = oldPosition + pVelocity * timeOfImpact;
		Vec2 unitNormal = (POI - pOther->owner.lock()->transform.lock()->GetGlobalPosition()).Normalized();
		return CollisionInfo(unitNormal,pOther,timeOfImpact);
	}
	return CollisionInfo();
}

bool CircleCollider::Overlaps(std::weak_ptr<CircleCollider> pOther, Vec2 pVelocity) const {
	Vec2 diffVec = owner.lock()->transform.lock()->GetGlobalPosition() - pOther.lock()->owner.lock()->transform.lock()->GetGlobalPosition();
	return (diffVec.Length() < radius + pOther.lock()->radius);
}
#pragma endregion

#pragma region Helper Methods
float CircleCollider::CalculateCircleTimeOfImpact(const CircleCollider* pOther, const Vec2 pVelocity) {
	Vec2 u = ((owner.lock()->transform.lock()->GetGlobalPosition() - pVelocity) - pOther->owner.lock()->transform.lock()->GetGlobalPosition());

	float a = pow(pVelocity.Length(), 2);
	float b = 2 * u.Dot(pVelocity);
	float c = pow(u.Length(), 2) - pow(radius + pOther->radius, 2);
	float D = pow(b, 2) - 4 * a * c;

	if (c < 0) {
		if (b < 0)
			return 0;
		else
			return -1;
	}

	if (a == 0)
		return -1;

	if (D < 0)
		return -1;

	float t = (-b - sqrt(D)) / (2 * a);

	if (0 <= t && t < 1)
		return t;

	return -1;
}
#pragma endregion