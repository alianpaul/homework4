#ifndef CL_THREAD_H
#define CL_THREAD_H

#include "CLStatus.h"
#include "CLExecutive.h"
#include "CLExecutiveFunctionProvider.h"
#include "CLEvent.h"
#include <pthread.h>

class CLThread : public CLExecutive{
 public:
  CLThread(CLExecutiveFunctionProvider * pExeFunProvider, bool bWaitForDeath); 
  ~CLThread();

  CLStatus Run(void *pContext = 0);
  CLStatus WaitForDeath();
  
 private:
  static void* StartFunctionOfThread(void * pThis);
  //used in the pthread_create function,must be static function.

 private:
  void* m_pContext;
  pthread_t m_ThreadID;
  bool m_bWaitForDeath;  //true, need to run WaitForDeath
  bool m_bThreadCreated; //ensure run only create a single thread
  CLEvent m_EventForDetached;
  CLEvent m_EventForChildRunning;
};

#endif
