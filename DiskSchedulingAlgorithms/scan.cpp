#include <cstdio>
#include <cstring>
#include <stdlib.h>

int* SCAN(int **req, int head, int n, int* distance, int* pathSize, int dir, int high);
int compareDesc(const void *a, const void *b);
int compareAsc(const void *a, const void *b);
void read(int **req, int *n);

int main(int argc, char *argv[]) {
  int head;
  int tmp;
  int us;
  int dir; 
  int high;
  int* req = NULL;
  int distance = 0;
  int n = 0;
  int pathSize;

  if (argc < 4 ){
    fprintf(stderr, "Use %s -d <num> -high <num> -head <num> -us <num> \n", argv[0]);
  } else {
    for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-d") == 0) {
        dir = atoi(argv[++i]);
      } else if (strcmp(argv[i], "-high") == 0) {
        high = atoi(argv[++i]);
      } else if (strcmp(argv[i], "-head") == 0){
        head = atoi(argv[++i]);
        tmp = head;
      } else if (strcmp(argv[i], "-us") == 0) {
        us = atoi(argv[++i]);
      }
    }

    read(&req,&n); 
    int* path = SCAN(&req,head,n,&distance,&pathSize,dir,high);
    
    printf("Length: %d\n",distance);
    printf("Time: %d\n",us*distance);
    printf("Route: %d ",tmp);
    for(int i=0; i < pathSize; i++)
      printf("%d ",path[i]);
    printf("\n");

    free(req);
    free(path);
  }
  return 0;
}

int* SCAN(int **req, int head, int n, int* distance, int* pathSize, int dir, int high) {
  int* left = NULL;
  int* right = NULL;
  int r = 0;
  int l = 0;
  int res = 0;

  for (int i = n-1; i >= 0; i--){
    if ((*req)[i] < head){
      left = (int *)realloc(left, (l+1) * sizeof(int));
      left[l] = (*req)[i];
      l++;
    }
    else {
      right = (int *)realloc(right, (r+1) * sizeof(int));
      right[r] = (*req)[i];
      r++;
    }
  }

  qsort(left, l, sizeof(int), compareDesc);
  qsort(right, r, sizeof(int), compareAsc);
  
  int* path = (int*)malloc((l + r + 1)* sizeof(int));
 *pathSize = l + r + 1;

  if (dir){
    for(int i = 0; i < l; i++){
      *distance += abs(head-left[i]);
      head = left[i];
      path[i] = head;
    }

    if (head != 0){
      *distance += head;
      path[l] = 0;
      head = 0;
    }else {
      l -=1;
    }

    for(int j = 0; j < r; j++){
      *distance += abs(head-right[j]);
      head = right[j];
      path[l+j+1] = head;
    }
  } else {
    
    for(int j = 0; j < r; j++){
      *distance += abs(head-right[j]);
      head = right[j];
      path[j] = head;
    }
    
    *distance += (high-head);
    head = high;
    path[r] = head;  

    for(int i = 0; i < l; i++){
      *distance += abs(head-left[i]);
      head = left[i];
      path[r+i+1] = head;
    }
    if (head != 0){
      path[r+l+2] = 0;
      *pathSize += 1;
    }
  }
  
  free(left);
  free(right);

  return path;

}

int compareDesc(const void *a, const void *b){
  return (*(int*)b-*(int*)a);
}

int compareAsc(const void *a, const void *b){
  return (*(int*)a - *(int*)b); 
}

void read(int** req, int * n){
  FILE *file;
  char line[10];
  int res; 
  file = fopen("program.txt", "r");
  
  while(fgets(line,10, file) != NULL){
      res = atoi(line);  
      *req = (int *)realloc(*req, (*n + 1) * sizeof(int));
      (*req)[*n] = res;
      (*n)++;     
  }
  fclose(file);  
}

