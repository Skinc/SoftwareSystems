/*
	By Shane Skikne 1/29/14
	For Software Systems. Olin
*/


#include <stdio.h>
#include <stdlib.h>
int main()
{
	char card_name[3];
	int count = 0;
	while (card_name[0] != 'X'){
		puts("Enter the card_name: ");
		scanf("%2s", card_name);
		int card_Val = checkCard(card_name);
		if (card_Val > -1){
			count =	updateCount(card_Val, count);
			printf("Current count:%i\n", count);

		}
		
	}
	return 0;
}

// checkCard takes a card Char and checks if it is a valid card. 
//If the card is valid, checkCard returns its value in BlackJack. If the card is invalid, it returns -1.
int checkCard(char card[3]){
	int val = 0;
	switch(card[0]){
	case 'K':
	case 'Q':
	case 'J':
		val = 10;
		break;
	case 'A':
		val = 11;
		break;
	case 'X':
		val = -1;
		break;
	default:
		val = atoi(card);
		if ((val < 1) || (val >10)){
			puts("I don't understand that value!");
			val = -1;	

		}
	}
	return val;
}

//updateCount takes the value of the card and the current count and updates the count if necessary. 
int updateCount(int val, int count){
	if ((val >2) && (val <7)){
			count++;
	} else if (val == 10) {
			count--;
	}
	return count;
}
