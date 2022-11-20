/*
 * Antoine MEYER, ZZ2(F2) promo 24
 * TP Lab # 4a - A more realistic population growth
 * Code créé le 7 novembre 2022 à Aubière
 */

#include <stdio.h>
// #include <math.h>
// #include "mt19937ar.h"

/*
 * How to compile :
 * > gcc -c [file_name].c
 * > gcc *.o -o [compile_file_name] -lm
 * > ./[compile_file_name]
 */

/*
 * Rôle de la fonction :
 * Calculer les valeurs d'une suite de Fibonacci
 *
 * Rôle des paramètres d'entrées :
 * nb_month, nombre de pas dans la suite de Fibonacci
 *
 * Résultat attendu :
 * Valeur dans la suite de Fibonacci
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
 * Rôle de la fonction :
 * Fonction principale qui utilise le reste du code pour
 * présenter les résultats du TP Lab # 4a - A more
 * realistic population growth.
 *
 * Rôle des paramètres d'entrée : Aucun
 *
 * Résultat attendu : Aucun
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
