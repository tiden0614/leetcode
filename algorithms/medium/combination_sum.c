/**
* Return an array of arrays of size *returnSize.
* The sizes of the arrays are returned as *columnSizes array.
* Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
*/ 
#include <stdlib.h>
#include <stdio.h>
#define SIZE 10
int** combinationSum3(int k, int n, int** columnSizes, int* returnSize) {
	// declarations
	int   capacity;
	int** result;
	int*  stack;
	int   sp, cn, i;
	int** p;
	int*  q;

	*returnSize = 0;
	capacity = 0;

	// corner conditions
	if (k == 1 && 1 <= n && n <= 9) {
		*returnSize = 1;
		(*columnSizes)[0] = 1;
		result[0] = (int*) malloc(sizeof(int));
		result[0][0] = n;
	} else if (!(k <= 0 || k > 9 || n < 1 || n > 50)) {
		// k is greater than or equal to 2 in this case
		// init a stack
		stack = (int*) malloc(k * sizeof(int));
		// init the stack with 1, 2, 3, 4...
		for (sp = 0; sp < k; sp++) {
			stack[sp] = sp + 1;
		}
		while (1) {
			cn = n;
			for (sp = 0; sp < k - 1; sp++) {
				cn -= stack[sp];
			}
			if (stack[k - 2] < cn && cn <= 9) {
				// we found a match combination
				// copy the content of the stack into result
				stack[k - 1] = cn;
				if (*returnSize >= capacity) {
					// increase the capacity of result array
					p = (int**) malloc((capacity + SIZE) * sizeof(int*));
					q = (int*) malloc((capacity + SIZE) * sizeof(int));
					for (i = 0; i < capacity; i++) {
						*(p + i) = *(result + i);
						*(q + i) = *(*columnSizes + i);
					}
					if (capacity > 0) {
						free(result);
						free(*columnSizes);
					}
					result = p;
					*columnSizes = q;
					capacity += SIZE;
				}
				result[*returnSize] = (int*) malloc(k * sizeof(int));
				// copy
				for (sp = 0; sp < k; sp++) {
					result[*returnSize][sp] = stack[sp];
				}
				(*columnSizes)[*returnSize] = k;
				*returnSize += 1;
			}

			// pop up all pointers that reach the end of its layer
			for (sp = k - 2; sp > -1 && stack[sp] == 10 - k + sp; sp--) ;
			if (sp > -1) {
				// increment the first number that doesn't reach the end of its layer
				stack[sp] += 1;
				// then set the following numbers as one bigger than their proceeding
				// numbers
				while (sp < k - 1) {
					stack[sp + 1] = stack[sp] + 1;
					sp += 1;
				}
			} else {
				break;
			}
		}
		free(stack);
	}
	return result;
}

void main() {
	int*   cs;
	int    rs;
	int    i, j;
	int    k = 5;
	int    n = 25;
	int**  res = combinationSum3(5, 25, &cs, &rs);
	for (i = 0; i < rs; i++) {
		printf("[");
		for (j = 0; j < cs[i]; j++) {
			printf("%d", res[i][j]);
			if (j < cs[i] - 1) {
				printf(",");
			}
		}
		printf("]");
		if (i < rs - 1) {
			printf(",");
		}
	}
}