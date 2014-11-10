#include "DropletCustomOne.h"

DropletCustomOne::DropletCustomOne(ObjectPhysicsData *objPhysics) 
	: DSimDroplet(objPhysics)
{ return; }

DropletCustomOne::~DropletCustomOne() { }

void DropletCustomOne::DropletInit()
{
	droplet_id_type my_id = get_droplet_id();
	uint8_t r=0, g=0, b=0;
	get_color_from_id(my_id, &r, &g, &b);
	set_rgb_led(r, g, b);
}

void DropletCustomOne::DropletMainLoop()
{
}

void DropletCustomOne::get_color_from_id(droplet_id_type id, uint8_t* r, uint8_t* g, uint8_t* b)
{
	switch (id) {
	case 1:
		*r=255;
		*g=0;
		*b=0;
		break;
	case 2:
		*r=0;
		*g=255;
		*b=0;
		break;
	case 3:
		*r=0;
		*g=0;
		*b=255;
		break;
	case 4:
		*r=255;
		*g=255;
		*b=0;
		break;
	case 5:
		*r=255;
		*g=0;
		*b=255;
		break;
	case 6:
		*r=0;
		*g=255;
		*b=255;
		break;
	case 7:
		*r=255;
		*g=255;
		*b=255;
		break;
	case 8:
		*r=255;
		*g=0;
		*b=128;
		break;
	default:
		*r=0;
		*g=0;
		*b=0;
		break;
	}

}