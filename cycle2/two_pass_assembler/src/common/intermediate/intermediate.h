/* intermediate.h */
// The ifdef parts make multiple inclusion safe.
// So, optional, but will save you many headaches later
// when your include files start including other include files.
#ifndef __INTERMEDIATE_H__
#define __INTERMEDIATE_H__

// public struct for intermediate_read_line_return
typedef struct
{
  char* line;
  int assemblerProgram;
} INTERMEDIATE_READ_LINE_RETURN_OBJECT;

// function to read line from INTERMEDIATE. must resume from next unread line.
extern INTERMEDIATE_READ_LINE_RETURN_OBJECT intermediate_read_line(int lineNo, int assemblerProgram);

// function to save line to INTERMEDIATE
extern int intermediate_save_line(char* line);

#endif
/*__INTERMEDIATE_H__*/
