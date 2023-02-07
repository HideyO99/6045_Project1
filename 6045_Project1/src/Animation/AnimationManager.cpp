#include "AnimationManager.h"
#include <glm/gtx/easing.hpp>
#include <iostream>

AnimationManager::AnimationManager()
{
	animationOBJList.empty();
	continuePlay = false;
}

AnimationManager::~AnimationManager()
{
}

bool AnimationManager::AddAnimation(const std::string& name, AnimationData animation)
{
	std::map<std::string, AnimationData>::iterator itFind = AnimationList.find(name);
	if (itFind != AnimationList.end())
	{
		std::cout << "Cannot add " << name << std::endl;
		return false;
	}

	AnimationList.emplace(name, animation); 

	return true;
}

void AnimationManager::AnimationUpdate(bool& playCMD,float dt)
{
	bool isPlaying = false;

	for (size_t i = 0; i < animationOBJList.size(); i++)
	{
		cMeshObj* AnimationOBJ = animationOBJList[i];

		cAnimation& animation = AnimationOBJ->Animation;
		std::map<std::string, AnimationData>::iterator animation_it = AnimationList.find(animation.tag);

		if (animation_it != AnimationList.end())
		{
			const AnimationData& animationData = animation_it->second;

			if (animation.IsPlaying && animation.Speed != 0.f)
			{
				isPlaying = true;
				animation.AnimationTime += dt * animation.Speed;
				if (animation.AnimationTime > animationData.Duration)
				{
					if (animation.IsLooping)
					{
						if (animation.Speed > 0)
						{
							animation.AnimationTime = 0.0f;
						}
						else
						{
							animation.AnimationTime = animationData.Duration;
						}

					}
					else if (continuePlay)
					{
						unsigned nextSeq = animation.curSeq + 1;
						if (nextSeq < animation.seq.size())
						{
							animation.tag = animation.seq[nextSeq].c_str();
							animation.AnimationTime = 0.0f;
							animation.curSeq++;
							std::cout << "play animation sequence " << animation.curSeq + 1 << std::endl;
							continue;
						}
						else
						{
							animation.AnimationTime = animationData.Duration;
							animation.IsPlaying = false;
							isPlaying = false;
						}
					}
					else
					{
						animation.AnimationTime = animationData.Duration;
						animation.IsPlaying = false;
						isPlaying = false;

					}
				}
				else if (animation.AnimationTime < 0.f)
				{
					if (animation.IsLooping)
					{
						if (animation.Speed < 0)
						{
							animation.AnimationTime = animationData.Duration;
						}
						else
						{
							animation.AnimationTime = 0.f;
						}

					}
					else if (continuePlay)
					{
						unsigned nextSeq = animation.curSeq - 1;
						if (nextSeq < animation.seq.size())
						{
							animation.tag = animation.seq[nextSeq].c_str();
							animation.AnimationTime = animationData.Duration;
							animation.curSeq--;
							std::cout << "play animation sequence " << animation.curSeq + 1 << std::endl;
							continue;
						}
						else
						{
							animation.AnimationTime = 0.f;
							animation.IsPlaying = false;
							isPlaying = false;
						}
					}
					else
					{
						animation.AnimationTime = 0.f;
						animation.IsPlaying = false;
						isPlaying = false;
					}
				}

				AnimationOBJ->position = GetAnimationPosition(animationData, animation.AnimationTime);
				AnimationOBJ->scale = GetAnimationScale(animationData, animation.AnimationTime);
				AnimationOBJ->rotation = glm::eulerAngles(GetAnimationRotation(animationData, animation.AnimationTime));
			}
		}
	}
	playCMD = isPlaying;

}

void AnimationManager::play(bool isPlay)
{
	for (size_t i = 0; i < animationOBJList.size(); i++)
	{
		cMeshObj* AnimationOBJ = animationOBJList[i];

		cAnimation& animation = AnimationOBJ->Animation;
		animation.IsPlaying = isPlay;
	}
}

void AnimationManager::setSpeed(float speedX)
{
	for (size_t i = 0; i < animationOBJList.size(); i++)
	{
		cMeshObj* AnimationOBJ = animationOBJList[i];

		cAnimation& animation = AnimationOBJ->Animation;
		animation.Speed = speedX;
	}
}

void AnimationManager::setSequence(unsigned int& sequence)
{
	for (size_t i = 0; i < animationOBJList.size(); i++)
	{
		cMeshObj* AnimationOBJ = animationOBJList[i];

		cAnimation& animation = AnimationOBJ->Animation;
		if (sequence < animation.seq.size())
		{
			animation.tag = animation.seq[sequence].c_str();
			animation.AnimationTime = 0.f;
			animation.curSeq = sequence;
		}
		else
		{
			sequence = animation.seq.size() - 1;
		}
	}
}

void AnimationManager::getSequence(unsigned int& sequence)
{
	sequence = animationOBJList[0]->Animation.curSeq;
}

int AnimationManager::FindPositionKeyIndex(const AnimationData& animation, float time)
{
	for (size_t i = 0; i < animation.PositionKeyFrames.size(); i++)
	{
		if (animation.PositionKeyFrames[i].time > time) 
		{
			return i - 1;
		}
	}

	return animation.PositionKeyFrames.size() - 1;
}

int AnimationManager::FindScaleKeyIndex(const AnimationData& animation, float time)
{
	for (size_t i = 0; i < animation.ScaleKeyFrames.size(); i++)
	{
		if (animation.ScaleKeyFrames[i].time > time)
		{
			return i - 1;
		}
	}

	return animation.ScaleKeyFrames.size() - 1;
}

int AnimationManager::FindRotationKeyIndex(const AnimationData& animation, float time)
{
	for (size_t i = 0; i < animation.RotationKeyFrames.size(); i++)
	{
		if (animation.RotationKeyFrames[i].time > time)
		{
			return i - 1;
		}
	}

	return animation.RotationKeyFrames.size() - 1;
}

glm::vec3 AnimationManager::GetAnimationPosition(const AnimationData& animation, float time)
{
	int currentPosKFIndex = FindPositionKeyIndex(animation, time);
	if ((animation.PositionKeyFrames.size() == 1)|| (currentPosKFIndex == animation.PositionKeyFrames.size() - 1))
	{
		return animation.PositionKeyFrames[currentPosKFIndex].Pos;
	}

	int nextPosKFIndex = currentPosKFIndex + 1;
	PositionKeyFrame currentKF = animation.PositionKeyFrames[currentPosKFIndex];
	PositionKeyFrame nextKF = animation.PositionKeyFrames[nextPosKFIndex];
	float diff = nextKF.time - currentKF.time;
	float ratio = (time - currentKF.time) / diff;

	switch (currentKF.type)
	{
	case EaseIn:
		ratio = glm::sineEaseIn(ratio);
		break;
	case EaseOut:
		ratio = glm::sineEaseOut(ratio);
		break;
	case EaseInOut:
		ratio = glm::sineEaseInOut(ratio);
		break;
	case None:
		break;
	default:
		break;
	}

	return glm::mix(currentKF.Pos, nextKF.Pos, ratio);
}

glm::vec3 AnimationManager::GetAnimationScale(const AnimationData& animation, float time)
{
	int currentScaleKFIndex = FindScaleKeyIndex(animation, time);
	if ((animation.ScaleKeyFrames.size() == 1) || (currentScaleKFIndex == animation.ScaleKeyFrames.size() - 1))
	{
		return animation.ScaleKeyFrames[currentScaleKFIndex].Scale;
	}

	int nextScaleKFIndex = currentScaleKFIndex + 1;
	ScaleKeyFrame currentKF = animation.ScaleKeyFrames[currentScaleKFIndex];
	ScaleKeyFrame nextKF = animation.ScaleKeyFrames[nextScaleKFIndex];
	float diff = nextKF.time - currentKF.time;
	float ratio = (time - currentKF.time) / diff;

	switch (currentKF.type)
	{
	case EaseIn:
		ratio = glm::sineEaseIn(ratio);
		break;
	case EaseOut:
		ratio = glm::sineEaseOut(ratio);
		break;
	case EaseInOut:
		ratio = glm::sineEaseInOut(ratio);
		break;
	case None:
		break;
	default:
		break;
	}

	return glm::mix(currentKF.Scale, nextKF.Scale, ratio);
}

glm::quat AnimationManager::GetAnimationRotation(const AnimationData& animation, float time)
{
	int currentRotatationKFIndex = FindRotationKeyIndex(animation, time);
	if ((animation.RotationKeyFrames.size() == 1) || (currentRotatationKFIndex == animation.RotationKeyFrames.size() - 1))
	{
		return animation.RotationKeyFrames[currentRotatationKFIndex].Rotation;
	}

	int nextRotatationKFIndex = currentRotatationKFIndex + 1;
	RotationKeyFrame currentKF = animation.RotationKeyFrames[currentRotatationKFIndex];
	RotationKeyFrame nextKF = animation.RotationKeyFrames[nextRotatationKFIndex];
	float diff = nextKF.time - currentKF.time;
	float ratio = (time - currentKF.time) / diff;

	switch (currentKF.type)
	{
	case EaseIn:
		ratio = glm::sineEaseIn(ratio);
		break;
	case EaseOut:
		ratio = glm::sineEaseOut(ratio);
		break;
	case EaseInOut:
		ratio = glm::sineEaseInOut(ratio);
		break;
	case None:
		break;
	default:
		break;
	}

	return glm::slerp(currentKF.Rotation, nextKF.Rotation, ratio);
}
