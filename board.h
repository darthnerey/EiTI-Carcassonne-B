#pragma once
#ifndef _BOARD_H
#define _BOARD_H 1

/* =========================== */
/* ======== Includes  ======== */
/* =========================== */

#include "Tile.h"
#include "Utils.h"

/* =========================== */
/* ======== Structures ======= */
/* =========================== */

typedef TileRef* TileRow;
typedef TileRow* TileRows;

typedef struct Board
{
	Rect2 Bounds;
	int32_t Score;
	TileRows Rows;
} Board;

extern Board current_board;

/* =========================== */
/* ======== Functions ======== */
/* =========================== */

void initBoard(Board* board);
void freeBoard(Board* board);
void emptyBoard(Board* board);
void allocBoard(Board* board, Size2 size);

int32_t getBoardWidth(const Board* board);
int32_t getBoardHeight(const Board* board);
int32_t calculateScore(const Board* board);

Size2 getBoardSize(const Board* board);

TileRef assertTile(Board* board, const Point2 tile);

bool isBoardValid(const Board* board);
bool isTilePresent(const Board* board, const Point2 pos);

bool setTile(Board* board, const Point2 pos, const TileRef tile);
TileRef getTile(const Board* board, const Point2 pos);

#endif