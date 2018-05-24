/* =========================== */
/* ======== Includes  ======== */
/* =========================== */

#include "file_io.h"

extern int app_returns;

/* =========================== */
/* ======== Constants ======== */
/* =========================== */

const char* err_file_open = "Can't open file: ";
const char* file_mode_write = "w";
const char* file_mode_read = "r";

/* =========================== */
/* ======== Functions ======== */
/* =========================== */

/*!
Reads board data from a file
*/
bool read_board(char* path, Board* board)
{
	char chr, pchr = '\0';
	Point2 position;
	TileRef tile;
	Size2 size;

	FILE* handle = NULL;
	handle = fopen(path, file_mode_read);
	if (handle == NULL)
	{
		printf("%s'%s'\n", err_file_open, path);
		app_returns = -1;
		return false;
	}

	position.X = 0;
	position.Y = 0;
	size.Width = 0;
	size.Height = 0;

	do
	{
		chr = fgetc(handle);
		if (chr == ' ')
			size.Width++;
		else if (chr == '\n')
		{
			size.Height++;
			size.Width = 0;
		}
	} while (chr != EOF);

	fseek(handle, 0, SEEK_SET);

	freeBoard(&current_board);
	allocBoard(&current_board, size);

	do
	{
		chr = fgetc(handle);

		switch (chr)
		{
		case ' ':
			position.X++;
			break;
		case '\n':
			position.Y++;
			position.X = 0;
			break;
		case '\t':
			// T'was an empty [NULL] tile
			break;
		case T_Field:
		case T_Road:
		case T_Temple:
		case T_City:
		case T_Shield:
		case T_Nothing:
			tile = assertTile(board, position);
			tile->Top = (T_Part)chr;
			tile->Right = (T_Part)(chr = fgetc(handle));
			tile->Bottom = (T_Part)(chr = fgetc(handle));
			tile->Left = (T_Part)(chr = fgetc(handle));
			tile->Middle = (T_Part)(chr = fgetc(handle));
			break;
		default:
			// printf("Unidentified symbol: '%c'", chr);
			break;
		}

		pchr = chr;
	} while (chr != EOF);

	fclose(handle);
	return true;
}

/*!
	Writes board data into a file
*/
bool write_board(char* path, const Board* board)
{
	Point2 position;
	FILE* handle;
	TileRef tile;

	handle = fopen(path, file_mode_write);
	if (handle == NULL)
	{
		printf("%s'%s'\n", err_file_open, path);
		app_returns = -1;
		return false;
	}

	for (position.Y = 0; position.Y < board->Bounds.Max.Y; position.Y++)
	{
		for (position.X = 0; position.X < board->Bounds.Max.X; position.X++)
		{
			tile = getTile(board, position);
			if (tile == NULL)
				fputc('\t', handle);
			else
			{
				fputc(tile->Top, handle);
				fputc(tile->Right, handle);
				fputc(tile->Bottom, handle);
				fputc(tile->Left, handle);
				fputc(tile->Middle, handle);
			}
			fputc(' ', handle);
		}
		fputc('\n', handle);
	}

	fclose(handle);
	return true;
}

TilePool* read_tile_pool(char* path)
{
	TilePool* pool;
	FILE* handle;
	TileRef tile;
	char chr;

	handle = fopen(path, file_mode_read);
	if (handle == NULL)
	{
		printf("%s'%s'\n", err_file_open, path);
		app_returns = -1;
		return NULL;
	}

	pool = allocTilePool();

	do
	{
		chr = fgetc(handle);
		
		switch (chr)
		{
		case ' ':
			// Separator
			break;
		case T_Field:
		case T_Road:
		case T_Temple:
		case T_City:
		case T_Shield:
		case T_Nothing:
			tile = allocTile();
			tile->Top = (T_Part)chr;
			tile->Right = (T_Part)(chr = fgetc(handle));
			tile->Bottom = (T_Part)(chr = fgetc(handle));
			tile->Left = (T_Part)(chr = fgetc(handle));
			tile->Middle = (T_Part)(chr = fgetc(handle));
			insertNextIntoTilePool(pool, tile);
			break;
		default:
			// printf("Unidentified symbol: '%c'", chr);
			break;
		}

	} while (chr != EOF);

	pool = pool->Next;

	return pool;
}

bool write_tile_pool(char* path, const TilePool* pool)
{
	FILE* handle;
	TileRef tile;

	handle = fopen(path, file_mode_write);
	if (handle == NULL)
	{
		printf("%s'%s'\n", err_file_open, path);
		app_returns = -1;
		return false;
	}

	pool = getTilePoolRoot(pool);

	while (pool->Next != NULL)
	{
		tile = pool->Tile;

		if (tile == NULL)
			fputc('\t', handle);
		else
		{
			fputc(tile->Top, handle);
			fputc(tile->Right, handle);
			fputc(tile->Bottom, handle);
			fputc(tile->Left, handle);
			fputc(tile->Middle, handle);
		}

		pool = pool->Next;
	}

	fclose(handle);
	return true;
}
