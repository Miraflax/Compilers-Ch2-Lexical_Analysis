CC = gcc
FLAGS = -Wall -Werror -std=c99 -D_XOPEN_SOURCE=700 -g
APP = lextest

$(APP): driver.o lex.yy.o errormsg.o util.o
	$(CC) $(FLAGS) $^ -o $@

driver.o: driver.c tokens.h errormsg.h util.h
	$(CC) $(FLAGS) -c $<

errormsg.o: errormsg.c errormsg.h util.h
	$(CC) $(FLAGS) -c $<

lex.yy.o: lex.yy.c tokens.h errormsg.h util.h
	$(CC) $(FLAGS) -c $<

util.o: util.c util.h
	$(CC) $(FLAGS) -c $<

lex.yy.c: tiger.lex
	lex $^

clean: 
	rm -f $(APP) util.o driver.o lex.yy.o lex.yy.c errormsg.o
