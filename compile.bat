@echo off
setlocal enabledelayedexpansion

rem Set variables
set CC=g++
set SRCDIR=src
set BUILDDIR=build

rem Check if a target filename is provided as an argument
if "%1"=="" (
    echo Usage: %0 target_filename, default: App
    set TARGET=App
)

rem Set the target filename from the first argument
if NOT "%1"=="" set TARGET=%1

set SRCEXT=cpp
set CFLAGS=-g -Wno-deprecated -std=c++17 -Wall
set INC=-I .

rem Detect the OS and set LIB and SOURCES accordingly
rem For simplicity, we assume we're on Windows
set LIB=-lopengl32 -lglu32 -lfreeglut

rem Find all source files
for /r %SRCDIR% %%f in (*.cpp) do (
    set SOURCES=!SOURCES! %%f
)

rem Convert SOURCES to OBJECTS
for %%f in (!SOURCES!) do (
    set obj=%%f
    set obj=!obj:%SRCDIR%=%BUILDDIR%!
    set obj=!obj:.cpp=.o!
    set OBJECTS=!OBJECTS! !obj!
)

set buildAll=TRUE


rem Compile each source file to an object file
for %%f in (!SOURCES!) do (
    set obj=%%f
    set obj=!obj:%SRCDIR%=%BUILDDIR%!
    set obj=!obj:.cpp=.o!
    if not exist "!obj!" mkdir "!obj!\.."
    rem echo %CC% %CFLAGS% %INC% -c -o "!obj!" "%%f"
	rem echo "!obj!"
    if %buildAll%==TRUE ( %CC% %CFLAGS% %INC% -c -o "!obj!" "%%f" )
	if %%f == %cd%\%SRCDIR%\%TARGET%.cpp ( %CC% %CFLAGS% %INC% -c -o "!obj!" "%%f" )
)

	
rem Link the object files into the final executable
rem echo %CC% -o %TARGET% !OBJECTS! %LIB%
%CC% -o %TARGET%.exe !OBJECTS! %LIB%

rem Clean up
echo Cleaning...
if exist %BUILDDIR% rmdir /s /q %BUILDDIR%
if exist %TARGET% del %TARGET%
