#pragma once
#ifndef _UTILS_H
#define _UTILS_H 1

/* =========================== */
/* ======== Includes  ======== */
/* =========================== */

#include <Windows.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/* =========================== */
/* ======== Structures ======= */
/* =========================== */

typedef struct Point2
{
	int32_t X;
	int32_t Y;
} Point2;

typedef struct Rect2
{
	Point2 Min;
	Point2 Max;
} Rect2;

typedef struct Size2
{
	int32_t Width;
	int32_t Height;
} Size2;

/* =========================== */
/* ======== Functions ======== */
/* =========================== */

int32_t Rect2Width(Rect2 R);
int32_t Rect2Height(Rect2 R);
int32_t Max(int32_t A, int32_t B);
int32_t Min(int32_t A, int32_t B);
Rect2 Intersect(Rect2 A, Rect2 B);
Rect2 Contain(Rect2 R, Point2 P);
Size2 Rect2Size(Rect2 R);
bool Contains(Rect2 R, Point2 P);
bool Rect2Equals(Rect2 A, Rect2 B);
bool Point2Equals(Point2 A, Point2 B);

void ClearConsole();
void LowerCase(char* str, int32_t len);

#endif