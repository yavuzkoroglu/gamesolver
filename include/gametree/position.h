#ifndef GAMETREE_POSITION_H
    #define GAMETREE_POSITION_H
    #include <stdint.h>
    #include "games.h"
    #include GAME_POSINFO_HDR
    #include "padkit/chunkset.h"
    #include "padkit/stack.h"

    typedef struct PositionBody {
        PositionInfo            details[1];
        DECLARE_STACK(uint32_t, plyIds)
        DECLARE_STACK(uint32_t, parentPositionIds)
        uint32_t                siblingId;
    } Position;

    bool construct_pos(
        Position* const pos, char const* const posStr, uint64_t const posStrLen,
        uint32_t const parentPositionId
    );

    bool isValid_pos(Position const* const pos);

    uint32_t readToChunkSet_pos(ChunkSet* const cset, FILE* const posStream);
#endif
