// Dump your includes and other stuff here, under <windows.h>
// Otherwise, keep this file clean, neat and utility-only.
// -- Lemur

#pragma once
#ifndef _BASE_H
#define _BASE_H 1

/* =========================== */
/* ======== Includes  ======== */
/* =========================== */
#include <windows.h>
#include <stdio.h>

/* =========================== */
/* ======== Constants ======== */
/* =========================== */
const char* str_authors = "Leonid Sawin, Mazen Ibrahim, Vlad Podar, Lukasz Glowka, Maciek Zadlo";
const char* str_title = "EPFU Carcassonne Project";

/* =========================== */
/* ========  Globals  ======== */
/* =========================== */

// App's main return code
int app_returns;

// File Handles
FILE *fh_board = NULL;
FILE *fh_board_input = NULL;
FILE *fh_board_output = NULL;

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
	Print out usage options
*/
void print_usage()
{
	// TODO
}

/*!
	Parse arguments for the Auto-Mode
*/
void parse_args_auto_mode(int argc, char** argv)
{
	const char* err_file_open = "Can't open file: ";
	const char* file_mode_write = "wb";
	const char* file_mode_read = "rb";
	
	// Open the Board file
	fh_board = fopen(argv[1], file_mode_read);
	if (fh_board == NULL) 
	{
		app_returns -1;
		printf("%s'%s'", err_file_open, argv[1]);
		return;
	}
	
	// Open the Input file
	fh_board_input = fopen(argv[2], file_mode_read);
	if (fh_board_input == NULL) 
	{
		app_returns -1;
		printf("%s'%s'", err_file_open, argv[2]);
		return;
	}
	
	// Open the Output file
	fh_board_output = fopen(argv[3], file_mode_write);
	if (fh_board_output == NULL) 
	{
		app_returns -1;
		printf("%s'%s'", err_file_open, argv[3]);
		return;
	}
	
	// #Goal #1: since we passed all error checks, now it's time to run one iteration of the game.
	// ...
	// Here
	// ...
	
	// Clean-up and dispose the file handles
	fclose(fh_board);
	fclose(fh_board_input);
	fclose(fh_board_output);
}

/*!
	Parse the input arguments
*/
void parse_args(int argc, char **argv)	
{
	const char* str_arg_authors = "/authors";
	// Goal #1: Determine what to do (mode, it's dependent arglist)
	// Goal #2: Call the appropriate function.
	
	switch (argc)
	{
		case 4:
			parse_args_auto_mode(argc, argv);
			break;		
			
		case 2:	
			// Warning #1: strcmp is case-sensitive.
			// Warning #2: strcmp returns 0 for Matching Strings.
			if (strcmp(argv[1], str_arg_authors) == 0)
				print_authors();
			else
				print_usage();
			break;
			
		default: 
			print_usage();
			break;
	}
}

#endif