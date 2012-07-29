#pragma once
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include "../type/histogram.hpp"

using bandai::Histogram;
namespace bandai
{
  namespace image
  {
    class Parser
    {
    public:
      Histogram parse(const char *filename);
    private:
      int getColorIndex(int red, int green, int blue);
    };
  }
}
