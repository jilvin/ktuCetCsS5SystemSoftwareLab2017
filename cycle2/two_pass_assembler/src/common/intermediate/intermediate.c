#include <stdio.h>
#include <unistd.h>

int intermediate_save_line(char* line)
{
  // print recieved line
  printf("%s\n", line);

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
    fprintf(intermediatefp, "%s\n", line);

    // close FILE pointer
    fclose(intermediatefp);

    // return success
    return 1;
  }
}
