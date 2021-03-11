/**
 * Pranav Grover
 * COEN 11
 * Lab 8
 * Wednesday 5:15PM
 * 
 * Created Mar. 3, 2020
 */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# define NODE struct entry

// Initialize globals
struct entry {
    char name[20];
    int size;
    NODE* next;
    NODE* previous;
};

NODE* head;
NODE* tail;

int checkDuplicate(char name[20]) {
    int duplicate = 0;
    NODE *node = head;
    while(node != NULL && !duplicate) {
        if(strcmp(node->name, name) == 0) {
            duplicate = 1;
        }
        node = node->next;
    }
    return duplicate;
}

/**
 * Removes an element from a linked list.
 * @param {int} arr[10] Target array
 * @param {int} index Index to remove element from
 * @returns void
 */
void removeNode(NODE* node) {
    if(node != NULL) {
        if(node != head && node != tail) {
            node->next->previous = node->previous;
            node->previous->next = node->next;
        }
        if(node == head) {
            head = node->next;
            if(head != NULL) {
                head->previous = NULL;
            }
        }
        if (node == tail) {
            tail = node->previous;
            if(tail != NULL) {
                tail->next = NULL;
            }
        }
        free(node);
    }
}

/**
 * Recursive function which calls the same function with the next element in the linked list, and then prints the name and size of each group.
 */
void backwardList(NODE* node) {
    if(node->next != NULL) {
        backwardList(node->next);
    }
    printf("%20s | %d\n", node->name, node->size);
}

/**
 * Recursive function which calls the same function with the next character in the name, and then prints it one character at a time.
 */
void backwardName(char* name, int i) {
    if(*(name + i) != '\0') {
        backwardName(name, i + 1);
    }
    printf("%c", name[i]);
}

void deleteList(NODE* node) {
    if(node->next != NULL) {
        deleteList(node->next);
    }
    removeNode(node);
}

/**
 * Inserts a group to the end of the waiting list.
 * @param {char} name[20] Name of the group
 * @param {int} size Size of the group 
 * @returns void
 */
void insert(char name[20], int size) {
    if(!checkDuplicate(name)) {
        NODE *node = (NODE*) malloc(sizeof(NODE));
        strcpy(node->name, name);
        node->size = size;
        node->previous = tail;
        node->next = NULL;
        if(head == NULL)
            head = node;
        if(tail != NULL)
            tail->next = node;
        tail = node;
    } else {
        printf("Error: Duplicate name. %s could not be added.\n", name);
    }
}

/**
 * Removes a set number of people from the group. This starts from the oldest possible matches, and continues to remove groups until there are no more spots left.
 * @param {int} size Size of the opening 
 * @returns void
 */
void delete(int size) {
    struct entry *node = head;
    while(node != NULL && size >= 0) {
        if(node->size <= size) {
            size -= node->size;
            printf("%s was removed, a group of %d people.\n", node->name, node->size);
            removeNode(node);
        }
        node = node->next;
    }
}

void searchSize(int size) {
    NODE *node = head;
    if(node == NULL) {
        printf("The list is empty.");
    } else if(size <= 0) {
        printf("There are no entries below the specified size.");
    } else {
        printf("                 WAITING LIST\n");
        printf("%20s | Group Size\n", "Name");
        printf("---------------------|---------------------\n");
        while(node != NULL) {
            if(node->size <= size) {
                printf("%20s | %d\n", node->name, node->size);
            }
            node = node->next;
        }
    }
}

/**
 * Prints the current waiting list, or indicates if the list is empty
 * @returns void
 */
void list(void) {
    NODE *node = head;
    if(node == NULL) {
        printf("The list is empty.");
    } else {
        printf("                 WAITING LIST\n");
        printf("%20s | Group Size\n", "Name");
        printf("---------------------|---------------------\n");
        while(node != NULL) {
            printf("%20s | %d\n", node->name, node->size);
            node = node->next;
        }
    }
}

void backLists() {
    if(head == NULL) {
        printf("The list is empty.");
    } else {
        backwardList(head);
    }
}

void backNames() {
    if(head == NULL) {
        printf("The list is empty.");
    } else {
        NODE *node = head;
        while(node != NULL) {
            backwardName(node->name, 0);
            printf("\n");
            node = node->next;
        }
    }
}

/** FILE I/O **/
void readAll(char* filename) {
    FILE* file = fopen(filename, "r");
    char name[20];
    int size;
    if(file == NULL) {
        file = fopen(filename, "w+");
    }
    while(!feof(file)) {
        fscanf(file, "%[^,],", name);
        fscanf(file, "%d\n", &size);
        if(size) {
            printf("Adding group '%s' with size %d\n", name, size);
            insert(name, size);
        }
    }
    
    fclose(file);
}

void saveAll(char* filename) {
    
    FILE* file = fopen(filename, "w");
    if(file == NULL) {
        printf("Error: Invalid file!\n");
    } else {
        NODE *node = head;
        if(node == NULL) {
            // The list is empty
        } else {
            while(node != NULL) {
                fprintf(file, "%s,", node->name);
                fprintf(file, "%d\n", node->size);
                node = node->next;
            }
        }
    }
    fclose(file);
}

void quit(char* filename) {
    saveAll(filename);
    deleteList(head);
}

/**
 * The entry point for the program.
 */
int main(int argc, char *argv[]) {
    char* WAITING_LIST_FILE = argv[1];

    if(argc == 1) {
        printf("Error: The name of the file is missing!\n");
        return 1;
    } else {
        readAll(WAITING_LIST_FILE);
    }

    int choice;
    while(1) {
        printf("Welcome to the waiting room. Please select your choice: \n\n\
        1) View the waiting list\n\
        2) Add a name to the waiting list\n\
        3) Remove a group from the waiting list\n\
        4) Find groups below a certain size\n\
        5) Fill the list with names\n\
        6) Display the list in reverse order\n\
        7) Display the names backwards\n\
        0) Save the list and exit\
        \n\n> ");
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
            if(head != NULL) {
                printf("\n\nHow many members would you like to remove?\n> ");
                scanf(" %d", &size);
                printf("Removing %d members...\n", size);
                delete(size);
            }
        } else if (choice == 4) {
            // Remove a group from the waiting list
            int size;
            if(head != NULL) {
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
            backLists();
        }  else if (choice == 7) {
            backNames();
        }  else if (choice == 0) {
            quit(WAITING_LIST_FILE);
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
