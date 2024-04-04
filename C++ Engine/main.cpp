#include<iostream>
#include<SFML/Graphics.hpp>
#include<memory>
#include "Base/GameObject.h"
#include "Base/Vec2.h";
#include "Base/TimeClass.h";

int main() {

	std::shared_ptr<GameObject> test = std::shared_ptr<GameObject>(new GameObject());
	std::weak_ptr<GameObject> ptr = test;

	//test->GetComponentOfType<Component>();


	//GameObject g = GameObject();
	//g.Destroy(&g);

	TimeClass* t = TimeClass::GetInstance();

	Vec2 vec1 = Vec2(1, 1);
	Vec2 vec2 = Vec2(1, 4);

	vec2 = 2*vec1;
	std::cout << vec2;

	//std::cout << (vec1*2+vec2);

	return 0;
}


