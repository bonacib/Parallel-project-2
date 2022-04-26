#!/bin/csh

foreach t ( 1 2 4 8 10 12)
  foreach n ( 2 5 10 50 75 100 250 500 900)
        g++ -O3   project2.cpp  -DNUMT=$t -DNUMNODES=$n  -o project2  -lm  -fopenmp
    ./project2
  end
end