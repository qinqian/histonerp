### Prerequisites

#### Mac

``` bash
brew install openssl
export C_INCLUDE_PATH=${C_INCLUDE_PATH}:/usr/local/Cellar/openssl/your_version/include
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/usr/local/Cellar/openssl/your_version/lib/"
```

#### Linux
``` bash
sudo apt-get install openssl
sudo apt-get install default-libmysqlclient-dev # on vm image with docker
```

### Install the module using:

``` bash
sudo python setup.py install
# or 
python setup.py install --user
```

### Module on the production:

#### test the module:

``` bash
./getbw
``` 

``` bash
import _bw
_bw.getrp('your_bigWig', 'annotation_TSS', 'output', 10000.0)
```

#### Command line
regpot.py  -n out -b test/42359_treat.bw --tss test/test_tss.bed

adjust `-a ALPHA` for decay rate.

#### Further instruction
annotation_TSS `--tss` should be formatted as:

    chr1    11873   11874   NR_046018:DDX11L1       0       +
    chr1    17436   17437   NR_107063:MIR6859-3     0       -
    chr1    17436   17437   NR_128720:MIR6859-4     0       -

output demo `-n`, `5th` column is the regulatory potential score from bigWig: 

    chr1    11873   11874   NR_046018       208.234170501   DDX11L1 +
    chr1    17436   17437   NR_107063       219.513716641   MIR6859-3       -
    chr1    17436   17437   NR_128720       219.513716641   MIR6859-4       -


#### parameter to delete one specific region

This removal of region does not consider strand, e.g., to delete all promoter +/- 1kb:

``` bash
_bw.getrp('test/test.bw', 'test/test_tss.bed', 'test/out.tab', 10000.0, -1000, 1000)
```

Below would delete the downstream 1kb in the gene body for positive strand transcript, but upstream 1kb for negative strand transcript.

``` bash
_bw.getrp('test/test.bw', 'test/test_tss.bed', 'test/out.tab', 10000.0, 0, 1000)
```

