#include "InputManager.h"
#include "../Base/Game.h"

bool InputManager::keyPressed[Key::KeyCount] = {};
bool InputManager::keyUp[Key::KeyCount] = {};
bool InputManager::keyDown[Key::KeyCount] = {};
std::vector<Key> InputManager::keysPressedThisFrame;

Vec2 InputManager::mousePosition = Vec2(0, 0);
bool InputManager::buttonPressed[Button::ButtonCount] = {};
bool InputManager::buttonUp[Button::ButtonCount] = {};
bool InputManager::buttonDown[Button::ButtonCount] = {};
std::vector<Button> InputManager::buttonsPressedThisFrame;

int InputManager::scrollWheelDirection = 0;

#pragma region Runtime
void InputManager::update(const sf::Event& pEvent) {
	sf::Vector2i mp = sf::Mouse::getPosition(*Game::window);
	mousePosition = Vec2(mp.x, mp.y);

	UpdateKeys(pEvent);
	UpdateMouse(pEvent);
}

void InputManager::UpdateKeys(const sf::Event& pEvent) {

	if (pEvent.type != sf::Event::KeyPressed)
		return;

	keysPressedThisFrame.clear();

	for (int i = 0; i < Key::KeyCount; i++) {

		keyDown[i] = false;
		keyUp[i] = false;

		bool keyValue = (pEvent.key.code == i);

		if (!keyPressed[i] && keyValue)
			keyDown[i] = true;//key was just pressed

		if (keyPressed[i] && !keyValue)
			keyUp[i] = true;//key was just released

		keyPressed[i] = keyValue;

		if (keyValue)
			keysPressedThisFrame.push_back(static_cast<Key>(i));
	}
}

void InputManager::UpdateMouse(const sf::Event& pEvent) {

	if (pEvent.type != sf::Event::MouseButtonPressed)
		return;

	buttonsPressedThisFrame.clear();

	for (int i = 0; i < Button::ButtonCount; i++) {
		buttonDown[i] = false;
		buttonUp[i] = false;

		bool buttonValue = (pEvent.mouseButton.button == i);

		if (!buttonPressed[i] && buttonValue)
			buttonDown[i] = true;//button was just pressed

		if (buttonPressed[i] && !buttonValue)
			buttonUp[i] = true;//button was just released

		keyPressed[i] = buttonValue;

		if (buttonValue)
			buttonsPressedThisFrame.push_back(static_cast<Button>(i));
	}
}

void InputManager::UpdateScrollWheel(const sf::Event& pEvent){

	if (pEvent.type != sf::Event::MouseWheelScrolled)
		return;

	scrollWheelDirection = pEvent.mouseWheelScroll.delta;
}
#pragma endregion

#pragma region Keyboard Input

bool InputManager::IsKeyPressed(const Key& pKey) const {
	return keyPressed[pKey];
}

bool InputManager::IsKeyUp(const Key& pKey) const {
	return keyUp[pKey];
}

bool InputManager::IsKeyDown(const Key& pKey) const {
	return keyDown[pKey];
}
#pragma endregion

#pragma region Mouse Input
bool InputManager::IsButtonPressed(const Key& pKey) const {
	return buttonPressed[pKey];
}

bool InputManager::IsButtonUp(const Key& pKey) const {
	return buttonUp[pKey];
}

bool InputManager::IsButtonDown(const Key& pKey) const {
	return buttonDown[pKey];
}
#pragma endregion

#pragma region Scroll Wheel
int InputManager::ReturnScrollDirection() const {
	return scrollWheelDirection;
}
#pragma endregion