// 1) Simulate the following non-preemptive CPU scheduling algorithms to find turnaround time and waiting time.
// a) FCFS b) SJF c) Round Robin (pre-emptive) d) Priority

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int choice = 3;

struct process
{
  int integerData[4];
  char processName[32];
  struct process* nextProcess;
  // int processID;
  // int jobEntryTime;
  // int jobBurstTime; //burstTime
  // int priority;
};

struct process* startPointer=NULL;

void clearScreen()
{
  printf("\033[H\033[J");
}

void listProcess(struct process* pointer)
{
  printf("processID\t:\t%d\nprocessName\t:\t%s\npriority\t:\t%d\njobEntryTime\t:\t%d\njobBurstTime\t:\t%d\n\n",pointer->integerData[0],pointer->processName,pointer->integerData[3],pointer->integerData[1],pointer->integerData[2]);
}

void listAllProcesses(struct process* recievedStartPointer)
{
  // clearScreen();
  struct process* pointer = recievedStartPointer;
  if(pointer!=NULL)
  {
    while(pointer->nextProcess!=NULL)
    {
      listProcess(pointer);
      pointer = pointer->nextProcess;
    }
    listProcess(pointer);
  }
  else
  {
    printf("Error: No processes found.\n\n");
  }
}

struct process* deleteProcess(int processID, struct process* startPointer)
{
  int processFound=0;
  struct process* pointer = startPointer;
  struct process* pointerBack = NULL;
  if(pointer->nextProcess == NULL)
  {
    if(pointer->integerData[0] == processID)
    {
      processFound = 1;
    }
  }
  else
  {
    while(pointer->nextProcess!=NULL && processFound == 0)
    {
      if(pointer->integerData[0] == processID)
      {
        processFound = 1;
      }
      else
      {
        if(pointerBack != NULL)
        {
          pointerBack = pointerBack->nextProcess;
        }
        pointer = pointer->nextProcess;
      }
      if(pointer == startPointer->nextProcess)
      {
        pointerBack = startPointer;
      }
    }
    if(pointer->nextProcess == NULL && processFound == 0)
    {
      // case of last element
      if(pointer->integerData[0] == processID)
      {
        processFound = 1;
      }
    }
  }
  if(processFound == 1)
  {
    if(pointerBack == NULL)
    {
      // first element is to be deleted
      if(pointer->nextProcess == NULL)
      {
        // single element
        startPointer = NULL;
      }
      else
      {
        startPointer = pointer->nextProcess;
      }
    }
    else if(pointer->nextProcess == NULL)
    {
      // case of last element
      pointerBack->nextProcess = NULL;
    }
    else
    {
      pointerBack->nextProcess = pointer->nextProcess;
    }
    free(pointer);
    // clearScreen();
    // printf("Process with processID %d deleted successfully.\n\n", processID);
    return startPointer;
  }
  else if(processFound == 0)
  {
    // clearScreen();
    printf("Error: Process with processID %d not found.\n\n",processID);
  }
}

void deleteProcessPrompt()
{
  clearScreen();
  int processID;
  struct process* pointer = startPointer;
  if(pointer!=NULL)
  {
    printf("Enter processID of the process to be deleted:\n");
    scanf("%d",&processID);
    startPointer = deleteProcess(processID, startPointer);
    printf("Process with processID %d deleted successfully.\n\n", processID);
  }
  else
  {
    printf("Error: No processes found.\n\n");
  }
}

void newProcess()
{
  clearScreen();
  int processNo;
  struct process* pointer = startPointer;
  struct process* savePointer = NULL;
  if(pointer != NULL && pointer->integerData[0] == 1)
  {
    while(pointer->nextProcess != NULL && savePointer == NULL)
    {
      if(pointer->integerData[0]+1 == pointer->nextProcess->integerData[0])
      {
        pointer = pointer->nextProcess;
      }
      else
      {
        savePointer = pointer->nextProcess;
      }
    }
    //reached end of list
    pointer->nextProcess = malloc(sizeof(struct process));
    processNo = pointer->integerData[0];
    pointer = pointer->nextProcess;
  }
  else if(pointer != NULL)
  {
    pointer = malloc(sizeof(struct process));
    processNo = 0;
    savePointer = startPointer;
    startPointer = pointer;
  }
  else
  {
    pointer = malloc(sizeof(struct process));
    startPointer = pointer;
    processNo = 0;
  }
  pointer->integerData[0] = ++processNo;
  printf("Enter processName:\n");
  scanf("%s",&(pointer->processName[0]));
  printf("Enter priority:\n");
  scanf("%d",&(pointer->integerData[3]));
  // printf("Enter jobEntryTime:\n");
  // scanf("%d",&(pointer->integerData[1]));
  pointer->integerData[1] = 0;
  printf("Enter jobBurstTime:\n");
  scanf("%d",&(pointer->integerData[2]));
  clearScreen();
  printf("Process Details:\n\n");
  listProcess(pointer);
  if(savePointer==NULL)
  {
    pointer->nextProcess=NULL;
  }
  else
  {
    pointer->nextProcess = savePointer;
  }
}

void copyProcessStructure(struct process* copyPointer, struct process* originalPointer)
{
  // copying starts here
  if(copyPointer == NULL)
  {
    copyPointer = malloc(sizeof(struct process));
  }
  for(int i=0; i<4; i++)
  {
    copyPointer->integerData[i] = originalPointer->integerData[i];
  }
  strcpy(copyPointer->processName, originalPointer->processName);
}

void copyProcessStructureUsingProcessID(struct process* pointer, int lessValueProcessID)
{
  struct process* movePointer = startPointer;
  int flag = 0;
  while(movePointer != NULL && flag == 0)
  {
    if(movePointer->integerData[0] == lessValueProcessID)
    {
      flag = 1;
    }
    if(flag == 0)
    {
      movePointer=movePointer->nextProcess;
    }
  }
  // copying starts here
  for(int i=0; i<4; i++)
  {
    pointer->integerData[i] = movePointer->integerData[i];
  }
  strcpy(pointer->processName, movePointer->processName);
  pointer->nextProcess = movePointer->nextProcess;
  // printf("just checking\n");
}

struct process* copyList(struct process* copyList, struct process* originalList, int isCopyListEmpty)
{
  struct process* copyListPointer = copyList;
  struct process* copyStartPointer = copyListPointer;
  struct process* pointer = originalList;
  struct process* backPointer = NULL;
  int runOnce = 0;
  if(isCopyListEmpty == 1)
  {
    while(pointer != NULL)
    {
      if(runOnce == 1)
      {
        copyListPointer = malloc(sizeof(struct process));
        backPointer->nextProcess = copyListPointer;
      }
      copyProcessStructure(copyListPointer, pointer);
      // printf("no issue till here\n");
      backPointer = copyListPointer;
      pointer = pointer->nextProcess;
      if(runOnce == 0)
      {
        runOnce = 1;
      }
    }
    return copyStartPointer;
  }
}

struct process* makeListSort(int value)
{
  struct process* returnStartPointer = NULL;
  struct process* pointer = NULL;
  struct process* savePointer = NULL;
  struct process* copyStartPointer = NULL;
  int lessValue;
  int lessValueProcessID;
  int lessFound;
  struct process* movePointer = NULL;
  copyStartPointer = malloc(sizeof(struct process));
  copyStartPointer = copyList(copyStartPointer, startPointer, 1);
  // listAllProcesses(copyStartPointer);
  // printf("i checked here\n");
  // copyStartPointer = startPointer;
  if(copyStartPointer != NULL)
  {
    lessValue = copyStartPointer->integerData[value];
    lessValueProcessID = copyStartPointer->integerData[0];
    do
    {
      // printf("%d\n",lessValue);
      movePointer = copyStartPointer;
      lessFound = 0;
      while(movePointer != NULL)
      {
        if(lessValue >= movePointer->integerData[value])
        {
          lessValue = movePointer->integerData[value];
          lessValueProcessID = movePointer->integerData[0];
          lessFound = 1;
        }
        movePointer = movePointer->nextProcess;
      }
      // printf("lessValue:%d\nlessValueProcessID:%d\n",lessValue,lessValueProcessID);
      if(lessFound == 1)
      {
        if(pointer != NULL)
        {
          savePointer = pointer;
        }
        pointer = malloc(sizeof(struct process));
        if(savePointer != NULL) // && savePointer != copyStartPointer)
        {
          savePointer->nextProcess = pointer;
        }
        if(returnStartPointer == NULL)
        {
          returnStartPointer = pointer;
        }
        copyProcessStructureUsingProcessID(pointer, lessValueProcessID);
        copyStartPointer = deleteProcess(lessValueProcessID, copyStartPointer);
        if(copyStartPointer != NULL)
        {
          lessValue = copyStartPointer->integerData[value];
          lessValueProcessID = copyStartPointer->integerData[0];
        }
        // listAllProcesses(copyStartPointer);
      }
    } while(copyStartPointer != NULL);
    // printf("works here\n");
    pointer->nextProcess = NULL;
    return returnStartPointer;
  }
  else
  {
    printf("Error: No processes found.\n\n");
    return NULL;
  }
}

float sumOfWaitingTimeCalc(struct process* pointer)
{
  struct process* copyStartPointer = pointer;
  float sumOfWaitingTime = 0.0, avgWaitingTime = 0.0;
  int count = 0;
  while(pointer != NULL)
  {
    if(pointer->nextProcess != NULL)
    {
      sumOfWaitingTime = (2 * sumOfWaitingTime) + pointer->integerData[2];
    }
    pointer = pointer->nextProcess;
  }
  return sumOfWaitingTime;
}

void calcAndPrintAverageTurnAroundTime(struct process* pointer)
{
  float sumOfWaitingTime=0.0, sumOfTurnAroundTime = 0.0, sumOfBurstTime = 0.0, avgTurnAroundTime = 0.0;
  int count = 0;
  sumOfWaitingTime = sumOfWaitingTimeCalc(pointer);
  while(pointer != NULL)
  {
    count++;
    sumOfBurstTime = sumOfBurstTime + pointer->integerData[2];
    pointer = pointer->nextProcess;
  }
  sumOfTurnAroundTime = sumOfWaitingTime + sumOfBurstTime;
  avgTurnAroundTime = (sumOfTurnAroundTime/count);
  printf("Average Turn Around Time\t:\t%f\n",avgTurnAroundTime);
}

void calcAndPrintAverageWaitingTime(struct process* pointer)
{
  float sumOfWaitingTime = 0.0, avgWaitingTime = 0.0;
  int count = 0;
  sumOfWaitingTime = sumOfWaitingTimeCalc(pointer);
  while(pointer != NULL)
  {
    count++;
    pointer = pointer->nextProcess;
  }
  avgWaitingTime = (sumOfWaitingTime/count);
  printf("Average Waiting Time\t\t:\t%f\n",avgWaitingTime);
}

void fcfs_non_premptive()
{
  clearScreen();
  // First Come First Serve - Non Premptive
  struct process* pointer = NULL;
  if(startPointer != NULL)
  {
    // 1 - jobEntryTime
    pointer = makeListSort(1);
    if(pointer != NULL)
    {
      listAllProcesses(pointer);
      calcAndPrintAverageTurnAroundTime(pointer);
      calcAndPrintAverageWaitingTime(pointer);
      printf("\n");
    }
  }
  else
  {
    printf("Error: No processes found.\n\n");
  }
}

void sjf_non_premptive()
{
  clearScreen();
  // printf("sjf\n");
  struct process* pointer = NULL;
  if(startPointer != NULL)
  {
    // 1 - jobEntryTime
    pointer = makeListSort(2);
    if(pointer != NULL)
    {
      listAllProcesses(pointer);
      calcAndPrintAverageTurnAroundTime(pointer);
      calcAndPrintAverageWaitingTime(pointer);
      printf("\n");
    }
  }
  else
  {
    printf("Error: No processes found.\n\n");
  }
}

void round_robin_non_premptive()
{
  clearScreen();
  // printf("round robin\n");
  struct process* pointer = NULL;
  if(startPointer != NULL)
  {
    // 1 - jobEntryTime
    pointer = makeListSort(1);
    if(pointer != NULL)
    {
      listAllProcesses(pointer);
      calcAndPrintAverageTurnAroundTime(pointer);
      calcAndPrintAverageWaitingTime(pointer);
      printf("\n");
    }
  }
  else
  {
    printf("Error: No processes found.\n\n");
  }
}

void priority_non_premptive()
{
  clearScreen();
  // printf("priority\n");
  struct process* pointer = NULL;
  if(startPointer != NULL)
  {
    // 1 - jobEntryTime
    pointer = makeListSort(3);
    if(pointer != NULL)
    {
      listAllProcesses(pointer);
      calcAndPrintAverageTurnAroundTime(pointer);
      calcAndPrintAverageWaitingTime(pointer);
      printf("\n");
    }
  }
  else
  {
    printf("Error: No processes found.\n\n");
  }
}

void processDataManagerMenu()
{
  clearScreen();
  int innerChoice;
  do
  {
    printf("Non-preemptive CPU Scheduling Simulation - Process Data Manager\n\n1)\tAdd new process\n2)\tList all processes\n3)\tDelete a process\n4)\tBack to main menu\n5)\tExit\n\nPlease enter your choice:\n");
    scanf("%d",&innerChoice);
    switch(innerChoice)
    {
      case 1: newProcess();
      break;
      case 2: listAllProcesses(startPointer);
      break;
      case 3: deleteProcessPrompt();
      break;
      case 5: choice = 3;
      break;
      default: innerChoice = 4;
    }
  }while( (innerChoice>0) && (innerChoice<4));
}

void processSimulatorMenu()
{
  clearScreen();
  int innerChoice;
  do
  {
    printf("Non-preemptive CPU Scheduling Simulation - Process Simulation\n\n1)\tFCFS Scheduling Algorithm Simulation\n2)\tSJF Scheduling Algorithm Simulation\n3)\tRound Robin Scheduling Algorithm Simulation\n4)\tPriority Scheduling Algorithm Simulation\n5)\tBack to main menu\n6)\tExit\n\nPlease enter your choice:\n");
    scanf("%d",&innerChoice);
    switch(innerChoice)
    {
      case 1: fcfs_non_premptive();
      break;
      case 2: sjf_non_premptive();
      break;
      case 3: round_robin_non_premptive();
      break;
      case 4: priority_non_premptive();
      break;
      case 6: choice = 3;
      break;
      default: innerChoice = 5;
    }
  }while( (innerChoice>0) && (innerChoice<5));
}

int main()
{
  do
  {
    clearScreen();
    printf("Non-preemptive CPU Scheduling Simulation - Main Menu\n\n1)\tProcess Data Manager\n2)\tProcess Simulation\n3)\tExit\n\nPlease enter your choice:\n");
    scanf("%d",&choice);
    switch(choice)
    {
      case 1: processDataManagerMenu();
      break;
      case 2: processSimulatorMenu();
      break;
      default: choice = 3;
    }
  }while( (choice>0) && (choice<3));
  clearScreen();
  printf("Thanks for using Non-preemptive CPU Scheduling Simulation. Take care. Bye.\n");
  return 1;
}
