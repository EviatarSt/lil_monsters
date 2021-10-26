#include "monster.h"
#include "drawable.h"
#include "drawable_list.h"
#include <string.h>

Monster::Monster(unsigned short arg1, unsigned short arg2, int arg3)
	:Drawable({ arg1, arg2, 1, 1 }), level(1), vel(1), direction_hold(arg3),
	current_direction(left), direction_counter(0), gfx(MONSTER0), next_bb({ 0,0,1,1 }) {}

void Monster::move(direction_t direction){
	if (this->direction_counter == 0) {
		current_direction = direction;
	}
	struct rect test = mini_gui_get_screen_size(mg);
	if (current_direction == left){
		if ((bounding_box.x - vel) <= test.x) {
			next_bb = bounding_box;
		}
		else{
			next_bb = bounding_box;
			next_bb.x -= vel;
		}
	}
	if (current_direction == up) {
		if ((bounding_box.y - vel) <= test.y) {
			next_bb = bounding_box;
		}
		else {
			next_bb = bounding_box;
			next_bb.y -= vel;
		}
	}
	if (current_direction == right) {
		if ((bounding_box.x +bounding_box.width + vel) >= test.width) {
			next_bb = bounding_box;
		}
		else {
			next_bb = bounding_box;
			next_bb.x += vel;
		}
	}
	if (current_direction == down) {
		if ((bounding_box.y + bounding_box.height + vel) >= test.height) {
			next_bb = bounding_box;
		}
		else {
			next_bb = bounding_box;
			next_bb.y += vel;
		}
	}
	draw();
	if (this->direction_counter == 0) { direction_counter = direction_hold; }
	else { direction_counter--; }
}

void Monster::draw() {
	mini_gui_clear_rect(mg, bounding_box);
	mini_gui_print_rect(mg, next_bb, gfx);
}

void Monster::refresh() {
	if ((5 <= level) && (level < 15)) {
		gfx = MONSTER1;
		bounding_box = { bounding_box.x, bounding_box.y, 3, 1 };
		next_bb = { next_bb.x, next_bb.y, 3, 1 };
	}
	if ((15 <= level) && (level < 25)){
		gfx = MONSTER2;
		bounding_box = { bounding_box.x, bounding_box.y, 3, 2 };
		next_bb = { next_bb.x, next_bb.y, 3, 2 };
	}
	if ((25 <= level)) {
		vel = 2;
		gfx = MONSTER3;
		bounding_box = { bounding_box.x, bounding_box.y, 8, 3 };
		next_bb = { next_bb.x, next_bb.y, 8, 3 };
	}
	struct rect size = mini_gui_get_screen_size(mg);
	int x = bounding_box.x + bounding_box.width - size.width;
	int y = bounding_box.y + bounding_box.height - size.height;
	bounding_box.x = (x < 0) ? bounding_box.x : (bounding_box.x - x);
	bounding_box.y = (y < 0) ? bounding_box.y : (bounding_box.y - y);
}

int Monster::id() { return 2; }

void Monster::step(DrawableList& lst) {
	Iterator self = lst.find(this);
	Iterator current = lst.begin();
	while (current.valid()) {
		Drawable* point = current.get_object();
		//making sure the monster doesn't collide with itself.
		if (point == this) { current = current.next(); continue; }
		if (collide(*point)) {
			if (point->id() == 1) {
				point->refresh();
				level++;
				refresh();
				lst.erase(current);
			}
			else {
				Monster* mons = (Monster*)point;
				if (mons->level < level) {
					level += mons->level;
					lst.erase(current);
					refresh();
				}
				else {
					mons->level += level;
					mons->refresh();
					lst.erase(self);
					break;
				}
			}
		}
		current = current.next();
	}
}