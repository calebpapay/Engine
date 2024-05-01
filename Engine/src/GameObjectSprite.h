//2024. Caleb Papay

#ifndef GAME_OBJECT_SPRITE_H
#define GAME_OBJECT_SPRITE_H

#include "GameObjectRigid.h"
#include "MathEngine.h"
#include "ShaderObject.h"
#include "Mesh.h"
#include "GraphicsObject.h"
#include "PCSNode.h"
#include "Image.h"
#include "AnimTime.h"
#include "GraphicsObject_Sprite.h"

namespace Azul
{
	class GameObjectSprite : public GameObjectRigid
	{
	public:
		GameObjectSprite(GraphicsObject *graphicsObject);

		// Big four
		GameObjectSprite() = delete;
		GameObjectSprite(const GameObjectSprite &) = delete;
		GameObjectSprite &operator=(GameObjectSprite &) = delete;
		virtual ~GameObjectSprite();

		virtual void Update(AnimTime currTime);

		void SetImage(Image::Name image);

	private:
		void privUpdate(AnimTime currTime);

	public:   // add accessors later
		float scaleX;
		float scaleY;
		float posX;
		float posY;
		float angle;
		float cur_rot;
		float delta_rot;
		Mat4 *poLocal;

		// alias
		GraphicsObject_Sprite *pGraphicsObjectSprite;
	};
}

#endif

// --- End of File ---