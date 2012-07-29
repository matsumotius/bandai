#pragma once
#include "../conf/config.hpp"
#include "histogram.hpp"

using bandai::Histogram;
namespace bandai
{
  struct Opening
  {
  public:
    const char *name;
    Histogram histograms[OP_HIST_COUNT];
    Opening(const char *name, Histogram histograms[])
    {
      this->name = name;

      for (int i=0;i<OP_HIST_COUNT;i++)
      {
        Histogram tmp = histograms[i];
        this->histograms[i] = tmp;
      }
    }
  };
}
