#!/bin/bash

make clean
make shared && make clean
make static && make clean
make

