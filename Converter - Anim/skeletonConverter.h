//----------------------------------------------------------------------------
//2024. Caleb Papay
//----------------------------------------------------------------------------

#ifndef SKELETON2_H
#define SKELETON2_H

#include <vector>

#include "tiny_gltf.h"
#include "MathEngine.h"

#include "skelData.h"

using namespace tinygltf;

namespace Azul
{

	struct skeleton
	{
		skeleton();
		skeleton(const skeleton &) = default;
		skeleton &operator = (const skeleton &) = default;
		~skeleton() = default;

		int			nodeIndexInSkel;
		int          nodeIndex;
		std::string  nodeName;
		int			parentIndexInSkel;
		int          parentIndex;
		std::string  parentName;
	};

	struct skeleton_table
	{
		//static const unsigned int SKELETON_NAME_SIZE = 64;
		// use SkelData.h
		bool operator<(const skeleton_table &other) const
		{
			return parentIndex < other.parentIndex;
		}

		skeleton_table() = default;
		skeleton_table(const skeleton_table &) = default;
		skeleton_table &operator = (const skeleton_table &) = default;
		~skeleton_table() = default;

		int   nodeIndex;
		int   parentIndex;
		char  nodeName[skelEntry::SKELETON_NAME_SIZE];
	};

	class SKEL
	{
	public:
		void CreateSkeleton(Model &model, const char *const pTargetName, int meshNum = 0);
		void CreateHierarchy(Model &model, const char *const pTargetName, int meshNum = 0);
	private:
		std::vector<skeleton>      skeletonVector;
		std::vector<skeleton_table> skeletonTable;

	};

}

#endif

// --- End of File ---
