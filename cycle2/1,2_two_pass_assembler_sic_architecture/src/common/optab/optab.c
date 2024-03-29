// Program for management of OPTAB related actions

#include <stdio.h>
#include <string.h>

// Header for management of OPTAB
#include "optab.h"

char opCode[3];

char* checkIfValidMnemonic(char* mnemonic, FILE* fp)
{
  // Search for the passed mnemonic in OPTAB
  int mnemonicFound = 0;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char *token;
  const char s[2] = " ";

  if((read = getline(&line, &len, fp)) != -1)
  {
    // printf("Retrieved line of length %zu :\n", read);
    // printf("%s", line);

    // deletion of \n at the end of line
    char *newline = strchr( line, '\n' );
    if ( newline )
    *newline = 0;

    // get first token
    token = strtok(line, s);

    // printf("%s %s\n", token, mnemonic);
    if(strcmp(token, mnemonic) == 0)
    {
      // mnemonic found
      mnemonicFound = 1;

      // obtain next token from the read line
      token = strtok(NULL, s);

      strcpy(opCode, token);
      return opCode;
    }

    while ((read = getline(&line, &len, fp)) != -1 && mnemonicFound == 0)
    {
      // printf("Retrieved line of length %zu :\n", read);
      // printf("%s", line);

      // deletion of \n at the end of line
      char *newline = strchr( line, '\n' );
      if ( newline )
      *newline = 0;

      // get first token
      token = strtok(line, s);
      if(strcmp(token, mnemonic) == 0)
      {
        // mnemonic found
        mnemonicFound = 1;

        // obtain next token from the read line
        token = strtok(NULL, s);

        strcpy(opCode, token);
        return opCode;
      }
    }

    if(mnemonicFound == 0)
    {
      // Invalid mnemonic
      strcpy(opCode, "GG");
      return opCode;
    }

    // Unexpected error
    printf("Error: Unexpected error occurred in optab.c\n");

    // Return error state
    strcpy(opCode, "HH");
    return opCode;
  }
  else
  {
    printf("Error: OPTAB is empty.\n");

    // returning error
    strcpy(opCode, "HH");
    return opCode;
  }
}

// function to return machine code when passed a valid mnemonic.
// if mnemonic is invalid returns GG
// if error occurs returns HH
char* returnMachineCodeForMnemonic(char* mnemonic)
{
  FILE *opfp;

  opfp = fopen("files/OPTAB", "r");

  // printf("%s\n", mnemonic);

  if(!opfp)
  {
    // OPTAB not found or is not accessible
    printf("Error: OPTAB not found or is inaccessible.\n");

    // return error occurred state to first_pass_process_line()
    strcpy(opCode, "HH");
    return opCode;
  }
  else
  {
    // OPTAB is accessible
    // printf("OPTAB is accessible.\n");

    // check if a valid mnemonic
    strcpy(opCode, checkIfValidMnemonic(mnemonic, opfp));
    if(strcmp(opCode, "GG") == 0)
    {
      // close connection to opfp
      fclose(opfp);

      // printf("%s\n", opCode);
      return opCode;
    }
    else
    {
      // close connection to opfp
      fclose(opfp);

      return opCode;
    }
  }
}
