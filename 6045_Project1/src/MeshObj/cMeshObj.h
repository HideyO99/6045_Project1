#pragma once
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include "../Animation/cAnimation.h"
//#include <glm/vec3.hpp>

class cMeshObj
{
public:
	cMeshObj();
	~cMeshObj();

	std::string meshName;
	std::string instanceName;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	bool isWireframe;
	glm::vec4 color_RGBA;
	bool bUse_RGBA_colour;
	glm::vec4 specular_colour_and_power;
	bool isVisible;
	bool bDoNotLight;
	std::string textures[8];
	float textureRatios[8];
	bool isSkybox;
	bool isIslandModel;

	cAnimation Animation;

	std::vector<cMeshObj*> vecChildMesh;
	
	cMeshObj* findMeshObjByName(std::string name, bool searchChild = true);

};

