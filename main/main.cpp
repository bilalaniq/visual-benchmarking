#include <iostream>
#include "visual_benchmarking.h"

void function1()
{
  profile_Function();
  for (volatile int i = 0; i < 500000000; ++i)
  {
  }
}

void function2()
{
  profile_Function();
  for (volatile int i = 0; i < 2000000000; ++i)
  {
  }
}

int main()
{
  begin_session("Profile");
  {

    profile_Function();

    function1();
    function2();

    for (volatile int i = 0; i < 1000000000; ++i)
    {
    }
  }

  end_session();

  return 0;
}
