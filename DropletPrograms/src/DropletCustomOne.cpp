#include "DropletCustomOne.h"

DropletCustomOne::DropletCustomOne(ObjectPhysicsData *objPhysics) 
	: DSimDroplet(objPhysics)
{ return; }

DropletCustomOne::~DropletCustomOne() { }

void DropletCustomOne::DropletInit()
{
	init_all_systems();
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
	// initial id depends on the number of non-droplet objects added to the scene
	// choose red, green, blue, yellow, cyan, magenta, white or off based on id
	int color = (int)id % 8;
	switch (color)
	{
	case 0: // red
		*r = 255; 
		*g = 0;
		*b = 0;
		break;
	case 1: // green
		*r = 0;
		*g = 255;
		*b = 0;
		break;
	case 2: // blue
		*r = 0; 
		*g = 0;
		*b = 255;
		break;
	case 3: // yellow
		*r = 255;
		*g = 255;
		*b = 0;
		break;
	case 4: // cyan
		*r = 0;
		*g = 255;
		*b = 255;
		break;
	case 5: // magenta
		*r = 255;
		*g = 0;
		*b = 255;
		break;
	case 6: // white
		*r = 255;
		*g = 255;
		*b = 255;
		break;
	case 7: // off;
		*r = 0;
		*g = 0;
		*b = 0;
		break;
	default: // off 
		*r = 0;
		*g = 0;
		*b = 0;
		break;
		break;
	}
}