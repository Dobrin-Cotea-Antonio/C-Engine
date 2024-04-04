#include "SceneManager.h"
#include "Scene.h"

SceneManager* SceneManager::instance = nullptr;

#pragma region Constructor/Destructor
SceneManager::SceneManager() {
}

SceneManager::~SceneManager() {
}
#pragma endregion

#pragma region Runtime
void SceneManager::update() {
	scenes[activeScene]->update();
}

void SceneManager::Update() {
	scenes[activeScene]->Update();
}

void SceneManager::render() {
	scenes[activeScene]->render();
}

void SceneManager::DestroyObjects(){
	scenes[activeScene]->DestroyObjects();
}
#pragma endregion

#pragma region Helper Methods
void SceneManager::EnableScene(const std::string pID){
	if (!activeScene.empty())
		scenes[activeScene]->DestroyScene();
	activeScene = pID;
	scenes[activeScene]->CreateLevel();
}

std::string SceneManager::GetActiveScene(){
	return activeScene;
}

SceneManager* SceneManager::GetInstance(){
	if (instance == nullptr)
		instance = new SceneManager();
	return instance;
}
#pragma endregion
