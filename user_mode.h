#pragma once
#ifndef _USER_H
#define _USER_H 1

/* =========================== */
/* ======== Includes  ======== */
/* =========================== */

#include "Utils.h"

/* =========================== */
/* ======== Structures ======= */
/* =========================== */

typedef struct UsrCmd
{
	void* Method;
	char* String;
	char* Help;
} UsrCmd;

/* =========================== */
/* ======== Functions ======== */
/* =========================== */

/*!
Registers a User-Mode command
*/
bool RegUsrCmd(void* method, char* str, char* help);

/*!
Finds a User-Mode command and returns a pointer to it
*/
UsrCmd* GetUsrCmd(const char* input);

/*!
Prints out User-Mode command help
*/
void PrintUsrCmdHelp(void);

/*!
Initialize user mode
*/
void init_user_mode();

/*!
Process one command from user's input
*/
void process_input();

/*!
Enter an input processing loop
*/
void input_loop();

#endif