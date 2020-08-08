# orderbook

This repository contains implementation of an order book. 

# Build

<b>Prerequisites : </b>
  - Cmake version >= 2.8.7
  - c++11
  - g++-8.3
            
<b>Build Steps - </b> 

In the main directory execute the following commands :
  - mkdir build
  - cd build
  - cmake -DCMAKE_CXX_COMPILER=/path/to/g++-8.3/ ..
  - make

An execuatble named "orderbook" along with book.test will get generated in the bin folder

</b>Run Steps - </b>

  - For Running orderbook - ./orderbook path/to/mktdatafile
  - For Running gtest - ./book.test
