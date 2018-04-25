#pragma once
#ifndef _DRAWING_H
#define _DRAWING_H 1

#include "board.h"

/* =========================== */
/* ======== Functions ======== */
/* =========================== */
	
/*!
	Draw tiles around (x, y) in "radius" r
*/
void draw_tiles(const Board* board, int x, int y, int r);

/*!
	Draw a tile at (x, y)
*/
void draw_tile(const Board* board, int x, int y);

#endif