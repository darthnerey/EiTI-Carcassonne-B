#pragma once
#ifndef _DRAWING_H
#define _DRAWING_H 1

/* =========================== */
/* ======== Includes  ======== */
/* =========================== */

#include "Board.h"

/* =========================== */
/* ======== Functions ======== */
/* =========================== */

void draw_tile(const Board* board, const Point2 position);
void draw_tiles(const Board* board, Rect2 view);

#endif