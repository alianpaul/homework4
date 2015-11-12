#ifndef CL_MSGLOOPMANAGER_FRO_QUEUE_STL_LIST
#define CL_MSGLOOPMANAGER_FRO_QUEUE_STL_LIST

#include "CLMessageLoopManager.h"
#include "CLMessageQueueBySTLList.h"
#include "CLMessage.h"
#include "CLMessageObserver.h"
#include <string>

class CLMsgLoopManagerForQueueBySTLList : public CLMessageLoopManager {

 public:
  CLMsgLoopManagerForQueueBySTLList(CLMessageObserver * pMsgObserver, const char * pstrThreadName);
  ~CLMsgLoopManagerForQueueBySTLList();
  CLStatus Initialize();
  CLStatus Uninitialize();
  CLMessage * WaitForMessage();
  
 private:
  /*need to manipulate the queue,has a pointer to a member
   */
  CLMessageQueueBySTLList * m_pMsgQueue;
  /*not initialized by outside,newed inside,because with NameServer,
   *out side can post without holding a pointer to msg queue
   */
  std::string m_strThreadName;
  /*need to register ExecutiveCommunication to NameServer
   *so also need a name offer by outside
   */

};

#endif
