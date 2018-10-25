CFLAGS= -Wall -fpic -coverage -std=c99

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

all: playdom player unittestresults.out

unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c testSmithy.c testAdventurer.c testVillage.c testOutpost.c dominion.o rngs.o
	
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

	printf "\n---- testSmithy.c:\n" >> unittestresults.out
	gcc -g -o testSmithy testSmithy.c dominion.o rngs.o $(CFLAGS)
	-./testSmithy >> unittestresults.out

	printf "\n---- testAdventurer.c:\n" >> unittestresults.out
	gcc -g -o testAdventurer testAdventurer.c dominion.o rngs.o $(CFLAGS)
	-./testAdventurer >> unittestresults.out

	printf "\n---- testVillage.c:\n" >> unittestresults.out
	gcc -g -o testVillage testVillage.c dominion.o rngs.o $(CFLAGS)
	-./testVillage >> unittestresults.out

	printf "\n---- testOutpost.c:\n" >> unittestresults.out
	gcc -g -o testOutpost testOutpost.c dominion.o rngs.o $(CFLAGS)
	-./testOutpost >> unittestresults.out

	printf "\n---- gcov results.c:\n" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
