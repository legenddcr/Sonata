# ==========================================
#   Unity Project - A Test Framework for C
#   Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
#   [Released under MIT License. Please refer to license.txt for details]
# ========================================== 

C_COMPILER=gcc
TARGET_BASE1=test1
TARGET_BASE2=test2
ifeq ($(OS),Windows_NT)
	TARGET_EXTENSION=.exe
else
	TARGET_EXTENSION=.out
endif
TARGET1 = $(TARGET_BASE1)$(TARGET_EXTENSION)
TARGET2 = $(TARGET_BASE2)$(TARGET_EXTENSION)
SRC_FILES1=../Unity/src/unity.c src/ilist_parse.c src/gc.c test/test_ilist_parse.c test/no_ruby/test_ilist_parse_runner.c
SRC_FILES2=../Unity/src/unity.c ~/dev_tools/CMock/src/cmock.c test/no_ruby/Mockgc.c src/ilist_parse.c test/no_ruby/test_ilist_parse_mock_testing.c test/no_ruby/test_ilist_parse_mock_runner.c

# Cmock file is only needed by mock testing
INC_DIRS=-Isrc -I../Unity/src -I/home/chengrui/dev_tools/CMock/src
SYMBOLS=-DTEST -Wall -Wstrict-prototypes -g -O0  -fprofile-arcs -ftest-coverage

ifeq ($(OS),Windows_NT)
	CLEANUP = del /F /Q build\* && del /F /Q $(TARGET1)
else
	CLEANUP = rm -f build/*.o ; rm -f $(TARGET1) ; rm -f $(TARGET2) ; rm -f *.gc* ; rm -f *.info ; rm -rf mocks ; rm -f test/no_ruby/* ; rm -rf cov_result
endif

all: clean default

default:
	ruby ../Unity/auto/generate_test_runner.rb test/test_ilist_parse.c test/no_ruby/test_ilist_parse_runner.c
	ruby ../Unity/auto/generate_test_runner.rb test/test_ilist_parse_mock_testing.c test/no_ruby/test_ilist_parse_mock_runner.c
#http://sourceforge.net/p/cmock/discussion/822277/thread/fdea3b7d
	mkdir -p mocks
	ruby ~/dev_tools/CMock/lib/cmock.rb src/gc.h
	cp -f src/gc.h mocks/
	mv mocks/* test/no_ruby/
	cp -f test/test_ilist_parse_mock_testing.c test/no_ruby/
	$(C_COMPILER) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES1) -o ./$(TARGET1)
	valgrind --tool=memcheck --leak-check=full ./$(TARGET1)
	gcov ./src/ilist_parse.c -o 'ilist_parse1'
#	lcov --directory . --zerocounters
	lcov -d . -t 'ilist_parse' -o ilist_parse1.info -b . -c

	$(C_COMPILER) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES2) -o ./$(TARGET2)
	valgrind --tool=memcheck --leak-check=full ./$(TARGET2)
	gcov ./src/ilist_parse.c -o 'ilist_parse2'
	lcov -d . -t 'ilist_parse' -o ilist_parse2.info -b . -c

	lcov -a ilist_parse1.info -a ilist_parse2.info -o ilist_parse.info
	genhtml -o cov_result ./ilist_parse.info



clean:
	$(CLEANUP)

