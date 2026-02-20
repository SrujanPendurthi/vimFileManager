#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

void findDataSize(struct stat st)
{
  double bytes = (double)st.st_size;
  const char *dataUnits[5] = {"B","KB","MB","GB","TB"};
  
  int sizeIndex=0;
  while (bytes > 1024 && sizeIndex < 4)
  {
    bytes /= 1024;
    ++sizeIndex;
  }
  printf("%.2f %s", bytes,dataUnits[sizeIndex]);
}

void filterDotFile(struct dirent *entry) 
{
  if(entry->d_name[0] != '.')
  {
    struct stat st;
    if (stat(entry->d_name, &st) == -1) 
    {
      printf("%s [Error getting stats]\n", entry->d_name);
      return;
    }

    if (S_ISDIR(st.st_mode))
    {
      printf("%-20s [DIR]\n", entry->d_name); 
    }
    else 
    {
      printf("%-20s [FILE]", entry->d_name);
      findDataSize(st);
      printf("\n");
    }
  }
}

int main(void) 
{
  char path[256] = ".";
  char choice[256];

  while(1) 
  {
    struct dirent *entry;
    DIR *dp = opendir(".");

    if (dp==NULL) 
    {
      perror("there was an error opening");
      break;
    }
    while((entry = readdir(dp)) != NULL) 
    {
      filterDotFile(entry);
    }
    closedir(dp);

    printf("\nEnter a directory to open(or 'q' to quit)");
    scanf(" %s",choice);
  
    if (choice[0] == 'q') {exit(0);}
    if (chdir(choice)!= 0) 
    {
      printf("Could not move to %s\n",choice);
    }
  }
  return 0;
}

