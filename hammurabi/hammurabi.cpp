#include <stdio.h>
#include "hamcore.h"

int main()
{
	signed short turn;
	struct GAME_STATUS* status = setup_game();

	show_header();
	status->year = turn = 1;

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

		status->year = turn++;
	} 

	show_status(status);
	printf("\nEnd of the game\n\n");
}
