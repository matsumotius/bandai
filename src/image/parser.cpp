#include "parser.hpp"

Histogram bandai::image::Parser::parse(const char *filename)
{
  Histogram hist;

  IplImage *input = cvLoadImage(filename, CV_LOAD_IMAGE_COLOR);
  if (NULL == input)
  {
    throw "can not open image\n";
  }

  IplImage *output = cvCreateImage(cvGetSize(input), input->depth, 3);
  for (int y = 0; y < input->height; y++)
  {
      uchar *pin = (uchar *)(input->imageData + y * input->widthStep);
      for (int x = 0; x < input->width; x++)
      {
          int blue  = pin[3*x+0];
          int green = pin[3*x+1];
          int red   = pin[3*x+2];
          hist.data[getColorIndex(red, green, blue)] += 1;
      }
  }
  cvReleaseImage(&input);

  return hist;
}

int bandai::image::Parser::getColorIndex(int red, int green, int blue)
{
  int r = red   / HIST_SIZE;
  int g = green / HIST_SIZE;
  int b = blue  / HIST_SIZE;
  return 16 * r + 4 * g + b;
}
