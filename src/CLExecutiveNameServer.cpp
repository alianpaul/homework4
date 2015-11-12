#include "CLExecutiveNameServer.h"
#include "CLCriticalSection.h"
#include <iostream>

CLMutex *  CLExecutiveNameServer :: m_pMutexForNameServer = new CLMutex;

CLExecutiveNameServer * CLExecutiveNameServer :: m_pNameServer = 0;

CLExecutiveNameServer * CLExecutiveNameServer :: GetInstance() {

  if(m_pNameServer != 0)
    return m_pNameServer;
  
  {
    CLCriticalSection cs(m_pMutexForNameServer);
    if(m_pNameServer == 0) {
      m_pNameServer = new CLExecutiveNameServer;
    }
  }

  return m_pNameServer;
  
  
}

CLStatus CLExecutiveNameServer :: PostExecutiveMessage(const char * pstrExecutiveName, CLMessage * pMessage) {
  CLExecutiveNameServer * pNameServer = CLExecutiveNameServer :: GetInstance();
  if(pNameServer == 0) {
    std::cout << "NameServer Get Error" << std::endl;
    return CLStatus(-1, 0);
  }else {
    CLExecutiveCommunication * pComm = pNameServer->GetCommunicationPtr(pstrExecutiveName);
    if(pComm == 0){
      std::cout << "ExecutiveCommunication Get Error" << std::endl;
      return CLStatus(-1, 0);
    }else {
      CLStatus s = pComm->PostExecutiveMessage(pMessage);
      if(!s.IsSuccess()){
	std::cout << "ExecutiveCommunication Post Error" << std::endl;
	pNameServer->ReleaseCommunicationPtr(pstrExecutiveName);
	return s;
      }
    }
    pNameServer->ReleaseCommunicationPtr(pstrExecutiveName);
    return CLStatus(0, 0);
  }
  
}

CLStatus CLExecutiveNameServer :: Register(const char * strExecutiveName, CLExecutiveCommunication * pExecutiveCommunication) {

  {
    CLCriticalSection cs(&m_MutexForNameTable);
    /* if ExecutiveName already Exists, return*/
    std::map<std::string, SLExecutiveCommunicationPtrCount *>::iterator it;
    it = m_NameTable.find(strExecutiveName);
    if(it != m_NameTable.end())
      return CLStatus(-1, 0);

    /*doesn't exist, need to register
     *the message receiver initialize the the ExecutiveCommunication
     *and resigter to the NameServer,So when registering, message receiver
     *is already using ExecutiveCommnication,so nCount in associated SLExecutiveCommnicationPtrCoun
     *t = 1
     */

    SLExecutiveCommunicationPtrCount *pExeCommPtrCnt = new SLExecutiveCommunicationPtrCount;
    pExeCommPtrCnt->pExecutiveCommunication = pExecutiveCommunication;
    pExeCommPtrCnt->nCount = 1;
     
    m_NameTable[strExecutiveName] = pExeCommPtrCnt;
  }

  return CLStatus(0, 0);
}

CLExecutiveCommunication * CLExecutiveNameServer :: GetCommunicationPtr(const char * strExecutiveName) {

  {
    CLCriticalSection cs(&m_MutexForNameTable);
    std::map<std::string, SLExecutiveCommunicationPtrCount *>::iterator it;
    it = m_NameTable.find(strExecutiveName);

    if(it == m_NameTable.end())
      return 0;

    /*find it*/
    it->second->nCount++;

    return it->second->pExecutiveCommunication;
  
  }
}

CLStatus CLExecutiveNameServer :: ReleaseCommunicationPtr(const char * strExecutiveName) {
  CLExecutiveCommunication * pTmpExeComm = 0;
  {
    CLCriticalSection cs(&m_MutexForNameTable);
    std::map<std::string, SLExecutiveCommunicationPtrCount *>::iterator it;
    it = m_NameTable.find(strExecutiveName);

    if(it == m_NameTable.end())
      return CLStatus(-1, 0);

    /*find it*/
    it->second->nCount--;

    /*nCount == 0
     *but still exist some message in the queue
     *and in the destructor of message send message to other thread
     *will got a dead block,so dump the queue out side the critical section
     */
    if(it->second->nCount == 0) {
      pTmpExeComm =  it->second->pExecutiveCommunication;
      /*NameServer is responsible for delete
       *ExecutiveCommunication ptr,so the ExecutiveCommunication obj newed in
       *the receiver need don't need to delete.so as the msg queue
       */
      delete it->second;
      m_NameTable.erase(it);
    }
  }
  if(pTmpExeComm != 0)
    delete pTmpExeComm;
  return CLStatus(0, 0);
}

CLExecutiveNameServer :: CLExecutiveNameServer(){

}

CLExecutiveNameServer :: ~CLExecutiveNameServer(){

}
