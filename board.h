#pragma once
#ifndef BOARD_H
#define BOARD_H

#include "Utils.h"
#include "Tile.h"
#include "TilePool.h"

typedef struct Board
{
	Size Size;
	int32_t Score;
	TileRef** Tiles;
} Board;

typedef Board* BoardRef;

BoardRef AllocBoard(const Size size);

Size GetBoardSize(const BoardRef board);
Point GetBoardMaxTile(const BoardRef board);
Point GetBoardMinTile(const BoardRef board);
Rectangle GetBoardBounds(const BoardRef board);

int32_t GetBoardWidth(const BoardRef board);
int32_t GetBoardHeight(const BoardRef board);

TileRef GetTile(const BoardRef board, const Point at);

bool FreeBoard(BoardRef* board);
bool TileExists(BoardRef board, const Point at);
bool TryRemoveTile(BoardRef board, const Point at);
bool ShiftBoard(BoardRef board, const Point shift);
bool ShiftBoardX(BoardRef board, const int32_t x);
bool ShiftBoardY(BoardRef board, const int32_t y);
bool StretchBoard(BoardRef board, const Size size);
bool AssertBoardSize(BoardRef board, const Point fits);
bool StretchBoardW(BoardRef board, const int32_t width);
bool StretchBoardH(BoardRef board, const int32_t height);
bool TrySetTile(BoardRef board, const TileRef tile, const Point at);
bool CanSetTile(BoardRef board, const TileRef tile, const Point at);
bool TryPlaceTile(BoardRef board, const TileRef tile, const Point at);
#endif