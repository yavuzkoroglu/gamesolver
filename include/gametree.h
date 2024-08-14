#ifndef GAMETREE_H
    #define GAMETREE_H
    #include "gametree/ply.h"
    #include "gametree/position.h"
    #include "padkit/chunkset.h"

    #define GTREE_CSET_POS  0
    #define GTREE_CSET_PLY  1
    #define GTREE_CSET_LAST GTREE_CSET_PLY
    typedef struct GameTreeBody {
        ChunkSet                sets[GTREE_CSET_LAST + 1];
        DECLARE_STACK(Position, posStack)
        DECLARE_STACK(Ply,      plyStack)
    } GameTree;

    #define GTREE_CONSTRUCT_SUCCESS                         0
    #define GTREE_CONSTRUCT_FAIL_CANNOT_READ_IO             1
    #define GTREE_CONSTRUCT_FAIL_CORRUPT_CSET               2
    #define GTREE_CONSTRUCT_FAIL_INITIAL_POSITION_INVALID   3
    int constructEmpty_gtree(GameTree* const gTree, FILE* const posStream);

    void free_gtree(GameTree* const gTree);

    bool isValid_gtree(GameTree const* const gTree);

    void prepareStatic_gtree(void);
#endif
