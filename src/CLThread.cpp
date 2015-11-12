#include "CLThread.h"
#include <iostream>

CLThread :: CLThread(CLExecutiveFunctionProvider * pExeFunProvider, bool bWaitForDeath) : CLExecutive(pExeFunProvider), m_EventForDetached(false), m_EventForChildRunning(false) {
  m_pContext = 0;
  m_bThreadCreated = false;
  m_bWaitForDeath = bWaitForDeath;
}

CLThread :: ~CLThread() {

}

CLStatus CLThread :: Run(void * pContext) {
  
  if(m_bThreadCreated)
    return CLStatus(-1, 0);
  
  m_pContext = pContext;
  int rnt = pthread_create(&m_ThreadID, 0, StartFunctionOfThread, this);
  if(rnt != 0) {
    delete this;
    return CLStatus(-1, 0);
  }

  if(!m_bWaitForDeath) {
    /*need to detach before child thread terminated and 
     *delete CLThread object on the heap,in other word,when child terminated
     *and need to delete CLThread obj,child need to wait until father already detach the child
     */
    rnt = pthread_detach(m_ThreadID);
    if(rnt != 0){
      delete this;
      return CLStatus(-1, 0);
    }
    m_EventForDetached.Set();
  }
  
  m_bThreadCreated = true;
  /*make sure that when run return, new thread is already running
   *in other word,wait until new thread is running
   *if function StartFunctionOfThread runs,new thread is running
   */
  m_EventForChildRunning.Wait();
  return CLStatus(0, 0);
}

void* CLThread :: StartFunctionOfThread(void* pThis) {
  /*when two thread running 
   *CLThread obj pointer is pass to child
   *both father and child can access CLThread obj
   *so inside CLThread,we can use CLEvent member to do syn
   */
  CLThread * pCLThread = (CLThread *) pThis;
  pCLThread -> m_EventForChildRunning.Set();
  pCLThread -> m_pExeFunProvider -> RunExecutiveFunction(pCLThread -> m_pContext);
  
  /*child service finish*/
  
  if(!pCLThread -> m_bWaitForDeath) {
    pCLThread -> m_EventForDetached.Wait();
    delete pCLThread;
  }
 
  return 0;
}


CLStatus CLThread :: WaitForDeath() {
  
  if(!m_bThreadCreated)
    return CLStatus(-1, 0);

  if(!m_bWaitForDeath)
    return CLStatus(-1, 0);
  
  int rnt = pthread_join(m_ThreadID, 0);
  if(rnt != 0){
    std:: cout << "WaitForDeath error" << std::endl;
    return CLStatus(-1, 0);
  }

  delete this;
  
  return CLStatus(0, 0);
}
