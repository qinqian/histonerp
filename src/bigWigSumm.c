/* bigWigSummary - Extract summary information from a bigWig file.. */

/* Copyright (C) 2011 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

/* CAM 05-07-2015: edited bigWigSummary to pass values back to python interface */

#include "common.h"
#include "linefile.h"
#include "hash.h"
#include "options.h"
#include "sqlNum.h"
#include "udc.h"
#include "bigWig.h"
#include "obscure.h"

/*char *summaryType = "mean";*/

void usage()
/* Explain usage and exit. */
{
errAbort(
  "bigWigSummary - Extract summary information from a bigWig file.\n"
  "usage:\n"
  "   bigWigSummary file.bigWig chrom start end dataPoints\n"
  "Get summary data from bigWig for indicated region, broken into\n"
  "dataPoints equal parts.  (Use dataPoints=1 for simple summary.)\n"
  "\nNOTE:  start and end coordinates are in BED format (0-based)\n\n"
  "options:\n"
  "   -type=X where X is one of:\n"
  "         mean - average value in region (default)\n"
  "         min - minimum value in region\n"
  "         max - maximum value in region\n"
  "         std - standard deviation in region\n"
  "         coverage - %% of region that is covered\n"
  "   -udcDir=/dir/to/cache - place to put cache for remote bigBed/bigWigs\n"
  );
}

static struct optionSpec options[] = {
   {"type", OPTION_STRING},
   {"udcDir", OPTION_STRING},
   {NULL, 0},
};

int bigWigSummary(char *bigWigFile, char *chrom, int start, int end, int dataPoints, double *summaryValues, char *summaryType )
/* bigWigSummary - Extract summary information from a bigWig file.. */
{
struct bbiFile *bwf = bigWigFileOpen(bigWigFile);
/* Make up values array initialized to not-a-number. */
double nan0 = strtod("NaN", NULL);
/*double summaryValues[dataPoints];*/
int i;
for (i=0; i<dataPoints; ++i)
    summaryValues[i] = nan0;

    if (bigWigSummaryArray(bwf, chrom, start, end, bbiSummaryTypeFromString(summaryType),dataPoints, summaryValues)){
        for (i=0; i<dataPoints; ++i){
            double val = summaryValues[i];
            if (isnan(val))
                summaryValues[i] = 0;
        }
    }else{
        bigWigFileClose(&bwf);
        return 1;
    }

    bigWigFileClose(&bwf);
    return 0;
}

