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
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
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
}

/*!
	Parse arguments for the User-Mode
*/
void parse_args_user_mode(int argc, char** argv)
{
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
		case 3:
			parse_args_user_mode(argc, argv);
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