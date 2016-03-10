#include "SudokoProject.h"

//input: data, pointers of left and right tree nodes.
//this function create new tree node.
TreeNode* CreateNewTreeNode(PLAYERSListNode* data, TreeNode* left, TreeNode* right)
{
	TreeNode* res; //for the new tree node.
	res = (TreeNode*)malloc(sizeof (TreeNode)); //allocate.
	CheckTreeNodeAllocation(res); //check allocation.
	res->data = data; //insert data to res->data.
	res->left = left; //res->left is left.
	res->right = right; //res->right is right.
	return res;
}

//input: pointer of tree node.
//this function check if allocation succeed.
void CheckTreeNodeAllocation(TreeNode* node)
{
	if (node == NULL)
	{
		printf("Allocation Faild!\n");
		exit(1);
	}
}

//input: array if ints, his size.
//return: Tree.
Tree BuildTreeFromArray(PLAYERSListNode** arr, int size)
{
	Tree res; //for the tree.
	res.root = BuildTreeFromArrayHelper(arr, 0, size - 1); //call BuildTreeFromArrayHelper with the array, his first place, his last place.
	return res;
}

//input: array, first place, last place.
//this function build tree from the array.
TreeNode* BuildTreeFromArrayHelper(PLAYERSListNode** arr, int first, int last)
{
	TreeNode *root, *right, *left;
	int middle;
	if (first > last) //if the array is empty exit.
	{
		return NULL;
	}

	else if (first == last) //if there is just 1 value in the array.
	{
		root = CreateNewTreeNode(arr[first], NULL, NULL); // Create new tree node from his value (no childrens because this his the only node in the tree).
	}

	else
	{
		middle = (first + last) / 2; //get middle place.
		left = BuildTreeFromArrayHelper(arr, first, middle-1); //build tree from the left side of the array.
		right = BuildTreeFromArrayHelper(arr, middle+1, last); //build tree from the right side of the array.
		root = CreateNewTreeNode(arr[middle], left, right); //create new tree node with his value, his ft is left, his right is right.
	}
	return root;
}

//this function free Tree.
void freeTree(Tree tr)
{
	freeTreeHelper(tr.root);
	tr.root = NULL;
}

//input: root (TreeNode*)
//this function free tree.
void freeTreeHelper(TreeNode* root)
{
	if (root == NULL) //if the tree is empty exit.
		return;
	else
	{
		freeTreeHelper(root->left); //free the left side.
		freeTreeHelper(root->right); //free the right side.
		free(root); //free root.
	}
}
