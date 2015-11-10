Same program to run on host machine and docker container.

Run:

    python main.py

This will automatically compile and run the numeric integration program (which is a massively parallelizable program). The program will be run for multiple cases of NUMT. i.e. number of threads.

This is a massively parallelizable program which means that when number of threads increase performance should increase atleast until NUMT is atleast equal to number of cores.

performance is calculated as: NUMS*NUMS/run_time

NUMS = number of divisions used to divide numeric integration area. This is essentially the problem size. NUMS is set to a large value 14000 so the only thing that really effects performance is run_time in this case.
