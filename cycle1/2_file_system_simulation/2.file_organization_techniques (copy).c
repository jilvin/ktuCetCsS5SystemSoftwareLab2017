// 2) Simulate the following file organization techniques
// a) Single level directory b) Two level directory c) Hierarchical

#include <stdio.h>

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
