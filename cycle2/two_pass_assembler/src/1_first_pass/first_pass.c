// Program to implement first pass of two-pass assembler for SIC Architecture.

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

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
int SYSTAB_Created = 0;
int locCtr;
int lineCount=0;

int getTotalNumberOfTokens(char* line, const char s[2])
{
  char *token;
  int tokenNo = 0;

  /* get the first token */
  token = strtok(line, s);

  /* walk through other tokens */
  while( token != NULL )
  {
    // printf("%s", token);
    token = strtok(NULL, s);
    tokenNo++;
  }

  // printf("%d\n", tokenNo);
  return tokenNo;
}

// function to operate on the line read from first_pass()
void first_pass_process_line(char* line)
{
  int len, tokenNo=1, checkAndSaveInSYSTAB_Flag, totalTokenCount;
  int* checkAndSaveInSYSTAB_Return;
  const char s[2] = " ";
  char *token;
  char tempLabel[20];
  char* tempOpCode = NULL;

  // obtain length of line
  len = strlen(line);

  char secondCopyLine[strlen(line) + 1];

  strcpy(secondCopyLine, line);

  lineCount++;

  // check for empty line
  if(len == 1 && line[0] == '\n')
  {
    // printf("Empty line.\n");
  }
  else
  {
    if(assemblerProgram != 2)
    {
      // END not found yet
      if(assemblerProgram == 0)
      {
        // check if comment
        if(line[0] == '.')
        {
          // printf("Comment line.\n");
        }
        else
        {
          // Check to find START first. If finding some other non-recognizable words first, terminate.

          /* get the first token */
          token = strtok(line, s);

          /* walk through other tokens */
          while( token != NULL )
          {
            if(tokenNo == 2)
            {
              // printf("%s\n", token);
              if(!strcmp(token, "START"))
              {
                // printf("gets here\n");
                assemblerProgram = 1;
              }
              else
              {
                assemblerProgram = -1;
              }
            }
            else if(tokenNo == 3 && assemblerProgram == 1)
            {
              // printf("%s\n", token);

              // get startAddress
              startAddress = atoi(token);

              // printf("START found\n");

              // Print startAddress
              // printf("%d\n", startAddress);

              // inititalizing locCtr
              locCtr = startAddress;
            }
            token = strtok(NULL, s);
            tokenNo++;
          }

          // save the line in INTERMEDIATE
          intermediate_save_line(line);
        }
      }
      else if(assemblerProgram == 1)
      {
        // check if comment
        if(line[0] == '.')
        {
          // printf("Comment line.\n");
        }
        else
        {
          // print read line with the current value of locCtr
          // printf("%d %s\n", locCtr, line);

          // get total number of tokens in the line
          totalTokenCount = getTotalNumberOfTokens(secondCopyLine, s);

          // printf("%d\n", totalTokenCount);

          /* get the first token */
          token = strtok(line, s);

          /* walk through other tokens */
          while( token != NULL )
          {
            if(totalTokenCount == 3)
            {
              // line with label
              if(tokenNo == 1)
              {
                strcpy(tempLabel, token);
              }
              else if(tokenNo == 2)
              {
                if(strcmp(token, "BYTE") == 0)
                {
                  // obtain next token from the read line
                  token = strtok(NULL, s);

                  // increment token number
                  tokenNo++;

                  if(token != NULL && tokenNo == 3)
                  {
                    if(strncmp(token, "C\'", 2) == 0)
                    {
                      // printf("Found character input in line.\n");
                    }
                    else if(strncmp(token, "X\'", 2) == 0)
                    {
                      // printf("Found input device id in line.\n");
                    }
                    locCtr = locCtr + 1;
                  }
                }
                else if(strcmp(token, "WORD") == 0)
                {
                  // obtain next token from the read line
                  token = strtok(NULL, s);

                  // increment token number
                  tokenNo++;

                  if(token != NULL && tokenNo == 3)
                  {
                    locCtr = locCtr + 3;
                  }
                }
                else if(strcmp(token, "RESW") == 0)
                {
                  // obtain next token from the read line
                  token = strtok(NULL, s);

                  // increment token number
                  tokenNo++;

                  if(token != NULL && tokenNo == 3)
                  {
                    locCtr = locCtr + (3 * atoi(token));
                  }
                }
                else if(strcmp(token, "RESB") == 0)
                {
                  // obtain next token from the read line
                  token = strtok(NULL, s);

                  // increment token number
                  tokenNo++;

                  if(token != NULL && tokenNo == 3)
                  {
                    locCtr = locCtr + atoi(token);
                  }
                }
                else
                {
                  // printf("%s\n", token);
                  tempOpCode = returnMachineCodeForMnemonic(token);

                  if(strcmp(tempOpCode, "GG") == 0)
                  {
                    // Invalid mnemonic found
                    printf("Error: Invalid mnemonic found on line %d\n", lineCount);
                    assemblerProgram = -1;
                  }
                  else if(strcmp(tempOpCode, "HH") == 0)
                  {
                    // Error encountered in returnMachineCodeForMnemonic()

                    // request to terminate assembly
                    assemblerProgram = -1;
                  }

                  // printf("Recieved opCode from returnMachineCodeForMnemonic() for %s is %s.\n", token, tempOpCode);

                  checkAndSaveInSYSTAB_Return = checkAndSaveInSYSTAB(tempLabel, locCtr, SYSTAB_Created);
                  checkAndSaveInSYSTAB_Flag = checkAndSaveInSYSTAB_Return[0];
                  SYSTAB_Created = checkAndSaveInSYSTAB_Return[1];
                  // printf("%d\n", checkAndSaveInSYSTAB_Flag);

                  if(checkAndSaveInSYSTAB_Flag == 1)
                  {
                    // label inserted successfully
                    // printf("Line %d: Label inserted successfully.\n", lineCount);
                  }
                  else if(checkAndSaveInSYSTAB_Flag == 0)
                  {
                    // label already exists
                    printf("Error: Line %d: Label already exists.\n", lineCount);

                    // request to terminate assembly
                    assemblerProgram = -1;
                  }
                  else if(checkAndSaveInSYSTAB_Flag == -1)
                  {
                    // error occurred in checkAndSaveInSYSTAB()
                    printf("Line %d: Error occurred in checkAndSaveInSYSTAB().\n", lineCount);

                    // request to terminate assembly
                    assemblerProgram = -1;
                  }
                  locCtr = locCtr+3;
                }
              }
            }
            else if(totalTokenCount == 2)
            {
              if(tokenNo == 1)
              {
                // line without label or direct value declaration
                // printf("Line %d: 2 tokens found.\n", lineCount);

                if(strcmp(token, "END") == 0)
                {
                  // END found
                  assemblerProgram = 2;
                }
                else
                {
                  // printf("%s\n", token);
                  tempOpCode = returnMachineCodeForMnemonic(token);

                  if(strcmp(tempOpCode, "GG") == 0)
                  {
                    // Invalid mnemonic found
                    printf("Error: Invalid mnemonic found on line %d\n", lineCount);
                    assemblerProgram = -1;
                  }
                  else if(strcmp(tempOpCode, "HH") == 0)
                  {
                    // Error encountered in returnMachineCodeForMnemonic()

                    // request to terminate assembly
                    assemblerProgram = -1;
                  }

                  // printf("Recieved opCode from returnMachineCodeForMnemonic() for %s is %s.\n", token, tempOpCode);

                  locCtr = locCtr+3;
                }
              }
            }
            else if(totalTokenCount == 1)
            {
              locCtr = locCtr+3;
            }

            // obtain next token from the read line
            token = strtok(NULL, s);

            // increment token number
            tokenNo++;
          }

          // save the line in INTERMEDIATE
          intermediate_save_line(line);
        }
      }
    }
    else
    {
      // END already found
      printf("Error: Non-empty lines found after END assembler directive.\n");

      // request to terminate assembly
      assemblerProgram = -1;
    }
  }
}

// function to initate first pass of the assembler
void first_pass(FILE *fp, char* fileName)
{
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  if((read = getline(&line, &len, fp)) != -1)
  {
    // printf("Retrieved line of length %zu :\n", read);
    // printf("%s", line);

    // process the read line
    first_pass_process_line(line);

    while ((read = getline(&line, &len, fp)) != -1 && assemblerProgram != -1)
    {
      // printf("Retrieved line of length %zu :\n", read);
      // printf("%s", line);

      // process the read line
      first_pass_process_line(line);
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

// obtain file name as command line argument.
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
      first_pass(fp, args[1]);

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
