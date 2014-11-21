#include "DropletCustomTwo.h"

DropletCustomTwo::DropletCustomTwo(ObjectPhysicsData *objPhysics) 
	: DSimDroplet(objPhysics)
{ return; }

DropletCustomTwo::~DropletCustomTwo() {}

void DropletCustomTwo::DropletInit()
{
	init_all_systems();
	droplet_id_type my_id = get_droplet_id();
	uint8_t r=0, g=0, b=0;
	get_color_from_id(my_id, &r, &g, &b);
	set_rgb_led(r, g, b);

}

void DropletCustomTwo::DropletMainLoop()
{
}

void DropletCustomTwo::get_color_from_id(droplet_id_type id, uint8_t* r, uint8_t* g, uint8_t* b)
{
	// initial id depends on the number of non-droplet objects added to the scene
	// choose red, green, blue, yellow, cyan, magenta, white or off based on id
	int color = (int)id % 8;
	switch (color)
	{
	default: // off 
		*r = 0;
		*g = 0;
		*b = 0;
		break;
	}
}