#pragma once
#ifndef _BOARD_H
#define _BOARD_H 1

#include <stdbool.h>

/* =========================== */
/* ======== Constants ======== */
/* =========================== */

#define MAX_BOARD 128

/* =========================== */
/* ======== Structures ======= */
/* =========================== */

typedef enum T_Part
{
	T_Field = 'f',
	T_Road = 'r',
	T_Temple = 't',
	T_City = 'c',
	T_Shield = '*',
	T_Nothing = '_'
} T_Part;

typedef struct Tile
{
	T_Part Top;
	T_Part Bottom;
	T_Part Left;
	T_Part Right;
	T_Part Middle;
} Tile;

typedef struct Board
{
	int Width;
	int Height;
	Tile Tiles[MAX_BOARD][MAX_BOARD];
} Board;

/* =========================== */
/* ======== Functions ======== */
/* =========================== */

/*!
	Is the tile empty (basically, T_Nothing everywhere)
*/
bool isTileEmpty(const Tile tile);
/*!
	Randomize the Board to be just a random set of tiles
*/
void randomize_board(Board* board);
int getBoardPoints(const Board* board);

#endif