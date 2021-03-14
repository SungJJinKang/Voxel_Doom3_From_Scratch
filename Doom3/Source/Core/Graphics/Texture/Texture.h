#pragma once

#include <vector>
#include <string>

#include "../Graphics_Core.h"
#include "../OverlapBindChecker.h"
#include <ZeroResetMoveContainer.h>
#include "TextureFormat.h"

#include <magic_enum.hpp>

namespace DirectX
{
	struct Image;
	class ScratchImage;
}


namespace doom
{
	namespace graphics
	{
		/// <summary>
		/// reference : https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
		/// </summary>
		class Texture
		{
			friend class Graphics_Server;

		public:

			enum class eTextureType : unsigned int {
				NONE = 0,
				DIFFUSE = 1,
				SPECULAR = 2,
				AMBIENT = 3,
				EMISSIVE = 4,
				HEIGHT = 5,
				NORMALS = 6,
				SHININESS = 7,
				OPACITY = 8,
				DISPLACEMENT = 9,
				LIGHTMAP = 10,
				REFLECTION = 11,
				BASE_COLOR = 12,
				NORMAL_CAMERA = 13,
				EMISSION_COLOR = 14,
				METALNESS = 15,
				DIFFUSE_ROUGHNESS = 16,
				AMBIENT_OCCLUSION = 17,
				UNKNOWN = 18,
			};

			enum class eBindTarget : unsigned int
			{
				TEXTURE_1D = GL_TEXTURE_1D,
				TEXTURE_2D = GL_TEXTURE_2D,
				TEXTURE_3D = GL_TEXTURE_3D,
				TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
				TEXTURE_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
				TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE,
				TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
				TEXTURE_CUBE_MAP_ARRAY = GL_TEXTURE_CUBE_MAP_ARRAY,
				TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
				TEXTURE_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE,
				TEXTURE_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
			};
			static constexpr eBindTarget DEFAULT_BIND_TARGET = eBindTarget::TEXTURE_2D;
			
			enum class eTargetTexture : unsigned int
			{
				TEXTURE_1D = GL_TEXTURE_1D,
				PROXY_TEXTURE_1D = GL_PROXY_TEXTURE_1D,
				TEXTURE_2D = GL_TEXTURE_2D,
				PROXY_TEXTURE_2D = GL_PROXY_TEXTURE_2D,
				TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
				PROXY_TEXTURE_1D_ARRAY = GL_PROXY_TEXTURE_1D_ARRAY,
				TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE,
				PROXY_TEXTURE_RECTANGLE = GL_PROXY_TEXTURE_RECTANGLE,
				TEXTURE_CUBE_MAP_POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
				TEXTURE_CUBE_MAP_NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
				TEXTURE_CUBE_MAP_POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
				TEXTURE_CUBE_MAP_NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
				TEXTURE_CUBE_MAP_POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
				TEXTURE_CUBE_MAP_NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
				PROXY_TEXTURE_CUBE_MAP = GL_PROXY_TEXTURE_CUBE_MAP,
				TEXTURE_3D = GL_TEXTURE_3D
			};
			static constexpr eTargetTexture DEFAULT_TARGET_TEXTURE = eTargetTexture::TEXTURE_2D;



			static constexpr eTextureInternalFormat DEFAULT_INTERNAL_FORMAT = eTextureInternalFormat::RGBA;

			
			static constexpr eTextureComponentFormat DEFAULT_DATA_FORMAT = eTextureComponentFormat::RGBA;

			enum class eDataType : unsigned int
			{
				UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
				BYTE = GL_BYTE,
				UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
				SHORT = GL_SHORT,
				UNSIGNED_INT = GL_UNSIGNED_INT,
				INT = GL_INT,
				HALF_FLOAT = GL_HALF_FLOAT,
				FLOAT = GL_FLOAT,
				UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
				UNSIGNED_BYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV,
				UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
				UNSIGNED_SHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV,
				UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
				UNSIGNED_SHORT_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV,
				UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
				UNSIGNED_SHORT_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV,
				UNSIGNED_INT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
				UNSIGNED_INT_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV,
				UNSIGNED_INT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
				UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV,
				UNSIGNED_INT_24_8 = GL_UNSIGNED_INT_24_8,
				FLOAT_32_UNSIGNED_INT_24_8_REV = GL_FLOAT_32_UNSIGNED_INT_24_8_REV
			};
			static constexpr eDataType DEFAULT_DATA_TYPE = eDataType::UNSIGNED_BYTE;

			enum class eTextureParameterType : unsigned int
			{
				DEPTH_STENCIL_TEXTURE_MODE = GL_DEPTH_STENCIL_TEXTURE_MODE,
				TEXTURE_BASE_LEVEL = GL_TEXTURE_BASE_LEVEL,
				TEXTURE_COMPARE_FUNC = GL_TEXTURE_COMPARE_FUNC,
				TEXTURE_COMPARE_MODE = GL_TEXTURE_COMPARE_MODE,
				TEXTURE_LOD_BIAS = GL_TEXTURE_LOD_BIAS,
				TEXTURE_MIN_FILTER = GL_TEXTURE_MIN_FILTER,
				TEXTURE_MAG_FILTER = GL_TEXTURE_MAG_FILTER,
				TEXTURE_MIN_LOD = GL_TEXTURE_MIN_LOD,
				TEXTURE_MAX_LOD = GL_TEXTURE_MAX_LOD,
				TEXTURE_MAX_LEVEL = GL_TEXTURE_MAX_LEVEL,
				TEXTURE_SWIZZLE_R = GL_TEXTURE_SWIZZLE_R,
				TEXTURE_SWIZZLE_G = GL_TEXTURE_SWIZZLE_G,
				TEXTURE_SWIZZLE_B = GL_TEXTURE_SWIZZLE_B,
				TEXTURE_SWIZZLE_A = GL_TEXTURE_SWIZZLE_A,
				TEXTURE_WRAP_S = GL_TEXTURE_WRAP_S,
				TEXTURE_WRAP_T = GL_TEXTURE_WRAP_T,
				TEXTURE_WRAP_R = GL_TEXTURE_WRAP_R
			};

			enum class eTextureParameterValue : unsigned int
			{
				NEAREST = GL_NEAREST,
				LINEAR = GL_LINEAR,
				NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
				LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
				NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
				LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
				CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
				CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
				MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
				REPEAT = GL_REPEAT,
				MIRROR_CLAMP_TO_EDGE = GL_MIRROR_CLAMP_TO_EDGE,
			};

			enum class eWrapMode : unsigned int
			{
				CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
				CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
				MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
				REPEAT = GL_REPEAT,
				MIRROR_CLAMP_TO_EDGE = GL_MIRROR_CLAMP_TO_EDGE,
			};

			enum class eFilterMode : unsigned int
			{
				NEAREST = GL_NEAREST,
				LINEAR = GL_LINEAR,
				NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
				LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
				NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
				LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
			};

		private:

			/// <summary>
			/// some times primitive ways works well
			/// </summary>
			/// <param name="bindTarget"></param>
			/// <returns></returns>
			static const char* GetBindTargetTag(eBindTarget bindTarget)
			{
				switch (bindTarget)
				{
				case eBindTarget::TEXTURE_1D:
					return "TEXTURE_1D";
				case eBindTarget::TEXTURE_2D:
					return "TEXTURE_2D";
				case eBindTarget::TEXTURE_3D:
					return "TEXTURE_3D";
				case eBindTarget::TEXTURE_1D_ARRAY:
					return "TEXTURE_1D_ARRAY";
				case eBindTarget::TEXTURE_2D_ARRAY:
					return "TEXTURE_2D_ARRAY";
				case eBindTarget::TEXTURE_RECTANGLE:
					return "TEXTURE_RECTANGLE";
				case eBindTarget::TEXTURE_CUBE_MAP:
					return "TEXTURE_CUBE_MAP";
				case eBindTarget::TEXTURE_CUBE_MAP_ARRAY:
					return "TEXTURE_CUBE_MAP_ARRAY";
				case eBindTarget::TEXTURE_BUFFER:
					return "TEXTURE_BUFFER";
				case eBindTarget::TEXTURE_2D_MULTISAMPLE:
					return "TEXTURE_2D_MULTISAMPLE";
				case eBindTarget::TEXTURE_2D_MULTISAMPLE_ARRAY:
					return "TEXTURE_2D_MULTISAMPLE_ARRAY";
				default:
					NEVER_HAPPEN;
				}
			}

			static inline std::vector<std::string> TEXTURE_UNIT_TAG{};
			static inline const char* ACTIVE_TEXTURE_TAG{ "ActiveTexture" };
			static void InitTextureUnitTag(int availiableTextureUnitCount);

			eWrapMode mWrapS;
			eWrapMode mWrapT;
			eWrapMode mWrapR;


		protected:

			BufferID mBufferID{};

			Texture() = delete;
			Texture(const Texture&) = delete;
			Texture& operator=(const Texture&) noexcept = delete;

			Texture(Texture&&) noexcept = default;
			Texture& operator=(Texture&&) noexcept = default;

			/// <summary>
			/// for 1d texture
			/// </summary>
			Texture(eTextureType textureType, eBindTarget bindTarget,
				eTargetTexture targetTexture, eTextureInternalFormat internalFormat, eTextureCompressedInternalFormat compressedInternalFormat, unsigned int width, eTextureComponentFormat format, eDataType type);

			/// <summary>
			/// for 2d texture
			/// </summary>
			/// <param name="textureType"></param>
			/// <param name="bindTarget"></param>
			/// <param name="target"></param>
			/// <param name="internalFormat"></param>
			/// <param name="width"></param>
			/// <param name="height"></param>
			/// <param name="format"></param>
			/// <param name="type"></param>
			/// <param name="data"></param>
			Texture(eTextureType textureType, eBindTarget bindTarget,
				eTargetTexture targetTexture, eTextureInternalFormat internalFormat, eTextureCompressedInternalFormat compressedInternalFormat, unsigned int width, unsigned int height, eTextureComponentFormat format, eDataType type);

			virtual ~Texture();
			virtual void OnEndContructor();

		public:

			

			const eTextureType mTextureType;
			const eBindTarget mBindTarget;

			const eTargetTexture mTarget;
			const eTextureInternalFormat mInternalFormat;
			const eTextureCompressedInternalFormat mCompressedInternalFormat;
			const unsigned int mWidth;
			const unsigned int mHeight;
			const eTextureComponentFormat mDataFormat;
			const eDataType mDataType;

			

			inline void BindTexture() noexcept
			{
				if (OverlapBindChecker::GetBoundID(GetBindTargetTag(this->mBindTarget)) != this->mBufferID)
				{
					D_CHECK_OVERLAP_BIND_AND_SAVE_BIND(GetBindTargetTag(this->mBindTarget), this->mBufferID);
					glBindTexture(static_cast<unsigned int>(this->mBindTarget), this->mBufferID);
				}
			}
			inline void ActiveTexture(unsigned int bindingPoint) noexcept
			{
				if (OverlapBindChecker::GetBoundID(ACTIVE_TEXTURE_TAG) != bindingPoint)
				{
					D_CHECK_OVERLAP_BIND_AND_SAVE_BIND(ACTIVE_TEXTURE_TAG, bindingPoint);
					glActiveTexture(GL_TEXTURE0 + bindingPoint);
				}
			}


			inline void UnBindTexture() noexcept
			{
				if (OverlapBindChecker::GetBoundID(GetBindTargetTag(this->mBindTarget)) != 0)
				{
					D_CHECK_OVERLAP_BIND_AND_SAVE_BIND(GetBindTargetTag(this->mBindTarget), 0);
					glBindTexture(static_cast<unsigned int>(this->mBindTarget), 0);
				}
			}

			inline void BindTextureWithUnit(unsigned int bindingPoint)
			{
				if (OverlapBindChecker::GetBoundID(TEXTURE_UNIT_TAG[bindingPoint].data()) != this->mBufferID)
				{
					D_CHECK_OVERLAP_BIND_AND_SAVE_BIND(TEXTURE_UNIT_TAG[bindingPoint].data(), this->mBufferID);
					glBindTextureUnit(bindingPoint, this->mBufferID);
				}
				//glActiveTexture(GL_TEXTURE0 + bindingPoint);
				//glBindTexture(GL_TEXTURE_2D, this->mBufferID);
			}

			virtual inline void TexImage1D(
				int level, const void* data
			) = 0;

			
			/// <summary>
			/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
			/// </summary>
			/// <param name="level"></param>
			/// <param name="data"></param>
			virtual inline void TexImage2D(
				int level, const void* data
			) = 0;

			unsigned int GetID();

			void SetWrapMode(eWrapMode wrapMode, bool bBind);
			void SetFilterMin(eFilterMode filterMode, bool bBind);
			void SetFilterMax(eFilterMode filterMode, bool bBind);

			eWrapMode GetWrapModeS();
			eWrapMode GetWrapModeT();
			eWrapMode GetWrapModeR();

			inline void TexParameterf(eBindTarget target, eTextureParameterType pname, eTextureParameterValue param) noexcept
			{
				glTexParameterf(static_cast<unsigned int>(target), static_cast<unsigned int>(pname), static_cast<float>(param));
			}
			inline void TexParameteri(eBindTarget target, eTextureParameterType pname, eTextureParameterValue param) noexcept
			{
				glTexParameteri(static_cast<unsigned int>(target), static_cast<unsigned int>(pname), static_cast<int>(param));
			}
			inline void TexParameterf(eBindTarget target, eTextureParameterType pname, float param) noexcept
			{
				glTexParameterf(static_cast<unsigned int>(target), static_cast<unsigned int>(pname), param);
			}
			inline void TexParameteri(eBindTarget target, eTextureParameterType pname, int param) noexcept
			{
				glTexParameteri(static_cast<unsigned int>(target), static_cast<unsigned int>(pname), param);
			}

		};
	}
}