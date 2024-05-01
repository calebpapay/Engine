//2024. Caleb Papay

#include "Anim.h"
#include "Mixer.h"
#include "Clip.h"


namespace Azul
{
	//extern Clip *pWalkClip;
	Anim::Anim()
		:name(Name::NULL_ANIM),
		//poBoneResult(nullptr),
		//texName(TextureObject::Name::NullTexture),
		//poHierarchy(nullptr),
		pClip(nullptr),
		pMixer(nullptr),
		poWorldCompute(nullptr)
	{

	}


	void Anim::Set(Anim::Name _name, Clip* pC, Mixer *pMix, WorldCompute* pWorldCompute)
	{
		this->name = _name;
	
		assert(pC);
		assert(pMix);
		this->pClip = pC;
		this->pMixer = pMix;
		this->poWorldCompute = pWorldCompute;
	}

	/*Skel::Name Anim::GetSkelName()
	{
		return this->pClip->GetSkelName();
	}*/
	//Mesh::Name Anim::GetMeshName()
	//{
	//	return this->pClip->GetMeshName();
	//}

	Clip *Anim::GetClip()
	{
		return this->pClip;
	}

	//TextureObject::Name Anim::GetTextureName()
	//{
	//	return this->texName;
	//}

	//Bone *Anim::FetchBones()
	//{
	//	//good boy
	//	return poBoneResult;
	//}

	

	char *Anim::GetName()
	{
		static char pTmp[128];
		//strcpy_s(pTmp, 128, StringMe(this->name));
		return pTmp;
	}

	void Anim::SetName(Anim::Name _name)
	{
		this->name = _name;
	}

	

	Anim::~Anim()
	{
		//this->pMixer = nullptr;
		delete this->pMixer;
		delete this->poWorldCompute;
		//delete[] this->poBoneResult;
		//delete   this->poHierarchy;
		this->pClip = nullptr;
	}

	AnimTime Anim::FindMaxTime()
	{
		assert(pClip);
		return this->pClip->GetTotalTime();
	}

	//AnimTime Anim::FindDeltaTime()
	//{
	//	assert(pClip);
	//	return this->pClip->GetDeltaTime();
	//}


	void Anim::Animate(AnimTime tCurr)
	{

		
		this->pClip->AnimateBones(tCurr, this->pMixer);
	}

	//void Anim::SetQuat(Quat &r)
	//{
	//	//*this->poQuat = r;
	//	this->poHierarchy->GetPivot()->SetQuat(r);
	//}

	//void Anim::SetDeltaRotXYX(float rX, float rY, float rZ)
	//{
	//	
	//	this->poHierarchy->GetPivot()->delta_x = rX;
	//	this->poHierarchy->GetPivot()->delta_y = rY;
	//	this->poHierarchy->GetPivot()->delta_z = rZ;
	//}



	void Anim::SetClip(Clip* _pClip)
	{
		this->pClip = _pClip;
		/*if(this->pTag)
		{
			
			this->pTag->UpdateMessage(this->pClip->GetName());
		}
		else
		{
			this->pTag = FontMan::Add(Font::Name::TestMessage0, this->pClip->GetName(), Glyph::Name::Consolas15pt, 0.0f, 0.0f);
		}*/
	}




	void Anim::Wash()
	{
		this->pMixer = nullptr;
		//delete   this->poHierarchy;
		this->pClip = nullptr;
	}

	bool Anim::Compare(DLink *pTargetNode)
	{
		// This is used in ManBase.Find() 
		assert(pTargetNode);

		Anim *pDataB = (Anim *)pTargetNode;

		bool status = false;

		if(this->name == pDataB->name)
		{
			status = true;
		}

		return status;
	}

	void Anim::Dump()
	{
		Trace::out("      Anim(%p)\n", this);


		
		DLink::Dump();
	}



	
}

//--- End of File ----