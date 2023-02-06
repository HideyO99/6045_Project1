#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <string>
#include <vector>

enum EasingType
{
	EaseIn,
	EaseOut,
	EaseInOut,
	None
};

struct PositionKeyFrame
{
	glm::vec3 Pos;
	float time;
	EasingType type;
};

struct ScaleKeyFrame
{
	glm::vec3 Scale;
	float time;
	EasingType type;
};

struct RotationKeyFrame
{
	glm::quat Rotation;
	float time;
	//bool useSlerp;
	EasingType type;
};

struct AnimationData
{
	std::vector<PositionKeyFrame> PositionKeyFrames;
	std::vector<ScaleKeyFrame> ScaleKeyFrames;
	std::vector<RotationKeyFrame> RotationKeyFrames;
	float Duration;
};


class cAnimation
{
public:
	cAnimation();
	~cAnimation();

	std::string tag;
	float AnimationTime;
	bool IsPlaying;
	bool IsLooping;
	float Speed;

};

