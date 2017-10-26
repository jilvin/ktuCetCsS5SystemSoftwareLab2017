#include <stdio.h>
#include <unistd.h>

// Header for management of INTERMEDIATE
#include "intermediate.h"

// function to read line from INTERMEDIATE. must resume from next unread line.
INTERMEDIATE_READ_LINE_RETURN_OBJECT intermediate_read_line(int lineNo, int assemblerProgram)
{
  FILE *intermediatefp;
  char cwd[1024];
  int readFlag = 0, lineCounter = 0;
  size_t len = 0;
  ssize_t read;
  char* line = NULL;

  INTERMEDIATE_READ_LINE_RETURN_OBJECT returnStruct;

  // open FILE pointer
  intermediatefp = fopen("files/temp/INTERMEDIATE", "a+");

  if(!intermediatefp)
  {
    // get current working directory and store it in cwd char array.
    getcwd(cwd, sizeof(cwd));

    // SYSTAB not found or is not accessible
    printf("Error: INTERMEDIATE not found or is inaccessible. Make sure %s/files/temp is accessible.\n", cwd);

    // return error
    returnStruct.line = NULL;
    returnStruct.assemblerProgram = -1;

    return returnStruct;
  }
  else
  {
    if((read = getline(&line, &len, intermediatefp)) != -1 && readFlag == 0)
    {
      lineCounter++;

      // printf("%d %s\n", lineCounter, line);

      if(lineNo == lineCounter)
      {
        // printf("%d %s\n", lineCounter, line);

        // read line from INTERMEDIATE
        readFlag = 1;
      }
      else
      {
        while(readFlag == 0 && (read = getline(&line, &len, intermediatefp)) != -1)
        {
          lineCounter++;

          // printf("%d %s\n", lineCounter, line);

          if(lineNo == lineCounter)
          {
            // printf("%d %s\n", lineCounter, line);

            // read line from INTERMEDIATE
            readFlag = 1;
          }
        }
      }
    }
    else
    {
      printf("Error: Empty INTERMEDIATE file.\n");
    }

    // close FILE pointer
    fclose(intermediatefp);

    if(readFlag == 1)
    {
      returnStruct.line = line;
      returnStruct.assemblerProgram = assemblerProgram;

      return returnStruct;
    }
    else
    {
      returnStruct.line = NULL;
      returnStruct.assemblerProgram = -1;

      return returnStruct;
    }
  }
}

// function to save line to INTERMEDIATE
int intermediate_save_line(char* line)
{
  // print recieved line
  // printf("%s", line);

  FILE *intermediatefp;
  char cwd[1024];

  // open FILE pointer
  intermediatefp = fopen("files/temp/INTERMEDIATE", "a+");

  if(!intermediatefp)
  {
    // get current working directory and store it in cwd char array.
    getcwd(cwd, sizeof(cwd));

    // SYSTAB not found or is not accessible
    printf("Error: INTERMEDIATE not found or is inaccessible. Make sure %s/files/temp is accessible.\n", cwd);

    // return error
    return -1;
  }
  else
  {
    // appending line on to INTERMEDIATE
    fprintf(intermediatefp, "%s", line);

    // close FILE pointer
    fclose(intermediatefp);

    // return success
    return 1;
  }
}
