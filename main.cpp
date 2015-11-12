#include <iostream>
#include <unistd.h>
#include "libexe.h"
#include "CLMsgMainControl.h"
#include "CLControlMsgProcessor.h"
#include "CLMainMsgProcessor.h"

using namespace std;

int main(){

  int ArrayData[1000];

  for(int i = 0; i < 1000 ; i++) {
    ArrayData[i] = 1;
  }
  
  CLThreadForMsgLoop tControl(new CLControlMsgProcessor, "control", true);
  tControl.Run();
  
  cout << "main push to control" << endl;
  CLExecutiveNameServer::PostExecutiveMessage("control",new CLAddMsg(ArrayData, 1000));
    
  CLNonThreadForMsgLoop tMain(new CLMainMsgProcessor, "main");
  tMain.Run();
  
}

