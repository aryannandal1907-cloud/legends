#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 20
#define MAX_NAME 30

// Structure for Adjacency List Node
struct Node {
    int destIndex;
    int cost;
    struct Node* next;
};

// Global Graph Variables
char cities[MAX_CITIES][MAX_NAME];
struct Node* adjList[MAX_CITIES];
int numCities = 0;

// Function to find the index of a city by its name
int findCityIndex(char* name) {
    for (int i = 0; i < numCities; i++) {
        if (strcmp(cities[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

// Function to add a flight (edge) between source and destination
void addEdge(int src, int dest, int cost) {
    // Add destination to source's adjacency list
    struct Node* newNode1 = (struct Node*)malloc(sizeof(struct Node));
    newNode1->destIndex = dest;
    newNode1->cost = cost;
    newNode1->next = adjList[src];
    adjList[src] = newNode1;

    // Add source to destination's adjacency list (Undirected Graph)
    struct Node* newNode2 = (struct Node*)malloc(sizeof(struct Node));
    newNode2->destIndex = src;
    newNode2->cost = cost;
    newNode2->next = adjList[dest];
    adjList[dest] = newNode2;
}

// Function to display the graph representation
void displayGraph() {
    if (numCities == 0) {
        printf("\nGraph is empty. Please input cities and flights first (Option 1).\n");
        return;
    }

    printf("\n=========================================\n");
    printf("     FLIGHT PATH GRAPH (ADJACENCY LIST)  \n");
    printf("=========================================\n");
    for (int i = 0; i < numCities; i++) {
        printf("%s", cities[i]);
        struct Node* temp = adjList[i];
        if (temp == NULL) {
            printf(" -> [No direct flights]");
        } else {
            while (temp != NULL) {
                printf(" -> [%s, Cost: %d]", cities[temp->destIndex], temp->cost);
                temp = temp->next;
            }
        }
        printf("\n");
    }
}

// DFS traversal helper function
void DFS(int cityIndex, int visited[]) {
    visited[cityIndex] = 1;
    struct Node* temp = adjList[cityIndex];
    while (temp != NULL) {
        if (!visited[temp->destIndex]) {
            DFS(temp->destIndex, visited);
        }
        temp = temp->next;
    }
}

// Function to check whether the graph is connected
void checkConnectivity() {
    if (numCities == 0) {
        printf("\nGraph is empty. No cities to check.\n");
        return;
    }

    int visited[MAX_CITIES] = {0};

    // Start DFS from the first city (index 0)
    DFS(0, visited);

    // Check if all cities were visited
    int isConnected = 1;
    for (int i = 0; i < numCities; i++) {
        if (!visited[i]) {
            isConnected = 0;
            break;
        }
    }

    printf("\n=========================================\n");
    if (isConnected) {
        printf("RESULT: The graph is CONNECTED.\n");
        printf("All cities are reachable from one another.\n");
    } else {
        printf("RESULT: The graph is NOT connected.\n");
        printf("Some cities are isolated or unreachable.\n");
    }
    printf("=========================================\n");
}

// Main Menu-Driven Function
int main() {
    int choice;

    // Initialize adjacency list pointers to NULL
    for (int i = 0; i < MAX_CITIES; i++) {
        adjList[i] = NULL;
    }

    do {
        printf("\n=========================================\n");
        printf("       FLIGHT NETWORK MANAGEMENT         \n");
        printf("=========================================\n");
        printf("1. Input Cities and Flights\n");
        printf("2. Display Graph Representation\n");
        printf("3. Check Graph Connectivity (DFS)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n'); // clear buffer
            continue;
        }
        getchar(); // consume newline

        switch (choice) {
            case 1: {
                // Clear previous graph memory if any
                for (int i = 0; i < MAX_CITIES; i++) {
                    struct Node* curr = adjList[i];
                    while (curr != NULL) {
                        struct Node* next = curr->next;
                        free(curr);
                        curr = next;
                    }
                    adjList[i] = NULL;
                }

                printf("Enter number of cities (max %d): ", MAX_CITIES);
                scanf("%d", &numCities);
                getchar(); // consume newline

                if (numCities <= 0 || numCities > MAX_CITIES) {
                    printf("Invalid number of cities!\n");
                    numCities = 0;
                    break;
                }

                printf("Enter the names of the %d cities:\n", numCities);
                for (int i = 0; i < numCities; i++) {
                    printf("  City %d: ", i + 1);
                    fgets(cities[i], MAX_NAME, stdin);
                    cities[i][strcspn(cities[i], "\n")] = 0; // remove trailing newline
                }

                int numFlights;
                printf("Enter number of flights (edges): ");
                scanf("%d", &numFlights);
                getchar(); // consume newline

                for (int i = 0; i < numFlights; i++) {
                    char src[MAX_NAME], dest[MAX_NAME];
                    int cost;
                    printf("\nFlight %d:\n", i + 1);
                    printf("  Source City: ");
                    fgets(src, MAX_NAME, stdin);
                    src[strcspn(src, "\n")] = 0;

                    printf("  Destination City: ");
                    fgets(dest, MAX_NAME, stdin);
                    dest[strcspn(dest, "\n")] = 0;

                    printf("  Flight Cost (Time/Fuel): ");
                    scanf("%d", &cost);
                    getchar(); // consume newline

                    int srcIdx = findCityIndex(src);
                    int destIdx = findCityIndex(dest);

                    if (srcIdx != -1 && destIdx != -1) {
                        addEdge(srcIdx, destIdx, cost);
                        printf("  -> Flight added successfully!\n");
                    } else {
                   printf("  -> Error: One or both cities not found in the list! Flight skipped.\n");
                    }
                }
                break;
            }
            case 2:
                displayGraph();
                break;

            case 3:
                checkConnectivity();
                break;

            case 4:
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice! Please select between 1 and 4.\n");
        }
    } while (choice != 4);

    return 0;
}
