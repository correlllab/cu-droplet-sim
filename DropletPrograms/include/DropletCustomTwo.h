/* *** PROGRAM DESCRIPTION ***
 * 
 */
#pragma once

#include <DSimDroplet.h>
#include <DSimGlobals.h>
#include <DSimDataStructs.h>
#include <inttypes.h>

class DropletCustomTwo : public DSimDroplet
{
private :
	droplet_id_type my_id;
	void get_color_from_id(droplet_id_type id, uint8_t* r, uint8_t* g, uint8_t* b);

public :
	DropletCustomTwo(ObjectPhysicsData *objPhysics);
	~DropletCustomTwo(void);
	
	void DropletInit(void);
	void DropletMainLoop(void);
};