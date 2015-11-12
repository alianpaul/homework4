#ifndef CL_MSG_MAIN_CONTROL_H
#define CL_MSG_MAIN_CONTROL_H

#include "CLMessage.h"

#define ADD_MSG 0
#define START_MSG 1
#define THRD_CNT_MSG 2
#define RESULT_MSG 3
#define QUIT_LOOP 1000

/*******************************/
/*MAIN TO CONTROL*/

class CLAddMsg : public CLMessage {
 public:
 CLAddMsg(int * pnStart, int nLength) : CLMessage(ADD_MSG){
    m_pnStart = pnStart;
    m_nLength = nLength;
  }
  ~CLAddMsg(){}
  int * m_pnStart;
  int m_nLength;
};

class CLStartMsg : public CLMessage {
 public:
 CLStartMsg() : CLMessage(START_MSG){}
  ~CLStartMsg(){}
};

/*CONTROL TO MAIN*/

class CLThreadCntMsg : public CLMessage {
 public:
  CLThreadCntMsg(int nThreadCnt) : CLMessage(THRD_CNT_MSG), m_cnThreadCnt(m_nThreadCnt) {
    m_nThreadCnt = nThreadCnt;
  }
  ~CLThreadCntMsg() {}
  const int & m_cnThreadCnt;
 private:
  int m_nThreadCnt;
};

#endif

/*CALCULATE TO MAIN*/

class CLResultMsg : public CLMessage {
 public:
 CLResultMsg(int result) : CLMessage(RESULT_MSG),m_cnResult(m_nResult) {
    m_nResult = result;
  }
  ~CLResultMsg(){}
  const int & m_cnResult;
 private:
  int m_nResult;
};
