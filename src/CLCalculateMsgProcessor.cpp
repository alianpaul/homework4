#include "CLCalculateMsgProcessor.h"
#include "CLMsgMainControl.h"
#include <iostream>
#include "CLExecutiveNameServer.h"

CLCalculateMsgProcessor :: CLCalculateMsgProcessor(){}

CLCalculateMsgProcessor :: ~CLCalculateMsgProcessor(){}

CLStatus CLCalculateMsgProcessor :: Initialize(CLMessageLoopManager * pMsgLoopManager, void *pContext) {
  pMsgLoopManager->Register(ADD_MSG, CallBackForMessageLoop (&CLCalculateMsgProcessor :: On_ADD));

  return CLStatus(0, 0);
}

CLStatus CLCalculateMsgProcessor :: On_ADD(CLMessage * pMessage) {
  std::cout << "calculate: ADD_MSG Rcv" << std::endl;
  CLAddMsg * pAddMsg = (CLAddMsg *)pMessage;
  int * pBegin = pAddMsg->m_pnStart;
  int length = pAddMsg->m_nLength;
  int ans = 0;
  for(int i = 0; i < length; i++) {
    ans += *(pBegin++);
  }
  CLExecutiveNameServer :: PostExecutiveMessage("main", new CLResultMsg(ans));
  return CLStatus(QUIT_LOOP, 0);
}
