#include "AnimationData.h"

#pragma region Constructor/Destructor
AnimationData::AnimationData()
{
}
AnimationData::AnimationData(const int pCols, const int pRows, const int pFrames, const float pAnimationSpeed) :cols(pCols), rows(pRows), frames(pFrames), animationSpeed(pAnimationSpeed),animate(true) {
}

AnimationData::~AnimationData() {
}
#pragma endregion