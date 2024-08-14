include padkit/compile.mk

GAMENAME=chess1d
GAMES=chess1d rubiks2by2 tictactoe upsidedown
INCLUDES=-Iinclude -Ipadkit/include

ifndef (${GAMENAME})
GAMENAME=chess1d
endif

OBJECTS=                            \
    obj/games/${GAMENAME}/posinfo.o \
    obj/gamesolver.o                \
    obj/gametree.o                  \
    obj/gametree/position.o

ifeq (${GAMENAME},chess1d)
GAMEID=0
else ifeq (${GAMENAME},rubiks2by2)
GAMEID=1
else ifeq (${GAMENAME},tictactoe)
GAMEID=2
else ifeq (${GAMENAME},upsidedown)
GAMEID=3
else
GAMEID=0
endif

default: bin/gamesolver

.PHONY: default clean cleanobjects cleanpadkit documentation objects

bin: ; mkdir bin

bin/gamesolver: bin objects padkit/lib/libpadkit.a  \
    ; ${COMPILE} ${OBJECTS} padkit/lib/libpadkit.a -o bin/gamesolver

clean: ; rm -rf obj bin padkit *.gcno *.gcda *.gcov html latex

cleanlibpadkit: ; rm -rf padkit/obj padkit/lib/libpadkit.a

cleanobjects: ; rm -rf obj

documentation: ; doxygen

obj: ; mkdir obj

obj/games: obj; mkdir obj/games

obj/games/chess1d: obj/games; mkdir obj/games/chess1d

obj/games/chess1d/posinfo.o:                \
    obj/games/chess1d                       \
    include/games/chess1d/posinfo.h         \
    padkit/include/padkit/bliterals.h       \
    padkit/include/padkit/chunk.h           \
    padkit/include/padkit/chunkset.h        \
    padkit/include/padkit/debug.h           \
    src/games/chess1d/posinfo.c             \
    ; ${COMPILE} ${INCLUDES} src/games/chess1d/posinfo.c -c -o obj/games/chess1d/posinfo.o

obj/gamesolver.o: obj                       \
    include/games.h                         \
    include/gametree.h                      \
    include/gametree/ply.h                  \
    include/gametree/position.h             \
    padkit/include/padkit/chunk.h           \
    padkit/include/padkit/chunkset.h        \
    padkit/include/padkit/debug.h           \
    padkit/include/padkit/preprocessor.h    \
    padkit/include/padkit/reallocate.h      \
    padkit/include/padkit/stack.h           \
    src/gamesolver.c                        \
    ; ${COMPILE} ${INCLUDES} src/gamesolver.c -c -o obj/gamesolver.o

obj/gametree: obj; mkdir obj/gametree

obj/gametree.o: obj                         \
    include/games.h                         \
    include/gametree.h                      \
    include/gametree/ply.h                  \
    include/gametree/position.h             \
    padkit/include/padkit/chunk.h           \
    padkit/include/padkit/chunkset.h        \
    padkit/include/padkit/debug.h           \
    padkit/include/padkit/preprocessor.h    \
    padkit/include/padkit/reallocate.h      \
    padkit/include/padkit/stack.h           \
    src/gametree.c                    	    \
    ; ${COMPILE} ${INCLUDES} -DGAME_ID=${GAMEID} src/gametree.c -c -o obj/gametree.o

obj/gametree/position.o: obj/gametree       \
    include/games.h                         \
    include/gametree/position.h             \
    padkit/include/padkit/chunk.h           \
    padkit/include/padkit/chunkset.h        \
    padkit/include/padkit/debug.h           \
    padkit/include/padkit/preprocessor.h    \
    padkit/include/padkit/reallocate.h      \
    padkit/include/padkit/stack.h           \
    src/gametree/position.c                 \
    ; ${COMPILE} ${INCLUDES} -DGAME_ID=${GAMEID} src/gametree/position.c -c -o obj/gametree/position.o

objects: cleanobjects ${OBJECTS}

padkit: ; git clone https://github.com/yavuzkoroglu/padkit.git

padkit/compile.mk: padkit; $(make padkit/compile.mk)

padkit/include/padkit.h: padkit; make -C padkit include/padkit.h

padkit/lib/libpadkit.a: cleanlibpadkit padkit; make -C padkit lib/libpadkit.a
