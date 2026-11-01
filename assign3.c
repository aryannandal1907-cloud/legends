
#include <stdio.h> 
#define SIZE 10 
int hash(int key) 
{ 
 return key % SIZE; 
} 
int hash2(int key) 
{ 
 return 7 - (key % 7); 
} 
/* Insert using 1=Linear, 2=Quadratic, 3=Double */ 
void insert(int table[], int key, int type) 
{ 
 int i, index, pos; 
 index = hash(key); 
 for (i = 0; i < SIZE; i++) 
 { 
 if (type == 1) 
 pos = (index + i) % SIZE; 
 else if (type == 2) 
 pos = (index + i * i) % SIZE; 
 else 
 pos = (index + i * hash2(key)) % SIZE; 
 if (table[pos] == -1) 
 { 
 table[pos] = key; 
 return; 
 } 
 } 
} 
/* Search using the same probing technique */ 
int search(int table[], int key, int type) 
{ 
 int i, index, pos; 
 index = hash(key); 
 for (i = 0; i < SIZE; i++) 
 { 
 if (type == 1) 
 pos = (index + i) % SIZE; 
 else if (type == 2) 
 pos = (index + i * i) % SIZE; 
 else 
 pos = (index + i * hash2(key)) % SIZE; 
 if (table[pos] == key) 
 return pos; 
 if (table[pos] == -1) 
 return -1; 
 } 
 return -1; 
} 
void display(int table[]) 
{ 
 int i; 
 for (i = 0; i < SIZE; i++) 
 { 
 if (table[i] == -1) 
 printf("%d : Empty\n", i); 
 else 
 printf("%d : %d\n", i, table[i]); 
 } 
} 
int main() 
{ 
 int linear[SIZE], quadratic[SIZE], doub[SIZE]; 
 int n, i, key, searchKey, pos; 
 /* Initialize tables */ 
 for (i = 0; i < SIZE; i++) 
 { 
 linear[i] = -1; 
 quadratic[i] = -1;
 doub[i] = -1; 
 } 
 printf("Enter number of clients: "); 
 scanf("%d", &n); 
 printf("Enter telephone numbers:\n"); 
 for (i = 0; i < n; i++) 
 { 
 scanf("%d", &key); 
 insert(linear, key, 1); 
 insert(quadratic, key, 2); 
 insert(doub, key, 3); 
 } 
 printf("\n--- Linear Probing ---\n");  display(linear); 
 printf("\n--- Quadratic Probing ---\n");  display(quadratic); 
 printf("\n--- Double Hashing ---\n");  display(doub); 
 printf("\nEnter telephone number to search: ");  scanf("%d", &searchKey); 
 pos = search(linear, searchKey, 1); 
 printf("Linear Probing: "); 
 if (pos != -1) printf("Found at index %d\n", pos);  else printf("Not Found\n"); 
 pos = search(quadratic, searchKey, 2);  printf("Quadratic Probing: "); 
 if (pos != -1) printf("Found at index %d\n", pos);  else printf("Not Found\n"); 
 pos = search(doub, searchKey, 3); 
 printf("Double Hashing: "); 
 if (pos != -1) printf("Found at index %d\n", pos);  else printf("Not Found\n"); 
 return 0; 
}
