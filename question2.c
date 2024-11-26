#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

//queue structure definition
typedef struct Queue {
    int arr[MAX_SIZE];
    int front, rear;
} Queueformat;

//stack structure definition
typedef struct Stack {
    int arr[MAX_SIZE];
    int top;
} Stackformat;

//queue functions (there is only 1 queue btw)
void inQueue(Queueformat* q) {
    q->front = -1;
    q->rear = -1;
}

int isEmptyQueue(Queueformat* q) {
    return q->front == -1;
}

int isFullQueue(Queueformat* q) {
    return q->rear == MAX_SIZE - 1;
}

void enqueue(Queueformat* q, int value) {
    if (isFullQueue(q)) {
        printf("Queue is full\n");
        return;
    }
    if (isEmptyQueue(q)) {
        q->front = 0;
    }
    q->arr[++q->rear] = value;
}

int dequeue(Queueformat* q) {
    if (isEmptyQueue(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    int value = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return value;
}
//gets the size of the queue of how many elements there are in there. We do a +1 bc front and rear pointer are inclusive
int sizeQueue(Queueformat* q) {
    return q->rear - q->front + 1;
}

//stack functions (there is only 1 stack)
void inStack(Stackformat* s) {
    s->top = -1;
}

int isEmptyStack(Stackformat* s) {
    return s->top == -1;
}

int isFullStack(Stackformat* s) {
    return s->top == MAX_SIZE - 1;
}

void push(Stackformat* s, int value) {
    if (isFullStack(s)) {
        printf("Stack is full\n");
        return;
    }
    s->arr[++s->top] = value;
}

int pop(Stackformat* s) {
    if (isEmptyStack(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->arr[s->top--];
}

//function to reverse the first K elements of the queue
void reverseFirstKElements(Queueformat* q, int K) {
    if (K > sizeQueue(q)) {
        printf("K is larger than the amount of elements in queue. Doesn't work.\n");
        return;
    }

    Stackformat stack; //stack called "stack"
    inStack(&stack);

    //dequeue the first K elements and push them onto the stack
    for (int i = 0; i < K; i++) { //do this K times
        int value = dequeue(q);
        push(&stack, value);
    }

    //pop from the stack and enqueue back to the queue to reverse the order of first K elements
    while (!isEmptyStack(&stack)) {
        enqueue(q, pop(&stack));
    }

    //to reorganize the remaining elemments back into its orignal order in the queue
    int remainingElements = sizeQueue(q) - K;
    for (int i = 0; i < remainingElements; i++) {
        int value = dequeue(q); //do this one leftover element at a time so that the order it is enequeued at doesn't get mixed up
        enqueue(q, value);
    }
}

//function to print the queue
void printQueue(Queueformat* q) {
    if (isEmptyQueue(q)) {
        printf("Queue is empty\n");
        return;
    }
    for (int i = q->front; i <= q->rear; i++) { //since the queue is used as an array, we cant do while loop w/ !isEmpty func
        printf("%d ", q->arr[i]); //prints all its elements
    }
    printf("\n");
}

int main() {
    Queueformat q; //Queue called "q"
    inQueue(&q);

    int value;
    char choice;
    
    // User input for the queue elements
    printf("Input elements into the queue(there is a max of 100):\n");
    while (1) {
        if (isFullQueue(&q)) {
            printf("Queue is full! Cannot add more elements.\n");
            break;
        }
        
        // Prompt for input
        printf("Enter an element to enqueue: ");
        scanf("%d", &value);
        enqueue(&q, value);

        // Ask if the user wants to continue
        printf("Do you want to add another element? (y/n): ");
        scanf(" %c", &choice); //if they press "y" then it will reach the end of this iteration and go back all the way to the top of the while loop

        if (choice == 'n' || choice == 'N') {
            break;
        }
    }

    //print the queue before reversing process
    printf("Queue before reversing first K elements: ");
    printQueue(&q);

    //reverse the first K elements
    int K;
    printf("Enter the value of K (number of elements to reverse): ");
    scanf("%d", &K);

    reverseFirstKElements(&q, K);

    //print the queue after reversing the first K elements
    printf("Queue after reversing first %d elements: ", K);
    printQueue(&q);

    return 0;
}