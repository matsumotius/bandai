#include "writer.hpp"

int bandai::serializer::Writer::writeOp(Opening op, const char *filepath)
{
  array histograms;
  for (int i=0;i<OP_HIST_COUNT;i++)
  {
    object histogram;
    histogram.insert(make_pair(JSON_KEY_HIST_DATA, convertHistogram(op.histograms[i])));
    histograms.push_back(value(histogram));
  }

  object json;
  json.insert(make_pair(JSON_KEY_NAME, op.name));
  json.insert(make_pair(JSON_KEY_HIST_LIST, histograms));

  ofstream ofs;
  ofs.open(filepath, ios_base::out | ios_base::trunc | ios_base::binary);
  ofs << value(json).serialize().c_str() << endl;
  ofs.close();

  return 0;
}

int bandai::serializer::Writer::writeFull(Full full, const char *filepath)
{
  array histograms;
  for (int i=0;i<FULL_HIST_COUNT;i++)
  {
    object histogram;
    histogram.insert(make_pair(JSON_KEY_HIST_DATA, convertHistogram(full.histograms[i])));
    histograms.push_back(value(histogram));
  }

  object json;
  json.insert(make_pair(JSON_KEY_NAME, full.name));
  json.insert(make_pair(JSON_KEY_HIST_LIST, histograms));

  ofstream ofs;
  ofs.open(filepath, ios_base::out | ios_base::trunc | ios_base::binary);
  ofs << value(json).serialize().c_str() << endl;
  ofs.close();

  return 0;
}

array bandai::serializer::Writer::convertHistogram(Histogram histogram)
{
  array hist_array;
  for (int i=0;i<HIST_SIZE;i++)
  {
    hist_array.push_back(value((double)histogram.data[i]));
  }
  return hist_array;
}
