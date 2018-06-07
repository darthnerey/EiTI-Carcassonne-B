#include "Utils.h"

void ClearScreen(void)
{
#if LINUX
	system("clear");
#else
	system("cls");
#endif
}

Rectangle CreateRectangle(const Size s)
{
	Rectangle result;
	result.Max.X = s.W;
	result.Max.Y = s.H;
	result.Min.X = 0;
	result.Min.Y = 0;
	return result;
}

Rectangle MarginRectangle(const Rectangle r, const uint32_t m)
{
	Rectangle result;
	result.Min.X = r.Min.X - m;
	result.Min.Y = r.Min.Y - m;
	result.Max.X = r.Max.X + m;
	result.Max.Y = r.Max.Y + m;
	return result;
}

bool ContainsPoint(const Rectangle r, const Point p)
{
	return r.Max.X >= p.X
		&& r.Min.X <= p.X
		&& r.Max.Y >= p.Y
		&& r.Min.Y <= p.Y;
}

Point RandomPosition(const Rectangle within)
{
	Point result;
	result.X = Random(within.Min.X, within.Max.X + 1);
	result.Y = Random(within.Min.Y, within.Max.Y + 1);
	return result;
}

Size RectangleSize(const Rectangle r)
{
	Size result;
	result.W = r.Max.X - r.Min.X;
	result.H = r.Max.Y - r.Min.Y;
	return result;
}

int32_t RectangleWidth(const Rectangle r)
{
	return r.Max.X - r.Min.X;
}

int32_t RectangleHeight(const Rectangle r)
{
	return r.Max.Y - r.Min.Y;
}

int32_t Abs(int32_t x)
{
	return x > 0 ? x : -x;
}

int32_t Max(int32_t a, int32_t b)
{
	return a > b ? a : b;
}

int32_t Min(int32_t a, int32_t b)
{
	return a > b ? b : a;
}

int32_t Random(int32_t min, int32_t max)
{
	int32_t range = max - min;
	return rand() % range + min;
}

int32_t IndexOf(const char chr, const char* str)
{
	int32_t i = 0, length = strlen(str);
	for (; i < length; i++)
	{
		if (str[i] == chr)
			return i;
	}
	return -1;
}

int32_t IndexOfAny(const char* str, const char* chars)
{
	int32_t i = 0, j, length = strlen(chars);
	for (; i < length; i++)
	{
		j = IndexOf(chars[i], str);
		if (j > -1) return j;
	}
	return -1;
}