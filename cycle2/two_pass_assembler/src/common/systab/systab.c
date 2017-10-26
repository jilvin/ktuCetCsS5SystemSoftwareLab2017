#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "systab.h"

int array[2];

RETURN_ADDRESS_IF_EXISTING_LABEL_RETURN_OBJECT returnAddressIfExisitingLabel(char* label)
{
  RETURN_ADDRESS_IF_EXISTING_LABEL_RETURN_OBJECT returnStruct;
  char cwd[1024];
  FILE *sysfp;

  // open FILE pointer
  sysfp = fopen("files/temp/SYSTAB", "a+");

  if(!sysfp)
  {
    // get current working directory and store it in cwd char array.
    getcwd(cwd, sizeof(cwd));

    // SYSTAB not found or is not accessible
    printf("Error: SYSTAB not found or is inaccessible. Make sure %s/files/temp is accessible.\n", cwd);

    // fprintf( sysfp, "%s\n", label);

    // close FILE pointer
    // fclose(sysfp);

    // return error
    returnStruct.resultFlag = -1;
    returnStruct.line = NULL;

    return returnStruct;
  }
  else
  {
    // close FILE pointer
    fclose(sysfp);

    returnStruct.resultFlag = 1;
    returnStruct.line = NULL;

    return returnStruct;
  }
}

// return 1 if already present
// return 0 if not already present
// return -1 if error occurs
int checkIfExisitingLabel(char* label)
{
  // Search for passed label in SYSTAB
  char cwd[1024];
  int labelFound = 0;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char *token;
  const char s[2] = " ";

  FILE *sysfp;

  // open FILE pointer
  sysfp = fopen("files/temp/SYSTAB", "a+");

  if(!sysfp)
  {
    // get current working directory and store it in cwd char array.
    getcwd(cwd, sizeof(cwd));

    // SYSTAB not found or is not accessible
    printf("Error: SYSTAB not found or is inaccessible. Make sure %s/files/temp is accessible.\n", cwd);

    // fprintf( sysfp, "%s %d\n", label, locCtr);

    // close FILE pointer
    // fclose(sysfp);

    // return error
    return -1;
  }
  else
  {
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

        // printf("%s %s\n", token, label);
        if(strcmp(token, label) == 0)
        {
          // label found
          labelFound = 1;

          // close FILE pointer
          fclose(sysfp);

          return 1;
        }
      }

      if(labelFound == 0)
      {
        // close FILE pointer
        fclose(sysfp);

        // Label not found
        return 0;
      }

      // close FILE pointer
      fclose(sysfp);

      // Unexpected error
      printf("Error: Unexpected error occurred in SYSTAB.c\n");

      // Return error state
      return -1;
    }
    else
    {
      // printf("Error: SYSTAB is empty.\n");

      // close FILE pointer
      fclose(sysfp);

      // returning label not found
      return 0;
    }
  }
}

// [0]
// return 1 on successful addition
// return 0 if already present
// return -1 if error occurs during execution
// [1]
// return 1 if SYSTAB is created
int* checkAndSaveInSYSTAB(char* label, int locCtr, int SYSTAB_Created)
{
  int checkIfExisitingLabelReturn;
  char cwd[1024];

  // printf("SYSTAB works!\n");
  // printf("%s %d\n", label, locCtr);

  array[1] = SYSTAB_Created;

  FILE *sysfp;

  // open FILE pointer
  sysfp = fopen("files/temp/SYSTAB", "a+");

  if(!sysfp)
  {
    // get current working directory and store it in cwd char array.
    getcwd(cwd, sizeof(cwd));

    // SYSTAB not found or is not accessible
    printf("Error: SYSTAB not found or is inaccessible. Make sure %s/files/temp is accessible.\n", cwd);

    // fprintf( sysfp, "%s %d\n", label, locCtr);

    // close FILE pointer
    // fclose(sysfp);

    array[0] = 1;

    // Setting SYSTAB_Created
    array[1] = 1;
    return array;
  }
  else
  {
    // close FILE pointer
    fclose(sysfp);

    // SYSTAB is accessible
    // printf("SYSTAB is accessible.\n");

    // check if existing label
    checkIfExisitingLabelReturn = checkIfExisitingLabel(label);
    // printf("%d\n", checkIfExisitingLabelReturn);

    if(checkIfExisitingLabelReturn == 1)
    {
      // label found
      array[0] = 0;
      return array;
    }
    else if(checkIfExisitingLabelReturn == 0)
    {
      // open FILE pointer
      sysfp = fopen("files/temp/SYSTAB", "a+");

      // label not found
      fprintf( sysfp, "%s %d\n", label, locCtr);

      // close FILE pointer
      fclose(sysfp);
      array[0] = 1;
      return array;
    }
    else if(checkIfExisitingLabelReturn == -1)
    {
      // Error in checkIfExisitingLabel().
      array[0] = -1;
      return array;
    }
    else
    {
      // Unexpected error.
      printf("Error: Unexpected error.\n");
      array[0] = -1;
      return array;
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
