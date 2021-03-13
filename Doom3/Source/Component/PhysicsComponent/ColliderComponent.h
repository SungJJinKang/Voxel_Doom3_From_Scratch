#pragma once
#include "../Core/ServerComponent.h"
#include <StaticContainer/StaticContainer.h>

#include "Physics/Collider/AABB.h"
#include "utility/BVH/BVH_Node_Object.h"

namespace doom
{
	namespace physics 
	{
		class Physics_Server;
	}

	class ColliderComponent : public ServerComponent, public StaticContainer<ColliderComponent>, public BVH3D_Node_Object
	{
		friend class physics::Physics_Server;

	private:

		void ResetAllCollisionState();
	
		void OnPreUpdatePhysics();
		void UpdatePhysics();
		void OnPostUpdatePhysics();

	protected:

		DirtyReceiver bmIsWorldColliderDirty{ true };
		DirtyReceiver bmIsLocalColliderDirty{ true };

		bool bmIsTrigger{ false };

		bool mbIsColliderEnter{ false };
		bool mbIsColliderExit{ false };
		bool mbIsColliderStay{ false };
		
		bool mbIsTriggerEnter{ false };
		bool mbIsTriggerExit{ false };
		bool mbIsTriggerStay{ false };
		
		void InitComponent() override;
		void UpdateComponent() final;
		virtual void FixedUpdateComponent() override;
		void OnEndOfFrame_Component() override;
		void OnDestroy() override;
		void OnActivated() override;
		void OnDeActivated() override;

		/// <summary>
		/// Never Update collider(like AABB3D, Circle2D, Ray) directly!!!
		/// Store collider information 
		/// </summary>
		virtual void UpdateWorldCollider() = 0;
		virtual void UpdateLocalCollider() = 0;

		/// <summary>
		/// Set Collider variable depending on Renderer's mesh
		/// </summary>
		virtual void AutoColliderSetting() = 0;
		/// <summary>
		/// return true if There is Renderer and have AABB3D
		/// </summary>
		/// <param name="aabb3D">aabb will be set by reference</param>
		/// <returns></returns>
		bool GetMeshAABB3D(physics::AABB3D& aabb3D);

		virtual physics::Collider* GetWorldCollider() = 0;

		const math::Matrix4x4& GetModelMatrix() const final;

	public:

	

		bool GetIsColliderEnter()
		{
			return this->mbIsColliderEnter;
		}

		bool GetIsColliderExit()
		{
			return this->mbIsColliderExit;
		}

		bool GetIsColliderStay()
		{
			return this->mbIsColliderStay;
		}


		bool GetIsTriggerEnter()
		{
			return this->mbIsTriggerEnter;
		}

		bool GetIsTriggerExit()
		{
			return this->mbIsTriggerExit;
		}

		bool GetIsTriggerStay()
		{
			return this->mbIsTriggerStay;
		}

		

	};
}
