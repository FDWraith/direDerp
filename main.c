#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

int main(){
  DIR *cur = opendir(".");
  struct dirent *line = readdir(cur);
  do{
    printf("Line:: Name:[%s] Type:[%d]\n",line->d_name, line->d_type);
    line = readdir(cur);
  }while(line != NULL);

  
  
  return 0;
}

int computeDirSize(char * path){
  DIR *cur = opendir(path);
  int sum = 0;
  struct dirent *line = readdir(cur);
  do{
    if( line->d_type == 4){
      char * newPath = (char *)malloc(sizeof(path) + 8)
      sum += computeDirSize()
    }
  }
}

