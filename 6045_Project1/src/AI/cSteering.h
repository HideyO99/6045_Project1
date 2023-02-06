#pragma once
#include <glm/glm.hpp> 

#define AHEAD	3
#define APPROCH_OUTER_RADIUS	7
#define APPROCH_INNER_RADIUS	5

class cSteering
{
public:
	cSteering();
	~cSteering();

	cSteering(glm::vec3* pos, glm::vec3* dir, glm::vec3* v);

	glm::vec3* position;
	glm::vec3* faceDir;
	glm::vec3* velocity;

	void Seek(glm::vec3 Target_Pos);
	void Flee(glm::vec3 Target_Pos);
	void Pursues(glm::vec3 Target_Pos, glm::vec3 Target_velocity);
	void Evades(glm::vec3 Target_Pos, glm::vec3 Target_velocity);
	void Approches(glm::vec3 Target_Pos);
};

