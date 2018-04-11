/* =========================== */
/* ======== Includes  ======== */
/* =========================== */

#include "file_io.h"

/* =========================== */
/* ======== Functions ======== */
/* =========================== */

/*!
	Reads board data from a file
*/
bool read_board(char* path, Board* board)
{
	const char* err_file_open = "Can't open file: ";
	const char* file_mode_read = "rb";
	FILE* handle;
	
	handle = fopen(argv[1], file_mode_read);
	if (handle == NULL) 
	{
		app_returns -1;
		printf("%s'%s'", err_file_open, path);
		return;
	}

	// ...
	
	fclose(handle);
}

/*!
	Writes board data into a file
*/
bool write_board(char* path, const Board* board)
{
	const char* err_file_open = "Can't open file: ";
	const char* file_mode_write = "wb";
	FILE* handle;
	
	handle = fopen(argv[1], file_mode_write);
	if (handle == NULL) 
	{
		app_returns -1;
		printf("%s'%s'", err_file_open, path);
		return;
	}
	
	// ...
	
	fclose(handle);
}