#pragma once
#include <vector>
#include <iostream>
#include "Object.h"

class Component;
class Transform;

class GameObject : public Object {
private:
	std::vector<std::weak_ptr<Component>> components;

protected:
	std::vector<std::weak_ptr<GameObject>> children;
	std::weak_ptr<GameObject> parent;
	std::weak_ptr<GameObject> selfPointer;

public:
	std::weak_ptr<Transform> transform;
public:

#pragma region Constructor/Destructor
	GameObject();
	virtual ~GameObject();
#pragma endregion

#pragma region Hierarchy
	void AddChild(std::weak_ptr<GameObject> pGameObject);
	void RemoveChild(std::weak_ptr<GameObject> pGameObject);
	void RemoveParent();
#pragma endregion

#pragma region Runtime
	void update();
	void Update();
	void render();
#pragma endregion

#pragma region Utility
	bool IsEnabledGlobal() override;
#pragma endregion

#pragma region State
	void Destroy();
#pragma endregion

#pragma region Components
	template<typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
	void AddComponent(std::weak_ptr<T> pComponent) {
		bool wasFound = false;

		//check if the component was already assigned to a different GameObject


		for (int i = 0; i < components.size(); i++)
			if (pComponent.lock().get() == components[i].lock().get()) {
				wasFound = true;
				break;
			}

		if (!wasFound)
			components.push_back(pComponent);
		else
			std::cout << "Component was already assigned to this GameObject!";
	}

	template<typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
	void RemoveComponent(std::weak_ptr<T> pComponent) {
		bool wasFound = false;

		for (int i = 0; i < components.size(); i++)
			if (pComponent.lock().get() == components[i].lock().get()) {
				components.erase(components.begin() + i);
				wasFound = true;
				break;
			}

		if (!wasFound)
			std::cout << "Component isn`t assigned to this GameObject!";
	}

	template<typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
	std::weak_ptr<T> GetComponentOfType() {

		for (int i = 0; i < components.size(); i++) {
			T* comp = dynamic_cast<T*>(components[i].lock().get());
			if (comp != nullptr)
				return components[i];
		}
	}

	template<typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
	std::vector<std::weak_ptr<T>> GetComponentsOfType() {

		std::vector<std::weak_ptr<T>> componentList;

		for (int i = 0; i < components.size(); i++) {
			T* comp = dynamic_cast<T*>(components[i].lock().get());
			if (comp != nullptr)
				componentList.push_back(components[i]);
		}

		return componentList;
	}

#pragma endregion

};