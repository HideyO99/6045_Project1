#pragma once
#include <glm/glm.hpp> 
#include "cSteering.h"

class cAI
{
public:
	cAI();
	virtual ~cAI();

	glm::vec3 position;
	glm::vec3 faceDir;
	glm::vec3 velocity;
};

class cAI_TypeA : public cAI
{
public:
	cAI_TypeA();
	virtual ~cAI_TypeA();

	virtual void Seek();
	virtual void Flee();
};

class cAI_TypeB : public cAI_TypeA
{
public:
	cAI_TypeB();
	virtual ~cAI_TypeB();

	virtual void Pursues();
	virtual void Evades();
};

class cAI_TypeC : public cAI
{
public:
	cAI_TypeC();
	virtual ~cAI_TypeC();

	virtual void Approches();
};


