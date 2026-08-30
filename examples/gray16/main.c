#ifdef _MSC_VER
#ifdef _DEBUG
#pragma comment(lib, "moreinttypesd.lib")
#else
#pragma comment(lib, "moreinttypes.lib")
#endif
#endif

#include <stdio.h>
#include <assert.h>
#include <moreinttypes/core.h>

uint8_t bin2gray(uint8_t n);
static uint32_t msb(uint32_t n, uint8_t width);
static uint8_t bit_at(uint32_t n, uint32_t pos);
static uint32_t pown(uint32_t e, uint32_t b);

int main(void)
{
    const uint8_t gray[16] = { 0x0, 0x1, 0x3, 0x2, 0x6, 0x7, 0x5, 0x4,
                               0xc, 0xd, 0xf, 0xe, 0xa, 0xb, 0x9, 0x8 };

    Byte n = byte(0);

    printf("%12s | %-14s\n", "Binary", "Gray Code");
    printf("%12s | %-14s\n", "------", "----------");

    for (uint8_t i = 0; i < 16; i++)
    {
        uint8_t result = bin2gray(i);
        assert(result == gray[i]);
        Byte g = byte(result);
        printf("%12s |", as_binary(n));
        printf(" %-14s\n", as_binary(g));
        increment(n);
    }
    return 0;
}

uint8_t bin2gray(uint8_t n)
{
    if (n < 2)
        return n;

    uint32_t head = msb(n, 4);
    uint8_t gray = 0x1 << head;
    for (int32_t i = head, j = 1; (i - 1) > -1; i--, j++)
    {
        uint8_t b = bit_at(n, i) ^ bit_at(n, i - 1);
        gray |= b << (head - j);
    }
    return gray;
}

uint32_t msb(uint32_t n, uint8_t width)
{
    uint32_t msb = 0;
    for (uint8_t i = 1; i < width; i++)
    {
        if (bit_at(n, i) == 1)
            msb = i;
    }
    return msb;
}

uint8_t bit_at(uint32_t n, uint32_t pos)
{
    return ((n & 0xf) & pown(2, pos)) >> pos;
}

uint32_t pown(uint32_t b, uint32_t e)
{
    if (e < 1)
        return 1;

    uint32_t p = b;
    for (uint32_t i = 1; i < e; i++, p *= b);
    return p;
}
