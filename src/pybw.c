#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
// #include <numpy/arrayobject.h>
#include "pybw.h"
#define BW_DOC "Retrieve data from bigwig file returns numpy array of scores. bwfile_name, chrom_list, start_list, end_list, sub_intervals, option (mean,max,min)"
#define RP_DOC "Summarize data from bigwig file as regulatory potential returns numpy array of scores. bwfile_name, chrom_list, start_list, end_list, strand_list, weights, option (mean,max,min)"


/* static PyObject *pyError1; */
static PyObject *pyError2;

static PyObject *
getrp(PyObject *self, PyObject *args)
{
  PyObject *bigwigfileObj;  /* bigwig file name strings */
  PyObject *bedfile;   /* bed file name strings */
  PyObject *outfile;   /* bed file name strings */
  PyObject *decay;   /* bed file name strings */
  PyObject *left;   /* bed file name strings */
  PyObject *right;   /* bed file name strings */
  char *bigWigFile; 
  char *bed;
  char *out;
  double d;
  int l;
  int r;
  if (! PyArg_ParseTuple( args, "O!O!O!O!O!O!", &PyString_Type, &bigwigfileObj, &PyString_Type, &bedfile, &PyString_Type, &outfile, &PyFloat_Type, &decay, &PyInt_Type, &left, &PyInt_Type, &right)) {
    PyErr_SetString( pyError2, "argument fault" );
    return NULL;
  }
  bigWigFile = PyString_AsString(bigwigfileObj);
  bed = PyString_AsString(bedfile);
  out = PyString_AsString(outfile);
  d = PyFloat_AsDouble(decay);
  l = PyInt_AsLong(left);
  r = PyInt_AsLong(right);

  printf("%s %s %s %f %d %d \n", bigWigFile, bed, out, d, l, r);

  bigWigAverageOverBed(bigWigFile, bed, out, d, l, r);

  Py_INCREF(Py_None);
  return Py_None;

  /* rpval  = ( PyArrayObject * )PyArray_SimpleNew( 1, dim, PyArray_DOUBLE ); */

  /* for (i=0; i<dataPoints; i++){ */
  /*   weightObj = PyList_GetItem(weightlistObj, i); */
  /*   weight[i] = PyFloat_AsDouble(weightObj); */
  /* } */
}

/* static PyObject *getrp(PyObject *self, PyObject *args) */
/* { */

/*     int i,k; */
/*     int numLines;           /\* how many lines we passed for parsing *\/ */
/*     PyObject *bigwigfileObj;  /\* bigwig file name strings *\/ */
/*     PyObject *chrlistObj;   /\* list of strings *\/ */
/*     PyObject *startlistObj; /\* list of ints *\/ */
/*     PyObject *endlistObj;   /\* list of ints *\/ */
/*     PyObject *chrObj;       /\* one string in the list *\/ */
/*     PyObject *startObj;     /\* one int in the list *\/ */
/*     PyObject *endObj;       /\* one int in the list *\/ */
/*     PyObject *dataPointsObj; /\* one int in the list *\/ */
/*     PyArrayObject *bwval;   /\* values from bw file *\/ */

/*     PyObject *summaryTypeObj; /\* string *\/ */
/*     char     *summaryType;    /\* string  *\/ */

/*     PyObject *strandlistObj;/\* list of strings *\/ */
/*     PyObject *weightlistObj;    /\* list of doubles *\/ */
/*     PyObject *strandObj;    /\* one string in the list *\/ */
/*     PyObject *weightObj;    /\* one in the list *\/ */
/*     PyArrayObject *rpval;   /\* regulatory potential summaries *\/ */

/*     npy_intp dim[2]; */

/*     char tmpstr[100]; */
/*     char const MEAN_OPTION[] = "mean"; */
/*     char const MAX_OPTION[]  = "max"; */
/*     char const MIN_OPTION[]  = "min"; */

/*     char const PLUS[]  = "+"; */
/*     char const MINUS[] = "-"; */

/*     char *bigWigFile; */

/*     char *chrom;  */
/*     int start; */
/*     int end; */
/*     int dataPoints; */
/*     int nPoints; */
/*     char *strand; */
/*     double *summaryValues; */
/*     double *weight; */

/*     if (! PyArg_ParseTuple( args, "O!O!O!O!O!O!", &PyString_Type, &bigwigfileObj, &PyList_Type, &chrlistObj, &PyList_Type, &startlistObj, &PyList_Type, &endlistObj, &PyList_Type, &strandlistObj, &PyList_Type, &weightlistObj ) ) */
/*         return NULL; */

/*     bigWigFile = PyString_AsString(bigwigfileObj); */

/*     /\* get the number of lines passed to us *\/ */
/*     numLines   = PyList_Size(startlistObj); */
    
/*     /\* should raise an error here. *\/ */
/*     if ( numLines < 1 ){ */
/*         return NULL;    // trigger exception */
/*     } */

/*     dataPoints = 0; */
/*     for (i=0; i<numLines; i++){ */
/*         /\* grab the string object from the next element of the list *\/ */
/*         startObj = PyList_GetItem(startlistObj, i); /\* Can't fail *\/ */
/*         endObj   = PyList_GetItem(endlistObj,   i); /\* Can't fail *\/ */
/*         start    = PyInt_AsLong(startObj); */
/*         end      = PyInt_AsLong(endObj); */
/* 	    dataPoints = dataPoints > (end-start) ? dataPoints : (end-start); */
/*    } */

/*     summaryValues = (double *)malloc((dataPoints)*sizeof(double)); */
/*     weight        = (double *)malloc((dataPoints)*sizeof(double)); */

/*     dim[0] = numLines; */

/*     rpval  = ( PyArrayObject * )PyArray_SimpleNew( 1, dim, PyArray_DOUBLE ); */

/*     for (i=0; i<dataPoints; i++){ */
/*         weightObj = PyList_GetItem(weightlistObj, i); */
/* 	    weight[i] = PyFloat_AsDouble(weightObj); */
/*     } */

/*     /\* iterate over items of the list, grabbing strings, and parsing for numbers *\/ */
/*     for (i=0; i<numLines; i++){ */

/*         /\* grab the string object from the next element of the list *\/ */
/*         chrObj    = PyList_GetItem(chrlistObj,   i); /\* Can't fail *\/ */
/*         startObj  = PyList_GetItem(startlistObj, i); /\* Can't fail *\/ */
/*         endObj    = PyList_GetItem(endlistObj,   i); /\* Can't fail *\/ */
/*         strandObj = PyList_GetItem(strandlistObj,i); /\* Can't fail *\/ */
 
/* 	    chrom  = PyString_AsString(chrObj); */
/*         start  = PyInt_AsLong(startObj); */
/*         end    = PyInt_AsLong(endObj); */
/* 	strand = PyString_AsString(strandObj); */
 
/* 	    nPoints = end - start; */
/* 	    *(double *)( rpval->data + i*rpval->strides[0] ) = 0;  */

/* 	    if ( bigWigSummary( bigWigFile, chrom, start, end, nPoints, summaryValues, MEAN_OPTION ) > 0 ){ */
/*             sprintf( tmpstr, "Region not found: %s %d %d\n", chrom, start, end ); */
/* 	        *(double *)( rpval->data + i*rpval->strides[0] ) = 0; */
/*         }else{ */
/* 	        if ( strcmp( strand, PLUS ) == 0 ){ */
/*                 for( k=0; k<nPoints; k++ ){ */
/* 		            // on + strand missing end data will come from the 5' end */
/* 		            *(double *)( rpval->data + i*rpval->strides[0] ) += weight[dataPoints-k-1]*summaryValues[nPoints-k-1]; */
/* 		        } */
/* 	        }else{ */
/* 		        for( k=0; k<nPoints; k++ ){ */
/* 		            // on - strand missing end data will come from the 3' end */
/* 	                *(double *)( rpval->data + i*rpval->strides[0] ) += weight[dataPoints-k-1]*summaryValues[k]; */
/* 		        } */
/*             } */
/*         } */
    
/*     } */
 
/*     free( summaryValues ); */
/*     free( weight ); */

/*     return PyArray_Return(rpval);  */
/* } */


/* static PyObject *getbw(PyObject *self, PyObject *args) */
/* { */

/*     int i,k; */
/*     int numLines;           /\* how many lines we passed for parsing *\/ */
/*     PyObject *bigwigfileObj;  /\* bigwig file name strings *\/ */
/*     PyObject *chrlistObj;   /\* list of strings *\/ */
/*     PyObject *startlistObj; /\* list of ints *\/ */
/*     PyObject *endlistObj;   /\* list of ints *\/ */
/*     PyObject *chrObj;       /\* one string in the list *\/ */
/*     PyObject *startObj;     /\* one int in the list *\/ */
/*     PyObject *endObj;       /\* one int in the list *\/ */
/*     PyObject *dataPointsObj; /\* one int in the list *\/ */
/*     PyArrayObject *bwval;   /\* values from bw file *\/ */

/*     PyObject *summaryTypeObj; /\* string *\/ */
/*     char     *summaryType;    /\* string  *\/ */

/*     npy_intp dim[2]; */

/*     char tmpstr[100]; */
/*     char const MEAN_OPTION[] = "mean"; */
/*     char const MAX_OPTION[]  = "max"; */
/*     char const MIN_OPTION[]  = "min"; */

/*     char *bigWigFile; */

/*     char *chrom;  */
/*     int start; */
/*     int end; */
/*     int dataPoints; */
/*     int nPoints; */
/*     double *summaryValues; */

/*     if (! PyArg_ParseTuple( args, "O!O!O!O!O!O!", &PyString_Type, &bigwigfileObj, &PyList_Type, &chrlistObj, &PyList_Type, &startlistObj, &PyList_Type, &endlistObj, &PyInt_Type, &dataPointsObj, &PyString_Type, &summaryTypeObj ) ) */
/*         return NULL; */

/*     bigWigFile = PyString_AsString(bigwigfileObj); */
 
/*     /\* get the number of lines passed to us *\/ */
/*     numLines   = PyList_Size(startlistObj); */
/*     /\* dataPointsObj should indicate the maximum number of values in any interval *\/ */
/*     dataPoints = PyInt_AsLong(dataPointsObj); */

/*     /\* should raise an error here. *\/ */
/*     if ( numLines < 1 ){ */
/*         return NULL;    // trigger exception */
/*     } */

/*     /\* should raise an error here. *\/ */
/*     if ( dataPoints < 1 ){ */
/*         return NULL;    // trigger exception */
/*     } */

/*     summaryValues = (double *)malloc((dataPoints)*sizeof(double)); */

/*     dim[0] = numLines; */
/*     dim[1] = dataPoints; */

/*     bwval  = ( PyArrayObject * )PyArray_SimpleNew( 2, dim, PyArray_DOUBLE ); */
/*     summaryType = PyString_AsString(summaryTypeObj); */

/*     if ( strcmp( summaryType, MEAN_OPTION ) == 0 || strcmp( summaryType, MAX_OPTION ) == 0 || strcmp( summaryType, MIN_OPTION ) == 0 ){ */
/*         ; */
/*     }else{ */
/*         free( summaryValues ); */
/*         sprintf( tmpstr, "Option %s not mean, min or max.\n", summaryType ); */
/*         PyErr_SetString( pyError1, tmpstr); */
/*         return NULL; */
/*     } */

/*     /\* iterate over items of the list, grabbing strings, and parsing for numbers *\/ */
/*     for (i=0; i<numLines; i++){ */

/*         /\* grab the string object from the next element of the list *\/ */
/*         chrObj   = PyList_GetItem(chrlistObj,   i); /\* Can't fail *\/ */
/*         startObj = PyList_GetItem(startlistObj, i); /\* Can't fail *\/ */
/*         endObj   = PyList_GetItem(endlistObj,   i); /\* Can't fail *\/ */

/*         chrom = PyString_AsString(chrObj); */
/*         start = PyInt_AsLong(startObj); */
/*         end   = PyInt_AsLong(endObj); */
       
/*         /\* if dataPoints is longer than interval length *\/  */
/*         if ( dataPoints > end - start ){ */
/*             nPoints = end - start; */
/*         }else{ */
/*             nPoints = dataPoints; */
/*         }  */
     
/*         if ( bigWigSummary( bigWigFile, chrom, start, end, nPoints, summaryValues, summaryType ) > 0 ){ */
/*             free( summaryValues ); */
/*             sprintf( tmpstr, "Region not found: %s %d %d\n", chrom, start, end ); */
/*             PyErr_SetString( pyError1, tmpstr); */
/*             return NULL; */
/*         }else{ */

/*             for( k=0; k<nPoints; k++ ){ */
/*                 *(double *)( bwval->data + i*bwval->strides[0] + k*bwval->strides[1] ) = summaryValues[k]; */
/*             } */

/*             if ( nPoints < dataPoints ){ */
/*                 for( k=nPoints; k<dataPoints; k++ ){ */
/*                     *(double *)( bwval->data + i*bwval->strides[0] + k*bwval->strides[1] ) = 0; */
/*                 } */
/*             } */
/*         } */

/*     } */
 
/*     free( summaryValues ); */
/*     return PyArray_Return(bwval);  */
/* } */

PyMethodDef myMethods[] = {
    { "getrp",   getrp,   METH_VARARGS, RP_DOC },
    /* { "getbw",   getbw,   METH_VARARGS, BW_DOC }, */
    { NULL, NULL, 0, NULL }
};

PyMODINIT_FUNC init_bw(void)
{       
    PyObject *m; //*d;
    m=Py_InitModule("_bw", myMethods);
    // import_array();
    /* pyError1 = PyErr_NewException("getbw.error", NULL, NULL); */
    pyError2 = PyErr_NewException("getrp.error", NULL, NULL);
    /* Py_INCREF(pyError1); */
    Py_INCREF(pyError2);
    /* PyModule_AddObject(m, "bw error", pyError1); */
    PyModule_AddObject(m, "rp error", pyError2);

    /* d = PyModule_GetDict(m); */

}
