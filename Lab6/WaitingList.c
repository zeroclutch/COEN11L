/**
 * Pranav Grover
 * COEN 11
 * Lab 6
 * Wednesday 5:15PM
 * 
 * Created Feb. 24, 2020
 */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# define NODE struct entry
# define LIST struct list
# define WAITING_LIST_SIZE 4

// Initialize globals
struct entry {
    char name[20];
    int size;
    NODE* next;
    NODE* previous;
};

struct list {
    NODE* head;
    NODE* tail;
};

LIST* waitingList[WAITING_LIST_SIZE];


/** PRIVATE FUNCTIONS **/

/**
 * Finds the minimum of two integers
 */
int min(int a, int b) {
    return a > b ? b : a;
}

/**
 * Gets the appropriate linked-list for the waiting list based on its size.
 */
LIST* getListBySize(int size) {
    return waitingList[min(size / 2, WAITING_LIST_SIZE - 1)];
}

/**
 * Checks if the entire list is empty. Returns 1 if it is empty, or 0 if it isn't.
 */
int isListEmpty() {
    for(int i = 0; i < WAITING_LIST_SIZE; i++) {
        if(waitingList[i]->head != NULL) {
            return 0;
        }
    }
    return 1;
}

/**
 * Removes an element from a linked list.
 * @param {int} arr[10] Target array
 * @param {int} index Index to remove element from
 * @returns void
 */
void removeNode(NODE* node) {
    LIST* list = getListBySize(node->size);
    if(node != NULL) {
        if(node == list->head) {
            list->head = node->next;
            if(list->head != NULL) {
                list->head->previous = NULL;
            }
        } else if (node == list->tail) {
            list->tail = node->previous;
            if(list->tail != NULL) {
                list->tail->next = NULL;
            }
        } else {
            node->next->previous = node->previous;
            node->previous->next = node->next;
        }
        free(node);
    }
}

int checkDuplicate(char name[20]) {
    int duplicate = 0;
    for(int i = 0; i < WAITING_LIST_SIZE; i++) {
        LIST* list = waitingList[i];
        NODE *node = list->head;
        while(node != NULL && !duplicate) {
            if(strcmp(node->name, name) == 0) {
                duplicate = 1;
            }
            node = node->next;
        }
    }
    return duplicate;
}

/** WAITINGLIST API **/

/**
 * Initializes the waiting list elements
 * @returns void
 */
void init() {
    for(int i = 0; i < WAITING_LIST_SIZE; i++) {
        LIST* listItem = (LIST*) malloc(sizeof(LIST));
        waitingList[i] = listItem;
    }
}

/**
 * Inserts a group to the end of the waiting list.
 * @param {char} name[20] Name of the group
 * @param {int} size Size of the group 
 * @returns void
 */
void insert(char name[20], int size) {
    NODE *node = (NODE*) malloc(sizeof(NODE));

    strcpy(node->name, name);
    node->size = size;

    // Get list item
    LIST* list = getListBySize(node->size);

    node->previous = list->tail;
    node->next = NULL;
    
    if(list->head == NULL)
        list->head = node;
    if(list->tail != NULL)
        list->tail->next = node;
    list->tail = node;
}

/**
 * Removes a set number of people from the group. This starts from the oldest possible matches, and continues to remove groups until there are no more spots left.
 * @param {int} size Size of the opening 
 * @returns void
 */
void delete(int size) {
    if(isListEmpty()) {
        printf("The list is empty.");
    } else {
        for(int i = 0; i < WAITING_LIST_SIZE; i++) {
            LIST* list = waitingList[i];
            NODE *node = list->head;
            while(node != NULL && size >= 0) {
                if(node->size <= size) {
                    size -= node->size;
                    printf("%s was removed, a group of %d people.\n", node->name, node->size);
                    removeNode(node);
                }
                node = node->next;
            }
        }
    }
}

void searchSize(int size) {
    if(isListEmpty()) {
        printf("The list is empty.");
    } else if(size <= 0) {
        printf("There are no entries below the specified size.");
    } else {
        printf("                 WAITING LIST\n");
        printf("%20s | Group Size\n", "Name");
        printf("---------------------|---------------------\n");
        for(int i = 0; i < WAITING_LIST_SIZE; i++) {
            LIST* list = waitingList[i];
            NODE *node = list->head;
            while(node != NULL) {
                if(node->size <= size) {
                    printf("%20s | %d\n", node->name, node->size);
                }
                node = node->next;
            }
        }
    }
}

/**
 * Prints the current waiting list, or indicates if the list is empty
 * @returns void
 */
void list(void) {
    printf("                 WAITING LIST\n");
    printf("%20s | Group Size\n", "Name");
    printf("---------------------|---------------------\n");
    for(int i = 0; i < WAITING_LIST_SIZE; i++) {
        LIST* list = waitingList[i];
        NODE *node = list->head;
        while(node != NULL) {
            printf("%20s | %d\n", node->name, node->size);
            node = node->next;
        }
    }
}

/**
 * The entry point for the program.
 */
int main() {
    init();
    int choice;
    while(1) {
        printf("Welcome to the waiting room. Please select your choice: \n\n1) View the waiting list\n2) Add a name to the waiting list\n3) Remove a group from the waiting list\n4) Find groups below a certain size\n5) Fill the list with names\n6) Exit\n\n> ");
        scanf(" %d", &choice);

        if (choice == 1) {
            // List is printed after every command
        }
        else if (choice == 2) {
            // Adds a member to the waiting list
            char name[20];
            int size;
            printf("\n\nWhat name would you like to add?\n> ");
            scanf(" %s", name);
            if(checkDuplicate(name)==1) {
                printf("\n\nSorry, that name is already there\n");
            } else {
                printf("\n\nWhat size group do you have?\n> ");
                scanf(" %d", &size);
                insert(name, size);
            }
        } else if (choice == 3) {
            // Remove a group from the waiting list
            int size;
            if(!isListEmpty()) {
                printf("\n\nHow many members would you like to remove?\n> ");
                scanf(" %d", &size);
                printf("Removing %d members...\n", size);
                delete(size);
            }
        } else if (choice == 4) {
            // Find groups below a certain size
            int size;
            if(!isListEmpty()) {
                printf("\n\nWhat's the maximum group size?\n> ");
                scanf(" %d", &size);
                searchSize(size);
            }
        } else if (choice == 5) {
            // Fill the waiting list with random names
            insert("Steve", 4);
            insert("Maria", 2);
            insert("Paul", 5);
            insert("Mary", 7);
            insert("Will", 4);
            insert("Sophie", 10);
            insert("Chloe", 2);
            insert("Jack", 4);
            insert("Emma", 3);
            insert("Craig", 7);
            insert("Angie", 6);
        } else if (choice == 6) {
            return 0;
        } else {
		
            printf("\n\nInvalid option. Please try again.");
        }

        // Print list
        printf("\n\n");
        if(choice != 4) {
            list();
        }
        printf("\n\n");
    }
}
