/*just like the thread is already exists,so in Run,don't need to create a new thread
 *in run just execute ExecutiveFunctionProvider's RunExecutiveFunction
 *now is a messageloop,so we initialize ExecutiveFunctionProvider with new ExecutiveFunctionForMsgL
 *oop
 */

#ifndef CL_NON_THREAD_FOR_MSG_LOOP
#define CL_NON_THREAD_FOR_MSG_LOOP

#include "CLMessageObserver.h"
#include "CLExecutiveFunctionProvider.h"

class CLNonThreadForMsgLoop {
 public:
  CLNonThreadForMsgLoop(CLMessageObserver * pMsgObserver, const char * pstrThreadName);
  virtual ~CLNonThreadForMsgLoop();

  CLStatus Run();
  
 private:
  CLExecutiveFunctionProvider * m_pFunctionProvider;
};

#endif
