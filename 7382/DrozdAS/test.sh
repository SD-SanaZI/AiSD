#!/bin/bash
gcc ./Sourse/lab1.c -o Lab1
echo -e '_______\nTest 1:'
cat ./Tests/test1.txt
echo -e '_______\nTesting:\n'
./Lab1 < ./Tests/test1.txt
echo -e ''
echo -e '_______\nTest 2:'
cat ./Tests/test2.txt
echo -e '_______\nTesting:\n'
./Lab1 < ./Tests/test2.txt
echo -e ''
echo -e '_______\nTest 3:'
cat ./Tests/test3.txt
echo -e '_______\nTesting:\n'
./Lab1 < ./Tests/test3.txt
echo -e ''
echo -e '_______\nTest 4:'
cat ./Tests/test4.txt
echo -e '_______\nTesting:\n'
./Lab1 < ./Tests/test4.txt
echo -e ''
echo -e '_______\nTest 5:'
cat ./Tests/test5.txt
echo -e '_______\nTesting:\n'
./Lab1 < ./Tests/test5.txt
