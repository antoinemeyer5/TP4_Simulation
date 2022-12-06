/**
 * @brief
 * Usefull constantes
 */
#define POPULATION_MAX 10000000 // 10 millions
#define TIME_STEP_MAX 30
#define NUMBER_EXPERIENCE 35

typedef struct Rabbit {
    int id;
    int be_adult;       // bool 1:adult 0:young 
    int age;
} Rabbit_t;

Rabbit_t create_rabbit(int, int);

void init_program();

void display_rabbit(Rabbit_t);

void display_array_rabbit(Rabbit_t[], int);

void display_infos(FILE *);

void little_growing();

void adult_aging();

int number_of_couples();

int number_of_litters();

int number_of_new_little();

int new_little_sex();

void adult_reproducing();

int little_death();

int adult_death(Rabbit_t);

void little_and_adult_killing();

void diseases_killing();

void predators_killing();

int main(void);