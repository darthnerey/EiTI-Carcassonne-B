/* =========================== */
/* ======== Includes  ======== */
/* =========================== */

#include "board.h"

/* =========================== */
/* ======== Functions ======== */
/* =========================== */

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
	
	return 1;
}

void randomize_board(Board* board)
{
	
}