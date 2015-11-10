import os

nums_values = [14000,]
#nums_values = range(1000, 15000, 1000);
thread_values = range(1, 12);

for t in thread_values:
    for n in nums_values:
        print os.system('g++ -fopenmp -DNUMS=%s -DNUMT=%s project1.c  && ./a.out'%(str(n), str(t)))
