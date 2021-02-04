/**
 * Pranav Grover
 * COEN 10
 * Lab 3
 * Wednesday 5:15PM
 * 
 * Created Jan. 27, 2020
 */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>

// Initialize globals
int counter = 0;
struct entry {
    char name[20];
    int size;
};

struct entry waitingList[10];

/**
 * Removes an element from array of entries at a specified index.
 * @param {int} arr[10] Target array
 * @param {int} index Index to remove element from
 * @returns void
 */
void shift(struct entry arr[10], int index) {
    for(int i = index; i < 9; i++) {
        struct entry *node;
        node = &arr[i];
        struct entry *nextNode;
        nextNode = &arr[i + 1];
        memcpy(node->name, nextNode->name, 20);
        node->size = nextNode->size;
    }
    struct entry * empty;
}

/**
 * Removes an element from array of strings at a specified index.
 * @param {char} arr[10][20] Target array
 * @param {int} index Index to remove element from
 * @returns void
 */
void shiftString(char arr[10][20], int index) {
    for(int i = index; i < 9; i++) {
        strcpy(arr[i], arr[i + 1]);
    }
    strcpy(arr[9], "");
}

/**
 * Inserts a group into the waiting list. Prints an error if the list is full.
 * @param {char} name[20] Name of the group
 * @param {int} size Size of the group 
 * @returns void
 */
void insert(char name[20], int size) {
    if(size <= 0) {
        printf("Invalid size!");
    } else if(counter < 10) {
        waitingList[counter].size = size;
        strcpy(waitingList[counter].name, name);
        counter++;
    } else {
        printf("\n\nThe list is full. Please remove some members and try again later.");
    }
}

/**
 * Removes a set number of people from the group. This starts from the oldest possible matches, and continues to remove groups until there are no more spots left.
 * @param {int} size Size of the opening 
 * @returns void
 */
void removes(int size) {
    int i = 0;
    while(size > 0 && i < counter) {
        if(waitingList[i].size <= size) {
            size -= waitingList[i].size;
            counter--;
            printf("%s was removed, a group of %d people.\n", waitingList[i].name, waitingList[i].size);
            shift(waitingList, i);
        } else {
            i++;
        }
    }
}

void searchSize(int size) {
    if(counter == 0) {
        printf("The list is empty.");
    } else if(size <= 0) {
        printf("There are no entries below the specified size.");
    } else {
        printf("                 WAITING LIST\n");
        printf("%20s | Group Size\n", "Name");
        printf("---------------------|---------------------\n");
        for(int i = 0; i < counter; i++) {
            if(waitingList[i].size <= size)
            printf("%20s | %d\n", waitingList[i].name, waitingList[i].size);
        }
    }
}

int checkDuplicate(char name[20]) {
    for(int i = 0; i < 20; i++) {
	if(strcmp(waitingList[i].name, name) == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * Prints the current waiting list, or indicates if the list is empty
 * @returns void
 */
void list(void) {
    if(counter == 0) {
        printf("The list is empty.");
    } else {
        printf("                 WAITING LIST\n");
        printf("%20s | Group Size\n", "Name");
        printf("---------------------|---------------------\n");
        for(int i = 0; i < counter; i++) {
            printf("%20s | %d\n", waitingList[i].name, waitingList[i].size);
        }
    }
}

/**
 * The entry point for the program.
 */
int main() {
    int choice;
    while(1) {
        printf("Welcome to the waiting room. Please select your choice: \n\n1) View the waiting list\n2) Add a name to the waiting list\n3) Remove a group from the waiting list\n4) Find groups below a certain size\n5) Fill the list with names\n6) Exit\n\n> ");
        scanf(" %d", &choice);

        if (choice == 1) {
            // List is printed after every command
        }
        else if (choice == 2) {
            // Adds a member to the waiting list
            if(counter < 10) {
                char name[20];
                int size;
                printf("\n\nWhat name would you like to add?\n> ");
                scanf(" %s", name);
                if(checkDuplicate(name)==1) {
			printf("\n\nSorry, that name is already there\n");
			continue;
		}
		printf("\n\nWhat size group do you have?\n> ");
                scanf(" %d", &size);
                insert(name, size);
            } else {
                printf("\n\nThe list is full. Please remove some members and try again later.");
            }
        } else if (choice == 3) {
            // Remove a group from the waiting list
            int size;
            if(counter > 0) {
                printf("\n\nHow many members would you like to remove?\n> ");
                scanf(" %d", &size);
                printf("Removing %d members...\n", size);
                removes(size);
            }
        } else if (choice == 4) {
            // Remove a group from the waiting list
            int size;
            if(counter > 0) {
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
