#ifndef CL_CALCULATE_MSG_PROCESSOR_H
#define CL_CALCULATE_MSG_PROCESSOR_H

#include "CLMessageObserver.h"
#include "CLStatus.h"
#include "CLMessage.h"
#include "CLMessageLoopManager.h"

class CLCalculateMsgProcessor : public CLMessageObserver {
 public:
  CLCalculateMsgProcessor();
  ~CLCalculateMsgProcessor();

  CLStatus Initialize(CLMessageLoopManager * pMsgLoopManager, void *pContext);

  CLStatus On_ADD(CLMessage * pMessage);
};

#endif
