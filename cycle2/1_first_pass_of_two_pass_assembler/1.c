// Program to implement first pass of two-pass assembler for SIC Architecture.

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int assemblerProgram = 0;

// function to operate on the line read from first_pass()
void first_pass_process_line(char* line)
{
  int len;

  // obtain length of line
  len = strlen(line);

  // check for empty line
  if(len == 1 && line[0] == '\n')
  {
    printf("Empty line.\n");
  }
  else
  {
    if(assemblerProgram == 0)
    {
      // Check to find START first. If finding some other non-recognizable words first, terminate.

      // check if comment
      if(line[0] == '.')
      {
        printf("Comment line.\n");
      }
    }
    else
    {
      // START found
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
    printf("%s", line);

    // process the read line
    first_pass_process_line(line);

    while ((read = getline(&line, &len, fp)) != -1)
    {
      // printf("Retrieved line of length %zu :\n", read);
      printf("%s", line);

      // process the read line
      first_pass_process_line(line);
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
