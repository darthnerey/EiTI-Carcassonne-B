#pragma once
#ifndef RULESET_H
#define RULESET_H
#include "Tile.h"
#define RulesTotal (14 * 3)

void BuildRuleset(void);
bool CheckTileRules(const TileRef tile);

extern char* Ruleset[RulesTotal];
#endif