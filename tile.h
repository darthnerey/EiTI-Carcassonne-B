#pragma once
#ifndef TILE_H
#define TILE_H
#include "Utils.h"

#define TileParts 5
#define TileSides 4
#define TileSymbols "cfrt*_"

typedef enum TilePart
{
	City = 'c',
	Road = 'r',
	Field = 'f',
	Temple = 't',
	Shield = '*',
	Nothing = '_'
} TilePart;

typedef union Tile
{
	TilePart Parts[TileParts];
	struct {
		TilePart Top;
		TilePart Right;
		TilePart Bottom;
		TilePart Left;
		TilePart Middle;
	};
} Tile;

typedef Tile* TileRef;

TileRef AllocTile(void);
TileRef AllocRandomTile(void);
TileRef TileFromString(const char* str);

char* TileToString(const TileRef tile);

bool FreeTile(TileRef* tile);
bool FlipTileV(TileRef tile);
bool FlipTileH(TileRef tile);
bool RotateTileCW(TileRef tile);
bool RotateTileCCW(TileRef tile);
bool RandomizeTile(TileRef tile);
bool IsTileValid(const TileRef tile);
bool TileEqualsString(const TileRef tile, const char* string);

TileRef** AllocTiles(const Size size);
#endif