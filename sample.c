
#include "mini_gui.h"

// This will be our moving rectangle.
struct rect moving_rectangle = { 2, 2, 9, 4 };

// Our screen refresh method.
// Will draw screen borders
void refresh_screen(struct mini_gui* mg) {
	// Get the screen size
	struct rect r = mini_gui_get_screen_size(mg);
	// Top border
	mini_gui_move(mg, 0, 0);
	for (int i = 0; i < r.width; i++) {
		mini_gui_print(mg, "%s", "_");
	}
	// Bottom border
	mini_gui_move(mg, 0, r.height);
	for (int i = 0; i < r.width; i++) {
		mini_gui_print(mg, "%s", "_");
	}
	// Left border
	for (int i = 1; i < r.height; i++) {
		mini_gui_move(mg, 0, i);
		mini_gui_print(mg, "%s", "|");
	}
	// Right border
	for (int i = 1; i < r.height; i++) {
		mini_gui_move(mg, r.width - 1, i);
		mini_gui_print(mg, "%s", "|");
	}
	// Reset moving rect position
	moving_rectangle.x = 2;
	moving_rectangle.y = 2;
}


int main() {
	// Initiate the MG object.
	// Write logfile into log.txt file
	// Set 'refresh_screen' as the refresh callback method.
	struct mini_gui* mg = mini_gui_init("log.txt", refresh_screen);

	// The moving rectangle will have a velocity
	int vel_x = 1;
	int vel_y = 1;

	// We can write comments to the log file manually
	// (Mainly to help you debug events in the log)
	mini_gui_log(mg, "Hello, this is a line written to log. Velocity: (%d, %d)\n", vel_x, vel_y);

	// Wait for user to kill the program
	while (1) {
		// Sleep 500 ms
		mini_gui_sleep(mg, 300);
		// Clear the text in the current recangle
		mini_gui_clear_rect(mg, moving_rectangle);
		// Get the screen size
		struct rect screen_size = mini_gui_get_screen_size(mg);
		// Update rectangle position like in old DVDs
		if (moving_rectangle.x <= 1) vel_x *= -1;
		if (moving_rectangle.y <= 1) vel_y *= -1;
		if (moving_rectangle.x + moving_rectangle.width >= screen_size.width-1) vel_x *= -1;
		if (moving_rectangle.y + moving_rectangle.height >= screen_size.height-1) vel_y *= -1;
		moving_rectangle.x += vel_x;
		moving_rectangle.y += vel_y;
		// Print a text in a moving rectanlge
		mini_gui_print_rect(mg, moving_rectangle, "Just like printf! Here: %d", 2020);
		// Move the cursor to top screen
		mini_gui_move(mg, 0, 0);
	}

	// Destroy the MG object
	mini_gui_destroy(mg);
}