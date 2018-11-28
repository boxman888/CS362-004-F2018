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

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -g -o randomtestadventurer randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	-./randomtestadventurer >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -g -o randomtestcard1 randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	-./randomtestcard1 >> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -g -o randomtestcard2 randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	-./randomtestcard2 >> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

EthansTests: dominion.o rngs.o
	gcc -o myUnittest1 -g myUnittest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o myUnittest2 -g myUnittest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o myUnittest3 -g myUnittest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o myUnittest4 -g myUnittest4.c dominion.o rngs.o $(CFLAGS)
	
	gcc -o myCardtest1 -g myCardtest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o myCardtest2 -g myCardtest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o myCardtest3 -g myCardtest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o myCardtest4 -g myCardtest4.c dominion.o rngs.o $(CFLAGS)
	
	gcc -o myrandomtestcard1 -g myrandomtestcard1.c dominion.o rngs.o $(CFLAGS)
	gcc -o myrandomtestcard1 -g myrandomtestcard1.c dominion.o rngs.o $(CFLAGS)
	gcc -o myrandomtestcard2 -g myrandomtestcard2.c dominion.o rngs.o $(CFLAGS)

all: playdom player unittestresults randomtestadventurer randomtestcard1 randomtestcard2

unittestresults: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c randomtestadventurer.c randomtestcard1.c randomtestcard2.c dominion.o rngs.o
	
	echo "Result for running dominion unit & card tests:" > unittestresults.out
	printf "\n---- unittest1.c:\n" >> unittestresults.out
	gcc -g -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS)
	-./unittest1 >> unittestresults.out
	
	printf "\n---- unittest2.c:\n" >> unittestresults.out
	gcc -g -o unittest2 unittest2.c dominion.o rngs.o $(CFLAGS)
	-./unittest2 >> unittestresults.out
	
	printf "\n---- unittest3.c:\n" >> unittestresults.out
	gcc -g -o unittest3 unittest3.c dominion.o rngs.o $(CFLAGS)
	-./unittest3 >> unittestresults.out
	
	printf "\n---- unittest4.c:\n" >> unittestresults.out
	gcc -g -o unittest4 unittest4.c dominion.o rngs.o $(CFLAGS)
	-./unittest4 >> unittestresults.out

	printf "\n---- cardtest1.c:\n" >> unittestresults.out
	gcc -g -o cardtest1 cardtest1.c dominion.o rngs.o $(CFLAGS)
	-./cardtest1 >> unittestresults.out

	printf "\n---- cardtest2.c:\n" >> unittestresults.out
	gcc -g -o cardtest2 cardtest2.c dominion.o rngs.o $(CFLAGS)
	-./cardtest2 >> unittestresults.out

	printf "\n---- cardtest3.c:\n" >> unittestresults.out
	gcc -g -o cardtest3 cardtest3.c dominion.o rngs.o $(CFLAGS)
	-./cardtest3 >> unittestresults.out

	printf "\n---- cardtest4.c:\n" >> unittestresults.out
	gcc -g -o cardtest4 cardtest4.c dominion.o rngs.o $(CFLAGS)
	-./cardtest4 >> unittestresults.out

	printf "\n---- randomtestadventurer.c:\n" >> unittestresults.out
	gcc -g -o randomtestadventurer randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	-./randomtestadventurer >> unittestresults.out

	printf "\n---- randomtestcard1.c:\n" >> unittestresults.out
	gcc -g -o randomtestcard1 randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	-./randomtestcard1 >> unittestresults.out

	printf "\n---- randomtestcard2.c:\n" >> unittestresults.out
	gcc -g -o randomtestcard2 randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	-./randomtestcard2 >> unittestresults.out

	printf "\n---- gcov results.c:\n" >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

clean:
	find . -maxdepth 1 -type f -executable -exec rm {} +
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe testSmithy cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4 randomtestadventurer randomtestcard1 randomtestcard2
