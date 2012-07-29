#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "../conf/constants.hpp"
#include "../type/picojson.h"
#include "../type/histogram.hpp"
#include "../type/opening.hpp"
#include "../type/full.hpp"

using namespace std;
using namespace picojson;
using bandai::Histogram;
using bandai::Opening;
using bandai::Full;
namespace bandai
{
  namespace serializer
  {
    class Writer
    {
    public:
      int writeOp(Opening op, const char *filepath);
      int writeFull(Full full, const char *filepath);
    private:
      array convertHistogram(Histogram histogram);
    };
  }
}
