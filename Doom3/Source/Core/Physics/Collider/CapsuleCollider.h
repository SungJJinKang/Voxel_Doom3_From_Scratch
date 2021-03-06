#pragma once
#include "../Core.h"
#include <Vector3.h>
#include "Collider.h"
namespace doom
{
	namespace physics
	{
		class CapsuleCollider : public Collider
		{

		public:

			math::Vector3 mCenter;
			float mHeight;
			float mRadius;

			FORCE_INLINE virtual void* data() final
			{
				return &(this->mCenter);
			}

			FORCE_INLINE virtual const void* data() const final
			{
				return &(this->mCenter);
			}

			CapsuleCollider(const math::Vector3& center, float height, float radius);

			ColliderType GetColliderType() const override;

		protected:
			void Render(eColor color, bool drawInstantly = false) override;

		};

	
	}
}