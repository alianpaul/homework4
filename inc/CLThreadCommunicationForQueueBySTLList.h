#ifndef CL_THREAD_COMM_FOR_QUEUE_BY_STL_LIST
#define CL_THREAD_COMM_FOR_QUEUE_BY_STL_LIST

#include "CLExecutiveCommunication.h"
#include "CLMessageQueueBySTLList.h"
#include "CLStatus.h"
class CLThreadCommunicationForQueueBySTLList : public CLExecutiveCommunication {
 public:
  CLThreadCommunicationForQueueBySTLList(CLMessageQueueBySTLList * pMsgQueue);
  ~CLThreadCommunicationForQueueBySTLList();
  CLStatus PostExecutiveMessage(CLMessage * pMessage);
 private:
  CLMessageQueueBySTLList * m_pMsgQueue;
};

#endif
