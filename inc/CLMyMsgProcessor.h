#ifndef CL_MSG_PROCESSOR_H
#define CL_MSG_PROCESSOR_H

#include "CLStatus.h"
#include "CLMessage.h"
#include "CLMessageObserver.h"
#include "CLMessageLoopManager.h"

class CLMyMsgProcessor : public CLMessageObserver {
 public:
  CLMyMsgProcessor();
  ~CLMyMsgProcessor();

  CLStatus Initialize(CLMessageLoopManager * pMsgLoopManager, void * pContext);

  CLStatus On_Add(CLMessage * pMessage);

  CLStatus On_Quit(CLMessage * pMessage);
  
};

#endif
