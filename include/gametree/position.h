#ifndef GAMETREE_POSITION_H
    #define GAMETREE_POSITION_H
    #include <stdint.h>
    #include "games.h"
    #include GAME_POSINFO_HDR
    #include "padkit/chunkset.h"

    typedef struct PositionBody {
        PositionInfo    details[1];
        uint32_t        parentPosId;
        uint32_t        nextPlyId;
        uint32_t        depth;
        uint32_t        value;
    } Position;

    bool fromPosStr_pos(
        Position* const pos, char const* const posStr, uint64_t const posStrLen,
        uint32_t const parentPositionId
    );

    bool isValid_pos(Position const* const pos);

    uint32_t readToChunkSet_pos(ChunkSet* const cset, FILE* const posStream);
#endif
