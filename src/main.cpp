#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>

#include "type/picojson.h"
#include "serializer/reader.hpp"
#include "serializer/writer.hpp"
#include "image/parser.hpp"
#include "service/store.hpp"
#include "service/searcher.hpp"

using namespace std;
using namespace picojson;
using namespace bandai::serializer;
using namespace bandai::image;
using namespace bandai::service;

int main(int argc, char *argv[])
{

  bool is_write  = false;
  bool is_search = false;
  bool is_op     = false;
  bool is_full   = false;
  
  int c;
  while ((c = getopt(argc, argv, "wsof")) != -1)
  {
    switch (c)
    {
    case 's':
      is_search = true;
      is_write  = false;
      break;
    case 'w':
      is_write  = true;
      is_search = false;
      break;
    case 'o':
      is_op     = true;
      is_full   = false;
      break;
    case 'f':
      is_full   = true;
      is_op     = false;
      break;
    case '?':
      cout << "select -w or -s option." <<endl;
    }
  }
  argc -= optind;
  argv += optind;

  try {
    if (is_write)
    {
      Store store;
      if (is_op)
      {
        store.saveOp(argv[0]);
      }
      if (is_full)
      {
        store.saveFull(argv[0]);
      }
    }
 
    if (is_search)
    {
      Searcher searcher;
      Opening op = searcher.findByFull(argv[0]);

      // todo: result output format
      if (strlen(op.name) < 1)
      {
        printf("not found\n");
      }
      else
      {
        // todo: output filename without base path
        printf("%s\n", op.name);
      }
    }
  } 
  catch (const char *error_msg)
  {
    cout << error_msg << endl;
  }

  return 0;
}
