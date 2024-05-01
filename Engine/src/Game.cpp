
//2024. Caleb Papay


#include <d3d11.h>
#include <d3dcompiler.h>
#include <WinUser.h>
#include "Game.h"
#include "Engine.h"
#include "MathEngine.h"
#include "Colors.h"
#include "GameObject.h"

#include "ShaderObject.h"
#include "ShaderObject_ColorByVertex.h"
#include "ShaderObject_FlatTexture.h"
#include "ShaderObject_LightTexture.h"
#include "ShaderObject_ConstColor.h"
#include "ShaderObject_Sprite.h"
#include "Mesh.h"
#include "MeshProto.h"
#include "GraphicsObject_ColorByVertex.h"
#include "GraphicsObject_Wireframe.h"
#include "GraphicsObject_FlatTexture.h"
#include "GraphicsObject_LightTexture.h"
#include "GraphicsObject_ConstColor.h"
#include "GraphicsObject_Sprite.h"
#include "GraphicsObject_SkinFlatTexture.h"
#include "GameObjectAnimSkin.h"
#include "GameObjectMan.h"
#include "MeshNodeMan.h"
#include "ShaderObjectNodeMan.h"
#include "TextureObject.h"
#include "TextureProto.h"
#include "TexNodeMan.h"
#include "DirectXDeviceMan.h"
#include "MultiMesh.h"

#include "AnimTimer.h"
#include "MathApp.h"
#include "Anim.h"
#include "GameObjectBasic.h"
#include "TimerController.h"
#include "AnimController.h"
#include "Clip.h"

#include "AnimMan.h"
#include "GraphicsObject_SkinLightTexture.h"


#include "Camera.h"
#include "CameraMan.h"
#include "Camera_GodState.h"
#include "CameraNull.h"
#include "Camera_Debug.h"
#include "CameraMesh.h"
#include "Image.h"
#include "ImageMan.h"
#include "GameObjectSprite.h"
#include "GlyphMan.h"

#include "FontSprite.h"
#include "ClipMan.h"
#include "SkelMan.h"
#include "HierarchyMan.h"
#include "InvBindMan.h"
#include "ComputeRSVBuffer.h"
#include "ComputeUAVBuffer.h"
#include "Mixer.h"
#include "WorldCompute.h"
#include "AnimInstanceMan.h"

using namespace Azul;

namespace Azul
{

	//// Todo: clean up
	//AnimPod *poPod;

	FontSprite *pFontSprite1;

	//---------------
	//  Game::Game()
	//		Game Engine Constructor
	//---------------
	Game::Game(const char *const pName, int width, int height)
		: Engine(pName, width, height)
	{
		this->globalTimer.Tic();
		this->intervalTimer.Tic();
	}

	//---------------
	//  Game::~Game()
	//		Game Engine destructor
	//---------------
	Game::~Game()
	{
	}

	//---------------
	// Game::LoadContent()
	//		Allows you to load all content needed for your engine,
	//	    such as objects, graphics, etc.
	//---------------
	bool Game::LoadContent()
	{
		ShaderObjectNodeMan::Create();
		MeshNodeMan::Create();
		GameObjectMan::Create();
		TexNodeMan::Create();
		CameraMan::Create();
		ImageMan::Create();
		AnimMan::Create();
		GlyphMan::Create();
		ClipMan::Create();
		SkelMan::Create();
		AnimInstanceMan::Create();
		HierarchyMan::Create();
		InvBindMan::Create();
		// --------------------------
		// Camera setup
		// --------------------------

		// ---------------------------------
	//  Camera - Setup
	// ---------------------------------
		Vec3 up_Vec(0.0f, 1.0f, 0.0f);
		Vec3 tarVec(0.0f, 0.0f, 6.0f);
		Vec3 camPos(0.0f, 0.0f, -6.0f);

		{
			Camera *pCamGod = new Camera_GodState(Camera::Type::PERSPECTIVE_3D);
			assert(pCamGod);
			pCamGod->setViewport(0, 0, this->WindowWidth, this->WindowHeight);
			pCamGod->setPerspective(25.0f, float(pCamGod->getScreenWidth()) / float(pCamGod->getScreenHeight()), 1.0f, 100000.0f);
			pCamGod->setOrientAndPosition(Vec3(0.0f, 1.0f, 0.0f),
										Vec3(0.0f, 0.0f, -1.0f),
										Vec3(0.0f, 0.0f, 35.0f));
			
			CameraMan::Add(pCamGod, Camera::Name::CAMERA_0);
			CameraMan::SetCurrent(Camera::Name::CAMERA_0, Camera::Type::PERSPECTIVE_3D);
		}

		{
			Camera *pCam = new CameraDebug();
			assert(pCam);
			pCam->setViewport(0, 0, this->WindowWidth, this->WindowHeight);
			pCam->setOrthographic((float)-pCam->getScreenWidth() / 2.0f, (float)pCam->getScreenWidth() / 2.0f,
									(float)-pCam->getScreenHeight() / 2.0f, (float)pCam->getScreenHeight() / 2.0f,
									1.0f, 1000.0f);
			pCam->setOrientAndPosition(Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(0.0f, 0.0f, 2.0f));
			CameraMan::Add(pCam, Camera::Name::CAMERA_1);
			
			CameraMan::SetCurrent(Camera::Name::CAMERA_1, Camera::Type::ORTHOGRAPHIC_2D);
		}

		// --------------------------------
		//  Mesh
		// --------------------------------

	

		//Mesh *poMeshSprite = new MeshProto("SpriteMesh.m.proto.azul");
		/*Mesh *poMeshSprite =*/ MeshNodeMan::Add(Mesh::Name::SPRITE, "SpriteMesh.m.proto.azul")->GetMesh();
		Mesh *poMeshR2 = MeshNodeMan::Add(Mesh::Name::R2, "R2-D2.m.proto.azul")->GetMesh();
		Mesh *poCrate = MeshNodeMan::Add(Mesh::Name::CRATE, "crate.m.proto.azul")->GetMesh();
		Mesh *poFrigate = MeshNodeMan::Add(Mesh::Name::FRIGATE, "space_frigate.m.proto.azul")->GetMesh();


	//	//
	//	//// -----------------------------------
	//	////  Texture
	//	//// -----------------------------------
		TextureObject *pTexFrigate = TexNodeMan::Add(TextureObject::Name::Frigate, "space_frigate.t.proto.azul");
		TextureObject *pTexR2 = TexNodeMan::Add(TextureObject::Name::R2, "R2D2_BaseColor.t.proto.azul");
		TextureObject *pTexCrate = TexNodeMan::Add(TextureObject::Name::Crate, "crate.t.proto.azul");
		TexNodeMan::Add(TextureObject::Name::Test0, "TEST_PNG_RGB.t.proto.azul");
		TexNodeMan::Add(TextureObject::Name::Test1, "TEST_PNG_RGBA.t.proto.azul");
		TexNodeMan::Add(TextureObject::Name::Test2, "TEST_TGA_BGR.t.proto.azul");
		TexNodeMan::Add(TextureObject::Name::Test3, "TEST_TGA_BGRA.t.proto.azul");
		TexNodeMan::Add(TextureObject::Name::FontAriel36, "FontArial36.t.proto.azul");
		TexNodeMan::Add(TextureObject::Name::FontConsolas15, "Consolas15pt.t.proto.azul");

		
	//	// -----------------------------------
	//	//Setup 2D images
	//	// -----------------------------------

		ImageMan::Add(Image::Name::WhiteBird, TextureObject::Name::Test1, Rect(139.0f, 131.0f, 84.0f, 97.0f));
		ImageMan::Add(Image::Name::RedBird, TextureObject::Name::Test1, Rect(45.0f, 35.0f, 50.0f, 50.0f));
		ImageMan::Add(Image::Name::GreenBird, TextureObject::Name::Test1, Rect(244.0f, 134.0f, 102.0f, 75.0f));
		ImageMan::Add(Image::Name::Stitch,TextureObject::Name::Test3, Rect(299.0f, 409.0f, 299.0f, 409.0f));
		ImageMan::Add(Image::Name::FontImage, TextureObject::Name::FontAriel36, Rect(299.0f, 409.0f, 299.0f, 409.0f));

		GlyphMan::Add("MetricsArial36.xml.proto.azul", Glyph::Name::Arial36pt, TextureObject::Name::FontAriel36);
		GlyphMan::Add("MetricsConsolas15.xml.proto.azul", Glyph::Name::Consolas15pt, TextureObject::Name::FontConsolas15);

		GraphicsObject *pGraphicsObject(nullptr);
	//	// FontSprite
		pGraphicsObject = new GraphicsObject_Sprite(Image::GreenBird,
													Rect(100, 100, 100, 100));
		GameObjectSprite *pSprite = new GameObjectSprite(pGraphicsObject);
		GameObjectMan::Add(pSprite, GameObjectMan::GetRoot());

		

		pGraphicsObject = new GraphicsObject_Sprite(Image::FontImage,  
													Rect(100, 100, 100, 100)); //anything
		pFontSprite1 = new FontSprite(pGraphicsObject);
		GameObjectMan::Add(pFontSprite1, GameObjectMan::GetRoot());

		Color color(0, 0, 1.0f, 1.0f);
		pFontSprite1->Set(FontSprite::Name::TestOneOff, "PRESS Z", Glyph::Name::Arial36pt, 100, 500, color);

	
		GameObjectBasic *pGameObj(nullptr);

	
		
		{

			// -----------------------------------
			//Render r2
			// -----------------------------------
			pGraphicsObject = new GraphicsObject_FlatTexture(poMeshR2,pTexR2);

			pGameObj = new GameObjectBasic(pGraphicsObject);
			pGameObj->SetTrans(-5.0f, 2.5f, 10.0f);
			pGameObj->SetScale(100.0f, 100.0f, 100.0f);
			Quat test(Rot1::X, -1.5708f);
			pGameObj->SetQuat(test);
			//pGameObj->delta_z = 0.01f;
			pGameObj->delta_y = 0.007f;
			//pGameObj->delta_x = 0.0075f;
			GameObjectMan::Add(pGameObj, GameObjectMan::GetRoot());


			pGraphicsObject = new GraphicsObject_Wireframe(poMeshR2, ShaderObject::Name::ConstColor, tarVec);

			pGameObj = new GameObjectBasic(pGraphicsObject);
			pGameObj->SetTrans(5.0f, 2.5f, 10.0f);
			
			pGameObj->SetScale(100.0f, 100.0f, 100.0f);
			Quat test2(Rot1::X, -1.5708f);
			pGameObj->SetQuat(test2);
			//pGameObj->delta_z = 0.01f;
			pGameObj->delta_y = 0.007f;
			//pGameObj->delta_x = 0.0075f;
			GameObjectMan::Add(pGameObj, GameObjectMan::GetRoot());
		}


		{
			// -----------------------------------
			//Render crate and frigate
			// -----------------------------------
			pGraphicsObject = new GraphicsObject_FlatTexture(poCrate, pTexCrate);

			pGameObj = new GameObjectBasic(pGraphicsObject);
			pGameObj->SetTrans(-7.5f, -4.5f, 3.0f);
		
			//pGameObj->SetScale(1.0f, 1.0f, 1.0f);
			pGameObj->delta_z = 0.03f;
			pGameObj->delta_y = 0.02f;
			pGameObj->delta_x = 0.03f;
			GameObjectMan::Add(pGameObj, GameObjectMan::GetRoot());


			pGraphicsObject = new GraphicsObject_FlatTexture(poFrigate, pTexFrigate);

			pGameObj = new GameObjectBasic(pGraphicsObject);

			pGameObj->SetTrans( 7.5f, -4.5f, 3.0f);
			pGameObj->SetScale( 0.07f,0.07f, 0.07f);
			Quat test2(Rot1::Z, -1.5708f);
			pGameObj->SetQuat(test2);
			pGameObj->delta_z = 0.01f;
			//pGameObj->delta_y = 0.02f;
			pGameObj->delta_x = 0.003f;
			GameObjectMan::Add(pGameObj, GameObjectMan::GetRoot());
		}


		// -----------------------------------
		//SETUP animations
		// -----------------------------------
		{
			Vec3 startPos1(-2.0f, -1.0f, 11.0f); //top
			Vec3 startPos2(2.0f, -1.0f, 11.0f);//bottom
			Quat test3(Rot1::Z, 1.5708f);

			TexNodeMan::Add(TextureObject::Name::ChickenBot, "ChickenbotDiffuse.t.proto.azul");
			MeshNodeMan::Add(Mesh::Name::CHICKENBOT, "Chickenbot.m.proto.azul");


			TexNodeMan::Add(TextureObject::Name::ChickenBot, "ChickenbotDiffuse.t.proto.azul");
			MeshNodeMan::Add(Mesh::Name::CHICKENBOT, "Chickenbot.m.proto.azul");
			HierarchyMan::Add("chicken_table.h.proto.azul", Hierarchy::Name::ChickenBot);
			ClipMan::Add("chicken_clip_walk.a.proto.azul", Clip::Name::Walk_ChickenBot);
			ClipMan::Add("chicken_clip_dieLeft.a.proto.azul", Clip::Name::Die_ChickenBot); 
			ClipMan::Add("chicken_shot_up.a.proto.azul", Clip::Name::Shoot_ChickenBot);
			InvBindMan::Add("chicken_invBind.i.proto.azul", InvBind::Name::ChickenBot);

			// Create Anim
			Clip *pClip = ClipMan::Find(Clip::Name::Walk_ChickenBot);
			Mixer *ptMixer = new Mixer(pClip);
			WorldCompute *ptWorldCompute = new WorldCompute(ptMixer, Hierarchy::Name::ChickenBot, InvBind::Name::ChickenBot);
			assert(ptWorldCompute);
			AnimMan::Add(Anim::Name::Anim0, pClip, ptMixer, ptWorldCompute);

			// Skin Mesh
			GameObjectAnimSkin *pGameSkin;
			GraphicsObject_SkinLightTexture *pGraphicsSkin;

			Vec3 lightCol(1.9f, 1.9f, 1.9f);
			Vec3 lightPos(-100000, 100000, 0);


			for(int i = 0; i < 10; i++)
			{
				for(int j = 0; j < 10; j++)
				{


					pGraphicsSkin = new GraphicsObject_SkinLightTexture(Mesh::Name::CHICKENBOT,
																		ShaderObject::Name::SkinLightTexture,
																		TextureObject::Name::ChickenBot,
																		ptMixer,
																		ptWorldCompute, lightCol, lightPos);

					// add Mixer and WorldCompute to Game Object
					pGameSkin = new GameObjectAnimSkin(pGraphicsSkin, ptMixer, ptWorldCompute);
					pGameSkin->SetName("ChickenSkin");
					pGameSkin->delta_y = 0.003f;
					pGameSkin->SetTrans(i+20.0f, 0.0f, j+20.0f);
					GameObjectMan::Add(pGameSkin, GameObjectMan::GetRoot());


					AnimController *pAnimController = AnimInstanceMan::Add(AnimController::Name::ZERO, Anim::Name::Anim0, pGameSkin); //add for future control
					pAnimController->SetQuat(test3);
					pGameSkin->SetScale(50, 50, 50);

				}
			}

			pClip = ClipMan::Find(Clip::Name::Die_ChickenBot);
			// Mixer and WorldCompute 
			ptMixer = new Mixer(pClip);
			ptWorldCompute = new WorldCompute(ptMixer, Hierarchy::Name::ChickenBot, InvBind::Name::ChickenBot);
			assert(ptWorldCompute);
			AnimMan::Add(Anim::Name::Anim1, pClip, ptMixer, ptWorldCompute);

			for(float i = 0.0f; i < 10.0f; i++)
			{
				for(float j = 0.0f; j < 10.0f; j++)
				{
					pGraphicsSkin = new GraphicsObject_SkinLightTexture(Mesh::Name::CHICKENBOT,
																		ShaderObject::Name::SkinLightTexture,
																		TextureObject::Name::ChickenBot,
																		ptMixer,
																		ptWorldCompute, lightCol, lightPos);

																		// add Mixer and WorldCompute to Game Object
					pGameSkin = new GameObjectAnimSkin(pGraphicsSkin, ptMixer, ptWorldCompute);
					pGameSkin->SetName("ChickenSkin");
					pGameSkin->delta_y = 0.003f;
					pGameSkin->SetTrans(i+20.0f, 0.0f, j);
					GameObjectMan::Add(pGameSkin, GameObjectMan::GetRoot());


					AnimController *pAnimController = AnimInstanceMan::Add(AnimController::Name::ONE, Anim::Name::Anim1, pGameSkin); //add for future control
					pAnimController->SetQuat(test3);
					pGameSkin->SetScale(50, 50, 50);

				}
			}

			pClip = ClipMan::Find(Clip::Name::Shoot_ChickenBot);
			ptMixer = new Mixer(pClip);
			ptWorldCompute = new WorldCompute(ptMixer, Hierarchy::Name::ChickenBot, InvBind::Name::ChickenBot);
			assert(ptWorldCompute);
			AnimMan::Add(Anim::Name::Anim2, pClip, ptMixer, ptWorldCompute);

			for(float i = 0.0f; i < 10.0f; i++)
			{
				for(float j = 0.0f; j < 10.0f; j++)
				{
					pGraphicsSkin = new GraphicsObject_SkinLightTexture(Mesh::Name::CHICKENBOT,
																		ShaderObject::Name::SkinLightTexture,
																		TextureObject::Name::ChickenBot,
																		ptMixer,
																		ptWorldCompute, lightCol, lightPos);

					// add Mixer and WorldCompute to Game Object
					pGameSkin = new GameObjectAnimSkin(pGraphicsSkin, ptMixer, ptWorldCompute);
					pGameSkin->SetName("ChickenSkin");
					pGameSkin->delta_y = 0.003f;
					pGameSkin->SetTrans(i-20.0f, 0.0f, j);
					GameObjectMan::Add(pGameSkin, GameObjectMan::GetRoot());


					AnimController *pAnimController = AnimInstanceMan::Add(AnimController::Name::TWO, Anim::Name::Anim2, pGameSkin); //add for future control
					pAnimController->SetQuat(test3);
					pGameSkin->SetScale(50, 50, 50);

				}
			}



			//MOUSEY//**********************

			TexNodeMan::Add(TextureObject::Name::RatThing, "rat_thing.t.proto.azul");
			MeshNodeMan::Add(Mesh::Name::RAT_THING, "rat_thing.m.proto.azul");

			HierarchyMan::Add("rat_thing_table.h.proto.azul", Hierarchy::Name::Rat);
			ClipMan::Add("rat_thing_jump.a.proto.azul", Clip::Name::Jump_Rat);
			InvBindMan::Add("rat_thing_invBind.i.proto.azul", InvBind::Name::Rat);

			pClip = ClipMan::Find(Clip::Name::Jump_Rat);
			ptMixer = new Mixer(pClip);
			ptWorldCompute = new WorldCompute(ptMixer, Hierarchy::Name::Rat, InvBind::Name::Rat);
			assert(ptWorldCompute);
			AnimMan::Add(Anim::Name::Anim3, pClip, ptMixer, ptWorldCompute);


			// Skin Mesh
			for(float i = 0.0f; i < 10.0f; i++)
			{
				for(float j = 0.0f; j < 10.0f; j++)
				{
					pGraphicsSkin = new GraphicsObject_SkinLightTexture(Mesh::Name::RAT_THING,
																		ShaderObject::Name::SkinLightTexture,
																		TextureObject::Name::RatThing,
																		ptMixer,
																		ptWorldCompute, lightCol, lightPos);

					// add Mixer and WorldCompute to Game Object
					pGameSkin = new GameObjectAnimSkin(pGraphicsSkin, ptMixer, ptWorldCompute);
					pGameSkin->SetName("RatSkin");
					//pGameSkin->delta_y = 0.003f;
					pGameSkin->SetTrans(i, 0.0f, j);
					GameObjectMan::Add(pGameSkin, GameObjectMan::GetRoot());


					AnimInstanceMan::Add(AnimController::Name::THREE, Anim::Name::Anim3, pGameSkin); //add for future control

				}
			}




			TexNodeMan::Add(TextureObject::Name::SARDAUKAR, "Sardaukar.t.proto.azul");
			MeshNodeMan::Add(Mesh::Name::SARDAUKAR, "Sardaukar.m.proto.azul");
			HierarchyMan::Add("Sardaukar.h.proto.azul", Hierarchy::Name::Guy);
			ClipMan::Add("Sardaukar.a.proto.azul", Clip::Name::Guy_Dying);
			InvBindMan::Add("Sardaukar_invBind.i.proto.azul", InvBind::Name::Guy);

			pClip = ClipMan::Find(Clip::Name::Guy_Dying);

			ptMixer = new Mixer(pClip);



			ptWorldCompute = new WorldCompute(ptMixer, Hierarchy::Name::Guy, InvBind::Name::Guy);
			assert(ptWorldCompute);

			// Anim needs: 
			AnimMan::Add(Anim::Name::Anim4, pClip, ptMixer, ptWorldCompute);
			//assert(ptAnim);

			// Skin Mesh

			// add Mixer and WorldCompute to Graphics Object // for future -> provide Anim name and get mixer and compute from anim
			pGraphicsSkin = new GraphicsObject_SkinLightTexture(Mesh::Name::SARDAUKAR,
															   ShaderObject::Name::SkinLightTexture,
															   TextureObject::Name::SARDAUKAR,
															   ptMixer,
															   ptWorldCompute, lightCol, lightPos);

			// add Mixer and WorldCompute to Game Object
			pGameSkin = new GameObjectAnimSkin(pGraphicsSkin, ptMixer, ptWorldCompute);
			pGameSkin->SetName("GuySkin");
			//pGameSkin->delta_y = 0.003f;
			pGameSkin->SetTrans(6, 0, -10);
			GameObjectMan::Add(pGameSkin, GameObjectMan::GetRoot());


			AnimController* aC = AnimInstanceMan::Add(AnimController::Name::FOUR, Anim::Name::Anim4, pGameSkin); //add for future control
			aC->SetScale(6, 6, 6);
		}
		

		return true;
	}





	//---------------
	// Game::Update()
	//      Called once per frame, update data, tranformations, etc
	//      Use this function to control process order
	//      Input, AI, Physics, Animation, and Graphics
	//---------------
	//Hacky input system;
	Vec3 obj(0.0f, 0.0f, 0.0f);
	bool keyZ = false;
	bool keyX = false;
	bool key0 = false;
	bool key1 = false;
	bool space = false;
	bool paused = false;
	bool keyR = false;
	bool rev = false;
	int countTemp = 0;
	static int txtcount = 0;
	void Game::Update(float)
	{
		this->intervalTimer.Toc();
		this->intervalTimer.Tic();


	
			// ------------------------------------
			// Update the camera once per frame
			// ------------------------------------
			if((GetKeyState('Z') & 0x8000) && !keyZ)
			{
				
				txtcount++;
				char buff[20];
				memset(buff, 0x0, 20);
				sprintf_s(buff, 20, "Test: %d", txtcount);
				pFontSprite1->UpdateMessage(buff);
				keyZ = true;
				//FOR LATER USE
			}
			if((GetKeyState('X') & 0x8000) && !keyX)
			{
				keyX = true;
				//FOR LATER USE
			}
			
			if((GetKeyState('R') & 0x8000) && !keyR)
			{
				keyR = true;
				rev = true;
				
			}
			if((GetKeyState(VK_SPACE) & 0x8000) && !space)
			{
				space = true;
				paused = !paused;

			}
		
			if((GetKeyState('0') & 0x8000) && !key0)
			{
				key0 = true;
		
				AnimMan::SetClip(Anim::Name::Anim0, ClipMan::Find(Clip::Name::Shoot_ChickenBot));
				AnimMan::SetClip(Anim::Name::Anim1, ClipMan::Find(Clip::Name::Walk_ChickenBot));
		
			}

			if((GetKeyState('1') & 0x8000) && !key1)
			{
				key1 = true;
				AnimMan::SetClip(Anim::Name::Anim0, ClipMan::Find(Clip::Name::Shoot_ChickenBot));
				AnimMan::SetClip(Anim::Name::Anim1, ClipMan::Find(Clip::Name::Walk_ChickenBot));
		
			}

			if(!(GetKeyState('Z') & 0x8000) && keyZ)
			{
				keyZ = false;
			}
			if(!(GetKeyState('X') & 0x8000) && keyX)
			{
				keyX = false;
			}
			if(!(GetKeyState('R') & 0x8000) && keyR)
			{
				keyR = false;
			}
			if(!(GetKeyState(VK_SPACE) & 0x8000) && space)
			{
				space = false;
			}
			if(!(GetKeyState('0') & 0x8000) && key0)
			{
				key0 = false;
			}
			if(!(GetKeyState('1') & 0x8000) && key1)
			{
				key1 = false;
			}
		// -----------------------------------------------
		// Update animation Controller
		// -----------------------------------------------
		if(!paused)
		{
			AnimInstanceMan::Update();
		}

		
		// ------------------------------------
		// Update the camera once per frame
		// ------------------------------------
		CameraMan::Update();
		

		// -----------------------------------------------
		// Game update
		// -----------------------------------------------
		GameObjectMan::Update(this->globalTimer.Toc());
	}

	

	//---------------
	// Game::Render()
	//		This function is called once per frame
	//	    Use this for draw graphics to the screen.
	//      Only do rendering here
	//---------------
	void Game::Render()
	{
		this->SetDefaultTargetMode();

		GameObjectMan::Draw();
	}


	//---------------
	// Game::UnLoadContent()
	//       unload content (resources loaded above)
	//       unload all content that was loaded before the Engine Loop started
	//---------------
	void Game::UnloadContent()
	{
		HierarchyMan::Destroy();
		InvBindMan::Destroy();
		ImageMan::Destroy();
		GlyphMan::Destroy();
		AnimMan::Destroy();
		CameraMan::Destroy();
		ShaderObjectNodeMan::Destroy();
		MeshNodeMan::Destroy();
		GameObjectMan::Destroy();
		ClipMan::Destroy();
		SkelMan::Destroy();
		AnimInstanceMan::Destroy();
		TexNodeMan::Destroy();
		DirectXDeviceMan::Destroy();
	}


	// Game::ClearBufferFunc()
	// Allows user to change the way the clear buffer function works
	// 
	// Clear the color and depth buffers.
	void Game::ClearDepthStencilBuffer()
	{
#ifdef _DEBUG
		const Vec4 ClearColor = Azul::Colors::LightGray;
#else
		const Vec4 ClearColor = Azul::Colors::Wheat;
#endif
		float clearDepth = 1.0f;
		uint8_t clearStencil = 0;
		g_d3dDeviceContext->ClearRenderTargetView(g_d3dRenderTargetView, (const float *)&ClearColor);
		g_d3dDeviceContext->ClearDepthStencilView(g_d3dDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, clearDepth, clearStencil);
	}

}

// --- End of File ---
