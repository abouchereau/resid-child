# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/maurice/www/resid-child

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/maurice/www/resid-child

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components
.PHONY : list_install_components/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/maurice/www/resid-child/CMakeFiles /home/maurice/www/resid-child//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/maurice/www/resid-child/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named resid

# Build rule for target.
resid: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 resid
.PHONY : resid

# fast build rule for target.
resid/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/build
.PHONY : resid/fast

envelope.o: envelope.cc.o
.PHONY : envelope.o

# target to build an object file
envelope.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/envelope.cc.o
.PHONY : envelope.cc.o

envelope.i: envelope.cc.i
.PHONY : envelope.i

# target to preprocess a source file
envelope.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/envelope.cc.i
.PHONY : envelope.cc.i

envelope.s: envelope.cc.s
.PHONY : envelope.s

# target to generate assembly for a file
envelope.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/envelope.cc.s
.PHONY : envelope.cc.s

extfilt.o: extfilt.cc.o
.PHONY : extfilt.o

# target to build an object file
extfilt.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/extfilt.cc.o
.PHONY : extfilt.cc.o

extfilt.i: extfilt.cc.i
.PHONY : extfilt.i

# target to preprocess a source file
extfilt.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/extfilt.cc.i
.PHONY : extfilt.cc.i

extfilt.s: extfilt.cc.s
.PHONY : extfilt.s

# target to generate assembly for a file
extfilt.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/extfilt.cc.s
.PHONY : extfilt.cc.s

filter.o: filter.cc.o
.PHONY : filter.o

# target to build an object file
filter.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/filter.cc.o
.PHONY : filter.cc.o

filter.i: filter.cc.i
.PHONY : filter.i

# target to preprocess a source file
filter.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/filter.cc.i
.PHONY : filter.cc.i

filter.s: filter.cc.s
.PHONY : filter.s

# target to generate assembly for a file
filter.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/filter.cc.s
.PHONY : filter.cc.s

pot.o: pot.cc.o
.PHONY : pot.o

# target to build an object file
pot.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/pot.cc.o
.PHONY : pot.cc.o

pot.i: pot.cc.i
.PHONY : pot.i

# target to preprocess a source file
pot.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/pot.cc.i
.PHONY : pot.cc.i

pot.s: pot.cc.s
.PHONY : pot.s

# target to generate assembly for a file
pot.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/pot.cc.s
.PHONY : pot.cc.s

sid.o: sid.cc.o
.PHONY : sid.o

# target to build an object file
sid.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/sid.cc.o
.PHONY : sid.cc.o

sid.i: sid.cc.i
.PHONY : sid.i

# target to preprocess a source file
sid.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/sid.cc.i
.PHONY : sid.cc.i

sid.s: sid.cc.s
.PHONY : sid.s

# target to generate assembly for a file
sid.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/sid.cc.s
.PHONY : sid.cc.s

version.o: version.cc.o
.PHONY : version.o

# target to build an object file
version.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/version.cc.o
.PHONY : version.cc.o

version.i: version.cc.i
.PHONY : version.i

# target to preprocess a source file
version.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/version.cc.i
.PHONY : version.cc.i

version.s: version.cc.s
.PHONY : version.s

# target to generate assembly for a file
version.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/version.cc.s
.PHONY : version.cc.s

voice.o: voice.cc.o
.PHONY : voice.o

# target to build an object file
voice.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/voice.cc.o
.PHONY : voice.cc.o

voice.i: voice.cc.i
.PHONY : voice.i

# target to preprocess a source file
voice.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/voice.cc.i
.PHONY : voice.cc.i

voice.s: voice.cc.s
.PHONY : voice.s

# target to generate assembly for a file
voice.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/voice.cc.s
.PHONY : voice.cc.s

wave.o: wave.cc.o
.PHONY : wave.o

# target to build an object file
wave.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave.cc.o
.PHONY : wave.cc.o

wave.i: wave.cc.i
.PHONY : wave.i

# target to preprocess a source file
wave.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave.cc.i
.PHONY : wave.cc.i

wave.s: wave.cc.s
.PHONY : wave.s

# target to generate assembly for a file
wave.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave.cc.s
.PHONY : wave.cc.s

wave6581_PST.o: wave6581_PST.cc.o
.PHONY : wave6581_PST.o

# target to build an object file
wave6581_PST.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave6581_PST.cc.o
.PHONY : wave6581_PST.cc.o

wave6581_PST.i: wave6581_PST.cc.i
.PHONY : wave6581_PST.i

# target to preprocess a source file
wave6581_PST.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave6581_PST.cc.i
.PHONY : wave6581_PST.cc.i

wave6581_PST.s: wave6581_PST.cc.s
.PHONY : wave6581_PST.s

# target to generate assembly for a file
wave6581_PST.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave6581_PST.cc.s
.PHONY : wave6581_PST.cc.s

wave6581_PS_.o: wave6581_PS_.cc.o
.PHONY : wave6581_PS_.o

# target to build an object file
wave6581_PS_.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave6581_PS_.cc.o
.PHONY : wave6581_PS_.cc.o

wave6581_PS_.i: wave6581_PS_.cc.i
.PHONY : wave6581_PS_.i

# target to preprocess a source file
wave6581_PS_.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave6581_PS_.cc.i
.PHONY : wave6581_PS_.cc.i

wave6581_PS_.s: wave6581_PS_.cc.s
.PHONY : wave6581_PS_.s

# target to generate assembly for a file
wave6581_PS_.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave6581_PS_.cc.s
.PHONY : wave6581_PS_.cc.s

wave6581_P_T.o: wave6581_P_T.cc.o
.PHONY : wave6581_P_T.o

# target to build an object file
wave6581_P_T.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave6581_P_T.cc.o
.PHONY : wave6581_P_T.cc.o

wave6581_P_T.i: wave6581_P_T.cc.i
.PHONY : wave6581_P_T.i

# target to preprocess a source file
wave6581_P_T.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave6581_P_T.cc.i
.PHONY : wave6581_P_T.cc.i

wave6581_P_T.s: wave6581_P_T.cc.s
.PHONY : wave6581_P_T.s

# target to generate assembly for a file
wave6581_P_T.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave6581_P_T.cc.s
.PHONY : wave6581_P_T.cc.s

wave6581__ST.o: wave6581__ST.cc.o
.PHONY : wave6581__ST.o

# target to build an object file
wave6581__ST.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave6581__ST.cc.o
.PHONY : wave6581__ST.cc.o

wave6581__ST.i: wave6581__ST.cc.i
.PHONY : wave6581__ST.i

# target to preprocess a source file
wave6581__ST.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave6581__ST.cc.i
.PHONY : wave6581__ST.cc.i

wave6581__ST.s: wave6581__ST.cc.s
.PHONY : wave6581__ST.s

# target to generate assembly for a file
wave6581__ST.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave6581__ST.cc.s
.PHONY : wave6581__ST.cc.s

wave8580_PST.o: wave8580_PST.cc.o
.PHONY : wave8580_PST.o

# target to build an object file
wave8580_PST.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave8580_PST.cc.o
.PHONY : wave8580_PST.cc.o

wave8580_PST.i: wave8580_PST.cc.i
.PHONY : wave8580_PST.i

# target to preprocess a source file
wave8580_PST.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave8580_PST.cc.i
.PHONY : wave8580_PST.cc.i

wave8580_PST.s: wave8580_PST.cc.s
.PHONY : wave8580_PST.s

# target to generate assembly for a file
wave8580_PST.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave8580_PST.cc.s
.PHONY : wave8580_PST.cc.s

wave8580_PS_.o: wave8580_PS_.cc.o
.PHONY : wave8580_PS_.o

# target to build an object file
wave8580_PS_.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave8580_PS_.cc.o
.PHONY : wave8580_PS_.cc.o

wave8580_PS_.i: wave8580_PS_.cc.i
.PHONY : wave8580_PS_.i

# target to preprocess a source file
wave8580_PS_.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave8580_PS_.cc.i
.PHONY : wave8580_PS_.cc.i

wave8580_PS_.s: wave8580_PS_.cc.s
.PHONY : wave8580_PS_.s

# target to generate assembly for a file
wave8580_PS_.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave8580_PS_.cc.s
.PHONY : wave8580_PS_.cc.s

wave8580_P_T.o: wave8580_P_T.cc.o
.PHONY : wave8580_P_T.o

# target to build an object file
wave8580_P_T.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave8580_P_T.cc.o
.PHONY : wave8580_P_T.cc.o

wave8580_P_T.i: wave8580_P_T.cc.i
.PHONY : wave8580_P_T.i

# target to preprocess a source file
wave8580_P_T.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave8580_P_T.cc.i
.PHONY : wave8580_P_T.cc.i

wave8580_P_T.s: wave8580_P_T.cc.s
.PHONY : wave8580_P_T.s

# target to generate assembly for a file
wave8580_P_T.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave8580_P_T.cc.s
.PHONY : wave8580_P_T.cc.s

wave8580__ST.o: wave8580__ST.cc.o
.PHONY : wave8580__ST.o

# target to build an object file
wave8580__ST.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave8580__ST.cc.o
.PHONY : wave8580__ST.cc.o

wave8580__ST.i: wave8580__ST.cc.i
.PHONY : wave8580__ST.i

# target to preprocess a source file
wave8580__ST.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave8580__ST.cc.i
.PHONY : wave8580__ST.cc.i

wave8580__ST.s: wave8580__ST.cc.s
.PHONY : wave8580__ST.s

# target to generate assembly for a file
wave8580__ST.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/resid.dir/build.make CMakeFiles/resid.dir/wave8580__ST.cc.s
.PHONY : wave8580__ST.cc.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... install"
	@echo "... install/local"
	@echo "... install/strip"
	@echo "... list_install_components"
	@echo "... rebuild_cache"
	@echo "... resid"
	@echo "... envelope.o"
	@echo "... envelope.i"
	@echo "... envelope.s"
	@echo "... extfilt.o"
	@echo "... extfilt.i"
	@echo "... extfilt.s"
	@echo "... filter.o"
	@echo "... filter.i"
	@echo "... filter.s"
	@echo "... pot.o"
	@echo "... pot.i"
	@echo "... pot.s"
	@echo "... sid.o"
	@echo "... sid.i"
	@echo "... sid.s"
	@echo "... version.o"
	@echo "... version.i"
	@echo "... version.s"
	@echo "... voice.o"
	@echo "... voice.i"
	@echo "... voice.s"
	@echo "... wave.o"
	@echo "... wave.i"
	@echo "... wave.s"
	@echo "... wave6581_PST.o"
	@echo "... wave6581_PST.i"
	@echo "... wave6581_PST.s"
	@echo "... wave6581_PS_.o"
	@echo "... wave6581_PS_.i"
	@echo "... wave6581_PS_.s"
	@echo "... wave6581_P_T.o"
	@echo "... wave6581_P_T.i"
	@echo "... wave6581_P_T.s"
	@echo "... wave6581__ST.o"
	@echo "... wave6581__ST.i"
	@echo "... wave6581__ST.s"
	@echo "... wave8580_PST.o"
	@echo "... wave8580_PST.i"
	@echo "... wave8580_PST.s"
	@echo "... wave8580_PS_.o"
	@echo "... wave8580_PS_.i"
	@echo "... wave8580_PS_.s"
	@echo "... wave8580_P_T.o"
	@echo "... wave8580_P_T.i"
	@echo "... wave8580_P_T.s"
	@echo "... wave8580__ST.o"
	@echo "... wave8580__ST.i"
	@echo "... wave8580__ST.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

