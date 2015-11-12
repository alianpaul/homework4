#ifndef CL_EXECUTIVE_FUNC_FOR_MSG_LOOP_H
#define CL_EXECUTIVE_FUNC_FOR_MSG_LOOP_H

#include "CLStatus.h"
#include "CLExecutiveFunctionProvider.h"
#include "CLMessageLoopManager.h"


class CLExecutiveFunctionForMsgLoop : public  CLExecutiveFunctionProvider {
 public:
  CLExecutiveFunctionForMsgLoop(CLMessageLoopManager * pMsgLoopManager);
  ~CLExecutiveFunctionForMsgLoop();

  CLStatus RunExecutiveFunction(void* pContext = 0);

 private:
  CLMessageLoopManager * m_pMsgLoopManager;
  
};

#endif


