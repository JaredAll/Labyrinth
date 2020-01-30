#ifndef WALKING_STATE_H
#define WALKING_STATE_H

#include <stdio.h>
#include "state.h"

class walking_state : public State
{
public:
  void perform();
};

#endif
