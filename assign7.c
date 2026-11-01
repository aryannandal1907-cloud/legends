#include <stdio.h>
#include <stdlib.h>

// Define the maximum capacity (M) of orders the pizza parlor can hold at once
#define M 5

typedef struct {
    int items[M];
    int front;
    int rear;
    int count;
} PizzaQueue;

// Function to initialize the queue
void initializeQueue(PizzaQueue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

// Check if the queue is full (Overflow condition)
int isFull(PizzaQueue *q) {
    return q->count == M;
}

// Check if the queue is empty (Underflow condition)
int isEmpty(PizzaQueue *q) {
    return q->count == 0;
}

// Function to add a new order (Enqueue)
void enqueue(PizzaQueue *q, int orderId) {
    if (isFull(q)) {
        printf("\n[OVERFLOW ERROR] Pizza parlor is at full capacity (Max: %d orders). Please wait for orders to be served!\n", M);
        return;
    }
    q->rear = (q->rear + 1) % M;
    q->items[q->rear] = orderId;
    q->count++;
    printf("\n[SUCCESS] Order #%d has been accepted and added to the queue.\n", orderId);
}

// Function to serve/delete an order (Dequeue)
void dequeue(PizzaQueue *q) {
    if (isEmpty(q)) {
        printf("\n[UNDERFLOW ERROR] No pending orders to serve! The queue is empty.\n");
        return;
    }
    int servedOrder = q->items[q->front];
    q->front = (q->front + 1) % M;
    q->count--;
    printf("\n[SERVED] Order #%d has been processed and delivered to the customer.\n", servedOrder);
}

// Function to display the current status of the queue
void display(PizzaQueue *q) {
    if (isEmpty(q)) {
        printf("\n[STATUS] The pizza parlor order queue is currently EMPTY.\n");
        return;
    }
    
    printf("\n========================================\n");
    printf("   CURRENT PIZZA PARLOR ORDER QUEUE\n");
    printf("========================================\n");
    int i = q->front;
    for (int c = 0; c < q->count; c++) {
        printf(" Position %d -> Order ID: %d\n", c + 1, q->items[i]);
        i = (i + 1) % M;
    }
    printf("----------------------------------------\n");
    printf(" Total Active Orders: %d / %d\n", q->count, M);
    printf("========================================\n");
}

int main() {
    PizzaQueue q;
    initializeQueue(&q);
    int choice, orderId;

    printf("========================================\n");
    printf("   PIZZA PARLOR ORDER MANAGEMENT SYSTEM\n");
    printf("========================================\n");

    do {
        printf("\n--- MENU ---\n");
        printf("1. Place New Order (Enqueue)\n");
        printf("2. Serve Order (Dequeue)\n");
        printf("3. Display Current Queue Status\n");
        printf("4. Exit\n");
        printf("Enter your choice (1-4): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter Order ID (integer): ");
                scanf("%d", &orderId);
                enqueue(&q, orderId);
                break;
                
            case 2:
                dequeue(&q);
                break;
                
            case 3:
                display(&q);
                break;
                
            case 4:
                printf("\nExiting the system. Have a great day!\n");
                break;
                
            default:
                printf("\nInvalid choice! Please choose an option between 1 and 4.\n");
        }
    } while (choice != 4);

    return 0;
}  
