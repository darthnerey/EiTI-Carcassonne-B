#include "FileIO.h"

bool SaveBoard(const BoardRef board, const char* path)
{
	if (board == NULL)
		return false;

	FILE* handle = NULL;

	if ((handle = fopen(path, file_mode_write)) == NULL)
	{
		printf("%s'%s'\n", file_error_open, path);
		return false;
	}

	Point point;
	Size size = GetBoardSize(board);

	for (point.Y = 0; point.Y < size.H; point.Y++)
	{
		for (point.X = 0; point.X < size.W; point.X++)
		{
			TileRef Tile = GetTile(board, point);
			if (Tile == NULL)
			{
				fprintf(handle, "\t");
			}
			else
			{
				for (int32_t Z = 0; Z < TileParts; Z++) {
					fprintf(handle, "%c", Tile->Parts[Z]);
				}
			}
			if (point.X + 1 < size.W) fprintf(handle, " ");
		}
		if (point.Y + 1 < size.H) fprintf(handle, "\n");
	}

	fclose(handle);

	return true;
}

bool SaveList(const ListRef list, const char* path)
{
	FILE* handle = NULL;

	if ((handle = fopen(path, file_mode_write)) == NULL)
	{
		printf("%s'%s'\n", file_error_open, path);
		return false;
	}

	ListRef node = list;
	node = FirstInList(list);

	while (node != NULL)
	{
		for (int32_t i = 0; i < TileParts; i++)
			fputc(node->Tile->Parts[i], handle);

		node = node->Next;

		if (node != NULL)
			fputc('\n', handle);
	}

	fclose(handle);

	return true;
}

BoardRef LoadBoard(const char* path)
{
	if (!FileExists(path))
	{
		printf("File '%s' doesn't exist!\n", path);
		return NULL;
	}

	FILE* handle = NULL;

	if ((handle = fopen(path, file_mode_read)) == NULL)
	{
		printf("%s'%s'\n", file_error_open, path);
		return NULL;
	}

	BoardRef board = (BoardRef)malloc(sizeof(Board));
	board->Tiles = NULL;
	board->Size.W = 0;
	board->Size.H = 0;
	board->Score = 0;

	Point position;
	position.X = 0;
	position.Y = 0;

	do
	{
		int32_t Char = fgetc(handle);

		if (Char == EOF)
			break;

		if (Char == ' ') {
			position.X++;
			continue;
		}

		if (Char == '\n')
		{
			position.X = 0;
			position.Y++;
			continue;
		}

		if (Char == '\t') 
			continue;

		TileRef Tile = AllocTile();
		for (int32_t i = 0; i < TileParts; i++)
		{
			if (IndexOf(Char, TileSymbols) == -1)
			{
				printf("%s '%s'", file_error_read, path);
				fclose(handle);
				return NULL;
			}
			Tile->Parts[i] = Char;
			if (i + 1 < TileParts)
				Char = fgetc(handle);
		}

		if (TryPlaceTile(board, Tile, position))
			continue;
		else
		{
			if (TileExists(board, position))
				printf("There's a tile there already! ");
			printf("Couldn't place a tile on the board!\n");
			fclose(handle);
			return NULL;
		}
	} while (true);

	fclose(handle);

	return board;
}

ListRef LoadList(const char* path)
{
	if (!FileExists(path))
	{
		printf("File '%s' doesn't exist!\n", path);
		return NULL;
	}

	FILE* handle = NULL;

	if ((handle = fopen(path, file_mode_read)) == NULL)
	{
		printf("%s'%s'\n", file_error_open, path);
		return NULL;
	}

	ListRef list = NULL;
	int32_t Char;

	do
	{
		Char = fgetc(handle);

		if (Char == EOF)
			break;

		if (isspace(Char))
			continue;

		if (list == NULL)
			list = AllocList(AllocTile());

		for (int32_t i = 0; i < TileParts; i++)
		{
			if (IndexOf(Char, TileSymbols) == -1)
			{
				printf("%s '%s'", file_error_read, path);
				fclose(handle);
				return NULL;
			}
			list->Tile->Parts[i] = Char;
			if (i + 1 < TileParts)
				Char = fgetc(handle);
		}

		list->Next = AllocList(AllocTile());
		list->Next->Prev = list;
		list = list->Next;

	} while (true);

	ListRef excess = list;
	FreeTile(&excess->Tile);
	list = FirstInList(list);
	FreeList(&excess);

	return list;
}

bool FileExists(const char* path)
{
	FILE *file;
	if (file = fopen(path, file_mode_read)) {
		fclose(file);
		return 1;
	}
	return false;
}
