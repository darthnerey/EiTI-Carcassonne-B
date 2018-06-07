#pragma once
#ifndef FILEIO_H
#define FILEIO_H

#include "Drawing.h"
#include "Board.h"
#include "Tile.h"

#include "TilePool.h"

#define file_mode_read "r"
#define file_mode_write "w"
#define file_error_open "Can't open file: "
#define file_error_read "Error reading from file: "
#define file_error_write "Error reading to file: "

bool SaveBoard(const BoardRef board, const char* path);
bool SaveList(const ListRef list, const char* path);

bool FileExists(const char* path);

BoardRef LoadBoard(const char* path);
ListRef LoadList(const char* path);
#endif