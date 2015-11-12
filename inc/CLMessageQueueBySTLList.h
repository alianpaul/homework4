#ifndef CL_MESSAGE_QUEUE_BY_STL_LIST_H
#define CL_MESSAGE_QUEUE_BY_STL_LIST_H

#include "CLStatus.h"
#include "CLMessage.h"
#include "CLMutex.h"
#include "CLEvent.h"
#include <list>

class CLMessageQueueBySTLList {
 public:
  CLMessageQueueBySTLList();
  ~CLMessageQueueBySTLList();

  CLStatus PushMessage(CLMessage * pMessage);
  CLMessage * GetMessage();

 private:
  std::list<CLMessage *> m_MessageQueue;
  CLMutex m_Mutex; //m_MessageQueue is a shared res by threads
  CLEvent m_Event; //notification for the arrive of the message(Set)
};

#endif
