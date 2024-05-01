//2024. Caleb Papay

#include "GlyphProto.h"
#include "File.h"
#include "FontData.h"
#include "TextureObject.h"
#include "GlyphMan.h"

namespace Azul
{
	float squeezeHeightFromBottom = 2.0f;
	float squeezeWidthFromRight = 2.0f;
	float shiftRectRight = 1.0f;
	float shiftRectUp = 1.0f;
	//float shiftRectUp = 0.0f;

	GlyphProto::GlyphProto(const char *const pMeshFileName, Glyph::Name name, TextureObject::Name texName)
	{
		// future proofing it for a file
		assert(pMeshFileName);
		AZUL_UNUSED_VAR(pMeshFileName);

		// ----------------------------------------------
		// READ the data from the file ONLY
		// ----------------------------------------------

		// File stuff
		File::Handle fh;
		File::Error  ferror;

		ferror = File::Open(fh, pMeshFileName, File::Mode::READ);
		assert(ferror == File::Error::SUCCESS);

		// Get the size
		ferror = File::Seek(fh, File::Position::END, 0);
		assert(ferror == File::Error::SUCCESS);

		DWORD length;
		ferror = File::Tell(fh, length);
		assert(ferror == File::Error::SUCCESS);

		ferror = File::Seek(fh, File::Position::BEGIN, 0);
		assert(ferror == File::Error::SUCCESS);

		char *poBuff = new char[length];
		assert(poBuff);

		ferror = File::Read(fh, poBuff, length);
		assert(ferror == File::Error::SUCCESS);

		ferror = File::Close(fh);
		assert(ferror == File::Error::SUCCESS);

		// Now the raw data is poBUff
		// deserialize the data --> mB
		std::string strIn(poBuff, length);
		FontData_proto mB_proto;

		mB_proto.ParseFromString(strIn);

		FontData mB;
		mB.Deserialize(mB_proto);
		delete[] poBuff;
		FontEntry *pFontEntry = mB.poFontEntry;

		for(unsigned int i = 0; i < mB.numKeys; i++)
		{
			//FontEntry *pFontEntry = mB.poFontEntry;
			float posX = pFontEntry[i].x + shiftRectRight;
			float posY = pFontEntry[i].y + shiftRectUp;
			float width = pFontEntry[i].width - squeezeWidthFromRight;
			float height = pFontEntry[i].height - squeezeHeightFromBottom;

			Rect tmpRect(posX, posY, width, height);
			GlyphMan::Add(name, pFontEntry[i].key, texName, tmpRect);

		}



	}

}

//--- End of File ---
