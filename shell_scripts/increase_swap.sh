#!/bin/bash

if [ $# -eq 1 ]; then
    size=$1
else
    size=16
fi

sudo swapoff /swfile
sudo dd if=/dev/zero of=/swfile bs=1G count=$size
sudo chmod 600 /swfile
sudo mkswap /swfile
sudo swapon /swfile
echo '/swfile none swap sw 0 0' | sudo tee -a /etc/fstab
