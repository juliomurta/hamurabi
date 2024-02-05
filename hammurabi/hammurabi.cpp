#include <stdio.h>
#include "hamcore.h"
#include <stdlib.h>

void execute_game(GAME_STATUS* status);
GAME_STATUS* initial_options(void);

int main()
{	
	show_header();
	GAME_STATUS* status = initial_options();
	execute_game(status);
}

GAME_STATUS* initial_options(void)
{
	printf("\n1 - New Game");
	printf("\n2 - Continue");

	int option, valid_input = 0;
	while (!valid_input)
	{
		printf("\n>>> ");
		valid_input = scanf_s("%d", &option);
		if (!valid_input || (valid_input = (option == 1 || option == 2)))
		{
			printf("\nPlease type a valid number\n");
		}

		fflush(stdin);
	}

	GAME_STATUS* status = NULL;
	switch (option)
	{
		case 1:
			status = setup_new_game();
			break;
		case 2:
			status = load_progress();
			break;
	}

	return status;
}

void execute_game(GAME_STATUS* status)
{
	signed short turn = status->year;

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

		if (turn > status->year)
		{
			char save;
			int valid_input = 0;

			printf("\nDo you wish to save your game progress? [y/n]");
			fseek(stdin, 0, SEEK_END);

			while (!valid_input)
			{
				printf("\n>>> ");
				valid_input = scanf_s("%c", &save, 1);

				if (!valid_input || (valid_input = (save == 'y' || save == 'Y' || save == 'n' || save == 'N')))
				{
					printf("\nPlease type a valid option\n");
				}

				fseek(stdin, 0, SEEK_END);
			}

			if (save == 'y' || save == 'Y')
			{
				if (save_progress(status))
				{
					printf("\nProgress saved successfuly!!!\n");
				}

				exit(1);
			}
		}

		show_status(status);
		negotiate_acres(status);

		show_bushels(status);
		feed_people(status);

		show_bushels(status);
		cultivate_acres(status);

		update_values(status);
		check_plague(status);

		status->year = turn++;
	}

	show_status(status);
	printf("\nEnd of the game\n\n");
}
