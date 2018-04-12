#pragma once
#ifndef _DRAWING_H
#define _DRAWING_H 1

#include "board.h"

/* =========================== */
/* ======== Functions ======== */
/* =========================== */
	
void draw_tile(const Board* board, int x, int y);
void draw_tiles(const Board* board);

#endif