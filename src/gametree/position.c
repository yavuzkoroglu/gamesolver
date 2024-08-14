#include "gametree/position.h"

bool construct_pos(
    Position* const pos, char const* const posStr, uint64_t const posStrLen,
    uint32_t const parentPositionId
) {
    DEBUG_ERROR_IF(pos == NULL)
    DEBUG_ERROR_IF(posStr == NULL)
    DEBUG_ERROR_IF(posStrLen == 0)
    DEBUG_ERROR_IF(posStrLen == UINT64_MAX)
    DEBUG_ASSERT(posStr[posStrLen] == '\0')
    DEBUG_ASSERT(strlen(posStr) == posStrLen)

    if (!construct_posinfo(pos->details, posStr, posStrLen))
        return 0;

    CONSTRUCT_EMPTY_STACK(uint32_t, pos->plyIds, POSINFO_GUESS_NPLIES)
    CONSTRUCT_EMPTY_STACK(uint32_t, pos->parentPositionIds, POSINFO_GUESS_NPARENTS)

    if (parentPositionId != UINT32_MAX)
        PUSH_STACK(uint32_t, pos->parentPositionIds, &parentPositionId)

    pos->siblingId = UINT32_MAX;

    return 1;
}

bool isValid_pos(Position const* const pos) {
    if (pos == NULL)                    return 0;
    if (!isValid_posinfo(pos->details)) return 0;
    if (!IS_VALID_STACK(pos->plyIds))   return 0;

    return 1;
}

uint32_t readToChunkSet_pos(ChunkSet* const cset, FILE* const posStream) {
    DEBUG_ASSERT(isValid_cset(cset))
    DEBUG_ERROR_IF(posStream == NULL)

    return readToChunkSet_posinfo(cset, posStream);
}
