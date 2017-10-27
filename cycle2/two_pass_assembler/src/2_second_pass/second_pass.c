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

// 1 - successfull save to file
// -1 - error occurred during saveOutfile
int saveOutfile(char* line)
{
  FILE *outfilefp;
  char cwd[1024];

  // open FILE pointer
  outfilefp = fopen("OUTFILE", "a+");

  if(!outfilefp)
  {
    // get current working directory and store it in cwd char array.
    getcwd(cwd, sizeof(cwd));

    // SYSTAB not found or is not accessible
    printf("Error: OUTFILE not found or is inaccessible. Make sure %s is accessible.\n", cwd);

    // return error
    return -1;
  }
  else
  {
    // appending line on to OUTFILE
    fprintf(outfilefp, "%s\n", line);

    // close FILE pointer
    fclose(outfilefp);

    // return success
    return 1;
  }
}

// obtain number of tokens present
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

// function to operate on the line read from second_pass()
void second_pass_process_line(char* line, int lineNo)
{
  RETURN_ADDRESS_IF_EXISTING_LABEL_RETURN_OBJECT returnedObject;
  int len, tokenNo=1, totalTokenCount, saveOutfileReturn;
  const char s[2] = " ";
  char *token, *lastToken;
  char* tempOpCode = NULL;
  char outLine[7];

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
        // START not found yet
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
            token = strtok(NULL, s);
            tokenNo++;
          }
        }
      }
      else if(assemblerProgram == 1)
      {
        // START has already been found
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

                      // printf("%s", token);

                      char* p;

                      p = strchr(token, '\'');

                      sprintf(outLine, "%02X%02X%02X", p[1], p[2], p[3]);

                      // save to outfile
                      saveOutfileReturn = saveOutfile(outLine);

                      if(saveOutfileReturn == 1)
                      {
                        // printf("%d\n", saveOutfileReturn);
                      }
                      else
                      {
                        //Error in saveOutfile()

                        // request to terminate assembly
                        assemblerProgram = -1;
                      }
                    }
                    else if(strncmp(token, "X\'", 2) == 0)
                    {
                      // printf("Found input device id in line.\n");

                      char* p;
                      int i=1, j=0;

                      p = strchr(token, '\'');

                      while(p[i] != '\'' && j<7)
                      {
                        outLine[j] = p[i];
                        i++;
                        j++;
                      }

                      // save to outfile
                      saveOutfileReturn = saveOutfile(outLine);
                    }
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
                    int value = atoi(token);

                    sprintf(outLine, "%06X", value);

                    // save to outfile
                    saveOutfileReturn = saveOutfile(outLine);

                    if(saveOutfileReturn == 1)
                    {
                      // printf("%d\n", saveOutfileReturn);
                    }
                    else
                    {
                      //Error in saveOutfile()

                      // request to terminate assembly
                      assemblerProgram = -1;
                    }
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
                  }
                }
                else
                {
                  // obtain next token from the read line
                  lastToken = strtok(NULL, s);

                  tempOpCode = returnMachineCodeForMnemonic(token);
                  // printf("%s %s\n", token, tempOpCode);

                  if(strcmp(tempOpCode, "GG") == 0)
                  {
                    // Invalid mnemonic found
                    printf("Error: Invalid mnemonic found on line %d\n", lineNo);
                    assemblerProgram = -1;
                  }
                  else if(strcmp(tempOpCode, "HH") == 0)
                  {
                    // Error encountered in returnMachineCodeForMnemonic()

                    // request to terminate assembly
                    assemblerProgram = -1;
                  }
                  else
                  {
                    // valid mnemonic found
                    // printf("valid mnemonic found\n");

                    // strtok placed at top due to issues with returnMachineCodeForMnemonic()
                    token = lastToken;

                    // increment token number
                    tokenNo++;

                    // printf("%s %d\n", token, tokenNo);

                    if(token != NULL && tokenNo == 3)
                    {
                      // deletion of \n at the end of line
                      char *newtoken = strchr( token, '\n' );
                      if ( newtoken )
                      *newtoken = 0;

                      // printf("prints token: %s\n", token);

                      returnedObject = returnAddressIfExisitingLabel(token);
                      // printf("label %s. resultFlag obtained is %d. address obtained is %s.\n", token, returnedObject.resultFlag, returnedObject.line);

                      if(returnedObject.line != NULL)
                      {
                        if(returnedObject.resultFlag != -1)
                        {
                          strcpy(outLine, tempOpCode);
                          strcat(outLine, returnedObject.line);

                          // save to outfile
                          saveOutfileReturn = saveOutfile(outLine);

                          if(saveOutfileReturn == 1)
                          {
                            // printf("%d\n", saveOutfileReturn);
                          }
                          else
                          {
                            //Error in saveOutfile()

                            // request to terminate assembly
                            assemblerProgram = -1;
                          }
                        }
                        else
                        {
                          // request to terminate assembly
                          assemblerProgram = -1;
                        }
                      }
                      else
                      {
                        printf("Error: NULL address recieved from returnAddressIfExisitingLabel().\n");

                        // request to terminate assembly
                        assemblerProgram = -1;
                      }
                    }
                  }
                }
              }
            }
            else if(totalTokenCount == 2)
            {
              if(tokenNo == 1)
              {
                // line without label or direct value declaration
                // printf("Line %d: 2 tokens found.\n", lineNo);

                if(strcmp(token, "END") == 0)
                {
                  // END found
                  assemblerProgram = 2;
                }
                else
                {
                  // obtain next token from the read line
                  lastToken = strtok(NULL, s);

                  tempOpCode = returnMachineCodeForMnemonic(token);
                  // printf("%s %s\n", token, tempOpCode);

                  if(strcmp(tempOpCode, "GG") == 0)
                  {
                    // Invalid mnemonic found
                    printf("Error: Invalid mnemonic found on line %d\n", lineNo);
                    assemblerProgram = -1;
                  }
                  else if(strcmp(tempOpCode, "HH") == 0)
                  {
                    // Error encountered in returnMachineCodeForMnemonic()

                    // request to terminate assembly
                    assemblerProgram = -1;
                  }
                  else
                  {
                    // valid mnemonic found
                    // printf("valid mnemonic found\n");

                    // strtok placed at top due to issues with returnMachineCodeForMnemonic()
                    token = lastToken;

                    // increment token number
                    tokenNo++;

                    // printf("%s %d\n", token, tokenNo);

                    if(token != NULL && tokenNo == 2)
                    {
                      // deletion of \n at the end of line
                      char *newtoken = strchr( token, '\n' );
                      if ( newtoken )
                      *newtoken = 0;

                      // printf("prints token: %s\n", token);

                      returnedObject = returnAddressIfExisitingLabel(token);
                      // printf("label %s. resultFlag obtained is %d. address obtained is %s.\n", token, returnedObject.resultFlag, returnedObject.line);

                      if(returnedObject.line != NULL)
                      {
                        if(returnedObject.resultFlag != -1)
                        {
                          strcpy(outLine, tempOpCode);
                          strcat(outLine, returnedObject.line);

                          // save to outfile
                          saveOutfileReturn = saveOutfile(outLine);

                          if(saveOutfileReturn == 1)
                          {
                            // printf("%d\n", saveOutfileReturn);
                          }
                          else
                          {
                            //Error in saveOutfile()

                            // request to terminate assembly
                            assemblerProgram = -1;
                          }
                        }
                        else
                        {
                          // request to terminate assembly
                          assemblerProgram = -1;
                        }
                      }
                      else
                      {
                        printf("Error: NULL address recieved from returnAddressIfExisitingLabel().\n");

                        // request to terminate assembly
                        assemblerProgram = -1;
                      }
                    }
                  }
                }
              }
            }
            else if(totalTokenCount == 1)
            {
              if(tokenNo == 1)
              {
                // deletion of \n at the end of line
                char *newtoken = strchr( token, '\n' );
                if ( newtoken )
                *newtoken = 0;

                tempOpCode = returnMachineCodeForMnemonic(token);
                // printf("%s %s\n", token, tempOpCode);

                if(strcmp(tempOpCode, "GG") == 0)
                {
                  // Invalid mnemonic found
                  printf("Error: Invalid mnemonic found on line %d\n", lineNo);
                  assemblerProgram = -1;
                }
                else if(strcmp(tempOpCode, "HH") == 0)
                {
                  // Error encountered in returnMachineCodeForMnemonic()

                  // request to terminate assembly
                  assemblerProgram = -1;
                }
                else
                {
                  // valid mnemonic found
                  // printf("valid mnemonic found\n");

                  strcpy(outLine, tempOpCode);
                  strcat(outLine, "0000");

                  // save to outfile
                  saveOutfileReturn = saveOutfile(outLine);

                  if(saveOutfileReturn == 1)
                  {
                    // printf("%d\n", saveOutfileReturn);
                  }
                  else
                  {
                    //Error in saveOutfile()

                    // request to terminate assembly
                    assemblerProgram = -1;
                  }
                }
              }
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

  INTERMEDIATE_READ_LINE_RETURN_OBJECT obtainStruct;

  obtainStruct = intermediate_read_line(lineNo, assemblerProgram);

  while(obtainStruct.line != NULL && assemblerProgram != -1)
  {
    // printf("%s", obtainStruct.line);

    second_pass_process_line(obtainStruct.line, lineNo);

    lineNo++;

    obtainStruct = intermediate_read_line(lineNo, assemblerProgram);
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
    // second pass completed successfully.
    printf("Second pass completed successfully.\n");
  }
}

int main(int argNo, char** args)
{
  // initialize second pass of the two-pass assembler
  second_pass();
}
