#pragma once
#ifndef _FILE_IO_H
#define _FILE_IO_H 1

/* =========================== */
/* ======== Includes  ======== */
/* =========================== */

#include <stdbool.h>
#include <stdio.h>
#include "board.h"

/* =========================== */
/* ======== Functions ======== */
/* =========================== */

/*!
	Reads board data from a file
*/
bool read_board(char* path, Board* board)

/*!
	Writes board data into a file
*/
bool write_board(char* path, const Board* board)

#endif