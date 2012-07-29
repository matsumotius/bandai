#pragma once
#include <dirent.h>
#include "../conf/config.hpp"
#include "../conf/constants.hpp"
#include "../type/histogram.hpp"
#include "../type/opening.hpp"
#include "../type/full.hpp"
#include "../serializer/reader.hpp"
#include "../logic/bhattacharyya.hpp"
#include "../image/parser.hpp"

using bandai::Histogram;
using bandai::Opening;
using bandai::logic::Bhattacharyya;
using bandai::serializer::Reader;
namespace bandai
{
  namespace service
  {
    class Searcher
    {
    public:
      Searcher()
      {
        this->threshold = 0.99;
      }
      Opening findByFull(const char *filename);
    private:
      float threshold;
      Bhattacharyya compareAlgorithm;
      bool compare(Opening op, Full full);
      bool compareHistogram(Histogram a, Histogram b);
      Opening getEmptyResult();
    };
  }
}
