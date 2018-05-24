/* =========================== */
/* ======== Includes  ======== */
/* =========================== */

#include "drawing.h"
#include "board.h"
#include "utils.h"

/* =========================== */
/* ======== Functions ======== */
/* =========================== */

void draw_tile(const Board* board, const Point2 position)
{
	TileRef tile = getTile(board, position);
	if (tile == NULL) 
		printf("___\n___\n___");
	else 
	{
		printf(" %c \n", tile->Top);
		printf("%c%c%c\n",
			tile->Left,
			tile->Middle,
			tile->Right
		);
		printf(" %c \n", tile->Bottom);
	}
}

void draw_tiles(const Board* board, Rect2 view)
{
	TileRef tile;
	Point2 pos;

	view = Intersect(view, board->Bounds);

	for (pos.Y = view.Min.Y; pos.Y < view.Max.Y; pos.Y++)
	{
		// Scan-line 0
		for (pos.X = view.Min.X; pos.X < view.Max.X; pos.X++)
		{
			tile = getTile(board, pos);
			if (tile == NULL)
				printf("\t");
			else
				printf(" %c ", tile->Top);
		}
		printf("\n");
		// Scan-line 1
		for (pos.X = view.Min.X; pos.X < view.Max.X; pos.X++)
		{
			tile = getTile(board, pos);
			if (tile == NULL)
				printf("\t");
			else 
			{
				printf("%c%c%c",
					tile->Left,
					tile->Middle,
					tile->Right
				);
			}
		}
		printf("\n");
		// Scan-line 2		
		for (pos.X = view.Min.X; pos.X < view.Max.X; pos.X++)
		{
			tile = getTile(board, pos);
			if (tile == NULL)
				printf("\t");
			else
				printf(" %c ", tile->Bottom);
		}
		printf("\n");
	}
}