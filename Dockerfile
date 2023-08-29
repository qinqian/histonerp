FROM ubuntu:18.04
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y \
    && apt-get install -y \
	curl \
        bzip2 \
        g++ \
        git \
        libncurses5-dev \
        libpng-dev \
        libtool \
        lmod \
        make \
        zlib1g-dev \
        libz-dev \
    && rm -rf /tmp/downloaded_packages/ /tmp/*.rds \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /opt

ENV PATH /opt/conda/bin:${PATH}
ENV LANG C.UTF-8
ENV SHELL /bin/bash
RUN /bin/bash -c "curl -L https://github.com/conda-forge/miniforge/releases/latest/download/Mambaforge-Linux-\$(uname -m).sh > mambaforge.sh && \
    bash mambaforge.sh -b -p /opt/conda && \
    conda config --system --set channel_priority strict && \
    rm mambaforge.sh"
RUN /bin/bash -c "mamba create -q -y -c bioconda -n rp python==3.10 numpy"
RUN git clone https://github.com/qinqian/histonerp
RUN cd histonerp && /opt/conda/envs/rp/bin/python setup.py install
RUN echo "source activate rp" > ~/.bashrc
ENV PATH /opt/conda/envs/rp/bin:${PATH}

