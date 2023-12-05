#include <stdio.h>
#define TOTAL_TURNS 10

struct GAME_STATUS {
	signed short year;
	signed int starved_people;
	signed int new_comers;
	signed int population;
	signed int total_acres;
	signed int total_bushels;
	signed int harvested_bushels;
	signed int destroyed_bushels;
	signed int acre_price; 
};

void show_header(void);
void show_status(GAME_STATUS* status);
int negotiate_acres();
int feed_people();
int cultivate_acres();

int main()
{
	show_header();

    signed short turn = 1;
	while (turn < TOTAL_TURNS)
	{
		struct GAME_STATUS status;
		status.year = turn;
		status.starved_people = 10;
		status.new_comers = 10;
		status.population = 10;
		status.total_acres = 10;
		status.harvested_bushels = 10;
		status.destroyed_bushels = 10;
		status.total_bushels = 10;
		status.acre_price = 10;

		show_status(&status);

		turn++;
	} 
}

void show_status(GAME_STATUS* status)
{
	negotiate_acres();
	feed_people();
	cultivate_acres();

	printf("Hammurabi: I beg to report to you,\n");
	printf("In Year %i, %d people starved.\n", status->year, status->starved_people);
	printf("%d people came to the city.\n", status->new_comers);
	printf("The city population is now %d.\n", status->population);
	printf("The city now owns %d acres.\n", status->total_acres);
	printf("You harvested %d bushels per acre.\n", status->harvested_bushels);
	printf("Rats ate %d bushels.\n", status->destroyed_bushels);
	printf("You now have %d bushels in store.\n", status->total_bushels);
	printf("Land is trading at %d bushels per acre.\n\n", status->acre_price);
	printf("--------------------------------------------------------------\n\n");
}

void show_header(void)
{

	printf("********************************************************************************\n");
	printf("****                           HAMMURABI THE GAME                            ***\n");
	printf("****                                   by                                    ***\n");
	printf("****                               Julio Murta                               ***\n");
	printf("********************************************************************************\n\n\n");
}

int negotiate_acres()
{
	printf("How many acres do you wish to buy or sell? (enter a negative amount to sell bushels)\n");
	return 0;
}

int feed_people()
{
	printf("How many bushels do you wish to feed your people? (each citizen needs 20 bushels a year)\n");
	return 0;
}

int cultivate_acres()
{
	printf("How many acres do you wish to plant with seed? (each acre takes one bushel)\n");
	return 0;
}
