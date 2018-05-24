#pragma once
#ifndef _GAME_H
#define _GAME_H 1

/* =========================== */
/* ======== Includes  ======== */
/* =========================== */

#include "Utils.h"
#include "Board.h"
#include "File_IO.h"
#include "Tile_Pool.h"
#include "User_Mode.h"

/* =========================== */
/* ======== Constants ======== */
/* =========================== */

const char* str_authors = "Leonid Sawin and Mazen Ibrahim";
const char* str_title = "EPFU Carcassonne Project";

/* =========================== */
/* ========  Globals  ======== */
/* =========================== */

// App's main return code
int app_returns;
// Currently used board
Board current_board;
// Currently used tile pool
TilePool* current_tile_pool;

/* =========================== */
/* ======== Functions ======== */
/* =========================== */

/*!
Initialize everything before we start
*/
void initialize_app()
{
	// Via default, we have no error.
	app_returns = 0;

	// Initialize the current board
	initBoard(&current_board);
	current_tile_pool = NULL;

	// Set the appropriate window title
	SetConsoleTitle(str_title);
}

/*!
Print out the list of authors
*/
void print_authors()
{
	printf("Authors: %s\n", str_authors);
}

/*!
Print out the usage
*/
void print_usage(char* exename)
{
	printf("Usage: %s [tile_pool] [tile_board]\n", exename);
	printf("Usage: %s /user\n", exename);
}

/*!
Clear the screen
*/
void clear()
{
#if WINDOWS
	system("cls");
#elseif LINUX
	system("clear");
#endif
}

/*!
Parse arguments for the Auto-Mode
*/
void parse_args_auto_mode(int argc, char** argv)
{
}

/*!
Parse arguments for the User-Mode
*/
void parse_args_user_mode(int argc, char** argv)
{
	current_tile_pool = read_tile_pool(argv[1]);
	init_user_mode();
}

/*!
Parse the input arguments
*/
void parse_args(int argc, char **argv)
{
	const char* str_arg_authors = "/authors";
	const char* str_arg_user = "/user";

	switch (argc)
	{
	case 3:
		parse_args_auto_mode(argc, argv);
		break;
	case 2:
		// Warning #1: strcmp is case-sensitive.
		// Warning #2: strcmp returns 0 for Matching Strings.
		if (strcmp(argv[1], str_arg_authors) == 0)
			print_authors();
		else if (strcmp(argv[1], str_arg_user) == 0)
			init_user_mode();
		else
			parse_args_user_mode(argc, argv);
		break;

	default:
		print_usage(argv[0]);
		break;
	}
}

#endif