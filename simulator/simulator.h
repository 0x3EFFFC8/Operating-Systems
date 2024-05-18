#ifndef SIMULATOR_H
#define SIMULATOR_H

#define MAX_LINE_LENGTH 100 
#define INIT_INSTRUCTIONS 4400

void readASM();
void ControlUnit(char *insU,int ins0, char *ins1, char *ins2, char *ins3, char *ins4, int *band);

#endif
