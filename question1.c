#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Queue structure definition
typedef struct Queue {
    int arr[MAX_SIZE];
    int front, rear;
} Queueformat;

// Standard Queue "library" stuff
void inQueue(Queueformat* q) {
    q->front = -1;  // Initialize front to -1 to indicate an empty queue
    q->rear = -1;   // Initialize rear to -1 to indicate an empty queue
}

int isEmpty(Queueformat* q) {
    return q->front == -1; // Return 1 if the queue is empty
}

int isFull(Queueformat* q) {
    return q->rear == MAX_SIZE - 1; // Return 1 if the queue is full
}

void enqueue(Queueformat* q, int value) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }

    if (isEmpty(q)) {
        q->front = 0;  // Set front to 0 when adding the first element
    }

    q->arr[++q->rear] = value; // Increment rear and add element
}

int dequeue(Queueformat* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }

    int value = q->arr[q->front]; // Get the front element

    if (q->front == q->rear) {
        // If there's only one element left, reset the queue
        q->front = q->rear = -1;
    } else {
        q->front++;  // Increment front to dequeue the next element
    }

    return value;
}

// Stack structure using two queues
typedef struct Stack {
    Queueformat q1, q2;
} Stackformat;

// Initialize the stack. We'll be mainly using q1 and leave q2 for manipulation
void inStack(Stackformat* stack) {
    inQueue(&stack->q1);  // Initialize q1 to empty
    inQueue(&stack->q2);  // Initialize q2 to empty
}

// Push: Adds an element x to the stack (enqueue in q1)
void push(Stackformat* stack, int x) {
    enqueue(&stack->q1, x);  // Simply enqueue into q1 for now
    printf("Pushed: %d\n", x);
}

// Pop: Removes and returns the top element of the stack
int pop(Stackformat* stack) {
    if (isEmpty(&stack->q1)) {
        printf("Stack is empty\n");
        return -1;
    }

    // Transfer all elements except the last one from q1 to q2
    while (stack->q1.front < stack->q1.rear) {
        enqueue(&stack->q2, dequeue(&stack->q1));
    }

    // The last element in q1 is the top element of the "stack". Completely remove it (or skip it)
    int topElement = dequeue(&stack->q1);

    // Move all elements from q2 back to q1
    while (!isEmpty(&stack->q2)) {
        enqueue(&stack->q1, dequeue(&stack->q2));
    }

    return topElement;  // Return the top element
}

// Top/Peek: Get the top element of the "stack" without removing it
int top(Stackformat* stack) {
    if (isEmpty(&stack->q1)) {
        printf("Stack is empty\n");
        return -1;
    }

    //first dequeued item from q1 is the top element that we need
    int topElement = dequeue(&stack->q1);
    // Transfer all elements from q1 to q2
    while (!isEmpty(&stack->q1)) {
        enqueue(&stack->q2, dequeue(&stack->q1));
    }

    // Put top element back into q1 as it should remain in the stack (this is PEEK function not POP)
    enqueue(&stack->q1, topElement);

    // Move all elements from q2 back to q1
    while (!isEmpty(&stack->q2)) {
        enqueue(&stack->q1, dequeue(&stack->q2));
    }

    return topElement;  // Return the top element
}

// Empty: Check if the stack is empty
int empty(Stackformat* stack) {
    return isEmpty(&stack->q1);  // Return if q1 is empty
}

// Example usage
int main() {
    Stackformat stack;  // Create a stack 
    inStack(&stack);    // Initialize the stack
    char func;

    //push some random elements onto the "stack"
    push(&stack, 1);
    push(&stack, 2);
    push(&stack, 3);
    printf("Pre-made stack with pushed elements of 1 2 3...\n");
    //looped switch case for an interactive User face stack function that uses 2 queues
    while (1) {
        printf("\nChoose your function (push[x]= P, pop = O, top = T, empty = E): ");
        scanf(" %c", &func);

        switch (func) {
            case 'P': {
                int inputvalue;
                printf("This is the push function. Enter your value: ");
                scanf("%d", &inputvalue);
                push(&stack, inputvalue);
                break;
            }
            case 'O': {
                printf("This is the pop function.\n");
                int topElementReturned = pop(&stack);
                if(topElementReturned == -1){
                    printf("Stack can't be popped anymore");
                }
                else{
                printf("Your popped element is ... %d\n", topElementReturned);
                }
                break;
            }
            case 'T': {
                printf("This is the top/peek function for the 'Stack'\n");
                int topElementPeeked = top(&stack);
                printf("Here is your peeked element... %d\n", topElementPeeked);
                break;
            }
            case 'E': {
                printf("This is the stack empty checker function\n");
                int emptyflag = empty(&stack);
                printf("The stack is ... %d (1 = empty, 0 = not empty)\n", emptyflag);
                break;
            }
        }
    }

    return 0;
}

