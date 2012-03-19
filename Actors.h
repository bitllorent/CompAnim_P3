
#ifndef ACTORS_H
#define ACTORS_H

#include "NxPhysics.h"

class Actors
{
public:
	NxPhysicsSDK *mPhysicsSDK;
	NxScene *mScene;
	NxActor *mSelectedActor;
	
	Actors(NxPhysicsSDK *sdk, NxScene *scene);
	~Actors(){};
	NxActor* CreateGroundPlane(NxReal d = 0);
	NxActor* CreateGroundPlane2();
	NxActor* CreateBox(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);
	NxActor* CreateBox2(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);
	NxActor* CreateBoxOriented(const NxVec3& pos, const NxQuat& orientation, const NxVec3& boxDim, const NxReal density);
	NxActor* CreateSphere(const NxVec3& pos, const NxReal radius, const NxReal density);
	NxActor* CreateCapsule(const NxVec3& pos, const NxReal height, const NxReal radius, const NxReal density);
	
	NxActor* CreateHalfPyramid(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);
	NxActor* CreatePyramid(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);
	NxActor* CreateDownWedge(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);
	
	NxActor* CreateConvexObjectComputeHull(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);
	NxActor* CreateConvexObjectSupplyHull(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);
	NxActor* CreateConcaveObject(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);
	
	NxActor* CreateBunny(const NxVec3& pos, NxTriangleMesh* triangleMesh, const NxReal density);
	
	NxActor** CreateStack(const NxVec3& pos, const NxVec3& stackDim, const NxVec3& boxDim, NxReal density);
	NxActor** CreateTower(const NxVec3& pos, const int heightBoxes, const NxVec3& boxDim, NxReal density);
	
	NxActor* CreateBoxGear(const NxVec3& pos, const NxReal minRadius, const NxReal maxRadius, const NxReal height, const NxU32 numTeeth, const NxReal density);
	NxActor* CreateWheel(const NxVec3& pos, const NxReal minRadius, const NxReal maxRadius, const NxReal height, const NxU32 numTeeth, const NxReal density);
	NxActor* CreateFrame(const NxVec3& pos, const NxReal density);
	NxActor* CreateStep(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);	
	
	NxActor* CreateChassis(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);
	NxActor* CreateTurret(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);
	NxActor* CreateCannon(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);
	
	NxActor* CreateBlade(const NxVec3& pos, const NxVec3& boxDim, const NxReal mass);
	NxActor* CreateBall(const NxVec3& pos, const NxReal radius, const NxReal mass);	
	
	NxFixedJoint* CreateFixedJoint(NxActor* a0, NxActor* a1, const NxVec3& globalAnchor, const NxVec3& globalAxis);
	NxRevoluteJoint* CreateRevoluteJoint(NxActor* a0, NxActor* a1, const NxVec3& globalAnchor, const NxVec3& globalAxis);
	NxSphericalJoint* CreateSphericalJoint(NxActor* a0, NxActor* a1, const NxVec3& globalAnchor, const NxVec3& globalAxis);
	NxD6Joint* CreateD6Joint(NxActor* a0, NxActor* a1, const NxVec3& globalAnchor, const NxVec3& globalAxis);
	NxPrismaticJoint* CreatePrismaticJoint(NxActor* a0, NxActor* a1, const NxVec3& globalAnchor, const NxVec3& globalAxis);
	NxCylindricalJoint* CreateCylindricalJoint(NxActor* a0, NxActor* a1, const NxVec3& globalAnchor, const NxVec3& globalAxis);
	NxPointOnLineJoint* CreatePointOnLineJoint(NxActor* a0, NxActor* a1, const NxVec3& globalAnchor, const NxVec3& globalAxis);
	NxPointInPlaneJoint* CreatePointInPlaneJoint(NxActor* a0, NxActor* a1, const NxVec3& globalAnchor, const NxVec3& globalAxis);
	
	NxSphericalJoint* CreateRopeSphericalJoint(NxActor* a0, NxActor* a1, const NxVec3& globalAnchor, const NxVec3& globalAxis);
	NxSphericalJoint* CreateClothSphericalJoint(NxActor* a0, NxActor* a1, const NxVec3& globalAnchor, const NxVec3& globalAxis);
	NxSphericalJoint* CreateBodySphericalJoint(NxActor* a0, NxActor* a1, const NxVec3& globalAnchor, const NxVec3& globalAxis);
	NxRevoluteJoint* CreateWheelJoint(NxActor* a0, NxActor* a1, const NxVec3& globalAnchor, const NxVec3& globalAxis);
	NxRevoluteJoint* CreateStepJoint(NxActor* a0, NxActor* a1, const NxVec3& globalAnchor, const NxVec3& globalAxis);
	
	NxRevoluteJoint* CreateChassisJoint(NxActor* a0, NxActor* a1, const NxVec3& globalAnchor, const NxVec3& globalAxis);
	NxFixedJoint* CreateCannonJoint(NxActor* a0, NxActor* a1, const NxVec3& globalAnchor, const NxVec3& globalAxis);
	
	NxSphericalJoint* CreateBladeLink(NxActor* a0, NxActor* a1, const NxVec3& globalAnchor, const NxVec3& globalAxis);	
	
private:
	NxQuat AnglesToQuat(const NxVec3& angles);
	void SetActorGroup(NxActor *actor, NxCollisionGroup group);
	void SetActorMaterial(NxActor *actor, NxMaterialIndex index);
	
};

#endif  // ACTORS_H
