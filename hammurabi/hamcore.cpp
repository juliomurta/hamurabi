#include <stdio.h>
#include "hamcore.h"
#include "hamutils.h"
#include <stdlib.h>
#include <string.h>

GAME_STATUS* setup_new_game(void)
{
	GAME_STATUS* status = new GAME_STATUS();
	status->starved_people = 0;
	status->new_comers = INITIAL_NEWCOMERS;
	status->population = INITIAL_POPULATION;
	status->total_acres = INITIAL_ACRES;
	status->harvested_bushels = 3;
	status->destroyed_bushels = 200;
	status->total_bushels = 3000;
	status->year = 1;
	status->acre_price = generate_random(ACRE_PRICE_MIN, ACRE_PRICE_MAX);

	return status;
}

void show_header(void)
{

	printf("********************************************************************************\n");
	printf("****                           HAMMURABI THE GAME                            ***\n");
	printf("****                                   by                                    ***\n");
	printf("****                               Julio Murta                               ***\n");
	printf("********************************************************************************\n\n\n");
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
		printf("\nUnfortunately you dont have enough acres to cultivate.\n");
	}

	if (status->year > TOTAL_TURNS)
	{
		printf("\nDuring your reign there were a total of %d deaths\n", status->total_deaths);
		printf("\nDuring your reign there were a total of %d new comers\n", status->total_newcomers);

		double popPercent = 100 - (((double)status->population / INITIAL_POPULATION) * 100);
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

		double acrPercent = ((double)(INITIAL_ACRES - status->total_acres) / INITIAL_ACRES) * 100;
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

void show_bushels(GAME_STATUS* status)
{
	printf("\nTotal Acres: %d - Total Bushels: %d\n", status->total_acres, status->total_bushels);
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

void negotiate_acres(GAME_STATUS* status)
{
	int acres, valid_input = 0;
	printf("\nHow many acres do you wish to buy or sell? (enter a negative amount to sell bushels)\n");
	while (!valid_input)
	{
		valid_input = scanf_s("%d", &acres);
		if (!valid_input)
		{
			printf("\nPlease type a valid number\n");
			fflush(stdin);			
		}
	}	

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

int save_progress(GAME_STATUS* status) 
{
	FILE* file = NULL;
	errno_t err = 0;

	if (status == NULL || (err = fopen_s(&file, "gamedata.dat", "wb")) != 0)
	{
		printf("\nThere were an error while saving the game status.\n");
		return 0;
	}

	char acre_price[5], 
		 destroyed_bushels[5], 
		 harvested_bushels[5], 
		 new_comers[5], 
		 population[5], 
		 starved_people[5], 
		 total_acres[5], 
		 total_bushels[5], 
		 total_deaths[5], 
		 total_newcomers[5], 
		 year[5];

	_itoa_s(status->acre_price, acre_price, 10);
	_itoa_s(status->destroyed_bushels, destroyed_bushels, 10);
	_itoa_s(status->harvested_bushels, harvested_bushels, 10);
	_itoa_s(status->new_comers, new_comers, 10);
	_itoa_s(status->population, population, 10);
	_itoa_s(status->starved_people, starved_people, 10);
	_itoa_s(status->total_acres, total_acres, 10);
	_itoa_s(status->total_bushels, total_bushels, 10);
	_itoa_s(status->total_deaths, total_deaths, 10);
	_itoa_s(status->total_newcomers, total_newcomers, 10);
	_itoa_s(status->year, year, 10);

	char game_status_binary[500] = "ACRE_PRICE=";
	strcat_s(game_status_binary, sizeof(game_status_binary), acre_price);
	strcat_s(game_status_binary, sizeof(game_status_binary), ";DBUSHELS=");
	strcat_s(game_status_binary, sizeof(game_status_binary), destroyed_bushels);
	strcat_s(game_status_binary, sizeof(game_status_binary), ";HBUSHELS=");
	strcat_s(game_status_binary, sizeof(game_status_binary), harvested_bushels);
	strcat_s(game_status_binary, sizeof(game_status_binary), ";NEWCMS=");
	strcat_s(game_status_binary, sizeof(game_status_binary), new_comers);
	strcat_s(game_status_binary, sizeof(game_status_binary), ";POP=");
	strcat_s(game_status_binary, sizeof(game_status_binary), population);
	strcat_s(game_status_binary, sizeof(game_status_binary), ";STVPPL=");
	strcat_s(game_status_binary, sizeof(game_status_binary), starved_people);
	strcat_s(game_status_binary, sizeof(game_status_binary), ";TACRE=");
	strcat_s(game_status_binary, sizeof(game_status_binary), total_acres);
	strcat_s(game_status_binary, sizeof(game_status_binary), ";TBUSHELS=");
	strcat_s(game_status_binary, sizeof(game_status_binary), total_bushels);
	strcat_s(game_status_binary, sizeof(game_status_binary), ";TDEATHS=");
	strcat_s(game_status_binary, sizeof(game_status_binary), total_deaths);
	strcat_s(game_status_binary, sizeof(game_status_binary), ";TNEWCMRS=");
	strcat_s(game_status_binary, sizeof(game_status_binary), total_newcomers);
	strcat_s(game_status_binary, sizeof(game_status_binary), ";YEAR=");
	strcat_s(game_status_binary, sizeof(game_status_binary), year);

	if (fwrite(game_status_binary, 1, 500, file) != 500) 
	{
		printf("\nThere were an error while saving the game status.");
		return 0;
	}

	fclose(file);
	return 1;
}

GAME_STATUS* load_progress(void)
{
	FILE* file = NULL;
	GAME_STATUS* status = setup_new_game();
	errno_t err = fopen_s(&file, "gamedata.dat", "rb");

	if (file == NULL && err != 0)
	{
		printf("\nThere were an error while loading the game status.");
		exit(1);
	}

	char game_status_binary[500];
	if (fread(game_status_binary, 500, 1, file) != 0)
	{
		char *prop_next, *val_next;
		const char *prop_delim = ";", *val_delim = "=";
		char *prop_token = strtok_s(game_status_binary, prop_delim, &prop_next);

		while (prop_token)
		{
			char* val_token = strtok_s(prop_token, val_delim, &val_next);	
			while (val_token)
			{				
				if (strcmp(val_token, "ACRE_PRICE")) {
					val_token = strtok_s(NULL, val_delim, &val_next);
					status->acre_price = atoi(val_token);
					continue;
				}
				else if (strcmp(val_token, "DBUSHELS")) {
					val_token = strtok_s(NULL, val_delim, &val_next);
					status->destroyed_bushels = atoi(val_token);
					continue;
				}
				else if (strcmp(val_token, "HBUSHELS")) {
					val_token = strtok_s(NULL, val_delim, &val_next);
					status->harvested_bushels = atoi(val_token);
					continue;
				}
				else if (strcmp(val_token, "NEWCMS")) {
					val_token = strtok_s(NULL, val_delim, &val_next);
					status->new_comers = atoi(val_token);
					continue;
				}
				else if (strcmp(val_token, "POP")) {
					val_token = strtok_s(NULL, val_delim, &val_next);
					status->population = atoi(val_token);
					continue;
				}
				else if (strcmp(val_token, "STVPPL")) {
					val_token = strtok_s(NULL, val_delim, &val_next);
					status->starved_people = atoi(val_token);
					continue;
				}
				else if (strcmp(val_token, "TACRE")) {
					val_token = strtok_s(NULL, val_delim, &val_next);
					status->total_acres = atoi(val_token);
					continue;
				}
				else if (strcmp(val_token, "TBUSHELS")) {
					val_token = strtok_s(NULL, val_delim, &val_next);
					status->total_bushels = atoi(val_token);
					continue;
				}
				else if (strcmp(val_token, "TDEATHS")) {
					val_token = strtok_s(NULL, val_delim, &val_next);
					status->total_deaths = atoi(val_token);
					continue;
				}
				else if (strcmp(val_token, "TNEWCMRS")) {
					val_token = strtok_s(NULL, val_delim, &val_next);
					status->total_newcomers = atoi(val_token);
					continue;
				}
				else if (strcmp(val_token, "YEAR")) {
					val_token = strtok_s(NULL, val_delim, &val_next);
					status->year = atoi(val_token);
					continue;
				}
			}

			prop_token = strtok_s(NULL, prop_delim, &prop_next);
		}


		show_status(status);
		exit(1);
	}

	return NULL;
}