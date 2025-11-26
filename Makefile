


all: stockTracker

stockTracker: src/main.cpp lib/fetcher.o lib/ui.o
	g++ -o stockTracker src/main.cpp lib/fetcher.o lib/ui.o -lcurl -lncurses

