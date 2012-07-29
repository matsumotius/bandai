#pragma once
#define HIST_SIZE 64
namespace bandai
{
  struct Histogram
  {
  public:
    int size;
    int data[HIST_SIZE];
    Histogram()
    {
      size = HIST_SIZE;

      for (int i=0;i<HIST_SIZE;i++)
      {
        data[i] = 0; 
      }
    }
  };
}

