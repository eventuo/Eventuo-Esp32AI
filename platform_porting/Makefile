# Variables to control Makefile operation

CC = g++
CFLAGS = -fpermissive -pthread -std=gnu++17 -g

MAIN_SRCPATH = ../main/
MAIN_INCLUDEPATH = ../components/briand_ai/include/
MAIN_OUTNAME = main

LIB_SRCPATH = ../components/briand_ai/
LIB_INCLUDEPATH = ../components/briand_ai/include/
LIB_OUTNAME = briand_ai

all:

# Build library first
# -c option means no linking
	
	$(CC) -c $(LIB_SRCPATH)*.cpp -I$(LIB_INCLUDEPA