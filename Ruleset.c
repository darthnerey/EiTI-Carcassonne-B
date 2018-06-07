#include "Ruleset.h"

char* Ruleset[RulesTotal];

void BuildRuleset(void)
{
	const char* defaults[14] = 
	{
		"ffrft",
		"fffft",
		"cccc*",
		"rcrf_",
		"cfff_",
		"fcfc_",
		"fccf_",
		"crrf_",
		"rcfr_",
		"rcrr_",
		"rfrf_",
		"ffrr_",
		"frrr_",
		"rrrr_"
	};

	int32_t counter = 0;
	for (int32_t i = 0; i < 14; i++)
	{
		TileRef Tile = TileFromString(defaults[i]);
		for (int32_t r = 0; r < 4; r++)
		{
			RotateTileCW(Tile);
			Ruleset[counter++] = TileToString(Tile);
		}
		FreeTile(&Tile);
	}
}

bool CheckTileRules(const TileRef tile)
{
	for (int32_t i = 0; i < RulesTotal; i++)
	{
		if (TileEqualsString(tile, Ruleset[i]))
			return true;
	}
	return false;
}
