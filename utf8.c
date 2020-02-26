#include "utf8.h"
#include "types.h"

static usize
utf8validate(Rune *u, usize i)
{
        if (*u < utfmin[i] || *u > utfmax[i] || (0xD800 <= *u && *u <= 0xDFFF))
                *u = RuneInvalid;
        for (i = 1; *u > utfmax[i]; ++i);
        return i;
}

static Rune
utf8decodebyte(u8 c, usize *i)
{
        for (*i = 0; *i < UtfSz + 1; ++(*i))
                if ((c & utfmask[*i]) == utfbyte[*i])
                        return c & ~utfmask[*i];
        return 0;
}

usize
utf8decode(char *c, Rune *u, usize clen)
{
        usize i, j, len, type;
        Rune udecoded;

        *u = RuneInvalid;
        if (!clen)
                return 0;
        udecoded = utf8decodebyte(c[0], &len);
        if (len < 1 || len > UtfSz)
                return 1;
        for (i = 1, j = 1; i < clen && j < len; ++i, ++j) {
                udecoded = (udecoded << 6) | utf8decodebyte(c[i], &type);
                if (type != 0)
                        return j;
        }
        if (j < len)
                return 0;
        *u = udecoded;
        utf8validate(u, len);
        return len;
}

static char
utf8encodebyte(Rune u, usize i)
{
        return utfbyte[i] | (u & ~utfmask[i]);
}

static usize
utf8encode(Rune u, char *c)
{
        usize len, i;

        len = utf8validate(&u, 0);
        if (len > UtfSz)
                return 0;
        for (i = len - 1; i != 0; --i) {
                c[i] = utf8encodebyte(u, 0);
                u >>= 6;
        }
        c[0] = utf8encodebyte(u, len);
        return len;
}
