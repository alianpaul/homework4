#ifndef CL_CRITICAL_SECTION_H
#define CL_CRITICAL_SECTION_H

#include "CLMutex.h"

class CLCriticalSection {
 public:
  CLCriticalSection(CLMutex *pMutex);
  ~CLCriticalSection();

 private:
  CLMutex * m_pMutex;
};

#endif
