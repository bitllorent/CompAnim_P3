/*
 *  Simulator.h
 *  BasicPhyx
 *
 *  Created by Karen Liu on 12/11/10.
 *  Copyright 2010 GA Tech. All rights reserved.
 *
 */

#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

#include "NxPhysics.h"
#include <vector>

class Actors;
class UserAllocator;

class Simulator
{
public:
	NxPhysicsSDK *mSDK;
	NxScene *mScene;	
	
private:
	Actors *mActors;
	UserAllocator *mAllocator;
	NxVec3 mForceVec;
	NxReal mForceStrength;
	bool mForceMode;
	
	
	std::vector<NxActor*> mObjects;
	NxActor *mSelectedObject;
	
public:
	Simulator();
	~Simulator();
	
	bool InitNx();
	void ReleaseNx();
	void CreateScene();
	
	void RenderScene();
	void RunPhysics();
	void ProcessKeys(const bool *keys);

	NxActor* getSelectedActor();
		
private:
	void Reset();
	
	void RenderActors();
	void RenderForce(NxActor* actor, NxVec3& forceVec, const NxVec3& color);	
	NxVec3 ApplyForceToActor(NxActor *actor, const NxVec3 & forceVec);
	
};

#endif