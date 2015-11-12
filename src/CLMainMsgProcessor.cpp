#include "CLMainMsgProcessor.h"
#include "CLMsgMainControl.h"
#include "CLMessageLoopManager.h"
#include <iostream>
#include <unistd.h>
#include "CLExecutiveNameServer.h"

CLMainMsgProcessor :: CLMainMsgProcessor(){
  m_nRecvAnswerCnt = 0;
  m_nTotalAnswerCnt = 0;
}

CLMainMsgProcessor :: ~CLMainMsgProcessor(){

}

CLStatus CLMainMsgProcessor :: Initialize(CLMessageLoopManager * pMsgLoopManager, void* pContext) {
  pMsgLoopManager->Register(THRD_CNT_MSG, (CallBackForMessageLoop)(&CLMainMsgProcessor::On_THRD_CNT));
  pMsgLoopManager->Register(RESULT_MSG, (CallBackForMessageLoop)(&CLMainMsgProcessor::On_RESULT ));
  return CLStatus(0, 0);
}

CLStatus CLMainMsgProcessor :: On_THRD_CNT(CLMessage * pMessage) {
  std::cout << "main: THRD_CNT_MSG Rcv" << std::endl;
  CLThreadCntMsg * pThreadCntMsg = (CLThreadCntMsg *)pMessage;
  m_nTotalAnswerCnt = pThreadCntMsg->m_cnThreadCnt;
  std::cout << "Total answer cnt " << m_nTotalAnswerCnt << std :: endl;
  
  std::cout << "main: send to control START_MSG" << std::endl;
  CLExecutiveNameServer :: PostExecutiveMessage("control", new CLStartMsg);
  return CLStatus(0, 0);
}



CLStatus CLMainMsgProcessor :: On_RESULT(CLMessage * pMessage) {
  std::cout << "main: RESULT_MSG Rcv" << std::endl;
  CLResultMsg * pResult = (CLResultMsg *) pMessage;
  std::cout << pResult->m_cnResult << std::endl;
  if(++m_nRecvAnswerCnt == m_nTotalAnswerCnt)
    return CLStatus(QUIT_LOOP, 0);
  return CLStatus(0, 0);
}
