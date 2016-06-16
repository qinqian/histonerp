#!/usr/bin/env python

import os
import sys
from setuptools import setup, Extension
from numpy.distutils.misc_util import get_numpy_include_dirs

cbw = Extension( '_bw',
                 sources = ['src/bigWigRegPotential.c', 'src/pybw.c', 'lib/ffScore.c', 'lib/rbTree.c', 'lib/rangeTree.c', 'lib/ffAli.c', 'lib/ffAliHelp.c', 'lib/fuzzyFind.c', 'lib/bwgValsOnChrom.c', 'lib/tokenizer.c', 'lib/asParse.c', 'lib/aliType.c', 'lib/dnaseq.c', 'lib/dnautil.c', 'lib/gfxPoly.c', 'lib/psl.c', 'lib/binRange.c', 'lib/sqlList.c', 'lib/basicBed.c', 'lib/bPlusTree.c','lib/base64.c','lib/bbiRead.c','lib/bbiWrite.c','src/bigWigSumm.c','lib/bits.c','lib/bwgQuery.c','lib/cheapcgi.c','lib/cirTree.c','lib/common.c','lib/dlist.c','lib/dystring.c','lib/errAbort.c','lib/hash.c','lib/hex.c','lib/hmmstats.c','lib/https.c','lib/intExp.c','lib/internet.c','lib/kxTok.c','lib/linefile.c','lib/localmem.c','lib/memalloc.c','lib/mime.c','lib/net.c','lib/obscure.c','lib/options.c','lib/osunix.c','lib/pipeline.c','lib/portimpl.c','lib/servBrcMcw.c','lib/servCrunx.c','lib/servcis.c','lib/servcl.c','lib/servmsII.c','lib/servpws.c','lib/sqlNum.c','lib/udc.c','lib/verbose.c','lib/wildcmp.c','lib/zlibFace.c'],
                 extra_compile_args = ['-O3', '-std=c99', '-Wall'],
	         libraries=['ssl','z','crypto'],
                 #extra_link_args = ['-lc']
                 )

setup(name="PYBW",
      version="1.0.0",
      description="Python interface for UCSC bigwig reader",
      author='Cliff Meyer, Qian Alvin Qin',
      author_email='cliff@jimmy.harvard.edu',
      url='http://liulab.dfci.harvard.edu/',
      ext_modules = [cbw,],
      scripts=['getbw','regpot.py'],
      zip_safe=True,
      include_dirs=['inc'] + get_numpy_include_dirs(),
      classifiers=[
        'Development Status :: 5 - productive',
        'Environment :: Console',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: Artistic License',
        'Operating System :: MacOS :: MacOS X',
        'Programming Language :: Python',
        ])
