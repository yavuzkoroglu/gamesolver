#include "gametree.h"
#include "padkit/debug.h"

int constructEmpty_gtree(GameTree* const gTree, FILE* const posStream) {
    prepareStatic_gtree();

    DEBUG_ERROR_IF(gTree == NULL)
    DEBUG_ERROR_IF(posStream == NULL)

    DEBUG_ASSERT_NDEBUG_EXECUTE(
        constructEmpty_cset(gTree->posSet, CHUNK_SET_RECOMMENDED_PARAMETERS)
    )

    switch (readToChunkSet_pos(gTree->posSet, posStream)) {
        case UINT32_MAX:
            free_cset(gTree->posSet);
            return GTREE_CONSTRUCT_FAIL_CANNOT_READ_IO;
        case 0:
            break;
        default:
            free_cset(gTree->posSet);
            return GTREE_CONSTRUCT_FAIL_CORRUPT_CSET;
    }

    char const* const initialPosStr = getKey_cset(gTree->posSet, 0);
    DEBUG_ERROR_IF(initialPosStr == NULL)

    uint64_t initialPosStrLen = strlen_cset(gTree->posSet, 0);
    DEBUG_ERROR_IF(initialPosStrLen == UINT64_MAX)

    CONSTRUCT_EMPTY_STACK(Position, gTree->posStack, BUFSIZ)

    PUSH_STACK_N(Position, Position* const initialPos, gTree->posStack)
    if (!fromString_pos(initialPos, initialPosStr, initialPosStrLen, UINT32_MAX, 0)) {
        free_cset(gTree->posSet);
        FREE_STACK(gTree->posStack)
        return GTREE_CONSTRUCT_FAIL_INITIAL_POSITION_INVALID;
    }

    DEBUG_ASSERT(isValid_gtree(gTree))

    return GTREE_CONSTRUCT_SUCCESS;
}

void free_gtree(GameTree* const gTree) {
    DEBUG_ASSERT(isValid_gtree(gTree))

    free_cset(gTree->posSet);

    for (uint32_t posId = 0; posId < gTree->posStack_size; posId++) {
        Position* const pos = gTree->posStack + posId;
        DEBUG_ASSERT(isValid_pos(pos))

        free_pos(pos);
    }
    FREE_STACK(gTree->posStack)
}

bool isValid_gtree(GameTree const* const gTree) {
    if (gTree == NULL)                      return 0;
    if (!isValid_cset(gTree->posSet))       return 0;
    if (!IS_VALID_STACK(gTree->posStack))   return 0;
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
