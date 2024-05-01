//2024. Caleb Papay

#include "Game.h"
#include "MathEngine.h"
#include "GameObjectSprite.h"
#include "GraphicsObject_Sprite.h"
#include "GraphicsObject.h"
#include "Mesh.h"
#include "Anim.h"

namespace Azul
{
	GameObjectSprite::GameObjectSprite(GraphicsObject *pGraphicsObject)
		: GameObjectRigid(pGraphicsObject),
		scaleX(1.0f),
		scaleY(1.0f),
		posX(0.0f),
		posY(0.0f),
		angle(0.0f),
		cur_rot(0.0f)
	{
		assert(pGraphicsObject);

		this->pGraphicsObjectSprite = (GraphicsObject_Sprite *)poGraphicsObject; //alias

		this->angle = 0.0f;
		this->posX = pGraphicsObjectSprite->origPosX;
		this->posY = pGraphicsObjectSprite->origPosY;
		this->scaleX = 1.0f;
		this->scaleY = 1.0f;

	}

	GameObjectSprite::~GameObjectSprite()
	{

	}

	void GameObjectSprite::SetImage(Image::Name imageName)
	{
		pGraphicsObjectSprite->SetImage(imageName);
	}

	void GameObjectSprite::privUpdate(AnimTime currentTime)
	{
		AZUL_UNUSED_VAR(currentTime);

		// Goal: update the world matrix
		Scale S(this->scaleX, this->scaleY, 1.0f);
		Quat Q(Rot1::Z, this->angle);
		Trans T(this->posX, this->posY, 0.0f);


		cur_rot += delta_rot;
		Rot Rz(Rot1::Z, cur_rot);

		// world matrix
		*this->poWorld = S * Q * Rz * T;

	}

	void GameObjectSprite::Update(AnimTime currentTime)
	{
		// Goal: update the world matrix
		this->privUpdate(currentTime);

		// update the bounding volume based on world matrix
		this->poGraphicsObject->SetWorld(*this->poWorld);
	}


}

// --- End of File ---