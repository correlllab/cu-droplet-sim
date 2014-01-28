/* *** PROGRAM DESCRIPTION ***
 * Swarm collaboration using sigmoid function.
 */
#pragma once

#ifndef _DROPLET_CUSTOM_TWO
#define _DROPLET_CUSTOM_TWO

#include <DSimDroplet.h>
#include <DSimGlobals.h>
#include <DSimDataStructs.h>
#include <inttypes.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#define _USE_MATH_DEFINES // For math constants
#include <math.h>

#define RED   0
#define GREEN 1
#define BLUE  2

#define RED_THRESHOLD 220

class DropletCustomTwo : public DSimDroplet
{
private :
	enum STATE
	{
		SEARCH,
		DISCOVER_GROUP,
		LEAD_GROUP,
		WAIT,
		COLLABORATE,
		NUM_STATES
	} state;

	enum MSG_TYPE
	{
		RQST_DISCOVER_GROUP,
		RSP_DISCOVER_GROUP,
		RQST_UPDATE_COLLAB,
	} msg_type;

	uint8_t color_msg[3];
	uint8_t group_size, i_am_leader, repeat_discover_msg;
	static const uint8_t led_state_colors[NUM_STATES][3];
	std::vector<droplet_id_type> unique_ids;

	uint8_t rqst_group_size, sigmoid_slope;

	void init_leader(void);
	void set_state_led(void);
	uint8_t run_sigmoid(void);

	void searching(void);
	void discovering_group(void);
	void leading_group(void);
	void waiting_at_object(void);
	void collaborating(void);
	

public :
	DropletCustomTwo(ObjectPhysicsData *objPhysics);
	~DropletCustomTwo(void);

	void DropletInit(void);
	void DropletMainLoop(void);
};

#endif