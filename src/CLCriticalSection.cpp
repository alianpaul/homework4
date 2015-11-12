#include "CLCriticalSection.h"

CLCriticalSection :: CLCriticalSection(CLMutex *pMutex) {
  m_pMutex = pMutex;
  m_pMutex -> Lock();
}

CLCriticalSection :: ~CLCriticalSection() {
  m_pMutex -> Unlock();
}
