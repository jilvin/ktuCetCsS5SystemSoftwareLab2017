// 1) Simulate the following non-preemptive CPU scheduling algorithms to find turnaround time and waiting time.
// a) FCFS b) SJF c) Round Robin (pre-emptive) d) Priority

#include <stdio.h>
#include <stdlib.h>

int choice = 3;

struct process
{
  int processID;
  char processName[32];
  int jobEntryTime;
  int jobBurstTime; //burstTime
  int priority;
  struct process* nextProcess;
};

struct process* startPointer=NULL;

void clearScreen()
{
  printf("\033[H\033[J");
}

void listProcess(struct process* pointer)
{
  printf("processID\t:\t%d\nprocessName\t:\t%s\npriority\t:\t%d\njobEntryTime\t:\t%d\njobBurstTime\t:\t%d\n\n",pointer->processID,pointer->processName,pointer->priority,pointer->jobEntryTime,pointer->jobBurstTime);
}

void listAllProcesses()
{
  clearScreen();
  struct process* pointer = startPointer;
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

void deleteProcessPrompt()
{
  clearScreen();
  int processID, processFound=0;
  struct process* pointer = startPointer;
  struct process* pointerBack = NULL;
  if(pointer!=NULL)
  {
    printf("Enter processID of the process to be deleted:\n");
    scanf("%d",&processID);
    if(pointer->nextProcess == NULL)
    {
      if(pointer->processID == processID)
      {
        processFound = 1;
      }
    }
    else
    {
      while(pointer->nextProcess!=NULL && processFound == 0)
      {
        if(pointer->processID == processID)
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
        if(pointer->processID == processID)
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
      printf("Process with processID %d deleted successfully.\n\n", processID);
    }
    else if(processFound == 0)
    {
      // clearScreen();
      printf("Error: Process with processID %d not found.\n\n",processID);
    }
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
  if(pointer != NULL && pointer->processID == 1)
  {
    while(pointer->nextProcess != NULL && savePointer == NULL)
    {
      if(pointer->processID+1 == pointer->nextProcess->processID)
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
    processNo = pointer->processID;
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
  pointer->processID = ++processNo;
  printf("Enter processName:\n");
  scanf("%s",&(pointer->processName[0]));
  printf("Enter priority:\n");
  scanf("%d",&(pointer->priority));
  printf("Enter jobEntryTime:\n");
  scanf("%d",&(pointer->jobEntryTime));
  printf("Enter jobBurstTime:\n");
  scanf("%d",&(pointer->jobBurstTime));
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

void fcfs_non_premptive()
{
  clearScreen();
  printf("fcfs\n");
}

void sjf_non_premptive()
{
  clearScreen();
}

void round_robin_non_premptive()
{
  clearScreen();
}

void priority_non_premptive()
{
  clearScreen();
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
      case 2: listAllProcesses();
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
