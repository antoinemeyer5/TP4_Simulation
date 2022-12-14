#ifndef MT19937AR_H_ /* Include guard */
#define MT19937AR_H_

void init_genrand(unsigned long);

void init_by_array(unsigned long [], int);

unsigned long genrand_int32(void);

long genrand_int31(void);

double genrand_real1(void);

double genrand_real2(void);

double genrand_real3(void);

double genrand_res53(void);

#endif // MT19937AR_H_