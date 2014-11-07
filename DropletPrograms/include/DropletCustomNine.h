/* *** PROGRAM DESCRIPTION ***
 * Testing global_rx_buffer.data_len bug
 */
#pragma once

#include <DSimDroplet.h>
#include <DSimGlobals.h>
#include <DSimDataStructs.h>
#include <inttypes.h>

class DropletCustomNine : public DSimDroplet
{
private :

public :
	DropletCustomNine(ObjectPhysicsData *objPhysics);
	~DropletCustomNine(void);
	
	void DropletInit(void);
	void DropletMainLoop(void);
};