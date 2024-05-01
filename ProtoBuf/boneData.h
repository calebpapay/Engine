
#ifndef BONE_DATA_H
#define BONE_DATA_H

#include "MathEngine.h"
#include "boneData.pb.h"

#include "QuatData.h"
#include "Vec3Data.h"

namespace Azul
{

	class boneData
	{
	public:
		boneData();
		boneData(const boneData &) = default;
		boneData & operator = (const boneData &) = default;
		~boneData();

		boneData(Vec3 &s, Quat &q, Vec3 &t);
		void set(Vec3 &s, Quat &q, Vec3 &t);

		// Serialization 
		void Serialize(boneData_proto &out) const;
		void Deserialize(const boneData_proto &in);

		void Print(const char *const pName) const;

	public:
		Vec3Data S;
		QuatData Q;
		Vec3Data T;
	};

}

#endif

// --- End of File ---
