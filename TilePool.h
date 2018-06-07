#pragma once
#ifndef TILE_POOL_H
#define TILE_POOL_H
#include "Tile.h"

struct List;
typedef struct List* ListRef;
typedef struct List
{
	TileRef Tile;
	ListRef Next;
	ListRef Prev;
} List;

ListRef AllocList(const TileRef tile);
ListRef GenerateList(const int32_t size);
ListRef ListPopRandom(ListRef* list);
int32_t ListSize(const ListRef list);
ListRef LastInList(const ListRef list);
ListRef FirstInList(const ListRef list);
ListRef IndexInList(const ListRef list, const int32_t index);

bool FreeList(ListRef* list);
bool RemoveList(ListRef* list);
bool InsertAfterList(ListRef node, ListRef after);
bool InsertBeforeList(ListRef node, ListRef before);
#endif