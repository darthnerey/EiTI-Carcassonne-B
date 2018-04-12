/* =========================== */
/* ======== Includes  ======== */
/* =========================== */

#include "user_mode.h"
#include "drawing.h"
#include "board.h"

#include <stdbool.h>
#include <string.h>

/* =========================== */
/* ======== Constants ======== */
/* =========================== */
const char* str_help = "help";
const char* str_exit = "exit";
const char* str_setTile = "setTile";
const char* str_getTile = "getTile";
const char* str_getTiles = "getTiles";
const char* str_rotateCW = "rotateCW";
const char* str_rotateCCW = "rotateCCW";

const char* str_help_desc = "setTile [x] [y] [t][r][b][l][m] - sets all parts of a tile\ngetTile [x] [y] - shows a single tile\nrotateCW [x] [y] - rotates a tile clockwise\nrotateCCW [x] [y] - rotates a tile counter-clockwise\ngetTiles - shows the entire board\nexit - exits the game\n";

/* =========================== */
/* ======== Functions ======== */
/* =========================== */

#define INPUT(X) \
	if (strcmp(command, X) == 0)
 
/*!
	Process one command from user's input
*/
void process_input()
{
	int x, y;
	char command[256];
	char t, r, b, l, m;
	scanf("%s", &command);
	
	INPUT(str_help) printf(str_help_desc);
	INPUT(str_exit) exit(0);
	INPUT(str_setTile) 
	{
		printf("x = ");
		scanf("%i", &x);
		printf("y = ");
		scanf("%i", &y);
		printf("value = ");
		scanf(" %c%c%c%c%c", &t, &r, &b, &l, &m);
		current_board.Tiles[x][y].Top = (T_Part)t;
		current_board.Tiles[x][y].Right = (T_Part)r;
		current_board.Tiles[x][y].Bottom = (T_Part)b;
		current_board.Tiles[x][y].Left = (T_Part)l;
		current_board.Tiles[x][y].Middle = (T_Part)m;
	}
	INPUT(str_getTile)
	{
		printf("x = ");
		scanf("%i", &x);
		printf("y = ");
		scanf("%i", &y);
		draw_tile((const Board*)&current_board, x, y);
	}
	INPUT(str_rotateCW)
	{
		printf("x = ");
		scanf("%i", &x);
		printf("y = ");
		scanf("%i", &y);
		rotateTileCW(&current_board.Tiles[x][y]);
	}
	INPUT(str_rotateCCW)
	{
		printf("x = ");
		scanf("%i", &x);
		printf("y = ");
		scanf("%i", &y);
		rotateTileCCW(&current_board.Tiles[x][y]);
	}
	INPUT(str_getTiles) draw_tiles((const Board*)&current_board);
}

/*!
	Enter an input processing loop
*/
void input_loop()
{
	do 
	{
		process_input();
	}
	while (true);
}