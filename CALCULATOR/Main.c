


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "DA.h"
#include "TREE.h"

#define SIZE_INPUT_BUFFER 256



typedef enum TOKEN_TYPE {NA,OPERATION,DIGIT, NUMBER,PARENTHESIS} TOKEN_T;
typedef enum  {PLUS,MINUS,TIMES,DIV} OPERATION_T;
typedef size_t DIGIT_T;
typedef enum {LEFT,RIGHT} PARENTHESIS_T;
typedef struct TOKEN_ARR TOKEN_ARR;
typedef struct TOKEN TOKEN;

struct TOKEN {
	TOKEN_T type;
	
	union {
	
		OPERATION_T operation;
	
	
		DIGIT_T digit;

	
		PARENTHESIS_T lorr;
	
	};
};

struct TOKEN_ARR {
	DA_HANDLER_P tokens;
	size_t current_token;

};




#define ASCIIN 256
TOKEN characters[ASCIIN];


int tokenize(char* input, DA_HANDLER_P* output);
int remove_NA(DA_HANDLER_P tokens);

TREE_P PARSE_integer(TOKEN_ARR* tokens);
TOKEN* PARSE_get_current_token(TOKEN_ARR* tokens);
void PARSE_advance(TOKEN_ARR* tokens);
void print_token_type(TOKEN_ARR tokens);

int main() {
	

	for (size_t i = 0; i < ASCIIN; i++) {
		characters[i] = (TOKEN){.type = NA};

	}

	characters['+'] = (TOKEN){ .type = OPERATION,.operation = PLUS};
	characters['-'] = (TOKEN){ .type = OPERATION,.operation = MINUS };
	characters['*'] = (TOKEN){ .type = OPERATION,.operation = TIMES };
	characters['/'] = (TOKEN){ .type = OPERATION,.operation = DIV };
	characters['0'] = (TOKEN){ .type = DIGIT,.digit = 0 };
	characters['1'] = (TOKEN){ .type = DIGIT,.digit = 1 };
	characters['2'] = (TOKEN){ .type = DIGIT,.digit = 2 };
	characters['3'] = (TOKEN){ .type = DIGIT,.digit = 3 };
	characters['4'] = (TOKEN){ .type = DIGIT,.digit = 4 };
	characters['5'] = (TOKEN){ .type = DIGIT,.digit = 5 };
	characters['6'] = (TOKEN){ .type = DIGIT,.digit = 6 };
	characters['7'] = (TOKEN){ .type = DIGIT,.digit = 7 };
	characters['8'] = (TOKEN){ .type = DIGIT,.digit = 8 };
	characters['9'] = (TOKEN){ .type = DIGIT,.digit = 9 };
	characters['('] = (TOKEN){ .type = PARENTHESIS,.lorr = LEFT};
	characters[')'] = (TOKEN){ .type = PARENTHESIS,.lorr = RIGHT};


	char input[SIZE_INPUT_BUFFER] = { 0 };

	printf(">> ");
	fgets(input, SIZE_INPUT_BUFFER, stdin);
	
	
	input[strlen(input) - 1] = '\0'; //gets rid of the trailing newline. 

	printf(">> ");
	printf("%s\n\n", input);


	TOKEN_ARR tokens;
	tokens.current_token = 0;

	tokenize(input, &(tokens.tokens));
	
	remove_NA(tokens.tokens);
	print_token_type(tokens);

	printf("\n\n");
	TOKEN temporary = { .type = NA };
	DA_append_elem(tokens.tokens, &temporary);

	print_token_type(tokens);

	TREE_P integer = PARSE_integer(&tokens);

	size_t res = ((TOKEN*) integer->obj)->digit;
	printf("%zu\n", res);
}



// S  -> E
// E  -> T E' 
// T  -> (E) | N
// E' -> OP T E'|e
// N  -> D N'
// N' -> D N' | e
// D  -> "1" | "2" | "3" | "5" | "6" | "7" | "8" | "9" 
// OP -> "+" | "-" | "*" | "/" 


TOKEN * PARSE_get_current_token(TOKEN_ARR * tokens) {
	if (tokens == NULL) {
		return NULL; 
	}
	return &DA_TO_ARR(tokens->tokens, tokens->current_token, TOKEN);

}
void PARSE_advance(TOKEN_ARR* tokens) {
	tokens->current_token++;

}

/*
TREE_P PARSE_start(TOKEN_ARR* tokens) {
	return PARSE_expresion(tokens);

}


TREE_P PARSE_terminal(TOKEN_ARR * tokens){ 
	TREE_P expr_integer = NULL;
	TOKEN * current_token = PARSE_get_current_token(tokens);
	if (current_token->type == DIGIT) {
		TOKEN* parsed_integer = malloc(sizeof(TOKEN));
		if (parsed_integer == NULL) return NULL;
		parsed_integer->type = DIGIT;
		parsed_integer->digit = PARSE_integer(tokens);
		expr_integer = TREE_create_TREE(parsed_integer);
		return expr_integer;
	}
	else if (current_token->type = PARENTHESIS && current_token->lorr == LEFT) {
		PARSE_advance(tokens);
		expr_integer = PARSE_expresion(tokens);
		if (expr_integer == NULL) {
			return NULL;
		}
		PARSE_advance(tokens);
		current_token = PARSE_get_current_token(tokens);
		if (current_token->type != PARENTHESIS || current_token->lorr != RIGHT) {
			return NULL;
		}

		return expr_integer;
	}
	else {
		return NULL;
	}
	
}



TREE_P PARSE_expresion(TOKEN_ARR* tokens) {
	TREE_P terminal_subexpression = TREE_create_TREE(NULL);
	terminal_subexpression->obj = tokens->tokens;
	if (TREE_add_child(terminal_subexpression, PARSE_terminal(tokens)) == NULL) {
		return NULL;

	}







}

*/

//TODO implement PARSE expresion , PARSE subexpression , PARSE integer
TREE_P PARSE_integer(TOKEN_ARR * tokens) {
	
	size_t acc = 0;
	TOKEN* currenttoken = NULL;
	
	while ((currenttoken = PARSE_get_current_token(tokens))->type == DIGIT) {
		acc *= 10;
		acc += currenttoken->digit;
		PARSE_advance(tokens);

	}
	TOKEN* token = malloc(sizeof(TOKEN));
	if (token == NULL) return NULL;
	token->type = NUMBER;
	token->digit = acc;

	

	TREE_P retval = TREE_create_TREE(token, sizeof(TOKEN));
	if (retval == NULL) return NULL;
	return retval;
}


int tokenize(char* input, DA_HANDLER_P *output) {
	if (input == NULL) return -1; 
	//if (output == NULL) { return -2; }; not needed since the output could be any array. 
	
	DA_HANDLER_P tokens = DA_create_da(0, sizeof(TOKEN));
	if (tokens == NULL) return -3;

	TOKEN temporary = { .type = NA };

	
	for (size_t i = 0; input[i] != 0 && i < SIZE_INPUT_BUFFER; i++) {
		temporary = characters[input[i]];
		if (DA_append_elem(tokens, &temporary) != 0) {
			return -4;
		}

	}
	*output = tokens;
	return 0;



}


int remove_NA(DA_HANDLER_P tokens) {
	if (tokens == NULL) {
		return -1;
	}
	if (tokens->da_size==0) {
		return -2;
	}
	for (size_t i = 0; i < tokens->da_size; i++) {
		if (DA_TO_ARR(tokens, i, TOKEN).type == NA) {
			if (DA_delete_elem(tokens, i) != 0) {
				return -3;
			}
		}


	}
	return -4;
}

void print_token_type(TOKEN_ARR tokens) {
	for (int i = 0; i < tokens.tokens->da_size; i++) {
		if (DA_TO_ARR(tokens.tokens, i, TOKEN).type == DIGIT) {
			printf("D, ");
		}
		else if (DA_TO_ARR(tokens.tokens, i, TOKEN).type == PARENTHESIS) {
			printf("P, ");

		}
		else if (DA_TO_ARR(tokens.tokens, i, TOKEN).type == OPERATION) {
			printf("O, ");
		}
		else if (DA_TO_ARR(tokens.tokens, i, TOKEN).type == NA) {
			printf("NA, ");
		}
		else {
			printf("IDK,");
		}

	}




}

//miscelaneous
int main2() {


	DA_HANDLER_P my_da = DA_create_da(0, sizeof(int));

	int st[10] = { 1,2,3,4,5,6,7,8,9,10 };


	int xd = 20;
	for (int i = 0; i < xd; i++) {
		//DA_store_elems(my_da, my_da->da_size, &i, 1);
		DA_append_elem(my_da, &i);

		//DA_store_elems(my_da, 0, st, 10);
		printf("%d \n", DA_TO_ARR(my_da, i, int));


	}
	/*
	for (int i = xd - 1; i >=0 ; i--) {
		//DA_store_elems(my_da, my_da->da_size, &i, 1);
		DA_HANDLER_P exceselem = DA_pop_elem(my_da);

		//DA_store_elems(my_da, 0, st, 10);
		printf("%d \n", DA_TO_ARR(exceselem, 0, int));
		DA_destroy_da(exceselem);

	}
	*/

	for (int i = 0; i < 4; i++) {

		DA_delete_elem(my_da, 4);
	}

	for (int i = 0; i < my_da->da_size; i++) {
		printf("%d \n", DA_TO_ARR(my_da, i, int));
	}
	DA_destroy_da(my_da);


	return 0;
}


void printtree(TREE_P tree) {
	if (tree == NULL) {
		printf("\n");
		return;

	}
	/*
	if (tree->childs == NULL) {
		printf("-");

	}
	if (tree->siblings == NULL) {
		printf("|");


	}
	*/

	else {
		if (tree->obj != NULL) {
			printf("%d , ", *(int*)tree->obj);
		}


		printtree(tree->childs);
		printf("-");

		printtree(tree->siblings);
		printf("+");
	}



}

/*
void add_elem_divis(TREE_P tree, void* elem) {
	if (tree == NULL ||elem == NULL || tree->obj == NULL)return;
	if ((*(int*)elem) % (*(int*)tree->obj) == 0) {

		add_elem_divis(tree->childs, elem);
		add_elem_divis(tree->siblings, elem);
		TREE_add_child(tree, elem);//the key is to add the child after the recursion
	}
	else {
		add_elem_divis(tree->childs, elem);
		add_elem_divis(tree->siblings, elem);
	}
}

void create_divisibility_tree(TREE_P tree,int* nums,int maxindex) {

	for (int i = 1; i < maxindex; i++) {
		add_elem_divis(tree, &nums[i]);

	}


}

int main3() {


#define	N 10

	int elem[N] = { 0 };
	for (int r = 0; r < N; r++) {
		elem[r] = r + 1;
	}
	TREE_P handler = TREE_create_TREE(&elem[0]);


handler->obj = &elem[0];

for (int b = 1; b < N / 2; b++) {
TREE_add_child(TREE_add_child(TREE_add_child(handler, &elem[b]), &elem[b]), &elem[b]);
	}

	create_divisibility_tree(handler, elem, N);

	printtree(handler);

	return 0;

}
*/


