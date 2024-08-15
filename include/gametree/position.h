#ifndef GAMETREE_POSITION_H
    #define GAMETREE_POSITION_H
    #include "games.h"
    #include GAME_POSINFO_HDR
    #include "padkit/chunkset.h"

    typedef struct PositionBody {
        PositionInfo    details[1];
        uint32_t        parentPosId;
        uint32_t        nextPosId;
        uint32_t        depth;
        uint32_t        value;
    } Position;

    void free_pos(Position* const pos);

    bool fromString_pos(
        Position* const pos, char const* const posStr, uint64_t const posStrLen,
        uint32_t const parentPosId, uint32_t const depth
    );

    bool isValid_pos(Position const* const pos);

    uint32_t readToChunkSet_pos(ChunkSet* const cset, FILE* const posStream);
#endif
