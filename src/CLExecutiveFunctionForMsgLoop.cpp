#include "CLExecutiveFunctionForMsgLoop.h"
#include <iostream>
#include <unistd.h>

CLExecutiveFunctionForMsgLoop :: CLExecutiveFunctionForMsgLoop(CLMessageLoopManager * pMsgLoopManager){
  m_pMsgLoopManager = pMsgLoopManager;
}

CLExecutiveFunctionForMsgLoop :: ~CLExecutiveFunctionForMsgLoop(){
  delete m_pMsgLoopManager;
}

CLStatus CLExecutiveFunctionForMsgLoop ::  RunExecutiveFunction(void* pContext) {
  CLStatus s = m_pMsgLoopManager->EnterMessageLoop(pContext);
  return s;
}
