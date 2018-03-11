// Please, keep this file clean AF and don't add ya things here.
// Let it be just be the main() with 2 calls and a ret.
// -- Lemur

#include "game_base.h"

/*!
	An entry point.
*/
int main(char* args)
{	
	// Generate things, set titles, default values et cetera
	initialize_app();
	// Parse the arguments
	parse_args(args);
	// Return the chosen code
	return app_returns;
}