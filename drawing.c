/* =========================== */
/* ======== Includes  ======== */
/* =========================== */

#include "drawing.h"
#include "board.h"

/* =========================== */
/* ======== Functions ======== */
/* =========================== */
	
void draw_tile(const Board* board, int x, int y)
{
	printf(" %c \n", board->Tiles[x][y].Top);
	printf("%c%c%c\n", 
		board->Tiles[x][y].Left, 
		board->Tiles[x][y].Middle, 
		board->Tiles[x][y].Right
	);
	printf(" %c \n", board->Tiles[x][y].Bottom);
}

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a > b ? b : a; }

void draw_tiles(const Board* board, int x, int y, int r)
{
	int minX = max(0, x - r), maxX = min(MAX_BOARD - 1, x + r);
	int minY = max(0, y - r), maxY = min(MAX_BOARD - 1, y + r);
	
	for (y = minY; y <= maxY; y++)
	{
		// Scan-line 0
		for (x = minX; x <= maxX; x++)
			printf(" %c ", board->Tiles[x][y].Top);
		printf("\n");
		// Scan-line 1
		for (x = minX; x <= maxX; x++)
		{
			printf("%c%c%c", 
				board->Tiles[x][y].Left, 
				board->Tiles[x][y].Middle, 
				board->Tiles[x][y].Right
			);
		}
		printf("\n");
		// Scan-line 2		
		for (x = minX; x <= maxX; x++)
			printf(" %c ", board->Tiles[x][y].Bottom);
		printf("\n");
	}
}