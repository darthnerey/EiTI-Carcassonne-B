#pragma once
#ifndef AI_H
#define AI_H
#include "Utils.h"
#include "Board.h"
#include "Tile.h"
#include "TilePool.h"

bool AIMove(BoardRef board, ListRef* tiles);
bool AISmartMove(BoardRef board, ListRef* tiles);
bool AIRandomMove(BoardRef board, ListRef* tiles);
#endif