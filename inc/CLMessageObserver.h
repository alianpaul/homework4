#ifndef CL_MSG_OBSERVER_H
#define CL_MSG_OBSERVER_H

#include "CLStatus.h"
#include "CLMessage.h"
#include "CLMessageLoopManager.h"

class CLMessageLoopManager;
/*why need to declare again*/

class CLMessageObserver {
 public:
  virtual CLStatus Initialize(CLMessageLoopManager * pMsgLoopManager,void * pContext) = 0;
};

#endif
