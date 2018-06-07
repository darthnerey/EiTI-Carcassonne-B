#include "TilePool.h"

ListRef AllocList(const TileRef tile)
{
	ListRef result = (ListRef)malloc(sizeof(List));
	if (result == NULL) return NULL;
	result->Prev = NULL;
	result->Next = NULL;
	result->Tile = tile;
	return result;
}

ListRef GenerateList(const int32_t size)
{
	if (size < 1 || size > 1024)
	{
		printf("TileGen: Improper size - it should be a number between 1 and 1024\n");
		return NULL;
	}

	ListRef List = NULL;

	for (int32_t i = 0; i < size; i++)
	{
		if (List == NULL)
		{
			List = AllocList(AllocTile());
			List->Tile = AllocRandomTile();
		}

		if (i + 1 < size)
		{
			List->Next = AllocList(AllocRandomTile());
			if (List->Next != NULL)
			{
				List->Next->Prev = List;
				List = List->Next;
			}
			else
			{
				printf("TileGen: Error allocating another tile\n");
				return NULL;
			}
		}
	}

	return FirstInList(List);
}

ListRef ListPopRandom(ListRef* list)
{
	ListRef pointer = *list;
	if (pointer == NULL) return NULL;
	pointer = FirstInList(pointer);
	int32_t size = ListSize(pointer);
	int32_t index = Random(0, size);
	ListRef node = IndexInList(pointer, index);
	ListRef result = node;
	*list = node;
	if (RemoveList(list))
		return result;
	return NULL;
}

int32_t ListSize(const ListRef list)
{
	int32_t counter = 0;
	ListRef node = list;
	while (node != NULL)
	{
		node = node->Next;
		++counter;
	}
	return counter;
}

ListRef LastInList(const ListRef list)
{
	if (list == NULL)
		return NULL;
	ListRef node = list;
	do
	{
		if (node->Next != NULL)
			node = node->Next;
		else break;
	} while (true);
	return node;
}

ListRef FirstInList(const ListRef list)
{
	if (list == NULL)
		return NULL;
	ListRef node = list;
	do
	{
		if (node->Prev != NULL)
			node = node->Prev;
		else break;
	} while (true);
	return node;
}

ListRef IndexInList(const ListRef list, const int32_t index)
{
	if (list == NULL)
		return NULL;
	ListRef root = FirstInList(list);
	int32_t size = ListSize(root);
	if (size <= index)
		return NULL;
	ListRef node = root;
	int32_t counter = 1;
	while (counter <= index)
	{
		node = node->Next;
		++counter;
	}
	return node;
}

bool FreeList(ListRef* list)
{
	ListRef pointer = *list;
	if (pointer == NULL)
		return false;
	if (RemoveList(list))
	{
		free(pointer);
		return true;
	}
	return false;
}

bool RemoveList(ListRef* list)
{
	ListRef node = *list;
	if (node == NULL)
		return false;
	ListRef next = node->Next;
	ListRef prev = node->Prev;
	if (next != NULL) next->Prev = prev;
	if (prev != NULL) prev->Next = next;
	node->Next = NULL;
	node->Prev = NULL;
	if (next != NULL) {
		*list = next;
		return true;
	}
	if (prev != NULL) {
		*list = prev;
		return true;
	}
	*list = NULL;
	return true;
}

bool InsertBeforeList(ListRef node, ListRef before)
{
	if (node == NULL)
		return false;
	if (before == NULL)
		return false;

	node->Next = before;
	node->Prev = before->Prev;

	before->Prev = node;

	if (node->Prev != NULL)
		node->Prev->Next = node;

	return true;
}

bool InsertAfterList(ListRef node, ListRef after)
{
	if (node == NULL)
		return false;
	if (after == NULL)
		return false;

	node->Prev = after;
	after->Next = node;

	return true;
}

