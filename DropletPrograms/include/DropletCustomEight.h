/* *** PROGRAM DESCRIPTION ***
* This is the tile assembly model for making concentric sqaures
*/
#pragma once

#include <DSimDroplet.h>
#include <DSimGlobals.h>
#include <DSimDataStructs.h>
#include <inttypes.h>

class DropletCustomEight : public DSimDroplet
{
private:

public:
	DropletCustomEight(ObjectPhysicsData *objPhysics);
	~DropletCustomEight(void);

	void DropletInit(void);
	void DropletMainLoop(void);
};