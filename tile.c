#include "Tile.h"
#include "Ruleset.h"

TileRef AllocTile(void)
{
	TileRef result = (TileRef)malloc(sizeof(Tile));
	if (result == NULL) return NULL;
	for (int32_t i = 0; i < TileParts; i++)
		result->Parts[i] = Nothing;
	return result;
}

TileRef AllocRandomTile(void)
{
	TileRef result = AllocTile();
	RandomizeTile(result);
	return result;
}

TileRef TileFromString(const char* str)
{
	if (strlen(str) != 5)
		return NULL;

	for (int32_t i = 0; i < TileParts; i++)
	{
		if (IndexOf(str[i], TileSymbols) == -1)
			return NULL;
	}

	TileRef result = AllocTile();

	for (int32_t i = 0; i < TileParts; i++)
		result->Parts[i] = str[i];

	return result;
}

char* TileToString(const TileRef tile)
{
	char* result = (char*)malloc(sizeof(char) * 6);
	for (int32_t i = 0; i < TileParts; i++)
		result[i] = tile->Parts[i];
	result[5] = '\0';
	return result;
}

bool FreeTile(TileRef* tile)
{
	if (*tile != NULL)
	{
		free(*tile);
		*tile = NULL;
		return true;
	}
	return false;
}

bool FlipTileV(TileRef tile)
{
	if (tile == NULL)
		return false;
	TilePart T = tile->Top;
	tile->Top = tile->Bottom;
	tile->Bottom = T;
	return true;
}

bool FlipTileH(TileRef tile)
{
	if (tile == NULL)
		return false;
	TilePart T = tile->Left;
	tile->Left = tile->Right;
	tile->Right = T;
	return true;
}

bool RotateTileCW(TileRef tile)
{
	if (tile == NULL)
		return false;
	TilePart t, b, r, l;
	t = tile->Top;
	b = tile->Bottom;
	r = tile->Right;
	l = tile->Left;
	tile->Top = l;
	tile->Right = t;
	tile->Bottom = r;
	tile->Left = b;
	return true;
}

bool RotateTileCCW(TileRef tile)
{
	if (tile == NULL)
		return false;
	TilePart t, b, r, l;
	t = tile->Top;
	b = tile->Bottom;
	r = tile->Right;
	l = tile->Left;
	tile->Top = r;
	tile->Left = t;
	tile->Bottom = l;
	tile->Right = b;
	return true;
}

bool RandomizeTile(TileRef tile)
{
	if (tile == NULL)
		return false;
	int32_t rule = Random(0, RulesTotal);
	for (int32_t i = 0; i < TileParts; i++)
		tile->Parts[i] = Ruleset[rule][i];
	return true;
}

bool IsTileValid(const TileRef tile)
{
	if (tile == NULL)
		return false;
	return CheckTileRules(tile);
}

bool TileEqualsString(const TileRef tile, const char* string)
{
	for (int32_t j = 0; j < TileParts; j++)
	{
		if (string[j] != tile->Parts[j])
		{
			return false;
		}
	}
	return true;
}

TileRef** AllocTiles(const Size size)
{
	if (size.W == 0 || size.H == 0)
		return NULL;

	TileRef** result = (TileRef**)malloc(sizeof(TileRef*) * size.W);
	if (result == NULL) return NULL;

	for (int32_t X = 0; X < size.W; X++)
	{
		result[X] = (TileRef*)malloc(sizeof(TileRef) * size.H);
		if (result[X] == NULL) return NULL;
		for (int32_t Y = 0; Y < size.H; Y++)
		{
			result[X][Y] = NULL;
		}
	}

	return result;
}
