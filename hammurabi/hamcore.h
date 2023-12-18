
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
void show_bushels(GAME_STATUS* status);
void negotiate_acres(GAME_STATUS* status);
void feed_people(GAME_STATUS* status);
void cultivate_acres(GAME_STATUS* status);
void update_values(GAME_STATUS* status);
void check_plague(GAME_STATUS* status);
GAME_STATUS* setup_game(void);