#pragma once
#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

typedef struct Point
{
	int32_t X;
	int32_t Y;
} Point;

typedef struct Size
{
	int32_t W;
	int32_t H;
} Size;

typedef struct Rectangle
{
	Point Min;
	Point Max;
} Rectangle;

void ClearScreen(void);

Rectangle CreateRectangle(const Size s);
Rectangle MarginRectangle(const Rectangle r, const uint32_t m);

bool ContainsPoint(const Rectangle r, const Point p);

Point RandomPosition(const Rectangle within);

Size RectangleSize(const Rectangle r);

int32_t RectangleWidth(const Rectangle r);
int32_t RectangleHeight(const Rectangle r);

int32_t Abs(int32_t x);
int32_t Max(int32_t a, int32_t b);
int32_t Min(int32_t a, int32_t b);
int32_t Random(int32_t min, int32_t max);

int32_t IndexOf(const char chr, const char* str);
int32_t IndexOfAny(const char* str, const char* chars);
#endif