#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/mqbase.o \
	${OBJECTDIR}/src/mqdump.o \
	${OBJECTDIR}/src/mqtype.o \
	${OBJECTDIR}/src/rename_for_new_project.o \
	${OBJECTDIR}/test/src/t_main_000.o \
	${OBJECTDIR}/test/src/t_mqbase_000.o \
	${OBJECTDIR}/test/src/t_mqbase_001.o \
	${OBJECTDIR}/test/src/t_mqbase_002.o \
	${OBJECTDIR}/test/src/t_mqbase_003.o \
	${OBJECTDIR}/test/src/t_mqbase_004.o \
	${OBJECTDIR}/test/src/t_mqbase_005.o \
	${OBJECTDIR}/test/src/t_mqbase_006.o \
	${OBJECTDIR}/test/src/t_mqbase_007.o \
	${OBJECTDIR}/test/src/t_template_000.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmqUtil.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmqUtil.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmqUtil.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/main.o: src/main.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.c

${OBJECTDIR}/src/mqbase.o: src/mqbase.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/mqbase.o src/mqbase.c

${OBJECTDIR}/src/mqdump.o: src/mqdump.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/mqdump.o src/mqdump.c

${OBJECTDIR}/src/mqtype.o: src/mqtype.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/mqtype.o src/mqtype.c

${OBJECTDIR}/src/rename_for_new_project.o: src/rename_for_new_project.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/rename_for_new_project.o src/rename_for_new_project.c

${OBJECTDIR}/test/src/t_main_000.o: test/src/t_main_000.c 
	${MKDIR} -p ${OBJECTDIR}/test/src
	${RM} $@.d
	$(COMPILE.c) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/src/t_main_000.o test/src/t_main_000.c

${OBJECTDIR}/test/src/t_mqbase_000.o: test/src/t_mqbase_000.c 
	${MKDIR} -p ${OBJECTDIR}/test/src
	${RM} $@.d
	$(COMPILE.c) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/src/t_mqbase_000.o test/src/t_mqbase_000.c

${OBJECTDIR}/test/src/t_mqbase_001.o: test/src/t_mqbase_001.c 
	${MKDIR} -p ${OBJECTDIR}/test/src
	${RM} $@.d
	$(COMPILE.c) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/src/t_mqbase_001.o test/src/t_mqbase_001.c

${OBJECTDIR}/test/src/t_mqbase_002.o: test/src/t_mqbase_002.c 
	${MKDIR} -p ${OBJECTDIR}/test/src
	${RM} $@.d
	$(COMPILE.c) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/src/t_mqbase_002.o test/src/t_mqbase_002.c

${OBJECTDIR}/test/src/t_mqbase_003.o: test/src/t_mqbase_003.c 
	${MKDIR} -p ${OBJECTDIR}/test/src
	${RM} $@.d
	$(COMPILE.c) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/src/t_mqbase_003.o test/src/t_mqbase_003.c

${OBJECTDIR}/test/src/t_mqbase_004.o: test/src/t_mqbase_004.c 
	${MKDIR} -p ${OBJECTDIR}/test/src
	${RM} $@.d
	$(COMPILE.c) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/src/t_mqbase_004.o test/src/t_mqbase_004.c

${OBJECTDIR}/test/src/t_mqbase_005.o: test/src/t_mqbase_005.c 
	${MKDIR} -p ${OBJECTDIR}/test/src
	${RM} $@.d
	$(COMPILE.c) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/src/t_mqbase_005.o test/src/t_mqbase_005.c

${OBJECTDIR}/test/src/t_mqbase_006.o: test/src/t_mqbase_006.c 
	${MKDIR} -p ${OBJECTDIR}/test/src
	${RM} $@.d
	$(COMPILE.c) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/src/t_mqbase_006.o test/src/t_mqbase_006.c

${OBJECTDIR}/test/src/t_mqbase_007.o: test/src/t_mqbase_007.c 
	${MKDIR} -p ${OBJECTDIR}/test/src
	${RM} $@.d
	$(COMPILE.c) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/src/t_mqbase_007.o test/src/t_mqbase_007.c

${OBJECTDIR}/test/src/t_template_000.o: test/src/t_template_000.c 
	${MKDIR} -p ${OBJECTDIR}/test/src
	${RM} $@.d
	$(COMPILE.c) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/src/t_template_000.o test/src/t_template_000.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmqUtil.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
