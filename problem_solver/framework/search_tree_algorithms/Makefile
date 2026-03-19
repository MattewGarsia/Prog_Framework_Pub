GCC := g++
GCCFLAGS := -std=c++17 -Wall -Wextra -I. -Igeneral
TARGET := main.exe
SRC := main.cpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(GCC) $(GCCFLAGS) -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	if exist $(TARGET) del /Q $(TARGET)