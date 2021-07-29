#!/bin/sh
echo "Start, please Wait"
g++ main.cpp -o stego `pkg-config --cflags --libs opencv`
echo "Finish, run C++ Project"
./stego
