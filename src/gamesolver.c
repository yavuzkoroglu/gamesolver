#include "gametree.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("\nUsage: %s <initial-position-file>\n\n", argv[0]);
        return EXIT_SUCCESS;
    }

    FILE* const posStream = fopen(argv[1], "r");
    if (posStream == NULL) {
        printf("\nERROR: Cannot open %s\n\n", argv[1]);
        return EXIT_FAILURE;
    }

    GameTree* const gTree = malloc(sizeof(GameTree));
    if (gTree == NULL) {
        printf("\nERROR: Could not allocate %zu bytes\n\n", sizeof(GameTree));
        return EXIT_FAILURE;
    }

    switch (constructEmpty_gtree(gTree, posStream)) {
        case GTREE_CONSTRUCT_SUCCESS:
            break;
        case GTREE_CONSTRUCT_FAIL_CANNOT_READ_IO:
            printf("\nERROR: Corrupt IO\n\n");
            free(gTree);
            return EXIT_FAILURE;
        case GTREE_CONSTRUCT_FAIL_CORRUPT_CSET:
            printf("\nERROR: Corrupt ChunkSet\n\n");
            free(gTree);
            return EXIT_FAILURE;
        case GTREE_CONSTRUCT_FAIL_INITIAL_POSITION_INVALID:
            printf("\nERROR: Invalid Position Syntax @ %s\n\n", argv[1]);
            free(gTree);
            return EXIT_FAILURE;
        default:
            printf("\nERROR: Unknown\n\n");
            free(gTree);
            return EXIT_FAILURE;
    }

    free_gtree(gTree);
    free(gTree);

    DEBUG_ASSERT(fclose(posStream) == 0)
    NDEBUG_EXECUTE(fclose(posStream))

    return EXIT_SUCCESS;
}
