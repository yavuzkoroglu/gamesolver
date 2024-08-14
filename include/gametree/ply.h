#ifndef GAMETREE_PLY_H
    #define GAMETREE_PLY_H
    #include <stdint.h>

    typedef struct PlyBody {
        uint32_t prevPositionId;
        uint32_t nextPositionId;
    } Ply;
#endif
