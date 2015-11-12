#ifndef CL_CONTROL_MSG_PROCESSOR_H
#define CL_CONTROL_MSG_PROCESSOR_H

#include "CLMessageObserver.h"
#include "CLStatus.h"
#include "CLMessage.h"
#include "CLMessageLoopManager.h"

class CLControlMsgProcessor : public CLMessageObserver {
 public:
  CLControlMsgProcessor();
  ~CLControlMsgProcessor();

  CLStatus Initialize(CLMessageLoopManager * pMsgLoopManager, void * pContext);

  CLStatus On_ADD(CLMessage * pMessage);

  CLStatus On_START(CLMessage * pMessage);

 private:
  int m_nThreadCnt;
  int * m_pnStartOfArray;
  int m_TotalLengthOfArray;
};

#endif
