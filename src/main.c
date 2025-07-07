#include <xor.h>

// a hex value that you need to put in-order to get the en/de coded value.
unsigned char key = 0xAA;

int main(int argc, const char *argv[]) {
    if(argv[1] == NULL) printUsage(argv[0]);
    if(strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "--file") == 0) {
        if(argv[2] == NULL) printUsage(argv[0]);
        uint64_t hash = xor64FileHash(argv[2]);
        printf("0x%016" PRIX64 " - %s\n", hash, argv[2]);
        return 0;
    }
    else if(strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--string") == 0) {
        const char *mode = argv[2];
        const char *input = argv[3];
        size_t len = strlen(input);
        if(strcmp(mode, "-e") == 0 || strcmp(mode, "--encode") == 0) {
            if(argv[3] == NULL) printUsage(argv[0]);
            unsigned char *encoded = xorEncode(input, len);
            if(!encoded) return EXIT_FAILURE;
            printf("0x");
            for(size_t i = 0; i < len; ++i) printf("%02X", encoded[i]);
            printf("\n");
            free(encoded);
        }
        else if(strcmp(mode, "-d") == 0 || strcmp(mode, "--decode") == 0) {
            if(input == NULL) printUsage(argv[0]);
            if(strncmp(input, "0x", 2) == 0 || strncmp(input, "0X", 2) == 0) {
                input += 2;
                len -= 2;
            }
            if(len % 2 != 0) {
                fprintf(stderr, "Error: Hex input length must be even.\n");
                return EXIT_FAILURE;
            }
            size_t out_len = len / 2;
            unsigned char *bytes = malloc(out_len);
            if(!bytes) {
                perror("malloc");
                return EXIT_FAILURE;
            }
            for(size_t i = 0; i < out_len; ++i) {
                if(sscanf(&input[i * 2], "%2hhx", &bytes[i]) != 1) {
                    fprintf(stderr, "Error: Invalid hex character at position %zu.\n", i * 2);
                    free(bytes);
                    return EXIT_FAILURE;
                }
            }
            unsigned char *decoded = xorDecode(bytes, out_len);
            if(!decoded) {
                free(bytes);
                return EXIT_FAILURE;
            }
            printf("%s\n", decoded);
            free(decoded);
            free(bytes);
        }
        else {
            fprintf(stderr, "Unknown mode: %s\n", mode);
            printUsage(argv[0]);
        }
    }
    else printUsage(argv[0]);
    return EXIT_SUCCESS;
}