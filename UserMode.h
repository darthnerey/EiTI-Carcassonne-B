#pragma once
#ifndef USERMODE_H
#define USERMODE_H
#include "TilePool.h"
#include "Drawing.h"
#include "Board.h"
#include "Tile.h"
#include "AI.h"

#include "FileIO.h"

typedef struct Command
{
	void* Method;
	const char* Name;
	const char* Help;
} Command;

typedef Command* CommandRef;

typedef struct GameState
{
	int32_t CommandsTotal;
	CommandRef* Commands;
	BoardRef Board;
	ListRef List;
} GameState;

CommandRef CreateCommand(void* method, const char* string, const char* name);

int UserMode(const char* path);
#endif