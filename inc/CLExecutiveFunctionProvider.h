#ifndef CL_EXECUTIVE_FUNC_PROVIDER_H
#define CL_EXECUTIVE_FUNC_PROVIDER_H

#include "CLStatus.h"

class CLExecutiveFunctionProvider {
 public:
  CLExecutiveFunctionProvider();
  virtual ~CLExecutiveFunctionProvider();

  virtual CLStatus RunExecutiveFunction(void* pContext = 0) = 0;
};

#endif
