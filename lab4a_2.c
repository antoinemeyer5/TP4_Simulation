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
    little_male_size = 1;
    little_female_size = 1;
    adult_male_size = 1;
    adult_female_size = 1;

    little_male[0] = create_rabbit(0, 0);
    //little_male[1] = create_rabbit(0, 0, 0);

    little_female[0] = create_rabbit(0, 0);
    //little_female[1] = create_rabbit(0, 0);
    //little_female[1] = create_rabbit(7, 0, 0);

    adult_male[0] = create_rabbit(2, 1);

    adult_female[0] = create_rabbit(2, 1);
    //adult_female[1] = create_rabbit(2, 1);
    //adult_female[2] = create_rabbit(2, 1);
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
 * @brief
 *
 */
void display_infos(FILE *fp)
{
    /*printf("Number little male: %d\n", little_male_size);
    printf("Number little female: %d\n", little_female_size);
    printf("Number adult male: %d\n", adult_male_size);
    printf("Number adult female: %d\n", adult_female_size);*/

    fprintf(fp, "%d", little_male_size);
    fputc('\t', fp);
    fprintf(fp, "%d", little_female_size);
    fputc('\t', fp);
    fprintf(fp, "%d", adult_male_size);
    fputc('\t', fp);
    fprintf(fp, "%d", adult_female_size);
    fputc('\t', fp);
    fputc('\n', fp);
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
 * @return int
 */
int number_of_new_little()
{
    int response = 3;
    double random = genrand_real2();
    if (random < 0.25)
    {
        response = 3;
    }
    else if (random < 0.50)
    {
        response = 4;
    }
    else if (random < 0.75)
    {
        response = 5;
    }
    else
    {
        response = 6;
    }
    return response;
}

/**
 * @brief
 *
 * @return int
 */
int new_little_sex()
{
    int response = 0;
    double random = genrand_real2();
    if (random >= 0.50)
    {
        response = 1;
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
    int litter_number = 0;
    int total_new_little = 0;

    /* For each couple */
    for (int i = 0; i < couple_number; i++)
    {
        litter_number = number_of_litters();
        /* For each litter */
        for (int j = 0; j < litter_number; j++)
        {
            total_new_little = total_new_little + number_of_new_little();
        }
    }
    /* While each new rabbits */
    int new_one = 0;
    while (new_one < total_new_little)
    {
        /* New female */
        if (new_little_sex() == 0)
        {
            if (little_female_size < POPULATION_MAX)
            {
                little_female[little_female_size] = create_rabbit(0, 0);
                little_female_size++;
            }
        }
        else
        {
            if (little_male_size < POPULATION_MAX)
            {
                little_male[little_male_size] = create_rabbit(0, 0);
                little_male_size++;
            }
        }
        new_one++;
    }
}

/**
 * @brief
 *
 * @return int
 */
int little_death()
{
    int response = 1;
    double random = genrand_real2();
    if (random < 0.65)
    {
        response = 0;
    }
    return response;
}

/**
 * @brief
 *
 * @return int
 */
int adult_death(Rabbit_t rabbit)
{
    int response = 1;
    double random = genrand_real2();
    double survival_rate = 0.40;
    if (rabbit.age >= 10)
    {
        survival_rate = survival_rate + 0.10 * (rabbit.age - 10);
    }
    if (random < survival_rate)
    {
        response = 0;
    }
    if (rabbit.age >= 15)
    {
        response = 0;
        printf("\n### death of an old venerable rabbit ###\n");
    }
    return response;
}

/**
 * @brief
 *
 */
void little_and_adult_killing()
{
    // on parcours les jeunes et les adultes et on les tue
    // jeune males
    for (int i = 0; i < little_male_size; i++)
    {
        if (little_death() == 0)
        {
            little_male_size--;
        }
    }

    // jeunes femelles
    for (int i = 0; i < little_female_size; i++)
    {
        if (little_death() == 0)
        {
            little_female_size--;
        }
    }

    // vieux males
    for (int i = 0; i < adult_male_size; i++)
    {
        if (adult_death(adult_male[i]) == 0)
        {
            adult_male_size--;
        }
    }

    // vieilles femelles
    for (int i = 0; i < adult_female_size; i++)
    {
        if (adult_death(adult_female[i]) == 0)
        {
            adult_female_size--;
        }
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

    char *filename = "DATA_DEV.txt";

    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening the file %s", filename);
        return -1;
    }

    fprintf(fp, "%d\t", little_male_size);
    fprintf(fp, "%d\t", little_female_size);
    fprintf(fp, "%d\t", adult_male_size);
    fprintf(fp, "%d\n", adult_female_size);

    fprintf(fp, "%d\n", POPULATION_MAX);
    fprintf(fp, "%d\n", TIME_STEP_MAX);

    /**
     * @brief Loop throught years
     */
    for (int i = 0; i < TIME_STEP_MAX; i++)
    {
        printf("Year n°%d\n", time_step);
        fprintf(fp, "%d", time_step);
        fputc('\n', fp);

        printf("=> Before reproducing <=\n");
        display_infos(fp);

        //// TOUTE LANNEE
        // ADULT REPRODUSING AND CREATE LITTLE RABBITS !!
        adult_reproducing();

        printf("=> After reproducing <=\n");
        display_infos(fp);

        //// EN FIN DANNEE
        // ADULT RABBITS MAY DIED
        little_and_adult_killing();

        printf("=> After death(ing) <=\n");
        display_infos(fp);

        // OLDING
        little_growing(); // LITTLE RABBITS BECOME ADULT
        adult_aging();    // ADULT GET OLDER

        printf("=> After growing and aging <=\n");
        display_infos(fp);

        // ..AND AGAIN
        time_step++;
        printf("=================================\n");
    }

    fclose(fp);

    return 0;
}
