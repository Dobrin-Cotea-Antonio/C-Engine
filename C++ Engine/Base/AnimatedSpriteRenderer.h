#pragma once
#include "SpriteRenderer.h"
#include "Vec2.h"
#include "AnimationData.h";

class AnimatedSpriteRenderer :public SpriteRenderer {

protected:
	bool animate = true;
	bool animationIsInReverse = false;
	int currentFrame = 0;
	AnimationData animData;

	int animationCycleStart;
	int animationCycleEnd;

	Vec2 frameSize;
	float elapsedTime;

public:
#pragma region Constructor/Destructor
	AnimatedSpriteRenderer();
	virtual ~AnimatedSpriteRenderer();
#pragma endregion

#pragma region Sprite
	void LoadSprite(const std::string& pTextureAdress)override;
#pragma endregion

#pragma region Runtime
	void update()override;
#pragma endregion

protected:
#pragma region Animation
	void Animate();
	void SelectSubFrame();
	void SetAnimationCycle(int pFrameStart, int pFrameEnd);
	void ChangeAnimationState(const bool pState);
	void SetAnimationData(const AnimationData& pAnimationData);
#pragma endregion

};