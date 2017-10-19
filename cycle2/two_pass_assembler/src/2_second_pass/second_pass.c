// Program to implement second pass of two-pass assembler for SIC Architecture.

#include <stdio.h>
#include <unistd.h>
#include <string.h>

// Header for management of OPTAB
#include "../common/optab/optab.h"

// Header for management of SYSTAB
#include "../common/systab/systab.h"

// Header for management of INTERMEDIATE
#include "../common/intermediate/intermediate.h"

// assemblerProgram
// 0 - START not found yet
// 1 - START found
// -1 - error in finding START on the first line excepting comment lines
// 2 - END found
int assemblerProgram = 0;
int startAddress = 0;
int lineCount=0;

// to obtain valid line from intermediate_read_line
// char *line = NULL;

// function to initate second pass of the assembler
void second_pass()
{
  int lineNo = 1;

  INTERMEDIATE_READ_LINE_RETURN obtainStruct;

  obtainStruct = intermediate_read_line(lineNo, assemblerProgram);

  while(obtainStruct.line != NULL)
  {
    printf("%s", obtainStruct.line);

    lineNo++;

    obtainStruct = intermediate_read_line(lineNo, assemblerProgram);
  }
}

int main(int argNo, char** args)
{
  // initialize second pass of the two-pass assembler
  second_pass();
}
