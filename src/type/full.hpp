#pragma once
#include "../conf/config.hpp"
#include "histogram.hpp"

using bandai::Histogram;
namespace bandai
{
  struct Full
  {
  public:
    const char *name;
    Histogram histograms[FULL_HIST_COUNT];
    Full(const char *name, Histogram histograms[])
    {
      this->name = name;

      for (int i=0;i<FULL_HIST_COUNT;i++)
      {
        Histogram tmp = histograms[i];
        this->histograms[i] = tmp;
      }
    }
  };
}

