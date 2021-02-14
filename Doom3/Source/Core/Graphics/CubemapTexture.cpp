#include "CubemapTexture.h"

using namespace doom::graphics;

CubemapTexture::CubemapTexture(eTextureType textureType, eTargetTexture target, eInternalFormat internalFormat, unsigned int width, eDataFormat format, eDataType type, const void* data)
	: Texture{ textureType, eBindTarget::TEXTURE_CUBE_MAP, target, internalFormat, width, format, type, data }
{
	this->TexImage1D(0, data);
}

CubemapTexture::CubemapTexture(eTextureType textureType, eTargetTexture target, eInternalFormat internalFormat, unsigned int width, unsigned int height, eDataFormat format, eDataType type, const void* data)
	: Texture{ textureType, eBindTarget::TEXTURE_CUBE_MAP, target, internalFormat, width, height, format, type, data }
{
	this->TexImage2D(0, data);
}
