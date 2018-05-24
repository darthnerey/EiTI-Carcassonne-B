#include "Tile_Pool.h"

int32_t getTilePoolSize(TilePool* pool)
{
	int32_t size = 0;

	if (pool->Prev != NULL)
	{
		return getTilePoolSize(getTilePoolRoot(pool));
	}

	do
	{
		size++;
		pool = pool->Next;
		if (pool->Next == NULL)
			break;
	} while (true);

	return size;
}

TilePool* allocTilePool(void)
{
	TilePool* result = (TilePool*)malloc(sizeof(TilePool));
	result->Next = result->Prev = NULL;
	result->Tile = NULL;
	return result;
}

void freeTilePool(TilePool* pool) 
{
	if (pool != NULL)
	{
		while (pool->Next != NULL)
			pool = pool->Next;
		TilePool* prev;
		while (pool->Prev != NULL)
		{
			prev = pool->Prev;
			freeTilePoolNode(pool);
			pool = prev;
		}
		freeTilePoolNode(pool);
	}
}

void freeTilePoolNode(TilePool* node)
{
	removeFromTilePool(node);
	free(node);
}

TilePool* getTilePoolRoot(TilePool* pool)
{
	if (pool == NULL)
		return NULL;
	while (pool->Prev != NULL) 
		pool = pool->Prev;
	return pool;
}

TilePool* insertNextIntoTilePool(TilePool* pool, TileRef tile)
{
	TilePool* next = pool->Next;
	pool->Next = (TilePool*)malloc(sizeof(TilePool));
	pool->Next->Tile = tile;
	pool->Next->Next = NULL;
	pool->Next->Prev = pool;
	if (next != NULL)
	{
		next->Prev = pool->Next;
		pool->Next->Next = next;
	}
	return pool->Next;
}

TilePool* insertPrevIntoTilePool(TilePool* pool, TileRef tile)
{
	TilePool* prev = pool->Prev;
	pool->Prev = (TilePool*)malloc(sizeof(TilePool));
	pool->Prev->Tile = tile;
	pool->Prev->Next = prev;
	pool->Prev->Prev = NULL;
	if (prev != NULL)
	{
		prev->Next = pool->Next;
		prev->Prev = pool;
	}
	return pool->Prev;
}

TilePool* removeFromTilePool(TilePool* pool)
{
	TilePool* prev = pool->Prev;
	TilePool* next = pool->Next;
	if (prev != NULL) prev->Next = next;
	if (next != NULL) next->Prev = prev;
	return next;
}
