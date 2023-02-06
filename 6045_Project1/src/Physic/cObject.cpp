#include "cObject.h"

cObject::cObject()
{
	//position = &pMeshObj->position;
	isHover = false;
	AI_Type = TYPE_NONE;
	yRotation = 0;
}

cObject::~cObject()
{
}

void cObject::setMass(float mass)
{
	invMass = 1.f / mass;
}

void cObject::integrate(float dT)
{
	acceleration = force * invMass;
	velocity = glm::vec3((acceleration.x * dT) + velocity.x, (acceleration.y * dT) + velocity.y, (acceleration.z * dT) + velocity.z);

	prevPosition = position;
	position = glm::vec3((velocity.x * dT) + position.x, (velocity.y * dT) + position.y, (velocity.z * dT) + position.z);
}

void cObject::applyForce(const glm::vec3& f_dir)
{
	force += f_dir;
}

void cObject::killAllForces()
{
	force = glm::vec3(0.f);
}

void cObject::update()
{
	//if (this->position.y < 0)
	//{
	//	this->position.y = 0;
	//}
	//if (this->position.y > 300)
	//{
	//	this->position.y = 300;
	//}
	if (this->position.x < -48)
	{
		this->position.x = -48;
	}
	if (this->position.x > 48)
	{
		this->position.x = 48;
	}

	if (this->position.z < -48)
	{
		this->position.z = -48;
	}
	if (this->position.z > 48)
	{
		this->position.z = 48;
	}
	//this->position.y = 30;
	pMeshObj->position = this->position;
	pMeshObj->rotation = glm::vec3(0,this->yRotation,0);
	this->direction = glm::vec3(sin(pMeshObj->rotation.y), 0, cos(pMeshObj->rotation.y));
	this->prevPosition = this->position;

	//this->pBBox->pMeshObj->position = this->position+ this->pBBox->centerPointOffset;
	this->pBBox->centerPoint = this->position + this->pBBox->centerPointOffset;
	this->pBBox->minPoint = this->position + this->pBBox->minPointOffset;
	this->pBBox->maxPoint = this->position + this->pBBox->maxPointOffset;
	this->pBBox->halfExtent = this->position + this->pBBox->halfExtentOffset;
}

void cObject::AI_update(cObject* playerObj)
{
	
	if (AI_Type == AI_type::TYPE_A)
	{
		float faceforward = glm::dot(playerObj->direction, this->position - playerObj->position);
		if (faceforward > 0)
		{
			//flee
			this->pSteering->Flee(playerObj->position);
			this->pMeshObj->color_RGBA = FLEE_COLOR;
		}
		else
		{
			//seek
			this->pSteering->Seek(playerObj->position);
			this->pMeshObj->color_RGBA = SEEK_COLOR;
		}
	}
	if (AI_Type == AI_type::TYPE_B)
	{
		float faceAngle = glm::length(glm::cross(playerObj->direction, this->position - playerObj->position)) / ((glm::length(playerObj->direction) * (glm::length(this->position - playerObj->position))));

		if (faceAngle > 0.5 || faceAngle < -0.5)
		{
			this->pSteering->Pursues(playerObj->position, playerObj->velocity);
			this->pMeshObj->color_RGBA = PURSUE_COLOR;
		}
		else
		{
			this->pSteering->Evades(playerObj->position, playerObj->velocity);
			this->pMeshObj->color_RGBA = EVADE_COLOR;
		}

	}
	if (AI_Type == AI_type::TYPE_C)
	{
		this->pSteering->Approches(playerObj->position);
		this->pMeshObj->color_RGBA = APPROCH_COLOR;
	}

	//float angle = acos(glm::dot(this->direction, this->position - playerObj->position) / (glm::length(this->direction) * glm::length(this->position - playerObj->position)));
	//this->yRotation = angle * 0.1f;
}
