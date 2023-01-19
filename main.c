#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

static FILE* in_stream    = NULL;
static FILE* out_stream   = NULL;
static bool  should_print = 0;

static char chunk[1024]     = { 0 }; 
static char identifier[128] = { 0 };
static uint32_t chunk_index = 0;
static uint32_t chunk_len   = 0;

static bool get_chunk(void)
{
    // TODO: check error
    chunk_len = fread(chunk, 1, 1024, in_stream);
    return chunk_len > 0;
}

static bool get_identifier(void)
{
    for (; chunk_index < chunk_len; ++chunk_index) {
        if (should_print) {
            fputc(chunk[chunk_index], out_stream);
        }
    }
    if (!get_chunk()) {
        return 0;
    }
    get_identifier();
}


static void dump_chunk(void)
{
    fwrite(chunk, 1, chunk_len, out_stream);
}

int main(void)
{
    in_stream = stdin;
    out_stream = stdout;
    while(get_chunk()) {
        dump_chunk();
    }
    return 0;
}
