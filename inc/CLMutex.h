#ifndef CL_MUTEX_H
#define CL_MUTEX_H

#include "CLStatus.h"
#include <pthread.h>


class CLMutex{
 public:
  CLMutex();
  virtual ~CLMutex();

  CLStatus Lock();
  CLStatus Unlock();

 private:
  pthread_mutex_t m_Mutex;

 friend class CLConditionVariable;
  
};

#endif
