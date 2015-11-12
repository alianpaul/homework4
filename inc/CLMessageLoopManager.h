#ifndef CL_MESSAGE_LOOP_MANAGER_H
#define CL_MESSAGE_LOOP_MANAGER_H

#include "CLStatus.h"
#include "CLMessage.h"
#include "CLMessageObserver.h"
#include <map>

#define QUIT_LOOP 1000

class CLMessageObserver;

typedef CLStatus (CLMessageObserver :: *CallBackForMessageLoop)(CLMessage *);

class CLMessageLoopManager {
 public:
  CLMessageLoopManager(CLMessageObserver * pMsgObserver);
  virtual ~CLMessageLoopManager();
  virtual CLStatus EnterMessageLoop(void * pContext);
  virtual CLStatus Register(unsigned long MsgID, CallBackForMessageLoop pFunction);
 protected:
  /*depends on the implement of message queue
   */
  virtual CLStatus Initialize() = 0;
  virtual CLStatus Uninitialize() = 0;
  virtual CLMessage * WaitForMessage() = 0;
  virtual CLStatus DispatchMessage(CLMessage * pMessage);
  
  std::map<unsigned long, CallBackForMessageLoop> m_MsgMappingTable;

 private:
  CLMessageObserver * m_pMsgObserver;
  /*for register the member function in the observer*/
};

#endif

