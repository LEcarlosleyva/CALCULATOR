

#include "DA.h"





DA_HANDLER_P DA_create_da(size_t start_size, size_t elem_size) {


	DA_HANDLER_P da = NULL;

	da = malloc(sizeof(DA));

	if (da == NULL) {
		return NULL;
	}
	
	if (elem_size == 0) {
		return NULL;
	}

	if (start_size == 0) {
		da->contents = NULL;

	}
	else {
		da->contents = malloc(start_size * elem_size);
		if (da->contents == NULL) {

			return NULL;
		}
	}

	da->da_size = start_size;
	da->elem_size = elem_size;

	//number_of_DA_actif++;
	return da;




}


int DA_store_elems(DA_HANDLER_P handler, size_t at, void* elems, size_t how_many_elems) {

	//


	if (handler == NULL) {
		return -1;
	}
	
	if (at + 1 > handler->da_size) {
		return -2; //this restrictions is to ensure that only DA_enalrge can increase the size of the array. 
	}

	if (elems == NULL) {
		return -3;

	}
	if (how_many_elems == 0) {
		return -4;
	}
	int excess_elems = how_many_elems - (handler->da_size - (at + 1) + 1);
	if (excess_elems > 0) {
		int enlarged_correctly = DA_enlarge_da(handler, excess_elems);
		if (enlarged_correctly == 0) {
			memmove((char*)handler->contents + at*(handler->elem_size), elems, how_many_elems * handler->elem_size);

		}
		else {
			return -5;
		}


	}
	else {
		memmove((char*)handler->contents + at * (handler->elem_size), elems, how_many_elems * handler->elem_size);

	}

	return 0;

}



int DA_enlarge_da(DA_HANDLER_P handler, size_t how_many_more_elems) {

	if (handler == NULL) {
		return -1;
	}
	if (how_many_more_elems == 0) {
		return -2;

	}
	void* contents = realloc(handler->contents, (handler->da_size + how_many_more_elems) * handler->elem_size);
	if (contents == NULL) {
		return -3;
	}

	handler->contents = contents;
	handler->da_size = handler->da_size + how_many_more_elems;

	return 0;
}

int DA_shrink_da(DA_HANDLER_P handler, size_t how_many_less_elems) {

	if (handler == NULL) {
		return -1;
	}
	if (how_many_less_elems == 0) {
		return -2;

	}
	if (how_many_less_elems >= handler->da_size) {
		return -3;
	}
	void* contents = realloc(handler->contents, (handler->da_size - how_many_less_elems) * handler->elem_size);
	if (contents == NULL) {
		return -4;
	}

	handler->contents = contents;
	handler->da_size = handler->da_size - how_many_less_elems;

	return 0;
}


int DA_append_elem(DA_HANDLER_P handler, void* elem) {

	if (handler == NULL) {
		return -1;

	}
	if (elem == NULL) {
		return -2;
	}

	if (DA_enlarge_da(handler, 1) != 0) {
		return -3;
	}
	if (DA_store_elems(handler, handler->da_size - 1, elem, 1) != 0) {
		return -4;
	}

	return 0;


}

DA_HANDLER_P DA_pop_elem(DA_HANDLER_P handler) {
	if (handler == NULL) {
		return NULL;
	}

	if (handler->da_size == 0) {
		return NULL;
	}

	DA_HANDLER_P cpy = DA_create_da(0, handler->elem_size);
	if (cpy == NULL) {
		return NULL;
	}
	
	if (DA_append_elem(cpy, (char*)handler->contents + (handler->da_size-1) * (handler->elem_size)) != 0) {
		return NULL;
	}

	DA_shrink_da(handler, 1);
	return cpy;
}


int DA_delete_elem(DA_HANDLER_P handler, size_t at) {
	if (handler == NULL) {
		return -1;
	}
	if (at >= handler->da_size) {
		return -2;
	}
	if (handler->da_size == 0) {
		return -3;
	}

	if (at == handler->da_size - 1) {// we need to handle the ereasure of the last element like this otherwise we could end up copying undefined data into the last element
		if(DA_shrink_da(handler, 1) != 0){
	
			return -4;
		}
	}
	
	if (DA_store_elems(handler, at, (char*)handler->contents + (at + 1) * (handler->elem_size), handler->da_size - (at + 1)) != 0) {
		return -5;
	}
	
	if (DA_shrink_da(handler, 1) != 0) {
		return -6;
	}
	
	return 0;
}

int DA_destroy_da(DA_HANDLER_P handler) {
	if (handler == NULL) {
		return -1;
	}
	if (handler->contents == NULL) {
		return -2;
	}

	free(handler->contents);
	free(handler);
	//number_of_DA_actif--;
	return 0;

}