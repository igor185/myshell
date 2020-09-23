#!/bin/bash

sed 's/\r$//' apt_packages.txt | sed 's/#.*//' | xargs sudo apt-get install -y