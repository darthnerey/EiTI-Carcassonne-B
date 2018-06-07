#include "Drawing.h"

bool PrintListFile(const ListRef list)
{
	if (list == NULL)
		return false;

	ListRef node = FirstInList(list);

	do
	{
		TileRef Tile = node->Tile;
		for (int32_t Z = 0; Z < TileParts; Z++) {
			printf("%c", Tile->Parts[Z]);
		}
		node = node->Next;
		printf("\n");
	} while (node != NULL);

	return true;
}

bool PrintBoardFile(const BoardRef board)
{
	if (board == NULL)
		return false;
	if (board->Tiles == NULL)
		return false;
	
	Point point;
	Size size = GetBoardSize(board);
	for (point.Y = 0; point.Y < size.H; point.Y++)
	{
		for (point.X = 0; point.X < size.W; point.X++)
		{
			TileRef Tile = GetTile(board, point);
			if (Tile == NULL)
			{
				for (int32_t Z = 0; Z < TileParts; Z++) {
					printf("#");
				}
			}
			else
			{
				for (int32_t Z = 0; Z < TileParts; Z++) {
					printf("%c", Tile->Parts[Z]);
				}
			}
			if (point.X + 1 < size.W) printf(" ");
		}
		printf("\n");
	}

	return true;
}

bool PrintBoardGrid(const BoardRef board)
{
	if (board == NULL)
		return false;
	if (board->Tiles == NULL)
		return false;

	Point point;
	Size size = GetBoardSize(board);
	for (point.Y = 0; point.Y < size.H; point.Y++)
	{
		// Scan-Line 0
		for (point.X = 0; point.X < size.W; point.X++)
		{
			TileRef Tile = GetTile(board, point);
			if (Tile == NULL)
				printf("###");
			else 
				printf("#%c#", Tile->Top);
		}
		printf("\n");

		// Scan-Line 1
		for (point.X = 0; point.X < size.W; point.X++)
		{
			TileRef Tile = GetTile(board, point);
			if (Tile == NULL)
				printf("###");
			else
				printf("%c%c%c", Tile->Left, Tile->Middle, Tile->Right);
		}
		printf("\n");

		// Scan-Line 2
		for (point.X = 0; point.X < size.W; point.X++)
		{
			TileRef Tile = GetTile(board, point);
			if (Tile == NULL)
				printf("###");
			else
				printf("#%c#", Tile->Bottom);
		}
		printf("\n");
	}

	return true;
}
