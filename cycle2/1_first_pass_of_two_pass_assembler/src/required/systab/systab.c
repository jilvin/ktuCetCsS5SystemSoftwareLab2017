#include <stdio.h>
#include <string.h>

#include "systab.h"

// return 1 if already present
// return 0 if not already present
// return -1 if error occurs
int checkIfExisitingLabel(char* label, FILE* sysfp)
{
  // Search for passed label in SYSTAB
  int labelFound = 0;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char *token;
  const char s[2] = " ";

  if((read = getline(&line, &len, sysfp)) != -1)
  {
    // printf("Retrieved line of length %zu :\n", read);
    // printf("%s", line);

    // deletion of \n at the end of line
    char *newline = strchr( line, '\n' );
    if ( newline )
    *newline = 0;

    // get first token
    token = strtok(line, s);

    // printf("%s %s\n", token, label);
    if(strcmp(token, label) == 0)
    {
      // label found
      labelFound = 1;

      // obtain next token from the read line
      token = strtok(NULL, s);

      return 1;
    }

    while ((read = getline(&line, &len, sysfp)) != -1 && labelFound == 0)
    {
      // printf("Retrieved line of length %zu :\n", read);
      // printf("%s", line);

      // deletion of \n at the end of line
      char *newline = strchr( line, '\n' );
      if ( newline )
      *newline = 0;

      // get first token
      token = strtok(line, s);
      if(strcmp(token, label) == 0)
      {
        // label found
        labelFound = 1;

        // obtain next token from the read line
        token = strtok(NULL, s);

        return 1;
      }
    }

    if(labelFound == 0)
    {
      // Label not found
      return 0;
    }

    // Unexpected error
    printf("Error: Unexpected error occurred in SYSTAB.c\n");

    // Return error state
    return -1;
  }
  else
  {
    printf("Error: SYSTAB is empty.\n");

    // returning error
    return -1;
  }
}

// return 1 on successful addition
// return 0 if already present
// return -1 if error occurs during execution
int checkAndSaveInSYSTAB(char* label, int locCtr)
{
  int checkIfExisitingLabelReturn;

  // printf("SYSTAB works!\n");
  // printf("%s %d\n", label, locCtr);

  FILE *sysfp;

  sysfp = fopen("files/temp/SYSTAB", "a+");

  if(!sysfp)
  {
    // SYSTAB not found or is not accessible
    printf("Error: SYSTAB not found or is inaccessible.\n");

    fprintf( sysfp, "%s %d\n", label, locCtr);

    return 1;
  }
  else
  {
    // SYSTAB is accessible
    // printf("SYSTAB is accessible.\n");

    // check if existing label
    checkIfExisitingLabelReturn = checkIfExisitingLabel(label, sysfp);
    // printf("%d\n", checkIfExisitingLabelReturn);

    if(checkIfExisitingLabelReturn == 1)
    {
      return 1;
    }
    else if(checkIfExisitingLabelReturn == 0)
    {
      return 0;
    }
    else if(checkIfExisitingLabelReturn == -1)
    {
      // Unexpected error.
      return -1;
    }
    else
    {
      // Unexpected error.
      return -1;
    }
  }
}

// delete SYSTAB if present
void deleteSYSTAB()
{
  int status;

  status = remove("files/temp/SYSTAB");

  if( status == 0 )
  {
    // printf("SYSTAB deleted successfully.\n");
  }
  else
  {
    printf("Error: Unable to delete SYSTAB.\n");
    perror("Error");
  }
}
