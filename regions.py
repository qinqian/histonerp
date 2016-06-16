import sys,time,os,math,struct,random,numpy
import twobitreader

import __init__
#import seqpos.seqpos as seqpos
#import re,MySQLdb,operator 
#import mystats

NONEARESTSITE = 999999999
MISSINGVAL    = -99999999
NOCLUSTER     = -1
ERRCODE  = 1
PASSCODE = 0

def maskseq( seq, masklocs ):
    """
    seq is a list of sequence strings
    masklocs is a list of 3 tuples / lists: 
        x[0] index of string to be masked
        x[1] start position to be masked
        x[2] end position + 1 
    """
    for xloc in masklocs:
        l = list( seq[xloc[0]] )
        l[xloc[1]:xloc[2]] = (xloc[2]-xloc[1])*['N']
        seq[xloc[0]] = ''.join(l)
    return


class interval(object):

    def __init__(self,genome,description=''):
        self.description = description
        self.genome = genome
        self.chrom  = None 
        self.start  = None
        self.end    = None
        self.idx    = None
        self.length = None
        self.prob   = None
        self.val    = None
        self.name   = None
        self.namelookup = None # MakeIndex makes a dictionary of names mapping to indices 
        self.mid    = None
        self.strand = None
        self.name2  = None
        self.seq    = None
        self.conservation = None
        self.motifscores  = None
        self.basecontent  = None
        self.info   = None # list of strings holding information about ChIP 

    def __str__(self):
        """
        print bed file
        """
        s=''
        for i,elem in enumerate(self.chrom):
            s += '\t'.join([self.chrom[i],str(self.start[i]),str(self.end[i])])
            if self.name and (len(self.name) == len(self.chrom)):
                s+= '\t%s' % self.name[i]
            if self.val != None: # and len(self.val) == len(self.chrom):
                s+= '\t%5.2f' % self.val[i]
            if self.strand != None: # and len() == len(self.chrom):
                s+= '\t%s' % self.strand[i]
           
            s += '\n'
        return s

    def __getitem__(self,key):
        """
        Slice interval object
        """
        new = interval(self.genome,description=self.description)

        for elem in self.__dict__:
            # copy lists 
            if type( self.__dict__[elem] ) == type([]):
                new.__dict__[elem] = self.__dict__[elem][key]
            # copy arrays
            if type( self.__dict__[elem] ) == type(numpy.zeros(1,float)):
                new.__dict__[elem] = self.__dict__[elem][key]
            # copy dictionaries
            #if type( self.__dict__[elem] ) == type({}):
            #    new.__dict__[elem] = self.__dict__[elem]

        return new


    def read_bed(self,file,scorefield=4,strandfield=5,name2field=6):
        """
        Scorefield is the column to be read as score (index starting at 0).
        """

        CHROMFIELD,STARTFIELD,ENDFIELD,NAMEFIELD = range(4)
        SCOREFIELD = scorefield
        STRANDFIELD = strandfield
        NAME2FIELD = name2field

        try:
            fp=open(file,'r')
        except IOError:
            print "%s not found." % file
            raise

        self.chrom, self.start, self.end = [],[],[]
        self.length, self.mid = [],[]
    
        fi = iter(fp)

        nameflag,scoreflag,strandflag,name2flag = False,False,False,False
        for i,line in enumerate(fi):
            if line[0:3] == 'chr':
 
                try:
                    field    = line.split()
                    chrom_t  = field[CHROMFIELD]
                    start_t  = int(field[STARTFIELD])
                    end_t    = int(field[ENDFIELD])
                    length_t = end_t-start_t
                    mid_t    = int(0.5*(end_t+start_t))
                    #strand_t = field[STRANDFIELD]
                    
                except:
                    chrom_t,start_t,end_t,length_t,mid_t = None,None,None,None,None
                    print "Error reading line of bedfile %s on line %d:\n%s" % (file,i,line)
                    continue
                    #return ERRCODE
   
                #print strand_t
                if chrom_t:
                    self.chrom  += [chrom_t]
                    self.start  += [start_t]
                    self.end    += [end_t]
                    self.length += [length_t]
                    self.mid    += [mid_t]
                    #self.strand    += [strand_t]
     
                    if len(self.chrom) == 1:
                        if len(field) > NAMEFIELD:
                            nameflag = True
                            self.name = []
                        if len(field) > SCOREFIELD:
                            scoreflag = True
                            self.val = []
                        if len(field) > STRANDFIELD and field[STRANDFIELD] in ['+','-']:
                            strandflag = True
                            self.strand = []
                        if len(field) > NAME2FIELD:
                            name2flag = True
                            self.name2 = []

                    if nameflag == True:
                        try:
                            self.name   += [field[NAMEFIELD]]
                        except IndexError:
                            print "Error reading name in bedfile %s on line %d:\n%s" % (file,i,line)
                            return ERRCODE
                    
                    if scoreflag == True:
                        try:
                            self.val    += [float(field[SCOREFIELD])]
                        except:
                            print "Error reading score in bedfile %s on line %d:\n%s" % (file,i,line)
                            return ERRCODE

                    if strandflag == True:
                        try:
                            self.strand += [field[STRANDFIELD]]
                            if self.strand[-1] not in ['-','+']:
                                print "Error reading strand in bedfile %s on line %d:\n%s" % (file,i,line)
                                print "Bed file error: strand must be + or - %s" % strand[-1]
                                return ERRCODE
                        except:
                            print "Error reading bedfile %s on line %d:\n%s" % (file,i,line)
                            return ERRCODE
                    if name2flag == True:
                        try:
                            self.name2 += [field[NAME2FIELD]]
                        except:
                            print "Error reading score in bedfile %s on line %d:\n%s" % (file,i,line)
                            return ERRCODE
                    
                        #self.strand += [field[STRANDFIELD]]

        #print "number of regions:", len(self.chrom)
        return PASSCODE

