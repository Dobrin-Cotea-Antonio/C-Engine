#pragma once

struct AnimationData {

public:
	int cols = 1;
	int rows = 1;
	int frames = 1;
	float animationSpeed = 0.2f;
	bool animate = false;

#pragma region Constructor/Destructor
	AnimationData();
	AnimationData(const int pCols, const int pRows, const int pFrames, const float pAnimationSpeed);
	virtual ~AnimationData();
#pragma endregion

};