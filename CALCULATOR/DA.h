#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


#define DA_TO_ARR(HANDLER ,at, TYPE) (((TYPE *)HANDLER->contents)[at]) 

//extern size_t number_of_DA_actif; 

typedef struct DA DA;
struct DA {

	void* contents;
	//size_t used_size;
	size_t da_size;
	size_t elem_size;



};
typedef DA* DA_HANDLER_P;

int DA_enlarge_da(DA_HANDLER_P handler, size_t how_many_more_elems);
DA_HANDLER_P DA_create_da(size_t start_size, size_t elem_size);
int DA_store_elems(DA_HANDLER_P handler, size_t at, void* elems, size_t how_many_elems);
int DA_shrink_da(DA_HANDLER_P handler, size_t how_many_less_elems);
int DA_destroy_da(DA_HANDLER_P handler);
int DA_append_elem(DA_HANDLER_P handler, void* elem);
int DA_delete_elem(DA_HANDLER_P handler, size_t at);
DA_HANDLER_P DA_pop_elem(DA_HANDLER_P handler);