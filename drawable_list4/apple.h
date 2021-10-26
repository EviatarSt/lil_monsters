#ifndef APPLE_H
#define APPLE_H

#include "drawable.h"
#include "ascii_objects.h"

class Apple: public Drawable {

public:

	Apple(int arg1, int arg2);

	virtual void move(direction_t dirction);

	virtual void draw();
	
	virtual int id();

	virtual void refresh();

	virtual void step(DrawableList& lst);
};


#endif