SRCS = src/*.c

scanner: $(SRCS)
	cc -o scanner -g -I include $(SRCS)

clean:
	rm -rf scanner *.o