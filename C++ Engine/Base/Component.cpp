#include "Component.h"
#include "GameObject.h"

#pragma region Constructor/Destructor
Component::Component() {
}

Component::~Component() {
}
#pragma endregion

#pragma region SpecialEvents
void Component::OnEnable() {
}

void Component::OnDisable() {
}

void Component::OnCreate() {
}

void Component::OnDestroy() {
}
#pragma endregion 

#pragma region Runtime
void Component::Update() {
}

void Component::update() {
}
#pragma endregion

#pragma region State
void Component::Destroy() {
	isDestroyed = true;

	//std::weak_ptr<Object> weakBasePtr;

	std::weak_ptr<Component> comp = std::dynamic_pointer_cast<Component>(selfPointer.lock());

	owner.lock()->RemoveComponent(comp);

	//if (auto sharedBasePtr = weakBasePtr.lock()) {
	//    if (auto sharedDerivedPtr = std::dynamic_pointer_cast<Component>(sharedBasePtr)) {
	//        std::weak_ptr<Component> weakDerivedPtr = sharedDerivedPtr;

	//        // Use weakDerivedPtr
	//    }
	//    else {
	//        // Handle the case where the dynamic cast fails
	//    }
	//}
	//else {
	//    // Handle the case where the weak_ptr is expired
	//}
}

void Component::Enable(const bool pState) {
	if (pState == isEnabled)
		return;

	isEnabled = pState;

	if (isEnabled)
		OnEnable();
	else
		OnDisable();
}
#pragma endregion

#pragma region Utility
bool Component::IsEnabledGlobal() {
	if (owner.lock() == nullptr) {
		return isEnabled;
	} else {
		return (isEnabled && owner.lock()->IsEnabledGlobal());
	}
}
#pragma endregion


