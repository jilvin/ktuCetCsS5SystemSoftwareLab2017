// 2) Simulate the following file organization techniques
// b) Two level directory

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
  struct directory* nextDirectory;
  struct file* startFile;
  struct directory* startDirectory;
};

void clearScreen()
{
  printf("\033[H\033[J");
}

int ceiling(float x)
{
  int y = (int) x;
  if(x>y)
  {
    y++;
  }
  // printf("%f\t%d\n",x,y);
  return y;
}

void newFolder(struct directory* ourDirectory)
{
  struct directory* endPointer = ourDirectory->startDirectory;
  struct directory* secondLastPointer = NULL;
  if(ourDirectory != NULL)
  {
    clearScreen();
    while(endPointer != NULL)
    {
      if(endPointer != NULL)
      {
        secondLastPointer = endPointer;
      }
      endPointer = endPointer->nextDirectory;
    }
    endPointer = malloc(sizeof(struct file));
    printf("Enter folder name:\n");
    scanf("%s",&(endPointer->directoryName[0]));
    endPointer->nextDirectory = NULL;
    if(secondLastPointer != NULL)
    {
      secondLastPointer->nextDirectory = endPointer;
    }
    else
    {
      ourDirectory->startDirectory = endPointer;
    }
    clearScreen();
    printf("Folder added successfully.\n\n");
  }
  else
  {
    clearScreen();
    printf("Error: Unable to allocate required structure.\n");
  }
}

void newFile(struct directory* ourDirectory)
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

int listFolders(struct directory* ourDirectory)
{
  // clearScreen();
  if(ourDirectory != NULL)
  {
    if(ourDirectory->startDirectory != NULL)
    {
      struct directory* movePointer = ourDirectory->startDirectory;
      // printf("List of files:\n\n");
      while(movePointer != NULL)
      {
        int tCount = (7-ceiling(((float) strlen(movePointer->directoryName))/8.0));
        printf("%s",movePointer->directoryName);
        for(int i=0; i<tCount; i++)
        {
          printf("\t");
        }
        printf("d\n");
        movePointer = movePointer->nextDirectory;
      }
      // printf("\n");
      return 1;
    }
    else
    {
      // printf("No folders found in directory %s.\n",ourDirectory->directoryName);
      return 0;
    }
  }
  else
  {
    clearScreen();
    printf("Error: Unable to allocate required structure.\n");
  }
}

int listFiles(struct directory* ourDirectory)
{
  // clearScreen();
  if(ourDirectory != NULL)
  {
    if(ourDirectory->startFile != NULL)
    {
      struct file* movePointer = ourDirectory->startFile;
      // printf("List of files:\n\n");
      while(movePointer != NULL)
      {
        int tCount = (7-ceiling(((float) strlen(movePointer->fileName))/8.0));
        printf("%s",movePointer->fileName);
        for(int i=0; i<tCount; i++)
        {
          printf("\t");
        }
        printf("f\n");
        movePointer = movePointer->nextFile;
      }
      // printf("\n");
      return 1;
    }
    else
    {
      // printf("No files found in directory %s.\n\n",ourDirectory->directoryName);
      return 0;
    }
  }
  else
  {
    clearScreen();
    printf("Error: Unable to allocate required structure.\n");
  }
}

void searchFile(struct directory* ourDirectory)
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

void deleteFile(struct directory* ourDirectory)
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
  struct directory* root = malloc(sizeof(struct directory));
  strcpy(root->directoryName,"/");
  root->nextDirectory=NULL;
  root->startFile = NULL;
  root->startDirectory = NULL;
  if(root != NULL)
  {
    do
    {
      char* path;
      int returnListFoldersStatus, returnListFilesStatus;
      strcpy(path,"/");
      printf("Current path:\n%s\n\n1)\tNew Folder\n2)\tNew File\n3)\tList\n4)\tSearch File\n5)\tDelete File\n6)\tExit\n\nPlease enter your choice:\n",path);
      scanf("%d",&choice);
      switch(choice)
      {
        case 1: newFolder(root);
        break;
        case 2: newFile(root);
        break;
        case 3: clearScreen();
        printf("Name\t\t\t\t\t\tType\n\n");
        returnListFoldersStatus = listFolders(root);
        returnListFilesStatus = listFiles(root);
        if(returnListFoldersStatus == 0 && returnListFilesStatus == 0)
        {
          clearScreen();
          printf("Nothing found in directory %s.\n\n",root->directoryName);
        }
        else
        {
          printf("\n");
        }
        break;
        case 4: searchFile(root);
        break;
        case 5: deleteFile(root);
        break;
        default: choice = 6;
      }
    }while( (choice>0) && (choice<6));
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
