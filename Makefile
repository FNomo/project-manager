.SILENT:

CPP = g++
CCFLAGS = --std=c++11 -Wall
CCPATH = -I ./src/header
TESTS_COUNTER = 0
TESTS = TestTask TestRookieManager TestExpertManager TestProtoProject TestRunProject

all: init $(TESTS)
	$(info [Makefile] Building done.)

# ----- Initialisation ----- #

init:
ifeq ($(wildcard bin),)
	mkdir bin/
	mkdir bin/obj
	$(info [Makefile] ./bin/ directory has been created)
	$(info [Makefile] ./bin/obj/ directory has been created)
else
	$(info [Makefile] ./bin/ directory already exist)
	$(info [Makefile] ./bin/obj/ directory already exist)
endif
ifeq ($(wildcard log),)
	mkdir log
	$(info [Makefile] ./log/ directory has been created)
else
	$(info [Makefile] ./log/ directory already exist)
endif





TestTask: Task.main Test.test TestTask.test Log.lib Util.lib
	$(CPP) $(CCFLAGS) $(CCPATH) -o $@ $(OBJ_FILE) $(addsuffix .o, $(addprefix bin/obj/, $(basename $^)))
	mv ./$@ bin/
	$(info [Makefile] Class Task can be tested.)

TestRookieManager: RookieManager.main Manager.main Task.main RunProject.main ProtoProject.main Project.main Test.test TestRookieManager.test Log.lib Util.lib
	$(CPP) $(CCFLAGS) $(CCPATH) -o $@ $(addsuffix .o, $(addprefix bin/obj/, $(basename $^)))
	mv ./$@ bin/
	$(info [Makefile] Class RookieManager can be tested.)

TestExpertManager: ExpertManager.main Manager.main Task.main RunProject.main ProtoProject.main Project.main Test.test TestExpertManager.test Log.lib Util.lib
	$(CPP) $(CCFLAGS) $(CCPATH) -o $@ $(addsuffix .o, $(addprefix bin/obj/, $(basename $^)))
	mv ./$@ bin/
	$(info [Makefile] Class ExpertManager can be tested.)

TestProtoProject:	ProtoProject.main	Project.main	Task.main	Test.test	TestProtoProject.test	Log.lib	Util.lib
	$(CPP) $(CCFLAGS) $(CCPATH) -o $@ $(addsuffix .o, $(addprefix bin/obj/, $(basename $^)))
	mv ./$@ bin/
	echo "[Makefile] Class ProtoProject can be tested."

TestRunProject:	RunProject.main	ProtoProject.main	Project.main	Task.main	Test.test	TestRunProject.test	Log.lib	Util.lib
	$(CPP) $(CCFLAGS) $(CCPATH) -o $@ $(addsuffix .o, $(addprefix bin/obj/, $(basename $^)))
	mv ./$@ bin/
	echo "[Makefile] Class RunProject can be tested."





%.test:
	$(CPP) $(CCFLAGS) $(CCPATH) -c src/test/$*.cpp
	mv $*.o bin/obj
	$(info [Makefile] Compiling src/test/$*.cpp. done)

%.lib:
	$(CPP) $(CCFLAGS) $(CCPATH) -c src/lib/$*.cpp
	mv $*.o bin/obj
	$(info [Makefile] Compiling src/lib/$*.cpp. done)

%.main:
	$(CPP) $(CCFLAGS) $(CCPATH) -c src/main/$*.cpp
	mv $*.o bin/obj
	$(info [Makefile] Compiling src/main/$*.cpp. done)





test_All: test_Task test_RookieManager test_ExpertManager  test_ProtoProject test_RunProject
	$(info [Makefile] All tests done.)


test_%:
	./bin/Test$*
	$(info [Makefile] Test for $*.cpp done)


clean	:
	rm -rfv bin
	rm -rfv log
