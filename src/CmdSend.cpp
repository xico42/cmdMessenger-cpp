#include "CmdBase.h"
#include "CmdSend.h"

using namespace cmd;

/*----------CTOR | DTOR----------*/

CmdSend::CmdSend(int id)
  :CmdBase(id),
  state_(false)
{ 
}

CmdSend::~CmdSend()
{ 
}

void CmdSend::add(CmdEnd end)
{
  state_ = true;
}

void CmdSend::operator<<(CmdEnd end)
{
  state_ = true;
}

bool CmdSend::getState() const
{
  return state_;
}

int CmdSend::getNumArgs() const
{
  return args_.size();
}

void CmdSend::clear()
{
  args_.clear();
}
