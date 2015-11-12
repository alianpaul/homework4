#ifndef CL_EXE_NAME_SEVER_H
#define CL_EXE_NAME_SEVER_H

#include "CLExecutiveCommunication.h"
#include "CLMutex.h"
#include "CLStatus.h"
#include "CLMessage.h"
#include <string>
#include <map>

struct SLExecutiveCommunicationPtrCount{
  CLExecutiveCommunication * pExecutiveCommunication; //point to the communication object
  unsigned int nCount; //num of Threads that are using the communication object
};

class CLExecutiveNameServer {

 public:
  static CLExecutiveNameServer * GetInstance();

  CLStatus Register(const char* strExecutiveName, CLExecutiveCommunication * pExecutiveCommunication);
  

  static CLStatus PostExecutiveMessage(const char * strExecutiveName, CLMessage * pMessage);
  CLStatus ReleaseCommunicationPtr(const char * strExecutiveName);
  

 private:
  CLExecutiveNameServer();
  ~CLExecutiveNameServer();

  CLExecutiveCommunication * GetCommunicationPtr(const char* strExecutiveName);
  

 private:
  /*to ensure that only one NameServer exists between multiple Threads,
   *so we need a Mutex when initialize the NameSever.we initialize NameServer in
   *GetInstance if m_pNameServer == 0; so we need to wrap this test and initialization with mutex.this 
   *mutex can't be a member field,so need to be static too.
   */
  static CLMutex * m_pMutexForNameServer;
  static CLExecutiveNameServer * m_pNameServer;
  std::map<std::string, SLExecutiveCommunicationPtrCount*> m_NameTable;
  CLMutex m_MutexForNameTable;
};

#endif
