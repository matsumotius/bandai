#include "searcher.hpp"

Opening bandai::service::Searcher::findByFull(const char *filename)
{
  DIR* dir;
  struct dirent* dp;

  if (NULL==(dir=opendir(OP_DATA_PATH)))
  {
    throw "failed to open dir\n";
  }

  Reader reader;

  char full_data_path[strlen(FULL_DATA_PATH) + strlen(filename) + strlen(".json")];
  sprintf(full_data_path, "%s%s.json", FULL_DATA_PATH, filename);

  Full full = reader.readFull(full_data_path);
  for (int i=0;NULL!=(dp=readdir(dir));i++)
  {
    if (0 == strcmp(".", dp->d_name) ||
        0 == strcmp("..", dp->d_name))
    {
      continue;
    }

    char op_data_path[strlen(OP_DATA_PATH) + strlen(dp->d_name)];
    sprintf(op_data_path, "%s%s", OP_DATA_PATH, dp->d_name);

    Opening op = reader.readOp(op_data_path);
    if (compare(op, full))
    {
      return op;
    }
  }
  closedir(dir);

  return getEmptyResult();
}

bool bandai::service::Searcher::compare(Opening op, Full full)
{
  for (int op_index=0;op_index<OP_HIST_COUNT;op_index++)
  {
    for (int full_index=0;full_index<FULL_HIST_COUNT;full_index++)
    {
      if (compareHistogram(op.histograms[op_index], full.histograms[full_index]))
      {
        // todo: log index of matched image file for debugging.
        return true;
      }
    }
  }
  return false;
}

bool bandai::service::Searcher::compareHistogram(Histogram a, Histogram b)
{
  return (this->compareAlgorithm.calc(a, b) > this->threshold);
}

Opening bandai::service::Searcher::getEmptyResult()
{
  Histogram histograms[OP_HIST_COUNT];
  for (int i=0;i<OP_HIST_COUNT;i++)
  {
    Histogram tmp;
    histograms[i] = tmp;
  }
  Opening op("", histograms);

  return op;
}
