#include "cMeshObj.h"

cMeshObj::cMeshObj()
{
	this->meshName.clear();

	this->position = glm::vec3(0.f);
	this->rotation = glm::vec3(0.0f);
	this->scale = glm::vec3(1.f);
	this->isWireframe = false;

	this->color_RGBA = glm::vec4(0.f, 0.f, 0.f, 1.f);
	this->bUse_RGBA_colour = true;
	this->specular_colour_and_power = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	this->isVisible = true;
	this->bDoNotLight = false;
	this->isSkybox = false;
	this->isIslandModel = false;

	this->textureRatios[0] = 0.0f;
	this->textureRatios[1] = 0.0f;
	this->textureRatios[2] = 0.0f;
	this->textureRatios[3] = 0.0f;
	this->textureRatios[4] = 0.0f;
	this->textureRatios[5] = 0.0f;
	this->textureRatios[6] = 0.0f;
	this->textureRatios[7] = 0.0f;
}

cMeshObj::~cMeshObj()
{
}

cMeshObj* cMeshObj::findMeshObjByName(std::string name, bool searchChild)
{
	std::vector<cMeshObj*>::iterator currMesh_it;

	for (currMesh_it = this->vecChildMesh.begin(); currMesh_it!= this->vecChildMesh.end(); currMesh_it++)
	{
		cMeshObj* pCurrMesh = *currMesh_it;

		if (pCurrMesh->instanceName == name)
		{
			return pCurrMesh;
		}

		cMeshObj* pChildMesh = pCurrMesh->findMeshObjByName(name, searchChild);

		if (pChildMesh)
		{
			return pChildMesh;
		}
	}

	return nullptr;
}
