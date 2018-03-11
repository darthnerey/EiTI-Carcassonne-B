// Dump your includes and other stuff here, under <windows.h>
// Otherwise, keep this file clean, neat and utility-only.
// -- Lemur

#pragma once
#ifndef _BASE_H 1
#define _BASE_H 1

/* =========================== */
/* ======== Includes  ======== */
/* =========================== */
#include <windows.h>

/* =========================== */
/* ======== Constants ======== */
/* =========================== */
const char* str_authors = "Leonid Sawin, Mazen Ibrahim, Vlad Podar, Łukasz Główka, Maciek Żądło";
const char* str_title = "EPFU Carcassonne Project";

/* =========================== */
/* ========  Globals  ======== */
/* =========================== */
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
	Parse the list of authors
*/
void print_authors()
{
	printf("Authors: %s", str_authors);
}

/*!
	Parse the input arguments
*/
void parse_args(char* args)
{
	// Goal #1: Determine what to do (mode, it's dependant arglist)
	// Goal #2: Call the appropriate function.
}

#endif