#ifndef CL_EVENT_H
#define CL_EVENT_H

#include "CLStatus.h"
#include "CLMutex.h"
#include "CLConditionVariable.h"

class CLEvent{
 public:
  CLEvent(bool bSemaphore);
  ~CLEvent();
  
  CLStatus Set(); //event happens
  CLStatus Wait(); //wait for the event to happen
  
 private:
  int m_Flag;
  bool m_bSemaphore; //true, m_Flag represents the time cnt the event happens
  CLMutex m_Mutex;
  CLConditionVariable m_Condition;
};

#endif
