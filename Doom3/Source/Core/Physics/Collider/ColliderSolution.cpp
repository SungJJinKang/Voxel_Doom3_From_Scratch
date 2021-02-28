#include "ColliderSolution.h"

#include "AABB.h"
#include "CapsuleCollider.h"
#include "Circle2D.h"
#include "Line.h"
#include "Plane.h"
#include "Ray.h"
#include "Sphere.h"
#include "PhysicsGeneric.h"

// enum class ColliderType
// {
// 	AABB2D,
// 	AABB3D,
// 	Circle2D,
// 	CapsuleCollider,
// 	Line,
// 	Plane,
// 	Ray,
// 	Sphere
// };

//TODO : �� ���� ��� ã�ƺ���
doom::physics::ColliderSolution::is_overlap_algorithm_func doom::physics::ColliderSolution::CollisionAlgorithms[COLLIDER_TYPE_COUNT][COLLIDER_TYPE_COUNT]
{

	//AABB2D
	{
		&(physics::IsOverlapAABB2DAndAABB2D), //AABB2D
		nullptr, //AABB3D
		nullptr, //Circle2D
		nullptr, //CapsuleCollider
		nullptr, //Line
		nullptr, //Plane
		nullptr, //Ray
		nullptr, //Sphere
		nullptr, //Triangle
	},


	//AABB3D
	{
		nullptr, //AABB2D
		&(physics::IsOverlapAABB3DAndAABB3D), //AABB3D
		nullptr, //Circle2D
		nullptr, //CapsuleCollider
		& (physics::RaycastLineAndAABB3D), //Line
		& (physics::IsOverlapAABB3DAndPlane), //Plane
		& (physics::RaycastRayAndAABB3D), //Ray
		&(physics::IsOverlapSphereAndAABB3D), //Sphere
		nullptr, //Triangle
	},


	//Circle2D
	{
		nullptr, //AABB2D
		nullptr, //AABB3D
		nullptr, //Circle2D
		nullptr, //CapsuleCollider
		nullptr, //Line
		nullptr, //Plane
		nullptr, //Ray
		nullptr, //Sphere
		nullptr, //Triangle
	},


	//CapsuleCollider
	{
		nullptr, //AABB2D
		nullptr, //AABB3D
		nullptr, //Circle2D
		nullptr, //CapsuleCollider
		nullptr, //Line
		nullptr, //Plane
		nullptr, //Ray
		nullptr, //Sphere
		nullptr, //Triangle
	},


	//Line
	{
		nullptr, //AABB2D
		& (physics::RaycastLineAndAABB3D), //AABB3D
		nullptr, //Circle2D
		nullptr, //CapsuleCollider
		nullptr, //Line
		& (physics::RaycastLineAndPlane), //Plane
		nullptr, //Ray
		& (physics::RaycastLineAndSphere), //Sphere
		nullptr, //Triangle
	},


	//Plane
	{
		nullptr, //AABB2D
		& (physics::IsOverlapAABB3DAndPlane), //AABB3D
		nullptr, //Circle2D
		nullptr, //CapsuleCollider
		& (physics::RaycastLineAndPlane), //Line
		& (physics::IsOverlapPlaneAndPlane),  //Plane
		& (physics::RaycastRayAndPlane),  //Ray
		& (physics::IsOverlapSphereAndPlane), //Sphere
		nullptr, //Triangle
	},


	//Ray
	{
		nullptr, //AABB2D
		& (physics::RaycastRayAndAABB3D), //AABB3D
		nullptr, //Circle2D
		nullptr, //CapsuleCollider
		nullptr, //Line
		& (physics::RaycastRayAndPlane), //Plane
		nullptr, //Ray
		&(physics::RaycastRayAndSphere), //Sphere
		nullptr, //Triangle
	},


	//Sphere
	{
		nullptr, //AABB2D
		& (physics::IsOverlapSphereAndAABB3D), //AABB3D
		nullptr, //Circle2D
		nullptr, //CapsuleCollider
		& (physics::RaycastLineAndSphere), //Line
		& (physics::IsOverlapSphereAndPlane), //Plane
		& (physics::RaycastRayAndSphere), //Ray
		& (physics::IsOverlapSphereAndSphere), //Sphere
		nullptr, //Triangle
	},

	//Triangle
	{
		nullptr, //AABB2D
		nullptr, //AABB3D
		nullptr, //Circle2D
		nullptr, //CapsuleCollider
		nullptr, //Line
		nullptr, //Plane
		nullptr, //Ray
		nullptr, //Sphere
		nullptr, //Triangle
	}
};

doom::physics::ColliderSolution::is_overlap_algorithm_func doom::physics::ColliderSolution::GetCollisionAlgorithm(Collider* colliderA, Collider* colliderB)
{
	return doom::physics::ColliderSolution::CollisionAlgorithms[static_cast<unsigned int>(colliderA->GetColliderType())][static_cast<unsigned int>(colliderB->GetColliderType())];
}