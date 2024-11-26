#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

//stack's structure
typedef struct Stack {
    char arr[MAX_SIZE];
    int top;
} Stackformat;

//stack functions
void initStack(Stackformat *stack) {
    stack->top = -1;
}

int isEmpty(Stackformat *stack) {
    return stack->top == -1;
}

int isFull(Stackformat *stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(Stackformat *stack, char value) {
    if (isFull(stack)) {
        printf("Stack is full!\n");
        return;
    }
    stack->arr[++stack->top] = value;
}

char pop(Stackformat *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return stack->arr[stack->top--];
}

char peek(Stackformat *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return stack->arr[stack->top];
}



//game structure with three stacks: s1, s2, s3
typedef struct Game {
    Stackformat s1, s2, s3;
} Gameformat;

void displayStack(Stackformat *stack) {
    if (stack->top == -1) {
        printf("Stack is empty\n");
        return;
    }
    // Display from bottom to top
    for (int i = 0; i <= stack->top; i++) {
        printf("[%c]\n", stack->arr[i]);  // Print each element in a new line
    }
}



//function to perform the transformation for part (a) of [A, B, C, D] -> [A, B, D, C]
void transformA(Gameformat *game) {
    //Initially in the form of (s1) (s2) (s3)
    // [A] [blank] [blank]
    // [B] [blank] [blank]
    // [C] [blank] [blank]
    // [D] [blank] [blank]
    push(&game->s2, pop(&game->s1)); // pops D into s2   |
    push(&game->s2, pop(&game->s1)); // pops C into s2   | Pop s1 3x bascially
    push(&game->s2, pop(&game->s1)); // pops B into S2   |
    //now int he form of...
    // [A]     [D]      [blank]
    // [blank] [C]      [blank]
    // [blank] [B]      [blank]
    // [blank] [blank]  [blank]

    push(&game->s3, pop(&game->s1)); // pops A into S3   | Pop remaining A into s3
    //now int he form of...
    // [blank] [D]      [A]
    // [blank] [C]      [blank]
    // [blank] [B]      [blank]
    // [blank] [blank]  [blank]

    push(&game->s3, pop(&game->s2)); // pops B into S3   |
    //now int he form of...
    // [blank] [D]      [A]
    // [blank] [C]      [B]
    // [blank] [blank]  [blank]
    // [blank] [blank]  [blank]  
    push(&game->s1, pop(&game->s2)); // pops C into S1   |   
    //now int he form of...
    // [C]     [D]      [A]
    // [blank] [blank]  [B]
    // [blank] [blank]  [blank]
    // [blank] [blank]  [blank]     
    push(&game->s3, pop(&game->s2)); // pops D into S3   |  
    //now int he form of...
    // [C]     [blank]  [A]
    // [blank] [blank]  [B]
    // [blank] [blank]  [D]
    // [blank] [blank]  [blank]     
    push(&game->s3, pop(&game->s1)); // pops C into S3   |   
    //now int he form of...
    // [blank] [blank]  [A]
    // [blank] [blank]  [B]
    // [blank] [blank]  [D]
    // [blank] [blank]  [C]       

//TRANSFORM COMPLETE
}

// Function to perform the transformation for part (b) [A, B, C, D] -> [B, D, A, C]
void transformB(Gameformat *game) {

    push(&game->s2, pop(&game->s1)); // D
    push(&game->s2, pop(&game->s1)); // C

    push(&game->s3, pop(&game->s1)); // B

    push(&game->s1, pop(&game->s2)); // C

    push(&game->s3, pop(&game->s2)); // D

    push(&game->s2, pop(&game->s1)); // C

    push(&game->s3, pop(&game->s1)); // A

    push(&game->s3, pop(&game->s2)); // C

}

int main() {
    Gameformat game; //create the game instance with 3 stacks
    initStack(&game.s1);
    initStack(&game.s2);
    initStack(&game.s3);

    // Initial state: A, B, C, D in s1
    push(&game.s1, 'A');
    push(&game.s1, 'B');
    push(&game.s1, 'C');
    push(&game.s1, 'D');

    printf("Initial state of stacks:\n");
    printf("Stack1 contents:\n");
    displayStack(&game.s1);
    printf("Stack2 contents:\n");   
    displayStack(&game.s2);
    printf("Stack3 contents:\n");
    displayStack(&game.s3);

    // Perform transformation (a) [A, B, C, D] -> [A, B, D, C]
    printf("\nPerforming transformation (a): [A, B, C, D] -> [A, B, D, C]\n");
    transformA(&game);

    printf("Final state of stacks:\n");
    printf("Stack1 contents:\n");
    displayStack(&game.s1);
    printf("Stack2 contents:\n");   
    displayStack(&game.s2);
    printf("Stack3 contents:\n");
    displayStack(&game.s3);

    //reinitiate/reset stacks for next transformation
    initStack(&game.s1);
    initStack(&game.s2);
    initStack(&game.s3);
    push(&game.s1, 'A');
    push(&game.s1, 'B');
    push(&game.s1, 'C');
    push(&game.s1, 'D');
    //now in the form of regular ABCD






    printf("Initial state of stacks:\n");
    printf("Stack1 contents:\n");
    displayStack(&game.s1);
    printf("Stack2 contents:\n");   
    displayStack(&game.s2);
    printf("Stack3 contents:\n");
    displayStack(&game.s3);
    // Perform transformation (b) [A, B, C, D] -> [B, D, A, C]
    printf("\nPerforming transformation (b): [A, B, C, D] -> [B, D, A, C]\n");
    transformB(&game);

    printf("Final state of stacks:\n");
    printf("Stack1 contents:\n");
    displayStack(&game.s1);
    printf("Stack2 contents:\n");   
    displayStack(&game.s2);
    printf("Stack3 contents:\n");
    displayStack(&game.s3);

    return 0;
}
