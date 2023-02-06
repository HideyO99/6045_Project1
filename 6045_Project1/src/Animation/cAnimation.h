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
	PositionKeyFrame(glm::vec3 Pos, float time, EasingType type = None) : Pos(Pos), time(time), type(type) {}
	glm::vec3 Pos;
	float time;
	EasingType type;
};

struct ScaleKeyFrame
{
	ScaleKeyFrame(glm::vec3 Scale, float time, EasingType type = None) : Scale(Scale), time(time), type(type) {}
	glm::vec3 Scale;
	float time;
	EasingType type;
};

struct RotationKeyFrame
{
	RotationKeyFrame(glm::quat Rotation, float time, EasingType type = None) : Rotation(Rotation), time(time), type(type) {}
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

