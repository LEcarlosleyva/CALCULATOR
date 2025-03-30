#include "TREE.h"



TREE_P TREE_create_TREE(void * obj,size_t obj_size) {
	TREE_P tmp = malloc(sizeof(TREE));
	if (tmp == NULL) {
		return NULL;
	}
	tmp->obj = malloc(obj_size);
	if (tmp->obj == NULL) {
		return NULL;
	}
	if (obj == NULL) {
		return NULL;
	}
	if (memmove(tmp->obj, obj, obj_size) == NULL) {
		return NULL;
	}
	tmp->childs = NULL;
	tmp->siblings = NULL;
	return tmp;
}


TREE_P TREE_add_child(TREE_P tree,void * obj, size_t obj_size) {
	if (tree == NULL) {
		return NULL;
	}
	
	TREE_P current_TREE;
	if(tree->childs == NULL) {
		tree->childs = TREE_create_TREE(obj, obj_size);
		if (tree->childs == NULL) {
			return NULL;
		}
		return tree->childs;
	}
	else {
		current_TREE = tree->childs;
		while (current_TREE->siblings != NULL) {
			current_TREE = current_TREE->siblings;
		}
		current_TREE->siblings = TREE_create_TREE(obj, obj_size);
		if (current_TREE->siblings == NULL) {
			return NULL;
		}
		return current_TREE->siblings;
	}
}

TREE_P TREE_add_child_TREE(TREE_P tree, TREE_P tree_append) {
	if (tree == NULL) {
		return NULL;
	}

	TREE_P current_TREE;
	if (tree->childs == NULL) {
		tree->childs = tree_append;
		if (tree->childs == NULL) {
			return NULL;
		}
		return tree->childs;
	}
	else {
		current_TREE = tree->childs;
		while (current_TREE->siblings != NULL) {
			current_TREE = current_TREE->siblings;
		}
		current_TREE->siblings = tree_append;
		if (current_TREE->siblings == NULL) {
			return NULL;
		}
		return current_TREE->siblings;
	}
}



