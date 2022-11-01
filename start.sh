#!bin/bash

#add this to home, and execute it, logout

# nohup python3 bloom-in/bloom-in.py

# nohup python3 bloom-in/file.py

while true; do

    for pid in $(ps -ef | grep python3 | awk '{print $2}'); do

        kill -9 $pid

    done

    cd ~

    nohup python3 bloom-in/bloom-in.py

    nohup python3 bloom-in/file.py

    sleep 15m

done
