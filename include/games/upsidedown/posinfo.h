#ifndef GAMES_POSINFO_H
    #define GAMES_POSINFO_H
    #include "padkit/chunkset.h"
    #include "padkit/graphmatrix.h"

    #define UD_HEADS    'H'
    #define UD_TAILS    'T'

    #define POSINFO_MAX_POS_STR_LEN 1000

    typedef struct UpsideDownPositionBody {
        uint32_t    n;
        uint32_t    m;
        GraphMatrix arrangement[1];
    } UpsideDownPosition, PositionInfo;

    void free_posinfo(PositionInfo* const pos);

    bool fromString_posinfo(PositionInfo* const pos, char const* const str, uint64_t const len);

    bool isValid_posinfo(PositionInfo const* const pos);

    void prepareStatic_posinfo(void);

    uint32_t readToChunkSet_posinfo(ChunkSet* const cset, FILE* const posStream);
#endif
