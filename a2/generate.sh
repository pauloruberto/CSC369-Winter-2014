#!/bin/bash
echo "-------------- Results for rand --------------"
echo "*********simpleloop*********"
echo "!!!!!!!!!Memory size: 50!!!!!!!!!"
./sim -f traceprogs/tr-simpleloop.ref -m 50 -s 3000 -a rand | tail -n 7 
echo "!!!!!!!!!Memory size: 100!!!!!!!!!"
./sim -f traceprogs/tr-simpleloop.ref -m 100 -s 3000 -a rand | tail -n 7
echo "!!!!!!!!!Memory size: 150!!!!!!!!!"
./sim -f traceprogs/tr-simpleloop.ref -m 150 -s 3000 -a rand | tail -n 7
echo "!!!!!!!!!Memory size: 200!!!!!!!!!"
./sim -f traceprogs/tr-simpleloop.ref -m 200 -s 3000 -a rand | tail -n 7
echo
echo "*********matmul*********"
echo "!!!!!!!!!Memory size: 50!!!!!!!!!"
./sim -f traceprogs/tr-matmul.ref -m 50 -s 3000 -a rand | tail -n 7
echo "!!!!!!!!!Memory size: 100!!!!!!!!!"
./sim -f traceprogs/tr-matmul.ref -m 100 -s 3000 -a rand | tail -n 7
echo "!!!!!!!!!Memory size: 150!!!!!!!!!"
./sim -f traceprogs/tr-matmul.ref -m 150 -s 3000 -a rand | tail -n 7
echo "!!!!!!!!!Memory size: 200!!!!!!!!!"
./sim -f traceprogs/tr-matmul.ref -m 200 -s 3000 -a rand | tail -n 7
echo
echo "*********blocked*********"
echo "!!!!!!!!!Memory size: 50!!!!!!!!!"
./sim -f traceprogs/tr-blocked.ref -m 50 -s 3000 -a rand | tail -n 7
echo "!!!!!!!!!Memory size: 100!!!!!!!!!"
./sim -f traceprogs/tr-blocked.ref -m 100 -s 3000 -a rand | tail -n 7
echo "!!!!!!!!!Memory size: 150!!!!!!!!!"
./sim -f traceprogs/tr-blocked.ref -m 150 -s 3000 -a rand | tail -n 7
echo "!!!!!!!!!Memory size: 200!!!!!!!!!"
./sim -f traceprogs/tr-blocked.ref -m 200 -s 3000 -a rand | tail -n 7
echo
echo "*********fib*********"
echo "!!!!!!!!!Memory size: 50!!!!!!!!!"
./sim -f traceprogs/tr-fib.ref -m 50 -s 3000 -a rand | tail -n 7
echo "!!!!!!!!!Memory size: 100!!!!!!!!!"
./sim -f traceprogs/tr-fib.ref -m 100 -s 3000 -a rand | tail -n 7
echo "!!!!!!!!!Memory size: 150!!!!!!!!!"
./sim -f traceprogs/tr-fib.ref -m 150 -s 3000 -a rand | tail -n 7
echo "!!!!!!!!!Memory size: 200!!!!!!!!!"
./sim -f traceprogs/tr-fib.ref -m 200 -s 3000 -a rand | tail -n 7
echo "-------------- Results for FIFO --------------"
echo "*********simpleloop*********"
echo "!!!!!!!!!Memory size: 50!!!!!!!!!"
./sim -f traceprogs/tr-simpleloop.ref -m 50 -s 3000 -a fifo | tail -n 7
echo "!!!!!!!!!Memory size: 100!!!!!!!!!"
./sim -f traceprogs/tr-simpleloop.ref -m 100 -s 3000 -a fifo | tail -n 7
echo "!!!!!!!!!Memory size: 150!!!!!!!!!"
./sim -f traceprogs/tr-simpleloop.ref -m 150 -s 3000 -a fifo | tail -n 7
echo "!!!!!!!!!Memory size: 200!!!!!!!!!"
./sim -f traceprogs/tr-simpleloop.ref -m 200 -s 3000 -a fifo | tail -n 7
echo
echo "*********matmul*********"
echo "!!!!!!!!!Memory size: 50!!!!!!!!!"
./sim -f traceprogs/tr-matmul.ref -m 50 -s 3000 -a fifo | tail -n 7
echo "!!!!!!!!!Memory size: 100!!!!!!!!!"
./sim -f traceprogs/tr-matmul.ref -m 100 -s 3000 -a fifo | tail -n 7
echo "!!!!!!!!!Memory size: 150!!!!!!!!!"
./sim -f traceprogs/tr-matmul.ref -m 150 -s 3000 -a fifo | tail -n 7
echo "!!!!!!!!!Memory size: 200!!!!!!!!!"
./sim -f traceprogs/tr-matmul.ref -m 200 -s 3000 -a fifo | tail -n 7
echo
echo "*********blocked*********"
echo "!!!!!!!!!Memory size: 50!!!!!!!!!"
./sim -f traceprogs/tr-blocked.ref -m 50 -s 3000 -a fifo | tail -n 7
echo "!!!!!!!!!Memory size: 100!!!!!!!!!"
./sim -f traceprogs/tr-blocked.ref -m 100 -s 3000 -a fifo | tail -n 7
echo "!!!!!!!!!Memory size: 150!!!!!!!!!"
./sim -f traceprogs/tr-blocked.ref -m 150 -s 3000 -a fifo | tail -n 7
echo "!!!!!!!!!Memory size: 200!!!!!!!!!"
./sim -f traceprogs/tr-blocked.ref -m 200 -s 3000 -a fifo | tail -n 7
echo
echo "*********fib*********"
echo "!!!!!!!!!Memory size: 50!!!!!!!!!"
./sim -f traceprogs/tr-fib.ref -m 50 -s 3000 -a fifo | tail -n 7
echo "!!!!!!!!!Memory size: 100!!!!!!!!!"
./sim -f traceprogs/tr-fib.ref -m 100 -s 3000 -a fifo | tail -n 7
echo "!!!!!!!!!Memory size: 150!!!!!!!!!"
./sim -f traceprogs/tr-fib.ref -m 150 -s 3000 -a fifo | tail -n 7
echo "!!!!!!!!!Memory size: 200!!!!!!!!!"
./sim -f traceprogs/tr-fib.ref -m 200 -s 3000 -a fifo | tail -n 7
echo "-------------- Results for LRU --------------"
echo "*********simpleloop*********"
echo "!!!!!!!!!Memory size: 50!!!!!!!!!"
./sim -f traceprogs/tr-simpleloop.ref -m 50 -s 3000 -a lru | tail -n 7
echo "!!!!!!!!!Memory size: 100!!!!!!!!!"
./sim -f traceprogs/tr-simpleloop.ref -m 100 -s 3000 -a lru | tail -n 7
echo "!!!!!!!!!Memory size: 150!!!!!!!!!"
./sim -f traceprogs/tr-simpleloop.ref -m 150 -s 3000 -a lru | tail -n 7
echo "!!!!!!!!!Memory size: 200!!!!!!!!!"
./sim -f traceprogs/tr-simpleloop.ref -m 200 -s 3000 -a lru | tail -n 7
echo
echo "*********matmul*********"
echo "!!!!!!!!!Memory size: 50!!!!!!!!!"
./sim -f traceprogs/tr-matmul.ref -m 50 -s 3000 -a lru | tail -n 7
echo "!!!!!!!!!Memory size: 100!!!!!!!!!"
./sim -f traceprogs/tr-matmul.ref -m 100 -s 3000 -a lru | tail -n 7
echo "!!!!!!!!!Memory size: 150!!!!!!!!!"
./sim -f traceprogs/tr-matmul.ref -m 150 -s 3000 -a lru | tail -n 7
echo "!!!!!!!!!Memory size: 200!!!!!!!!!"
./sim -f traceprogs/tr-matmul.ref -m 200 -s 3000 -a lru | tail -n 7
echo
echo "*********blocked*********"
echo "!!!!!!!!!Memory size: 50!!!!!!!!!"
./sim -f traceprogs/tr-blocked.ref -m 50 -s 3000 -a lru | tail -n 7
echo "!!!!!!!!!Memory size: 100!!!!!!!!!"
./sim -f traceprogs/tr-blocked.ref -m 100 -s 3000 -a lru | tail -n 7
echo "!!!!!!!!!Memory size: 150!!!!!!!!!"
./sim -f traceprogs/tr-blocked.ref -m 150 -s 3000 -a lru | tail -n 7
echo "!!!!!!!!!Memory size: 200!!!!!!!!!"
./sim -f traceprogs/tr-blocked.ref -m 200 -s 3000 -a lru | tail -n 7
echo
echo "*********fib*********"
echo "!!!!!!!!!Memory size: 50!!!!!!!!!"
./sim -f traceprogs/tr-fib.ref -m 50 -s 3000 -a lru | tail -n 7
echo "!!!!!!!!!Memory size: 100!!!!!!!!!"
./sim -f traceprogs/tr-fib.ref -m 100 -s 3000 -a lru | tail -n 7
echo "!!!!!!!!!Memory size: 150!!!!!!!!!"
./sim -f traceprogs/tr-fib.ref -m 150 -s 3000 -a lru | tail -n 7
echo "!!!!!!!!!Memory size: 200!!!!!!!!!"
./sim -f traceprogs/tr-fib.ref -m 200 -s 3000 -a lru | tail -n 7
echo "-------------- Results for clock --------------"
echo "*********simpleloop*********"
echo "!!!!!!!!!Memory size: 50!!!!!!!!!"
./sim -f traceprogs/tr-simpleloop.ref -m 50 -s 3000 -a clock | tail -n 7
echo "!!!!!!!!!Memory size: 100!!!!!!!!!"
./sim -f traceprogs/tr-simpleloop.ref -m 100 -s 3000 -a clock | tail -n 7
echo "!!!!!!!!!Memory size: 150!!!!!!!!!"
./sim -f traceprogs/tr-simpleloop.ref -m 150 -s 3000 -a clock | tail -n 7
echo "!!!!!!!!!Memory size: 200!!!!!!!!!"
./sim -f traceprogs/tr-simpleloop.ref -m 200 -s 3000 -a clock | tail -n 7
echo
echo "*********matmul*********"
echo "!!!!!!!!!Memory size: 50!!!!!!!!!"
./sim -f traceprogs/tr-matmul.ref -m 50 -s 3000 -a clock | tail -n 7
echo "!!!!!!!!!Memory size: 100!!!!!!!!!"
./sim -f traceprogs/tr-matmul.ref -m 100 -s 3000 -a clock | tail -n 7
echo "!!!!!!!!!Memory size: 150!!!!!!!!!"
./sim -f traceprogs/tr-matmul.ref -m 150 -s 3000 -a clock | tail -n 7
echo "!!!!!!!!!Memory size: 200!!!!!!!!!"
./sim -f traceprogs/tr-matmul.ref -m 200 -s 3000 -a clock | tail -n 7
echo
echo "*********blocked*********"
echo "!!!!!!!!!Memory size: 50!!!!!!!!!"
./sim -f traceprogs/tr-blocked.ref -m 50 -s 3000 -a clock | tail -n 7
echo "!!!!!!!!!Memory size: 100!!!!!!!!!"
./sim -f traceprogs/tr-blocked.ref -m 100 -s 3000 -a clock | tail -n 7
echo "!!!!!!!!!Memory size: 150!!!!!!!!!"
./sim -f traceprogs/tr-blocked.ref -m 150 -s 3000 -a clock | tail -n 7
echo "!!!!!!!!!Memory size: 200!!!!!!!!!"
./sim -f traceprogs/tr-blocked.ref -m 200 -s 3000 -a clock | tail -n 7
echo
echo "*********fib*********"
echo "!!!!!!!!!Memory size: 50!!!!!!!!!"
./sim -f traceprogs/tr-fib.ref -m 50 -s 3000 -a clock | tail -n 7
echo "!!!!!!!!!Memory size: 100!!!!!!!!!"
./sim -f traceprogs/tr-fib.ref -m 100 -s 3000 -a clock | tail -n 7
echo "!!!!!!!!!Memory size: 150!!!!!!!!!"
./sim -f traceprogs/tr-fib.ref -m 150 -s 3000 -a clock | tail -n 7
echo "!!!!!!!!!Memory size: 200!!!!!!!!!"
./sim -f traceprogs/tr-fib.ref -m 200 -s 3000 -a clock | tail -n 7
echo "----------------------------------------------"