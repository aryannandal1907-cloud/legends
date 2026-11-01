#include <stdio.h> 
#include <stdlib.h> 
#define ROWS 10 
#define SEATS 7 
// Structure for a seat node 
struct Node 
{ 
int seatNo; 
struct Node *prev; 
struct Node *next; 
}; 
// Array of head pointers for 10 rows 
struct Node *head[ROWS]; 
/* Function to create a new seat node */ 
struct Node *createNode(int seatNo) 
{ 
struct Node *newNode; 
newNode = (struct Node *)malloc(sizeof(struct Node)); 
newNode->seatNo = seatNo; 
newNode->prev = NULL; 
newNode->next = NULL; 
return newNode; 
} 
/* Initialize all seats as available */ 
void initializeSeats() 
{ 
int i, j; 
for (i = 0; i < ROWS; i++) 
{ 
head[i] = NULL; 
for (j = 1; j <= SEATS; j++) 
{ 
struct Node *newNode = createNode(j);
// Insert at the end of doubly linked list if (head[i] == NULL) 
{ 
head[i] = newNode; 
} 
else 
{ 
struct Node *temp = head[i]; 
while (temp->next != NULL) 
{ 
temp = temp->next; 
} 
temp->next = newNode; 
newNode->prev = temp; 
} 
} 
} 
} 
/* Display available seats */ 
void displayAvailableSeats() 
{ 
int i; 
printf("\n--- Available Seats ---\n"); 
for (i = 0; i < ROWS; i++) 
{ 
struct Node *temp = head[i]; 
printf("Row %d: ", i + 1); 
if (temp == NULL) 
{ 
printf("No seats available"); 
} 
while (temp != NULL) 
{ 
printf("%d ", temp->seatNo); 
temp = temp->next; 
}
printf("\n"); 
} 
} 
/* Book a seat */ 
void bookSeat() 
{ 
int row, seat; 
struct Node *temp; 
printf("\nEnter Row Number (1-10): "); 
scanf("%d", &row); 
printf("Enter Seat Number (1-7): "); 
scanf("%d", &seat); 
// Validate row and seat number 
if (row < 1 || row > ROWS || seat < 1 || seat > SEATS) { 
printf("Invalid row or seat number!\n"); return; 
} 
temp = head[row - 1]; 
// Search for the seat 
while (temp != NULL && temp->seatNo != seat) { 
temp = temp->next; 
} 
if (temp == NULL) 
{ 
printf("Seat is already booked!\n"); 
return; 
} 
// Case 1: Only one node 
if (temp->prev == NULL && temp->next == NULL) { 
head[row - 1] = NULL; 
} 
// Case 2: First node
else if (temp->prev == NULL) 
{ 
head[row - 1] = temp->next; 
temp->next->prev = NULL; 
} 
// Case 3: Last node 
else if (temp->next == NULL) 
{ 
temp->prev->next = NULL; 
} 
// Case 4: Middle node 
else 
{ 
temp->prev->next = temp->next; 
temp->next->prev = temp->prev; 
} 
free(temp); 
printf("Seat booked successfully!\n"); 
} 
/* Cancel booking */ 
void cancelBooking() 
{ 
int row, seat; 
struct Node *newNode; 
struct Node *temp; 
printf("\nEnter Row Number (1-10): "); 
scanf("%d", &row); 
printf("Enter Seat Number (1-7): "); 
scanf("%d", &seat); 
// Validate row and seat number 
if (row < 1 || row > ROWS || seat < 1 || seat > SEATS) { 
printf("Invalid row or seat number!\n"); return; 
} 
// Check whether the seat is already available
temp = head[row - 1]; 
while (temp != NULL) 
{ 
if (temp->seatNo == seat) 
{ 
printf("Seat is already available. Cannot cancel booking!\n"); return; 
} 
temp = temp->next; 
} 
// Create new node 
newNode = createNode(seat); 
// Insert at beginning if list is empty 
if (head[row - 1] == NULL) 
{ 
head[row - 1] = newNode; 
} 
// Insert in sorted order 
else if (seat < head[row - 1]->seatNo) 
{ 
newNode->next = head[row - 1]; 
head[row - 1]->prev = newNode; 
head[row - 1] = newNode; 
} 
else 
{ 
temp = head[row - 1]; 
// Find correct position 
while (temp->next != NULL && 
temp->next->seatNo < seat) 
{ 
temp = temp->next; 
} 
newNode->next = temp->next; 
newNode->prev = temp; 
if (temp->next != NULL)
{ 
temp->next->prev = newNode; 
} 
temp->next = newNode; 
} 
printf("Booking cancelled successfully!\n"); 
} 
/* Main Function */ 
int main() 
{ 
int choice; 
// Initialize theater seats 
initializeSeats(); 
// Assume some random bookings initially 
// These bookings will be simulated by removing seats printf("Welcome to Cinemax Theater Booking System\n"); 
do 
{ 
printf("\n--- MENU ---\n"); 
printf("1. Display Available Seats\n"); 
printf("2. Book a Seat\n"); 
printf("3. Cancel Booking\n"); 
printf("4. Exit\n"); 
printf("Enter your choice: "); 
scanf("%d", &choice); 
switch (choice) 
{ 
case 1: 
displayAvailableSeats(); 
break; 
case 2: 
bookSeat(); 
break; 
case 3: 
cancelBooking();
break; 
case 4: 
printf("Thank you for using Cinemax Booking System!\n"); break; 
default: 
printf("Invalid choice!\n"); 
} 
} while (choice != 4); 
return 0; 
}
