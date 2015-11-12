#include "CLControlMsgProcessor.h"
#include "CLMsgMainControl.h"
#include "CLThreadForMsgLoop.h"
#include <iostream>
#include <unistd.h>
#include "CLExecutiveNameServer.h"
#include "CLCalculateMsgProcessor.h"
#include <string>
#include <sstream>

CLControlMsgProcessor :: CLControlMsgProcessor() {

}

CLControlMsgProcessor :: ~CLControlMsgProcessor() {

}

CLStatus CLControlMsgProcessor :: Initialize(CLMessageLoopManager * pMsgLoopManager, void * pContext) {

  pMsgLoopManager->Register(ADD_MSG, CallBackForMessageLoop (&CLControlMsgProcessor :: On_ADD));
  pMsgLoopManager->Register(START_MSG, CallBackForMessageLoop (&CLControlMsgProcessor :: On_START));
  return CLStatus(0, 0);
}

CLStatus CLControlMsgProcessor :: On_ADD(CLMessage * pMessage) {
  std::cout << "control : ADD_MSG rcv" << std :: endl;
  
  CLAddMsg * pAddMsg = (CLAddMsg *)pMessage;
  m_nThreadCnt = pAddMsg->m_nLength/100;
  if(pAddMsg->m_nLength - (m_nThreadCnt*100) > 0){
    m_nThreadCnt += 1;
  }
  m_pnStartOfArray = pAddMsg->m_pnStart;
  m_TotalLengthOfArray =pAddMsg->m_nLength;
  
  CLThreadForMsgLoop * pCalculateThread = 0;
  for (int i = 0; i < m_nThreadCnt; i++) {
    std::ostringstream strname;
    strname << i;
    pCalculateThread = new CLThreadForMsgLoop(new CLCalculateMsgProcessor,strname.str().c_str(),true);
    pCalculateThread->Run();
  }
  
  std::cout << "control : send to main THRD_CNT" << std::endl;
  CLExecutiveNameServer :: PostExecutiveMessage("main", new CLThreadCntMsg(m_nThreadCnt));
  return CLStatus(ADD_MSG, 0);
}

CLStatus CLControlMsgProcessor :: On_START(CLMessage * pMessage) {
  std::cout << "control : START_MSG rcv" << std :: endl;
  /*the first 0  == nThreadCnt-2 thread length is 100*/
  int  * pnBegin = m_pnStartOfArray;
  int i = 0;
  
  for (i = 0; i < m_nThreadCnt - 1; i++) {
    std::ostringstream strname;
    strname << i;
    CLExecutiveNameServer :: PostExecutiveMessage(strname.str().c_str(), new CLAddMsg(pnBegin,100));
    pnBegin += 100;
  }

  std::ostringstream strname;
  strname << i;
  int nlastPartLength = m_TotalLengthOfArray - ((m_nThreadCnt - 1)*100);
  CLExecutiveNameServer :: PostExecutiveMessage(strname.str().c_str(), new CLAddMsg(pnBegin, nlastPartLength));
  
  return CLStatus(QUIT_LOOP, 0);
}
