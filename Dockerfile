FROM ubuntu:24.04

ENV DEBIAN_FRONTEND noninteractive
ENV TERM=xterm

RUN apt update && \
    apt install -yq --no-install-recommends apt-utils && \
    apt install -yq build-essential parallel cmake git libgmp3-dev libmpfr-dev zlib1g zlib1g-dev bc wget python3 python3-pip python3-matplotlib gcc-13 g++-13 ncurses-term && \
    apt clean && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /home

####################################################################
# Move soplex 4.0.1 and build it
####################################################################
COPY soplex-4.0.1.tar.gz /home/soplex-4.0.1.tar.gz
RUN tar -xvf soplex-4.0.1.tar.gz && \
    cd soplex-4.0.1/ && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    cd ../..

ENV SOPLEX_PATH=/home/soplex-4.0.1
####################################################################
# git clone pldi2025artifact
####################################################################
RUN git clone https://github.com/spark423/pldi2025-artifact.git && \
    cd pldi2025-artifact

WORKDIR /home/pldi2025-artifact
