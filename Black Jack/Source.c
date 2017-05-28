#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>   
#include <conio.h>
#include <process.h>
#include <string.h>

//if cannot see the symbols of card please turn your console the oldest one
#define heart   03
#define diamond 04
#define club    05
#define spade   06

void decks();
void shuffle_deck();
char cardtype(int);
char cardface(int);
int playertotal(int, int);
void scorecheck();

int Numplayer;
int i, x, m = 0, a = 0, counter = 0, aceVal, dealt = 0,flag,b=-1,finish=0,showsecond,secondval;
int Cre_deck[52], shuf_deck[52], move[52],move1[52], score[52], countermove[52], totalWin[52], totalLose[52], totaltie[52];
int begin, Dealer_total;

int main()
{
	do {
			printf("!!!Welcome BlackJack Game!!!\n");
			printf("\t   %c %c %c %c\n\n", spade, club, heart, diamond);
			printf("Press <1> to Start-->\n\n");scanf_s("%d", &begin);
			system("cls");
		} while (begin<1 || begin>1);
				
		if (begin == 1)
		{
			do {
				do {
					printf("How Many Player(Max-7)-->?\n\n");scanf_s("%d", &Numplayer);
					system("cls");
				} while(Numplayer>7 || Numplayer<1);

				decks();

				srand((unsigned)time(NULL));
				shuffle_deck();
				printf("\n");
				printf("!!!Decks Shuffled!!!\n\n");
				a = 0;

				do
				{
					if (dealt >= 52 - (Numplayer + 1) * 2) {
						system("cls");
						flag = 1;
						break;
					}

					for (x = 1;x <= (Numplayer + 1);x++)
					{
						if (x == 1)
						{
							printf("Dealer hand is: %c%c -- ??\n\n", cardtype(dealt), cardface(dealt));
							showsecond = (dealt + Numplayer + 1); secondval = shuf_deck[showsecond];//to show second card

							playertotal(dealt, x);
							playertotal(dealt + Numplayer + 1, x);
							Dealer_total = score[x - 1];
							dealt++;
						}

						else
						{
							printf("%d.Player Card is : %c%c -- %c%c \n", x - 1, cardtype(dealt), cardface(dealt), cardtype(dealt + Numplayer + 1), cardface(dealt + Numplayer + 1));
							playertotal(dealt, x);
							playertotal(dealt + Numplayer + 1, x);
							printf("%d.Player Score is  : %d\n\n", x - 1, score[x - 1]);
							dealt++;
						}
					}

					dealt += Numplayer+1;
				
					if (dealt >= 51 - (Numplayer + 1) * 2) {
						system("cls");
						flag = 1;
						break;
					}

					for (x = 1;x <= Numplayer;x++)
					{
						do {
							printf("%d.Player --> Hit<1> or Stand<2>", x);
							scanf_s("%d", &move[x - 1]);
						} while (move[x - 1] < 1 || move[x - 1]>2);
					}
					printf("\n\n");

					for (x = 2;x <= Numplayer + 1;x++)
					{
						if (move[x - 2] == 1)
						{
							printf("%d.Player Next card is %c%c\n", x - 1, cardtype(dealt), cardface(dealt));
							playertotal(dealt, x);
							printf("%d.Player total score is %d\n\n", x - 1, score[x - 1]);

							if (score[x - 1] < 21)
							{
								countermove[m] = x;
								m++;
							}

							dealt++;							
						}
						else
							printf("%d.Player total score is %d and No more cards wanted..\n\n", x - 1, score[x - 1]);
					}
					m = 0;

					if (dealt >= 51 - (Numplayer + 1) * 2) {
						system("cls");
						flag = 1;
						break;
					}
				
					for (x = 2;x <=( Numplayer*2+1 );x++)
					{
						if (countermove[m] == x)
						{
							do {
								printf("%d.Player --> Hit<1> or Stand<2>", x - 1);
								scanf_s("%d", &move1[x - 1]);
							} while (move1[x-1]<1 || move1[x-1]>2);

							if (move1[x - 1] == 1)
							{								
								printf("%d.Player Next card is %c%c\n", x - 1, cardtype(dealt), cardface(dealt));
								playertotal(dealt, x);
								printf("%d.Player total score is %d\n\n", x - 1, score[x - 1]);
								dealt++;				
							}
							m++;
						}

						if (x > (Numplayer+1)) {
							if ((score[x - (Numplayer+1) ] < 17 && move1[x-1]==2) || (score[x - (Numplayer + 1)] < 17 && move1[x - 1] == 2))
							{
								do {
									printf("%d.Player --> Hit<1> or Stand<2>", x - (Numplayer + 1));
									scanf_s("%d", &move1[x - 1]);
								} while (move1[x - 1] < 1 || move1[x - 1] > 2);

								if (move1[x - 1] == 1)
								{
									printf("%d.Player Next card is %c%c\n", x - (Numplayer + 1), cardtype(dealt), cardface(dealt));
									playertotal(dealt, (x - (Numplayer)));
									printf("%d.Player total score is %d\n\n", x - (Numplayer + 1), score[x - (Numplayer+1)]);
									dealt++;
								}
							}
						}
					}

					if (dealt >= 51 - (Numplayer + 1) * 2) {
						system("cls");
						flag = 1;
						break;
					}

					if (score[0] < 17)
					{
						shuf_deck[showsecond] = secondval;
						printf("Dealer second card is :%c%c\n", cardtype(showsecond), cardface(showsecond));
						do {

							printf("Dealer next card is: %c%c\n", cardtype(dealt), cardface(dealt));
							x = 1;
							playertotal(dealt, x);
							dealt++;
						
						} while (score[0] < 17);

						printf("Dealer hand total is: %d\n\n", score[0]);
						Dealer_total = score[0];
					}
					else {
						shuf_deck[showsecond] = secondval;
						printf("Dealer second card is :%c%c\nDealer hand total is: %d\n\n", cardtype(showsecond), cardface(showsecond), score[0]);
					}


					if (dealt > 51 - (Numplayer + 1) * 2) {
						system("cls");
						flag = 1;
						break;
					}

					for (x = 1;x <= Numplayer;x++)
					{
						if (x == 1)
							printf("\n\nResults!!\n\n\n\a\a\a");
						scorecheck();
					}

					do {
						printf("Press <1>-->Play Again\nPress<2>-->To Exit\n");scanf_s("%d", &begin);
					} while (begin < 1 || begin>2);

					if (begin == 2)
					{
						system("cls");
						printf("Thanks For Playing (: !!");
						finish = 1;
						break;
					}
					for (x = 0;x <= 51;x++)
					{
						score[x] = 0;
						move[x] = 0;
						countermove[x] = 0;
					}
					m = 0;
					system("cls");

				} while (begin == 1);


				if (finish != 1)
				{
					if (flag == 1)
					{
						printf("Game is aborted!!");
						for (x = 1;x <= Numplayer;x++)
						{
							if (x == 1)
								printf("\n\nFinal Results!!\n\n\n\a\a\a");
							printf("%d.player Win-->%d Tie-->%d Lose-->%d\n\n", x, totalWin[x - 1], totaltie[x - 1], totalLose[x - 1]);
						}
					}

					do {
						printf("Press-->1 to play New Game!!\nPress-->2 to Exit!!\n");scanf_s("%d", &begin);
					} while (begin < 1 || begin>2);

					system("cls");

					if (begin == 2) {
						printf("Thanks For Playing :)\n");break;
					}

					else if (begin == 1) {

						for (x = 0;x <= 20;x++)
						{
							score[x] = 0;	move[x] = 0; countermove[x] = 0; totalWin[x] = 0; totalLose[x] = 0; totaltie[x] = 0;
						}
					}
					dealt = 0;
					m = 0;
					a = 0;

					printf("!!!>--Welcome  BlackJack Game Again--<!!!\n");
					printf("\t    %c %c %c %c\n\n", spade, club, heart, diamond);
				}
			}while (begin==1);
		}

	printf("\n\n");
	system("pause");
}


void decks()
{
	for (i = 0; i <= 51; i++)
	{
		Cre_deck[i] = i + 1;
	}
}

void shuffle_deck()
{
	while (a < 52)
	{
		counter = rand() % 52;

		if (Cre_deck[counter] != 0)
		{
			shuf_deck[a] = Cre_deck[counter];
			Cre_deck[counter] = 0;	
			a++;
		}		
	}
}

char cardtype(dealt)
{
	if (shuf_deck[dealt] <= 13)
	{
		return heart;
	}

	else if (shuf_deck[dealt] >= 14 && shuf_deck[dealt] <= 26)
	{
		return diamond;
	}
	else if (shuf_deck[dealt] >= 27 && shuf_deck[dealt] <= 39)
	{
		return club;
	}
	else if (shuf_deck[dealt] >= 40)
	{
		return spade;
	}
}

char cardface(dealt)
{
	if (shuf_deck[dealt] <= 13)
	{
		if (shuf_deck[dealt] >= 2 && shuf_deck[dealt] <= 10)
		{
			switch (shuf_deck[dealt])
			{
			case 2: return '2';
			case 3: return '3';
			case 4: return '4';
			case 5: return '5';
			case 6: return '6';
			case 7: return '7';
			case 8: return '8';
			case 9: return '9';
			case 10: return 'T';
			}
		}
		else if (shuf_deck[dealt] == 13)
		{
			return 'K';
		}
		else if (shuf_deck[dealt] == 12)
		{
			return 'Q';
		}
		else if (shuf_deck[dealt] == 11)
		{
			return 'J';
		}
		if (shuf_deck[dealt] == 1)
		{
			return 'A';
		}
	}

	else if (shuf_deck[dealt] >= 14 && shuf_deck[dealt] <= 26)
	{
		if (shuf_deck[dealt] - 13 >= 2 && shuf_deck[dealt] - 13 <= 10)
			switch (shuf_deck[dealt] - 13)
			{
			case 2: return '2';
			case 3: return '3';
			case 4: return '4';
			case 5: return '5';
			case 6: return '6';
			case 7: return '7';
			case 8: return '8';
			case 9: return '9';
			case 10: return 'T';
			}

		else if (shuf_deck[dealt] - 13 == 13)
		{
			return 'K';
		}
		else if (shuf_deck[dealt] - 13 == 12)
		{
			return 'Q';
		}
		else if (shuf_deck[dealt] - 13 == 11)
		{
			return 'J';
		}

		if (shuf_deck[dealt] - 13 == 1)
		{
			return 'A';
		}
	}

	else if (shuf_deck[dealt] >= 27 && shuf_deck[dealt] <= 39)
	{
		if (shuf_deck[dealt] - 26 >= 2 && shuf_deck[dealt] - 26 <= 10)

			switch (shuf_deck[dealt] - 26)
			{
			case 2: return '2';
			case 3: return '3';
			case 4: return '4';
			case 5: return '5';
			case 6: return '6';
			case 7: return '7';
			case 8: return '8';
			case 9: return '9';
			case 10: return 'T';
			}

		else if (shuf_deck[dealt] - 26 == 13)
		{
			return 'K';
		}
		else if (shuf_deck[dealt] - 26 == 12)
		{
			return 'Q';
		}
		else if (shuf_deck[dealt] - 26 == 11)
		{
			return 'J';
		}

		if (shuf_deck[dealt] - 26 == 1)
		{
			return 'A';
		}
	}

	else if (shuf_deck[dealt] >= 40)
	{
		if (shuf_deck[dealt] - 39 >= 2 && shuf_deck[dealt] - 39 <= 10) {
			switch (shuf_deck[dealt] - 39)
			{
			case 2: return '2';
			case 3: return '3';
			case 4: return '4';
			case 5: return '5';
			case 6: return '6';
			case 7: return '7';
			case 8: return '8';
			case 9: return '9';
			case 10: return 'T';
			}
		}
		else if (shuf_deck[dealt] - 39 == 13)
		{
			return 'K';
		}
		else if (shuf_deck[dealt] - 39 == 12)
		{
			return 'Q';
		}
		else if (shuf_deck[dealt] - 39 == 11)
		{
			return 'J';
		}

		if (shuf_deck[dealt] - 39 == 1)
		{
			return 'A';
		}
	}
}

int playertotal(dealt, x)
{

	if (shuf_deck[dealt] <= 13)
	{
		if (shuf_deck[dealt] > 10)
			shuf_deck[dealt] = 10;
		if (shuf_deck[dealt] == 1)
		{
				if (x == 1 && score[x - 1] < 11)
					shuf_deck[dealt] = 11;
				else if (x == 1 && score[x - 1] >= 11)
					shuf_deck[dealt] = 1;
				else {
					do {
						printf("Choose Value of Ace 1 <press 1>--11 <press 2>");scanf_s("%d", &aceVal);
					} while (aceVal < 1 || aceVal>2);
					if (aceVal == 1)
						shuf_deck[dealt] = 1;
					else
						shuf_deck[dealt] = 11;
				}			
		}
		score[x - 1] = score[x - 1] + shuf_deck[dealt];
	}

	else if (shuf_deck[dealt] >= 14 && shuf_deck[dealt] <= 26)
	{
		if (shuf_deck[dealt] > 23)
			shuf_deck[dealt] = 23;
		if (shuf_deck[dealt] == 14)
		{
			if (x == 1 && score[x - 1] < 11)
				shuf_deck[dealt] = 24;
			else if (x == 1 && score[x - 1] >= 11)
				shuf_deck[dealt] = 14;
			else {
				do {
					printf("Choose Value of Ace 1 <press 1>--11 <press 2>");scanf_s("%d", &aceVal);
				} while (aceVal < 1 || aceVal>2);
				if (aceVal == 1)
					shuf_deck[dealt] = 14;
				else
					shuf_deck[dealt] = 24;
			}
		}

		score[x - 1] = score[x - 1] + shuf_deck[dealt] - 13;
	}

	else if (shuf_deck[dealt] >= 27 && shuf_deck[dealt] <= 39)
	{

		if (shuf_deck[dealt] > 36)
			shuf_deck[dealt] = 36;
		if (shuf_deck[dealt] == 27)
		{
			if (x == 1 && score[x - 1] < 11)
				shuf_deck[dealt] = 37;
			else if (x == 1 && score[x - 1] >= 11)
				shuf_deck[dealt] = 27;
			else {
				do {
					printf("Choose Value of Ace 1 <press 1>--11 <press 2>");scanf_s("%d", &aceVal);
				} while (aceVal < 1 || aceVal>2);
				if (aceVal == 1)
					shuf_deck[dealt] = 27;
				else
					shuf_deck[dealt] = 37;
			}
		}
		score[x - 1] = score[x - 1] + shuf_deck[dealt] - 26;
	}

	else if (shuf_deck[dealt] >= 40)
	{
		if (shuf_deck[dealt] > 49)
			shuf_deck[dealt] = 49;
		if (shuf_deck[dealt] == 40)
		{
			if (x == 1 && score[x - 1] < 11)
				shuf_deck[dealt] = 50;
			else if (x == 1 && score[x - 1] >= 11)
				shuf_deck[dealt] = 40;
			else
			{
				do {
					printf("Choose Value of Ace 1 <press 1>--11 <press 2>");scanf_s("%d", &aceVal);
				} while (aceVal < 1 || aceVal>2);
				if (aceVal == 1)
					shuf_deck[dealt] = 40;
				else
					shuf_deck[dealt] = 50;
			}
		}

		score[x - 1] = score[x - 1] + shuf_deck[dealt] - 39;
	}
	return score[x - 1];
}

void scorecheck()
{

	if (score[x] <= 21)
	{
		if (Dealer_total < score[x])
		{
			printf("%d.Player Win!!\n", x);
			totalWin[x - 1] += 1;
		}
		else if (Dealer_total > score[x] && Dealer_total>21)
		{
			printf("%d.Player Win!!\n", x);
			totalWin[x - 1] += 1;
		}
		else if (Dealer_total > score[x] && Dealer_total <= 21)
		{
			printf("%d.Player is Bust!!!\n", x);
			totalLose[x - 1] += 1;
		}
		else if (Dealer_total == score[x])
		{
			printf("%d.Player and Dealer are Tie\n", x);
			totaltie[x - 1] += 1;
		}

	}
	else if (Dealer_total == score[x])
	{
		printf("%d.Player and Dealer are Tie\n", x);
		totaltie[x - 1] += 1;
	}
	else if (score[x] > 21)
	{
		printf("%d.Player is Bust!!!\n", x);
		totalLose[x - 1] += 1;
	}
	printf("%d.player Win-->%d Tie-->%d Lose-->%d\n\n", x, totalWin[x - 1], totaltie[x - 1], totalLose[x - 1]);
}
