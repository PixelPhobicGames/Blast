    ifeq ($(OS),Windows_NT)
        PLATFORM = windows
    else
		ifeq ($(UNAMEOS),Linux)
			PLATFORM = linux
		endif
	endif
  ifeq ($(PLATFORM),windows)
    CC = C:\raylib\mingw\bin\gcc.exe
    exename ?= Lost.exe
    CFLAGS  = -s -static -Os -std=c99 -Wall -Iexternal -DPLATFORM_DESKTOP -lopengl32 -lraylib -lgdi32 -lwinmm
  endif
  ifeq ($(PLATFORM),linux)
    CC = gcc
    exename ?= Lost
    CFLAGS  = -s -static -Os -std=c99 -Wall -Iexternal -DPLATFORM_DESKTOP -lraylib -lGL -lm -lpthread -ldl -lrt -X11
  endif

  all: $(TARGET)
	$(CC) Blast.c -o $(exename) $(CFLAGS)
