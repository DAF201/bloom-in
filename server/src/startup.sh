# while true; do
#     for pid in $(ps -ef | grep python3 | awk '{print $2}'); do
#         kill -9 $pid
#     done

    cd ~
    python3 /home/ec2-user/bloom-in/bloom-in.py &
#     sleep 15m
# done
