//2024. Caleb Papay

#include "TexNodeMan.h"
#include "Image.h"
#include "Rect.h"
#include "StringThis.h"

namespace Azul
{
	// public methods: -------------------------------------------------------------

	Image::Image()
	{
		this->imageName = Image::Name::Not_Initialized;
		this->imageRect.clear();
		this->pText = nullptr;
	}

	Image::~Image()
	{
		
	}


	Image::Image(Image::Name _imageName, TextureObject *_pText, Rect _rect)
	{
		this->imageName = _imageName;
		this->pText = _pText;
		assert(pText);
		this->imageRect = _rect;
	}

	Image::Image(Image::Name _imageName, TextureObject::Name _textName, Rect _rect)
	{
		this->imageName = _imageName;
		this->pText = TexNodeMan::Find(_textName);
		assert(pText);
		this->imageRect = _rect;
	}

	void Image::Set(Image::Name _imageName, TextureObject *_pText, Rect _rect)
	{
		this->imageName = _imageName;
		assert(_pText);
		this->pText = _pText;
		this->imageRect = _rect;
	}

	void Image::Set(Image::Name _imageName, TextureObject::Name _textName, Rect _rect)
	{
		this->imageName = _imageName;
		this->pText = TexNodeMan::Find(_textName);
		assert(pText);
		this->imageRect = _rect;
	}

	void Image::Swap(TextureObject::Name _textName, Rect _rect)
	{
		this->pText = TexNodeMan::Find(_textName);
		assert(pText);
		this->imageRect = _rect;
	}

	void Image::Swap(TextureObject *_pTexture, Rect _rect)
	{
		assert(_pTexture);
		this->pText = _pTexture;
		this->imageRect = _rect;
	}
	bool Image::Compare(DLink *pTarget)
	{
		// This is used in ManBase.Find() 
		assert(pTarget != nullptr);

		Image *pDataB = (Image *)pTarget;

		bool status = false;

		if(this->imageName == pDataB->imageName)
		{
			status = true;
		}

		return status;
	}

	void Image::Dump()
	{
		Trace::out("      Image(%p)\n", this);

		// Data:
		//Trace::out("      Name: %s \n", StringMe(this->name));
		//Trace::out("         x: %d \n", this->x);

		DLink::Dump();
	}

	void Image::Wash()
	{
		this->imageName = Image::Name::Not_Initialized;
		this->imageRect.clear();
		this->pText = nullptr;
	}
}

//--- End of File ---