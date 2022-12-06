/**
 * @file lab4a_2.c
 * @author Antoine Meyer ZZ2(F2) class 24
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
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "lab4a_2.h"
#include "mt19937ar.h"

/**
 * @brief Local usefull variables
 */
int time_step;
int rabbit_ids;

static Rabbit_t little_male[POPULATION_MAX];
static Rabbit_t little_female[POPULATION_MAX];
static Rabbit_t adult_male[POPULATION_MAX];
static Rabbit_t adult_female[POPULATION_MAX];

long little_male_size;
long little_female_size;
long adult_male_size;
long adult_female_size;

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
    adult_male_size = 1;
    adult_female_size = 1;

    adult_male[0] = create_rabbit(2, 1);
    adult_female[0] = create_rabbit(2, 1);
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
    fprintf(fp, "%ld", little_male_size);
    fputc('\t', fp);
    fprintf(fp, "%ld", little_female_size);
    fputc('\t', fp);
    fprintf(fp, "%ld", adult_male_size);
    fputc('\t', fp);
    fprintf(fp, "%ld", adult_female_size);
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
    /* if there are still baby rabbits we kill them! :/ */
    little_male_size = 0;

    /* Little female rabbit become adult female rabbit */
    while (little_female_size > 0 && adult_female_size < POPULATION_MAX)
    {
        little_female[little_female_size - 1].be_adult = 1;
        adult_female[adult_female_size] = little_female[little_female_size - 1];
        adult_female_size++;
        little_female_size--;
    }
    /* if there are still baby rabbits we kill them! :/ */
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
        // printf("\n### death of an old venerable rabbit ###\n");
    }
    return response;
}

/**
 * @brief
 *
 */
void little_and_adult_killing()
{
    /* browser youngs and adults and remove them... */ 
    /* young males */
    for (int i = 0; i < little_male_size; i++)
    {
        if (little_death() == 0)
        {
            little_male_size--;
        }
    }

    /* young females */
    for (int i = 0; i < little_female_size; i++)
    {
        if (little_death() == 0)
        {
            little_female_size--;
        }
    }

    /* old males */
    for (int i = 0; i < adult_male_size; i++)
    {
        if (adult_death(adult_male[i]) == 0)
        {
            adult_male_size--;
        }
    }

    /* old females */
    for (int i = 0; i < adult_female_size; i++)
    {
        if (adult_death(adult_female[i]) == 0)
        {
            adult_female_size--;
        }
    }
}

/**
 * @brief if big population than killing half due to disease
 */
void diseases_killing()
{
    // RABBIT - COVID
    // little male
    if (little_male_size > 0.50 * POPULATION_MAX)
    {
        little_male_size = little_male_size / 2;
    }
    // little female
    if (little_female_size > 0.50 * POPULATION_MAX)
    {
        little_female_size = (int)(little_female_size / 1.8);
    }
    // adult male
    if (adult_male_size > 0.50 * POPULATION_MAX)
    {
        adult_male_size = adult_male_size / 2;
    }
    // adult female
    if (adult_female_size > 0.50 * POPULATION_MAX)
    {
        adult_female_size = (int)(adult_female_size / 1.8);
    }
}

/**
 * @brief eat 45% of young rabbits & 35% of adult rabbits
 */
void predators_killing()
{
    // little male
    little_male_size = little_male_size * 0.45;

    // little female
    little_female_size = little_female_size * 0.45;

    // adult male
    adult_male_size = adult_male_size * 0.35;

    // adult female
    adult_female_size = adult_female_size * 0.35;
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

    char *files[40];
    files[0] = "DATA/DATA_01.txt"; files[1] = "DATA/DATA_02.txt"; files[2] = "DATA/DATA_03.txt"; files[3] = "DATA/DATA_04.txt";
    files[4] = "DATA/DATA_05.txt"; files[5] = "DATA/DATA_06.txt"; files[6] = "DATA/DATA_07.txt"; files[7] = "DATA/DATA_08.txt";
    files[8] = "DATA/DATA_09.txt"; files[9] = "DATA/DATA_10.txt"; files[10] = "DATA/DATA_11.txt"; files[11] = "DATA/DATA_12.txt";
    files[12] = "DATA/DATA_13.txt"; files[13] = "DATA/DATA_14.txt"; files[14] = "DATA/DATA_15.txt"; files[15] = "DATA/DATA_16.txt";
    files[16] = "DATA/DATA_17.txt"; files[17] = "DATA/DATA_18.txt"; files[18] = "DATA/DATA_19.txt"; files[19] = "DATA/DATA_20.txt";
    files[20] = "DATA/DATA_21.txt"; files[21] = "DATA/DATA_22.txt"; files[22] = "DATA/DATA_23.txt"; files[23] = "DATA/DATA_24.txt";
    files[24] = "DATA/DATA_25.txt"; files[25] = "DATA/DATA_26.txt"; files[26] = "DATA/DATA_27.txt"; files[27] = "DATA/DATA_28.txt";
    files[28] = "DATA/DATA_29.txt"; files[29] = "DATA/DATA_30.txt"; files[30] = "DATA/DATA_31.txt"; files[31] = "DATA/DATA_32.txt";
    files[32] = "DATA/DATA_33.txt"; files[33] = "DATA/DATA_34.txt"; files[34] = "DATA/DATA_35.txt"; files[35] = "DATA/DATA_36.txt";

    char *filename;

    for (int i = 0; i < NUMBER_EXPERIENCE; i++)
    {
        init_program();
        filename = files[i];

        FILE *fp = fopen(filename, "w");
        if (fp == NULL)
        {
            printf("Error opening the file %s", filename);
            return -1;
        }

        fprintf(fp, "disease ACTIVE\n");
        fprintf(fp, "predator ACTIVE\n");

        fprintf(fp, "%ld\t", little_male_size);
        fprintf(fp, "%ld\t", little_female_size);
        fprintf(fp, "%ld\t", adult_male_size);
        fprintf(fp, "%ld\n", adult_female_size);

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

            //printf("=> Before reproducing <=\n");
            display_infos(fp);

            //// TOUTE LANNEE
            // ADULT REPRODUSING AND CREATE LITTLE RABBITS !!
            adult_reproducing();
            //printf("=> After reproducing <=\n");
            display_infos(fp);

            //// EN FIN DANNEE
            // ADULT RABBITS MAY DIED
            little_and_adult_killing();
            //printf("=> After death(ing) <=\n");
            display_infos(fp);

            // DISEASES
            diseases_killing();
            //printf("=> After diseases(ing) <=\n");
            display_infos(fp);

            // PREDATORS
            predators_killing();
            //printf("=> After preadot(ing) <=\n");
            display_infos(fp);

            // OLDING
            little_growing(); // LITTLE RABBITS BECOME ADULT
            adult_aging();    // ADULT GET OLDER
            //printf("=> After growing and aging <=\n");
            //display_infos(fp);

            // ..AND AGAIN
            time_step++;
            //printf("=================================\n");
        }

        fclose(fp);
    }

    return 0;
}