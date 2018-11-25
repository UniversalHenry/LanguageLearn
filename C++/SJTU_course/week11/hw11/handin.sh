#!/bin/bash

function print_usage() {
	echo -e "\033[1;37mHomework 11: LRU and LFU Cache\033[0m"
	echo
	echo -e "\033[4;37mUsage:\033[0m"
	echo -e "  \033[32m./handin.sh -id [Your Student ID]\033[0m"
	echo
	echo -e "\033[4;37mExample:\033[0m"
	echo -e "  \033[34m./handin.sh 515030910477\033[0m"
}

case $1 in
-id)
	tar -zcvf hw11_$2.tar.gz lfu.h lru.h *.pdf
	echo -e "\033[34mhw11_$2.tar.gz created. Please submit to the course website.\033[0m"
	;;
--help | -h | *)
	print_usage
	exit
	;;
esac
