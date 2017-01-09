#!/bin/sh

LD_PRELOAD=$PWD/profiling.so python benchmark.py
