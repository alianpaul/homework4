#include "CLStatus.h"

CLStatus::CLStatus(long lReturnCode, long lErrorCode):m_clReturnCode(m_lReturnCode), m_clErrorCode(m_lErrorCode){
  m_lErrorCode = lErrorCode;
  m_lReturnCode = lReturnCode;
}

CLStatus::CLStatus(const CLStatus & s):m_clReturnCode(m_lReturnCode), m_clErrorCode(m_lErrorCode){
  m_lErrorCode = s.m_clErrorCode;
  m_lReturnCode = s.m_clReturnCode;
}

CLStatus::~CLStatus(){

}

CLStatus & CLStatus :: operator=(const CLStatus & s) {
  m_lErrorCode = s.m_lErrorCode;
  m_lReturnCode = s.m_clReturnCode;
  return *this;
}

bool CLStatus::IsSuccess(){
  return m_clErrorCode >= 0;
}
