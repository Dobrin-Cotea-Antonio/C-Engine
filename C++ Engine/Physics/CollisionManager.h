#pragma once
#include <vector>
#include <memory>
#include "../Base/Vec2.h"

class Collider;

class CollisionManager {
private:
	static CollisionManager* instance;
	std::vector<std::weak_ptr<Collider>> triggerColliders;
	std::vector<std::weak_ptr<Collider>> solidColliders;

#pragma region Constructor/Destructor
protected:
	CollisionManager();
public:
	virtual ~CollisionManager();
#pragma endregion

#pragma region Deleted Methods
	CollisionManager(CollisionManager& pOther) = delete;
	void operator=(const CollisionManager&) = delete;
#pragma endregion

#pragma region Instance
public:
	static CollisionManager* GetInstance();
#pragma endregion

#pragma region Lists
public:
	void AddSolidCollider(const std::weak_ptr<Collider> pCollider);
	void RemoveSolidCollider(const std::weak_ptr<Collider> pCollider);
	void AddTriggerCollider(const std::weak_ptr<Collider> pCollider);
	void RemoveTriggerCollider(const std::weak_ptr<Collider> pCollider);
#pragma endregion

#pragma region Helper Methods
private:
	bool ListContainsCollider(const std::vector<std::weak_ptr<Collider>>& pList, const std::weak_ptr<Collider> pCollider);
	bool ModifyList(std::vector<std::weak_ptr<Collider>>& pList, const std::weak_ptr<Collider> pCollider, bool pColliderRemove);//if true remove collider
#pragma endregion

#pragma region Move
public:
	void Move(const std::weak_ptr<Collider> pCollider, const Vec2 pVelocity);
private:
	void CalculateOverlaps(const std::weak_ptr<Collider> pCollider, const Vec2 pVelocity)const;
	void CalculateCollisions(const std::weak_ptr<Collider> pCollider, const Vec2 pVelocity)const;
#pragma endregion
};