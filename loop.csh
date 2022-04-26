#!/bin/csh

foreach t ( 1 2 4 8)
  foreach n ( 1 10 100 1000 10000 100000 )
        g++ -O3   project2.cpp  -DNUMT=$t -DNUMNODES=$n  -o project2  -lm  -fopenmp
    ./project2
  end
end