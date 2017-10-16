// Program to implement second pass of two-pass assembler for SIC Architecture.

#include <stdio.h>
#include <unistd.h>

// Header for management of OPTAB
#include "../common/optab/optab.h"

// Header for management of SYSTAB
#include "../common/systab/systab.h"

// assemblerProgram
// 0 - START not found yet
// 1 - START found
// -1 - error in finding START on the first line excepting comment lines
// 2 - END found
int assemblerProgram = 0;
int startAddress = 0;
int lineCount=0;

// function to initate second pass of the assembler
void second_pass(FILE *fp, char* fileName)
{
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  if((read = getline(&line, &len, fp)) != -1)
  {
    // printf("Retrieved line of length %zu :\n", read);
    // printf("%s", line);

    // process the read line
    second_pass_process_line(line);

    while ((read = getline(&line, &len, fp)) != -1 && assemblerProgram != -1)
    {
      // printf("Retrieved line of length %zu :\n", read);
      // printf("%s", line);

      // process the read line
      second_pass_process_line(line);
    }

    // delete temporary files if present
    // deleteSYSTAB();

    if(assemblerProgram == -1)
    {
      // terminating assembly.
      printf("Assembling terminated.\n");
    }
    else if(assemblerProgram == 2)
    {
      // first pass completed successfully.
      printf("First pass completed successfully.\n");
    }
  }
  else
  {
    printf("%s is empty.\n", fileName);

    // terminating assembly.
    printf("Assembling terminated.\n");
  }
}

int main(int argNo, char** args)
{
  if(argNo == 2)
  {
    // check if right number of arguments are passed.
    FILE *fp;
    char cwd[1024];

    printf("Two-Pass Assembler for SIC Architecture\n");
    // printf("Accessing %s.\n", args[1]);
    fp = fopen(args[1], "r");

    // get current working directory and store it in cwd char array.
    getcwd(cwd, sizeof(cwd));

    if(!fp)
    {
      // file does not exist or is not accessible.

      // print error with details.
      perror("Error");

      // print file address as calculated.
      printf("%s/%s\n", cwd, args[1]);

      // terminating assembly.
      printf("Assembling terminated.\n");
    }
    else
    {
      // file exists and is accessbile.
      second_pass(fp, args[1]);

      // closing file pointer properly.
      fclose(fp);
    }
  }
  else
  {
    if(argNo == 1)
    {
      printf("Error: File name argument expected.\nAssembling terminated.\n");
    }
    else
    {
      printf("Error: Invalid number of arguments passed.\nAssembling terminated.\n");
    }
  }
}
