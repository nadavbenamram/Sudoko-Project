//Sudoko Project By Nadav Ben-Amram.
//id: 203268362

#include "SudokoProject.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void main()
{
	PLAYERSList *ActiveList, *WinnersList; //for active and winners lists.
	Player* newPlayer; //for new player.
	PLAYERSListNode** Active_Arr; //for Array of pointers of the active list nodes.
	Tree ActiveTree; //for Tree of Active Players.
	int x; //the number of the players (input by user).
	char dummy; //for skip \n
	int i; //for index;
	srand(12345); //srand call.
	ActiveList = (PLAYERSList*)malloc(sizeof(PLAYERSList)); //allocate active list.
	CheckPlayerListAllocation(ActiveList); //check allocation.
	makeEmptyPLAYERSList(ActiveList); //make active list empty.
	WinnersList = (PLAYERSList*)malloc(sizeof(PLAYERSList)); //allocate winners list.
	CheckPlayerListAllocation(WinnersList); //check allocation.
	makeEmptyPLAYERSList(WinnersList); //make winner list empty.
	printf("Press the number of the players: \n"); //get number of players form user.
	scanf("%d", &x);
	dummy = getchar(); //skip \n.
	
	printf("Press the names of the players: \n");
	for (i = 0; i < x; i++) //get x players from user into active list.
	{
		newPlayer = CreateNewPlayer(); //Create the player.
		insertPlayerToEndPLAYERSList(ActiveList, newPlayer); //insert him to the end of ActiveList.
	}

	Active_Arr = (PLAYERSListNode**)malloc(x * sizeof(PLAYERSListNode*)); //allocate Active_Arr
	CheckActiveArrAllocation(Active_Arr); //check allocation.

	//copy the pointers of the active list nodes into active_arr.
	CopyPLAYERSListNODEpointersFromListToArray(ActiveList, Active_Arr, x);

	//Merge Active_Arr by the number of the filled cells (or if equal by name).
	mergesort(Active_Arr, 0, x - 1);

	Active_Arr = ExpandActive_Arr(Active_Arr, &x); //Expand Active Arr.

	ActiveTree = BuildTreeFromArray(Active_Arr, x); //Build Active Tree from Active_Arr.

	//while ActiveList isn't empty.
	while (isEmptyPLAYERSList(ActiveList) == FALSE)
	{
		Round(&ActiveTree, ActiveList, WinnersList); //make Round.
	}

	PrintPLAYERSListToFile(WinnersList); //make file of the winners list.

	//free allocations.

	freePLAYERSList(ActiveList);

	freePLAYERSList(WinnersList);

	freeTree(ActiveTree);

}