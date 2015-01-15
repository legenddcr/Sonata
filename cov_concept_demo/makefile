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
SRC_FILES1=../Unity/src/unity.c src/example.c test/test1.c test/no_ruby/test1_runner.c
SRC_FILES2=../Unity/src/unity.c src/example.c test/test2.c test/no_ruby/test2_runner.c

INC_DIRS=-Isrc -I../Unity/src
SYMBOLS=-DTEST -Wall -Wstrict-prototypes -g -O0  -fprofile-arcs -ftest-coverage

ifeq ($(OS),Windows_NT)
	CLEANUP = del /F /Q build\* && del /F /Q $(TARGET1) && del /F /Q $(TARGET2)
else
	CLEANUP = rm -f build/*.o ; rm -f $(TARGET1) ; rm -f $(TARGET2) ; rm -f *.gc* ; rm -f *.info ; rm -rf mocks ; rm -f test/no_ruby/* ; rm -rf *_cov_*
endif

all: clean default

default:
	ruby ../Unity/auto/generate_test_runner.rb test/test1.c test/no_ruby/test1_runner.c
#	ruby ../Unity/auto/generate_test_runner.rb test/test2.c test/no_ruby/test2_runner.c

	$(C_COMPILER) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES1) -o ./$(TARGET1)
	./$(TARGET1)
	gcov -a -b -c ./src/example.c -o 'example'
#	lcov --directory . --zerocounters
	lcov -c -d . -t 'example' -o example.info -b .
	genhtml -o decision_cov_result ./example.info --frames --title "Simple test" --show-details --legend

#	$(C_COMPILER) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES2) -o ./$(TARGET2)
#	./$(TARGET2)
#	gcov ./src/example.c -o 'example'
#	lcov -d . -t 'example' -o example2.info -b . -c
#	genhtml -o condition_cov_result ./example2.info


clean:
	$(CLEANUP)

