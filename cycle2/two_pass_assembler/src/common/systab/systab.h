/* systab.h */
// The ifdef parts make multiple inclusion safe.
// So, optional, but will save you many headaches later
// when your include files start including other include files.
#ifndef __SYSTAB_H__
#define __SYSTAB_H__

// public struct for returnAddressIfExisitingLabel()
typedef struct
{
  int resultFlag;
  char* line; // for storing address
} RETURN_ADDRESS_IF_EXISTING_LABEL_RETURN_OBJECT;

extern RETURN_ADDRESS_IF_EXISTING_LABEL_RETURN_OBJECT returnAddressIfExisitingLabel(char* label);

extern int* checkAndSaveInSYSTAB(char* label, int locCtr, int SYSTAB_Created);

extern void deleteSYSTAB();

#endif
/*__SYSTAB_H__*/
