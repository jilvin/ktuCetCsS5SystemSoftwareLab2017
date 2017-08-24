// 4) Simulate the following disk scheduling algorithms.
// a) FCFS
// b) SCAN
// c) C-SCAN

#include<stdio.h>
#include<stdlib.h>

struct track
{
  int trackID;
  struct track* nextTrack;
};

void clearScreen()
{
  printf("\033[H\033[J");
}

void FCFS()
{
  int totalTrackCount, requiredTrackCount, i, tempStore, distanceTravelled = 0, save = 0;
  struct track* pointer = NULL;
  struct track* startPointer = NULL;
  clearScreen();
  printf("FCFS Simulation\n\n");
  printf("Enter the total number of tracks available in the disk\n");
  scanf("%d", &totalTrackCount);
  printf("\nEnter number of tracks that you would like to seek\n");
  scanf("%d", &requiredTrackCount);
  printf("\nInput the track IDs in order\n");

  // tracks input section -- start
  i = 0;
  while(i < requiredTrackCount)
  {
    scanf("%d",&tempStore);
    if(tempStore>0 && tempStore<=totalTrackCount)
    {
      if(pointer != NULL)
      {
        pointer->nextTrack = malloc(sizeof(struct track));
        pointer = pointer->nextTrack;
      }
      else
      {
        pointer = malloc(sizeof(struct track));
        startPointer = pointer;
      }
      pointer->trackID = tempStore;
      pointer->nextTrack = NULL;
      i++;
    }
    else
    {
      printf("Invalid TrackID Inputted. Input again.\n");
    }
  }
  // tracks input section -- end

  // tracks traversal -- start
  pointer = startPointer;

  while(pointer != NULL)
  {
    if(save != 0)
    {
      distanceTravelled+= abs((pointer->trackID) - save);
    }
    save = pointer->trackID;
    pointer = pointer->nextTrack;
  }
  // tracks traversal -- end

  clearScreen();
  printf("Distance for complete traversal by the use of FCFS algorithm is: %d\n\n", distanceTravelled);
}

void SCAN()
{
  int totalTrackCount, requiredTrackCount;
  clearScreen();
  printf("SCAN Simulation\n\n");
  printf("Enter the total number of tracks available in the disk\n");
  scanf("%d", &totalTrackCount);
  printf("Enter number of tracks that you would like to seek\n");
  scanf("%d", &requiredTrackCount);
}

void CSCAN()
{
  int totalTrackCount, requiredTrackCount;
  clearScreen();
  printf("C-SCAN Simulation\n\n");
  printf("Enter the total number of tracks available in the disk\n");
  scanf("%d", &totalTrackCount);
  printf("Enter number of tracks that you would like to seek\n");
  scanf("%d", &requiredTrackCount);
}

int main()
{
  int choice;
  clearScreen();
  do
  {
    printf("Disk Scheduling Algorithms Simulator\n\n1)\tFCFS\n2)\tSCAN\n3)\tC-SCAN\n4)\tExit\n\nPlease enter your choice:\n");
    scanf("%d", &choice);
    switch(choice)
    {
      case 1: FCFS();
      break;
      case 2: SCAN();
      break;
      case 3: CSCAN();
      break;
      default: choice = 4;
    }
  }while(choice > 0 && choice < 4);
  clearScreen();
  printf("Thanks for using Disk Scheduling Algorithms Simulator. Bye.\n\n");
}
