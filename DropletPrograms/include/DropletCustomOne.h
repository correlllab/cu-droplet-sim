/* *** PROGRAM DESCRIPTION ***
 * 
 */
#pragma once

#include <DSimDroplet.h>
#include <DSimGlobals.h>
#include <DSimDataStructs.h>

#include <inttypes.h>
#include <map>
#include <utility>
#include <cstdlib>
#include <cstring>
#define _USE_MATH_DEFINES
#include <math.h>

class DropletCustomOne : public DSimDroplet
{
private :
	droplet_id_type my_id;
	void get_color_from_id(droplet_id_type id, uint8_t* r, uint8_t* g, uint8_t* b);
public :
	DropletCustomOne(ObjectPhysicsData *objPhysics);
	~DropletCustomOne(void);
	
	void DropletInit(void);
	void DropletMainLoop(void);
};