#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
typedef struct TREE TREE;
typedef TREE* TREE_P;


struct TREE {

	void* obj;

	TREE_P childs;
	TREE_P siblings;


};

TREE_P TREE_add_child(TREE_P tree, void* obj, size_t obj_size);
TREE_P TREE_add_child_TREE(TREE_P tree, TREE_P tree_append);
TREE_P TREE_create_TREE(void* obj, size_t obj_size);