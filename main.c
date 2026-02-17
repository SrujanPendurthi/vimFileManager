#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

float findDataSize(struct stat st)
{
  float dataSize;
  //make everything in GB, MB, KB, etc.
  //count the number of digits you chop off 
  //before you hit three sig figs
  //(might be a more data driven way to do this)
  return dataSize; 
}

void filterDotFile(struct dirent *entry) // Added struct keyword for clarity
{
  if(entry->d_name[0] != '.')
  {
    struct stat st;
        // We need to call stat to get the actual file information
    if (stat(entry->d_name, &st) == -1) 
    {
      printf("%s [Error getting stats]\n", entry->d_name);
      return;
    }

    if (S_ISDIR(st.st_mode)) // More portable way to check for Directory
    {
      printf("%-20s [DIR]\n", entry->d_name); 
    }
    else 
    {
      printf("%-20s [FILE] %ld bytes\n", entry->d_name, (long)st.st_size);
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

