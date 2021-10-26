#include "apple.h"
#include "drawable.h"
#include "drawable_list.h"

Apple::Apple(int arg1, int arg2) 
	: Drawable({ (unsigned short)arg1, (unsigned short)arg2, 1, 1 }) {}

void Apple::move(direction_t direction) {}

void Apple :: draw() { mini_gui_print_rect(mg, this->bounding_box, APPLE); }

int Apple::id() { return 1; }

void Apple::refresh() { this->~Apple(); }

void Apple::step(DrawableList& lst) {}