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
	
void draw_tiles(const Board* board)
{
	int x, y = 0;
	
	for (; y < board->Height; y++)
	{
		// Scan-line 0
		for (x = 0; x < board->Width; x++)
			printf(" %c ", board->Tiles[x][y].Top);
		printf("\n");
		// Scan-line 1
		for (x = 0; x < board->Width; x++)
		{
			printf("%c%c%c", 
				board->Tiles[x][y].Left, 
				board->Tiles[x][y].Middle, 
				board->Tiles[x][y].Right
			);
		}
		printf("\n");
		// Scan-line 2		
		for (x = 0; x < board->Width; x++)
			printf(" %c ", board->Tiles[x][y].Bottom);
		printf("\n");
	}
}