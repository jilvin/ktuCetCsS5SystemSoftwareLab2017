#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearScreen()
{
  printf("\033[H\033[J");
}

struct Philosopher
{
  int uid;
  char name[40];
  int leftHand;
  int rightHand;
  char status[20];
  struct Philosopher* leftPhilosopher;
  struct Philosopher* rightPhilosopher;
};

struct Philosopher* getPhilosopherInfo()
{
  struct Philosopher* newPhilosopher = NULL;
  newPhilosopher = (struct Philosopher*) malloc(sizeof(struct Philosopher));
  if(newPhilosopher != NULL)
  {
    clearScreen();
    newPhilosopher->uid = 0;
    printf("Enter name of Philosopher:\n");
    scanf("%s",newPhilosopher->name);
    newPhilosopher->leftHand = 0;
    newPhilosopher->rightHand = 0;
    strcpy(newPhilosopher->status, "thinking");
    newPhilosopher->leftPhilosopher = NULL;
    newPhilosopher->rightPhilosopher = NULL;
    printf("\n");
  }
  else
  {
    printf("Error: Unable to allocate memory.\n");
  }
  return newPhilosopher;
}

struct Philosopher* addPhilosopher(struct Philosopher* startPhilosopher)
{
  if(startPhilosopher != NULL)
  {
    struct Philosopher* movePointer = startPhilosopher;

    if(movePointer->uid == movePointer->rightPhilosopher->uid)
    {
      // do nothing
    }
    else
    {
      while(movePointer->uid < movePointer->rightPhilosopher->uid && movePointer->rightPhilosopher->uid != startPhilosopher->uid)
      {
        // printf("the weather is lovely\n");
        movePointer = movePointer->rightPhilosopher;
      }
    }

    movePointer->rightPhilosopher = getPhilosopherInfo();
    if(movePointer->rightPhilosopher != NULL)
    {
      movePointer->rightPhilosopher->uid = movePointer->uid + 1;
      // circular seating -- start
      startPhilosopher->leftPhilosopher = movePointer->rightPhilosopher;
      movePointer->rightPhilosopher->rightPhilosopher = startPhilosopher;
      movePointer->rightPhilosopher->leftPhilosopher = movePointer;
      // circular seating -- end
      return startPhilosopher;
    }
    else
    {
      printf("Error: Unable to obtain information successfully.\n");
      return startPhilosopher;
    }
  }
  else
  {
    startPhilosopher = getPhilosopherInfo();

    startPhilosopher->uid = 1;
    // circular seating -- start
    startPhilosopher->leftPhilosopher = startPhilosopher;
    startPhilosopher->rightPhilosopher = startPhilosopher;
    // circular seating -- end

    return startPhilosopher;
  }
}

void displayPhilosophers(struct Philosopher* startPhilosopher)
{
  clearScreen();
  int slNo = 1;
  if(startPhilosopher != NULL)
  {
    printf("Dining Philosophers\n\n");
    struct Philosopher* movePointer = startPhilosopher;
    if(movePointer->uid == movePointer->rightPhilosopher->uid)
    {
      printf("%d)\t%s\n", slNo, movePointer->name);
      slNo++;
    }
    else
    {
      while(movePointer->uid < movePointer->rightPhilosopher->uid)
      {
        printf("%d)\t%s\n", slNo, movePointer->name);
        slNo++;
        movePointer = movePointer->rightPhilosopher;
      }
      printf("%d)\t%s\n", slNo, movePointer->name);
      slNo++;
      movePointer = movePointer->rightPhilosopher;
    }
    printf("\n");
  }
}

struct Philosopher* removePhilosopher(struct Philosopher* startPhilosopher)
{
  return startPhilosopher;
}

struct Philosopher* managePhilosophers(struct Philosopher* startPhilosopher)
{
  clearScreen();
  int choice;
  printf("Manage Philosophers - Menu\n\n1)\tAdd Philosopher\n2)\tList Philosophers\n3)\tRemove Philosopher\n4)\tBack to Main Menu\n\nPlease enter your choice:\n");
  scanf("%d", &choice);

  // switching -- start
  switch(choice)
  {
    case 1: startPhilosopher = addPhilosopher(startPhilosopher);
    break;

    case 2: displayPhilosophers(startPhilosopher);
    break;

    case 3: startPhilosopher = removePhilosopher(startPhilosopher);
    break;
  }
  // switching -- end
  if(choice < 1 || choice > 3)
  {
    clearScreen();
  }
  return startPhilosopher;
}

struct Philosopher* philosopherActions(struct Philosopher* startPhilosopher)
{
  clearScreen();
  int slNo = 1, choice, choice2;
  if(startPhilosopher != NULL)
  {
    printf("Dining Philosophers\n\n");
    struct Philosopher* movePointer =  startPhilosopher;
    if(movePointer->uid == movePointer->rightPhilosopher->uid)
    {
      printf("%d)\t%s\n", slNo, movePointer->name);
      slNo++;
    }
    else
    {
      while(movePointer->uid < movePointer->rightPhilosopher->uid)
      {
        printf("%d)\t%s\n", slNo, movePointer->name);
        slNo++;
        movePointer = movePointer->rightPhilosopher;
      }
      printf("%d)\t%s\n", slNo, movePointer->name);
      slNo++;
      movePointer = movePointer->rightPhilosopher;
    }
    printf("\n");

    printf("Philosopher Actions - Menu\n\nSelect the philosopher you want to act upon.\n");
    scanf("%d", &choice);

    if(choice>0 && choice<slNo)
    {
      int counter = 1;
      movePointer = startPhilosopher;
      clearScreen();
      while(counter < choice)
      {
        movePointer = movePointer->rightPhilosopher;
        counter++;
      }
      printf("Philosopher %s\n\nCurrent Status:\t%s\n\n", movePointer->name, movePointer->status);
      printf("Possilble Actions\n\n1)\tThinking\n2)\tEating\n\n");
      printf("Choose your action\n");
      scanf("%d", &choice2);

      // switching -- start
      switch(choice2)
      {
        case 1: movePointer->leftHand = 0;
        movePointer->rightHand = 0;
        strcpy(movePointer->status, "thinking");
        clearScreen();
        printf("%s is currently %s.\n", movePointer->name, movePointer->status);
        break;

        case 2: // set eating actions -- start
        if(movePointer->leftPhilosopher->rightHand == 0 && movePointer->rightPhilosopher->leftHand == 0)
        {
          movePointer->leftHand = 1;
          movePointer->rightHand = 1;
          strcpy(movePointer->status, "eating");
          clearScreen();
          printf("%s is currently %s.\n", movePointer->name, movePointer->status);
        }
        else
        {
          clearScreen();
          printf("Unable to change action of philosopher %s to eating.\n", movePointer->name);
        }
        // set eating actions -- end
        break;

        default: strcpy(movePointer->status, "thinking");
        clearScreen();
        printf("%s is currently %s.\n", movePointer->name, movePointer->status);
      }
      // switching -- end
    }
    else
    {
      clearScreen();
      printf("Error: Invalid Philosopher selection.\n");
    }
    printf("\n");
    return startPhilosopher;
  }
  else
  {
    printf("The table is absolutely free. Try luring some philosopher. :P\n\n");
    return NULL;
  }
}

struct Philosopher* currentStatus(struct Philosopher* startPhilosopher)
{
  clearScreen();
  if(startPhilosopher != NULL)
  {
    printf("Status of Philosophers\n\n");
    int slNo = 1;
    struct Philosopher* movePointer =  startPhilosopher;
    if(movePointer->uid == movePointer->rightPhilosopher->uid)
    {
      printf("%d)\t%s is %s.\n", slNo, movePointer->name, movePointer->status);
      slNo++;
    }
    else
    {
      while(movePointer->uid < movePointer->rightPhilosopher->uid)
      {
        printf("%d)\t%s is %s.\n", slNo, movePointer->name, movePointer->status);
        slNo++;
        movePointer = movePointer->rightPhilosopher;
      }
      printf("%d)\t%s is %s.\n", slNo, movePointer->name, movePointer->status);
      slNo++;
      movePointer = movePointer->rightPhilosopher;
    }
    printf("\n");
    return startPhilosopher;
  }
  else
  {
    printf("The table is absolutely free. Try luring some philosopher. :P\n\n");
    return NULL;
  }
}

int main()
{
  int choice;
  struct Philosopher* startPhilosopher = NULL;
  clearScreen();
  do
  {
    printf("The Great Philosopher's Dining Table!\n\n");
    printf("1)\tManage Philosophers\n");
    printf("2)\tPhilosopher Actions\n");
    printf("3)\tCurrent Status\n");
    printf("4)\tExit\n");

    printf("\nEnter your choice:\n");
    scanf("%d", &choice);

    // switching -- start
    switch(choice)
    {
      case 1: startPhilosopher = managePhilosophers(startPhilosopher);
      break;
      case 2: startPhilosopher = philosopherActions(startPhilosopher);
      break;
      case 3: startPhilosopher = currentStatus(startPhilosopher);
      break;
      default: choice = 4;
    }
    // switching -- end

  } while(choice>0 && choice<4);
  clearScreen();
  printf("Thanks for visiting The Great Philosopher's Dining Table. We are honoured to serve you.\n\n");
}
