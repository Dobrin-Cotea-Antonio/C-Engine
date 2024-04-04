#include "Game.h"
#include "SceneManager.h"
#include "TimeClass.h"
#include "TextureCache.h"

sf::RenderWindow* Game::window = nullptr;

#pragma region Constructor/Destructor
Game::Game(const Vec2 pWindowSize) {
	sceneManager = SceneManager::GetInstance();
	textureCache = TextureCache::GetInstance();
	timeClass = TimeClass::GetInstance();
	window = new sf::RenderWindow(sf::VideoMode(pWindowSize.x, pWindowSize.y), "Yes");
	window->setKeyRepeatEnabled(false);//might need to delete
	CreateGame();
}

Game::~Game() {
}
#pragma endregion

#pragma region Runtime
void Game::run() {
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event))
			if (event.type == sf::Event::Closed)
				window->close();

		timeClass->update();
		sceneManager->update();
		sceneManager->Update();
		sceneManager->DestroyObjects();
		
		window->clear();
		sceneManager->render();
		window->display();
	}
}
#pragma endregion

#pragma region Game
void Game::CreateGame() {
}
#pragma endregion
