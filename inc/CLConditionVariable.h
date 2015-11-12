#ifndef CL_CONDITION_VARIABLE_H
#define CL_CONDITION_VARIABLE_H
#include "CLStatus.h"
#include <pthread.h>
#include "CLMutex.h"

class CLConditionVariable {

 public:
  CLConditionVariable();
  ~CLConditionVariable();

  CLStatus Wait(CLMutex * pMutex);
  CLStatus Wakeup();
  CLStatus WakeupAll();

 private:
  pthread_cond_t m_ConditionVariable;
};

#endif
