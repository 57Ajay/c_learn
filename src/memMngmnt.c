#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Some Notes;
// STATIC MEMORY ALLOCATION -> COMPILE TIME MEMORY ALLOCATION;
//-->> int students[20];
//-->> printf("%lu", sizeof(students)); // 80 bytes
// DYNAMIC MEMORY ALLOCATION -> RUNTIME MEMORY ALLOCATION;
//-->> int *ptr1 = malloc(size);
//-->> int *ptr2 = calloc(amount, size);

int basicMalloc() {
  int *ptr = malloc(sizeof(int)); // Allocate memory for one integer
  if (ptr == NULL) {
    printf("Memory allocation failed\n");
    return 1;
  }

  *ptr = 42; // Assign a value
  printf("Value: %d\n", *ptr);

  free(ptr); // Free allocated memory
  return 0;
}

void memory(void) {
  // int student[20];
  int *students;
  int numStudents = 12;
  students = calloc(numStudents, sizeof(*students));
  printf("%llu", numStudents * sizeof(*students)); // 48 bytes
}

int dynArray() {
  int n = 5;
  int *arr = malloc(n * sizeof(int)); // Allocate array for 5 integers
  if (arr == NULL) {
    printf("Memory allocation failed\n");
    return 1;
  }

  for (int i = 0; i < n; i++) {
    arr[i] = i + 1; // Initialize array elements
  }

  printf("Original array: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  n = 10;
  arr = realloc(arr, n * sizeof(int)); // Resize the array to 10 integers
  if (arr == NULL) {
    printf("Memory reallocation failed\n");
    return 1;
  }

  for (int i = 5; i < n; i++) {
    arr[i] = i + 1; // Assign values to new elements
  }

  printf("Resized array: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  free(arr); // Free allocated memory
  return 0;
}

int caloc() {
  int rows = 3, cols = 4;
  int **matrix =
      calloc(rows, sizeof(int *)); // Allocate memory for row pointers
  if (matrix == NULL) {
    printf("Memory allocation failed\n");
    return 1;
  }

  for (int i = 0; i < rows; i++) {
    matrix[i] = calloc(cols, sizeof(int)); // Allocate memory for each row
    if (matrix[i] == NULL) {
      printf("Memory allocation failed\n");
      return 1;
    }
  }

  // Initialize and print the matrix
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] = i + j;
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }

  // Free allocated memory
  for (int i = 0; i < rows; i++) {
    free(matrix[i]);
  }
  free(matrix);

  return 0;
}

typedef struct {
  char *name;
  int age;
} Person;

int structDyn() {
  Person *p = malloc(sizeof(Person)); // Allocate memory for the structure
  if (p == NULL) {
    printf("Memory allocation failed\n");
    return 1;
  }

  p->name = malloc(50 * sizeof(char)); // Allocate memory for the name
  if (p->name == NULL) {
    printf("Memory allocation failed\n");
    free(p);
    return 1;
  }

  strcpy(p->name, "John Doe"); // Assign values
  p->age = 30;

  printf("Name: %s, Age: %d\n", p->name, p->age);

  free(p->name); // Free inner memory
  free(p);       // Free outer memory
  return 0;
}

void leakExample() {
  int *arr = malloc(5 * sizeof(int)); // Memory allocated
  // Missing `free(arr)` causes a memory leak
  free(arr); // added just for freeing memory
}

int avdmemLeak() {
  int *data = malloc(10 * sizeof(int)); // Allocate memory
  if (data == NULL) {
    printf("Memory allocation failed\n");
    return 1;
  }

  // Always free the allocated memory
  free(data);

  leakExample(); // Demonstrating a potential memory leak
  return 0;
}

int dynStr() {
  char *str = malloc(10 * sizeof(char)); // Allocate memory for string
  if (str == NULL) {
    printf("Memory allocation failed\n");
    return 1;
  }

  strcpy(str, "Hello");
  printf("String: %s\n", str);

  str = realloc(str, 20 * sizeof(char)); // Resize string
  if (str == NULL) {
    printf("Memory reallocation failed\n");
    return 1;
  }

  strcat(str, ", World!");
  printf("Updated String: %s\n", str);

  free(str); // Free memory
  return 0;
}

typedef struct Node {
  int data;
  struct Node *next;
} Node;

Node *createNode(int data) {
  Node *newNode = malloc(sizeof(Node));
  if (newNode == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

void freeList(Node *head) {
  Node *temp;
  while (head != NULL) {
    temp = head;
    head = head->next;
    free(temp);
  }
}

int lnkdLst() {
  Node *head = createNode(1);
  head->next = createNode(2);
  head->next->next = createNode(3);

  // Print the list
  Node *current = head;
  while (current != NULL) {
    printf("%d -> ", current->data);
    current = current->next;
  }
  printf("NULL\n");

  freeList(head); // Free allocated memory
  return 0;
}

struct list {
  int *data;    // Points to the memory where the list items are stored
  int numItems; // Indicates how many items are currently in the list
  int size;     // Indicates how many items fit in the allocated memory
};

void addToList(struct list *myList, int item);

int infList() {
  struct list myList;
  int amount;

  // Create a list and start with enough space for 10 items
  myList.numItems = 0;
  myList.size = 10;
  myList.data = malloc(myList.size * sizeof(int));

  // Find out if memory allocation was successful
  if (myList.data == NULL) {
    printf("Memory allocation failed");
    return 1; // Exit the program with an error code
  }

  // Add any number of items to the list specified by the amount variable
  amount = 44;
  for (int i = 0; i < amount; i++) {
    addToList(&myList, i + 1);
  }

  // Display the contents of the list
  for (int j = 0; j < myList.numItems; j++) {
    printf("%d ", myList.data[j]);
  }

  // Free the memory when it is no longer needed
  free(myList.data);
  myList.data = NULL;

  return 0;
}

// This function adds an item to a list
void addToList(struct list *myList, int item) {

  // If the list is full then resize the memory to fit 10 more items
  if (myList->numItems == myList->size) {
    myList->size += 10;
    myList->data = realloc(myList->data, myList->size * sizeof(int));
  }

  // Add the item to the end of the list
  myList->data[myList->numItems] = item;
  myList->numItems++;
}

int memMngmntMain(void) {
  memory();
  printf("\nBasic malloc\n");
  basicMalloc();
  printf("\nDynamic Array Allocation\n");
  dynArray();
  printf("\ncalloc\n");
  caloc();
  printf("\nStructure with Dynamic Memory\n");
  structDyn();
  printf("\nAvoid Memory Leaks\n");
  avdmemLeak();
  printf("\nDynamic String Manipulation\n");
  dynStr();
  printf("\nLinked List\n");
  lnkdLst();
  printf("\nInfinite List\n");
  infList();
  return 0;
}
