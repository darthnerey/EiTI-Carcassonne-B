#pragma once
#ifndef _TILE_POOL_H
#define _TILE_POOL_H 1

/* =========================== */
/* ======== Includes  ======== */
/* =========================== */

#include "Tile.h"

/* =========================== */
/* ======== Structures ======= */
/* =========================== */

typedef struct _TilePool
{
	TileRef Tile;
	struct _TilePool* Next;
	struct _TilePool* Prev;
} TilePool;

extern TilePool* current_tile_pool;

/* =========================== */
/* ======== Functions ======== */
/* =========================== */

int32_t getTilePoolSize(TilePool* pool);

TilePool* allocTilePool(void);
void freeTilePool(TilePool* pool);
void freeTilePoolNode(TilePool* node);

TilePool* getTilePoolRoot(TilePool* pool);
TilePool* insertNextIntoTilePool(TilePool* pool, TileRef tile);
TilePool* insertPrevIntoTilePool(TilePool* pool, TileRef tile);
TilePool* removeFromTilePool(TilePool* pool);

#endif