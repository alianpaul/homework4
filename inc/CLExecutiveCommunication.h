#ifndef CL_EXECUTIVE_COMM_H
#define CL_EXECUTIVE_COMM_H

#include "CLStatus.h"
#include "CLMessage.h"

class CLExecutiveCommunication {
 public:
  CLExecutiveCommunication();
  virtual ~CLExecutiveCommunication();

  virtual CLStatus PostExecutiveMessage(CLMessage * pMessage) = 0;
  
};

#endif
