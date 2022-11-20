/**
 * @brief
 * Usefull constantes
 */
#define POPULATION_MAX 1000
#define TIME_STEP_MAX 10

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

int main(void);