//----------------------------------------------------------------------------
//2024. Caleb Papay
//----------------------------------------------------------------------------

#include "GLTF.h"
#include "meshData.h"
#include "meshDataConverter.h"
#include "json.hpp"
#include "File.h"
#include "MathEngine.h"
#include "ConvertSkeleton.h"
#include "skeletonConverter.h"

using namespace Azul;
using namespace tinygltf;
using json = nlohmann::json;

namespace Azul
{
	void ConvertSkeleton(const char *const pName, const char *const pTargetName, int meshNum)
	{
		assert(pName);
		Trace::out("ConvertSkeleton(%s):", pName);

		bool status;
		tinygltf::Model gltfModel;

		// runtime model
		meshData  runModel;

		// glb file name defined here:
		const char *pGLB_Name = pName;
		const char *pGLB_extension = ".glb";

		size_t FileNameSize = strlen(pGLB_Name) + strlen(pGLB_extension) + 1;

		char *poFileName = new char[FileNameSize]();
		strcat_s(poFileName, FileNameSize, pGLB_Name);
		strcat_s(poFileName, FileNameSize, pGLB_extension);

		// Load the gltfModel
		status = GLTF::LoadBinary(gltfModel, poFileName);
		assert(status);

		// SKELETON
		SKEL skelData;
		skelData.CreateSkeleton(gltfModel, pTargetName, meshNum);

		delete[] poFileName;
	}
}

// --- End of File ---
