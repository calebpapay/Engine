//----------------------------------------------------------------------------
//2024. Caleb Papay
//----------------------------------------------------------------------------

#include "GLTF.h"
#include "ConvertModel.h"
#include "ConvertSkin.h"
#include "CreateTexture.h"
#include "CubeMesh.h"
#include "SphereMesh.h"
#include "PyramidMesh.h"
#include "ConvertAnim.h"
#include "SpriteMesh.h"
#include "FontConverter.h"
#include "ConvertSkeleton.h"
#include "ConvertHierarchy.h"
//#include "ConvertAnimModel.h"
using namespace Azul;

int main()
{
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION; 
	//Sleep(500);
	Trace::out("PugiXml - test 1\n");
	CreateTexturePNG("FontArial36.png", "FontArial36");
	ReadXMLData("MetricsArial36" );

	CreateTexturePNG("Consolas15pt.png", "Consolas15pt");
	ReadXMLData("MetricsConsolas15");


	//ConvertAnimModel("walk_mesh", "chicken_skin", "chicken_skel");
	ConvertSkin("walk_mesh", "Chickenbot");
	ConvertHierarchy("walk_mesh", "chicken_table");
	ConvertInvBind("walk_mesh", "chicken_invBind");
	//ConvertSkeleton("walk_mesh", "chicken_skel");
	ConvertAnim("walk_mesh", "chicken_clip_walk");
	ConvertAnim("shot_up_mesh", "chicken_shot_up");
	ConvertAnim("die_left_mesh", "chicken_clip_dieLeft");

	ConvertSkin("joyful_jump", "rat_thing");
	ConvertHierarchy("joyful_jump", "rat_thing_table");
	ConvertInvBind("joyful_jump", "rat_thing_invBind");
	ConvertSkeleton("joyful_jump", "rat_thing");
	ConvertAnim("joyful_jump", "rat_thing_jump");
	CreateTexturePNG("Ch14_1001_Diffuse.png", "rat_thing");


	//ConvertSkin("Jog_Circle", "rat_thing");
	//ConvertHierarchy("Jog_Circle", "rat_thing_table");
	//ConvertInvBind("Jog_Circle", "rat_thing_invBind");
	//ConvertSkeleton("Jog_Circle", "rat_thing");
	//ConvertAnim("Jog_Circle", "rat_thing_jog");
	//CreateTexturePNG("Ch14_1001_Diffuse.png", "rat_thing");

	ConvertSkin("dying_vanguard", "Sardaukar", 1);
	ConvertHierarchy("dying_vanguard", "Sardaukar",1);
	ConvertInvBind("dying_vanguard", "Sardaukar_invBind");
	ConvertSkeleton("dying_vanguard", "Sardaukar", 1);
	ConvertAnim("dying_vanguard", "Sardaukar", 1);
	CreateTexturePNG("vanguard_diffuse1.png", "Sardaukar");

	CreateSpriteMesh();
	CreateCubeMesh();
	CreateSphereMesh();	
	CreatePyramidMesh();

	ConvertModel("space_frigate.glb", "space_frigate");
	ConvertModel("crate.glb","crate");
	ConvertModel("R2-D2.glb", "R2-D2");
	CreateTexturePNG("R2D2_BaseColor.png", "R2D2_BaseColor");
	CreateTexturePNG("TEST_PNG_RGB.png", "TEST_PNG_RGB");
	CreateTexturePNG("TEST_PNG_RGBA.png", "TEST_PNG_RGBA");
	CreateTextureTGA("TEST_TGA_BGR.tga", "TEST_TGA_BGR");
	CreateTextureTGA("TEST_TGA_BGRA.tga", "TEST_TGA_BGRA");


	CreateTextureTGA("Duckweed.tga", "Duckweed");
	CreateTextureTGA("RedBrick.tga", "RedBrick");
	CreateTextureTGA("Rocks.tga", "Rocks");
	CreateTextureTGA("Stone.tga", "Stone");
	CreateTexturePNG("ChickenbotDiffuse.png","ChickenbotDiffuse");  //<--- use this for the model
	
	/*CreateChickenBotModels();
	CreateChickenBotSkel("walk_mesh");
	
	CreateChickenBotModelsAnim("die_left_mesh", "DIE LEFT");
	CreateChickenBotModelsAnim("shot_up_mesh", "BLAST SKY");
	CreateChickenBotModelsAnim("walk_mesh", "WALK");
	CreateChickenBotModelsAnim("sidestep_right_mesh", "STEP RIGHT");*/

	// clean up data directory
	system("del *.png");
	system("del *.tga");
	system("del *.glb");
	system("del *.xml");
	//Sleep(500);
	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}

// ---  End of File ---------------
