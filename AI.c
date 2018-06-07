#include "AI.h"

bool AIMove(BoardRef board, ListRef* tiles)
{
	if (!AISmartMove(board, tiles))
		return AIRandomMove(board, tiles);
	return true;
}

bool AISmartMove(BoardRef board, ListRef* tiles)
{
	ListRef List = *tiles;
	do
	{
		TileRef Tile = List->Tile;
		Point at;
		at.X = 0;
		at.Y = 0;

		for (at.X = 0; at.X < board->Size.W; at.X++)
		{
			for (at.Y = 0; at.Y < board->Size.H; at.Y++)
			{
				if (TileExists(board, at))
					continue;
				else
				{
					Point pT;
					pT.X = at.X;
					pT.Y = at.Y - 1;
					TileRef tT = GetTile(board, pT);

					Point pB;
					pB.X = at.X;
					pB.Y = at.Y + 1;
					TileRef tB = GetTile(board, pB);

					Point pL;
					pL.Y = at.Y;
					pL.X = at.X - 1;
					TileRef tL = GetTile(board, pL);

					Point pR;
					pR.Y = at.Y;
					pR.X = at.X + 1;
					TileRef tR = GetTile(board, pR);

					if (tT == NULL && tB == NULL && tL == NULL && tR == NULL)
						continue;

					if (tT != NULL && Tile->Top == tT->Bottom)
					{
						if (TryPlaceTile(board, List->Tile, at)) {
							*tiles = List;
							FreeList(tiles);
							return true;
						}
					}
					if (tB != NULL && Tile->Bottom == tB->Top)
					{
						if (TryPlaceTile(board, List->Tile, at)) {
							*tiles = List;
							FreeList(tiles);
							return true;
						}
					}
					if (tL != NULL && Tile->Left == tL->Right)
					{
						if (TryPlaceTile(board, List->Tile, at)) {
							*tiles = List;
							FreeList(tiles);
							return true;
						}
					}
					if (tR != NULL && Tile->Right == tR->Left)
					{
						if (TryPlaceTile(board, List->Tile, at)) {
							*tiles = List;
							FreeList(tiles);
							return true;
						}
					}
				}
			}
		}

		List = List->Next;
	} while (List != NULL);
	return false;
}

bool AIRandomMove(BoardRef board, ListRef* tiles)
{
	ListRef pointer = FirstInList(*tiles);
	if (pointer != NULL)
	{
		ListRef List = ListPopRandom(tiles);
		Point Position;
		Position.X = 0;
		Position.Y = 0;

		if (board->Tiles == NULL)
		{
			if (!TryPlaceTile(board, List->Tile, Position))
			{
				printf("Unknown error while initializing the board!\n");
				return false;
			}
		}
		else
		{
			Rectangle bounds = GetBoardBounds(board);

			Position = RandomPosition(bounds); 
			bounds = MarginRectangle(bounds, 1);

			while (!TryPlaceTile(board, List->Tile, Position))
				Position = RandomPosition(bounds);
		}
		
		FreeList(&List);
		return true;
	}
	else
	{
		printf("No tiles available!\n");
		return false;
	}
}