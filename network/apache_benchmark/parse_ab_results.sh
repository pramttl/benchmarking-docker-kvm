#usage bash parse_ab_results.sh ab_results_file
echo 'Concurrency Level'
cat $1 | grep 'Concurrency Level' | awk '{print $3}'
echo 'Complete requests'
cat $1 | grep 'Complete requests' | awk '{print $3}'
echo 'Failed requests'
cat $1 | grep 'Failed requests' | awk '{print $3}'
echo 'Requests per second'
cat $1 | grep 'Requests per second' | awk '{print $4}'
echo 'Time per request'
cat $1 | grep 'Time per request' | awk '{print $4}'| sed -n 1~2p
echo 'Transfer rate'
cat $1 | grep 'Transfer rate' | awk '{print $3}'
