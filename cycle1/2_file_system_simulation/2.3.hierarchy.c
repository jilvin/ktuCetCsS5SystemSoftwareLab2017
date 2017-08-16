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
  struct directory* parentDirectory;
};

struct directory* currentDirectory;
// char* currentPath;

void clearScreen()
{
  printf("\033[H\033[J");
}

int customCeiling(float x)
{
  // printf("%f\n", x);
  int y = (int) x;
  if(x>y || x==y)
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
    endPointer = malloc(sizeof(struct directory));
    printf("Enter directory name:\n");
    scanf("%s",&(endPointer->directoryName[0]));
    endPointer->startFile = NULL;
    endPointer->nextDirectory = NULL;
    endPointer->startDirectory = NULL;
    if(secondLastPointer != NULL)
    {
      secondLastPointer->nextDirectory = endPointer;
      endPointer->parentDirectory = secondLastPointer;
    }
    else
    {
      ourDirectory->startDirectory = endPointer;
      endPointer->parentDirectory = ourDirectory;
    }
    clearScreen();
    printf("Directory added successfully.\n\n");
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
        int tCount = (7-customCeiling((((float) strlen(movePointer->directoryName))/8.0)));
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
        int tCount = (7-customCeiling(((float) strlen(movePointer->fileName))/8.0));
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

void searchDirectory(struct directory* ourDirectory)
{
  clearScreen();
  char searchString[40];
  int flag = 0;
  if(ourDirectory != NULL)
  {
    if(ourDirectory->startDirectory != NULL)
    {
      struct directory* movePointer = ourDirectory->startDirectory;
      printf("Enter directoryName to be searched for:\n");
      scanf("%s", searchString);
      while(movePointer != NULL)
      {
        if(strcmp(movePointer->directoryName, searchString) == 0)
        {
          flag = 1; // match found
        }
        movePointer = movePointer->nextDirectory;
      }
      if(flag == 1)
      {
        clearScreen();
        printf("File with directoryName %s found.\n\n", searchString);
      }
      else
      {
        clearScreen();
        printf("File with directoryName %s not found.\n\n", searchString);
      }
    }
    else
    {
      printf("No directories found in directory %s.\n\n",ourDirectory->directoryName);
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

void deleteDirectory(struct directory* ourDirectory)
{
  // Urgent: Rewrite for recursive freeing of memory resources.
  clearScreen();
  char searchString[40];
  int flag = 0;
  if(ourDirectory != NULL)
  {
    if(ourDirectory->startDirectory != NULL)
    {
      struct directory* movePointer = ourDirectory->startDirectory;
      struct directory* prevSavePointer = ourDirectory->startDirectory;
      struct directory* savePointer = NULL;
      printf("Enter directoryName to be searched and deleted for:\n");
      scanf("%s", searchString);
      while(movePointer != NULL)
      {
        if(strcmp(movePointer->directoryName, searchString) == 0 && flag == 0) // finds the first match
        {
          flag = 1; // match found
          savePointer = movePointer;
        }
        if(movePointer != ourDirectory->startDirectory && flag == 0)
        {
          prevSavePointer = prevSavePointer->nextDirectory;
        }
        movePointer = movePointer->nextDirectory;
      }
      if(flag == 1)
      {
        clearScreen();
        if(savePointer == ourDirectory->startDirectory)
        {
          // first directory to be deleted
          ourDirectory->startDirectory = savePointer->nextDirectory;
          free(savePointer);
        }
        else
        {
          prevSavePointer->nextDirectory = savePointer->nextDirectory;
          free(savePointer);
        }
        printf("Directory with directoryName %s found and deleted successfully.\n\n", searchString);
      }
      else
      {
        clearScreen();
        printf("Directory with directoryName %s not found.\n\n", searchString);
      }
    }
    else
    {
      clearScreen();
      printf("No directories found in directory %s.\n\n",ourDirectory->directoryName);
    }
  }
  else
  {
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

void changeDirectory(struct directory* ourDirectory)
{
  clearScreen();
  int tCount, num, i, j, intLen, choice, flagChanged = 0;
  if(ourDirectory != NULL)
  {
    if(ourDirectory->startDirectory != NULL || ourDirectory->parentDirectory != NULL)
    {
      struct directory* movePointer = ourDirectory->startDirectory;
      printf("List of directories:\n\n");
      if(ourDirectory -> parentDirectory != NULL)
      {
        tCount = (6-customCeiling(((float) strlen("1"))/8.0));
        printf("0");
        for(int i=0; i<tCount; i++)
        {
          printf("\t");
        }
        tCount = (7-customCeiling(((float) strlen(".."))/8.0));
        printf("..");
        for(int i=0; i<tCount; i++)
        {
          printf("\t");
        }
        printf("d\n");
      }
      num = 1;
      while(movePointer != NULL)
      {
        intLen = 0;
        j = num;
        while(j % 10 != 0)
        {
          intLen++;
          j = j/10;
        }
        tCount = (6-customCeiling((intLen/8.0)));
        printf("%d",num);
        num++;
        for(int i=0; i<tCount; i++)
        {
          printf("\t");
        }
        tCount = (7-customCeiling(((float) strlen(movePointer->directoryName))/8.0));
        printf("%s",movePointer->directoryName);
        for(int i=0; i<tCount; i++)
        {
          printf("\t");
        }
        printf("d\n");
        movePointer = movePointer->nextDirectory;
      }
      printf("\n");
      printf("Choose your desired directory:\n");
      scanf("%d", &choice);
      if(choice>-1 && choice<num)
      {
        clearScreen();
        if(choice == 0 && ourDirectory->parentDirectory!=NULL)
        {
          currentDirectory = ourDirectory->parentDirectory;
        }
        else
        {
          j = 1;
          movePointer = ourDirectory->startDirectory;
          while(movePointer != NULL && flagChanged == 0)
          {
            if(choice == j)
            {
              currentDirectory = movePointer;
              flagChanged = 1;
            }
            j++;
          }
          if(flagChanged == 1)
          {
            printf("Directory successfully changed.\n\n");
          }
          else
          {
            printf("Error: Unexpected error occurred.\n\n");
          }
        }
      }
      else
      {
        clearScreen();
        printf("Invalid Choice!\n");
      }
    }
    else
    {
      printf("No directories found in directory %s.\n",ourDirectory->directoryName);
    }
  }
  else
  {
    clearScreen();
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
  root->parentDirectory = NULL;
  currentDirectory = root;
  // strcpy(currentPath,"/");
  if(currentDirectory != NULL)
  {
    do
    {
      int returnListFoldersStatus, returnListFilesStatus;
      if(currentDirectory->parentDirectory != NULL)
      {
        printf("Parent directory:\n%s\n\n1)\tNew Folder\n2)\tNew File\n3)\tList\n4)\tSearch Folder\n5)\tSearch File\n6)\tDelete Folder\n7)\tDelete File\n8)\tChange directory\n9)\tExit\n\nPlease enter your choice:\n",currentDirectory->parentDirectory->directoryName);
      }
      else
      {
        printf("You are at the root directory.\n\n1)\tNew Folder\n2)\tNew File\n3)\tList\n4)\tSearch Folder\n5)\tSearch File\n6)\tDelete Folder\n7)\tDelete File\n8)\tChange directory\n9)\tExit\n\nPlease enter your choice:\n");
      }
      scanf("%d",&choice);
      switch(choice)
      {
        case 1: newFolder(currentDirectory);
        break;
        case 2: newFile(currentDirectory);
        break;
        case 3: clearScreen();
        printf("Name\t\t\t\t\t\tType\n\n");
        returnListFoldersStatus = listFolders(currentDirectory);
        returnListFilesStatus = listFiles(currentDirectory);
        if(returnListFoldersStatus == 0 && returnListFilesStatus == 0)
        {
          clearScreen();
          printf("Nothing found in directory %s.\n\n",currentDirectory->directoryName);
        }
        else
        {
          printf("\n");
        }
        break;
        case 4: searchDirectory(currentDirectory);
        break;
        case 5: searchFile(currentDirectory);
        break;
        case 6: deleteDirectory(currentDirectory);
        break;
        case 7: deleteFile(currentDirectory);
        break;
        case 8: changeDirectory(currentDirectory);
        break;
        default: choice = 9;
      }
    }while( (choice>0) && (choice<9));
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
