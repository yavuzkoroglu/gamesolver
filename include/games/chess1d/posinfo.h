#ifndef GAMES_POSINFO_H
    #define GAMES_POSINFO_H
    #include "padkit/chunkset.h"

    #define C1D_MIN_COORD               (1)
    #define C1D_MAX_COORD               (8)
    #define C1D_IS_VALID_COORD(i)       (C1D_MIN_COORD <= i && i <= C1D_MAX_COORD)

    #define C1D_TURN_WHITE              (0)
    #define C1D_TURN_BLACK              (1)

    #define C1D_SQ_EMPTY                (0)
    #define C1D_SQ_WHITE_KING           (1)
    #define C1D_SQ_WHITE_ROOK           (2)
    #define C1D_SQ_WHITE_KNIGHT         (3)
    #define C1D_SQ_BLACK_KING           (4)
    #define C1D_SQ_BLACK_ROOK           (5)
    #define C1D_SQ_BLACK_KNIGHT         (6)
    #define C1D_SQ_INVALID              (7)
    #define C1D_IS_VALID_VAL(val)       (val < C1D_SQ_INVALID)
    #define C1D_SQ_MIN_VAL              C1D_SQ_EMPTY
    #define C1D_SQ_MAX_VAL              (C1D_SQ_INVALID - 1)

    #define C1D_EMPTY_SQ_SYMBOL         ('.')
    #define C1D_WHITE_KING_SYMBOL       ('K')
    #define C1D_WHITE_ROOK_SYMBOL       ('R')
    #define C1D_WHITE_KNIGHT_SYMBOL     ('N')
    #define C1D_BLACK_KING_SYMBOL       ('k')
    #define C1D_BLACK_ROOK_SYMBOL       ('r')
    #define C1D_BLACK_KNIGHT_SYMBOL     ('n')
    #define C1D_TURN_WHITE_SYMBOL       ('w')
    #define C1D_TURN_BLACK_SYMBOL       ('b')
    #define C1D_TURN_WHITESPACE_SYMBOL  (' ')

    #define C1D_IS_OCCUPIER_WHITE(val)  \
        (val == C1D_SQ_WHITE_KING || val == C1D_SQ_WHITE_ROOK || C1D_SQ_WHITE_KNIGHT)

    #define C1D_IS_OCCUPIER_BLACK(val)  \
        (val == C1D_SQ_BLACK_KING || val == C1D_SQ_BLACK_ROOK || C1D_SQ_BLACK_KNIGHT)

    #define POSINFO_GUESS_NPLIES        (16)
    #define POSINFO_GUESS_NPARENTS      (4)
    #define POSINFO_STR_LEN             (11)
    #define POSINFO_STR_WHITESPACE_ID   (8)
    #define POSINFO_STR_TURN_ID         (9)

    typedef struct Chess1DPositionBody {
        uint32_t board:24;
        uint32_t turn:1;
        uint32_t is_check:1;
        uint32_t is_checkmate:1;
        uint32_t is_draw:1;
        uint32_t is_insufficientMaterial:1;
        uint32_t is_stalemate:1;
        uint32_t nRepetitions:2;
    } Chess1DPosition, PositionInfo;

    bool canMoveFrom_c1d(Chess1DPosition* const pos, uint32_t const from);

    bool canMoveTo_c1d(Chess1DPosition* const pos, uint32_t const to);

    void clearSq_c1d(Chess1DPosition* const pos, uint32_t const i);

    bool construct_posinfo(PositionInfo* const pos, char const* const str, uint64_t const len);

    uint32_t getSqVal_c1d(Chess1DPosition const* const pos, uint32_t const i);

    bool isValid_posinfo(PositionInfo const* const pos);

    void prepareStatic_posinfo(void);

    uint32_t readToChunkSet_posinfo(ChunkSet* const cset, FILE* const posStream);

    void setSqVal_c1d(Chess1DPosition* const pos, uint32_t const i, uint32_t const val);
#endif
