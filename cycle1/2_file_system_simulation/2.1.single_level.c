// 2) Simulate the following file organization techniques
// a) Single level directory

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct file
{
  char fileName[40];
  struct file* nextFile;
};

struct directory
{
  char directoryName[40];
  struct file* startFile;
};

struct directory* ourDirectory = NULL;

void clearScreen()
{
  printf("\033[H\033[J");
}

void newFile()
{
  struct file* endPointer = ourDirectory->startFile;
  struct file* secondLastPointer = NULL;
  if(ourDirectory != NULL)
  {
    clearScreen();
    while(endPointer != NULL)
    {
      if(endPointer != NULL)
      {
        secondLastPointer = endPointer;
      }
      endPointer = endPointer->nextFile;
    }
    endPointer = malloc(sizeof(struct file));
    printf("Enter file name:\n");
    scanf("%s",&(endPointer->fileName[0]));
    endPointer->nextFile = NULL;
    if(secondLastPointer != NULL)
    {
      secondLastPointer->nextFile = endPointer;
    }
    else
    {
      ourDirectory->startFile = endPointer;
    }
    clearScreen();
    printf("File added successfully.\n\n");
  }
  else
  {
    clearScreen();
    printf("Error: Unable to allocate required structure.\n");
  }
}

void listFiles()
{
  clearScreen();
  if(ourDirectory != NULL)
  {
    if(ourDirectory->startFile != NULL)
    {
      struct file* movePointer = ourDirectory->startFile;
      printf("List of files:\n\n");
      while(movePointer != NULL)
      {
        printf("%s\n",movePointer->fileName);
        movePointer = movePointer->nextFile;
      }
      printf("\n");
    }
    else
    {
      printf("No files found in directory %s.\n\n",ourDirectory->directoryName);
    }
  }
  else
  {
    clearScreen();
    printf("Error: Unable to allocate required structure.\n");
  }
}

void searchFile()
{
  clearScreen();
  char searchString[40];
  int flag = 0;
  if(ourDirectory != NULL)
  {
    if(ourDirectory->startFile != NULL)
    {
      struct file* movePointer = ourDirectory->startFile;
      printf("Enter fileName to be searched for:\n");
      scanf("%s", searchString);
      while(movePointer != NULL)
      {
        if(strcmp(movePointer->fileName, searchString) == 0)
        {
          flag = 1; // match found
        }
        movePointer = movePointer->nextFile;
      }
      if(flag == 1)
      {
        clearScreen();
        printf("File with fileName %s found.\n\n", searchString);
      }
      else
      {
        clearScreen();
        printf("File with fileName %s not found.\n\n", searchString);
      }
    }
    else
    {
      printf("No files found in directory %s.\n\n",ourDirectory->directoryName);
    }
  }
  else
  {
    clearScreen();
    printf("Error: Unable to allocate required structure.\n");
  }
}

void deleteFile()
{
  clearScreen();
  char searchString[40];
  int flag = 0;
  if(ourDirectory != NULL)
  {
    if(ourDirectory->startFile != NULL)
    {
      struct file* movePointer = ourDirectory->startFile;
      struct file* prevSavePointer = ourDirectory->startFile;
      struct file* savePointer = NULL;
      printf("Enter fileName to be searched and deleted for:\n");
      scanf("%s", searchString);
      while(movePointer != NULL)
      {
        if(strcmp(movePointer->fileName, searchString) == 0 && flag == 0) // finds the first match
        {
          flag = 1; // match found
          savePointer = movePointer;
        }
        if(movePointer != ourDirectory->startFile && flag == 0)
        {
          prevSavePointer = prevSavePointer->nextFile;
        }
        movePointer = movePointer->nextFile;
      }
      if(flag == 1)
      {
        clearScreen();
        if(savePointer == ourDirectory->startFile)
        {
          // first file to be deleted
          ourDirectory->startFile = savePointer->nextFile;
          free(savePointer);
        }
        else
        {
          prevSavePointer->nextFile = savePointer->nextFile;
          free(savePointer);
        }
        printf("File with fileName %s found and deleted successfully.\n\n", searchString);
      }
      else
      {
        clearScreen();
        printf("File with fileName %s not found.\n\n", searchString);
      }
    }
    else
    {
      clearScreen();
      printf("No files found in directory %s.\n\n",ourDirectory->directoryName);
    }
  }
  else
  {
    printf("Error: Unable to allocate required structure.\n");
  }
}

int main()
{
  clearScreen();
  int choice;
  ourDirectory = malloc(sizeof(struct directory));
  strcpy(ourDirectory->directoryName,"Main Directory");
  ourDirectory->startFile = NULL;
  if(ourDirectory != NULL)
  {
    do
    {
      printf("File System Simulator - Single Level\n\n1)\tNew File\n2)\tList Files\n3)\tSearch File\n4)\tDelete File\n5)\tExit\n\nPlease enter your choice:\n");
      scanf("%d",&choice);
      switch(choice)
      {
        case 1: newFile();
        break;
        case 2: listFiles();
        break;
        case 3: searchFile();
        break;
        case 4: deleteFile();
        break;
        default: choice = 5;
      }
    }while( (choice>0) && (choice<5));
    clearScreen();
    printf("Thanks for using Non-preemptive CPU Scheduling Simulation. Take care. Bye.\n");
    return 1;
  }
  else
  {
    printf("Error: Unable to allocate required structure. Exiting.\n");
    return 0;
  }
}
