#include "Object.h"

#pragma region Constructor/Destructor
Object::Object() {
}

Object::~Object() {

}
#pragma endregion

#pragma region Utility
bool Object::IsEnabledGlobal() {
	return isEnabled;
}
bool Object::GetDestroyStatus() const {
	return isDestroyed;
}
#pragma endregion

#pragma region State
void Object::Enable(const bool pState) {
	isEnabled = pState;
}

void Object::Destroy() {
	isDestroyed = true;
}
#pragma endregion
