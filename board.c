#include "Board.h"

void initBoard(Board* board)
{
	board->Bounds.Max.X = 0;
	board->Bounds.Max.Y = 0;
	board->Bounds.Min.X = 0;
	board->Bounds.Min.Y = 0;
	board->Rows = NULL;
	board->Score = 0;
}

void freeBoard(Board* board)
{
	Size2 size = getBoardSize(board);
	for (int32_t Y = 0; Y < size.Height; Y++)
	{
		for (int32_t X = 0; X < size.Width; X++)
			freeTile(board->Rows[Y][X]);
		free(board->Rows[Y]);
	}
	free(board->Rows);
	board->Rows = NULL;
}

void emptyBoard(Board* board)
{
	Size2 size = getBoardSize(board);
	for (int32_t Y = 0; Y < size.Height; Y++)
	{
		for (int32_t X = 0; X < size.Width; X++) 
		{
			freeTile(board->Rows[Y][X]);
			board->Rows[Y][X] = NULL;
		}
	}
}

void allocBoard(Board* board, Size2 size)
{
	// Because we don't wanna leak
	if (board->Rows != NULL)
		freeBoard(board);
	board->Bounds.Max.X = size.Width;
	board->Bounds.Max.Y = size.Height;
	board->Rows = (TileRows)malloc(sizeof(TileRows) * size.Height);
	for (int32_t Y = 0; Y < size.Height; Y++)
	{
		board->Rows[Y] = (TileRow)malloc(sizeof(TileRow) * size.Width);
		for (int32_t X = 0; X < size.Width; X++)
			board->Rows[Y][X] = NULL;
	}
}

int32_t getBoardWidth(const Board* board)
{
	return Rect2Width(board->Bounds);
}

int32_t getBoardHeight(const Board* board)
{
	return Rect2Height(board->Bounds);
}

int32_t calculateScore(const Board* board)
{
	return -1;
}

Size2 getBoardSize(const Board * board)
{
	Size2 result;
	result.Width = getBoardWidth(board);
	result.Height = getBoardHeight(board);
	return result;
}

TileRef assertTile(Board* board, const Point2 tile)
{
	if (board->Rows[tile.Y][tile.X] == NULL) 
	{
		TileRef result = allocTile();
		result->Top = T_Field;
		result->Left = T_Field;
		result->Right = T_Field;
		result->Middle = T_Field;
		result->Bottom = T_Field;
		board->Rows[tile.Y][tile.X] = result;
		return result;
	}
	return board->Rows[tile.Y][tile.X];
}

bool isBoardValid(const Board* board)
{
	return board->Rows != NULL
		&& board->Score >= 0;
}

bool isTilePresent(const Board* board, const Point2 pos)
{
	if (Contains(board->Bounds, pos))
	{
		return board->Rows[pos.Y][pos.X] != NULL;
	}
	return false;
}

bool setTile(Board* board, const Point2 pos, const TileRef tile)
{
	if (Contains(board->Bounds, pos))
	{
		board->Rows[pos.Y][pos.X] = tile;
		return true;
	}
	else return false;
}

TileRef getTile(const Board* board, const Point2 pos)
{
	if (Contains(board->Bounds, pos))
	{
		return board->Rows[pos.Y][pos.X];
	}
	return NULL;
}
