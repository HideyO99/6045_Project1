#pragma once
#include "cAnimation.h"
#include "../MeshObj/cMeshObj.h"
#include <map>

class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();

	bool AddAnimation(const std::string& name, AnimationData animation);
	void AnimationUpdate(bool& playCMD,float dt);
	void play(bool isPlay);
	void setSpeed(float speedX);
	void setSequence(int sequence);
	//void AnimationUpdate(const std::vector<cMeshObj*>& animationOBJList, float dt);

	std::vector<cMeshObj*> animationOBJList;

private:
	int FindPositionKeyIndex(const AnimationData& animation, float time);
	int FindScaleKeyIndex(const AnimationData& animation, float time);
	int FindRotationKeyIndex(const AnimationData& animation, float time);

	glm::vec3 GetAnimationPosition(const AnimationData& animation, float time);
	glm::vec3 GetAnimationScale(const AnimationData& animation, float time);
	glm::quat GetAnimationRotation(const AnimationData& animation, float time);

	std::map<std::string, AnimationData> AnimationList;
	
};

