#include <stdio.h>

int main() {
	srand((int) time (NULL));
	int score = 0;
 	int i = 0;
	while(i < 10) {
		int a = rand() % 12 + 1;
		int b = rand() % 13;
		int response;
		printf("\nWhat is %d divided by %d?\n> ", b, a);
		scanf("%d", &response);
		if(divide(response, b / a)) {
			printf("\nThat is correct!");
			score++;
		} else {
			printf("\nThat is not correct.");
		}
	i++;
	}
	printf("\nYou had %d correct answers out of 10", score);
}

int divide(int response, int actual) {
	return response == actual ? 1 : 0;
}
