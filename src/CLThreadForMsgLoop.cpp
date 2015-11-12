#include "CLMsgLoopManagerForQueueBySTLList.h"
#include "CLEvent.h"
#include "CLMessageObserver.h"
#include "CLThreadForMsgLoop.h"
#include "CLExecutiveFunctionForMsgLoop.h"

CLThreadForMsgLoop :: CLThreadForMsgLoop(CLMessageObserver * pMsgObserver, const char * pstrThreadName, bool bWaitForDeath) {
  m_bWaitForDeath = bWaitForDeath;
  m_pThread = new CLThread(new CLExecutiveFunctionForMsgLoop(new CLMsgLoopManagerForQueueBySTLList(pMsgObserver, pstrThreadName)), bWaitForDeath);
}

CLThreadForMsgLoop :: ~ CLThreadForMsgLoop() {
  if(m_bWaitForDeath && m_pThread != 0)
    m_pThread->WaitForDeath();
}

/*when Run of CLThread invoked, the new ExecutiveCommunication is registered in the 
 *Name Server.but we need to ensure that when Run returns in CLThreadForMsgLoop,the Exe
 *cutiveCommunication is registered.so we can wrap CLThread' Run with an Event;
 */

CLStatus CLThreadForMsgLoop :: Run() {
  CLEvent event(false);

  m_pThread->Run(&event);

  return event.Wait();
}
