#ifndef CL_MESSAGE_H
#define CL_MESSAGE_H

class CLMessage {
 public:
  CLMessage(unsigned long lmsgID);
  virtual ~CLMessage();

  const unsigned long & m_clMsgID;
  
 private:
  unsigned long m_lMsgID;
};

#endif
