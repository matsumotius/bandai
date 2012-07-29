#include "store.hpp"
#include "../conf/config.hpp"

int bandai::service::Store::saveOp(const char *filename)
{
  Parser parser;
  Writer writer;

  char op_data_path[strlen(OP_DATA_PATH) + strlen(filename) + strlen(".json") + 1];
  sprintf(op_data_path, "%s%s.json", OP_DATA_PATH, filename);

  Histogram histograms[OP_HIST_COUNT];
  for (int i=0;i<OP_HIST_COUNT;i++)
  {
    char op_raw_path[strlen(OP_RAW_PATH) + strlen(filename) + strlen("/xxxx.jpg")];
    sprintf(op_raw_path, "%s%s/%d.jpg", OP_RAW_PATH, filename, i);

    histograms[i] = parser.parse(op_raw_path);
  }

  Opening op(filename, histograms);
  writer.writeOp(op, op_data_path);

  return 0;
}

int bandai::service::Store::saveFull(const char *filename)
{
  Parser parser;
  Writer writer;

  char full_data_path[strlen(FULL_DATA_PATH) + strlen(filename) + strlen(".json") + 1];
  sprintf(full_data_path, "%s%s.json", FULL_DATA_PATH, filename);

  Histogram histograms[FULL_HIST_COUNT];
  for (int i=0;i<FULL_HIST_COUNT;i++)
  {
    char full_raw_path[strlen(FULL_RAW_PATH) + strlen(filename) + strlen("/xxxx.jpg")];
    sprintf(full_raw_path, "%s%s/%d.jpg", FULL_RAW_PATH, filename, i);

    histograms[i] = parser.parse(full_raw_path);
  }

  Full full(filename, histograms);
  writer.writeFull(full, full_data_path);

  return 0;
}

