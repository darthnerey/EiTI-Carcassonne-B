#pragma once
#ifndef _TILE_H
#define _TILE_H 1

/* =========================== */
/* ======== Includes  ======== */
/* =========================== */

#include "Utils.h"

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
typedef Tile* TileRef;

/* =========================== */
/* ======== Functions ======== */
/* =========================== */

TileRef allocTile(void);

void freeTile(TileRef tile);
void flipTileV(TileRef tile);
void flipTileH(TileRef tile);
void rotateTileCW(TileRef tile);
void rotateTileCCW(TileRef tile);

bool isTileValid(TileRef tile);
bool isTileLegal(TileRef tile);

#endif