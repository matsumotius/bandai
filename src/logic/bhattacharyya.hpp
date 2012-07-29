#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../type/histogram.hpp"

using bandai::Histogram;
namespace bandai
{
  namespace logic
  {
    class Bhattacharyya
    {
    public:
      float calc(Histogram a, Histogram b);
    };
  }
}

