#include "bhattacharyya.hpp"

float bandai::logic::Bhattacharyya::calc(Histogram a, Histogram b)
{
    int i     = 0;
    int sum_a = 0;
    int sum_b = 0;
    float score = 0;
    float vec_a[HIST_SIZE];
    float vec_b[HIST_SIZE];

    for (i=0;i<HIST_SIZE;i++)
    {
        sum_a += a.data[i];
        sum_b += b.data[i];
    }

    for (i=0;i<HIST_SIZE;i++)
    {
        vec_a[i] = (float) a.data[i] / sum_a;
        vec_b[i] = (float) b.data[i] / sum_b;
        score   += (float) sqrt(vec_a[i] * vec_b[i]);
    }

    return score;
}
