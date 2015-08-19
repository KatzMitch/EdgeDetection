CC=g++
CFLAGS=-I. -O2
DEPS = Image.hpp Kernel.hpp
DEMOOBJ = Image.o Kernel.o main.o
ANALYZEOBJ = Image.o Kernel.o CheckParam.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

imageProcessingDemo: $(DEMOOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

analyze: $(ANALYZEOBJ)
	$(CC) -o $@ $^ $(CFLAGS)