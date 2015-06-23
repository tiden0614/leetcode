#define MIN_SIZE 10
typedef struct {
    unsigned int capacity;
    unsigned int size;
    int* queue;
} Stack;

/* Create a stack */
void stackCreate(Stack *stack, int maxSize) {
    if (maxSize < MIN_SIZE) {
        maxSize = MIN_SIZE;
    }
    stack->capacity = maxSize;
    stack->size = 0;
    stack->queue = (int*) malloc(maxSize * sizeof(int));
}

/* Push element x onto stack */
void stackPush(Stack *stack, int element) {
    if (stack->size < stack->capacity) {
        stack->queue[stack->size++] = element;
    }
}

/* Removes the element on top of the stack */
void stackPop(Stack *stack) {
    if (stack->size > 0) {
        stack->size--;
    }
}

/* Get the top element */
int stackTop(Stack *stack) {
    return stack->queue[stack->size - 1];
}

/* Return whether the stack is empty */
bool stackEmpty(Stack *stack) {
    return stack->size == 0;
}

/* Destroy the stack */
void stackDestroy(Stack *stack) {
    free(stack->queue);
    free(stack);
}