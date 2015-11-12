#ifndef CL_EXECUTIVE_H
#define CL_EXECUTIVE_H

#include "CLStatus.h"
#include "CLExecutiveFunctionProvider.h"

class CLExecutive {
 public:
  explicit CLExecutive(CLExecutiveFunctionProvider * pExeFunProvider);
  virtual ~CLExecutive();

  virtual CLStatus Run(void *pContext = 0) = 0;
  virtual CLStatus WaitForDeath() = 0;

 protected:
  CLExecutiveFunctionProvider * m_pExeFunProvider;
};

#endif
