#include "../include/Utils.h"

#include <stdio.h>
#include <stdlib.h>

char *FileReadText(const char *filePath)
{
    FILE *file = fopen(filePath, "rb");

    if (!file)
        return NULL;

    size_t size;

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *text = malloc(size + 1);
    fread(text, size, 1, file);
    text[size] = 0;

    fclose(file);

    return text;
}

void *FileReadBytes(const char *filePath, int *size)
{
    FILE *file = fopen(filePath, "rb");

    if (!file)
        return NULL;

    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    fseek(file, 0, SEEK_SET);

    void *buffer = malloc(*size);
    fread(buffer, *size, 1, file);

    fclose(file);

    return buffer;
}

void FileFree(void *contents)
{
    free(contents);
}