################################################################################
# makefile for test util
################################################################################

MAKE_INCLUDE_PATH=mk.inc

# ------------------------------------------------------------------------------
# Compiler and BIT
# ------------------------------------------------------------------------------
CC=gcc
BIT = 64

# ------------------------------------------------------------------------------
# debugger
# ------------------------------------------------------------------------------
DBGOPT = -g

# ------------------------------------------------------------------------------
# sources
# ------------------------------------------------------------------------------
SOURCES = mqbase.c mqdump.c mqtype.c

MQ_GENERATED_SRC = mqreason.c

# ------------------------------------------------------------------------------
# libraries
# ------------------------------------------------------------------------------
AROWN = 
LSOWN = msgcat sogen

MQLIB = use
MQINST = /opt/mqm/750

# ------------------------------------------------------------------------------
# main source
# ------------------------------------------------------------------------------
MAIN = 

# ------------------------------------------------------------------------------
# BINARY
# ------------------------------------------------------------------------------
BINARY = 

# ------------------------------------------------------------------------------
# goal libraries dynamic & static 
# ------------------------------------------------------------------------------
LIBRARY = libmqutil.so 
ARCHIVE  =  libmqutil.a

# ------------------------------------------------------------------------------
# rollout includes
# ------------------------------------------------------------------------------
ROLLOUT_INC = mqbase.h mqreason.h mqtype.h

# ------------------------------------------------------------------------------
# general includes
# ------------------------------------------------------------------------------
include $(MAKE_INCLUDE_PATH)/general.modules.mk

# ------------------------------------------------------------------------------
# mqreason
# ------------------------------------------------------------------------------
#include $(MAKE_INCLUDE_PATH)/mq.mk

cleanlocal :
	$(RM) include/mqreason.h
	$(RM) src/mqreason.c

# ------------------------------------------------------------------------------
# tests
# ------------------------------------------------------------------------------
TEST = t_mqbase_000 t_mqbase_001 t_mqbase_002 t_mqbase_003 t_mqbase_004  \
       t_mqbase_006 t_mqbase_007   \
       t_mqbase_010 t_mqbase_011 
       #t_mqbase_005 

include $(MAKE_INCLUDE_PATH)/test.mk

