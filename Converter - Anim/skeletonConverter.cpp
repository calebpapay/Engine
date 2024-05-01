//----------------------------------------------------------------------------
//2024. Caleb Papay
//----------------------------------------------------------------------------

#include "skeletonConverter.h"
#include "skelData.h"
#include "File.h"
#include "HierarchyData.h"
#include <algorithm>
#include <unordered_map>

namespace Azul
{
	skeleton::skeleton()
		:nodeIndex(-1),
		nodeName(),
		parentIndex(-1),
		parentName("unknown")
	{

	};

	// Recursive function to sort the vector
	void sortTree(std::vector<skeleton_table> &vec, std::vector<skeleton_table> &sortedVec, int currentIndex)
	{
		// Find children of the current index
		std::vector<skeleton_table> children;
		for(const auto &entry : vec)
		{
			if(entry.parentIndex == currentIndex)
			{
				children.push_back(entry);
			}
		}

		// Append children to sorted vector
		for(const auto &child : children)
		{
			sortedVec.push_back(child);
			// Recursively sort the children's subtree
			sortTree(vec, sortedVec, child.nodeIndex);
		}
	}

	void SKEL::CreateSkeleton(Model &model, const char *const pTargetName, int meshNum)
	{
		assert(pTargetName);

		// Create a skeleton and Fill it
		std::vector<size_t> log;
		log.reserve(model.nodes.size());

		for(size_t i = 0; i < model.nodes.size(); i++)
		{
			/*skeleton tmpSkeleton;*/
			log.push_back((size_t)-1);
		}

		size_t StartNodeIndex = (size_t)model.skins[meshNum].joints[0];
		size_t numJoints = (size_t)model.skins[meshNum].joints.size();
		size_t trueIndex = 0;
		for(size_t i = 0; i < log.size(); i++)
		{
			auto pNode = model.nodes[i];
			for(size_t z = (size_t)model.skins[meshNum].joints[0]; z < StartNodeIndex + numJoints; z++)
			{
				if(model.skins[meshNum].joints[z - StartNodeIndex] == i)
				{
					log[i] = z - StartNodeIndex;
					trueIndex++;
					z = StartNodeIndex + numJoints;
				}
				else
				{

				}
			}
		}



		this->skeletonVector.reserve(model.skins[meshNum].joints.size());
		for(size_t i = 0; i < model.skins[meshNum].joints.size(); i++)
		{
			skeleton tmpSkeleton;
			this->skeletonVector.push_back(tmpSkeleton);
		}

		// Walk through the nodes starting on the node they state

		for(size_t i = StartNodeIndex; i < log.size(); i++)
		{
			size_t isJointed = log[i];
			if(isJointed != -1)
			{
				auto pNode = model.nodes[i];
				skeletonVector[isJointed].nodeIndexInSkel = (int)isJointed;
				skeletonVector[isJointed].nodeIndex = (int)i;
				skeletonVector[isJointed].nodeName = pNode.name;

				for(size_t j = 0; j < pNode.children.size(); j++)
				{
					size_t fillingIndex = log[pNode.children[j]];
					if(fillingIndex != -1)
					{
						skeletonVector[fillingIndex].nodeIndexInSkel = (int)fillingIndex;
						skeletonVector[fillingIndex].nodeIndex = (int)pNode.children[j];
						skeletonVector[fillingIndex].nodeName = model.nodes[(size_t)pNode.children[j]].name;
						skeletonVector[fillingIndex].parentIndexInSkel = ((int)log[i]);
						skeletonVector[fillingIndex].parentIndex = i;
						skeletonVector[fillingIndex].parentName = pNode.name;
					}
					else
					{

					}
				}
			}
		}

		// Fill skeletonTable
		skeletonTable.reserve(skeletonVector.size());
		for(size_t i = 0; i < skeletonVector.size(); i++)
		{
			skeleton_table table;
			
			table.nodeIndex = skeletonVector[i].nodeIndexInSkel;
			table.parentIndex = skeletonVector[i].parentIndexInSkel;

			// Copy the string
			memset(table.nodeName, 0, skelEntry::SKELETON_NAME_SIZE);
			strncpy_s(table.nodeName,
					  skelEntry::SKELETON_NAME_SIZE,
					  skeletonVector[i].nodeName.c_str(),
					  skelEntry::SKELETON_NAME_SIZE - 1);

			//int startIndex = (int)model.skins[meshNum].joints[0];
			//table.nodeIndex = table.nodeIndex - startIndex;
			//table.parentIndex = table.parentIndex - startIndex;
			if(table.parentIndex < -1)
			{
				table.parentIndex = -1;
			}

			skeletonTable.push_back(table);
			
		}

		std::vector<skeleton_table> sortedVec;
		sortedVec.push_back(skeletonTable[0]);
		// Sort the vector recursively
		sortTree(skeletonTable, sortedVec, 0);

		//sortedVec.push_back(skeletonTable[0]);
		//std::sort(skeletonTable.begin(), skeletonTable.end());
		// put this into the proto
		unsigned int numBones = sortedVec.size();
		skelData *pskelData = new skelData(numBones);
		assert(pskelData);

		for(size_t i = 0; i < numBones; i++)
		{
			pskelData->poSkelEntry[i].set(sortedVec[i].nodeIndex,
										  sortedVec[i].parentIndex,
										  &sortedVec[i].nodeName[0]);
		}

		//pskelData->Print("SkeData");
		skelData_proto mA_proto;
		pskelData->Serialize(mA_proto);

		// -------------------------------
		//  Write to file
		//--------------------------------

		File::Handle fh;
		File::Error err;

		// Create output name
		std::string sProtoFileType = "s";
		std::string sBaseName = pTargetName;

		std::string OutputFileName = sBaseName + "." + sProtoFileType + ".proto.azul";
		Trace::out("   --> %s\n", OutputFileName.c_str());
		err = File::Open(fh, OutputFileName.c_str(), File::Mode::WRITE);
		assert(err == File::Error::SUCCESS);

		std::string strOut;
		mA_proto.SerializeToString(&strOut);

		File::Write(fh, strOut.data(), strOut.length());
		assert(err == File::Error::SUCCESS);

		err = File::Close(fh);
		assert(err == File::Error::SUCCESS);

		// -------------------------------
		// Read and recreate model data
		// -------------------------------

		err = File::Open(fh, OutputFileName.c_str(), File::Mode::READ);
		assert(err == File::Error::SUCCESS);

		err = File::Seek(fh, File::Position::END, 0);
		assert(err == File::Error::SUCCESS);

		DWORD FileLength;
		err = File::Tell(fh, FileLength);
		assert(err == File::Error::SUCCESS);

		char *poNewBuff = new char[FileLength]();
		assert(poNewBuff);

		err = File::Seek(fh, File::Position::BEGIN, 0);
		assert(err == File::Error::SUCCESS);

		err = File::Read(fh, poNewBuff, FileLength);
		assert(err == File::Error::SUCCESS);

		err = File::Close(fh);
		assert(err == File::Error::SUCCESS);

		skelData_proto mB_proto;
		mB_proto.ParseFromArray(poNewBuff, (int)FileLength);

		skelData mB;
		mB.Deserialize(mB_proto);

		delete[] poNewBuff;
		delete pskelData;

	};

	void SKEL::CreateHierarchy(Model &model, const char *const pTargetName, int meshNum)
	{
		assert(pTargetName);


		// Create a skeleton and Fill it
		std::vector<size_t> log;
		log.reserve(model.nodes.size());

		for(size_t i = 0; i < model.nodes.size(); i++)
		{
			/*skeleton tmpSkeleton;*/
			log.push_back((size_t)-1);
		}

		size_t StartNodeIndex = (size_t)model.skins[meshNum].joints[0];
		size_t numJoints = (size_t)model.skins[meshNum].joints.size();
		size_t trueIndex = 0;
		for(size_t i = 0; i < log.size(); i++)
		{
			auto pNode = model.nodes[i];
			for(size_t z = (size_t)model.skins[meshNum].joints[0]; z < StartNodeIndex + numJoints; z++)
			{
				if(model.skins[meshNum].joints[z - StartNodeIndex] == i)
				{
					log[i] = z - StartNodeIndex;
					trueIndex++;
					z = StartNodeIndex + numJoints;
				}
				else
				{

				}
			}
		}



		this->skeletonVector.reserve(model.skins[meshNum].joints.size());
		for(size_t i = 0; i < model.skins[meshNum].joints.size(); i++)
		{
			skeleton tmpSkeleton;
			this->skeletonVector.push_back(tmpSkeleton);
		}

		// Walk through the nodes starting on the node they state

		for(size_t i = StartNodeIndex; i < log.size(); i++)
		{
			size_t isJointed = log[i];
			if(isJointed != -1)
			{
				auto pNode = model.nodes[i];
				skeletonVector[isJointed].nodeIndexInSkel = (int)isJointed;
				skeletonVector[isJointed].nodeIndex = (int)i;
				skeletonVector[isJointed].nodeName = pNode.name;

				for(size_t j = 0; j < pNode.children.size(); j++)
				{
					size_t fillingIndex = log[pNode.children[j]];
					if(fillingIndex != -1)
					{
						skeletonVector[fillingIndex].nodeIndexInSkel = (int)fillingIndex;
						skeletonVector[fillingIndex].nodeIndex = (int)pNode.children[j];
						skeletonVector[fillingIndex].nodeName = model.nodes[(size_t)pNode.children[j]].name;
						skeletonVector[fillingIndex].parentIndexInSkel = ((int)log[i]);
						skeletonVector[fillingIndex].parentIndex = i;
						skeletonVector[fillingIndex].parentName = pNode.name;
					}
					else
					{

					}
				}
			}
		}

		// Fill skeletonTable
		skeletonTable.reserve(skeletonVector.size());
		for(size_t i = 0; i < skeletonVector.size(); i++)
		{
			skeleton_table table;

			table.nodeIndex = skeletonVector[i].nodeIndexInSkel;
			table.parentIndex = skeletonVector[i].parentIndexInSkel;

			// Copy the string
			memset(table.nodeName, 0, skelEntry::SKELETON_NAME_SIZE);
			strncpy_s(table.nodeName,
					  skelEntry::SKELETON_NAME_SIZE,
					  skeletonVector[i].nodeName.c_str(),
					  skelEntry::SKELETON_NAME_SIZE - 1);

			//int startIndex = (int)model.skins[meshNum].joints[0];
			//table.nodeIndex = table.nodeIndex - startIndex;
			//table.parentIndex = table.parentIndex - startIndex;
			if(table.parentIndex < -1)
			{
				table.parentIndex = -1;
			}

			skeletonTable.push_back(table);

		}


		// ---------------------------------
		// Find max Depth
		// ---------------------------------

		int MaxDepth = -1;
		for(size_t i = 0; i < skeletonTable.size(); i++)
		{
			int start = (int)i;
			int curr = start;
			int count = 0;
			while(curr != -1)
			{
				//		Trace::out("curr: %d  %s\n",
				//			skeletonTable[(size_t)curr].nodeIndex,
				//			skeletonTable[(size_t)curr].nodeName);
				curr = (int)skeletonTable[(size_t)curr].parentIndex;
				count++;
			}

			if(count > MaxDepth)
			{
				MaxDepth = count;
			}
			//	Trace::out("curr: %d  depth: %d  max:%d\n", start, count, MaxDepth);
		}

		std::vector<std::vector<int>> TableA;
		for(size_t i = 0; i < skeletonTable.size(); i++)
		{
			std::vector<int> entry;

			int start = (int)i;
			int curr = start;
			int count = 0;
			while(curr != -1)
			{
				entry.push_back(skeletonTable[(size_t)curr].nodeIndex);

				curr = (int)skeletonTable[(size_t)curr].parentIndex;
				count++;
			}

			std::reverse(entry.begin(), entry.end());

			size_t extra = ((size_t)MaxDepth - entry.size());
			for(size_t j = 0; j < extra; j++)
			{
				// fill with -1 or anything
				//entry.push_back((int)skeletonTable.size());
				entry.push_back(-1);
			}

			TableA.push_back(entry);
		}

		//	Trace::out("\n");
		//	Trace::out("int JointTable[] = { \n");
		for(size_t i = 0; i < model.skins[0].joints.size(); i++)
		{
			//	Trace::out("%d: %d, \n", i, model.skins[0].joints[i]);
		}




		// -----------------------------------------------
		// Hierarchy Table
		// -----------------------------------------------

		for(size_t i = 0; i < TableA.size(); i++)
		{
			//	Trace::out("%2d: ", i);
			for(size_t j = 0; j < TableA[i].size(); j++)
			{
				//		Trace::out("%2d ", TableA[i][j]);
			}
			//		Trace::out("\n");
		}


		// -----------------------------------------------
		// put into a proto
		// -----------------------------------------------

		HierarchyData hData(TableA.size(), (unsigned int)MaxDepth);
		size_t k = 0;
		for(size_t i = 0; i < TableA.size(); i++)
		{
			for(size_t j = 0; j < TableA[i].size(); j++)
			{
				hData.poData[k++] = (unsigned int)TableA[i][j];
			}
		}

		//	hData.Print("proto");


		HierarchyData_proto hA_proto;
		hData.Serialize(hA_proto);


		HierarchyData hB;
		hB.Deserialize(hA_proto);
		//	hB.Print("hb");


			// -------------------------------
			//  Write to file
			//--------------------------------

		File::Handle fh;
		File::Error err;

		// Create output name
		std::string sProtoFileType = "h";
		std::string sBaseName = pTargetName;

		std::string OutputFileName = sBaseName + "." + sProtoFileType + ".proto.azul";
		Trace::out(" --> %s\n", OutputFileName.c_str());
		err = File::Open(fh, OutputFileName.c_str(), File::Mode::WRITE);
		assert(err == File::Error::SUCCESS);

		std::string strOut;
		hA_proto.SerializeToString(&strOut);

		File::Write(fh, strOut.data(), strOut.length());
		assert(err == File::Error::SUCCESS);

		err = File::Close(fh);
		assert(err == File::Error::SUCCESS);

		// -------------------------------
		// Read and recreate model data
		// -------------------------------

		err = File::Open(fh, OutputFileName.c_str(), File::Mode::READ);
		assert(err == File::Error::SUCCESS);

		err = File::Seek(fh, File::Position::END, 0);
		assert(err == File::Error::SUCCESS);

		DWORD FileLength;
		err = File::Tell(fh, FileLength);
		assert(err == File::Error::SUCCESS);

		char *poNewBuff = new char[FileLength]();
		assert(poNewBuff);

		err = File::Seek(fh, File::Position::BEGIN, 0);
		assert(err == File::Error::SUCCESS);

		err = File::Read(fh, poNewBuff, FileLength);
		assert(err == File::Error::SUCCESS);

		err = File::Close(fh);
		assert(err == File::Error::SUCCESS);


		delete[] poNewBuff;


	};


}

// --- End of File ---
