# Different number of requests are generated with concurrency level 1000
# usage bash run_benchmark.sh ip_address > benchmark_results.txt
ab -kc 1000 -n 10000 http://$1/index.html
ab -kc 1000 -n 20000 http://$1/index.html
ab -kc 1000 -n 30000 http://$1/index.html
ab -kc 1000 -n 40000 http://$1/index.html
ab -kc 1000 -n 50000 http://$1/index.html
ab -kc 1000 -n 60000 http://$1/index.html
ab -kc 1000 -n 70000 http://$1/index.html
ab -kc 1000 -n 80000 http://$1/index.html
ab -kc 1000 -n 90000 http://$1/index.html
