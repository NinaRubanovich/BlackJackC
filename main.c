#include "blackjack.h"

int main() {
	double userMoney = 0.0;
	double userBet = 0.0;
	char readRules[10];
	int currentCard = 0;
	Card deck[CARDS];
	int userTotal = 0;
	int dealerTotal = 0;
	char playAgainInput[10];
	bool playAgain = true;
	bool hit = true;
	char hitOrStand[10];

	const char *face[] = {"Ace", "Deuce", "Three", "Four",
	 					"Five","Six", "Seven", "Eight", 
	 					"Nine", "Ten", "Jack", "Queen",
	 					"King"
	 					};
	const char *suit[] = {"♥︎Hearts♥︎", "♦︎Diamonds♦︎", "♣︎Clubs♣︎", "♠︎Spades♠︎"};

	srand(time(NULL));
	fillDeck(deck, face, suit);
	shuffle(deck);

	printf("--------------------------------------------------------------------------------\n");
	printf("♥︎♦︎♣︎♠︎ WELCOME TO BLACJACK ♥︎♦︎♣︎♠︎\n\n");

	printf("How much money are bringing to the table? Enter here: $");
	scanf("%lf", &userMoney);

	printf("\nWould you like to read the rules? Enter \"yes\" or \"no\": ");
	scanf("%s", readRules);

	while ((strstr(readRules, "yes") == NULL) && (strstr(readRules, "no") == NULL)) {
			printf("Please enter either \"yes\" or \"no\": ");
			scanf("%s", readRules);
		}

	sleep(1);
	if (strstr(readRules, "yes") != NULL) { // user entered "yes"
		printf("\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_  RULES  _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
		printf("At each game, both the dealer and you place your bet. You are first dealt\n");
		printf("two cards face up, while the dealer recieves one card face-up and one card\n");
		printf("face down. You are then given a chance to draw more cards. You can either\n");
		printf("\"hit\" or \"stand\".If you call out \"HIT\", you are given an extra card.\n");
		printf("You can then either call \"HIT\" again, or \"STAND\" if you do not wish to\n");
		printf("draw any more cards. You can \"hit\" as many times, but aim not to \"bust\"\n");
		printf("(exceed a total of 21). If you bust, you immediatly lose your bet. After you\n");
		printf("have either stood or busted, the dealer takes their turn. The \"hit\" and\n");
		printf("\"stand\" rules are the same. If the dealer reaches a valid hand, their total\n");
		printf("card value is compared to yours. If you score higher than the dealer, you win.\n");
		printf("If the dealer scores higher than you, you lose. If you tie with the dealer, the\n");
		printf("original bet is returned to the player. a perfect hand combines an ace with a\n");
		printf("Ten, Jack, Queen, or King and is known as \'BlackJack\'.\n");
		printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n");
	}
	sleep(1);
	
	do {
			sleep(1);
			printf("\n-_-_-_-_ LET'S BEGIN! -_-_-_-_\n");
			shuffle(deck);
			userTotal = 0;
			dealerTotal = 0;
			currentCard = 0;
			hit = true;
			printf("Place your bet: $");
			scanf("%lf", &userBet);

			while (userBet > userMoney) {
				printf("**You can't bet more money than you have!**\n");
				printf("Place your bet: $");
				scanf("%lf", &userBet);
			}

			sleep(1);
			printf("You have been dealt: %s of %s", deck[currentCard].face, deck[currentCard].suit);
			if (isAce(deck[currentCard].face) == true) {
				printf(" and %s of %s\n", deck[currentCard+1].face, deck[currentCard+1].suit);
				usersTurn(&currentCard, deck[currentCard].face, &userTotal, deck);
			}
			else { 
				printf(" and ");
				usersTurn(&currentCard, deck[currentCard].face, &userTotal, deck);
				printf("%s of %s\n", deck[currentCard].face, deck[currentCard].suit);
			}
			usersTurn(&currentCard, deck[currentCard].face, &userTotal, deck);
			printf("Your current total is %d points.\n\n", userTotal);
			if ( isBlackJack(userTotal) == true) {
				// user gets BlackJack
				userMoney+= 100;
				printf("YOU GOT A BLACKJACK! You have won $%d and now have $%.2f total.\n", 100, userMoney);
				playAgain = playAgainFunc(playAgainInput);
				if (playAgain == true) {
					continue;
					continue;
				}
				else break;	
			}

			sleep(1);
			printf("Dealer has been dealt: %s of %s and another card face down.\n", deck[currentCard].face, deck[currentCard].suit);
			printf("Dealer's total is hidden.\n\n");
			dealersTurn(&currentCard, deck[currentCard].face, &dealerTotal, deck);
			// next card is the dealer's face down card (not revealed to the player)

			sleep(1);
			if ( isBlackJack(dealerTotal) == true ) {
				// dealer gets BlackJack
				userMoney -= userBet;
				printf("Dealer got BlackJack! You lost $%.2f and now have $%.2f total.\n", userBet, userMoney);
				playAgain = playAgainFunc(playAgainInput);
				if (playAgain == true) {
					continue;
					continue;
				}
				else break;	
			}

			while (userTotal < 21 && dealerTotal < 21 && hit == true) {
				// neither player got BlackJack, so game continues
				sleep(1);
				printf("Would you like to hit or stand? Enter \"hit\" or \"stand\": ");
				scanf("%s", hitOrStand);
				while ((strstr(hitOrStand, "hit") == NULL) && (strstr(hitOrStand, "stand") == NULL)) {
						printf("Please enter either \"hit\" or \"stand\": ");
						scanf("%s", hitOrStand);
				}
					sleep(2);
					if ((strstr(hitOrStand, "hit") != NULL)) {
						// player hits
						hit = true;
						printf("You have been dealt: %s of %s\n", deck[currentCard].face, deck[currentCard].suit);
						usersTurn(&currentCard, deck[currentCard].face, &userTotal, deck);
						printf("Your current total is %d points.\n\n", userTotal);

						if (userTotal > 21) break;

					}
					else {
						// player stands
						hit = false;
						sleep(2);
						printf("Dealer's hidden card is: %s of %s.\n", deck[currentCard].face, deck[currentCard].suit);
						dealersTurn(&currentCard, deck[currentCard].face, &dealerTotal, deck);
						printf("The dealer's total is %d points.\n\n", dealerTotal);

						while (dealerTotal < 17) {
							sleep(2);
							printf("Dealer chooses to hit.\n");
							printf("Dealer's has been dealt: %s of %s.\n", deck[currentCard].face, deck[currentCard].suit);
							dealersTurn(&currentCard, deck[currentCard].face, &dealerTotal, deck);
							printf("The dealer's total is %d points.\n\n", dealerTotal);
						}

						sleep(2);
						if (dealerTotal <= 21) printf("Dealer has chosen to stand.\n");

						}
					}

					sleep(1);
					printf("\n*-*-*-*-* FINAL RESULTS: *-*-*-*-*\n");
					sleep(2);
					if (userTotal > 21) {
						// player busts
						userMoney -= userBet;
						printf("BUST! You lost $%.2f and now have $%.2f total.\n", userBet, userMoney);
						playAgain = playAgainFunc(playAgainInput);
						if (playAgain == true) {
							continue;
							continue;
						}
						else break;	
					}
					else if (dealerTotal > 21) {
						// dealer busts
						userMoney += userBet;
						printf("Dealer busted! You won $%.2f and now have $%.2f total.\n", userBet, userMoney);
						playAgain = playAgainFunc(playAgainInput);
						if (playAgain == true) {
							continue;
							continue;
						}
						else break;	
					}
					else if (userTotal > dealerTotal) {
						// player wins
						userMoney += userBet;
						printf("You won! You gained $%.2f and now have $%.2f total.\n", userBet, userMoney);
						playAgain = playAgainFunc(playAgainInput);
						if (playAgain == true) {
							continue;
							continue;
						}
						else break;	
					}
					else if (dealerTotal > userTotal) {
						// dealer wins
						userMoney -= userBet;
						printf("Dealer won... You lost $%.2f and now have $%.2f total.\n", userBet, userMoney);
						playAgain = playAgainFunc(playAgainInput);
						if (playAgain == true) {
							continue;
							continue;
						}
						else break;	
					}
					else {
						// tie
						printf("TIE! No one wins or loses anything. You still have $%.2f total.\n", userMoney);
						playAgain = playAgainFunc(playAgainInput);
						if (playAgain == true) {
							continue;
							continue;
						}
						else break;	
					}
	
	} while (userMoney > 0.0 && playAgain == true);
	printf("--------------------------------------------------------------------------------\n");
	if (playAgain == true) printf("Uh oh... looks like you ran out of money!\n");
	else printf("Thank you for playing!\n");
}