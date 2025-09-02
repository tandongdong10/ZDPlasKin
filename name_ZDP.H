
#ifndef NAME_ZDP
#define NAME_ZDP

#ifdef __cplusplus
extern "C"{
#endif

extern void zdpsolver_init_(int *nBolsigReactions, int* nBolsigSpecies, char speciesName[][8], char reactionName[][20], double parameters[]);
extern void zdpsolver_(double parameters[], double Arate[]);
//extern type* func2_(type VAR1, type VAR2); //function

#ifdef __cplusplus
}
#endif

#endif
