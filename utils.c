#include "Utils.h"

int32_t Rect2Width(Rect2 R)
{
	return R.Max.X - R.Min.X;
}

int32_t Rect2Height(Rect2 R)
{
	return R.Max.Y - R.Min.Y;
}

int32_t Max(int32_t A, int32_t B)
{
	return A > B ? A : B;
}

int32_t Min(int32_t A, int32_t B)
{
	return A > B ? B : A;
}

Rect2 Intersect(Rect2 A, Rect2 B)
{
	Rect2 C;
	C.Max.X = Min(A.Max.X, B.Max.X);
	C.Max.Y = Min(A.Max.Y, B.Max.Y);
	C.Min.X = Max(A.Min.X, B.Min.X);
	C.Min.Y = Max(A.Min.Y, B.Min.Y);
	return C;
}

Rect2 Contain(Rect2 R, Point2 P)
{
	if (P.X > R.Max.X)
		R.Max.X = P.X;
	if (P.Y > R.Max.Y)
		R.Max.Y = P.Y;
	if (P.X < R.Min.X)
		R.Min.X = P.X;
	if (P.Y < R.Min.Y)
		R.Min.Y = P.Y;
	return R;
}

Size2 Rect2Size(Rect2 R)
{
	Size2 S;
	S.Width = Rect2Width(R);
	S.Height = Rect2Height(R);
	return S;
}

bool Contains(Rect2 R, Point2 P)
{
	return R.Min.X <= P.X
		&& R.Max.X >= P.X
		&& R.Min.Y <= P.Y
		&& R.Max.Y >= P.Y;
}

bool Rect2Equals(Rect2 A, Rect2 B)
{
	return Point2Equals(A.Min, B.Min) 
		&& Point2Equals(A.Max, B.Max);
}

bool Point2Equals(Point2 A, Point2 B)
{
	return A.X == B.X
		&& A.Y == B.Y;
}

void ClearConsole()
{
#if WINDOWS
	system("cls");
#elseif LINUX
	system("clear");
#endif
}

void LowerCase(char* str, int32_t len)
{
	for (--len; len >= 0; len--) 
		str[len] = tolower(str[len]);
}

