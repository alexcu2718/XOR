#include <xor.h>

unsigned char *xorEncode(const char *input, size_t len) {
    unsigned char *output = (unsigned char *)malloc(len);
    if(!output) return NULL;
    for(size_t i = 0; i < len; ++i) output[i] = input[i] ^ key;
    return output;
}

unsigned char *xorDecode(const unsigned char *input, size_t len) {
    unsigned char *output = (unsigned char *)malloc(len);
    if(!output) return NULL;
    for(size_t i = 0; i < len; ++i) output[i] = input[i] ^ key;
    output[len] = '\0';
    return output;
}

uint64_t xor64FileHash(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if(!file) {
        perror("Error opening file");
        return 0;
    }
    uint64_t hash = 0x1234DEADBEEF5678ULL;
    unsigned char key = key;
    unsigned char buffer[65536];
    size_t bytesRead;
    while((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        for(size_t i = 0; i < bytesRead; ++i) {
            hash ^= buffer[i] * key;
            hash = (hash << 5) | (hash >> (64 - 5));
            hash *= 0x100000001B3ULL;
            key = (key << 3) | (key >> 5); 
        }
    }
    fclose(file);
    return hash;
}

void printUsage(const char *prog) {
    printf("\033[1;36m─────────────────────────────────────────────────────\n");
    printf("\033[1;33mUsage:\033[0m \033[1;35m%s\033[0m \033[1;34m[OPTION]\033[0m \033[1;36m[SUB-OPTION]\033[0m \033[1;32m[FILE|STRING]\033[0m                   \n", basename(prog));
    printf("                                                                                                                                                      \n");
    printf("\033[1;32mOPTIONS:\033[0m                                                                                                                            \n");
    printf(" \033[1;36m-s\033[0m|\033[1;36m--string\033[0m : \033[0;33mSwitch to string-based operation                                                  \033[0m\n");
    printf(" \033[1;36m-f\033[0m|\033[1;36m--file\033[0m   : \033[0;33mSwitch to file-based operation                                                    \033[0m\n");
    printf("                                                                                                                                                      \n");
    printf("\033[1;32mSUB-OPTIONS:\033[0m                                                                                                                        \n");
    printf(" \033[1;36m-e\033[0m|\033[1;36m--encode\033[0m : \033[0;35mEncode input string and print hash                                                \033[0m\n");
    printf(" \033[1;36m-d\033[0m|\033[1;36m--decode\033[0m : \033[0;35mDecode base64 string and print result                                             \033[0m\n");
    printf(" \033[1;36m-f\033[0m|\033[1;36m--file\033[0m   : \033[0;35mGenerate 64-bit hash from file                                                    \033[0m\n");
    printf("                                                                                                                                                      \n");
    printf("\033[1;32mUSAGE-EXAMPLES:\033[0m                                                                                                                     \n");
    printf(" \033[1;33m%s\033[0m \033[1;36m-s -e\033[0m \033[1;32m\"Hello world!\"\033[0m         → \033[1;34mEncode string                              \033[0m\n", basename(prog));
    printf(" \033[1;33m%s\033[0m \033[1;36m-s -d\033[0m \033[1;32m\"SGVsbG8gd29ybGQh\"\033[0m      → \033[1;34mDecode string                             \033[0m\n", basename(prog));
    printf(" \033[1;33m%s\033[0m \033[1;36m-f\033[0m \033[1;32m\"./secure/file.bin\"\033[0m         → \033[1;34mHash file                                                                          \033[0m\n", basename(prog));
    printf("─────────────────────────────────────────────────────\n");
    exit(EXIT_FAILURE);
}