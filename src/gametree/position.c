#ifndef NDEBUG
    #include <string.h>
#endif
#include "gametree/position.h"
#include "padkit/debug.h"

bool fromString_pos(
    Position* const pos, char const* const posStr, uint64_t const posStrLen,
    uint32_t const parentPosId, uint32_t const depth
) {
    DEBUG_ERROR_IF(pos == NULL)
    DEBUG_ERROR_IF(posStr == NULL)
    DEBUG_ERROR_IF(posStrLen == 0)
    DEBUG_ERROR_IF(posStrLen == UINT64_MAX)
    DEBUG_ASSERT(posStr[posStrLen] == '\0')
    DEBUG_ASSERT(strlen(posStr) == posStrLen)

    if (!fromString_posinfo(pos->details, posStr, posStrLen))
        return 0;

    pos->parentPosId    = parentPosId;
    pos->nextPosId      = UINT32_MAX;
    pos->depth          = depth;
    pos->value          = UINT32_MAX;

    return 1;
}

void free_pos(Position* const pos) {
    DEBUG_ASSERT(isValid_pos(pos))

    free_posinfo(pos->details);
}

bool isValid_pos(Position const* const pos) {
    if (pos == NULL)                    return 0;
    if (!isValid_posinfo(pos->details)) return 0;

    return 1;
}

uint32_t readToChunkSet_pos(ChunkSet* const cset, FILE* const posStream) {
    DEBUG_ASSERT(isValid_cset(cset))
    DEBUG_ERROR_IF(posStream == NULL)

    return readToChunkSet_posinfo(cset, posStream);
}
