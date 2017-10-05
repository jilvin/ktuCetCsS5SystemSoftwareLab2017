// Program to implement first pass of two-pass assembler for SIC Architecture.

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int assemblerProgram = 0;
int startAddress = 0;
int locCtr;

// function to operate on the line read from first_pass()
void first_pass_process_line(char* line)
{
  int len, tokenNo=1;
  const char s[3] = "  ";
  char *token;

  // obtain length of line
  len = strlen(line);

  // check for empty line
  if(len == 1 && line[0] == '\n')
  {
    // printf("Empty line.\n");
  }
  else
  {
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

        if(assemblerProgram == 0)
        {
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
        printf("%s\n", line);
      }
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
    if(assemblerProgram == -1)
    {
      printf("Error: Not an assembly file for SIC.\n");

      // terminating assembly.
      printf("Assembling terminated.\n");
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
    printf("Accessing %s.\n", args[1]);
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
