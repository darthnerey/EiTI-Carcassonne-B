#pragma once
#ifndef DRAWING_H
#define DRAWING_H

#include "TilePool.h"
#include "Board.h"
#include "Tile.h"

bool PrintListFile(const ListRef list);
bool PrintBoardFile(const BoardRef board);
bool PrintBoardGrid(const BoardRef board);
#endif