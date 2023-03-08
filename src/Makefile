OBJ_TEST_DIR = obj_test/

GCOV_DIR = gcov_report

TEST_TARGET = test

DOC_INFO = doc.info

SRC_TEST =	test.c \
 			ft_split.c \
			list_utils.c \
			parse_value.c \
			parser.c \
			utils.c \
			transformation.c \
			clean.c \

OBJ_TEST = $(SRC_TEST:%.c=$(OBJ_TEST_DIR)%.o)

GCOV_FILES = $(SRC_TEST:%.c=$(OBJ_TEST_DIR)%.gcda)

HEADER = 3DViewer/include/viewer.h

RM = rm -rf

CC = gcc

CFLAGS = -Wall -Wextra -Werror

GCOV = -fprofile-arcs -ftest-coverage

VPATH = 3DViewer/src 3DViewer/src/parser

.PHONY : all install uninstall clean dvi dist tests gcov_report

all : install

install :
		@cd 3DViewer && qmake6
		@$(MAKE) -C ./3DViewer

uninstall :
		$(RM) $(GCOV_DIR)
		$(RM) $(TEST_TARGET)
		if [ -a 3DViewer/Makefile ]; then  $(MAKE) -C ./3DViewer distclean ; fi;
		$(MAKE) clean_2
		$(RM) doc.info
		$(RM) settings_3DViewer.ini

clean :
		if [ -a 3DViewer/Makefile ]; then  $(MAKE) -C ./3DViewer clean ; fi;
		$(MAKE) clean_2

clean_2 :
		$(RM) 3DViewer/obj
		$(RM) 3DViewer/.qm
		$(RM) 3DViewer/.qmake.stash
		$(RM) 3DViewer/qmake_qmake_qm_files.qrc
		$(RM) $(OBJ_TEST_DIR)

dvi: $(DOC_INFO)

$(DOC_INFO) :  3DViewer/src/doc.texi
		Makeinfo $< -o doc.info

dist :
		$(shell mkdir 3DViewer-1.0)
		$(shell cp -r 3DViewer 3DViewer-1.0)
		$(shell cp Makefile 3DViewer-1.0)
		$(MAKE) -C 3DViewer-1.0 uninstall
		$(shell tar -czf 3DViewer-1.0.tar 3DViewer-1.0)
		@$(RM) 3DViewer-1.0

$(TEST_TARGET) : $(OBJ_TEST)
		$(CC) $(OBJ_TEST) $(GCOV) -lm -o $(TEST_TARGET)

$(OBJ_TEST_DIR)%.o:%.c $(HEADER)
		mkdir -p $(OBJ_TEST_DIR)
		$(CC) $(CFLAGS) $(GCOV) -c $< -o $@

tests : $(TEST_TARGET)

gcov_report : tests
		./test
		mkdir -p $(GCOV_DIR)
		gcovr -r . --html	--html-details -o $(GCOV_DIR)/coverage_report.html

code_style :
	clang-format -n 3DViewer/include/*.h 3DViewer/src/*.c 3DViewer/src/*.cpp 3DViewer/src/parser/*.c