#include "reader.hpp"

Opening bandai::serializer::Reader::readOp(const char *filename)
{
  value fullJsonValue    = parseJsonString(getJsonString(filename));
  const object& fullJson = fullJsonValue.get<object>();

  value nameJson = fullJsonValue.get(JSON_KEY_NAME);
  value histJson = fullJsonValue.get(JSON_KEY_HIST_LIST);

  Histogram histograms[OP_HIST_COUNT];
  const array& hist_array = histJson.get<array>();

  int index = 0;
  array::const_iterator hist_itr = hist_array.begin();
  while (hist_itr != hist_array.end())
  {
    value dataJson = (*hist_itr).get(JSON_KEY_HIST_DATA);
    histograms[index] = convertArray(dataJson.get<array>());

    hist_itr++; index++;
  }

  Opening op(filename, histograms);
  return op;
}

Full bandai::serializer::Reader::readFull(const char *filename)
{
  value fullJsonValue    = parseJsonString(getJsonString(filename));
  const object& fullJson = fullJsonValue.get<object>();

  value nameJson = fullJsonValue.get(JSON_KEY_NAME);
  value histJson = fullJsonValue.get(JSON_KEY_HIST_LIST);

  Histogram histograms[FULL_HIST_COUNT];
  const array& hist_array = histJson.get<array>();

  int index = 0;
  array::const_iterator hist_itr = hist_array.begin();
  while (hist_itr != hist_array.end())
  {
    value dataJson = (*hist_itr).get(JSON_KEY_HIST_DATA);
    histograms[index] = convertArray(dataJson.get<array>());

    hist_itr++; index++;
  }

  Full full(filename, histograms);
  return full;
}

string bandai::serializer::Reader::getJsonString(const char* filename)
{
  ifstream ifs(filename);
  if (ifs.fail())
  {
    throw ERR_MSG_JSON_PARSE;
  }

  string str;
  string json_str = "";
  while(getline(ifs, str))
  {
    json_str += str;
  }

  return json_str;
}

value bandai::serializer::Reader::parseJsonString(string json_str)
{
  const char* json = json_str.c_str();

  value result;
  string json_error;
  parse(result, json, json + strlen(json), &json_error);

  if (!json_error.empty())
  {
    std::cerr << json_error << std::endl;
    throw ERR_MSG_JSON_INVALID;
  }

  return result;
}

Histogram bandai::serializer::Reader::convertArray(array data_array)
{
  Histogram histogram;

  int index = 0;
  array::const_iterator itr = data_array.begin();
  while (itr != data_array.end())
  {
    if (!(*itr).is<double>())
    {
      throw ERR_MSG_JSON_INVALID;
    }
    histogram.data[index] = (int) (*itr).get<double>();

    itr++; index++;
  }

  return histogram;
}
