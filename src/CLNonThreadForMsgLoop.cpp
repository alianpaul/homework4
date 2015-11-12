#include "CLNonThreadForMsgLoop.h"
#include "CLExecutiveFunctionForMsgLoop.h"
#include "CLMsgLoopManagerForQueueBySTLList.h"

CLNonThreadForMsgLoop :: CLNonThreadForMsgLoop(CLMessageObserver * pMsgObserver, const char * pstrThreadName) {
  m_pFunctionProvider = new CLExecutiveFunctionForMsgLoop(new CLMsgLoopManagerForQueueBySTLList(pMsgObserver, pstrThreadName));
}

CLNonThreadForMsgLoop :: ~CLNonThreadForMsgLoop() {
  delete m_pFunctionProvider;
}

CLStatus CLNonThreadForMsgLoop :: Run() {
  return m_pFunctionProvider->RunExecutiveFunction(0);
}
