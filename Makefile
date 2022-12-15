CC = gcc
CC_FLAGS := -Os
EXE_NAME= simple_shell5.out
CC_DEBUG_FLAGS := -g -Og -Wall

OBJS:= simple_shell5.o



build: $(OBJS)
	@$(CC) $(CC_FLAGS) $(OBJS) -o $(EXE_NAME)

simple_shell5.o: simple_shell5.c
	@ $(CC) -c simple_shell5.c

run: build
	@./$(EXE_NAME)
clean:
	@rm *.o *.out
