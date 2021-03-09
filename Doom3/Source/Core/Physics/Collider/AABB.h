#pragma once

#include "../Core.h"
#include <Utility.h>
#include <Vector2.h>
#include <Vector3.h>
#include "Collider.h"
#include <Matrix4x4.h>
#include <functional>

namespace doom
{
	namespace physics
	{
		class AABB2D;
		class AABB3D;

		/// <summary>
		/// reference : https://box2d.org/files/ErinCatto_DynamicBVH_GDC2019.pdf
		/// </summary>
		class AABB3D : public Collider
		{
		public:
			/// <summary>
			/// this is local coordinate, you should map to your world coordinate
			/// </summary>
			math::Vector3 mLowerBound; // minimum extent
			/// <summary>
			/// this is local coordinate, you should map to your world coordinate
			/// </summary>
			math::Vector3 mUpperBound; // maximum extent

			constexpr bool IsValid() const
			{
				return mUpperBound.x > mLowerBound.x && mUpperBound.y > mLowerBound.y && mUpperBound.z > mLowerBound.z;
			}

			constexpr void Validate()
			{
				if (mUpperBound.x < mLowerBound.x)
				{
					float temp = mLowerBound.x;
					mLowerBound.x = mUpperBound.x;
					mUpperBound.x = temp;
					D_DEBUG_LOG("AABB bound is wrong");
				}

				if (mUpperBound.y < mLowerBound.y)
				{
					float temp = mLowerBound.y;
					mLowerBound.y = mUpperBound.y;
					mUpperBound.y = temp;
					D_DEBUG_LOG("AABB bound is wrong");
				}

				if (mUpperBound.z < mLowerBound.z)
				{
					float temp = mLowerBound.z;
					mLowerBound.z = mUpperBound.z;
					mUpperBound.z = temp;
					D_DEBUG_LOG("AABB bound is wrong");
				}
			}

			math::Vector3 GetHalfExtent() const;
			/// <summary>
			/// Get 대각선
			/// </summary>
			/// <returns></returns>
			float GetDiagonarLineLength();

			virtual void Render(eColor color) final;


			ColliderType GetColliderType() const override;

			math::Vector3 GetCenter()
			{
				return (this->mLowerBound + this->mUpperBound) / 2;
			}

			/// <summary>
			/// 부피
			/// </summary>
			/// <param name="A"></param>
			/// <returns></returns>
			static constexpr float GetArea(const AABB3D& A)
			{
				math::Vector3 d = A.mUpperBound - A.mLowerBound;
				return 2.0f * (d.x * d.y + d.y * d.z + d.z * d.x);
			}
			static AABB3D Union(const AABB3D& A, const AABB3D& B)
			{
				return AABB3D(math::Min(A.mLowerBound, B.mLowerBound), math::Max(A.mUpperBound, B.mUpperBound));
			}
			static constexpr float GetUnionArea(const AABB3D& A, const AABB3D& B)
			{
				math::Vector3 d = math::Max(A.mUpperBound, B.mUpperBound) - math::Min(A.mLowerBound, B.mLowerBound);
				return 2.0f * (d.x * d.y + d.y * d.z + d.z * d.x);
			}

			constexpr AABB3D() : mLowerBound{}, mUpperBound{}
			{}
			constexpr AABB3D(const math::Vector3& lowerBound, const math::Vector3& upperBound)
				: mLowerBound(lowerBound), mUpperBound(upperBound)
			{
#ifdef DEBUG_MODE
				this->Validate();
#endif
			}
			constexpr AABB3D(const AABB3D&) = default;
			constexpr AABB3D(AABB3D&&) noexcept = default;
			constexpr AABB3D& operator=(const AABB3D&) = default;
			constexpr AABB3D& operator=(AABB3D&&) noexcept = default;
		};

	
	
		

		bool IsOverlapAABB3DAndPoint(const AABB3D& aabb, const math::Vector3& Point);
		bool IsOverlapAABB3DAndAABB3D(const AABB3D& aabb, const AABB3D& B);
		bool IsOverlapAABB3DAndAABB3D(Collider* aabb, Collider* B);

		math::Vector3 ClosestPointToPoint(const AABB3D& aabb, const math::Vector3& point);

		/// <summary>
		/// https://twitter.com/Herschel/status/1188613724665335808
		/// </summary>
		/// <param name="localAABB"></param>
		/// <param name="modelMatrix"></param>
		/// <param name="resultAABB"></param>
		void ApplyModelMatrixToAABB3D(const AABB3D& localAABB, const math::Matrix4x4& modelMatrix, AABB3D& resultAABB);

		class AABB2D : public Collider
		{
		public:
			/// <summary>
			/// this is local coordinate, you should map to your world coordinate
			/// </summary>
			math::Vector2 mLowerBound; // minimum extent
			/// <summary>
			/// this is local coordinate, you should map to your world coordinate
			/// </summary>
			math::Vector2 mUpperBound; // maximum extent

		

			constexpr bool IsValid() const
			{
				return mUpperBound.x > mLowerBound.x && mUpperBound.y > mLowerBound.y;
			}
			constexpr void Validate()
			{
				if (mUpperBound.x < mLowerBound.x)
				{
					float temp = mLowerBound.x;
					mLowerBound.x = mUpperBound.x;
					mUpperBound.x = temp;
					D_DEBUG_LOG("AABB bound is worng");
				}

				if (mUpperBound.y < mLowerBound.y)
				{
					float temp = mLowerBound.y;
					mLowerBound.y = mUpperBound.y;
					mUpperBound.y = temp;
					D_DEBUG_LOG("AABB bound is worng");
				}
			}

			math::Vector2 GetHalfExtent() const;
			virtual void Render(eColor color) final;
			ColliderType GetColliderType() const override;
			math::Vector2 GetCenter();

			static constexpr float GetArea(const AABB2D& A)
			{
				math::Vector2 d = A.mUpperBound - A.mLowerBound;
				return d.x * d.y;
			}
			static AABB2D Union(const AABB2D& A, const AABB2D& B)
			{
				return AABB2D(math::Min(A.mLowerBound, B.mLowerBound), math::Max(A.mUpperBound, B.mUpperBound));
			}
			static constexpr float GetUnionArea(const AABB2D& A, const AABB2D& B)
			{
				math::Vector2 d = math::Max(A.mUpperBound, B.mUpperBound) - math::Min(A.mLowerBound, B.mLowerBound);
				return d.x * d.y;
			}

			constexpr AABB2D() : mLowerBound{}, mUpperBound{}
			{}
			constexpr AABB2D(const math::Vector2& lowerBound, const math::Vector2& upperBound)
				: mLowerBound(lowerBound), mUpperBound(upperBound)
			{
#ifdef DEBUG_MODE
				this->Validate();
#endif
			}

			constexpr AABB2D(const AABB2D&) = default;
			constexpr AABB2D(AABB2D&&) noexcept = default;
			constexpr AABB2D(const AABB3D & aabb3D)
			{
				this->mLowerBound = aabb3D.mLowerBound;
				this->mUpperBound = aabb3D.mUpperBound;
			}
			AABB2D& operator=(const AABB2D&) = default;
			AABB2D& operator=(AABB2D&&) noexcept = default;
			AABB2D& operator=(const AABB3D & aabb3D);
		};

		
	

		bool IsOverlapAABB2DAndPoint(const AABB2D& aabb, const math::Vector2& Point);
		bool IsOverlapAABB2DAndAABB2D(const AABB2D& aabb, const AABB2D& B);
		bool IsOverlapAABB2DAndAABB2D(Collider* aabb, Collider* B);
		math::Vector2 ClosestPointToPoint(const AABB2D& aabb, const math::Vector2& point);
	
		/// <summary>
		/// https://twitter.com/Herschel/status/1188613724665335808
		/// </summary>
		/// <param name="localAABB"></param>
		/// <param name="modelMatrix"></param>
		/// <param name="resultAABB"></param>
		void ApplyModelMatrixToAABB2D(const AABB2D& localAABB, const math::Matrix4x4& modelMatrix, AABB2D& resultAABB);
	}
}

template<>
struct std::greater <doom::physics::AABB2D>
{
	constexpr bool operator()(const doom::physics::AABB2D& lhs, const doom::physics::AABB2D& rhs) const
	{
		return doom::physics::AABB2D::GetArea(lhs) > doom::physics::AABB2D::GetArea(rhs);
	}
};

template<>
struct std::greater <doom::physics::AABB3D>
{
	constexpr bool operator()(const doom::physics::AABB3D& lhs, const doom::physics::AABB3D& rhs) const
	{
		return doom::physics::AABB3D::GetArea(lhs) > doom::physics::AABB3D::GetArea(rhs);
	}
};