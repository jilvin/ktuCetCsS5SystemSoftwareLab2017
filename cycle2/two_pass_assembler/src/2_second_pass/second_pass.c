// Program to implement second pass of two-pass assembler for SIC Architecture.

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
int lineCount=0;

// to obtain valid line from intermediate_read_line
// char *line = NULL;

// function to operate on the line read from second_pass()
void second_pass_process_line(char* line, int lineNo)
{
  int len, tokenNo=1, totalTokenCount;
  const char s[2] = " ";
  char *token;

  // obtain length of line
  len = strlen(line);

  char secondCopyLine[strlen(line) + 1];

  strcpy(secondCopyLine, line);

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

          // save the line in INTERMEDIATE
          intermediate_save_line(line);

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
            }
            token = strtok(NULL, s);
            tokenNo++;
          }
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

          // save the line in INTERMEDIATE
          intermediate_save_line(line);

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

// function to initate second pass of the assembler
void second_pass()
{
  int lineNo = 1;

  INTERMEDIATE_READ_LINE_RETURN obtainStruct;

  obtainStruct = intermediate_read_line(lineNo, assemblerProgram);

  while(obtainStruct.line != NULL)
  {
    printf("%s", obtainStruct.line);

    second_pass_process_line(obtainStruct.line, lineNo);

    lineNo++;

    obtainStruct = intermediate_read_line(lineNo, assemblerProgram);
  }
}

int main(int argNo, char** args)
{
  // initialize second pass of the two-pass assembler
  second_pass();
}
