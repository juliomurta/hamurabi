#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TOTAL_TURNS 10
#define BUSHELS_NEEDED_PER_PERSON 20
#define ACRE_PRICE_MIN 17
#define ACRE_PRICE_MAX 26
#define NEWCOMERS_MIN 0
#define NEWCOMERS_MAX 10
#define BUSHELS_DESTROYED_BY_RATS_MIN 0
#define BUSHELS_DESTROYED_BY_RATS_MAX 450
#define HARVESTED_BY_BUSHEL_MIN 1
#define HARVESTED_BY_BUSHEL_MAX 5
#define INITIAL_POPULATION 95
#define INITIAL_NEWCOMERS 5
#define INITIAL_ACRES 1000

typedef struct GAME_STATUS {
	signed short year;
	signed int starved_people;
	signed int new_comers;
	signed int population;
	signed int total_acres;
	signed int total_bushels;
	signed int harvested_bushels;
	signed int destroyed_bushels;
	signed int acre_price; 
	signed int total_deaths;
	signed int total_newcomers;
} GAME_STATUS;

void show_header(void);
void show_status(GAME_STATUS* status);
void negotiate_acres(GAME_STATUS* status);
void feed_people(GAME_STATUS* status);
void cultivate_acres(GAME_STATUS* status);
void show_bushels(GAME_STATUS* status);
void update_values(GAME_STATUS* status);
void check_plague(GAME_STATUS* status);
int generate_random(int min, int max);
GAME_STATUS* setup_game( );

int main()
{
	show_header();

    signed short turn = 1;

	struct GAME_STATUS* status = setup_game();	
	status->year = turn;

	while (turn <= TOTAL_TURNS)
	{
		status->total_bushels -= status->destroyed_bushels;

		status->population -= status->starved_people;
		status->total_deaths += status->starved_people;

		status->population += status->new_comers; 
		status->total_newcomers += status->new_comers;

		if (status->population <= 0 || status->total_acres <= 0)
		{
			break;
		}

		show_status(status);
		negotiate_acres(status);

		show_bushels(status);
		feed_people(status);

		show_bushels(status);
		cultivate_acres(status);

		update_values(status);
		check_plague(status);

		turn++;
		status->year = turn;
	} 

	show_status(status);
	printf("\nEnd of the game\n\n");
}

GAME_STATUS* setup_game()
{
    GAME_STATUS* status = new GAME_STATUS();
	status->starved_people = 0;
	status->new_comers = INITIAL_NEWCOMERS;
	status->population = INITIAL_POPULATION;
	status->total_acres = INITIAL_ACRES;
	status->harvested_bushels = 3;
	status->destroyed_bushels = 200;
	status->total_bushels = 3000;
	status->acre_price = generate_random(ACRE_PRICE_MIN, ACRE_PRICE_MAX);

	return status;
}

void check_plague(GAME_STATUS* status)
{
	if (10 == generate_random(1, 10))
	{
		printf("\n********************************************************************************\n");
		printf("\n*               A terrible plague killed half of your population!!!            *\n");
		printf("\n********************************************************************************\n");
		int deaths = status->population / 2;
		status->population -= deaths;
		status->total_deaths += deaths;
	}
}

void update_values(GAME_STATUS* status)
{
	status->harvested_bushels = generate_random(HARVESTED_BY_BUSHEL_MIN, HARVESTED_BY_BUSHEL_MAX);
	status->acre_price = generate_random(ACRE_PRICE_MIN, ACRE_PRICE_MAX);
	
	int newcomers = generate_random(NEWCOMERS_MIN, NEWCOMERS_MAX);
	status->new_comers = newcomers;
	status->total_newcomers += newcomers;

	if (5 == generate_random(1, 5))
	{
		status->destroyed_bushels = generate_random(BUSHELS_DESTROYED_BY_RATS_MIN, BUSHELS_DESTROYED_BY_RATS_MAX);
	}
	else
	{
		status->destroyed_bushels = 0;
	}
}

int generate_random(int min, int max)
{
	srand(time(NULL));
	return rand() % ((max + 1) - min) + min;
}

void show_bushels(GAME_STATUS* status)
{
	printf("\nTotal Acres: %d - Total Bushels: %d\n", status->total_acres, status->total_bushels);
}

void show_status(GAME_STATUS* status)
{
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

	if (status->population <= 0)
	{
		printf("\nUnfortunately everyone in your village died.\n");
	}

	if (status->total_acres <= 0)
	{
		printf("\nUnfortunately you dont have acres anymore to cultivate.\n");
	}

	if (status->year > TOTAL_TURNS)
	{
		printf("\nDuring your reign there were a total of %d deaths\n", status->total_deaths);
		printf("\nDuring your reign there were a total of %d new comers\n", status->total_newcomers);

		double popPercent = 100 - (((double) status->population / INITIAL_POPULATION) * 100);
		if (status->population > INITIAL_POPULATION)
		{
			printf("\nYour population increased %.2f %%\n", popPercent);
		}
		else if (status->population < INITIAL_POPULATION)
		{
			printf("\nYour population decreased %.2f %%\n", popPercent);
		}
		else
		{
			printf("\nYour population remained the same\n");
		}

		double acrPercent = ((double) (INITIAL_ACRES - status->total_acres) / INITIAL_ACRES) * 100;
		acrPercent = acrPercent < 0 ? (-1) * acrPercent : acrPercent;
		if (status->total_acres > INITIAL_ACRES)
		{
			printf("\nYour total acres increased %.2f %%\n", acrPercent);
		}
		else if (status->total_acres < INITIAL_ACRES)
		{
			printf("\nYour total acres decreased %.2f %%\n", acrPercent);
		}
		else
		{
			printf("\nYour total acres remained the same\n");
		}
	}
}

void show_header(void)
{

	printf("********************************************************************************\n");
	printf("****                           HAMMURABI THE GAME                            ***\n");
	printf("****                                   by                                    ***\n");
	printf("****                               Julio Murta                               ***\n");
	printf("********************************************************************************\n\n\n");
}

void negotiate_acres(GAME_STATUS* status)
{
	int acres;
	printf("\nHow many acres do you wish to buy or sell? (enter a negative amount to sell bushels)\n");
	scanf_s("%d", &acres);

	if (acres > 0)
	{
		int transaction_value = status->acre_price * acres;
		if (transaction_value > status->total_bushels)
		{
			printf("\nYou dont have enough bushels. Transaction value: %d - Youe bushels: %d\n", transaction_value, status->total_bushels);
		}
		else
		{
			printf("\nTransaction value: %d", transaction_value);
			status->total_acres += acres;
			status->total_bushels -= transaction_value;
		}
	}
	else
	{
		if (acres > status->total_acres)
		{
			printf("\nYou cannot sell more acres than you own. Your acres: %d\n", status->total_acres);
		}
		else
		{
			int transaction_value = status->acre_price * (-1 * acres);
			printf("\nTransaction value: %d", transaction_value);

			status->total_acres += acres;
			status->total_bushels += transaction_value;
		}
	}
}

void feed_people(GAME_STATUS* status)
{
	int bushels_to_feed;
	int valid_input = 0;

	while (!valid_input)
	{
		printf("\nHow many bushels do you wish to feed your people? (each citizen needs %i bushels a year)\n", BUSHELS_NEEDED_PER_PERSON);
		scanf_s("%i", &bushels_to_feed);

		if (bushels_to_feed > status->total_bushels) {
			printf("%i is higher than the total bushels of %i\n", bushels_to_feed, status->total_bushels);
		}
		else
		{
			valid_input = 1;
			status->total_bushels -= bushels_to_feed;
		}
	}

	int bushels_per_person = bushels_to_feed / BUSHELS_NEEDED_PER_PERSON;
	int starved_people = status->population - bushels_per_person;
	status->starved_people = starved_people > 0 ? starved_people : 0;
	status->population -= status->starved_people;
	status->total_deaths += status->starved_people;
}

void cultivate_acres(GAME_STATUS* status)
{
	int acres_to_plant;
	int valid_input = 0;

	while (!valid_input)
	{
		printf("\nHow many acres do you wish to plant with seed? (each acre takes one bushel)\n");
		scanf_s("%i", &acres_to_plant);

		if (acres_to_plant > status->total_acres)
		{
			printf("%i cannot be higher than %i\n", acres_to_plant, status->total_acres);
		} 
		else if (status->population < (acres_to_plant / 10)) {
			printf("The population of %i isnt enough to cultivate %i acres", status->population, acres_to_plant);
		}
		else
		{
			int cultivated_bushels = acres_to_plant * status->harvested_bushels;
			printf("\nCultivated bushels: %d\n", cultivated_bushels);

			status->total_bushels += cultivated_bushels - acres_to_plant;
			valid_input = 1;
		}
	}

}
