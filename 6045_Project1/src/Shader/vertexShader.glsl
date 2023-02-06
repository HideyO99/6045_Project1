#version 420

layout (location = 0) in vec4 vColour ;
layout (location = 1) in vec4 vPosition ;
layout (location = 2) in vec4 vNormal ;		
layout (location = 3) in vec4 vUVx2;
layout (location = 4) in vec4 vTangent;
layout (location = 5) in vec4 vBiNormal;
layout (location = 6) in vec4 vBoneID;
layout (location = 7) in vec4 vBoneWeight;

// Going "out" to the fragment shader
out vec4 fColor;		
out vec4 fNormal;
out vec4 fVertWorldLocation;	// using only matModel
out vec4 fUVx2;
out vec4 fTangent;
out vec4 fBinormal;

//uniform
uniform mat4 mModel;
uniform mat4 mModelInverseTranspose;		// mModel with Only Rotation;
uniform mat4 mView;
uniform mat4 mProjection;

void main()
{
    vec3 vertPosition = vPosition.xyz;
    //vec3 vertNormal = vNormal.xyz;
    mat4 mMVP = mProjection * mView * mModel;

    gl_Position = mMVP * vec4(vertPosition, 1.0); 

    fVertWorldLocation.xyz = (mModel * vec4(vertPosition, 1.0f)).xyz;
	fVertWorldLocation.w = 1.0f;

    fNormal.xyz = normalize(mModelInverseTranspose * vec4(vNormal.xyz, 1.0f)).xyz;
	fNormal.w = 1.0f;
    //fNormal = vec4(vNormal.xyz, 1.0);
    //fColor = vec4(vColour.rgb/0xff,1.0f);
    fColor = vColour;
    fUVx2 = vUVx2;
    fTangent = vTangent;
    fBinormal = vBiNormal;

}