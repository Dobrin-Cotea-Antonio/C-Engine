#include "CollisionManager.h"
#include "../Physics/Collider.h"
#include "../Base/Transform.h"
#include "../Base/GameObject.h"

CollisionManager* CollisionManager::instance = nullptr;

#pragma region Constructor/Destructor
CollisionManager::CollisionManager() {
}

CollisionManager::~CollisionManager() {
}
#pragma endregion

#pragma region Instance
CollisionManager* CollisionManager::GetInstance() {
	if (instance == nullptr)
		instance = new CollisionManager();
	return instance;
}
#pragma endregion

#pragma region Lists
void CollisionManager::AddSolidCollider(const std::weak_ptr<Collider> pCollider) {
	if (ListContainsCollider(solidColliders, pCollider)) {
		std::cout << "List already contains that solid collider";
		return;
	}
	solidColliders.push_back(pCollider);
}

void CollisionManager::RemoveSolidCollider(const std::weak_ptr<Collider> pCollider) {
	if (!ModifyList(solidColliders, pCollider, true))
		std::cout << "List doesnt contain that solid collider";
}

void CollisionManager::AddTriggerCollider(const std::weak_ptr<Collider> pCollider) {
	if (ListContainsCollider(triggerColliders, pCollider)) {
		std::cout << "List already contains that trigger collider";
		return;
	}
	triggerColliders.push_back(pCollider);
}

void CollisionManager::RemoveTriggerCollider(const std::weak_ptr<Collider> pCollider) {
	if (!ModifyList(triggerColliders, pCollider, true))
		std::cout << "List doesnt contain that trigger collider";
}
#pragma endregion

#pragma region Helper Methods
bool CollisionManager::ListContainsCollider(const std::vector<std::weak_ptr<Collider>>& pList, const std::weak_ptr<Collider> pCollider) {
	bool wasFound = false;

	for (int i = 0; i < pList.size(); i++)
		if (pList[i].lock().get() == pCollider.lock().get()) {
			wasFound = true;
			break;
		}

	return wasFound;
}

bool CollisionManager::ModifyList(std::vector<std::weak_ptr<Collider>>& pList, const std::weak_ptr<Collider> pCollider, bool pColliderRemove) {
	bool wasFound = false;

	for (int i = 0; i < pList.size(); i++)
		if (pList[i].lock().get() == pCollider.lock().get()) {
			wasFound = true;
			if (pColliderRemove)
				pList.erase(pList.begin() + i);
			break;
		}

	return wasFound;
}
#pragma endregion

#pragma region Move
void CollisionManager::Move(const std::weak_ptr<Collider> pCollider, const Vec2 pVelocity) {
	if (pCollider.lock()->IsTrigger())
		CalculateOverlaps(pCollider, pVelocity);
	else
		CalculateCollisions(pCollider, pVelocity);
}

void CollisionManager::CalculateOverlaps(const std::weak_ptr<Collider> pCollider, const Vec2 pVelocity)const {
	for (int i = 0; i < triggerColliders.size(); i++) {
		if (pCollider.lock().get() == triggerColliders[i].lock().get())
			continue;
		if (!pCollider.lock()->Overlaps(triggerColliders[i]))
			continue;

		//<----------------------------------------------------------------->//
		//message both objects that they are overlaping						 //
		//<----------------------------------------------------------------->//
	}
}
void CollisionManager::CalculateCollisions(const std::weak_ptr<Collider> pCollider, const Vec2 pVelocity)const {

	Transform* colliderTransform = pCollider.lock()->owner.lock()->transform.lock().get();
	CollisionInfo firstCollision;

	colliderTransform->localPosition += pVelocity;
	for (int i = 0; i < solidColliders.size(); i++) {
		if (pCollider.lock().get() == solidColliders[i].lock().get())
			continue;

		CollisionInfo collisionInfo = pCollider.lock()->GetEarliestCollision(solidColliders[i], pVelocity);

		if (collisionInfo.timeOfImpact == -1 || collisionInfo.timeOfImpact >= 1)
			continue;

		if (firstCollision.timeOfImpact == -1 || firstCollision.timeOfImpact > collisionInfo.timeOfImpact)
			firstCollision = collisionInfo;
	}

	float timeOfImpact = 1;

	if (firstCollision.timeOfImpact == -1 || firstCollision.timeOfImpact > 1 || firstCollision.timeOfImpact < 0)
		return;

	timeOfImpact = firstCollision.timeOfImpact;

	colliderTransform->localPosition -= pVelocity;
	colliderTransform->localPosition += pVelocity * timeOfImpact;

	std::cout << "test\n";

	//<----------------------------------------------------------------->//
	//message both objects that they are colliding						 //
	//<----------------------------------------------------------------->//
}
#pragma endregion
