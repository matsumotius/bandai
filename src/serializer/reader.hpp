#pragma once
#include <fstream>
#include <iostream>
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
    class Reader
    {
    public:
      Opening readOp(const char *filename);
      Full readFull(const char *filename);
    private:
      string getJsonString(const char *filename);
      value parseJsonString(string json_str);
      Histogram convertArray(array data_array);
    };
  }
}

