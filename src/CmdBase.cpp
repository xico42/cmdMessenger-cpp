#include "CmdBase.h"

CmdBase::CmdBase(int id)
{
  CmdBase::setId(id);
}

CmdBase::~CmdBase()
{
}

void CmdBase::setId(int id)
{
  if(id >= 0) id_ = id;
}

int CmdBase::getId() const
{
  return id_;
}
