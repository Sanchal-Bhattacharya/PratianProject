# Global Connect (gc)
#
# Make configuration for compiler, flags and common directories
# Author: Anand

.PHONY:clean localinstall all debug debugBuild release releaseBuild buildMain

CXX                 = g++
CXXFLAGS            = -std=c++11 -g

# Project specific directory paths
MKINC               := 1

# Common directory path
PROJECT_ROOT        := $(PWD)
BIN_DIR             := $(PROJECT_ROOT)/bin
LIB_DIR             := $(PROJECT_ROOT)/lib
LIB_SRC             := $(LIB_DIR)/src
APPSERVER           := $(PROJECT_ROOT)/appserver


# Include directory
LIB_INC             := $(LIB_DIR)/inc

# Public Root Include Dir
PUBLIC_INC          := $(LIB_DIR)/public

# Project Directories
ENTITIES_DIR        := $(LIB_SRC)/entities
UTILS_DIR           := $(LIB_SRC)/utils
DBF_DIR             := $(LIB_SRC)/dbf
DAO_DIR             := $(LIB_SRC)/dao
BUSINESS_DIR        := $(LIB_SRC)/business
APPSERVER_DIR       := $(APPSERVER)/src


# Libarary Include Dir
LOG_INC             := $(LIB_INC)/utils/log
DBF_INC             := $(LIB_INC)/dbf
DAO_INC             := $(LIB_INC)/dao
BUSINESS_INC_DIR    := $(LIB_INC)/business
APPSERVER_INC       := $(APPSERVER)/inc
COMMON_INC          := $(LIB_INC)/common


# Projects Src directory
ENTITIES_SRC        := $(ENTITIES_DIR)
UTILS_SRC           := $(UTILS_DIR)
DBF_SRC             := $(DBF_DIR)
DAO_SRC             := $(DAO_DIR)
BUSINESS_SRC        := $(BUSINESS_DIR)
APPSERVER_SRC       := $(APPSERVER_DIR)

# Public Includes
ENTITIES_PUB_INC    := $(PUBLIC_INC)/entities
LOG_PUB_INC         := $(PUBLIC_INC)/utils
EXP_PUB_INC         := $(PUBLIC_INC)/exception
BUSINESS_PUB_INC    := $(PUBLIC_INC)/business

# Config directory
CONFIG_DIR          := $(PROJECT_ROOT)/config

# Oracle SDK include path
ORACLE_INC          := /usr/include/oracle/11.2/client64

#Oracle Library path
ORACLE_LIB          := /usr/lib/oracle/11.2/client64/lib

export