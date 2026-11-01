#include <stdio.h>
#include <stdlib.h>

// Structure for a BST Node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node into BST
struct Node* insert(struct Node* node, int value) {
    if (node == NULL) {
        return createNode(value);
    }
    if (value < node->data) {
        node->left = insert(node->left, value);
    } else if (value > node->data) {
        node->right = insert(node->right, value);
    }
    // Duplicate values are ignored in standard BST
    return node;
}

// Function to find height (number of nodes in the longest path from root)
int findHeight(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    int leftHeight = findHeight(node->left);
    int rightHeight = findHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Function to find the minimum data value in the tree
int findMin(struct Node* node) {
    if (node == NULL) {
        return -1; // Tree is empty
    }
    struct Node* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current->data;
}

// Function to mirror the tree (swap left and right pointers at every node)
void mirrorTree(struct Node* node) {
    if (node == NULL) {
        return;
    }
    // Recursively mirror subtrees first
    mirrorTree(node->left);
    mirrorTree(node->right);

    // Swap the left and right pointers
    struct Node* temp = node->left;
    node->left = node->right;
    node->right = temp;
}

// Function to search a value in BST
int search(struct Node* node, int key) {
    if (node == NULL) {
        return 0; // False
    }
    if (key == node->data) {
        return 1; // True
    } else if (key < node->data) {
        return search(node->left, key);
    } else {
        return search(node->right, key);
    }
}

// Inorder traversal to display the tree elements
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Main Menu-Driven Function
int main() {
    struct Node* root = NULL;
    int choice, value, key;

    do {
        printf("\n=========================================\n");
        printf("       BINARY SEARCH TREE OPERATIONS     \n");
        printf("=========================================\n");
        printf("1. Insert a new node\n");
        printf("2. Display tree (Inorder Traversal)\n");
        printf("3. Find number of nodes in longest path from root (Height)\n");
        printf("4. Find minimum data value in the tree\n");
        printf("5. Mirror the tree\n");
        printf("6. Search a value\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid integer.\n");
            while (getchar() != '\n'); // clear buffer
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                printf("Node %d inserted successfully.\n", value);
                break;

            case 2:
                printf("Inorder Traversal (Sorted Order): ");
                if (root == NULL) {
                    printf("Tree is empty.");
                } else {
                    inorder(root);
                }
                printf("\n");
                break;

            case 3:
                printf("Number of nodes in longest path from root = %d\n", findHeight(root));
                break;

            case 4:
                if (root == NULL) {
                    printf("Tree is empty!\n");
                } else {
                    printf("Minimum data value found = %d\n", findMin(root));
                }
                break;

            case 5:
                mirrorTree(root);
                printf("Tree mirrored successfully! (Left and right pointers swapped)\n");
                break;

            case 6:
                printf("Enter value to search: ");
                scanf("%d", &key);
                if (search(root, key)) {
                    printf("Key %d found in the tree.\n", key);
                } else {
                    printf("Key %d not found in the tree.\n", key);
                }
                break;

            case 7:
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice! Please select between 1 and 7.\n");
        }
    } while (choice != 7);

    return 0;
}
