#include <limits.h>
#include <string.h>
#include "games/chess1d/posinfo.h"
#include "padkit/bliterals.h"
#include "padkit/debug.h"

static uint32_t symbol2sq[UCHAR_MAX + 1];
static char     sq2symbol[C1D_SQ_MAX_VAL + 1];

bool canMoveFrom_c1d(Chess1DPosition* const pos, uint32_t const from) {
    DEBUG_ASSERT(isValid_posinfo(pos))
    DEBUG_ASSERT(C1D_IS_VALID_COORD(from))

    uint32_t const sqVal = getSqVal_c1d(pos, from);
    switch (pos->turn) {
        case C1D_TURN_WHITE:
            return (pos->is_check)
                ? (sqVal == C1D_SQ_WHITE_KING)
                : (C1D_IS_OCCUPIER_WHITE(sqVal));
        case C1D_TURN_BLACK:
            return (pos->is_check)
                ? (sqVal == C1D_SQ_BLACK_KING)
                : (C1D_IS_OCCUPIER_BLACK(sqVal));
        default:
            return 0;
    }
}

bool canMoveTo_c1d(Chess1DPosition* const pos, uint32_t const to) {
    DEBUG_ASSERT(isValid_posinfo(pos))
    DEBUG_ASSERT(C1D_IS_VALID_COORD(to))

    uint32_t const sqVal = getSqVal_c1d(pos, to);
    switch (pos->turn) {
        case C1D_TURN_WHITE:
            return !C1D_IS_OCCUPIER_WHITE(sqVal);
        case C1D_TURN_BLACK:
        default:
            return !C1D_IS_OCCUPIER_BLACK(sqVal);
    }
}

void clearSq_c1d(Chess1DPosition* const pos, uint32_t const i) {
    DEBUG_ERROR_IF(pos == NULL)
    DEBUG_ASSERT(C1D_IS_VALID_COORD(i))

    pos->board &= ~(pos->board & (B_111 << (3*i-3)));
}

bool construct_posinfo(PositionInfo* const pos, char const* const str, uint64_t const len) {
    DEBUG_ERROR_IF(pos == NULL)
    DEBUG_ERROR_IF(str == NULL)
    DEBUG_ASSERT(str[len] == '\0')
    DEBUG_ASSERT(strlen(str) == len)

    if (len != POSINFO_STR_LEN)
        return 0;

    for (uint32_t i = C1D_MIN_COORD; i <= C1D_MAX_COORD; i++) {
        uint32_t const sqVal = symbol2sq[(unsigned)str[i - 1]];
        if (!C1D_IS_VALID_VAL(sqVal))
            return 0;

        setSqVal_c1d(pos, i, sqVal);
    }

    if (str[POSINFO_STR_WHITESPACE_ID] != C1D_TURN_WHITESPACE_SYMBOL)
        return 0;

    switch (str[POSINFO_STR_TURN_ID]) {
        case C1D_TURN_WHITE_SYMBOL:
            pos->turn = C1D_TURN_WHITE;
            return 1;
        case C1D_TURN_BLACK_SYMBOL:
            pos->turn = C1D_TURN_BLACK;
            return 1;
        default:
            return 0;
    }
}

uint32_t getSqVal_c1d(Chess1DPosition const* const pos, uint32_t const i) {
    DEBUG_ERROR_IF(pos == NULL)
    DEBUG_ASSERT(C1D_IS_VALID_COORD(i))

    uint32_t const val = (pos->board & (B_111 << (3*i-3))) >> (3*i-3);
    DEBUG_ASSERT(C1D_IS_VALID_VAL(val))

    return val;
}

bool isValid_posinfo(PositionInfo const* const pos) {
    if (pos == NULL) return 0;

    for (uint32_t i = 1; i <= 8; i++)
        if (!C1D_IS_VALID_VAL(getSqVal_c1d(pos, i)))
            return 0;

    if (pos->is_check && pos->is_insufficientMaterial)                  return 0;
    if (pos->is_check && pos->is_stalemate)                             return 0;
    if (!pos->is_check && pos->is_checkmate)                            return 0;
    if (pos->is_checkmate && pos->is_draw)                              return 0;
    if (pos->is_checkmate && pos->is_insufficientMaterial)              return 0;
    if (pos->is_checkmate && pos->is_stalemate)                         return 0;
    if (pos->is_checkmate && pos->is_threeFoldRepetition)               return 0;
    if (
        pos->is_draw                    &&
        !pos->is_insufficientMaterial   &&
        !pos->is_stalemate              &&
        !pos->is_threeFoldRepetition
    ) return 0;
    if (!pos->is_draw && pos->is_insufficientMaterial)                  return 0;
    if (!pos->is_draw && pos->is_stalemate)                             return 0;
    if (!pos->is_draw && pos->is_threeFoldRepetition)                   return 0;
    if (pos->is_insufficientMaterial && pos->is_stalemate)              return 0;
    if (pos->is_insufficientMaterial && pos->is_threeFoldRepetition)    return 0;
    if (pos->is_stalemate && pos->is_threeFoldRepetition)               return 0;
    if (pos->last_bit == 0)                                             return 0;

    return 1;
}

void prepareStatic_posinfo(void) {
    for (uint32_t symbol = 0; symbol <= UCHAR_MAX; symbol++) {
        switch (symbol) {
            case C1D_EMPTY_SQ_SYMBOL:
                symbol2sq[symbol] = C1D_SQ_EMPTY;
                sq2symbol[C1D_SQ_EMPTY] = (char)symbol;
                break;
            case C1D_WHITE_KING_SYMBOL:
                symbol2sq[symbol] = C1D_SQ_WHITE_KING;
                sq2symbol[C1D_SQ_WHITE_KING] = (char)symbol;
                break;
            case C1D_WHITE_ROOK_SYMBOL:
                symbol2sq[symbol] = C1D_SQ_WHITE_ROOK;
                sq2symbol[C1D_SQ_WHITE_ROOK] = (char)symbol;
                break;
            case C1D_WHITE_KNIGHT_SYMBOL:
                symbol2sq[symbol] = C1D_SQ_WHITE_KNIGHT;
                sq2symbol[C1D_SQ_WHITE_KNIGHT] = (char)symbol;
                break;
            case C1D_BLACK_KING_SYMBOL:
                symbol2sq[symbol] = C1D_SQ_BLACK_KING;
                sq2symbol[C1D_SQ_BLACK_KING] = (char)symbol;
                break;
            case C1D_BLACK_ROOK_SYMBOL:
                symbol2sq[symbol] = C1D_SQ_BLACK_ROOK;
                sq2symbol[C1D_SQ_BLACK_ROOK] = (char)symbol;
                break;
            case C1D_BLACK_KNIGHT_SYMBOL:
                symbol2sq[symbol] = C1D_SQ_BLACK_KNIGHT;
                sq2symbol[C1D_SQ_BLACK_KNIGHT] = (char)symbol;
                break;
            default:
                symbol2sq[symbol] = C1D_SQ_INVALID;
        }
    }
}

uint32_t readToChunkSet_posinfo(ChunkSet* const cset, FILE* const posStream) {
    static char posStr[POSINFO_STR_LEN + 1];

    DEBUG_ASSERT(isValid_cset(cset))
    DEBUG_ERROR_IF(posStream == NULL)

    if (fread(posStr, 1, POSINFO_STR_LEN, posStream) != POSINFO_STR_LEN)
        return UINT32_MAX;

    return addKey_cset(cset, posStr, POSINFO_STR_LEN);
}

void setSqVal_c1d(Chess1DPosition* const pos, uint32_t const i, uint32_t const val) {
    DEBUG_ERROR_IF(pos == NULL)
    DEBUG_ASSERT(C1D_IS_VALID_COORD(i))
    DEBUG_ASSERT(C1D_IS_VALID_VAL(val))

    clearSq_c1d(pos, i);
    pos->board |= (val << (3*i-3));
}
