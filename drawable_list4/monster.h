#ifndef MONSTER_H
#define MONSTER_H

#include "drawable.h"

class Monster : public Drawable {

	// The level of the monster
	int level;

	// The velocity of the monster
	int vel;

	// The direction the moster is moving right now
	direction_t current_direction;

	// How much to keep the last direction
	int direction_hold;

	// Direction counter
	int direction_counter;

	// The next bounding box
	struct rect next_bb;

	// The gfx of the monster
	const char* gfx;

public:

	/**
	 * @brief Initiate a level 1 monster in x,y
	 */
	Monster(unsigned short x, unsigned short y, int direction_hold);

	/**
	 * @brief Move the object in the direction
	 */
	virtual void move(direction_t direction);

	/**
	 * @brief Draw the object
	 */
	virtual void draw();

	/**
	 * @brief Return an ID that is unique to 
	 * the dynamid type of the drawable object.
	 */
	virtual int id();

	/**
	 * @brief Is called whenever any refresh is required
	 */
	virtual void refresh();

	/**
	 * @brief Do a step in the 'game of life'
	 * @param lst A list of all drawable objects in the world
	 */
	virtual void step(DrawableList& lst);
};

#endif 
