/* *** PROGRAM DESCRIPTION ***
 * 
 */
#pragma once

#include <DSimDroplet.h>
#include <DSimGlobals.h>
#include <DSimDataStructs.h>
#include <inttypes.h>

class DropletCustomOne : public DSimDroplet
{
private :
 
public :
	DropletCustomOne(ObjectPhysicsData *objPhysics);
	~DropletCustomOne(void);
	
	void DropletInit(void);
	void DropletMainLoop(void);
};