//----------------------------------------------------------------------------
//2024. Caleb Papay
//----------------------------------------------------------------------------

#include "FontConverter.h"
//#include "GLTF.h"
#include "File.h"
#include "FontData.h"
#include "FontEntry.h"
#include "pugixml.hpp"
using namespace Azul;








//-----------------------------------------------------------------------------
// Allocate memory and load targa bits. Returns pointer to new buffer,
// height, and width of texture, and the OpenGL format of data.
// Call free() on buffer when finished!
// This only works on pretty vanilla targas... 8, 24, or 32 bit color
// only, no palettes, no RLE encoding.
//-----------------------------------------------------------------------------
namespace Azul
{
	void ReadXMLData(const char *pName)
	{
		assert(pName);
		Trace::out("ConvertXML(%s): \n", pName);

		char pFileName[128];
		sprintf_s(pFileName, 128, "%s.xml", pName);


		//Trace::out("\n-----------\n\n");

			//FontEntry fontEntryA;
			//fontEntryA.set(3, 4, 5, 6, 7);
			//fontEntryA.Print("FontEntryA");

			//FontEntry_proto fontEntryA_proto;
			//fontEntryA.Serialize(fontEntryA_proto);

			//FontEntry fontEntryB;
			//fontEntryB.Deserialize(fontEntryA_proto);
			//fontEntryB.Print("fontEntryB");

	//	Trace::out("\n-----------\n\n");

		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(pFileName);
		assert(result);

		//Trace::out("Load result: %s \n", result.description());
		//Trace::out("  file name: %s \n", (doc.child("fontMetrics").attribute("file").value()));

		//Trace::out("\n-----------\n\n");

		unsigned int count = 0;
		for(pugi::xml_node node = doc.child("fontMetrics").child("character"); node; node = node.next_sibling("character"))
		{
			count++;
		}

		FontData FontDataA(count);

		int i = -1;
		for(pugi::xml_node node = doc.child("fontMetrics").child("character"); node; node = node.next_sibling("character"))
		{
			unsigned int key = node.attribute("key").as_uint();
			assert(key > 31);
			assert(key < 128);

			float x = node.child("x").text().as_float();
			assert(x > -1);

			float y = node.child("y").text().as_float();
			assert(y > -1);

			float width = node.child("width").text().as_float();
			assert(width > -1);

			float height = node.child("height").text().as_float();
			assert(height > -1);

			/*Trace::out("key: %d  (x,y,w,h) %f %f %f %f \n",
					   key, x, y, width, height);*/

			i++;
			FontDataA.poFontEntry[i].set(key, x, y, width, height);
		}

		assert((unsigned int)(i + 1) == count);

			//FontDataA.Print("FontDataA");
		FontData_proto fontDataA_proto;
		FontDataA.Serialize(fontDataA_proto);

		FontData FontDataB;

		FontDataB.Deserialize(fontDataA_proto);
		//FontDataB.Print("FontDataB");

		/* -------------------------------
		  Write to file
		--------------------------------*/

		File::Handle fh;
		File::Error err;

		const char *pProtoFileType = ".xml";

		// Create output name
		std::string BaseName(pName);
		std::string OutputFileName = BaseName + pProtoFileType + ".proto.azul";

		Trace::out("   --> %s\n", OutputFileName.c_str());
		err = File::Open(fh, OutputFileName.c_str(), File::Mode::WRITE);
		assert(err == File::Error::SUCCESS);

		std::string strOut;
		fontDataA_proto.SerializeToString(&strOut);

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

	/*	Trace::out("--------------\n");
		Trace::out("--------------\n");
		Trace::out("--------------\n");

		FontData_proto mB_proto;
		mB_proto.ParseFromArray(poNewBuff,FileLength);

		FontData FontDataB;
		FontDataB.Deserialize(fontDataA_proto);
		FontDataB.Print("FontDataB");*/

		delete[] poNewBuff;
	}
}



// --- End of File ---
