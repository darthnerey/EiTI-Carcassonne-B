#include "Board.h"

BoardRef AllocBoard(const Size size)
{
	BoardRef result = (BoardRef)malloc(sizeof(Board));
	if (result == NULL) return NULL;
	result->Score = 0;
	result->Size = size;
	result->Tiles = AllocTiles(size);
	return result;
}

Size GetBoardSize(const BoardRef board)
{
	return board->Size;
}

Point GetBoardMaxTile(const BoardRef board)
{
	Point point;
	point.X = 0;
	point.Y = 0;
	if (board == NULL)
		return point;
	Size size = GetBoardSize(board);
	for (point.Y = size.H; point.Y >= 0; point.Y--)
	{
		for (point.X = size.W; point.X >= 0; point.X--)
		{
			if (TileExists(board, point))
				return point;
		}
	}
	return point;
}

Point GetBoardMinTile(const BoardRef board)
{
	Point point;
	point.X = 0;
	point.Y = 0;
	if (board == NULL)
		return point;
	Size size = GetBoardSize(board);
	for (point.Y = 0; point.Y < size.H; point.Y++)
	{
		for (point.X = 0; point.X < size.W; point.X++)
		{
			if (TileExists(board, point))
				return point;
		}
	}
	return point;
}

Rectangle GetBoardBounds(const BoardRef board)
{
	Rectangle result;
	result.Min.X = 0;
	result.Min.Y = 0;
	result.Max.X = board->Size.W;
	result.Max.Y = board->Size.H;
	return result;
}

int32_t GetBoardWidth(const BoardRef board)
{
	return board->Size.W;
}

int32_t GetBoardHeight(const BoardRef board)
{
	return board->Size.H;
}

TileRef GetTile(const BoardRef board, const Point at)
{
	if (board == NULL)
		return NULL;
	if (board->Tiles == NULL)
		return NULL;
	if (at.X < 0 || at.Y < 0)
		return NULL;
	Size size = GetBoardSize(board);
	if (at.X >= size.W || at.Y >= size.H)
		return NULL;
	return board->Tiles[at.X][at.Y];
}

bool FreeBoard(BoardRef* board)
{
	BoardRef pointer = *board;

	if (pointer == NULL)
		return false;
	if (pointer->Tiles == NULL)
		return false;

	for (int32_t X = GetBoardWidth(pointer) - 1; X >= 0; X--)
	{
		if (pointer->Tiles[X] != NULL)
		{
			free(pointer->Tiles[X]);
			pointer->Tiles[X] = NULL;
		}
	}

	free(pointer->Tiles);
	free(pointer);
	*board = NULL;

	return true;
}

bool TileExists(BoardRef board, const Point at)
{
	return GetTile(board, at) != NULL;
}

bool TryRemoveTile(BoardRef board, const Point at)
{
	if (TileExists(board, at))
	{
		board->Tiles[at.X][at.Y] = NULL;
		return true;
	}
	return false;
}

bool ShiftBoard(BoardRef board, const Point shift)
{
	return ShiftBoardX(board, shift.X) 
		&& ShiftBoardY(board, shift.Y);
}

bool ShiftBoardX(BoardRef board, const int32_t x)
{
	if (board == NULL)
		return false;
	if (board->Tiles == NULL)
		return false;
	if (x == 0) return true;

	Point point;
	Size size = GetBoardSize(board);
	Point Min = GetBoardMinTile(board);

	if (x > 0)
	{
		for (point.Y = 0; point.Y < size.H; point.Y++)
		{
			for (point.X = size.W - 1 - x; point.X >= 0; point.X--)
			{
				board->Tiles[point.X + x][point.Y] = GetTile(board, point);
			}
		}
	}
	else 
	{
		for (point.Y = 0; point.Y < size.H; point.Y++)
		{
			for (point.X = 0; point.X < size.W; point.X++)
			{
				Point xGet;
				xGet.X = point.X + Min.X;
				xGet.Y = point.Y;
				board->Tiles[point.X][point.Y] = GetTile(board, xGet);
			}
		}
	}

	return true;
}

bool ShiftBoardY(BoardRef board, const int32_t y)
{
	if (board == NULL)
		return false;
	if (board->Tiles == NULL)
		return false;
	if (y == 0) return true;

	Point point;
	Size size = GetBoardSize(board);
	Point Min = GetBoardMinTile(board);

	if (y > 0)
	{
		for (point.X = 0; point.X < size.W; point.X++)
		{
			for (point.Y = size.H - 1 - y; point.Y >= 0; point.Y--)
			{
				board->Tiles[point.X][point.Y + y] = GetTile(board, point);
			}
		}
	}
	else
	{
		for (point.X = 0; point.X < size.W; point.X++)
		{
			for (point.Y = size.H - 1; point.Y >= 0; point.Y--)
			{
				Point yGet;
				yGet.X = point.X;
				yGet.Y = point.Y + Min.Y;
				board->Tiles[point.X][point.Y] = GetTile(board, yGet);
			}
		}
	}

	return true;
}

bool StretchBoard(BoardRef board, const Size size)
{
	if (board == NULL)
		return false;
	Size curr = GetBoardSize(board);
	if (curr.W > size.W || curr.H > size.H)
		return false;
	if (curr.W == size.W && curr.H == size.H)
		return true;

	Size diff;
	diff.W = size.W - curr.W;
	diff.H = size.H - curr.H;

	if (diff.W > 0)
	{
		if (!StretchBoardW(board, diff.W))
			return false;
	}

	if (diff.H > 0)
	{
		if (!StretchBoardH(board, diff.H))
			return false;
	}

	return true;
}

bool StretchBoardW(BoardRef board, const int32_t width)
{
	if (board == NULL)
		return false;
	Size curr = GetBoardSize(board);
	if (curr.W > width)
		return false;
	if (curr.W == width)
		return true;

	Size size;
	size.W = width;
	size.H = curr.H;

	TileRef** Tiles = AllocTiles(size);
	if (Tiles == NULL)
	{
		printf("Couldn't allocate a [%i, %i] board\n", size.W, size.H);
		return false;
	}

	if (board->Tiles != NULL)
	{
		Point point;
		for (point.X = 0; point.X < curr.W; point.X++)
		{
			for (point.Y = 0; point.Y < curr.H; point.Y++)
			{
				Tiles[point.X][point.Y] = GetTile(board, point);
			}
		}

		for (point.X = 0; point.X < curr.W; point.X++)
		{
			for (point.Y = 0; point.Y < curr.H; point.Y++)
				board->Tiles[point.X][point.Y] = NULL;
			if (board->Tiles[point.X] != NULL)
			{
				free(board->Tiles[point.X]);
				board->Tiles[point.X] = NULL;
			}
		}
		free(board->Tiles);
	}

	board->Tiles = Tiles;
	board->Size = size;

	return true;
}

bool StretchBoardH(BoardRef board, const int32_t height)
{
	if (board == NULL)
		return false;
	Size curr = GetBoardSize(board);
	if (curr.H > height)
		return false;
	if (curr.H == height)
		return true;

	Size size;
	size.W = curr.W;
	size.H = height;

	TileRef** Tiles = AllocTiles(size);
	if (Tiles == NULL)
	{
		printf("Couldn't allocate a [%i, %i] board\n", size.W, size.H);
		return false;
	}

	if (board->Tiles != NULL) 
	{
		Point point;
		for (point.X = 0; point.X < curr.W; point.X++)
		{
			for (point.Y = 0; point.Y < curr.H; point.Y++)
			{
				Tiles[point.X][point.Y] = GetTile(board, point);
			}
		}

		for (point.X = 0; point.X < curr.W; point.X++)
		{
			for (point.Y = 0; point.Y < curr.H; point.Y++)
				board->Tiles[point.X][point.Y] = NULL;
			if (board->Tiles[point.X] != NULL)
			{
				free(board->Tiles[point.X]);
				board->Tiles[point.X] = NULL;
			}
		}
		free(board->Tiles);
	}

	board->Tiles = Tiles;
	board->Size = size;

	return true;
}

bool AssertBoardSize(BoardRef board, const Point fits)
{
	if (board == NULL)
		return false;
	if (board->Tiles == NULL)
	{
		Size size;
		size.W = Abs(fits.X) + 1;
		size.H = abs(fits.Y) + 1;
		board->Size = size;
		board->Tiles = AllocTiles(size);
		return true;
	}
	Size prev = GetBoardSize(board);
	Size curr = prev;
	if (fits.X > 0)
	{
		curr.W = Max(curr.W, fits.X + 1);
		StretchBoardW(board, curr.W);
	}
	if (fits.X < 0)
	{
		curr.W += (-fits.X);
		StretchBoardW(board, curr.W);
		ShiftBoardX(board, -fits.X);
	}
	if (fits.Y > 0)
	{
		curr.H = Max(curr.H, fits.Y + 1);
		StretchBoardH(board, curr.H);
	}
	if (fits.Y < 0)
	{
		curr.H += (-fits.Y);
		StretchBoardH(board, curr.H);
		ShiftBoardY(board, -fits.Y);
	}
	return true;
}

bool TrySetTile(BoardRef board, const TileRef tile, const Point at)
{
	if (CanSetTile(board, tile, at))
	{
		if (AssertBoardSize(board, at))
		{
			Point point;
			point.X = Max(at.X, 0);
			point.Y = Max(at.Y, 0);
			board->Tiles[point.X][point.Y] = tile;
			return true;
		}
	}
	return false;
}

bool CanSetTile(BoardRef board, const TileRef tile, const Point at)
{
	if (board == NULL)
		return false;
	if (board->Tiles == NULL)
		return true;
	if (TileExists(board, at))
		return false;
	if (at.X < -1 || at.Y < -1)
		return false;

	Point pT;
	pT.X = at.X;
	pT.Y = at.Y - 1;
	TileRef tT = GetTile(board, pT);

	Point pB;
	pB.X = at.X;
	pB.Y = at.Y + 1;
	TileRef tB = GetTile(board, pB);

	Point pL;
	pL.Y = at.Y;
	pL.X = at.X - 1;
	TileRef tL = GetTile(board, pL);

	Point pR;
	pR.Y = at.Y;
	pR.X = at.X + 1;
	TileRef tR = GetTile(board, pR);

	if (tT == NULL && tB == NULL && tL == NULL && tR == NULL)
		return false;

	if (tT != NULL && tile->Top != tT->Bottom)
		return false;
	if (tB != NULL && tile->Bottom != tB->Top)
		return false;
	if (tL != NULL && tile->Left != tL->Right)
		return false;
	if (tR != NULL && tile->Right != tR->Left)
		return false;

	return IsTileValid(tile);
}

bool TryPlaceTile(BoardRef board, const TileRef tile, const Point at)
{
	return TrySetTile(board, tile, at);
}
