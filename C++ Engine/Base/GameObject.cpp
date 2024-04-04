#include "GameObject.h"
#include "Component.h"

#pragma region Constructor/Destructor
GameObject::GameObject() {
}

GameObject::~GameObject() {
}
#pragma endregion

#pragma region Hierarchy
void GameObject::AddChild(std::weak_ptr<GameObject> pGameObject) {
	children.push_back(pGameObject);
	children[children.size() - 1].lock()->parent = selfPointer;
}

void GameObject::RemoveChild(std::weak_ptr<GameObject> pGameObject) {
	for (int i = 0; i < children.size(); i++)
		if ((children[i].lock().get() == pGameObject.lock().get())) { // just compare pointers
			children[i].lock()->RemoveParent();
			children.erase(children.begin() + i);
			return;
		}
}

void GameObject::RemoveParent() {
	parent.reset();
}
#pragma endregion

#pragma region Runtime
void GameObject::update() {
	for (int i = 0; i < components.size(); i++)
		if (components[i].lock()->IsEnabledGlobal())
			components[i].lock()->update();
}

void GameObject::Update() {
	for (int i = 0; i < components.size(); i++)
		if (components[i].lock()->IsEnabledGlobal())
			components[i].lock()->Update();
}

void GameObject::render(){
	for (int i = 0; i < components.size(); i++)
		if (components[i].lock()->IsEnabledGlobal())
			components[i].lock()->render();
}
#pragma endregion

#pragma region Utility
bool GameObject::IsEnabledGlobal() {
	if (parent.lock() == nullptr) {
		return isEnabled;
	}
	else {
		return (isEnabled && parent.lock()->IsEnabledGlobal());
	}
}
#pragma endregion

#pragma region State
void GameObject::Destroy() {
	isDestroyed = true;
	for (int i = 0; i < children.size(); i++) {
		children[i].lock()->Destroy();
	}
}
#pragma endregion
