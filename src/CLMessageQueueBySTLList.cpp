#include "CLMessageQueueBySTLList.h"
#include "CLCriticalSection.h"

CLMessageQueueBySTLList :: CLMessageQueueBySTLList() : m_Event(true){

}

CLMessageQueueBySTLList :: ~CLMessageQueueBySTLList() {
  
  while(!m_MessageQueue.empty()) {
    CLMessage * pMessage = m_MessageQueue.front();
    m_MessageQueue.pop_front();
    delete pMessage;
  }
  
}

CLStatus CLMessageQueueBySTLList :: PushMessage(CLMessage* pMessage) {
  {
    CLCriticalSection cs(&m_Mutex);
    //push to the back of the list
    if(pMessage == 0)
      return CLStatus(-1, 0);

    m_MessageQueue.push_back(pMessage);
  }

  //Push Success, have new message, set the Event;
  return m_Event.Set();
}

CLMessage * CLMessageQueueBySTLList :: GetMessage() {
  //Wait until the message has arrived,
  CLStatus s = m_Event.Wait();
  if(!s.IsSuccess())
    return 0;
  CLMessage * pMessage = 0;
  {
    CLCriticalSection cs(&m_Mutex);
    pMessage = m_MessageQueue.front();
    m_MessageQueue.pop_front(); //message obj still exits
  }

  return pMessage;
}

