#include "Tile.h"

TileRef allocTile(void)
{
	return (TileRef)malloc(sizeof(Tile));
}

void freeTile(TileRef tile)
{
	free(tile);
}

void flipTileV(TileRef tile)
{
	T_Part X = tile->Top;
	tile->Top = tile->Bottom;
	tile->Bottom = X;
}

void flipTileH(TileRef tile)
{
	T_Part X = tile->Left;
	tile->Left = tile->Right;
	tile->Right = X;
}

void rotateTileCW(TileRef tile)
{
	T_Part t, b, r, l;
	t = tile->Top;
	b = tile->Bottom;
	r = tile->Right;
	l = tile->Left;
	tile->Top = l;
	tile->Right = t;
	tile->Bottom = r;
	tile->Left = b;
}

void rotateTileCCW(TileRef tile)
{
	T_Part t, b, r, l;
	t = tile->Top;
	b = tile->Bottom;
	r = tile->Right;
	l = tile->Left;
	tile->Top = r;
	tile->Left = t;
	tile->Bottom = l;
	tile->Right = b;
}

bool isTileValid(TileRef tile)
{
	return tile != NULL && isTileLegal(tile);
}

bool isTileLegal(TileRef tile)
{
	// TODO: Think of.. What tiles might actually be illegal / impossible?
	return true;
}
