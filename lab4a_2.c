/**
 * @file lab4a_2.c
 * @author Antoine Meyer ZZ2(F2) promo 24
 * @brief TP Lab # 4a - A more realistic population growth
 * @version 0.1
 * @date 2022-11-15
 * @copyright Copyright (c) 2022
 *
 * How to compile :
 * > gcc -c [file_name].c
 * > gcc *.o -o [compile_file_name] -lm
 * > ./[compile_file_name]
 */

#include <stdio.h>
#include <math.h>
#include "lab4a_2.h"
#include "mt19937ar.h"

/**
 * @brief Local usefull variables
 */
int time_step;
int rabbit_ids;

Rabbit_t little_male[POPULATION_MAX];
Rabbit_t little_female[POPULATION_MAX];
Rabbit_t adult_male[POPULATION_MAX];
Rabbit_t adult_female[POPULATION_MAX];

int little_male_size;
int little_female_size;
int adult_male_size;
int adult_female_size;

/**
 * @brief Create a rabbit object
 *
 * @param age
 * @param be_adult
 * @return Rabbit_t
 */
Rabbit_t create_rabbit(int age, int be_adult)
{
    rabbit_ids++;

    Rabbit_t res;
    res.id = rabbit_ids;
    res.age = age;
    res.be_adult = be_adult;
    return res;
}

/**
 * @brief Init. usefull variables
 */
void init_program()
{
    time_step = 0;
    rabbit_ids = 0;

    /**
     * @brief
     * Init. array of rabbits
     */
    little_male_size = 0;
    little_female_size = 0;
    adult_male_size = 5;
    adult_female_size = 3;

    /*little_male[0] = create_rabbit(0, 0, 0);
    little_male[1] = create_rabbit(0, 0, 0);

    little_female[0] = create_rabbit(5, 0, 0);
    little_female[1] = create_rabbit(7, 0, 0);*/

    adult_male[0] = create_rabbit(9, 1);
    adult_male[1] = create_rabbit(10, 1);
    adult_male[2] = create_rabbit(11, 1);
    adult_male[3] = create_rabbit(12, 1);
    adult_male[4] = create_rabbit(13, 1);

    adult_female[0] = create_rabbit(5, 1);
    adult_female[1] = create_rabbit(6, 1);
    adult_female[2] = create_rabbit(8, 1);
}

/**
 * @brief
 *
 * @param rabbit
 */
void display_rabbit(Rabbit_t rabbit)
{
    printf("n°%d_%d", rabbit.id, rabbit.age);
}

/**
 * @brief
 *
 * @param array
 * @param array_size
 */
void display_array_rabbit(Rabbit_t array[], int array_size)
{
    printf("[");
    for (int i = 0; i < array_size - 1; i++)
    {
        display_rabbit(array[i]);
        printf(", ");
    }
    if (array_size != 0)
    {
        display_rabbit(array[array_size - 1]);
    }
    printf("]\n");
}

/**
 * @brief Little rabbit become adult rabbit
 */
void little_growing()
{
    /* Little male rabbit become adult male rabbit */
    while (little_male_size > 0 && adult_male_size < POPULATION_MAX)
    {
        little_male[little_male_size - 1].be_adult = 1;
        adult_male[adult_male_size] = little_male[little_male_size - 1];
        adult_male_size++;
        little_male_size--;
    }
    // s'il reste des bebes lapins on les tue ! :/
    little_male_size = 0;

    /* Little female rabbit become adult female rabbit */
    while (little_female_size > 0 && adult_female_size < POPULATION_MAX)
    {
        little_female[little_female_size - 1].be_adult = 1;
        adult_female[adult_female_size] = little_female[little_female_size - 1];
        adult_female_size++;
        little_female_size--;
    }
    // s'il reste des bebes lapins on les tue ! :/
    little_female_size = 0;
}

/**
 * @brief Adult getting older
 */
void adult_aging()
{
    /* Adult male getting older */
    for (int i = 0; i < adult_male_size; i++)
    {
        adult_male[i].age++;
    }

    /* Adult female getting older */
    for (int i = 0; i < adult_female_size; i++)
    {
        adult_female[i].age++;
    }
}

/**
 * @brief
 *
 * @return int
 */
int number_of_couples()
{
    int couple_number = adult_female_size;
    if (adult_male_size < couple_number)
    {
        couple_number = adult_male_size;
    }
    return couple_number;
}

/**
 * @brief n°litter :
 * 0(5%), 3(10%), 4(10%), 5(20%), 6(20%), 7(20%), 8(10%) and 9(5%)
 *
 * @return int
 */
int number_of_litters()
{
    int response = 0;
    double random = genrand_real2();
    if (random < 0.05)
    {
        response = 0;
    }
    else if (random < 0.15)
    {
        response = 3;
    }
    else if (random < 0.25)
    {
        response = 4;
    }
    else if (random < 0.45)
    {
        response = 5;
    }
    else if (random < 0.65)
    {
        response = 6;
    }
    else if (random < 0.85)
    {
        response = 7;
    }
    else if (random < 0.95)
    {
        response = 8;
    }
    else
    {
        response = 9;
    }
    return response;
}

/**
 * @brief
 *
 */
void adult_reproducing()
{
    int couple_number = number_of_couples();
    couple_number = 20;
    // pour chaque couple
    for (int i = 0; i < couple_number; i++)
    {
        // hasard le nombre de portée (entre 5 et 9 là)
        int litter_number = number_of_litters();
        printf("nombre de portées : %d\n", litter_number);
        // pour chaque portee
        for (int j = 0; j < litter_number; j++)
        {
            
        }
        // hasard le nombre de petit (entre 3 et 6 là)
        // pour chaque petit
        // hasard le sexe (50/50)
        // ajout a la liste des petits
    }
}

/**
 * @brief Main function who use code and display TP's result
 *
 * @return int
 */
int main(void)
{

    /**
     * @brief Init. MT generator
     */
    int i;
    unsigned long init[4] = {0x123, 0x234, 0x345, 0x456}, length = 4;
    init_by_array(init, length);

    /**
     * @brief Init. program
     */
    init_program();

    /**
     * @brief Loop throught years
     */
    for (int i = 0; i < TIME_STEP_MAX; i++)
    {
        printf("Year n°%d\n", time_step);
        printf("n°X_[age]\n");

        printf("Array of little male :\n");
        display_array_rabbit(little_male, little_male_size);
        printf("Array of little female :\n");
        display_array_rabbit(little_female, little_female_size);
        printf("Array of adult male :\n");
        display_array_rabbit(adult_male, adult_male_size);
        printf("Array of adult female :\n");
        display_array_rabbit(adult_female, adult_female_size);

        //// TOUTE LANNEE
        // ADULT REPRODUSING AND CREATE LITTLE RABBITS !!
        adult_reproducing();

        //// EN FIN DANNEE
        // LITTLE RABBITS BECOME ADULT
        little_growing();

        // ADULT GET OLDER
        adult_aging();

        // ADULT RABBITS MAY DIED
        // on parcours les adultes et on les tue

        // ..AND AGAIN
        time_step++;
        printf("\n=================================\n");
    }

    /*
     * 2) More realistic population growth where you
     * will have to make your own modeling choices and
     * use the simulated distributions of lab #2 (different
     * random variates). Use the C language (compare with
     * an object-oriented language if you can and have time).
     */

    /*x_rand = genrand_real2();
    printf("xrand: %10.8f\n", x_rand);

    printf("time_step: %d\n", time_step);*/

    return 0;
}
