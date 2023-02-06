#include "cSteering.h"

cSteering::cSteering()
{
}

cSteering::~cSteering()
{
}

cSteering::cSteering(glm::vec3* pos, glm::vec3* dir, glm::vec3* v)
{
	this->position = pos;
	this->faceDir = dir;
	this->velocity = v;
}

void cSteering::Seek(glm::vec3 Target_Pos)
{
	*this->faceDir = Target_Pos - *this->position;
	*this->faceDir = glm::normalize(*this->faceDir);
	
	//return *this->faceDir;
}

void cSteering::Flee(glm::vec3 Target_Pos)
{
	*this->faceDir = *this->position - Target_Pos;
	*this->faceDir = glm::normalize(*this->faceDir);


}

void cSteering::Pursues(glm::vec3 Target_Pos, glm::vec3 Target_velocity)
{
	glm::vec3 lookAhead_Pos = Target_Pos + glm::vec3(Target_velocity.x * AHEAD, 0, Target_velocity.z * AHEAD);
	*this->faceDir = lookAhead_Pos - (*this->position);
	*this->faceDir = glm::normalize(*this->faceDir);
}

void cSteering::Evades(glm::vec3 Target_Pos, glm::vec3 Target_velocity)
{
	glm::vec3 lookAhead_Pos = Target_Pos + glm::vec3(Target_velocity.x * AHEAD, 0, Target_velocity.z * AHEAD);
	*this->faceDir = *this->position - lookAhead_Pos;
	*this->faceDir = glm::normalize(*this->faceDir);
}

void cSteering::Approches(glm::vec3 Target_Pos)
{
	float distance = glm::length(Target_Pos - *this->position);
	static bool seekState = false;
	if(distance >= APPROCH_OUTER_RADIUS)
	{
		seekState = true;
	}
	else if (distance <= APPROCH_INNER_RADIUS)
	{
		seekState = false;
	}

	if (seekState)
	{
		Seek(Target_Pos);
	}
	else
	{
		Flee(Target_Pos);
	}
	
}
