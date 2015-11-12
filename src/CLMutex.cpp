#include "CLMutex.h"

CLMutex :: CLMutex() {
  pthread_mutex_init(&m_Mutex, 0);
}

CLMutex :: ~CLMutex() {
  pthread_mutex_destroy(&m_Mutex);
}

CLStatus CLMutex :: Lock() {
 int rnt =  pthread_mutex_lock(&m_Mutex);
 if(rnt != 0)
   return CLStatus(0, 0);
}

CLStatus CLMutex :: Unlock() {
  int rnt = pthread_mutex_unlock(&m_Mutex);
  if(rnt != 0)
    return CLStatus(0, 0);
}
