OUTPUT_NAME=mocknm.out
COMPILER=g++
CONFIG=`pkg-config --cflags --libs glib-2.0 libnm`
BUILD=$(COMPILER) $^ $(CONFIG) -o $(OUTPUT_NAME)
	
all: mock-nm.cpp configMockNm.cpp test.cpp
	make clean
	git pull
	$(BUILD)

clean:
	rm -f $(OUTPUT_NAME)
