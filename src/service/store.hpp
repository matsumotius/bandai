#pragma once
#include <stdlib.h>
#include "../type/histogram.hpp"
#include "../image/parser.hpp"
#include "../serializer/writer.hpp"

using namespace std;
using bandai::Histogram;
using bandai::serializer::Writer;
using bandai::image::Parser;
namespace bandai
{
  namespace service
  {
    class Store
    {
    public:
      int saveOp(const char *filename);
      int saveFull(const char *filename);
    };
  }
}

