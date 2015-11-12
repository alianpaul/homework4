#include "CLMsgLoopManagerForQueueBySTLList.h"
#include "CLExecutiveNameServer.h"
#include <iostream>
#include "CLThreadCommunicationForQueueBySTLList.h"

CLMsgLoopManagerForQueueBySTLList :: CLMsgLoopManagerForQueueBySTLList(CLMessageObserver * pMsgObserver,const char* pstrThreadName ) : CLMessageLoopManager(pMsgObserver) {
  m_pMsgQueue = new CLMessageQueueBySTLList;
  m_strThreadName = pstrThreadName;
}

CLMsgLoopManagerForQueueBySTLList :: ~CLMsgLoopManagerForQueueBySTLList(){
  
}

CLStatus CLMsgLoopManagerForQueueBySTLList ::  Initialize() {
  CLExecutiveNameServer * pNameServer = CLExecutiveNameServer :: GetInstance();
  if(pNameServer == 0) {
    std::cout << "Msg Loop get null name server in Ini" << std::endl;
    return CLStatus(-1, 0);
  }
  return pNameServer->Register(m_strThreadName.c_str(), new CLThreadCommunicationForQueueBySTLList(m_pMsgQueue));
}

CLStatus CLMsgLoopManagerForQueueBySTLList :: Uninitialize() {

  CLExecutiveNameServer * pNameServer = CLExecutiveNameServer :: GetInstance();
  if(pNameServer == 0) {
    std::cout << "Msg Loop get null name server in Uni" << std::endl;
    return CLStatus(-1, 0);
  }
  
  return pNameServer->ReleaseCommunicationPtr(m_strThreadName.c_str());
}

CLMessage * CLMsgLoopManagerForQueueBySTLList :: WaitForMessage() {
  return m_pMsgQueue->GetMessage();
}

