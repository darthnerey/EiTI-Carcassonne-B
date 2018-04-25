/* =========================== */
/* ======== Includes  ======== */
/* =========================== */

#include "board.h"

/* =========================== */
/* ======== Functions ======== */
/* =========================== */

void initBoard(Board* board)
{
	int x, y;
	for (y = 0; y < board->Height; y++)
	{
		for (x = 0; x < board->Width; x++)
		{
			board->Tiles[x][y].Top = T_Nothing;
			board->Tiles[x][y].Bottom = T_Nothing;
			board->Tiles[x][y].Left = T_Nothing;
			board->Tiles[x][y].Middle = T_Nothing;
			board->Tiles[x][y].Right = T_Nothing;
		}
	}
}

bool isTileEmpty(const Tile tile)
{
	return tile.Top == T_Nothing
		&& tile.Bottom == T_Nothing
		&& tile.Left == T_Nothing
		&& tile.Right == T_Nothing
		&& tile.Middle == T_Nothing;
}

int getBoardPoints(const Board* board)
{
}

void randomize_board(Board* board)
{
	
}

void rotateTileCW(Tile* tile)
{
	T_Part t, b, r, l;
	t = tile->Top;	
	b = tile->Bottom;	
	r = tile->Right;
	l = tile->Left;	
	tile->Top = l;
	tile->Right = t;
	tile->Bottom = r;
	tile->Left = b;
}

void rotateTileCCW(Tile* tile)
{
	T_Part t, b, r, l;
	t = tile->Top;	
	b = tile->Bottom;	
	r = tile->Right;
	l = tile->Left;	
	tile->Top = r;
	tile->Left = t;
	tile->Bottom = l;
	tile->Right = b;
}

void flipTileH(Tile* tile)
{
	T_Part X = tile->Left;
	tile->Left = tile->Right;
	tile->Right = X;
}

void flipTileV(Tile* tile)
{
	T_Part X = tile->Top;
	tile->Top = tile->Bottom;
	tile->Bottom = X;
}