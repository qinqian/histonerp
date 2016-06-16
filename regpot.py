#!/usr/bin/env python
import sys,os
import math
import argparse
import time
import _bw

PADDING = int(1e5)

def getregpot(bw, tss, output, alpha):
    _bw.getrp(bw, tss, output, alpha)
    rp = {}
    with open(output) as inf:
        for line in inf:
            line = line.strip().split()
            rp['\t'.join(line[:4])] = line[4]
    fout = open(output, 'w')
    with open(tss) as inf:
        for line in inf:
            line = line.strip().split()
            s = line[3].split(':')
            print >>fout, '\t'.join([line[0], line[1], line[2], s[0], rp['\t'.join(line[:4])], s[1], line[-1]])

if __name__ == "__main__":
    tstart = time.time()
    results = []
    parser = argparse.ArgumentParser(description="""Calculate regulatory potential for each TSS.""")
    parser.add_argument( '-n', dest='name',   type=str, required=True, help='name to associate with input bed file' )
    parser.add_argument( '-a', dest='alpha',  type=float, default=1e4, required=False, help='effect of distance on regulatory potential. Distance at which regulatory potential is 1/2, (default=10kb)' )
    parser.add_argument( '-b', dest='bw',     type=str, required=True, help='Bigwig file name' )
    parser.add_argument( '--tss', dest='refseqTSS',  type=str, required=True, help='refseqTSS is six columns: <chromosome name> <TSS> <TSS+1> <refseq:genesymbok> <score> <strand>' )
    args = parser.parse_args()

    output = args.name + '_all_RP.txt'
    getregpot(args.bw, args.refseqTSS, output, args.alpha)

    tend = time.time()
    total = tend - tstart
    hour = int(total/3600)
    minute = int(total - hour*3600)/60
    second = int(total - hour*3600 - minute*60)
    print 'total time: %s:%s:%s '%(hour, minute, second)

