#include "CLMessageLoopManager.h"
#include "CLEvent.h"

CLMessageLoopManager :: CLMessageLoopManager(CLMessageObserver * pMsgObserver) {
  m_pMsgObserver = pMsgObserver;
}

CLMessageLoopManager :: ~CLMessageLoopManager() {
  delete m_pMsgObserver;
}

CLStatus CLMessageLoopManager :: EnterMessageLoop(void * pContext) {
  /*pContext = 0
   *sent by CLNonThreadForMsgLoop
   */
  CLEvent * pEvent = (CLEvent *) pContext;
  CLStatus s = Initialize();
  if(!s.IsSuccess()){
    if(pEvent != 0)
      pEvent->Set();
    return s;
  }
    
  CLStatus s1 = m_pMsgObserver->Initialize(this, pContext);
  /*initialize the map in MsgObserver's Initialize */
  if(!s.IsSuccess()){
    if(pEvent != 0)
      pEvent->Set();
    return s;
  }

  if(pEvent !=0 )
    pEvent->Set();
    
  while(true) {
    CLMessage * pMessage = WaitForMessage();

    CLStatus s2 = DispatchMessage(pMessage);

    delete pMessage;
    
    if(s2.m_clReturnCode == QUIT_LOOP)
      break;
  }

  CLStatus s3 = Uninitialize();
  return s3;
}

CLStatus CLMessageLoopManager :: DispatchMessage(CLMessage * pMessage) {
  
  std::map<unsigned long, CallBackForMessageLoop> :: iterator it;
  it = m_MsgMappingTable.find(pMessage->m_clMsgID);
  
  if(it == m_MsgMappingTable.end())
    return CLStatus(-1, 0);

  /*invoke member function by pointer*/

  CallBackForMessageLoop pFunction = it->second;

  return (m_pMsgObserver->*pFunction)(pMessage);
  
}

/*only MsgObserver knows pFunction,so we need to invoke this function in oberver*/
CLStatus CLMessageLoopManager :: Register(unsigned long MsgID, CallBackForMessageLoop pFunction) {
  m_MsgMappingTable[MsgID] = pFunction;
  return CLStatus(0, 0);
}
