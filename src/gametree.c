#include "gametree.h"
#include "padkit/debug.h"

int constructEmpty_gtree(GameTree* const gTree, FILE* const posStream) {
    prepareStatic_gtree();

    DEBUG_ERROR_IF(gTree == NULL)
    DEBUG_ERROR_IF(posStream == NULL)

    ChunkSet* const posSet = gTree->sets + GTREE_CSET_POS;
    ChunkSet* const plySet = gTree->sets + GTREE_CSET_PLY;

    DEBUG_ASSERT_NDEBUG_EXECUTE(
        constructEmpty_cset(posSet, CHUNK_SET_RECOMMENDED_PARAMETERS)
    )
    DEBUG_ASSERT_NDEBUG_EXECUTE(
        constructEmpty_cset(plySet, CHUNK_SET_RECOMMENDED_PARAMETERS)
    )

    switch (readToChunkSet_pos(posSet, posStream)) {
        case UINT32_MAX:
            free_cset(posSet);
            free_cset(plySet);
            return GTREE_CONSTRUCT_FAIL_CANNOT_READ_IO;
        case 0:
            break;
        default:
            return GTREE_CONSTRUCT_FAIL_CORRUPT_CSET;
    }

    char const* const initialPosStr = getKey_cset(posSet, 0);
    DEBUG_ERROR_IF(initialPosStr == NULL)

    uint64_t initialPosStrLen = strlen_cset(posSet, 0);
    DEBUG_ERROR_IF(initialPosStrLen == UINT64_MAX)

    CONSTRUCT_EMPTY_STACK(Position, gTree->posStack, BUFSIZ)
    CONSTRUCT_EMPTY_STACK(Position, gTree->plyStack, BUFSIZ)

    PUSH_STACK_N(Position, Position* const initialPos, gTree->posStack)
    if (!construct_pos(initialPos, initialPosStr, initialPosStrLen, UINT32_MAX)) {
        free_cset(posSet);
        free_cset(plySet);
        FREE_STACK(gTree->posStack)
        FREE_STACK(gTree->plyStack)
        return GTREE_CONSTRUCT_FAIL_INITIAL_POSITION_INVALID;
    }

    DEBUG_ASSERT(isValid_gtree(gTree))

    return GTREE_CONSTRUCT_SUCCESS;
}

void free_gtree(GameTree* const gTree) {
    DEBUG_ASSERT(isValid_gtree(gTree))

    ChunkSet* const posSet = gTree->sets + GTREE_CSET_POS;
    ChunkSet* const plySet = gTree->sets + GTREE_CSET_PLY;

    free_cset(posSet);
    free_cset(plySet);
    FREE_STACK(gTree->posStack)
    FREE_STACK(gTree->plyStack)
}

bool isValid_gtree(GameTree const* const gTree) {
    if (gTree == NULL) return 0;

    for (uint32_t setId = 0; setId <= GTREE_CSET_LAST; setId++)
        if (!isValid_cset(gTree->sets + setId))
            return 0;

    if (!IS_VALID_STACK(gTree->posStack))   return 0;
    if (!IS_VALID_STACK(gTree->plyStack))   return 0;

    if (gTree->posStack_size == 0)          return 0;

    return 1;
}

void prepareStatic_gtree(void) {
    static bool is_prepareStaticCalled = 0;

    if (!is_prepareStaticCalled) {
        prepareStatic_posinfo();
        is_prepareStaticCalled = 1;
    }
}
