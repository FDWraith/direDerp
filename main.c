#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int computeDirSize(char * path);
void printOutDir(char * path);

int main(){
  DIR *cur = opendir(".");
  struct dirent *line = readdir(cur);
  do{
    //printf("Line:: Name:[%s] Type:[%d]\n",line->d_name, line->d_type);
    line = readdir(cur);
  }while(line != NULL);
  closedir(cur);

  printf("Printing out Directory Statistics\n");
  //char * p = ".";
  printf("Total Directory Size: %d Bytes\n", computeDirSize("."));
  printOutDir(".");
  return 0;
}

int computeDirSize(char * path){
  //printf("Function Accessed\n");
  DIR *cur = opendir(path);
  //printf("OpenDir successful\n");
  int sum = 0;
  struct dirent *line = readdir(cur);
  ///printf("reading successful\n");
  do{
    //printf("File Being Accessed:[%s]\n",line->d_name);
    if( line->d_type == 4){
      if( strcmp(line->d_name, ".") != 0 && strcmp(line->d_name, "..") != 0 ){
        char newPath[256];
        strcpy(newPath, path);
        strcat(newPath,"/");
        strcat(newPath,line->d_name);
        //printf("NewPath:%s\n",newPath);
        sum += computeDirSize(newPath);
      //free(newPath);
      }
    }else{
      struct stat buffer;
      int err = stat(path, &buffer);
      if( err < 0 ){ printf("Error:%s\n", strerror(errno)); };
      sum += buffer.st_size;
    }
    line = readdir(cur);
  }while( line != NULL);
  closedir(cur);
  return sum;
}

void printOutDir(char * path){
  DIR *cur = opendir(path);
  //printf("Seg faulted?\n");
  char dirList[1000] = "Directories:\n";
  char fileList[1000] = "Regular Files:\n";
  //printf("Seg\n");
  struct dirent *line = readdir(cur);
  do{
    //printf("File being Accessed [%s]\n",line->d_name);
    if(line->d_type == 4){
      char temp[256];
      sprintf(temp, "\t%s\n", line->d_name);
      strcat(dirList,temp);
    }else{
      char temp[256];
      sprintf(temp, "\t%s\n", line->d_name);
      strcat(fileList, temp);
    }
    line = readdir(cur);
  }while( line != NULL);
  printf("%s%s",dirList,fileList);  
  closedir(cur);
}
