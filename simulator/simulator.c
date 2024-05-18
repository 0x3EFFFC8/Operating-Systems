#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "simulator.h"
#include "memory.h"

//registers
int PC;
int MAR;
int ACC;
char *ICR[5];
char *MDR[5];

//arithmetic logic unit 
int ALU[2] = {INT_MIN, INT_MIN}; 

memory * mem;
Node * node;

char instructions[][9] = { "SET\0", "LDR\0", "ADD\0", "INC\0", "DEC\0", "STR\0", "SHW\0", "PAUSE\0", "END\0"}; 
char *trash[5] = {"0\0","0\0","0\0","0\0","0\0"};

int main(){
  mem = createList();
  for (int i=0; i < INIT_INSTRUCTIONS; i++){
    insertFirst(mem,i,0,INT_MIN,trash);
  }
  readASM();
  freeList(mem);
}

void readASM(){

  FILE *file;
  char line[MAX_LINE_LENGTH];
  char *tokens[5];
  char *token;
  int count = 0;
  int band = 1;
  ACC = INT_MIN;

  file = fopen("program.txt", "r");
  
  PC = INIT_INSTRUCTIONS;
  
  while(fgets(line,MAX_LINE_LENGTH, file) != NULL){

    token = strtok(line," ");
    count = 0;
    while (token != NULL && count < 5) {
        tokens[count++] = strdup(token); 
        token = strtok(NULL, " ");
    }
    insertFirst(mem,PC,1,INT_MIN,tokens);
    PC++;
  }
  
  fclose(file);
  
  PC = INIT_INSTRUCTIONS;
  
  while (band != 0){
    
    MAR = PC;  
    node = findNode(mem,MAR);
    
    for (int i=0; i < 5; i++){
      MDR[i] = node -> inst[i];  
    }
    
    for (int i=0; i < 5; i++){
      ICR[i] = MDR[i];
    }
    PC+=1;
    for (int ins = 0; ins < 9; ins++){
      if (strncmp(ICR[0],instructions[ins],3) == 0){
        ControlUnit(ICR[0],ins,ICR[1],ICR[2],ICR[3],ICR[4],&band);
        break;
      }
    }
  }
}

void ControlUnit(char *insU,int ins0, char *ins1, char *ins2, char *ins3, char *ins4, int *band){
  
  char *endptr;
  switch (ins0) {
    case 0:
            MAR = strtol(ins1, &endptr, 16);
            MDR[0] = ins2;
            node = findNode(mem,MAR);
            node -> data = atoi(MDR[0]);
            break;
    case 1: 
            MAR = strtol(ins1, &endptr, 16);
            node = findNode(mem,MAR);
            sprintf(MDR[0], "%d", node -> data);
            ACC = atoi(MDR[0]);
            break;
    case 2:  
            MAR = strtol(ins1,&endptr,16);
            node = findNode(mem,MAR);
            sprintf(MDR[0], "%d", node -> data);

            if (strncmp(ins2,"NULL",3) == 0) {
              ALU[0] = ACC;
              ALU[1] = atoi(MDR[0]);
            } else {
               ACC = atoi(MDR[0]);
               ALU[0] = ACC;
               MAR = strtol(ins2,&endptr,16);
               node = findNode(mem,MAR);
               sprintf(MDR[0], "%d", node -> data);
               ACC = atoi(MDR[0]);
               ALU[1] = ACC;
            }
            
            ALU[1] += ALU[0];
            ACC = ALU[1];
            
            if (strncmp(ins3,"NULL",3) != 0) {
              MAR = strtol(ins3,&endptr,16);
              sprintf(MDR[0], "%d", ACC);
              node = findNode(mem,MAR);
              node -> data = atoi(MDR[0]);
            } 
            break;
    case 3:
            MAR = strtol(ins1, &endptr, 16);
            node = findNode(mem,MAR);
            sprintf(MDR[0], "%d", node -> data);
            ACC = atoi(MDR[0]);
            ALU[0] = ACC;
            ALU[0]++;
            ACC = ALU[0];
            sprintf(MDR[0], "%d", ACC);
            node = findNode(mem,MAR);
            node -> data = atoi(MDR[0]);
            break;
    case 4:
            MAR = strtol(ins1, &endptr, 16);
            node = findNode(mem,MAR);
            sprintf(MDR[0], "%d", node -> data);
            ACC = atoi(MDR[0]);
            ALU[0] = ACC;
            ALU[0]--;
            ACC = ALU[0];
            sprintf(MDR[0], "%d", ACC);
            node = findNode(mem,MAR);
            node -> data = atoi(MDR[0]);
            break;
    case 5:
            MAR = strtol(ins1, &endptr, 16);
            sprintf(MDR[0], "%d",ACC);
            node = findNode(mem,MAR);
            node -> data = atoi(MDR[0]);
            break;
    case 6: 
            if (strncmp(ins1,"ACC",3) == 0){
              printf("%d\n",ACC);
            } else if (strncmp(ins1,"ICR",3) == 0) {
              printf("%s\n",*ICR);
            } else if (strncmp(ins1,"MAR",3) == 0) {
              printf("%d\n",MAR);
            } else if (strncmp(ins1,"MDR",3) == 0) {
              printf("%s\n",*MDR);
            } else if (strncmp(ins1,"UC",2) == 0) {
              printf("%s\n",insU);
            } else  {
              MAR = strtol(ins1, &endptr, 16);
              node = findNode(mem,MAR);
              sprintf(MDR[0], "%d", ACC);
              printf("%s\n",MDR[0]);
            }
            break;
    case 7:
            printf("PC: %d\n",PC);
            printf("MAR: %d\n",MAR);
            printf("ICR: ");
            for (int i = 0; i < 5; i++) {
              printf("%s ",ICR[i]);
            }
            printf("\nMDR: ");
            for (int i = 0; i < 5; i++) {
              printf("%s ",MDR[i]);
            }
            printf("ACC: %d\n",ACC);
            printf("MEMORY\n");
            Print(mem);
            
            break;
    case 8: 
            *band = 0;
            break;
      
    default: break;
  } 
}
