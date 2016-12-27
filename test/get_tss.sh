#!/bin/bash

refseq=$1

awk '(NR>1) {OFS="\t";if ($4=="+"){print $3,$5,$5+1,$2":"$13,0,$4} else {print $3,$6-1,$6,$2":"$13,0,$4}}' $refseq

