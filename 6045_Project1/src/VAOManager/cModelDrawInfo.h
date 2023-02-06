#pragma once
#include <string>
class cModelDrawInfo
{
public:
	cModelDrawInfo();
	~cModelDrawInfo();

	struct sVertex_RGBA_XYZ_N_UV_T_BiN_Bones
	{
		float x, y, z, w;		//	in vec3 vPosition;		
		float nx, ny, nz, nw;	//	in vec3 vNormal;	
		float r, g, b, a;
		float u0, v0, u1, v1;
		float tx, ty, yz, tw;
		float bx, by, bz, bw;
		float vBoneID[4];
		float vBoneWeight[4];
	};

	std::string meshName;

	unsigned int VAO_ID;

	unsigned int VertexBufferID;
	unsigned int VertexBuffer_Start_Index;
	unsigned int numberOfVertices;

	unsigned int IndexBufferID;
	unsigned int IndexBuffer_Start_Index;
	unsigned int numberOfIndices;
	unsigned int numberOfTriangles;

	void CalculateExtents(void);

	float maxX, maxY, maxZ;
	float minX, minY, minZ;

	float extentX, extentY, extentZ;

	float maxExtent;


	sVertex_RGBA_XYZ_N_UV_T_BiN_Bones* pVertices;

	unsigned int* pIndices;
};

