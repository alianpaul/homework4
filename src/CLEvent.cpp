#include "CLEvent.h"
#include "CLCriticalSection.h"
#include <iostream>

CLEvent :: CLEvent(bool bSemaphore){
  m_Flag = 0;
  m_bSemaphore = bSemaphore;
}

CLEvent :: ~CLEvent(){

}

CLStatus CLEvent :: Set() {
  {
    CLCriticalSection cs(&m_Mutex);
    
    if(m_bSemaphore) {
      m_Flag++;
    }else {
      m_Flag = 1;
    }
  }
  CLStatus s = m_Condition.Wakeup();
}

CLStatus CLEvent :: Wait() {
  {
    CLCriticalSection cs(&m_Mutex);
    while(m_Flag == 0) {
      CLStatus s = m_Condition.Wait(&m_Mutex);
      if(!s.IsSuccess())
	return s;
    }

    if(m_bSemaphore) {
      m_Flag--;
    }else {
      m_Flag = 0;
    }
  }

  return CLStatus(0, 0);
}
