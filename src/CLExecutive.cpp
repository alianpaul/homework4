#include "CLExecutive.h"

CLExecutive :: CLExecutive(CLExecutiveFunctionProvider * pExeFunProvider) {
  m_pExeFunProvider = pExeFunProvider;
}

CLExecutive :: ~CLExecutive() {
  delete m_pExeFunProvider;
}
