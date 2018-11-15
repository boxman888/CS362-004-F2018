CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults: dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	
	unittest1 >> unittestresults.out
	gcov unittest1 >> unittestresults.out
	echo "" >> unittestresults.out

	unittest2 >> unittestresults.out
	gcov unittest2 >> unittestresults.out
	echo "" >> unittestresults.out
	
	unittest3 >> unittestresults.out
	gcov unittest3 >> unittestresults.out
	echo "" >> unittestresults.out
	
	unittest4 >> unittestresults.out
	gcov unittest4 >> unittestresults.out
	echo "" >> unittestresults.out

	unittest1 >> unittestresults.out
	gcov unittest1 >> unittestresults.out
	echo "" >> unittestresults.out

	- cardtest2 >> unittestresults.out
	gcov cardtest2 >> unittestresults.out
	echo "$? Segfault occured here" >> unittestresults.out
	
	cardtest3 >> unittestresults.out
	gcov cardtest3 >> unittestresults.out
	echo "" >> unittestresults.out
	
	cardtest4 >> unittestresults.out
	gcov cardtest4 >> unittestresults.out
	echo "" >> unittestresults.out
	
buildrandtests: dominion.o rngs.o
	gcc -o randomtestcardadventure -g randomtestcardadventure.c dominion.o rngs.o $(CFLAGS)
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

runrandtests:
	- randomtestcardadventure > randomtestadventurer.out
	randomtestcard1 > randomtestcard1.out
	randomtestcard2 > randomtestcard2.out

cleanTests:
	- rm -f unittestresults.out
	- rm -f unittest1.g*
	- rm -f unittest2.g*
	- rm -f unittest3.g*
	- rm -f unittest4.g*
	- rm -f *.c.gcov
	- rm -r *.gcda
	- rm -r *gcno
	- rm -f *.out
	find . -maxdepth 1 -type f -executable -exec rm {} +

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
