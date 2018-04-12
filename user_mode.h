#pragma once
#ifndef _USER_MODE_H
#define _USER_MODE_H 1

/* =========================== */
/* ======== Includes  ======== */
/* =========================== */

#include <stdio.h>

/* =========================== */
/* ======== Functions ======== */
/* =========================== */

/*!
	Process one command from user's input
*/
void process_input();

/*!
	Enter an input processing loop
*/
void input_loop();

#endif