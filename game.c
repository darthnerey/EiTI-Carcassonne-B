#include "game.h"

/*!
An entry point.
*/
int main(int argc, char **argv)
{
	// Generate things, set titles, default values et cetera
	initialize_app();
	// Parse the arguments
	parse_args(argc, argv);
	// Return the chosen code
	return app_returns;
}