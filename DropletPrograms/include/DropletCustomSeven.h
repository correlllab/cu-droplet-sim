/* *** PROGRAM DESCRIPTION ***
 * 
 */
#pragma once
#include <DSimDroplet.h>
#include <DSimGlobals.h>
#include <DSimDataStructs.h>
#include <inttypes.h>

class DropletCustomSeven : public DSimDroplet
{
private :

public :
	DropletCustomSeven(ObjectPhysicsData *objPhysics);
	~DropletCustomSeven(void);

	
	void DropletInit(void);
	void DropletMainLoop(void);
};