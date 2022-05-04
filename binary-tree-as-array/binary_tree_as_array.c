#include <stdio.h>
#include <stdlib.h>
#include "fancylist.h"

typedef FancyList BinaryTree;

BinaryTree *initialize_tree(int root)
{
	BinaryTree *starting_node = (BinaryTree *)malloc(sizeof(BinaryTree));
	init_fancylist(starting_node, 1);
	starting_node->ptr[0] = root;
	starting_node->count_el++;
	return starting_node;
}

void insert(BinaryTree *bt, int val)
{
	append(bt, val);
}

int search(BinaryTree *bt, int val)
{
	for (int i = 0; i < bt->count_el; i++)
	{
		if (bt->ptr[i] == val)
		{
			return i;
		}
	}
	return -1;
}

void print_binary_tree(BinaryTree *bt)
{
	print_fancy_list(*bt);
}

int get_parent(BinaryTree *bt, int idx)
{
	return bt->ptr[(idx - 1) / 2];
}

int main()
{
	int x;

	x = 10;
	BinaryTree *bt = initialize_tree(x);

	x = 50;
	insert(bt, x);

	x = 19;
	insert(bt, x);

	x = 45;
	insert(bt, x);

	x = 60;
	insert(bt, x);

	x = 18;
	insert(bt, x);

	x = 2;
	insert(bt, x);

	x = 65;
	insert(bt, x);

	x = 15;
	insert(bt, x);

	print_binary_tree(bt);
	fprintf(stdout, "Parent of %d is %d\n", 15, get_parent(bt, 8));
}