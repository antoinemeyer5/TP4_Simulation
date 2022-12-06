/*
 * Antoine MEYER, ZZ2(F2) class 24
 * TP Lab # 4a - A more realistic population growth
 * Code created on November 7, 2022 in Aubière
 */

#include <stdio.h>

/*
 * How to compile :
 * > gcc -c [file_name].c
 * > gcc *.o -o [compile_file_name] -lm
 * > ./[compile_file_name]
 */

/*
 * Role of the function:
 * Calculate the values of a Fibonacci sequence
 *
 * Role of the input parameters:
 * nb_month, number of steps in the Fibonacci sequence
 *
 * Expected result:
 * Value in the Fibonacci sequence
 */
long leonardoPizzaModel(int nb_month)
{
    long nb_young_couple = 1; /* kittens */
    long nb_adult_couple = 0;
    long nb_couple = nb_young_couple + nb_adult_couple;
    int time_step = 1; /* nb_month */

    for (time_step; time_step < nb_month; time_step++)
    {
        nb_young_couple = nb_adult_couple;
        nb_adult_couple = nb_couple;
        nb_couple = nb_young_couple + nb_adult_couple;
    }

    return nb_couple;
}

/*
 * Function role:
 * Main function that uses the rest of the code to
 * present the results of TP Lab # 4a - A more
 * realistic population growth.
 *
 * Role of input parameters: None
 *
 * Expected outcome: None
 */
int main()
{
    /* 
     * 1) Life Science model – the origins: a fast
     * simulation of a rabbit population growth.
     */
    for (int i = 1; i <= 5; i++)
    {
        printf("Month n°%d: %ld couple of rabbits\n", i, leonardoPizzaModel(i));
    }
    for (int i = 1; i <= 5; i++)
    {
        printf("Year n°%d: %ld couple of rabbits\n", i, leonardoPizzaModel(i*12));
    }

    return 0;
}
