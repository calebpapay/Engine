//----------------------------------------------------------------------------
//2024. Caleb Papay
//----------------------------------------------------------------------------

#include "animConverter.h"
#include "GLTF.h"
#include "animData.h"
#include "File.h"

using namespace tinygltf;

namespace Azul
{

	void ANIM::CreateAnim(Model &model, const char *const pTargetName, int meshNum)
	{
		// Create a default frame

		// YES its too big... reduce at the end
		size_t numBones = model.nodes.size();

		// Default Bone
		Bone defaultBone;
		defaultBone.T = Vec3(0.0f, 0.0f, 0.0f);
		defaultBone.Q = Quat(0.0f, 0.0f, 0.0f, 1.0f);
		defaultBone.S = Vec3(1.0f, 1.0f, 1.0f);

		// Default Frame
		Frame defaultFrame;
		defaultFrame.frameIndex = -1;
		defaultFrame.time = -1.0f;
		defaultFrame.vectorBone.reserve(numBones);
		for(size_t i = 0; i < numBones; i++)
		{
			defaultFrame.vectorBone.push_back(defaultBone);
		}

		// Correct for Stationary data:
		for(size_t i = 0; i < model.nodes.size(); i++)
		{
			// MAGIC---> use reference
			auto Node = model.nodes[i];
			defaultFrame.vectorBone[i].T = Vec3((float)Node.translation[0], (float)Node.translation[1], (float)Node.translation[2]);
			defaultFrame.vectorBone[i].Q = Quat((float)Node.rotation[0], (float)Node.rotation[1], (float)Node.rotation[2], (float)Node.rotation[3]);
			defaultFrame.vectorBone[i].S = Vec3((float)Node.scale[0], (float)Node.scale[1], (float)Node.scale[2]);
		}

		// At this point we now have a default frame filled with stationary data
		// Next let's create animation clip

		// number of frames of data?
		// it should be the same size as time elements
		size_t numAnimFrames = model.accessors[0].count;

		this->clip.vectorClip.reserve(numAnimFrames);
		// initially copy the default frame with stationary data
		for(size_t i = 0; i < numAnimFrames; i++)
		{
			this->clip.vectorClip.push_back(defaultFrame);
		}


		// At this point we have the whole animation loaded with stationary
		// replace with the animated fields
		//Trace::out("\n");

		for(size_t i = 0; i < numAnimFrames; i++)
		{
			// MAGIC---> use reference
			auto &tmpClip = this->clip.vectorClip[i];

			tmpClip.frameIndex = (int)i;
			tmpClip.time = this->GetTime(model, 0, i);

			// overwrite the animation data into bone vector
			// iterate across the channels
			for(size_t k = 0; k < model.animations[0].channels.size(); k++)
			{
				size_t targetIndex = (size_t)model.animations[0].channels[k].target_node;
				if(model.animations[0].channels[k].target_path == "translation")
				{
					//	Trace::out("channel:%d n:%d trans\n", k,targetIndex);
						// Remember 0 is the time...so the channels are +1 index
					size_t accessorIndex = k + 1;
					Vec3 vTmp = this->GetTrans(model, accessorIndex, i);
					tmpClip.vectorBone[targetIndex].T = vTmp;

				}
				else if(model.animations[0].channels[k].target_path == "rotation")
				{
					//	Trace::out("channel:%d n:%d rotation\n", k, targetIndex);
						// Remember 0 is the time...so the channels are +1 index
					size_t accessorIndex = k + 1;
					Quat qTmp = this->GetQuat(model, accessorIndex, i);
					tmpClip.vectorBone[targetIndex].Q = qTmp;
				}
				else if(model.animations[0].channels[k].target_path == "scale")
				{
					//	Trace::out("channel:%d n:%d scale\n", k, targetIndex);
						// Remember 0 is the time...so the channels are +1 index

					assert(false);
					size_t accessorIndex = k + 1;
					Vec3 vTmp = this->GetScale(model, accessorIndex, i);
					tmpClip.vectorBone[targetIndex].S = vTmp;
				}
				else
				{
					assert(false);
				}
			}

		}

		animData clipA(this->clip.vectorClip.size(), model.skins[meshNum].joints.size());




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

			//check if node is a JOINT
			//if so, log its JOINT number
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




		// for every FrameBucket
		for(size_t i = 0; i < this->clip.vectorClip.size(); i++)
		{
			auto tmpClip = this->clip.vectorClip[i];
			
				clipA.poFrameBucketEntry[i].keyFrame = (unsigned int)tmpClip.frameIndex;
				clipA.poFrameBucketEntry[i].keyTime = tmpClip.time;
				clipA.poFrameBucketEntry[i].keyTimeIndex = (int)i;

				// for every bone in a specific frame bucket
				for(size_t p = 0; p < model.skins[meshNum].joints.size(); p++)
				{
					size_t k = model.skins[meshNum].joints[p];
					Bone tmpBone = tmpClip.vectorBone[k];

					Vec3 s(tmpBone.S[x], tmpBone.S[y], tmpBone.S[z]);
					Quat q(tmpBone.Q[x], tmpBone.Q[y], tmpBone.Q[z], tmpBone.Q[w]);
					Vec3 t(tmpBone.T[x], tmpBone.T[y], tmpBone.T[z]);

					size_t correctedIndex = log[k];
					//size_t correctedIndex = k - model.skins[0].joints[0];
					if(correctedIndex != -1)
					{
						//size_t correctedIndex = k - model.skins[0].joints[0];
						clipA.poFrameBucketEntry[i].poBoneEntry[correctedIndex].set(s, q, t);
					}
					else
					{
						assert(false);
					}
				}
			
		}


		//.Print("clipA");
		animData_proto clipA_proto;
		clipA.Serialize(clipA_proto);

		// -------------------------------
		//  Write to file
		//--------------------------------

		File::Handle fh;
		File::Error err;

		const char *pProtoFileType = ".a";

		// Create output name
		std::string BaseName(pTargetName);
		std::string OutputFileName = BaseName + pProtoFileType + ".proto.azul";
		Trace::out("  --> %s\n", OutputFileName.c_str());
		err = File::Open(fh, OutputFileName.c_str(), File::Mode::WRITE);
		assert(err == File::Error::SUCCESS);

		std::string strOut;
		clipA_proto.SerializeToString(&strOut);

		File::Write(fh, strOut.data(), strOut.length());
		assert(err == File::Error::SUCCESS);

		err = File::Close(fh);
		assert(err == File::Error::SUCCESS);

	}

	float ANIM::GetTime(Model &model, size_t accessorIndex, size_t frameIndex)
	{
		//Trace::out("Time: \n");
		unsigned char *pBuff = (unsigned char *)&model.buffers[0].data[0];
		auto TimeAccessor = model.accessors[accessorIndex];
		auto TimeBuffView = model.bufferViews[(size_t)TimeAccessor.bufferView];

		pBuff = pBuff + TimeBuffView.byteOffset;

		assert(TimeAccessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
		assert(TimeAccessor.type == TINYGLTF_TYPE_SCALAR);

		float *pFloatData = (float *)pBuff;

		float val = pFloatData[frameIndex];

		// sanity check
		size_t len = ((size_t)&pFloatData[frameIndex] - (size_t)pBuff);
		assert(len <= TimeBuffView.byteLength);

		return val;
	}

	Vec3 ANIM::GetTrans(Model &model, size_t accessorIndex, size_t frameIndex)
	{
		//Trace::out("Trans 4: \n");
		unsigned char *pBuff = (unsigned char *)&model.buffers[0].data[0];
		auto TransAccessor = model.accessors[accessorIndex];
		auto TransBuffView = model.bufferViews[(size_t)TransAccessor.bufferView];

		pBuff = pBuff + TransBuffView.byteOffset;
		assert(TransAccessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
		assert(TransAccessor.type == TINYGLTF_TYPE_VEC3);
		Vec3f *pVect3 = (Vec3f *)pBuff;

		Vec3 vOut(pVect3[frameIndex].x, pVect3[frameIndex].y, pVect3[frameIndex].z);

		// sanity check
		size_t len = ((size_t)&pVect3[frameIndex] - (size_t)pBuff);
		assert(len <= TransBuffView.byteLength);

		return vOut;
	}

	Vec3 ANIM::GetScale(Model &model, size_t accessorIndex, size_t frameIndex)
	{
		//Trace::out("Trans 4: \n");
		unsigned char *pBuff = (unsigned char *)&model.buffers[0].data[0];
		auto ScaleAccessor = model.accessors[accessorIndex];
		auto ScaleBuffView = model.bufferViews[(size_t)ScaleAccessor.bufferView];

		pBuff = pBuff + ScaleBuffView.byteOffset;
		assert(ScaleAccessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
		assert(ScaleAccessor.type == TINYGLTF_TYPE_VEC3);
		Vec3f *pVect3 = (Vec3f *)pBuff;

		Vec3 vOut(pVect3[frameIndex].x, pVect3[frameIndex].y, pVect3[frameIndex].z);

		// sanity check
		size_t len = ((size_t)&pVect3[frameIndex] - (size_t)pBuff);
		assert(len <= ScaleBuffView.byteLength);

		return vOut;
	}

	Quat ANIM::GetQuat(Model &model, size_t accessorIndex, size_t frameIndex)
	{
		//	Trace::out("Quat 4: \n");
		unsigned char *pBuff = (unsigned char *)&model.buffers[0].data[0];
		auto QuatAAccessor = model.accessors[accessorIndex];
		auto QuatABuffView = model.bufferViews[(size_t)QuatAAccessor.bufferView];

		pBuff = pBuff + QuatABuffView.byteOffset;
		assert(QuatAAccessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
		assert(QuatAAccessor.type == TINYGLTF_TYPE_VEC4);
		Vec4f *pVect4 = (Vec4f *)pBuff;

		Quat qOut(pVect4[frameIndex].x, pVect4[frameIndex].y, pVect4[frameIndex].z, pVect4[frameIndex].w);

		// sanity check
		size_t len = ((size_t)&pVect4[frameIndex] - (size_t)pBuff);
		assert(len <= QuatABuffView.byteLength);

		return qOut;
	}

}

// --- End of File ---
