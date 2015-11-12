#include "CLConditionVariable.h"

CLConditionVariable :: CLConditionVariable() {
  pthread_cond_init(&m_ConditionVariable, 0);
}

CLConditionVariable :: ~CLConditionVariable() {
  pthread_cond_destroy(&m_ConditionVariable);
}

CLStatus CLConditionVariable :: Wait(CLMutex * pMutex) {
  int rnt = pthread_cond_wait(&m_ConditionVariable, &(pMutex->m_Mutex));
  if(rnt != 0)
    return CLStatus(-1, 0);
  
  return CLStatus(0, 0);
}

CLStatus CLConditionVariable :: Wakeup() {
  int rnt = pthread_cond_signal(&m_ConditionVariable);
  if(rnt != 0)
    return CLStatus(-1, 0);

  return CLStatus(0, 0);
}

CLStatus CLConditionVariable :: WakeupAll() {
  int rnt = pthread_cond_broadcast(&m_ConditionVariable);
  if(rnt != 0)
    return CLStatus(-1, 0);

  return CLStatus(0, 0);
}
