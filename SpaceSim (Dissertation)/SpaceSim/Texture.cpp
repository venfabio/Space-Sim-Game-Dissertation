#include "Texture.h"

Texture::Texture()
{
}


Texture::~Texture()
{
}

// x86
void Texture::Initialize(ID3D11Device* dev, LPCWSTR name)
{
	D3DX11CreateShaderResourceViewFromFile(dev, name, NULL, NULL, &_texture, NULL);
}


// x64
/*
void Texture::Initialize(ID3D11Device* dev, LPCSTR name)
{
	D3DX11CreateShaderResourceViewFromFile(dev, name, NULL, NULL, &_texture, NULL);
}
*/

void Texture::Shutdown()
{
	if (_texture)
	{
		_texture->Release();
	}
}