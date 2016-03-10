#include "SudokoProject.h"

//input: pointer of PLAYERSList.
//return: True if the list is empty, false otherwise.
BOOL isEmptyPLAYERSList(PLAYERSList* lst)
{
	if (lst->head == NULL)
		return TRUE;
	else
		return FALSE;
}

//input: pointer of PLAYERSList.
//this function make empty PLAYERSList.
void makeEmptyPLAYERSList(PLAYERSList* lst)
{
	lst->head = lst->tail = NULL;
}

//input: pointers of: player, the next node, the previous node.
//this function create new PLAYERSListNode.
PLAYERSListNode* createNewPLAYERSListNode(Player* player, PLAYERSListNode* next, PLAYERSListNode* prev)
{
	PLAYERSListNode* res;
	res = (PLAYERSListNode*)malloc(sizeof(PLAYERSListNode));
	CheckPlayerListNodeAllocation(res); //check allocation.
	res->player = player;
	res->next = next;
	res->prev = prev;
	return res;
}

//input: pointers of: PLAYERSList, Player.
//this function insert Player to the end of PLAYERSList.
void insertPlayerToEndPLAYERSList(PLAYERSList* lst, Player* player)
{
	PLAYERSListNode* newTail; //for the new node of this player.
	newTail = createNewPLAYERSListNode(player, NULL, NULL); //create this node.
	insertNodeToEndPLAYERSList(lst, newTail); //insert this node to the end of the list.
}

//input: pointers of: PLAYERSList, PLAYERSListNode.
//this function insert PLAYERSListNode to the end of PLAYERSList.
void insertNodeToEndPLAYERSList(PLAYERSList* lst, PLAYERSListNode* Tail)
{
	if (isEmptyPLAYERSList(lst) == TRUE)
	{
		Tail->next = Tail->prev = NULL;
		lst->head = Tail;
		lst->tail = Tail;
	}
	else
	{
		Tail->next = NULL;
		Tail->prev = lst->tail;
		lst->tail->next = Tail;
		lst->tail = Tail;
	}
}

//input: pointer of PLAYERSListNode.
//this function free this PLAYERSListNode.
void freePLAYERSListNode(PLAYERSListNode* node)
{
	free(node->player->name); //free the player name.
	FreePD(node->player->PossibleDigits); //free the possible digits array of this player.
	free(node->player); //free player.
	free(node); //free the node of the list.
}

//input: pointer of PLAYERSList.
//this function free this PLAYERSList.
void freePLAYERSList(PLAYERSList* lst)
{
	PLAYERSListNode *curr, *saver; //for curr and saver.
	curr = lst->head; //curr is the first node in the list.
	while (curr != NULL) //for all the nodes in the list.
	{
		saver = curr->next; //saver is curr->next.
		freePLAYERSListNode(curr); //free curr (and all the allocattions inside him).
		curr = saver; //curr is saver.
	}
	free(lst); //free the list.
}

//input: pointers of: PLAYERSList, PLAYERSListNode
//this function delete this node from the list.
void deleteNodeFromPLAYERSList(PLAYERSList* lst, PLAYERSListNode* node)
{
	if (lst->head == node && lst->tail == node) //if this is the only node in the list
	{
		lst->head = lst->tail = NULL;
	}
	else if (lst->head == node) //if this is the first node in the list
	{
		lst->head = node->next;
		lst->head->prev = NULL;
	}
	else if (lst->tail == node) //if this is the last node in the list
	{
		lst->tail = node->prev;
		lst->tail->next = NULL;
	}
	else //if the node is in the middle of the list
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	freePLAYERSListNode(node); //free this node.
}


//input: pointers of: PLAYERSList, PLAYERSListNode
//this function delete this node from the list but doesn't free the player.
void deleteNodeFromPLAYERSListWithoutfreePlayer(PLAYERSList* lst, PLAYERSListNode* node)
{
	if (lst->head == node && lst->tail == node) //if this is the only node in the list
	{
		lst->head = lst->tail = NULL;
	}
	else if (lst->head == node) //if this is the first node in the list
	{
		lst->head = node->next;
		lst->head->prev = NULL;
	}
	else if (lst->tail == node) //if this is the last node in the list
	{
		lst->tail = node->prev;
		lst->tail->next = NULL;
	}
	else //if the node is in the middle of the list
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
}

//input: poiter of PCList.
//return: TRUE if the list is empty, FALSE otherwise.
BOOL isEmptyPCList(PCList* lst)
{
	if (lst->head == NULL)
		return TRUE;
	else
		return FALSE;
}

//input: poiter of PCList.
//this function make PCList empty.
void makeEmptyPCList(PCList* lst)
{
	lst->head = lst->tail = NULL;
	lst->size = 0;
}

//input: CellPlace, pointers of PCListNODEs (the next and prev nodes).
//return: pointer of newPCListNODE.
PCListNODE* CreateNewPCListNODE(CellPlace cp, PCListNODE* next, PCListNODE* prev)
{
	PCListNODE* res; //the result.
	res = (PCListNODE*)malloc(sizeof(PCListNODE)); //allocate the result.
	CheckPCListNodeAllocation(res); //check allocation.
	res->place = cp; //res->place is cp.
	res->next = next; //res->next is next.
	res->prev = prev; //res->prev is prev.
	return res; //return res.
}

//input: poiter of PCList and CellPlace.
//this function insert CellPlace to the end of the list.
void insertCPtoEndOfPCList(PCList* lst, CellPlace cp)
{
	PCListNODE* newTail; //for the new node.
	newTail = CreateNewPCListNODE(cp, NULL, NULL); //create the new node.
	insertNodeToEndPCList(lst, newTail); //insert it to the end of the list.
}

//input: poiters of: PCList, PCListNODE.
//this function insert node to the end of the list.
void insertNodeToEndPCList(PCList* lst, PCListNODE* newTail)
{
	if (isEmptyPCList(lst) == TRUE) //if the list is empty.
	{
		lst->head = lst->tail = newTail;
		newTail->next = NULL;
		newTail->prev = NULL;
	}
	else //else
	{
		lst->tail->next = newTail;
		newTail->prev = lst->tail;
		newTail->next = NULL;
		lst->tail = newTail;
	}
	lst->size++; //add 1 to list size.
}

//input: pointer of PCList and place in the list.
//return the PCListNode in this place.
PCListNODE* getPCListNode(PCList* lst, int place)
{
	PCListNODE* curr; //for the node.
	curr = lst->head;
	if (isEmptyPCList(lst) == TRUE || place > lst->size) //if the list isi empty or place is bigger than the size of the list return NULL.
		return NULL;
	else
	{
		while (place > 0) //else go to the place.
		{
			curr = curr->next;
			place--;
		}
	}
	return curr; //return the node.
}

//input: pointers of PCList and PCListNODE
//this function delete PCListNODE from PCList.
void deleteNodeFromPCList(PCList* lst, PCListNODE* node)
{
	if (lst->head == node && lst->tail == node) //if this is the only node in the list
	{
		lst->head = lst->tail = NULL;
	}
	else if (lst->head == node) //if this is the first node in the list
	{
		lst->head = node->next;
		lst->head->prev = NULL;
	}
	else if (lst->tail == node) //if this is the last node in the list
	{
		lst->tail = node->prev;
		lst->tail->next = NULL;
	}
	else //if the node is in the middle of the list
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	lst->size--; //minus 1 from the size of lst.
}
//input: poiter of PCList.
//this function free the list.
void freePCList(PCList* lst)
{
	PCListNODE* curr, *saver;
	curr = lst->head;
	while (curr != NULL)
	{
		saver = curr->next;
		free(curr);
		curr = saver;
		lst->size--;
	}
}

//input: empty PCList.
//this function build new pclist (all the cell's places of sudoko board).
void BuildNewPCList(PCList* lst)
{
	int i, j; //for index.
	CellPlace cp; //for cell place.
	for (i = 0; i < COLUMNSIZE; i++) //for all the rows.
	{
		for (j = 0; j < ROWSIZE; j++) //for all the cells in this row.
		{
			cp.R = i; //i is the number of the row.
			cp.C = j; //j is the number of the column.
			insertCPtoEndOfPCList(lst, cp);
		}
	}
}

//this function check allocation of PLAYERSLIST.
void CheckPlayerListAllocation(PLAYERSList* lst)
{
	if (lst == NULL)
	{
		printf("ERROR ALLOCAION DIDN'T SUCCEED!\n");
		exit(1);
	}
}

//this function check allocation fo PLAYERSListNode.
void CheckPlayerListNodeAllocation(PLAYERSListNode* node)
{
	if (node == NULL)
	{
		printf("ERROR ALLOCAION DIDN'T SUCCEED!\n");
		exit(1);
	}
}
//this function check allocation of PCListNODE.
void CheckPCListNodeAllocation(PCListNODE* node)
{
	if (node == NULL)
	{
		printf("ERROR ALLOCAION DIDN'T SUCCEED!\n");
		exit(1);
	}
}

//input: pointer of player list.
//this function create file (his name is the  define WINNER_LIST_FILE_NAME) of all the winners in the game.
//including their names and their finished sudoko boards.
void PrintPLAYERSListToFile(PLAYERSList* lst)
{
	FILE* fp; //for the file of the winners list.
	PLAYERSListNode* curr; //for index of the list.
	fp = fopen(WINNER_LIST_FILE_NAME, "w"); //open the file in write mode.
	fputs("Winners List:\n", fp);
	curr = lst->head; //curr is the first node in the list.
	while (curr != NULL) //for all the nodes in the list.
	{
		fprintf(fp, "Player Name: %s \n", curr->player->name); //insert thier name.
		fprintf(fp, "Player Board:\n"); //insert their sudoko board.
		sudokoPrintBoardToFile(fp, curr->player->board);
		curr = curr->next; //move to the next node.
	}
	fclose(fp); //close the file.
}