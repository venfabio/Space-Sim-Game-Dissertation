#include "TextHandler.h"

TextHandler::TextHandler()
{
}


TextHandler::~TextHandler()
{
}

IFW1FontWrapper* TextHandler::GetWrapper(ID3D11Device* dev)
{
	FW1CreateFactory(FW1_VERSION, &_factory);
	_factory->CreateFontWrapper(dev, L"ARIAL", &_wrapper);
	_factory->Release();
	return _wrapper;
}
