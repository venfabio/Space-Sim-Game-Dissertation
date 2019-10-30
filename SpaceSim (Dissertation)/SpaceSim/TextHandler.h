#pragma once

#include <FW1FontWrapper.h>

class TextHandler
{
private :
	IFW1Factory*		_factory;
	IFW1FontWrapper*	_wrapper;
	LPCWSTR				_fontFamily;

public:
	TextHandler();
	~TextHandler();

	IFW1FontWrapper* GetWrapper(ID3D11Device* dev);
};

