/* =========================== */
/* ======== Includes  ======== */
/* =========================== */

#include "tile_pool.h"
#include "user_mode.h"
#include "drawing.h"
#include "board.h"
#include "file_io.h"

#include <stdbool.h>
#include <string.h>

/* =========================== */
/* ======== Commands ========= */
/* =========================== */

#define MAX_UsrCmd 64
int32_t CommandsTotal = 0;
UsrCmd Commands[MAX_UsrCmd];

void cmd_allocBoard(void)
{
	Size2 size;
	printf("Width = ");
	scanf("%i", &size.Width);
	printf("Height = ");
	scanf("%i", &size.Height);
	allocBoard(&current_board, size);
}

void cmd_setTile(void)
{
	Point2 coords;
	char t, r, b, l, m;
	printf("X = ");
	scanf("%i", &coords.X);
	printf("Y = ");
	scanf("%i", &coords.Y);
	if (Contains(current_board.Bounds, coords))
	{
		TileRef tile = assertTile(&current_board, coords);
		printf("value = ");
		scanf(" %c%c%c%c%c", &t, &r, &b, &l, &m);
		tile->Top = t;
		tile->Left = l;
		tile->Right = r;
		tile->Bottom = b;
		tile->Middle = m;
	}
	else
	{
		printf("Out of bounds!\n");
	}
}

void cmd_placeTile(void)
{
	TileRef tile;
	Point2 coords;
	int32_t index = 0, counter = 0;
	TilePool* ptr = current_tile_pool;

	if (getTilePoolSize(ptr) == 0)
	{
		printf("Tile pool is empty!\n");
		return;
	}

	while (ptr != NULL)
	{
		tile = ptr->Tile;
		printf(
			"%i - [%c%c%c%c%c]\n",
			counter++,
			tile->Top,
			tile->Right,
			tile->Bottom,
			tile->Left,
			tile->Middle
		);
		ptr = ptr->Next;
	}

retry_index:
	printf("Pick your tile: ");
	scanf("%i", &index);
	if (index > counter || index < 0)
	{
		printf("Index out of bounds!\n");
		goto retry_index;
	}

	counter = 0;
	ptr = current_tile_pool;
	while (counter++ < index)
		ptr = ptr->Next;

	tile = ptr->Tile;

retry_coords:
	printf("X = ");
	scanf("%i", &coords.X);
	printf("Y = ");
	scanf("%i", &coords.Y);
	if (Contains(current_board.Bounds, coords))
	{
		if (isTilePresent(&current_board, coords))
		{
			printf("There's already a tile in there!\n");
			goto retry_coords;
		}
		setTile(&current_board, coords, tile);
		removeFromTilePool(ptr);
	}
	else
	{
		printf("Index out of bounds!\n");
		goto retry_coords;
	}
}

void cmd_getTile(void)
{
	Point2 coords;
	printf("X = ");
	scanf("%i", &coords.X);
	printf("Y = ");
	scanf("%i", &coords.Y);
	draw_tile(&current_board, coords);
}

void cmd_getTiles(void)
{
	Rect2 rect;
	printf("Min.X = ");
	scanf("%i", &rect.Min.X);
	printf("Min.Y = ");
	scanf("%i", &rect.Min.Y);
	printf("Max.X = ");
	scanf("%i", &rect.Max.X);
	printf("Max.Y = ");
	scanf("%i", &rect.Max.Y);
	draw_tiles(&current_board, rect);
}

void cmd_saveBoard(void)
{
	char buffer[512];
	printf("Filename = ");
	scanf("%s", &buffer);
	write_board(buffer, &current_board);
}

void cmd_loadBoard(void)
{
	char buffer[512];
	printf("Filename = ");
	scanf("%s", &buffer);
	read_board(buffer, &current_board);
}

void cmd_saveTilePool(void)
{
	char buffer[512];
	printf("Filename = ");
	scanf("%s", &buffer);
	write_tile_pool(buffer, current_tile_pool);
}

void cmd_loadTilePool(void)
{
	char buffer[512];
	printf("Filename = ");
	scanf("%s", &buffer);
	freeTilePool(current_tile_pool);
	current_tile_pool = read_tile_pool(buffer);
}

extern int app_returns;
void cmd_exit(void)
{
	exit(app_returns);
}

void cmd_rotateCW(void)
{
	Point2 pos;
	printf("X = ");
	scanf("%i", &pos.X);
	printf("Y = ");
	scanf("%i", &pos.Y);
	TileRef tile = getTile(&current_board, pos);
	if (tile != NULL)
		rotateTileCW(tile);
	else
		printf("Tile (%i, %i) isn't there!\n", pos.X, pos.Y);
}

void cmd_rotateCCW(void)
{
	Point2 pos;
	printf("X = ");
	scanf("%i", &pos.X);
	printf("Y = ");
	scanf("%i", &pos.Y);
	TileRef tile = getTile(&current_board, pos);
	if (tile != NULL)
		rotateTileCCW(tile);
	else
		printf("Tile (%i, %i) isn't there!\n", pos.X, pos.Y);
}

void cmd_flipTileH(void)
{
	Point2 pos;
	printf("X = ");
	scanf("%i", &pos.X);
	printf("Y = ");
	scanf("%i", &pos.Y);
	TileRef tile = getTile(&current_board, pos);
	if (tile != NULL)
		flipTileH(tile);
	else
		printf("Tile (%i, %i) isn't there!\n", pos.X, pos.Y);
}

void cmd_flipTileV(void)
{
	Point2 pos;
	printf("X = ");
	scanf("%i", &pos.X);
	printf("Y = ");
	scanf("%i", &pos.Y);
	TileRef tile = getTile(&current_board, pos);
	if (tile != NULL)
		flipTileV(tile);
	else
		printf("Tile (%i, %i) isn't there!\n", pos.X, pos.Y);
}

/* =========================== */
/* ======== Functions ======== */
/* =========================== */

bool RegUsrCmd(void* method, char* str, char* help)
{
	if (CommandsTotal >= MAX_UsrCmd)
		return false;
	Commands[CommandsTotal].Method = method;
	Commands[CommandsTotal].String = str;
	Commands[CommandsTotal].Help = help;
	CommandsTotal++;
	return true;
}

UsrCmd* GetUsrCmd(const char* input)
{
	int32_t i;
	for (i = 0; i < CommandsTotal; i++)
	{
		if (strcmp(input, Commands[i].String) == 0)
			return &Commands[i];
	}
	return NULL;
}

void PrintUsrCmdHelp(void)
{
	int32_t i;
	printf("Commands: \n");
	for (i = 0; i < CommandsTotal; i++)
		printf("\t%s %s\n", Commands[i].String, Commands[i].Help);
}

void init_user_mode()
{
	RegUsrCmd(PrintUsrCmdHelp, "help", "- prints this.");
	RegUsrCmd(cmd_exit, "exit", "- exits the game");

	RegUsrCmd(cmd_setTile, "setTile", "[x] [y] [trblm] - sets a tile at (x, y)");
	RegUsrCmd(cmd_placeTile, "placeTile", "[x] [y] [pick] - places a tile from the tile pool at (x, y)");
	RegUsrCmd(cmd_getTiles, "getTiles", "[x1] [y1] [x2] [y2] - prints all tiles inside a [(x1, y1), (x2, y2)] rectangle");
	RegUsrCmd(cmd_getTile, "getTile", "[x] [y] - prints a tile at (x, y)");

	RegUsrCmd(cmd_rotateCW, "rotateCW", "[x] [y] - rotates (clockwise) the tile at (x, y)");
	RegUsrCmd(cmd_rotateCCW, "rotateCCW", "[x] [y] - rotates (counter-clockwise) the tile at (x, y)");

	RegUsrCmd(cmd_flipTileH, "flipTileH", "[x] [y] - horizontally flips the tile at (x, y)");
	RegUsrCmd(cmd_flipTileV, "flipTileV", "[x] [y] - vertically flips the tile at (x, y)");

	RegUsrCmd(cmd_allocBoard, "allocBoard", "[w] [h] - allocates a (w, h) board");
	RegUsrCmd(cmd_saveBoard, "saveBoard", "[filename] - writes current board into a file");
	RegUsrCmd(cmd_loadBoard, "loadBoard", "[filename] - reads from a file into current board");
	RegUsrCmd(cmd_saveTilePool, "saveTilePool", "[filename] - writes current tile pool into a file");
	RegUsrCmd(cmd_loadTilePool, "loadTilePool", "[filename] - reads from a file into current tile pool");

	printf("Please, allocate a board:\n");
	cmd_allocBoard();
	input_loop();
}

void process_input()
{
	char buffer[256];
	scanf("%s", buffer);
	UsrCmd* command = GetUsrCmd(buffer);
	if (command != NULL)
	{
		void(*method_ptr)(void) = command->Method;
		method_ptr();
	}
}

void input_loop()
{
	do
	{
		process_input();
	} while (true);
}