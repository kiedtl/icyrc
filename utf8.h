#ifndef UTF8_H
#define UTF8_H

#include "types.h"
#include "wchar.h"

typedef wchar_t Rune;

enum {
	UtfSz = 4,
	RuneInvalid = 0xFFFD,
};

static unsigned char utfbyte[UtfSz + 1] = {0x80,    0, 0xC0, 0xE0, 0xF0};
static unsigned char utfmask[UtfSz + 1] = {0xC0, 0x80, 0xE0, 0xF0, 0xF8};
static Rune utfmin[UtfSz + 1] = {       0,    0,  0x80,  0x800,  0x10000};
static Rune utfmax[UtfSz + 1] = {0x10FFFF, 0x7F, 0x7FF, 0xFFFF, 0x10FFFF};

static usize utf8validate(Rune *u, usize i);
static Rune  utf8decodebyte(u8 c, usize *i);
       usize utf8decode(char *c, Rune *u, usize clen);
static char  utf8encodebyte(Rune u, usize i);
static usize utf8encode(Rune u, char *c);

#endif
