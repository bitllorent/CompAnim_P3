/*
 *  Simulator.cpp
 *  BasicPhyx
 *
 *  Created by Karen Liu on 12/11/10.
 *  Copyright 2010 GA Tech. All rights reserved.
 *
 */

#ifndef __SIMULATOR_H__
#include "Simulator.h"
#endif

#include "Util/UserAllocator.h"
#include "Util/Timing.h"
#include "Util/Utilities.h"
#include "DrawObjects.h"
#include "Actors.h"

NxVec3 Simulator::ApplyForceToActor(NxActor *actor, const NxVec3& forceDir)
{
	NxVec3 forceVec = mForceStrength * forceDir;
	
	if (mForceMode)
		actor->addForce(forceVec);
	else 
		actor->addTorque(forceVec);
	
	return forceVec;
}

void Simulator::ProcessKeys(const bool *keys)
{	
	
}

void Simulator::RenderActors()
{
    // Render all the actors in the scene
    int nActor = mScene->getNbActors();
    NxActor** actors = mScene->getActors();
    while (nActor--){
        NxActor* actor = *actors++;
        DrawActor(actor);
    }
}

void Simulator::RenderForce(NxActor* actor, NxVec3& forceVec, const NxVec3& color)
{
	// draw only if the force is large enough
	NxReal force = forceVec.magnitude();
	if (force < 0.1f)  return;
	
	forceVec = 3 * forceVec/force;
	
	NxVec3 pos = actor->getCMassGlobalPosition();
	DrawArrow(pos, pos + forceVec, color);
}

void Simulator::RenderScene()
{
	RenderActors();
	if(mActors->mSelectedActor)
		RenderForce(mActors->mSelectedActor, mForceVec, NxVec3(1, 0, 0));
}

bool Simulator::InitNx()
{
	if(mAllocator == NULL)
		mAllocator = new UserAllocator;
	
	// Initialize PhysicsSDK
	NxPhysicsSDKDesc desc;
	NxSDKCreateError errorCode = NXCE_NO_ERROR;
	mSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, mAllocator, NULL, desc, &errorCode);
	if(mSDK == NULL){
		printf("\nSDK create error (%d - %s).\nUnable to initialize the PhysX SDK, exiting the sample.\n\n", errorCode, getNxSDKCreateError(errorCode));
		return false;
	}
	
	// Set the physics parameters
	mSDK->setParameter(NX_SKIN_WIDTH, 0.005f);
	
	// Set the debug visualization parameters
	mSDK->setParameter(NX_VISUALIZATION_SCALE, 1);
	mSDK->setParameter(NX_VISUALIZE_COLLISION_SHAPES, 1);
	mSDK->setParameter(NX_VISUALIZE_JOINT_LIMITS, 1);
	mSDK->setParameter(NX_VISUALIZE_JOINT_LOCAL_AXES, 1);


    // Create the scene
    NxSceneDesc sceneDesc;
    sceneDesc.gravity = NxVec3(0, -9.8, 0);
    mScene = mSDK->createScene(sceneDesc);
	if(mScene == NULL){
		printf("\nError: Unable to create a PhysX scene, exiting the sample.\n\n");
		return false;
	}
	return true;
}

void Simulator::CreateScene()
{	
	mActors = new Actors(mSDK, mScene);
	NxMaterial *defaultMaterial = mScene->getMaterialFromIndex(0); 
	defaultMaterial->setRestitution(0.0f);
	defaultMaterial->setStaticFriction(0.5f);
	defaultMaterial->setDynamicFriction(0.5f);
	
	// Create the objects in the scene
	mObjects.push_back(mActors->CreateGroundPlane());

	//create player
	NxActor *player = mActors->CreateCatapult(NxVec3(5, 0, 0), NxVec3(0.5, 0.5, 0.5), 1.0);
	
	mActors->CreateStack(NxVec3(0, 0, 0), NxVec3(2, 7, 2), NxVec3(0.2, 0.2, 0.2), 1.0);
	
	
	mActors->mSelectedActor = player;
	getElapsedTime();
}


void Simulator::ReleaseNx()
{
	if(mSDK != NULL)
	{
		if(mScene != NULL) mSDK->releaseScene(*mScene);
		mScene = NULL;
		NxReleasePhysicsSDK(mSDK);
		mSDK = NULL;
	}
	
	if (mAllocator)
	{
		delete mAllocator;
		mAllocator = NULL;
	}
}

void Simulator::Reset()
{
	ReleaseNx();
	if (!InitNx()) exit(0);
}


void Simulator::RunPhysics()
{
	// Update the time step
	NxReal deltaTime = getElapsedTime();
//	NxReal deltaTime = 0.0005;

	// Run collision and dynamics for delta time since the last frame
	mScene->simulate(deltaTime);	
	mScene->flushStream();
	mScene->fetchResults(NX_RIGID_BODY_FINISHED, true);
}

NxActor* Simulator::getSelectedActor() {
	return mActors->mSelectedActor;
}


Simulator::Simulator()
{
	mSDK = NULL;
	mScene = NULL;	
	mActors = NULL;
	mAllocator = NULL;
	
	mForceVec = NxVec3(0, 0, 0);
	mForceStrength = 10.0;
	mForceMode = true;
	mSelectedObject = NULL;
}

Simulator::~Simulator()
{
	
	int nObject = mObjects.size();
	for(int i = 0; i < nObject; i++)
		mScene->releaseActor(*mObjects[i]);
	
	mObjects.clear(); 
}