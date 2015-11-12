/*ThreadForMsgLoop need to ensure that Thread name and ExecutiveCommunication has been register
 *in the name server when run returns
 *
 *the thread is for msg loop ,so the ExecutiveFunctionProvider must be CLExecutiveFunctionForMsgLoo
 *p, and assume CLMessageLoopManager be CLMsgLoopManagerForQueueBySTLList
 *so when initialize the CLThreadForMsgLoop, we need to provide MsgObserver and thread name only
 */

#ifndef CL_THREAD_FOR_MSG_LOOP_H
#define CL_THREAD_FOR_MSG_LOOP_H

#include "CLMessageObserver.h"
#include "CLThread.h"

class CLThreadForMsgLoop {
 public:
  CLThreadForMsgLoop(CLMessageObserver * pMsgObserver, const char * pstrThreadName, bool bWaitForDeath);

  virtual ~CLThreadForMsgLoop();

  CLStatus Run();

 private:
  CLThread * m_pThread;
  bool m_bWaitForDeath;
};

#endif
