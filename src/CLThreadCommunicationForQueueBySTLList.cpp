#include "CLThreadCommunicationForQueueBySTLList.h"

CLThreadCommunicationForQueueBySTLList :: CLThreadCommunicationForQueueBySTLList(CLMessageQueueBySTLList * pMsgQueue) {
  m_pMsgQueue = pMsgQueue;
}

CLThreadCommunicationForQueueBySTLList :: ~CLThreadCommunicationForQueueBySTLList() {
  delete m_pMsgQueue;
}

CLStatus CLThreadCommunicationForQueueBySTLList :: PostExecutiveMessage(CLMessage * pMessage) {
  return m_pMsgQueue->PushMessage(pMessage);
}
