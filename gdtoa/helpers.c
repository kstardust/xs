/* Two conversion helpers from FreeBSD contrib/gdtoa. */
#include "gdtoaimp.h"

void
ULtod(ULong *words, ULong *bits, Long exponent, int kind)
{
    switch (kind & STRTOG_Retmask) {
    case STRTOG_NoNumber:
    case STRTOG_Zero:
        words[0] = words[1] = 0;
        break;
    case STRTOG_Denormal:
        words[_1] = bits[0];
        words[_0] = bits[1];
        break;
    case STRTOG_Normal:
    case STRTOG_NaNbits:
        words[_1] = bits[0];
        words[_0] = (bits[1] & ~0x100000) |
            ((exponent + 0x3ff + 52) << 20);
        break;
    case STRTOG_Infinite:
        words[_0] = 0x7ff00000;
        words[_1] = 0;
        break;
    case STRTOG_NaN:
        words[0] = d_QNAN0;
        words[1] = d_QNAN1;
        break;
    }
    if (kind & STRTOG_Neg)
        words[_0] |= 0x80000000L;
}

Bigint *
increment(Bigint *value)
{
    ULong *word = value->x;
    ULong *end = word + value->wds;
    Bigint *larger;

    do {
        if (*word < (ULong)0xffffffffL) {
            ++*word;
            return value;
        }
        *word++ = 0;
    } while (word < end);
    if (value->wds >= value->maxwds) {
        larger = Balloc(value->k + 1);
        Bcopy(larger, value);
        Bfree(value);
        value = larger;
    }
    value->x[value->wds++] = 1;
    return value;
}
