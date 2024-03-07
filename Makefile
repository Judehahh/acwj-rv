SRCS = src/*.c

jcc: $(SRCS)
	cc -o jcc -g -I include $(SRCS)

clean:
	rm -rf jcc *.o
