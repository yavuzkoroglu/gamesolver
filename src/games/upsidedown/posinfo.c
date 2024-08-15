#include <inttypes.h>
#include <string.h>
#include "games/upsidedown/posinfo.h"
#include "padkit/debug.h"

void free_posinfo(PositionInfo* const pos) {
    DEBUG_ASSERT(isValid_posinfo(pos))
    DEBUG_ASSERT_NDEBUG_EXECUTE(free_gmtx(pos->arrangement))
}

bool fromString_posinfo(PositionInfo* const pos, char const* const str, uint64_t const len) {
    DEBUG_ERROR_IF(pos == NULL)
    DEBUG_ERROR_IF(str == NULL)
    DEBUG_ERROR_IF(len == 0)
    DEBUG_ERROR_IF(len == UINT64_MAX)
    DEBUG_ASSERT(str[len] == '\0')
    DEBUG_ASSERT(strlen(str) == len)

    char* coins = calloc((size_t)len, 1);
    DEBUG_ERROR_IF(coins == NULL)

    if (sscanf(str, "%"SCNu32" %"SCNu32" %s", &pos->m, &pos->n, coins) != 3) {
        free(coins);
        return 0;
    }
    if (pos->n == 0) {
        free(coins);
        return 0;
    }
    if (pos->m == 0) {
        free(coins);
        return 0;
    }
    if (pos->n == UINT32_MAX) {
        free(coins);
        return 0;
    }
    if (pos->m == UINT32_MAX) {
        free(coins);
        return 0;
    }
    if (pos->n != strlen(coins)) {
        free(coins);
        return 0;
    }

    DEBUG_ASSERT_NDEBUG_EXECUTE(construct_gmtx(pos->arrangement, 1, pos->n))

    for (uint32_t coinId = 0; coinId < pos->n; coinId++) {
        switch (coins[coinId]) {
            case UD_HEADS:
                break;
            case UD_TAILS:
                DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(pos->arrangement, 0, coinId))
                break;
            default:
                free(coins);
                return 0;
        }
    }

    free(coins);
    return 1;
}

bool isValid_posinfo(PositionInfo const* const pos) {
    if (pos == NULL)                        return 0;
    if (pos->n == 0)                        return 0;
    if (pos->m == 0)                        return 0;
    if (pos->n == UINT32_MAX)               return 0;
    if (pos->m == UINT32_MAX)               return 0;
    if (!isValid_gmtx(pos->arrangement))    return 0;

    return 1;
}

void prepareStatic_posinfo(void) {}

uint32_t readToChunkSet_posinfo(ChunkSet* const cset, FILE* const posStream) {
    DEBUG_ASSERT(isValid_cset(cset))
    DEBUG_ERROR_IF(posStream == NULL)

    static char buffer[POSINFO_MAX_POS_STR_LEN + 1];

    if (fgets(buffer, POSINFO_MAX_POS_STR_LEN, posStream) == NULL)
        return UINT32_MAX;

    size_t const len = strlen(buffer);
    if (len > POSINFO_MAX_POS_STR_LEN)
        return UINT32_MAX;

    return addKey_cset(cset, buffer, (uint64_t)len);
}
