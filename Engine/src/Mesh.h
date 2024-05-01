
//2024. Caleb Papay


#ifndef MESH_H
#define MESH_H

#include <d3d11.h>
#include "DLink.h"
#include "MathEngine.h"
#include "Camera.h"
#include "MeshLayout.h"

namespace Azul
{
	//enum class VertexSlot : uint32_t
	//{
	//	Position,  //0
	//	Color,     //1
	//	Norm,      //2
	//	TexCoord,   //3
	//	Weights,//4
	//	Joints//5
	//};

	//enum class ConstantBufferSlot : uint32_t
	//{
	//	Projection,//0
	//	View,//1
	//	World,//2
	//	LightColor,//3
	//	LightPos,//4
	//	UV_Correction,//5
	//	SpriteColor,//6
	//	InvBind,//7
	//	BoneWorld,//8
	//	


	//	csMixer,          //9
	//	csWorld			 //10
	//};

	class Mesh
	{
	public:

		// needs to match Vertex Shaders
		//static const unsigned int BoneCountMax = 8;

		enum class Name
		{
			CUBE,
			PYRAMID,
			CRATE,
			R2,
			SPHERE,
			CAMERA,
			FRIGATE,
			Bone,
			Bone_001,
			Bone_L,
			Bone_L_001,
			Bone_L_002,
			Bone_R,
			Bone_R_001,
			Bone_R_002,
			RAT_THING,
			SPRITE,
			MULTI_MESH_MODEL,
			NULL_MESH,
			CHICKENBOT,
			SARDAUKAR,
			NOT_INITIALIZED
		};

	public:
		Mesh() = delete;
		Mesh(Mesh &copyMesh) = delete;
		Mesh &operator = (Mesh &copyMesh) = delete;
		virtual ~Mesh();

		Mesh(unsigned int numVerts, unsigned int numTriangles, unsigned int numBones = 0);

		ID3D11Buffer *CreateVertexBuffer(unsigned int NumBytes, void *pData);
		ID3D11Buffer *CreateIndexBuffer(unsigned int NumBytes, void *pData);
		ID3D11Buffer *CreateConstantBuffer(unsigned int NumBytes);

		void Wash();
		bool Compare(DLink *pTarget);
		char *GetName();
		void SetName(Mesh::Name _name);
		void ActivateMesh();

		void TransferConstantBufferWorldViewProj(Camera *pCam, Mat4 *pWorld);
		void TransferUVCorrection(Mat4 *pUVMatrix);
		void TransferColor(Vec4 *pColor);
		//void TransferConstantBufferInvBindArray(Mat4 *pInvBindArray);
		//void TransferConstantBufferBoneWorldArray(Mat4 *pWorldBoneArray);


		void RenderIndexBuffer();

		// ---------------------------------------------
		// 	   Data:
		// ---------------------------------------------

		Name name;
		//Skel::Name skelName;
		
		unsigned int numVerts;
		unsigned int numIndices;
		unsigned int numBones;
		// Vertex buffer data
		ID3D11Buffer *poVertexBuffer_pos;
		ID3D11Buffer *poVertexBuffer_color;
		ID3D11Buffer *poVertexBuffer_norm;
		ID3D11Buffer *poVertexBuffer_texCoord;
		//vertex buffer anim data
		ID3D11Buffer *poVertexBuffer_weights;
		ID3D11Buffer *poVertexBuffer_joints;



		ID3D11Buffer *poIndexBuffer;

		// Shader resources - guaranteed every render
		ID3D11Buffer *poConstantBuff_vsProjection;
		ID3D11Buffer *poConstantBuff_vsWorld;
		ID3D11Buffer *poConstantBuff_vsView;

		// Shader resources - conditional depending on shader
		ID3D11Buffer *poConstantBuff_vsLightColor;
		ID3D11Buffer *poConstantBuff_vsLightPos;

		//
		ID3D11Buffer *poConstantBuff_psUvMatrix; // for sprite texture
		ID3D11Buffer *poConstantBuff_psSpriteColor;

		//Constant buffer clip data
		ID3D11Buffer *poConstantBuff_vsInvBind;//how to plug in inverse bind? what is the span? should this be a constant buff?
		ID3D11Buffer *poConstantBuff_vsBoneWorld;

		Mat4 *poInvBindArray;
	};
}

#endif

// --- End of File ---
