/* This file is composed of several different files from the upstream
   sourceware.org CVS.  Original file boundaries marked with **** */

#include "qemu/osdep.h"
#include <math.h>

#include "disas/bfd.h"

/* **** floatformat.h from sourceware.org CVS 2005-08-14.  */
/* IEEE floating point support declarations, for GDB, the GNU Debugger.
   Copyright 1991, 1994, 1995, 1997, 2000, 2003 Free Software Foundation, Inc.

This file is part of GDB.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see <http://www.gnu.org/licenses/>.  */

#if !defined (FLOATFORMAT_H)
#define FLOATFORMAT_H 1

/*#include "ansidecl.h" */

/* A floatformat consists of a sign bit, an exponent and a mantissa.  Once the
   bytes are concatenated according to the byteorder flag, then each of those
   fields is contiguous.  We number the bits with 0 being the most significant
   (i.e. BITS_BIG_ENDIAN type numbering), and specify which bits each field
   contains with the *_start and *_len fields.  */

/* What is the order of the bytes. */

enum floatformat_byteorders {

  /* Standard little endian byte order.
     EX: 1.2345678e10 => 00 00 80 c5 e0 fe 06 42 */

  floatformat_little,

  /* Standard big endian byte order.
     EX: 1.2345678e10 => 42 06 fe e0 c5 80 00 00 */

  floatformat_big,

  /* Little endian byte order but big endian word order.
     EX: 1.2345678e10 => e0 fe 06 42 00 00 80 c5 */

  floatformat_littlebyte_bigword

};

enum floatformat_intbit { floatformat_intbit_yes, floatformat_intbit_no };

struct floatformat
{
  enum floatformat_byteorders byteorder;
  unsigned int totalsize;	/* Total size of number in bits */

  /* Sign bit is always one bit long.  1 means negative, 0 means positive.  */
  unsigned int sign_start;

  unsigned int exp_start;
  unsigned int exp_len;
  /* Bias added to a "true" exponent to form the biased exponent.  It
     is intentionally signed as, otherwize, -exp_bias can turn into a
     very large number (e.g., given the exp_bias of 0x3fff and a 64
     bit long, the equation (long)(1 - exp_bias) evaluates to
     4294950914) instead of -16382).  */
  int exp_bias;
  /* Exponent value which indicates NaN.  This is the actual value stored in
     the float, not adjusted by the exp_bias.  This usually consists of all
     one bits.  */
  unsigned int exp_nan;

  unsigned int man_start;
  unsigned int man_len;

  /* Is the integer bit explicit or implicit?  */
  enum floatformat_intbit intbit;

  /* Internal name for debugging. */
  const char *name;

  /* Validator method.  */
  int (*is_valid) (const struct floatformat *fmt, const char *from);
};

/* floatformats for IEEE single and double, big and little endian.  */

extern const struct floatformat floatformat_ieee_single_big;
extern const struct floatformat floatformat_ieee_single_little;
extern const struct floatformat floatformat_ieee_double_big;
extern const struct floatformat floatformat_ieee_double_little;

/* floatformat for ARM IEEE double, little endian bytes and big endian words */

extern const struct floatformat floatformat_ieee_double_littlebyte_bigword;

/* floatformats for various extendeds.  */

extern const struct floatformat floatformat_i387_ext;
extern const struct floatformat floatformat_m68881_ext;
extern const struct floatformat floatformat_i960_ext;
extern const struct floatformat floatformat_m88110_ext;
extern const struct floatformat floatformat_m88110_harris_ext;
extern const struct floatformat floatformat_arm_ext_big;
extern const struct floatformat floatformat_arm_ext_littlebyte_bigword;
/* IA-64 Floating Point register spilt into memory.  */
extern const struct floatformat floatformat_ia64_spill_big;
extern const struct floatformat floatformat_ia64_spill_little;
extern const struct floatformat floatformat_ia64_quad_big;
extern const struct floatformat floatformat_ia64_quad_little;

/* Convert from FMT to a double.
   FROM is the address of the extended float.
   Store the double in *TO.  */

extern void
floatformat_to_double (const struct floatformat *, const char *, double *);

/* The converse: convert the double *FROM to FMT
   and store where TO points.  */

extern void
floatformat_from_double (const struct floatformat *, const double *, char *);

/* Return non-zero iff the data at FROM is a valid number in format FMT.  */

extern int
floatformat_is_valid (const struct floatformat *fmt, const char *from);

#endif	/* defined (FLOATFORMAT_H) */
/* **** End of floatformat.h */
/* **** m68k-dis.h from sourceware.org CVS 2005-08-14.  */
/* Opcode table header for m680[01234]0/m6888[12]/m68851.
   Copyright 1989, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1999, 2001,
   2003, 2004 Free Software Foundation, Inc.

   This file is part of GDB, GAS, and the GNU binutils.

   GDB, GAS, and the GNU binutils are free software; you can redistribute
   them and/or modify them under the terms of the GNU General Public
   License as published by the Free Software Foundation; either version
   1, or (at your option) any later version.

   GDB, GAS, and the GNU binutils are distributed in the hope that they
   will be useful, but WITHOUT ANY WARRANTY; without even the implied
   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
   the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this file; see the file COPYING.  If not,
   see <http://www.gnu.org/licenses/>.  */

/* These are used as bit flags for the arch field in the m68k_opcode
   structure.  */
#define	_m68k_undef  0
#define	m68000   0x001
#define	m68008   m68000 /* Synonym for -m68000.  otherwise unused.  */
#define	m68010   0x002
#define	m68020   0x004
#define	m68030   0x008
#define m68ec030 m68030 /* Similar enough to -m68030 to ignore differences;
			   gas will deal with the few differences.  */
#define	m68040   0x010
/* There is no 68050.  */
#define m68060   0x020
#define	m68881   0x040
#define	m68882   m68881 /* Synonym for -m68881.  otherwise unused.  */
#define	m68851   0x080
#define cpu32	 0x100		/* e.g., 68332 */

#define mcfmac   0x200		/* ColdFire MAC. */
#define mcfemac  0x400		/* ColdFire EMAC. */
#define cfloat   0x800		/* ColdFire FPU.  */
#define mcfhwdiv 0x1000		/* ColdFire hardware divide.  */

#define mcfisa_a 0x2000		/* ColdFire ISA_A.  */
#define mcfisa_aa 0x4000	/* ColdFire ISA_A+.  */
#define mcfisa_b 0x8000		/* ColdFire ISA_B.  */
#define mcfusp   0x10000	/* ColdFire USP instructions.  */

#define mcf5200  0x20000
#define mcf5206e 0x40000
#define mcf521x  0x80000
#define mcf5249  0x100000
#define mcf528x  0x200000
#define mcf5307  0x400000
#define mcf5407  0x800000
#define mcf5470  0x1000000
#define mcf5480  0x2000000

 /* Handy aliases.  */
#define	m68040up   (m68040 | m68060)
#define	m68030up   (m68030 | m68040up)
#define	m68020up   (m68020 | m68030up)
#define	m68010up   (m68010 | cpu32 | m68020up)
#define	m68000up   (m68000 | m68010up)

#define	mfloat  (m68881 | m68882 | m68040 | m68060)
#define	mmmu    (m68851 | m68030 | m68040 | m68060)

/* The structure used to hold information for an opcode.  */

struct m68k_opcode
{
  /* The opcode name.  */
  const char *name;
  /* The pseudo-size of the instruction(in bytes).  Used to determine
     number of bytes necessary to disassemble the instruction.  */
  unsigned int size;
  /* The opcode itself.  */
  unsigned long opcode;
  /* The mask used by the disassembler.  */
  unsigned long match;
  /* The arguments.  */
  const char *args;
  /* The architectures which support this opcode.  */
  unsigned int arch;
};

/* The structure used to hold information for an opcode alias.  */

struct m68k_opcode_alias
{
  /* The alias name.  */
  const char *alias;
  /* The instruction for which this is an alias.  */
  const char *primary;
};

/* We store four bytes of opcode for all opcodes because that is the
   most any of them need.  The actual length of an instruction is
   always at least 2 bytes, and is as much longer as necessary to hold
   the operands it has.

   The match field is a mask saying which bits must match particular
   opcode in order for an instruction to be an instance of that
   opcode.

   The args field is a string containing two characters for each
   operand of the instruction.  The first specifies the kind of
   operand; the second, the place it is stored.  */

/* Kinds of operands:
   Characters used: AaBbCcDdEeFfGgHIiJkLlMmnOopQqRrSsTtU VvWwXxYyZz01234|*~%;@!&$?/<>#^+-

   D  data register only.  Stored as 3 bits.
   A  address register only.  Stored as 3 bits.
   a  address register indirect only.  Stored as 3 bits.
   R  either kind of register.  Stored as 4 bits.
   r  either kind of register indirect only.  Stored as 4 bits.
      At the moment, used only for cas2 instruction.
   F  floating point coprocessor register only.   Stored as 3 bits.
   O  an offset (or width): immediate data 0-31 or data register.
      Stored as 6 bits in special format for BF... insns.
   +  autoincrement only.  Stored as 3 bits (number of the address register).
   -  autodecrement only.  Stored as 3 bits (number of the address register).
   Q  quick immediate data.  Stored as 3 bits.
      This matches an immediate operand only when value is in range 1 .. 8.
   M  moveq immediate data.  Stored as 8 bits.
      This matches an immediate operand only when value is in range -128..127
   T  trap vector immediate data.  Stored as 4 bits.

   k  K-factor for fmove.p instruction.   Stored as a 7-bit constant or
      a three bit register offset, depending on the field type.

   #  immediate data.  Stored in special places (b, w or l)
      which say how many bits to store.
   ^  immediate data for floating point instructions.   Special places
      are offset by 2 bytes from '#'...
   B  pc-relative address, converted to an offset
      that is treated as immediate data.
   d  displacement and register.  Stores the register as 3 bits
      and stores the displacement in the entire second word.

   C  the CCR.  No need to store it; this is just for filtering validity.
   S  the SR.  No need to store, just as with CCR.
   U  the USP.  No need to store, just as with CCR.
   E  the MAC ACC.  No need to store, just as with CCR.
   e  the EMAC ACC[0123].
   G  the MAC/EMAC MACSR.  No need to store, just as with CCR.
   g  the EMAC ACCEXT{01,23}.
   H  the MASK.  No need to store, just as with CCR.
   i  the MAC/EMAC scale factor.

   I  Coprocessor ID.   Not printed if 1.   The Coprocessor ID is always
      extracted from the 'd' field of word one, which means that an extended
      coprocessor opcode can be skipped using the 'i' place, if needed.

   s  System Control register for the floating point coprocessor.

   J  Misc register for movec instruction, stored in 'j' format.
	Possible values:
	0x000	SFC	Source Function Code reg	[60, 40, 30, 20, 10]
	0x001	DFC	Data Function Code reg		[60, 40, 30, 20, 10]
	0x002   CACR    Cache Control Register          [60, 40, 30, 20, mcf]
	0x003	TC	MMU Translation Control		[60, 40]
	0x004	ITT0	Instruction Transparent
				Translation reg 0	[60, 40]
	0x005	ITT1	Instruction Transparent
				Translation reg 1	[60, 40]
	0x006	DTT0	Data Transparent
				Translation reg 0	[60, 40]
	0x007	DTT1	Data Transparent
				Translation reg 1	[60, 40]
	0x008	BUSCR	Bus Control Register		[60]
	0x800	USP	User Stack Pointer		[60, 40, 30, 20, 10]
        0x801   VBR     Vector Base reg                 [60, 40, 30, 20, 10, mcf]
	0x802	CAAR	Cache Address Register		[        30, 20]
	0x803	MSP	Master Stack Pointer		[    40, 30, 20]
	0x804	ISP	Interrupt Stack Pointer		[    40, 30, 20]
	0x805	MMUSR	MMU Status reg			[    40]
	0x806	URP	User Root Pointer		[60, 40]
	0x807	SRP	Supervisor Root Pointer		[60, 40]
	0x808	PCR	Processor Configuration reg	[60]
	0xC00	ROMBAR	ROM Base Address Register	[520X]
	0xC04	RAMBAR0	RAM Base Address Register 0	[520X]
	0xC05	RAMBAR1	RAM Base Address Register 0	[520X]
	0xC0F	MBAR0	RAM Base Address Register 0	[520X]
        0xC04   FLASHBAR FLASH Base Address Register    [mcf528x]
        0xC05   RAMBAR  Static RAM Base Address Register [mcf528x]

    L  Register list of the type d0-d7/a0-a7 etc.
       (New!  Improved!  Can also hold fp0-fp7, as well!)
       The assembler tries to see if the registers match the insn by
       looking at where the insn wants them stored.

    l  Register list like L, but with all the bits reversed.
       Used for going the other way. . .

    c  cache identifier which may be "nc" for no cache, "ic"
       for instruction cache, "dc" for data cache, or "bc"
       for both caches.  Used in cinv and cpush.  Always
       stored in position "d".

    u  Any register, with ``upper'' or ``lower'' specification.  Used
       in the mac instructions with size word.

 The remainder are all stored as 6 bits using an address mode and a
 register number; they differ in which addressing modes they match.

   *  all					(modes 0-6,7.0-4)
   ~  alterable memory				(modes 2-6,7.0,7.1)
   						(not 0,1,7.2-4)
   %  alterable					(modes 0-6,7.0,7.1)
						(not 7.2-4)
   ;  data					(modes 0,2-6,7.0-4)
						(not 1)
   @  data, but not immediate			(modes 0,2-6,7.0-3)
						(not 1,7.4)
   !  control					(modes 2,5,6,7.0-3)
						(not 0,1,3,4,7.4)
   &  alterable control				(modes 2,5,6,7.0,7.1)
						(not 0,1,3,4,7.2-4)
   $  alterable data				(modes 0,2-6,7.0,7.1)
						(not 1,7.2-4)
   ?  alterable control, or data register	(modes 0,2,5,6,7.0,7.1)
						(not 1,3,4,7.2-4)
   /  control, or data register			(modes 0,2,5,6,7.0-3)
						(not 1,3,4,7.4)
   >  *save operands				(modes 2,4,5,6,7.0,7.1)
						(not 0,1,3,7.2-4)
   <  *restore operands				(modes 2,3,5,6,7.0-3)
						(not 0,1,4,7.4)

   coldfire move operands:
   m  						(modes 0-4)
   n						(modes 5,7.2)
   o						(modes 6,7.0,7.1,7.3,7.4)
   p						(modes 0-5)

   coldfire bset/bclr/btst/mulsl/mulul operands:
   q						(modes 0,2-5)
   v						(modes 0,2-5,7.0,7.1)
   b                                            (modes 0,2-5,7.2)
   w                                            (modes 2-5,7.2)
   y						(modes 2,5)
   z						(modes 2,5,7.2)
   x  mov3q immediate operand.
   4						(modes 2,3,4,5)
  */

/* For the 68851:  */
/* I didn't use much imagination in choosing the
   following codes, so many of them aren't very
   mnemonic. -rab

   0  32 bit pmmu register
	Possible values:
	000	TC	Translation Control Register (68030, 68851)

   1  16 bit pmmu register
	111	AC	Access Control (68851)

   2  8 bit pmmu register
	100	CAL	Current Access Level (68851)
	101	VAL	Validate Access Level (68851)
	110	SCC	Stack Change Control (68851)

   3  68030-only pmmu registers (32 bit)
	010	TT0	Transparent Translation reg 0
			(aka Access Control reg 0 -- AC0 -- on 68ec030)
	011	TT1	Transparent Translation reg 1
			(aka Access Control reg 1 -- AC1 -- on 68ec030)

   W  wide pmmu registers
	Possible values:
	001	DRP	Dma Root Pointer (68851)
	010	SRP	Supervisor Root Pointer (68030, 68851)
	011	CRP	Cpu Root Pointer (68030, 68851)

   f	function code register (68030, 68851)
	0	SFC
	1	DFC

   V	VAL register only (68851)

   X	BADx, BACx (16 bit)
	100	BAD	Breakpoint Acknowledge Data (68851)
	101	BAC	Breakpoint Acknowledge Control (68851)

   Y	PSR (68851) (MMUSR on 68030) (ACUSR on 68ec030)
   Z	PCSR (68851)

   |	memory 		(modes 2-6, 7.*)

   t  address test level (68030 only)
      Stored as 3 bits, range 0-7.
      Also used for breakpoint instruction now.

*/

/* Places to put an operand, for non-general operands:
   Characters used: BbCcDdFfGgHhIijkLlMmNnostWw123456789/

   s  source, low bits of first word.
   d  dest, shifted 9 in first word
   1  second word, shifted 12
   2  second word, shifted 6
   3  second word, shifted 0
   4  third word, shifted 12
   5  third word, shifted 6
   6  third word, shifted 0
   7  second word, shifted 7
   8  second word, shifted 10
   9  second word, shifted 5
   D  store in both place 1 and place 3; for divul and divsl.
   B  first word, low byte, for branch displacements
   W  second word (entire), for branch displacements
   L  second and third words (entire), for branch displacements
      (also overloaded for move16)
   b  second word, low byte
   w  second word (entire) [variable word/long branch offset for dbra]
   W  second word (entire) (must be signed 16 bit value)
   l  second and third word (entire)
   g  variable branch offset for bra and similar instructions.
      The place to store depends on the magnitude of offset.
   t  store in both place 7 and place 8; for floating point operations
   c  branch offset for cpBcc operations.
      The place to store is word two if bit six of word one is zero,
      and words two and three if bit six of word one is one.
   i  Increment by two, to skip over coprocessor extended operands.   Only
      works with the 'I' format.
   k  Dynamic K-factor field.   Bits 6-4 of word 2, used as a register number.
      Also used for dynamic fmovem instruction.
   C  floating point coprocessor constant - 7 bits.  Also used for static
      K-factors...
   j  Movec register #, stored in 12 low bits of second word.
   m  For M[S]ACx; 4 bits split with MSB shifted 6 bits in first word
      and remaining 3 bits of register shifted 9 bits in first word.
      Indicate upper/lower in 1 bit shifted 7 bits in second word.
      Use with `R' or `u' format.
   n  `m' withouth upper/lower indication. (For M[S]ACx; 4 bits split
      with MSB shifted 6 bits in first word and remaining 3 bits of
      register shifted 9 bits in first word.  No upper/lower
      indication is done.)  Use with `R' or `u' format.
   o  For M[S]ACw; 4 bits shifted 12 in second word (like `1').
      Indicate upper/lower in 1 bit shifted 7 bits in second word.
      Use with `R' or `u' format.
   M  For M[S]ACw; 4 bits in low bits of first word.  Indicate
      upper/lower in 1 bit shifted 6 bits in second word.  Use with
      `R' or `u' format.
   N  For M[S]ACw; 4 bits in low bits of second word.  Indicate
      upper/lower in 1 bit shifted 6 bits in second word.  Use with
      `R' or `u' format.
   h  shift indicator (scale factor), 1 bit shifted 10 in second word

 Places to put operand, for general operands:
   d  destination, shifted 6 bits in first word
   b  source, at low bit of first word, and immediate uses one byte
   w  source, at low bit of first word, and immediate uses two bytes
   l  source, at low bit of first word, and immediate uses four bytes
   s  source, at low bit of first word.
      Used sometimes in contexts where immediate is not allowed anyway.
   f  single precision float, low bit of 1st word, immediate uses 4 bytes
   F  double precision float, low bit of 1st word, immediate uses 8 bytes
   x  extended precision float, low bit of 1st word, immediate uses 12 bytes
   p  packed float, low bit of 1st word, immediate uses 12 bytes
   G  EMAC accumulator, load  (bit 4 2nd word, !bit8 first word)
   H  EMAC accumulator, non load  (bit 4 2nd word, bit 8 first word)
   F  EMAC ACCx
   f  EMAC ACCy
   I  MAC/EMAC scale factor
   /  Like 's', but set 2nd word, bit 5 if trailing_ampersand set
   ]  first word, bit 10
*/

extern const struct m68k_opcode m68k_opcodes[];
extern const struct m68k_opcode_alias m68k_opcode_aliases[];

extern const int m68k_numopcodes, m68k_numaliases;

/* **** End of m68k-opcode.h */
/* **** m68k-dis.c from sourceware.org CVS 2005-08-14.  */
/* Print Motorola 68k instructions.
   Copyright 1986, 1987, 1989, 1991, 1992, 1993, 1994, 1995, 1996, 1997,
   1998, 1999, 2000, 2001, 2002, 2003, 2004, 2005
   Free Software Foundation, Inc.

   This file is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, see <http://www.gnu.org/licenses/>.  */

/* Local function prototypes.  */

static const char * const fpcr_names[] =
{
  "", "%fpiar", "%fpsr", "%fpiar/%fpsr", "%fpcr",
  "%fpiar/%fpcr", "%fpsr/%fpcr", "%fpiar/%fpsr/%fpcr"
};

static const char *const reg_names[] =
{
  "%d0", "%d1", "%d2", "%d3", "%d4", "%d5", "%d6", "%d7",
  "%a0", "%a1", "%a2", "%a3", "%a4", "%a5", "%fp", "%sp",
  "%ps", "%pc"
};

/* Name of register halves for MAC/EMAC.
   Separate from reg_names since 'spu', 'fpl' look weird.  */
static const char *const reg_half_names[] =
{
  "%d0", "%d1", "%d2", "%d3", "%d4", "%d5", "%d6", "%d7",
  "%a0", "%a1", "%a2", "%a3", "%a4", "%a5", "%a6", "%a7",
  "%ps", "%pc"
};

/* Sign-extend an (unsigned char).  */
#if __STDC__ == 1
#define COERCE_SIGNED_CHAR(ch) ((signed char) (ch))
#else
#define COERCE_SIGNED_CHAR(ch) ((int) (((ch) ^ 0x80) & 0xFF) - 128)
#endif

/* Get a 1 byte signed integer.  */
#define NEXTBYTE(p)  (p += 2, fetch_data(info, p), COERCE_SIGNED_CHAR(p[-1]))

/* Get a 2 byte signed integer.  */
#define COERCE16(x) ((int) (((x) ^ 0x8000) - 0x8000))
#define NEXTWORD(p)  \
  (p += 2, fetch_data(info, p), \
   COERCE16 ((p[-2] << 8) + p[-1]))

/* Get a 4 byte signed integer.  */
#define COERCE32(x) ((bfd_signed_vma) ((x) ^ 0x80000000) - 0x80000000)
#define NEXTLONG(p)  \
  (p += 4, fetch_data(info, p), \
   (COERCE32 ((((((p[-4] << 8) + p[-3]) << 8) + p[-2]) << 8) + p[-1])))

/* Get a 4 byte unsigned integer.  */
#define NEXTULONG(p)  \
  (p += 4, fetch_data(info, p), \
   (unsigned int) ((((((p[-4] << 8) + p[-3]) << 8) + p[-2]) << 8) + p[-1]))

/* Get a single precision float.  */
#define NEXTSINGLE(val, p) \
  (p += 4, fetch_data(info, p), \
   floatformat_to_double (&floatformat_ieee_single_big, (char *) p - 4, &val))

/* Get a double precision float.  */
#define NEXTDOUBLE(val, p) \
  (p += 8, fetch_data(info, p), \
   floatformat_to_double (&floatformat_ieee_double_big, (char *) p - 8, &val))

/* Get an extended precision float.  */
#define NEXTEXTEND(val, p) \
  (p += 12, fetch_data(info, p), \
   floatformat_to_double (&floatformat_m68881_ext, (char *) p - 12, &val))

/* Need a function to convert from packed to double
   precision.   Actually, it's easier to print a
   packed number than a double anyway, so maybe
   there should be a special case to handle this... */
#define NEXTPACKED(p) \
  (p += 12, fetch_data(info, p), 0.0)

/* Maximum length of an instruction.  */
#define MAXLEN 22

struct private
{
  /* Points to first byte not fetched.  */
  bfd_byte *max_fetched;
  bfd_byte the_buffer[MAXLEN];
  bfd_vma insn_start;
  sigjmp_buf bailout;
};

/* Make sure that bytes from INFO->PRIVATE_DATA->BUFFER (inclusive)
   to ADDR (exclusive) are valid.  Returns 1 for success, longjmps
   on error.  */
static int
fetch_data2(struct disassemble_info *info, bfd_byte *addr)
{
  int status;
  struct private *priv = (struct private *)info->private_data;
  bfd_vma start = priv->insn_start + (priv->max_fetched - priv->the_buffer);

  status = (*info->read_memory_func) (start,
				      priv->max_fetched,
				      addr - priv->max_fetched,
				      info);
  if (status != 0)
    {
      (*info->memory_error_func) (status, start, info);
      siglongjmp(priv->bailout, 1);
    }
  else
    priv->max_fetched = addr;
  return 1;
}

static int
fetch_data(struct disassemble_info *info, bfd_byte *addr)
{
    if (addr <= ((struct private *) (info->private_data))->max_fetched) {
        return 1;
    } else {
        return fetch_data2(info, addr);
    }
}

/* This function is used to print to the bit-bucket.  */
static int
dummy_printer (FILE *file ATTRIBUTE_UNUSED,
	       const char *format ATTRIBUTE_UNUSED,
	       ...)
{
  return 0;
}

static void
dummy_print_address (bfd_vma vma ATTRIBUTE_UNUSED,
		     struct disassemble_info *info ATTRIBUTE_UNUSED)
{
}

/* Fetch BITS bits from a position in the instruction specified by CODE.
   CODE is a "place to put an argument", or 'x' for a destination
   that is a general address (mode and register).
   BUFFER contains the instruction.  */

static int
fetch_arg (unsigned char *buffer,
	   int code,
	   int bits,
	   disassemble_info *info)
{
  int val = 0;

  switch (code)
    {
    case '/': /* MAC/EMAC mask bit.  */
      val = buffer[3] >> 5;
      break;

    case 'G': /* EMAC ACC load.  */
      val = ((buffer[3] >> 3) & 0x2) | ((~buffer[1] >> 7) & 0x1);
      break;

    case 'H': /* EMAC ACC !load.  */
      val = ((buffer[3] >> 3) & 0x2) | ((buffer[1] >> 7) & 0x1);
      break;

    case ']': /* EMAC ACCEXT bit.  */
      val = buffer[0] >> 2;
      break;

    case 'I': /* MAC/EMAC scale factor.  */
      val = buffer[2] >> 1;
      break;

    case 'F': /* EMAC ACCx.  */
      val = buffer[0] >> 1;
      break;

    case 'f':
      val = buffer[1];
      break;

    case 's':
      val = buffer[1];
      break;

    case 'd':			/* Destination, for register or quick.  */
      val = (buffer[0] << 8) + buffer[1];
      val >>= 9;
      break;

    case 'x':			/* Destination, for general arg.  */
      val = (buffer[0] << 8) + buffer[1];
      val >>= 6;
      break;

    case 'k':
      fetch_data(info, buffer + 3);
      val = (buffer[3] >> 4);
      break;

    case 'C':
      fetch_data(info, buffer + 3);
      val = buffer[3];
      break;

    case '1':
      fetch_data(info, buffer + 3);
      val = (buffer[2] << 8) + buffer[3];
      val >>= 12;
      break;

    case '2':
      fetch_data(info, buffer + 3);
      val = (buffer[2] << 8) + buffer[3];
      val >>= 6;
      break;

    case '3':
    case 'j':
      fetch_data(info, buffer + 3);
      val = (buffer[2] << 8) + buffer[3];
      break;

    case '4':
      fetch_data(info, buffer + 5);
      val = (buffer[4] << 8) + buffer[5];
      val >>= 12;
      break;

    case '5':
      fetch_data(info, buffer + 5);
      val = (buffer[4] << 8) + buffer[5];
      val >>= 6;
      break;

    case '6':
      fetch_data(info, buffer + 5);
      val = (buffer[4] << 8) + buffer[5];
      break;

    case '7':
      fetch_data(info, buffer + 3);
      val = (buffer[2] << 8) + buffer[3];
      val >>= 7;
      break;

    case '8':
      fetch_data(info, buffer + 3);
      val = (buffer[2] << 8) + buffer[3];
      val >>= 10;
      break;

    case '9':
      fetch_data(info, buffer + 3);
      val = (buffer[2] << 8) + buffer[3];
      val >>= 5;
      break;

    case 'e':
      val = (buffer[1] >> 6);
      break;

    case 'm':
      val = (buffer[1] & 0x40 ? 0x8 : 0)
	| ((buffer[0] >> 1) & 0x7)
	| (buffer[3] & 0x80 ? 0x10 : 0);
      break;

    case 'n':
      val = (buffer[1] & 0x40 ? 0x8 : 0) | ((buffer[0] >> 1) & 0x7);
      break;

    case 'o':
      val = (buffer[2] >> 4) | (buffer[3] & 0x80 ? 0x10 : 0);
      break;

    case 'M':
      val = (buffer[1] & 0xf) | (buffer[3] & 0x40 ? 0x10 : 0);
      break;

    case 'N':
      val = (buffer[3] & 0xf) | (buffer[3] & 0x40 ? 0x10 : 0);
      break;

    case 'h':
      val = buffer[2] >> 2;
      break;

    default:
      abort ();
    }

  switch (bits)
    {
    case 1:
      return val & 1;
    case 2:
      return val & 3;
    case 3:
      return val & 7;
    case 4:
      return val & 017;
    case 5:
      return val & 037;
    case 6:
      return val & 077;
    case 7:
      return val & 0177;
    case 8:
      return val & 0377;
    case 12:
      return val & 07777;
    default:
      abort ();
    }
}

/* Check if an EA is valid for a particular code.  This is required
   for the EMAC instructions since the type of source address determines
   if it is a EMAC-load instruciton if the EA is mode 2-5, otherwise it
   is a non-load EMAC instruction and the bits mean register Ry.
   A similar case exists for the movem instructions where the register
   mask is interpreted differently for different EAs.  */

static bfd_boolean
m68k_valid_ea (char code, int val)
{
  int mode, mask;
#define M(n0,n1,n2,n3,n4,n5,n6,n70,n71,n72,n73,n74) \
  (n0 | n1 << 1 | n2 << 2 | n3 << 3 | n4 << 4 | n5 << 5 | n6 << 6 \
   | n70 << 7 | n71 << 8 | n72 << 9 | n73 << 10 | n74 << 11)

  switch (code)
    {
    case '*':
      mask = M (1,1,1,1,1,1,1,1,1,1,1,1);
      break;
    case '~':
      mask = M (0,0,1,1,1,1,1,1,1,0,0,0);
      break;
    case '%':
      mask = M (1,1,1,1,1,1,1,1,1,0,0,0);
      break;
    case ';':
      mask = M (1,0,1,1,1,1,1,1,1,1,1,1);
      break;
    case '@':
      mask = M (1,0,1,1,1,1,1,1,1,1,1,0);
      break;
    case '!':
      mask = M (0,0,1,0,0,1,1,1,1,1,1,0);
      break;
    case '&':
      mask = M (0,0,1,0,0,1,1,1,1,0,0,0);
      break;
    case '$':
      mask = M (1,0,1,1,1,1,1,1,1,0,0,0);
      break;
    case '?':
      mask = M (1,0,1,0,0,1,1,1,1,0,0,0);
      break;
    case '/':
      mask = M (1,0,1,0,0,1,1,1,1,1,1,0);
      break;
    case '|':
      mask = M (0,0,1,0,0,1,1,1,1,1,1,0);
      break;
    case '>':
      mask = M (0,0,1,0,1,1,1,1,1,0,0,0);
      break;
    case '<':
      mask = M (0,0,1,1,0,1,1,1,1,1,1,0);
      break;
    case 'm':
      mask = M (1,1,1,1,1,0,0,0,0,0,0,0);
      break;
    case 'n':
      mask = M (0,0,0,0,0,1,0,0,0,1,0,0);
      break;
    case 'o':
      mask = M (0,0,0,0,0,0,1,1,1,0,1,1);
      break;
    case 'p':
      mask = M (1,1,1,1,1,1,0,0,0,0,0,0);
      break;
    case 'q':
      mask = M (1,0,1,1,1,1,0,0,0,0,0,0);
      break;
    case 'v':
      mask = M (1,0,1,1,1,1,0,1,1,0,0,0);
      break;
    case 'b':
      mask = M (1,0,1,1,1,1,0,0,0,1,0,0);
      break;
    case 'w':
      mask = M (0,0,1,1,1,1,0,0,0,1,0,0);
      break;
    case 'y':
      mask = M (0,0,1,0,0,1,0,0,0,0,0,0);
      break;
    case 'z':
      mask = M (0,0,1,0,0,1,0,0,0,1,0,0);
      break;
    case '4':
      mask = M (0,0,1,1,1,1,0,0,0,0,0,0);
      break;
    default:
      abort ();
    }
#undef M

  mode = (val >> 3) & 7;
  if (mode == 7)
    mode += val & 7;
  return (mask & (1 << mode)) != 0;
}

/* Print a base register REGNO and displacement DISP, on INFO->STREAM.
   REGNO = -1 for pc, -2 for none (suppressed).  */

static void
print_base (int regno, bfd_vma disp, disassemble_info *info)
{
  if (regno == -1)
    {
      (*info->fprintf_func) (info->stream, "%%pc@(");
      (*info->print_address_func) (disp, info);
    }
  else
    {
      char buf[50];

      if (regno == -2)
	(*info->fprintf_func) (info->stream, "@(");
      else if (regno == -3)
	(*info->fprintf_func) (info->stream, "%%zpc@(");
      else
	(*info->fprintf_func) (info->stream, "%s@(", reg_names[regno]);

      sprintf_vma (buf, disp);
      (*info->fprintf_func) (info->stream, "%s", buf);
    }
}

/* Print an indexed argument.  The base register is BASEREG (-1 for pc).
   P points to extension word, in buffer.
   ADDR is the nominal core address of that extension word.  */

static unsigned char *
print_indexed (int basereg,
	       unsigned char *p,
	       bfd_vma addr,
	       disassemble_info *info)
{
  int word;
  static const char *const scales[] = { "", ":2", ":4", ":8" };
  bfd_vma base_disp;
  bfd_vma outer_disp;
  char buf[40];
  char vmabuf[50];

  word = NEXTWORD (p);

  /* Generate the text for the index register.
     Where this will be output is not yet determined.  */
  sprintf (buf, "%s:%c%s",
	   reg_names[(word >> 12) & 0xf],
	   (word & 0x800) ? 'l' : 'w',
	   scales[(word >> 9) & 3]);

  /* Handle the 68000 style of indexing.  */

  if ((word & 0x100) == 0)
    {
      base_disp = word & 0xff;
      if ((base_disp & 0x80) != 0)
	base_disp -= 0x100;
      if (basereg == -1)
	base_disp += addr;
      print_base (basereg, base_disp, info);
      (*info->fprintf_func) (info->stream, ",%s)", buf);
      return p;
    }

  /* Handle the generalized kind.  */
  /* First, compute the displacement to add to the base register.  */
  if (word & 0200)
    {
      if (basereg == -1)
	basereg = -3;
      else
	basereg = -2;
    }
  if (word & 0100)
    buf[0] = '\0';
  base_disp = 0;
  switch ((word >> 4) & 3)
    {
    case 2:
      base_disp = NEXTWORD (p);
      break;
    case 3:
      base_disp = NEXTLONG (p);
    }
  if (basereg == -1)
    base_disp += addr;

  /* Handle single-level case (not indirect).  */
  if ((word & 7) == 0)
    {
      print_base (basereg, base_disp, info);
      if (buf[0] != '\0')
	(*info->fprintf_func) (info->stream, ",%s", buf);
      (*info->fprintf_func) (info->stream, ")");
      return p;
    }

  /* Two level.  Compute displacement to add after indirection.  */
  outer_disp = 0;
  switch (word & 3)
    {
    case 2:
      outer_disp = NEXTWORD (p);
      break;
    case 3:
      outer_disp = NEXTLONG (p);
    }

  print_base (basereg, base_disp, info);
  if ((word & 4) == 0 && buf[0] != '\0')
    {
      (*info->fprintf_func) (info->stream, ",%s", buf);
      buf[0] = '\0';
    }
  sprintf_vma (vmabuf, outer_disp);
  (*info->fprintf_func) (info->stream, ")@(%s", vmabuf);
  if (buf[0] != '\0')
    (*info->fprintf_func) (info->stream, ",%s", buf);
  (*info->fprintf_func) (info->stream, ")");

  return p;
}

/* Returns number of bytes "eaten" by the operand, or
   return -1 if an invalid operand was found, or -2 if
   an opcode tabe error was found.
   ADDR is the pc for this arg to be relative to.  */

static int
print_insn_arg (const char *d,
		unsigned char *buffer,
		unsigned char *p0,
		bfd_vma addr,
		disassemble_info *info)
{
  int val = 0;
  int place = d[1];
  unsigned char *p = p0;
  int regno;
  const char *regname;
  unsigned char *p1;
  double flval;
  int flt_p;
  bfd_signed_vma disp;
  unsigned int uval;

  switch (*d)
    {
    case 'c':		/* Cache identifier.  */
      {
        static const char *const cacheFieldName[] = { "nc", "dc", "ic", "bc" };
        val = fetch_arg (buffer, place, 2, info);
        (*info->fprintf_func) (info->stream, "%s", cacheFieldName[val]);
        break;
      }

    case 'a':		/* Address register indirect only. Cf. case '+'.  */
      {
        (*info->fprintf_func)
	  (info->stream,
	   "%s@",
	   reg_names[fetch_arg (buffer, place, 3, info) + 8]);
        break;
      }

    case '_':		/* 32-bit absolute address for move16.  */
      {
        uval = NEXTULONG (p);
	(*info->print_address_func) (uval, info);
        break;
      }

    case 'C':
      (*info->fprintf_func) (info->stream, "%%ccr");
      break;

    case 'S':
      (*info->fprintf_func) (info->stream, "%%sr");
      break;

    case 'U':
      (*info->fprintf_func) (info->stream, "%%usp");
      break;

    case 'E':
      (*info->fprintf_func) (info->stream, "%%acc");
      break;

    case 'G':
      (*info->fprintf_func) (info->stream, "%%macsr");
      break;

    case 'H':
      (*info->fprintf_func) (info->stream, "%%mask");
      break;

    case 'J':
      {
	/* FIXME: There's a problem here, different m68k processors call the
	   same address different names. This table can't get it right
	   because it doesn't know which processor it's disassembling for.  */
	static const struct { const char *name; int value; } names[]
	  = {{"%sfc", 0x000}, {"%dfc", 0x001}, {"%cacr", 0x002},
	     {"%tc",  0x003}, {"%itt0",0x004}, {"%itt1", 0x005},
             {"%dtt0",0x006}, {"%dtt1",0x007}, {"%buscr",0x008},
	     {"%usp", 0x800}, {"%vbr", 0x801}, {"%caar", 0x802},
	     {"%msp", 0x803}, {"%isp", 0x804},
	     {"%flashbar", 0xc04}, {"%rambar", 0xc05}, /* mcf528x added these.  */

	     /* Should we be calling this psr like we do in case 'Y'?  */
	     {"%mmusr",0x805},

             {"%urp", 0x806}, {"%srp", 0x807}, {"%pcr", 0x808}};

	val = fetch_arg (buffer, place, 12, info);
	for (regno = sizeof names / sizeof names[0] - 1; regno >= 0; regno--)
	  if (names[regno].value == val)
	    {
	      (*info->fprintf_func) (info->stream, "%s", names[regno].name);
	      break;
	    }
	if (regno < 0)
	  (*info->fprintf_func) (info->stream, "%d", val);
      }
      break;

    case 'Q':
      val = fetch_arg (buffer, place, 3, info);
      /* 0 means 8, except for the bkpt instruction... */
      if (val == 0 && d[1] != 's')
	val = 8;
      (*info->fprintf_func) (info->stream, "#%d", val);
      break;

    case 'x':
      val = fetch_arg (buffer, place, 3, info);
      /* 0 means -1.  */
      if (val == 0)
	val = -1;
      (*info->fprintf_func) (info->stream, "#%d", val);
      break;

    case 'M':
      if (place == 'h')
	{
	  static const char *const scalefactor_name[] = { "<<", ">>" };
	  val = fetch_arg (buffer, place, 1, info);
	  (*info->fprintf_func) (info->stream, "%s", scalefactor_name[val]);
	}
      else
	{
	  val = fetch_arg (buffer, place, 8, info);
	  if (val & 0x80)
	    val = val - 0x100;
	  (*info->fprintf_func) (info->stream, "#%d", val);
	}
      break;

    case 'T':
      val = fetch_arg (buffer, place, 4, info);
      (*info->fprintf_func) (info->stream, "#%d", val);
      break;

    case 'D':
      (*info->fprintf_func) (info->stream, "%s",
			     reg_names[fetch_arg (buffer, place, 3, info)]);
      break;

    case 'A':
      (*info->fprintf_func)
	(info->stream, "%s",
	 reg_names[fetch_arg (buffer, place, 3, info) + 010]);
      break;

    case 'R':
      (*info->fprintf_func)
	(info->stream, "%s",
	 reg_names[fetch_arg (buffer, place, 4, info)]);
      break;

    case 'r':
      regno = fetch_arg (buffer, place, 4, info);
      if (regno > 7)
	(*info->fprintf_func) (info->stream, "%s@", reg_names[regno]);
      else
	(*info->fprintf_func) (info->stream, "@(%s)", reg_names[regno]);
      break;

    case 'F':
      (*info->fprintf_func)
	(info->stream, "%%fp%d",
	 fetch_arg (buffer, place, 3, info));
      break;

    case 'O':
      val = fetch_arg (buffer, place, 6, info);
      if (val & 0x20)
	(*info->fprintf_func) (info->stream, "%s", reg_names[val & 7]);
      else
	(*info->fprintf_func) (info->stream, "%d", val);
      break;

    case '+':
      (*info->fprintf_func)
	(info->stream, "%s@+",
	 reg_names[fetch_arg (buffer, place, 3, info) + 8]);
      break;

    case '-':
      (*info->fprintf_func)
	(info->stream, "%s@-",
	 reg_names[fetch_arg (buffer, place, 3, info) + 8]);
      break;

    case 'k':
      if (place == 'k')
	(*info->fprintf_func)
	  (info->stream, "{%s}",
	   reg_names[fetch_arg (buffer, place, 3, info)]);
      else if (place == 'C')
	{
	  val = fetch_arg (buffer, place, 7, info);
	  if (val > 63)		/* This is a signed constant.  */
	    val -= 128;
	  (*info->fprintf_func) (info->stream, "{#%d}", val);
	}
      else
	return -2;
      break;

    case '#':
    case '^':
      p1 = buffer + (*d == '#' ? 2 : 4);
      if (place == 's')
	val = fetch_arg (buffer, place, 4, info);
      else if (place == 'C')
	val = fetch_arg (buffer, place, 7, info);
      else if (place == '8')
	val = fetch_arg (buffer, place, 3, info);
      else if (place == '3')
	val = fetch_arg (buffer, place, 8, info);
      else if (place == 'b')
	val = NEXTBYTE (p1);
      else if (place == 'w' || place == 'W')
	val = NEXTWORD (p1);
      else if (place == 'l')
	val = NEXTLONG (p1);
      else
	return -2;
      (*info->fprintf_func) (info->stream, "#%d", val);
      break;

    case 'B':
      if (place == 'b')
	disp = NEXTBYTE (p);
      else if (place == 'B')
	disp = COERCE_SIGNED_CHAR (buffer[1]);
      else if (place == 'w' || place == 'W')
	disp = NEXTWORD (p);
      else if (place == 'l' || place == 'L' || place == 'C')
	disp = NEXTLONG (p);
      else if (place == 'g')
	{
	  disp = NEXTBYTE (buffer);
	  if (disp == 0)
	    disp = NEXTWORD (p);
	  else if (disp == -1)
	    disp = NEXTLONG (p);
	}
      else if (place == 'c')
	{
	  if (buffer[1] & 0x40)		/* If bit six is one, long offset.  */
	    disp = NEXTLONG (p);
	  else
	    disp = NEXTWORD (p);
	}
      else
	return -2;

      (*info->print_address_func) (addr + disp, info);
      break;

    case 'd':
      val = NEXTWORD (p);
      (*info->fprintf_func)
	(info->stream, "%s@(%d)",
	 reg_names[fetch_arg (buffer, place, 3, info) + 8], val);
      break;

    case 's':
      (*info->fprintf_func) (info->stream, "%s",
			     fpcr_names[fetch_arg (buffer, place, 3, info)]);
      break;

    case 'e':
      val = fetch_arg(buffer, place, 2, info);
      (*info->fprintf_func) (info->stream, "%%acc%d", val);
      break;

    case 'g':
      val = fetch_arg(buffer, place, 1, info);
      (*info->fprintf_func) (info->stream, "%%accext%s", val==0 ? "01" : "23");
      break;

    case 'i':
      val = fetch_arg(buffer, place, 2, info);
      if (val == 1)
	(*info->fprintf_func) (info->stream, "<<");
      else if (val == 3)
	(*info->fprintf_func) (info->stream, ">>");
      else
	return -1;
      break;

    case 'I':
      /* Get coprocessor ID... */
      val = fetch_arg (buffer, 'd', 3, info);

      if (val != 1)				/* Unusual coprocessor ID?  */
	(*info->fprintf_func) (info->stream, "(cpid=%d) ", val);
      break;

    case '4':
    case '*':
    case '~':
    case '%':
    case ';':
    case '@':
    case '!':
    case '$':
    case '?':
    case '/':
    case '&':
    case '|':
    case '<':
    case '>':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'v':
    case 'b':
    case 'w':
    case 'y':
    case 'z':
      if (place == 'd')
	{
	  val = fetch_arg (buffer, 'x', 6, info);
	  val = ((val & 7) << 3) + ((val >> 3) & 7);
	}
      else
	val = fetch_arg (buffer, 's', 6, info);

      /* If the <ea> is invalid for *d, then reject this match.  */
      if (!m68k_valid_ea (*d, val))
	return -1;

      /* Get register number assuming address register.  */
      regno = (val & 7) + 8;
      regname = reg_names[regno];
      switch (val >> 3)
	{
	case 0:
	  (*info->fprintf_func) (info->stream, "%s", reg_names[val]);
	  break;

	case 1:
	  (*info->fprintf_func) (info->stream, "%s", regname);
	  break;

	case 2:
	  (*info->fprintf_func) (info->stream, "%s@", regname);
	  break;

	case 3:
	  (*info->fprintf_func) (info->stream, "%s@+", regname);
	  break;

	case 4:
	  (*info->fprintf_func) (info->stream, "%s@-", regname);
	  break;

	case 5:
	  val = NEXTWORD (p);
	  (*info->fprintf_func) (info->stream, "%s@(%d)", regname, val);
	  break;

	case 6:
	  p = print_indexed (regno, p, addr, info);
	  break;

	case 7:
	  switch (val & 7)
	    {
	    case 0:
	      val = NEXTWORD (p);
	      (*info->print_address_func) (val, info);
	      break;

	    case 1:
	      uval = NEXTULONG (p);
	      (*info->print_address_func) (uval, info);
	      break;

	    case 2:
	      val = NEXTWORD (p);
	      (*info->fprintf_func) (info->stream, "%%pc@(");
	      (*info->print_address_func) (addr + val, info);
	      (*info->fprintf_func) (info->stream, ")");
	      break;

	    case 3:
	      p = print_indexed (-1, p, addr, info);
	      break;

	    case 4:
	      flt_p = 1;	/* Assume it's a float... */
	      switch (place)
	      {
		case 'b':
		  val = NEXTBYTE (p);
		  flt_p = 0;
		  break;

		case 'w':
		  val = NEXTWORD (p);
		  flt_p = 0;
		  break;

		case 'l':
		  val = NEXTLONG (p);
		  flt_p = 0;
		  break;

		case 'f':
		  NEXTSINGLE (flval, p);
		  break;

		case 'F':
		  NEXTDOUBLE (flval, p);
		  break;

		case 'x':
		  NEXTEXTEND (flval, p);
		  break;

		case 'p':
		  flval = NEXTPACKED (p);
		  break;

		default:
		  return -1;
	      }
	      if (flt_p)	/* Print a float? */
		(*info->fprintf_func) (info->stream, "#%g", flval);
	      else
		(*info->fprintf_func) (info->stream, "#%d", val);
	      break;

	    default:
	      return -1;
	    }
	}

      /* If place is '/', then this is the case of the mask bit for
	 mac/emac loads. Now that the arg has been printed, grab the
	 mask bit and if set, add a '&' to the arg.  */
      if (place == '/')
	{
	  val = fetch_arg (buffer, place, 1, info);
	  if (val)
	    info->fprintf_func (info->stream, "&");
	}
      break;

    case 'L':
    case 'l':
	if (place == 'w')
	  {
	    char doneany;
	    p1 = buffer + 2;
	    val = NEXTWORD (p1);
	    /* Move the pointer ahead if this point is farther ahead
	       than the last.  */
	    p = p1 > p ? p1 : p;
	    if (val == 0)
	      {
		(*info->fprintf_func) (info->stream, "#0");
		break;
	      }
	    if (*d == 'l')
	      {
		int newval = 0;

		for (regno = 0; regno < 16; ++regno)
		  if (val & (0x8000 >> regno))
		    newval |= 1 << regno;
		val = newval;
	      }
	    val &= 0xffff;
	    doneany = 0;
	    for (regno = 0; regno < 16; ++regno)
	      if (val & (1 << regno))
		{
		  int first_regno;

		  if (doneany)
		    (*info->fprintf_func) (info->stream, "/");
		  doneany = 1;
		  (*info->fprintf_func) (info->stream, "%s", reg_names[regno]);
		  first_regno = regno;
		  while (val & (1 << (regno + 1)))
		    ++regno;
		  if (regno > first_regno)
		    (*info->fprintf_func) (info->stream, "-%s",
					   reg_names[regno]);
		}
	  }
	else if (place == '3')
	  {
	    /* `fmovem' insn.  */
	    char doneany;
	    val = fetch_arg (buffer, place, 8, info);
	    if (val == 0)
	      {
		(*info->fprintf_func) (info->stream, "#0");
		break;
	      }
	    if (*d == 'l')
	      {
		int newval = 0;

		for (regno = 0; regno < 8; ++regno)
		  if (val & (0x80 >> regno))
		    newval |= 1 << regno;
		val = newval;
	      }
	    val &= 0xff;
	    doneany = 0;
	    for (regno = 0; regno < 8; ++regno)
	      if (val & (1 << regno))
		{
		  int first_regno;
		  if (doneany)
		    (*info->fprintf_func) (info->stream, "/");
		  doneany = 1;
		  (*info->fprintf_func) (info->stream, "%%fp%d", regno);
		  first_regno = regno;
		  while (val & (1 << (regno + 1)))
		    ++regno;
		  if (regno > first_regno)
		    (*info->fprintf_func) (info->stream, "-%%fp%d", regno);
		}
	  }
	else if (place == '8')
	  {
	    /* fmoveml for FP status registers.  */
	    (*info->fprintf_func) (info->stream, "%s",
				   fpcr_names[fetch_arg (buffer, place, 3,
							 info)]);
	  }
	else
	  return -2;
      break;

    case 'X':
      place = '8';
    case 'Y':
    case 'Z':
    case 'W':
    case '0':
    case '1':
    case '2':
    case '3':
      {
	int val = fetch_arg (buffer, place, 5, info);
        const char *name = 0;

	switch (val)
	  {
	  case 2: name = "%tt0"; break;
	  case 3: name = "%tt1"; break;
	  case 0x10: name = "%tc"; break;
	  case 0x11: name = "%drp"; break;
	  case 0x12: name = "%srp"; break;
	  case 0x13: name = "%crp"; break;
	  case 0x14: name = "%cal"; break;
	  case 0x15: name = "%val"; break;
	  case 0x16: name = "%scc"; break;
	  case 0x17: name = "%ac"; break;
 	  case 0x18: name = "%psr"; break;
	  case 0x19: name = "%pcsr"; break;
	  case 0x1c:
	  case 0x1d:
	    {
	      int break_reg = ((buffer[3] >> 2) & 7);

	      (*info->fprintf_func)
		(info->stream, val == 0x1c ? "%%bad%d" : "%%bac%d",
		 break_reg);
	    }
	    break;
	  default:
	    (*info->fprintf_func) (info->stream, "<mmu register %d>", val);
	  }
	if (name)
	  (*info->fprintf_func) (info->stream, "%s", name);
      }
      break;

    case 'f':
      {
	int fc = fetch_arg (buffer, place, 5, info);

	if (fc == 1)
	  (*info->fprintf_func) (info->stream, "%%dfc");
	else if (fc == 0)
	  (*info->fprintf_func) (info->stream, "%%sfc");
	else
	  /* xgettext:c-format */
	  (*info->fprintf_func) (info->stream, "<function code %d>", fc);
      }
      break;

    case 'V':
      (*info->fprintf_func) (info->stream, "%%val");
      break;

    case 't':
      {
	int level = fetch_arg (buffer, place, 3, info);

	(*info->fprintf_func) (info->stream, "%d", level);
      }
      break;

    case 'u':
      {
	short is_upper = 0;
	int reg = fetch_arg (buffer, place, 5, info);

	if (reg & 0x10)
	  {
	    is_upper = 1;
	    reg &= 0xf;
	  }
	(*info->fprintf_func) (info->stream, "%s%s",
			       reg_half_names[reg],
			       is_upper ? "u" : "l");
      }
      break;

    default:
      return -2;
    }

  return p - p0;
}

/* Try to match the current instruction to best and if so, return the
   number of bytes consumed from the instruction stream, else zero.  */

static int
match_insn_m68k (bfd_vma memaddr,
		 disassemble_info * info,
		 const struct m68k_opcode * best,
		 struct private * priv)
{
  unsigned char *save_p;
  unsigned char *p;
  const char *d;

  bfd_byte *buffer = priv->the_buffer;
  fprintf_function save_printer = info->fprintf_func;
  void (* save_print_address) (bfd_vma, struct disassemble_info *)
    = info->print_address_func;

  /* Point at first word of argument data,
     and at descriptor for first argument.  */
  p = buffer + 2;

  /* Figure out how long the fixed-size portion of the instruction is.
     The only place this is stored in the opcode table is
     in the arguments--look for arguments which specify fields in the 2nd
     or 3rd words of the instruction.  */
  for (d = best->args; *d; d += 2)
    {
      /* I don't think it is necessary to be checking d[0] here;
	 I suspect all this could be moved to the case statement below.  */
      if (d[0] == '#')
	{
	  if (d[1] == 'l' && p - buffer < 6)
	    p = buffer + 6;
	  else if (p - buffer < 4 && d[1] != 'C' && d[1] != '8')
	    p = buffer + 4;
	}

      if ((d[0] == 'L' || d[0] == 'l') && d[1] == 'w' && p - buffer < 4)
	p = buffer + 4;

      switch (d[1])
	{
	case '1':
	case '2':
	case '3':
	case '7':
	case '8':
	case '9':
	case 'i':
	  if (p - buffer < 4)
	    p = buffer + 4;
	  break;
	case '4':
	case '5':
	case '6':
	  if (p - buffer < 6)
	    p = buffer + 6;
	  break;
	default:
	  break;
	}
    }

  /* pflusha is an exceptions.  It takes no arguments but is two words
     long.  Recognize it by looking at the lower 16 bits of the mask.  */
  if (p - buffer < 4 && (best->match & 0xFFFF) != 0)
    p = buffer + 4;

  /* lpstop is another exception.  It takes a one word argument but is
     three words long.  */
  if (p - buffer < 6
      && (best->match & 0xffff) == 0xffff
      && best->args[0] == '#'
      && best->args[1] == 'w')
    {
      /* Copy the one word argument into the usual location for a one
	 word argument, to simplify printing it.  We can get away with
	 this because we know exactly what the second word is, and we
	 aren't going to print anything based on it.  */
      p = buffer + 6;
      fetch_data(info, p);
      buffer[2] = buffer[4];
      buffer[3] = buffer[5];
    }

  fetch_data(info, p);

  d = best->args;

  save_p = p;
  info->print_address_func = dummy_print_address;
  info->fprintf_func = dummy_printer;

  /* We scan the operands twice.  The first time we don't print anything,
     but look for errors.  */
  for (; *d; d += 2)
    {
      int eaten = print_insn_arg (d, buffer, p, memaddr + (p - buffer), info);

      if (eaten >= 0)
	p += eaten;
      else if (eaten == -1)
	{
	  info->fprintf_func = save_printer;
	  info->print_address_func = save_print_address;
	  return 0;
	}
      else
	{
	  info->fprintf_func (info->stream,
			      /* xgettext:c-format */
			      "<internal error in opcode table: %s %s>\n",
			      best->name,  best->args);
	  info->fprintf_func = save_printer;
	  info->print_address_func = save_print_address;
	  return 2;
	}
    }

  p = save_p;
  info->fprintf_func = save_printer;
  info->print_address_func = save_print_address;

  d = best->args;

  info->fprintf_func (info->stream, "%s", best->name);

  if (*d)
    info->fprintf_func (info->stream, " ");

  while (*d)
    {
      p += print_insn_arg (d, buffer, p, memaddr + (p - buffer), info);
      d += 2;

      if (*d && *(d - 2) != 'I' && *d != 'k')
	info->fprintf_func (info->stream, ",");
    }

  return p - buffer;
}

/* Print the m68k instruction at address MEMADDR in debugged memory,
   on INFO->STREAM.  Returns length of the instruction, in bytes.  */

int
print_insn_m68k (bfd_vma memaddr, disassemble_info *info)
{
  int i;
  const char *d;
  unsigned int arch_mask;
  struct private priv;
  bfd_byte *buffer = priv.the_buffer;
  int major_opcode;
  static int numopcodes[16];
  static const struct m68k_opcode **opcodes[16];
  int val;

  if (!opcodes[0])
    {
      /* Speed up the matching by sorting the opcode
	 table on the upper four bits of the opcode.  */
      const struct m68k_opcode **opc_pointer[16];

      /* First count how many opcodes are in each of the sixteen buckets.  */
      for (i = 0; i < m68k_numopcodes; i++)
	numopcodes[(m68k_opcodes[i].opcode >> 28) & 15]++;

      /* Then create a sorted table of pointers
	 that point into the unsorted table.  */
      opc_pointer[0] = malloc (sizeof (struct m68k_opcode *)
                               * m68k_numopcodes);
      opcodes[0] = opc_pointer[0];

      for (i = 1; i < 16; i++)
	{
	  opc_pointer[i] = opc_pointer[i - 1] + numopcodes[i - 1];
	  opcodes[i] = opc_pointer[i];
	}

      for (i = 0; i < m68k_numopcodes; i++)
	*opc_pointer[(m68k_opcodes[i].opcode >> 28) & 15]++ = &m68k_opcodes[i];
    }

  info->private_data = (PTR) &priv;
  /* Tell objdump to use two bytes per chunk
     and six bytes per line for displaying raw data.  */
  info->bytes_per_chunk = 2;
  info->bytes_per_line = 6;
  info->display_endian = BFD_ENDIAN_BIG;
  priv.max_fetched = priv.the_buffer;
  priv.insn_start = memaddr;

  if (sigsetjmp(priv.bailout, 0) != 0) {
      /* Error return.  */
      return -1;
  }

  switch (info->mach)
    {
    default:
    case 0:
      arch_mask = (unsigned int) -1;
      break;
    case bfd_mach_m68000:
      arch_mask = m68000|m68881|m68851;
      break;
    case bfd_mach_m68008:
      arch_mask = m68008|m68881|m68851;
      break;
    case bfd_mach_m68010:
      arch_mask = m68010|m68881|m68851;
      break;
    case bfd_mach_m68020:
      arch_mask = m68020|m68881|m68851;
      break;
    case bfd_mach_m68030:
      arch_mask = m68030|m68881|m68851;
      break;
    case bfd_mach_m68040:
      arch_mask = m68040|m68881|m68851;
      break;
    case bfd_mach_m68060:
      arch_mask = m68060|m68881|m68851;
      break;
    case bfd_mach_mcf5200:
      arch_mask = mcfisa_a;
      break;
    case bfd_mach_mcf521x:
    case bfd_mach_mcf528x:
      arch_mask = mcfisa_a|mcfhwdiv|mcfisa_aa|mcfusp|mcfemac;
      break;
    case bfd_mach_mcf5206e:
      arch_mask = mcfisa_a|mcfhwdiv|mcfmac;
      break;
    case bfd_mach_mcf5249:
      arch_mask = mcfisa_a|mcfhwdiv|mcfemac;
      break;
    case bfd_mach_mcf5307:
      arch_mask = mcfisa_a|mcfhwdiv|mcfmac;
      break;
    case bfd_mach_mcf5407:
      arch_mask = mcfisa_a|mcfhwdiv|mcfisa_b|mcfmac;
      break;
    case bfd_mach_mcf547x:
    case bfd_mach_mcf548x:
    case bfd_mach_mcfv4e:
      arch_mask = mcfisa_a|mcfhwdiv|mcfisa_b|mcfusp|cfloat|mcfemac;
      break;
    }

  fetch_data(info, buffer + 2);
  major_opcode = (buffer[0] >> 4) & 15;

  for (i = 0; i < numopcodes[major_opcode]; i++)
    {
      const struct m68k_opcode *opc = opcodes[major_opcode][i];
      unsigned long opcode = opc->opcode;
      unsigned long match = opc->match;

      if (((0xff & buffer[0] & (match >> 24)) == (0xff & (opcode >> 24)))
	  && ((0xff & buffer[1] & (match >> 16)) == (0xff & (opcode >> 16)))
	  /* Only fetch the next two bytes if we need to.  */
	  && (((0xffff & match) == 0)
	      ||
              (fetch_data(info, buffer + 4)
	       && ((0xff & buffer[2] & (match >> 8)) == (0xff & (opcode >> 8)))
	       && ((0xff & buffer[3] & match) == (0xff & opcode)))
	      )
	  && (opc->arch & arch_mask) != 0)
	{
	  /* Don't use for printout the variants of divul and divsl
	     that have the same register number in two places.
	     The more general variants will match instead.  */
	  for (d = opc->args; *d; d += 2)
	    if (d[1] == 'D')
	      break;

	  /* Don't use for printout the variants of most floating
	     point coprocessor instructions which use the same
	     register number in two places, as above.  */
	  if (*d == '\0')
	    for (d = opc->args; *d; d += 2)
	      if (d[1] == 't')
		break;

	  /* Don't match fmovel with more than one register;
	     wait for fmoveml.  */
	  if (*d == '\0')
	    {
	      for (d = opc->args; *d; d += 2)
		{
		  if (d[0] == 's' && d[1] == '8')
		    {
		      val = fetch_arg (buffer, d[1], 3, info);
		      if ((val & (val - 1)) != 0)
			break;
		    }
		}
	    }

          /* Don't match FPU insns with non-default coprocessor ID.  */
          if (*d == '\0')
            {
              for (d = opc->args; *d; d += 2)
                {
                  if (d[0] == 'I')
                    {
                      val = fetch_arg (buffer, 'd', 3, info);
                      if (val != 1)
                        break;
                    }
                }
            }

	  if (*d == '\0')
	    if ((val = match_insn_m68k (memaddr, info, opc, & priv)))
	      return val;
	}
    }

  /* Handle undefined instructions.  */
  info->fprintf_func (info->stream, "0%o", (buffer[0] << 8) + buffer[1]);
  return 2;
}
/* **** End of m68k-dis.c */
/* **** m68k-opc.h from sourceware.org CVS 2005-08-14.  */
/* Opcode table for m680[012346]0/m6888[12]/m68851/mcf5200.
   Copyright 1989, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999,
   2000, 2001, 2003, 2004, 2005
   Free Software Foundation, Inc.

   This file is part of GDB, GAS, and the GNU binutils.

   GDB, GAS, and the GNU binutils are free software; you can redistribute
   them and/or modify them under the terms of the GNU General Public
   License as published by the Free Software Foundation; either version
   1, or (at your option) any later version.

   GDB, GAS, and the GNU binutils are distributed in the hope that they
   will be useful, but WITHOUT ANY WARRANTY; without even the implied
   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
   the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this file; see the file COPYING.  If not,
   see <http://www.gnu.org/licenses/>.  */

#define one(x) ((unsigned int) (x) << 16)
#define two(x, y) (((unsigned int) (x) << 16) + (y))

/* The assembler requires that all instances of the same mnemonic must
   be consecutive.  If they aren't, the assembler will bomb at
   runtime.  */

const struct m68k_opcode m68k_opcodes[] =
{
{"abcd", 2,	one(0140400),	one(0170770), "DsDd", m68000up },
{"abcd", 2,	one(0140410),	one(0170770), "-s-d", m68000up },

{"addaw", 2,	one(0150300),	one(0170700), "*wAd", m68000up },
{"addal", 2,	one(0150700),	one(0170700), "*lAd", m68000up | mcfisa_a },

{"addib", 4,	one(0003000),	one(0177700), "#b$s", m68000up },
{"addiw", 4,	one(0003100),	one(0177700), "#w$s", m68000up },
{"addil", 6,	one(0003200),	one(0177700), "#l$s", m68000up },
{"addil", 6,	one(0003200),	one(0177700), "#lDs", mcfisa_a },

{"addqb", 2,	one(0050000),	one(0170700), "Qd$b", m68000up },
{"addqw", 2,	one(0050100),	one(0170700), "Qd%w", m68000up },
{"addql", 2,	one(0050200),	one(0170700), "Qd%l", m68000up | mcfisa_a },

/* The add opcode can generate the adda, addi, and addq instructions.  */
{"addb", 2,	one(0050000),	one(0170700), "Qd$b", m68000up },
{"addb", 4,	one(0003000),	one(0177700), "#b$s", m68000up },
{"addb", 2,	one(0150000),	one(0170700), ";bDd", m68000up },
{"addb", 2,	one(0150400),	one(0170700), "Dd~b", m68000up },
{"addw", 2,	one(0050100),	one(0170700), "Qd%w", m68000up },
{"addw", 2,	one(0150300),	one(0170700), "*wAd", m68000up },
{"addw", 4,	one(0003100),	one(0177700), "#w$s", m68000up },
{"addw", 2,	one(0150100),	one(0170700), "*wDd", m68000up },
{"addw", 2,	one(0150500),	one(0170700), "Dd~w", m68000up },
{"addl", 2,	one(0050200),	one(0170700), "Qd%l", m68000up | mcfisa_a },
{"addl", 6,	one(0003200),	one(0177700), "#l$s", m68000up },
{"addl", 6,	one(0003200),	one(0177700), "#lDs", mcfisa_a },
{"addl", 2,	one(0150700),	one(0170700), "*lAd", m68000up | mcfisa_a },
{"addl", 2,	one(0150200),	one(0170700), "*lDd", m68000up | mcfisa_a },
{"addl", 2,	one(0150600),	one(0170700), "Dd~l", m68000up | mcfisa_a },

{"addxb", 2,	one(0150400),	one(0170770), "DsDd", m68000up },
{"addxb", 2,	one(0150410),	one(0170770), "-s-d", m68000up },
{"addxw", 2,	one(0150500),	one(0170770), "DsDd", m68000up },
{"addxw", 2,	one(0150510),	one(0170770), "-s-d", m68000up },
{"addxl", 2,	one(0150600),	one(0170770), "DsDd", m68000up | mcfisa_a },
{"addxl", 2,	one(0150610),	one(0170770), "-s-d", m68000up },

{"andib", 4,	one(0001000),	one(0177700), "#b$s", m68000up },
{"andib", 4,	one(0001074),	one(0177777), "#bCs", m68000up },
{"andiw", 4,	one(0001100),	one(0177700), "#w$s", m68000up },
{"andiw", 4,	one(0001174),	one(0177777), "#wSs", m68000up },
{"andil", 6,	one(0001200),	one(0177700), "#l$s", m68000up },
{"andil", 6,	one(0001200),	one(0177700), "#lDs", mcfisa_a },
{"andi", 4,	one(0001100),	one(0177700), "#w$s", m68000up },
{"andi", 4,	one(0001074),	one(0177777), "#bCs", m68000up },
{"andi", 4,	one(0001174),	one(0177777), "#wSs", m68000up },

/* The and opcode can generate the andi instruction.  */
{"andb", 4,	one(0001000),	one(0177700), "#b$s", m68000up },
{"andb", 4,	one(0001074),	one(0177777), "#bCs", m68000up },
{"andb", 2,	one(0140000),	one(0170700), ";bDd", m68000up },
{"andb", 2,	one(0140400),	one(0170700), "Dd~b", m68000up },
{"andw", 4,	one(0001100),	one(0177700), "#w$s", m68000up },
{"andw", 4,	one(0001174),	one(0177777), "#wSs", m68000up },
{"andw", 2,	one(0140100),	one(0170700), ";wDd", m68000up },
{"andw", 2,	one(0140500),	one(0170700), "Dd~w", m68000up },
{"andl", 6,	one(0001200),	one(0177700), "#l$s", m68000up },
{"andl", 6,	one(0001200),	one(0177700), "#lDs", mcfisa_a },
{"andl", 2,	one(0140200),	one(0170700), ";lDd", m68000up | mcfisa_a },
{"andl", 2,	one(0140600),	one(0170700), "Dd~l", m68000up | mcfisa_a },
{"and", 4,	one(0001100),	one(0177700), "#w$w", m68000up },
{"and", 4,	one(0001074),	one(0177777), "#bCs", m68000up },
{"and", 4,	one(0001174),	one(0177777), "#wSs", m68000up },
{"and", 2,	one(0140100),	one(0170700), ";wDd", m68000up },
{"and", 2,	one(0140500),	one(0170700), "Dd~w", m68000up },

{"aslb", 2,	one(0160400),	one(0170770), "QdDs", m68000up },
{"aslb", 2,	one(0160440),	one(0170770), "DdDs", m68000up },
{"aslw", 2,	one(0160500),	one(0170770), "QdDs", m68000up },
{"aslw", 2,	one(0160540),	one(0170770), "DdDs", m68000up },
{"aslw", 2,	one(0160700),	one(0177700), "~s",   m68000up },
{"asll", 2,	one(0160600),	one(0170770), "QdDs", m68000up | mcfisa_a },
{"asll", 2,	one(0160640),	one(0170770), "DdDs", m68000up | mcfisa_a },

{"asrb", 2,	one(0160000),	one(0170770), "QdDs", m68000up },
{"asrb", 2,	one(0160040),	one(0170770), "DdDs", m68000up },
{"asrw", 2,	one(0160100),	one(0170770), "QdDs", m68000up },
{"asrw", 2,	one(0160140),	one(0170770), "DdDs", m68000up },
{"asrw", 2,	one(0160300),	one(0177700), "~s",   m68000up },
{"asrl", 2,	one(0160200),	one(0170770), "QdDs", m68000up | mcfisa_a },
{"asrl", 2,	one(0160240),	one(0170770), "DdDs", m68000up | mcfisa_a },

{"bhiw", 2,	one(0061000),	one(0177777), "BW", m68000up | mcfisa_a },
{"blsw", 2,	one(0061400),	one(0177777), "BW", m68000up | mcfisa_a },
{"bccw", 2,	one(0062000),	one(0177777), "BW", m68000up | mcfisa_a },
{"bcsw", 2,	one(0062400),	one(0177777), "BW", m68000up | mcfisa_a },
{"bnew", 2,	one(0063000),	one(0177777), "BW", m68000up | mcfisa_a },
{"beqw", 2,	one(0063400),	one(0177777), "BW", m68000up | mcfisa_a },
{"bvcw", 2,	one(0064000),	one(0177777), "BW", m68000up | mcfisa_a },
{"bvsw", 2,	one(0064400),	one(0177777), "BW", m68000up | mcfisa_a },
{"bplw", 2,	one(0065000),	one(0177777), "BW", m68000up | mcfisa_a },
{"bmiw", 2,	one(0065400),	one(0177777), "BW", m68000up | mcfisa_a },
{"bgew", 2,	one(0066000),	one(0177777), "BW", m68000up | mcfisa_a },
{"bltw", 2,	one(0066400),	one(0177777), "BW", m68000up | mcfisa_a },
{"bgtw", 2,	one(0067000),	one(0177777), "BW", m68000up | mcfisa_a },
{"blew", 2,	one(0067400),	one(0177777), "BW", m68000up | mcfisa_a },

{"bhil", 2,	one(0061377),	one(0177777), "BL", m68020up | cpu32 | mcfisa_b},
{"blsl", 2,	one(0061777),	one(0177777), "BL", m68020up | cpu32 | mcfisa_b},
{"bccl", 2,	one(0062377),	one(0177777), "BL", m68020up | cpu32 | mcfisa_b},
{"bcsl", 2,	one(0062777),	one(0177777), "BL", m68020up | cpu32 | mcfisa_b},
{"bnel", 2,	one(0063377),	one(0177777), "BL", m68020up | cpu32 | mcfisa_b},
{"beql", 2,	one(0063777),	one(0177777), "BL", m68020up | cpu32 | mcfisa_b},
{"bvcl", 2,	one(0064377),	one(0177777), "BL", m68020up | cpu32 | mcfisa_b},
{"bvsl", 2,	one(0064777),	one(0177777), "BL", m68020up | cpu32 | mcfisa_b},
{"bpll", 2,	one(0065377),	one(0177777), "BL", m68020up | cpu32 | mcfisa_b},
{"bmil", 2,	one(0065777),	one(0177777), "BL", m68020up | cpu32 | mcfisa_b},
{"bgel", 2,	one(0066377),	one(0177777), "BL", m68020up | cpu32 | mcfisa_b},
{"bltl", 2,	one(0066777),	one(0177777), "BL", m68020up | cpu32 | mcfisa_b},
{"bgtl", 2,	one(0067377),	one(0177777), "BL", m68020up | cpu32 | mcfisa_b},
{"blel", 2,	one(0067777),	one(0177777), "BL", m68020up | cpu32 | mcfisa_b},

{"bhis", 2,	one(0061000),	one(0177400), "BB", m68000up | mcfisa_a },
{"blss", 2,	one(0061400),	one(0177400), "BB", m68000up | mcfisa_a },
{"bccs", 2,	one(0062000),	one(0177400), "BB", m68000up | mcfisa_a },
{"bcss", 2,	one(0062400),	one(0177400), "BB", m68000up | mcfisa_a },
{"bnes", 2,	one(0063000),	one(0177400), "BB", m68000up | mcfisa_a },
{"beqs", 2,	one(0063400),	one(0177400), "BB", m68000up | mcfisa_a },
{"bvcs", 2,	one(0064000),	one(0177400), "BB", m68000up | mcfisa_a },
{"bvss", 2,	one(0064400),	one(0177400), "BB", m68000up | mcfisa_a },
{"bpls", 2,	one(0065000),	one(0177400), "BB", m68000up | mcfisa_a },
{"bmis", 2,	one(0065400),	one(0177400), "BB", m68000up | mcfisa_a },
{"bges", 2,	one(0066000),	one(0177400), "BB", m68000up | mcfisa_a },
{"blts", 2,	one(0066400),	one(0177400), "BB", m68000up | mcfisa_a },
{"bgts", 2,	one(0067000),	one(0177400), "BB", m68000up | mcfisa_a },
{"bles", 2,	one(0067400),	one(0177400), "BB", m68000up | mcfisa_a },

{"jhi", 2,	one(0061000),	one(0177400), "Bg", m68000up | mcfisa_a },
{"jls", 2,	one(0061400),	one(0177400), "Bg", m68000up | mcfisa_a },
{"jcc", 2,	one(0062000),	one(0177400), "Bg", m68000up | mcfisa_a },
{"jcs", 2,	one(0062400),	one(0177400), "Bg", m68000up | mcfisa_a },
{"jne", 2,	one(0063000),	one(0177400), "Bg", m68000up | mcfisa_a },
{"jeq", 2,	one(0063400),	one(0177400), "Bg", m68000up | mcfisa_a },
{"jvc", 2,	one(0064000),	one(0177400), "Bg", m68000up | mcfisa_a },
{"jvs", 2,	one(0064400),	one(0177400), "Bg", m68000up | mcfisa_a },
{"jpl", 2,	one(0065000),	one(0177400), "Bg", m68000up | mcfisa_a },
{"jmi", 2,	one(0065400),	one(0177400), "Bg", m68000up | mcfisa_a },
{"jge", 2,	one(0066000),	one(0177400), "Bg", m68000up | mcfisa_a },
{"jlt", 2,	one(0066400),	one(0177400), "Bg", m68000up | mcfisa_a },
{"jgt", 2,	one(0067000),	one(0177400), "Bg", m68000up | mcfisa_a },
{"jle", 2,	one(0067400),	one(0177400), "Bg", m68000up | mcfisa_a },

{"bchg", 2,	one(0000500),	one(0170700), "Dd$s", m68000up | mcfisa_a },
{"bchg", 4,	one(0004100),	one(0177700), "#b$s", m68000up },
{"bchg", 4,	one(0004100),	one(0177700), "#bqs", mcfisa_a },

{"bclr", 2,	one(0000600),	one(0170700), "Dd$s", m68000up | mcfisa_a },
{"bclr", 4,	one(0004200),	one(0177700), "#b$s", m68000up },
{"bclr", 4,	one(0004200),	one(0177700), "#bqs", mcfisa_a },

{"bfchg", 4,	two(0165300, 0), two(0177700, 0170000),	"?sO2O3",   m68020up },
{"bfclr", 4,	two(0166300, 0), two(0177700, 0170000),	"?sO2O3",   m68020up },
{"bfexts", 4,	two(0165700, 0), two(0177700, 0100000),	"/sO2O3D1", m68020up },
{"bfextu", 4,	two(0164700, 0), two(0177700, 0100000),	"/sO2O3D1", m68020up },
{"bfffo", 4,	two(0166700, 0), two(0177700, 0100000),	"/sO2O3D1", m68020up },
{"bfins", 4,	two(0167700, 0), two(0177700, 0100000),	"D1?sO2O3", m68020up },
{"bfset", 4,	two(0167300, 0), two(0177700, 0170000),	"?sO2O3",   m68020up },
{"bftst", 4,	two(0164300, 0), two(0177700, 0170000),	"/sO2O3",   m68020up },

{"bgnd", 2,	one(0045372),	one(0177777), "", cpu32 },

{"bitrev", 2,	one(0000300),	one(0177770), "Ds", mcfisa_aa},

{"bkpt", 2,	one(0044110),	one(0177770), "ts", m68010up },

{"braw", 2,	one(0060000),	one(0177777), "BW", m68000up | mcfisa_a },
{"bral", 2,	one(0060377),	one(0177777), "BL", m68020up | cpu32 | mcfisa_b},
{"bras", 2,	one(0060000),	one(0177400), "BB", m68000up | mcfisa_a },

{"bset", 2,	one(0000700),	one(0170700), "Dd$s", m68000up | mcfisa_a },
{"bset", 2,	one(0000700),	one(0170700), "Ddvs", mcfisa_a },
{"bset", 4,	one(0004300),	one(0177700), "#b$s", m68000up },
{"bset", 4,	one(0004300),	one(0177700), "#bqs", mcfisa_a },

{"bsrw", 2,	one(0060400),	one(0177777), "BW", m68000up | mcfisa_a },
{"bsrl", 2,	one(0060777),	one(0177777), "BL", m68020up | cpu32 | mcfisa_b},
{"bsrs", 2,	one(0060400),	one(0177400), "BB", m68000up | mcfisa_a },

{"btst", 2,	one(0000400),	one(0170700), "Dd;b", m68000up | mcfisa_a },
{"btst", 4,	one(0004000),	one(0177700), "#b@s", m68000up },
{"btst", 4,	one(0004000),	one(0177700), "#bqs", mcfisa_a },

{"byterev", 2,	one(0001300),	one(0177770), "Ds", mcfisa_aa},

{"callm", 4,	one(0003300),	one(0177700), "#b!s", m68020 },

{"cas2w", 6,    two(0006374,0), two(0177777,0007070), "D3D6D2D5r1r4", m68020up },
{"cas2w", 6,    two(0006374,0), two(0177777,0007070), "D3D6D2D5R1R4", m68020up },
{"cas2l", 6,    two(0007374,0), two(0177777,0007070), "D3D6D2D5r1r4", m68020up },
{"cas2l", 6,    two(0007374,0), two(0177777,0007070), "D3D6D2D5R1R4", m68020up },

{"casb", 4,	two(0005300, 0), two(0177700, 0177070),	"D3D2~s", m68020up },
{"casw", 4,	two(0006300, 0), two(0177700, 0177070),	"D3D2~s", m68020up },
{"casl", 4,	two(0007300, 0), two(0177700, 0177070),	"D3D2~s", m68020up },

{"chk2b", 4, 	two(0000300,0004000), two(0177700,07777), "!sR1", m68020up | cpu32 },
{"chk2w", 4, 	two(0001300,0004000),	two(0177700,07777), "!sR1", m68020up | cpu32 },
{"chk2l", 4, 	two(0002300,0004000),	two(0177700,07777), "!sR1", m68020up | cpu32 },

{"chkl", 2,	one(0040400),		one(0170700), ";lDd", m68000up },
{"chkw", 2,	one(0040600),		one(0170700), ";wDd", m68000up },

#define SCOPE_LINE (0x1 << 3)
#define SCOPE_PAGE (0x2 << 3)
#define SCOPE_ALL  (0x3 << 3)

{"cinva", 2,	one(0xf400|SCOPE_ALL),  one(0xff38), "ce",   m68040up },
{"cinvl", 2,	one(0xf400|SCOPE_LINE), one(0xff38), "ceas", m68040up },
{"cinvp", 2,	one(0xf400|SCOPE_PAGE), one(0xff38), "ceas", m68040up },

{"cpusha", 2,	one(0xf420|SCOPE_ALL),  one(0xff38), "ce",   m68040up },
{"cpushl", 2,	one(0xf420|SCOPE_LINE), one(0xff38), "ceas", m68040up | mcfisa_a },
{"cpushp", 2,	one(0xf420|SCOPE_PAGE), one(0xff38), "ceas", m68040up },

#undef SCOPE_LINE
#undef SCOPE_PAGE
#undef SCOPE_ALL

{"clrb", 2,	one(0041000),	one(0177700), "$s", m68000up | mcfisa_a },
{"clrw", 2,	one(0041100),	one(0177700), "$s", m68000up | mcfisa_a },
{"clrl", 2,	one(0041200),	one(0177700), "$s", m68000up | mcfisa_a },

{"cmp2b", 4,	two(0000300,0), two(0177700,07777), "!sR1", m68020up | cpu32 },
{"cmp2w", 4,	two(0001300,0),	two(0177700,07777), "!sR1", m68020up | cpu32 },
{"cmp2l", 4,	two(0002300,0),	two(0177700,07777), "!sR1", m68020up | cpu32 },

{"cmpaw", 2,	one(0130300),	one(0170700), "*wAd", m68000up },
{"cmpal", 2,	one(0130700),	one(0170700), "*lAd", m68000up | mcfisa_a },

{"cmpib", 4,	one(0006000),	one(0177700), "#b@s", m68000up },
{"cmpib", 4,	one(0006000),	one(0177700), "#bDs", mcfisa_b },
{"cmpiw", 4,	one(0006100),	one(0177700), "#w@s", m68000up },
{"cmpiw", 4,	one(0006100),	one(0177700), "#wDs", mcfisa_b },
{"cmpil", 6,	one(0006200),	one(0177700), "#l@s", m68000up },
{"cmpil", 6,	one(0006200),	one(0177700), "#lDs", mcfisa_a },

{"cmpmb", 2,	one(0130410),	one(0170770), "+s+d", m68000up },
{"cmpmw", 2,	one(0130510),	one(0170770), "+s+d", m68000up },
{"cmpml", 2,	one(0130610),	one(0170770), "+s+d", m68000up },

/* The cmp opcode can generate the cmpa, cmpm, and cmpi instructions.  */
{"cmpb", 4,	one(0006000),	one(0177700), "#b@s", m68000up },
{"cmpb", 4,	one(0006000),	one(0177700), "#bDs", mcfisa_b },
{"cmpb", 2,	one(0130410),	one(0170770), "+s+d", m68000up },
{"cmpb", 2,	one(0130000),	one(0170700), ";bDd", m68000up },
{"cmpb", 2,	one(0130000),	one(0170700), "*bDd", mcfisa_b },
{"cmpw", 2,	one(0130300),	one(0170700), "*wAd", m68000up },
{"cmpw", 4,	one(0006100),	one(0177700), "#w@s", m68000up },
{"cmpw", 4,	one(0006100),	one(0177700), "#wDs", mcfisa_b },
{"cmpw", 2,	one(0130510),	one(0170770), "+s+d", m68000up },
{"cmpw", 2,	one(0130100),	one(0170700), "*wDd", m68000up | mcfisa_b },
{"cmpl", 2,	one(0130700),	one(0170700), "*lAd", m68000up | mcfisa_a },
{"cmpl", 6,	one(0006200),	one(0177700), "#l@s", m68000up },
{"cmpl", 6,	one(0006200),	one(0177700), "#lDs", mcfisa_a },
{"cmpl", 2,	one(0130610),	one(0170770), "+s+d", m68000up },
{"cmpl", 2,	one(0130200),	one(0170700), "*lDd", m68000up | mcfisa_a },

{"dbcc", 2,	one(0052310),	one(0177770), "DsBw", m68000up },
{"dbcs", 2,	one(0052710),	one(0177770), "DsBw", m68000up },
{"dbeq", 2,	one(0053710),	one(0177770), "DsBw", m68000up },
{"dbf", 2,	one(0050710),	one(0177770), "DsBw", m68000up },
{"dbge", 2,	one(0056310),	one(0177770), "DsBw", m68000up },
{"dbgt", 2,	one(0057310),	one(0177770), "DsBw", m68000up },
{"dbhi", 2,	one(0051310),	one(0177770), "DsBw", m68000up },
{"dble", 2,	one(0057710),	one(0177770), "DsBw", m68000up },
{"dbls", 2,	one(0051710),	one(0177770), "DsBw", m68000up },
{"dblt", 2,	one(0056710),	one(0177770), "DsBw", m68000up },
{"dbmi", 2,	one(0055710),	one(0177770), "DsBw", m68000up },
{"dbne", 2,	one(0053310),	one(0177770), "DsBw", m68000up },
{"dbpl", 2,	one(0055310),	one(0177770), "DsBw", m68000up },
{"dbt", 2,	one(0050310),	one(0177770), "DsBw", m68000up },
{"dbvc", 2,	one(0054310),	one(0177770), "DsBw", m68000up },
{"dbvs", 2,	one(0054710),	one(0177770), "DsBw", m68000up },

{"divsw", 2,	one(0100700),	one(0170700), ";wDd", m68000up | mcfhwdiv },

{"divsl", 4, 	two(0046100,0006000),two(0177700,0107770),";lD3D1", m68020up|cpu32 },
{"divsl", 4, 	two(0046100,0004000),two(0177700,0107770),";lDD",   m68020up|cpu32 },
{"divsl", 4, 	two(0046100,0004000),two(0177700,0107770),"qsDD",   mcfhwdiv },

{"divsll", 4, 	two(0046100,0004000),two(0177700,0107770),";lD3D1",m68020up|cpu32 },
{"divsll", 4, 	two(0046100,0004000),two(0177700,0107770),";lDD",  m68020up|cpu32 },

{"divuw", 2,	one(0100300),		one(0170700), ";wDd", m68000up | mcfhwdiv },

{"divul", 4,	two(0046100,0002000),two(0177700,0107770),";lD3D1", m68020up|cpu32 },
{"divul", 4,	two(0046100,0000000),two(0177700,0107770),";lDD",   m68020up|cpu32 },
{"divul", 4,	two(0046100,0000000),two(0177700,0107770),"qsDD",   mcfhwdiv },

{"divull", 4,	two(0046100,0000000),two(0177700,0107770),";lD3D1",m68020up|cpu32 },
{"divull", 4,	two(0046100,0000000),two(0177700,0107770),";lDD",  m68020up|cpu32 },

{"eorib", 4,	one(0005000),	one(0177700), "#b$s", m68000up },
{"eorib", 4,	one(0005074),	one(0177777), "#bCs", m68000up },
{"eoriw", 4,	one(0005100),	one(0177700), "#w$s", m68000up },
{"eoriw", 4,	one(0005174),	one(0177777), "#wSs", m68000up },
{"eoril", 6,	one(0005200),	one(0177700), "#l$s", m68000up },
{"eoril", 6,	one(0005200),	one(0177700), "#lDs", mcfisa_a },
{"eori", 4,	one(0005074),	one(0177777), "#bCs", m68000up },
{"eori", 4,	one(0005174),	one(0177777), "#wSs", m68000up },
{"eori", 4,	one(0005100),	one(0177700), "#w$s", m68000up },

/* The eor opcode can generate the eori instruction.  */
{"eorb", 4,	one(0005000),	one(0177700), "#b$s", m68000up },
{"eorb", 4,	one(0005074),	one(0177777), "#bCs", m68000up },
{"eorb", 2,	one(0130400),	one(0170700), "Dd$s", m68000up },
{"eorw", 4,	one(0005100),	one(0177700), "#w$s", m68000up },
{"eorw", 4,	one(0005174),	one(0177777), "#wSs", m68000up },
{"eorw", 2,	one(0130500),	one(0170700), "Dd$s", m68000up },
{"eorl", 6,	one(0005200),	one(0177700), "#l$s", m68000up },
{"eorl", 6,	one(0005200),	one(0177700), "#lDs", mcfisa_a },
{"eorl", 2,	one(0130600),	one(0170700), "Dd$s", m68000up | mcfisa_a },
{"eor", 4,	one(0005074),	one(0177777), "#bCs", m68000up },
{"eor", 4,	one(0005174),	one(0177777), "#wSs", m68000up },
{"eor", 4,	one(0005100),	one(0177700), "#w$s", m68000up },
{"eor", 2,	one(0130500),	one(0170700), "Dd$s", m68000up },

{"exg", 2,	one(0140500),	one(0170770), "DdDs", m68000up },
{"exg", 2,	one(0140510),	one(0170770), "AdAs", m68000up },
{"exg", 2,	one(0140610),	one(0170770), "DdAs", m68000up },
{"exg", 2,	one(0140610),	one(0170770), "AsDd", m68000up },

{"extw", 2,	one(0044200),	one(0177770), "Ds", m68000up|mcfisa_a },
{"extl", 2,	one(0044300),	one(0177770), "Ds", m68000up|mcfisa_a },
{"extbl", 2,	one(0044700),	one(0177770), "Ds", m68020up|cpu32|mcfisa_a },

{"ff1", 2,   	one(0002300), one(0177770), "Ds", mcfisa_aa},

/* float stuff starts here */

{"fabsb", 4,	two(0xF000, 0x5818), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fabsb", 4,	two(0xF000, 0x5818), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fabsd", 4,	two(0xF000, 0x0018), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fabsd", 4,	two(0xF000, 0x0018), two(0xF1C0, 0xE07F), "IiFt", cfloat },
{"fabsd", 4,	two(0xF000, 0x5418), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fabsd", 4,	two(0xF000, 0x5418), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fabsl", 4,	two(0xF000, 0x4018), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fabsl", 4,	two(0xF000, 0x4018), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fabsp", 4,	two(0xF000, 0x4C18), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fabss", 4,	two(0xF000, 0x4418), two(0xF1C0, 0xFC7F), "Ii;fF7", cfloat },
{"fabss", 4,	two(0xF000, 0x4418), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fabsw", 4,	two(0xF000, 0x5018), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fabsw", 4,	two(0xF000, 0x5018), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fabsx", 4,	two(0xF000, 0x0018), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fabsx", 4,	two(0xF000, 0x4818), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"fabsx", 4,	two(0xF000, 0x0018), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"fsabsb", 4,	two(0xF000, 0x5858), two(0xF1C0, 0xFC7F), "Ii;bF7", m68040up },
{"fsabsb", 4,	two(0xF000, 0x5858), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsabsd", 4,	two(0xF000, 0x0058), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fsabsd", 4,	two(0xF000, 0x0058), two(0xF1C0, 0xE07F), "IiFt", cfloat },
{"fsabsd", 4,	two(0xF000, 0x5458), two(0xF1C0, 0xFC7F), "Ii;FF7", m68040up },
{"fsabsd", 4,	two(0xF000, 0x5458), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fsabsl", 4,	two(0xF000, 0x4058), two(0xF1C0, 0xFC7F), "Ii;lF7", m68040up },
{"fsabsl", 4,	two(0xF000, 0x4058), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsabsp", 4,	two(0xF000, 0x4C58), two(0xF1C0, 0xFC7F), "Ii;pF7", m68040up },
{"fsabss", 4,	two(0xF000, 0x4258), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsabss", 4,	two(0xF000, 0x4458), two(0xF1C0, 0xFC7F), "Ii;fF7", m68040up },
{"fsabsw", 4,	two(0xF000, 0x5058), two(0xF1C0, 0xFC7F), "Ii;wF7", m68040up },
{"fsabsw", 4,	two(0xF000, 0x5058), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsabsx", 4,	two(0xF000, 0x0058), two(0xF1C0, 0xE07F), "IiF8F7", m68040up },
{"fsabsx", 4,	two(0xF000, 0x4858), two(0xF1C0, 0xFC7F), "Ii;xF7", m68040up },
{"fsabsx", 4,	two(0xF000, 0x0058), two(0xF1C0, 0xE07F), "IiFt",   m68040up },

{"fdabsb", 4,	two(0xF000, 0x585C), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdabsb", 4,	two(0xF000, 0x585c), two(0xF1C0, 0xFC7F), "Ii;bF7", m68040up},
{"fdabsd", 4,	two(0xF000, 0x005C), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fdabsd", 4,	two(0xF000, 0x005C), two(0xF1C0, 0xE07F), "IiFt", cfloat },
{"fdabsd", 4,	two(0xF000, 0x545C), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fdabsd", 4,	two(0xF000, 0x545c), two(0xF1C0, 0xFC7F), "Ii;FF7", m68040up},
{"fdabsl", 4,	two(0xF000, 0x405C), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdabsl", 4,	two(0xF000, 0x405c), two(0xF1C0, 0xFC7F), "Ii;lF7", m68040up},
{"fdabsp", 4,	two(0xF000, 0x4C5c), two(0xF1C0, 0xFC7F), "Ii;pF7", m68040up},
{"fdabss", 4,	two(0xF000, 0x425C), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdabss", 4,	two(0xF000, 0x445c), two(0xF1C0, 0xFC7F), "Ii;fF7", m68040up},
{"fdabsw", 4,	two(0xF000, 0x505C), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdabsw", 4,	two(0xF000, 0x505c), two(0xF1C0, 0xFC7F), "Ii;wF7", m68040up},
{"fdabsx", 4,	two(0xF000, 0x005c), two(0xF1C0, 0xE07F), "IiF8F7", m68040up},
{"fdabsx", 4,	two(0xF000, 0x485c), two(0xF1C0, 0xFC7F), "Ii;xF7", m68040up},
{"fdabsx", 4,	two(0xF000, 0x005c), two(0xF1C0, 0xE07F), "IiFt",   m68040up},

{"facosb", 4,	two(0xF000, 0x581C), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"facosd", 4,	two(0xF000, 0x541C), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"facosl", 4,	two(0xF000, 0x401C), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"facosp", 4,	two(0xF000, 0x4C1C), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"facoss", 4,	two(0xF000, 0x441C), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"facosw", 4,	two(0xF000, 0x501C), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"facosx", 4,	two(0xF000, 0x001C), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"facosx", 4,	two(0xF000, 0x481C), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"facosx", 4,	two(0xF000, 0x001C), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"faddb", 4,	two(0xF000, 0x5822), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"faddb", 4,	two(0xF000, 0x5822), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"faddd", 4,	two(0xF000, 0x0022), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"faddd", 4,	two(0xF000, 0x5422), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"faddd", 4,	two(0xF000, 0x5422), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"faddd", 4,	two(0xF000, 0x5422), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"faddl", 4,	two(0xF000, 0x4022), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"faddl", 4,	two(0xF000, 0x4022), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"faddp", 4,	two(0xF000, 0x4C22), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fadds", 4,	two(0xF000, 0x4422), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fadds", 4,	two(0xF000, 0x4422), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"faddw", 4,	two(0xF000, 0x5022), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"faddw", 4,	two(0xF000, 0x5022), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"faddx", 4,	two(0xF000, 0x0022), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"faddx", 4,	two(0xF000, 0x4822), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },

{"fsaddb", 4,	two(0xF000, 0x5862), two(0xF1C0, 0xFC7F), "Ii;bF7", m68040up },
{"fsaddb", 4,	two(0xF000, 0x5862), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsaddd", 4,	two(0xF000, 0x0066), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fsaddd", 4,	two(0xF000, 0x5462), two(0xF1C0, 0xFC7F), "Ii;FF7", m68040up },
{"fsaddd", 4,	two(0xF000, 0x5462), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fsaddl", 4,	two(0xF000, 0x4062), two(0xF1C0, 0xFC7F), "Ii;lF7", m68040up },
{"fsaddl", 4,	two(0xF000, 0x4062), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsaddp", 4,	two(0xF000, 0x4C62), two(0xF1C0, 0xFC7F), "Ii;pF7", m68040up },
{"fsadds", 4,	two(0xF000, 0x4462), two(0xF1C0, 0xFC7F), "Ii;fF7", m68040up },
{"fsadds", 4,	two(0xF000, 0x4862), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsaddw", 4,	two(0xF000, 0x5062), two(0xF1C0, 0xFC7F), "Ii;wF7", m68040up },
{"fsaddw", 4,	two(0xF000, 0x5062), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsaddx", 4,	two(0xF000, 0x0062), two(0xF1C0, 0xE07F), "IiF8F7", m68040up },
{"fsaddx", 4,	two(0xF000, 0x4862), two(0xF1C0, 0xFC7F), "Ii;xF7", m68040up },

{"fdaddb", 4,	two(0xF000, 0x5826), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdaddb", 4,	two(0xF000, 0x5866), two(0xF1C0, 0xFC7F), "Ii;bF7", m68040up },
{"fdaddd", 4,	two(0xF000, 0x0066), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fdaddd", 4,	two(0xF000, 0x5426), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdaddd", 4,	two(0xF000, 0x5466), two(0xF1C0, 0xFC7F), "Ii;FF7", m68040up },
{"fdaddl", 4,	two(0xF000, 0x4026), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fdaddl", 4,	two(0xF000, 0x4066), two(0xF1C0, 0xFC7F), "Ii;lF7", m68040up },
{"fdaddp", 4,	two(0xF000, 0x4C66), two(0xF1C0, 0xFC7F), "Ii;pF7", m68040up },
{"fdadds", 4,	two(0xF000, 0x4466), two(0xF1C0, 0xFC7F), "Ii;fF7", m68040up },
{"fdadds", 4,	two(0xF000, 0x4826), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdaddw", 4,	two(0xF000, 0x5026), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdaddw", 4,	two(0xF000, 0x5066), two(0xF1C0, 0xFC7F), "Ii;wF7", m68040up },
{"fdaddx", 4,	two(0xF000, 0x0066), two(0xF1C0, 0xE07F), "IiF8F7", m68040up },
{"fdaddx", 4,	two(0xF000, 0x4866), two(0xF1C0, 0xFC7F), "Ii;xF7", m68040up },

{"fasinb", 4,	two(0xF000, 0x580C), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fasind", 4,	two(0xF000, 0x540C), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fasinl", 4,	two(0xF000, 0x400C), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fasinp", 4,	two(0xF000, 0x4C0C), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fasins", 4,	two(0xF000, 0x440C), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fasinw", 4,	two(0xF000, 0x500C), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fasinx", 4,	two(0xF000, 0x000C), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fasinx", 4,	two(0xF000, 0x480C), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"fasinx", 4,	two(0xF000, 0x000C), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"fatanb", 4,	two(0xF000, 0x580A), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fatand", 4,	two(0xF000, 0x540A), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fatanl", 4,	two(0xF000, 0x400A), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fatanp", 4,	two(0xF000, 0x4C0A), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fatans", 4,	two(0xF000, 0x440A), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fatanw", 4,	two(0xF000, 0x500A), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fatanx", 4,	two(0xF000, 0x000A), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fatanx", 4,	two(0xF000, 0x480A), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"fatanx", 4,	two(0xF000, 0x000A), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"fatanhb", 4,	two(0xF000, 0x580D), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fatanhd", 4,	two(0xF000, 0x540D), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fatanhl", 4,	two(0xF000, 0x400D), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fatanhp", 4,	two(0xF000, 0x4C0D), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fatanhs", 4,	two(0xF000, 0x440D), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fatanhw", 4,	two(0xF000, 0x500D), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fatanhx", 4,	two(0xF000, 0x000D), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fatanhx", 4,	two(0xF000, 0x480D), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"fatanhx", 4,	two(0xF000, 0x000D), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"fbeq", 2,	one(0xF081),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbf", 2,	one(0xF080),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbge", 2,	one(0xF093),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbgl", 2,	one(0xF096),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbgle", 2,	one(0xF097),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbgt", 2,	one(0xF092),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fble", 2,	one(0xF095),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fblt", 2,	one(0xF094),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbne", 2,	one(0xF08E),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbnge", 2,	one(0xF09C),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbngl", 2,	one(0xF099),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbngle", 2,	one(0xF098),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbngt", 2,	one(0xF09D),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbnle", 2,	one(0xF09A),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbnlt", 2,	one(0xF09B),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fboge", 2,	one(0xF083),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbogl", 2,	one(0xF086),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbogt", 2,	one(0xF082),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbole", 2,	one(0xF085),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbolt", 2,	one(0xF084),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbor", 2,	one(0xF087),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbseq", 2,	one(0xF091),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbsf", 2,	one(0xF090),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbsne", 2,	one(0xF09E),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbst", 2,	one(0xF09F),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbt", 2,	one(0xF08F),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbueq", 2,	one(0xF089),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbuge", 2,	one(0xF08B),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbugt", 2,	one(0xF08A),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbule", 2,	one(0xF08D),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbult", 2,	one(0xF08C),		one(0xF1FF), "IdBW", mfloat | cfloat },
{"fbun", 2,	one(0xF088),		one(0xF1FF), "IdBW", mfloat | cfloat },

{"fbeql", 2,	one(0xF0C1),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbfl", 2,	one(0xF0C0),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbgel", 2,	one(0xF0D3),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbgll", 2,	one(0xF0D6),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbglel", 2,	one(0xF0D7),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbgtl", 2,	one(0xF0D2),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fblel", 2,	one(0xF0D5),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbltl", 2,	one(0xF0D4),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbnel", 2,	one(0xF0CE),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbngel", 2,	one(0xF0DC),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbngll", 2,	one(0xF0D9),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbnglel", 2,	one(0xF0D8),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbngtl", 2,	one(0xF0DD),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbnlel", 2,	one(0xF0DA),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbnltl", 2,	one(0xF0DB),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbogel", 2,	one(0xF0C3),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbogll", 2,	one(0xF0C6),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbogtl", 2,	one(0xF0C2),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbolel", 2,	one(0xF0C5),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fboltl", 2,	one(0xF0C4),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fborl", 2,	one(0xF0C7),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbseql", 2,	one(0xF0D1),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbsfl", 2,	one(0xF0D0),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbsnel", 2,	one(0xF0DE),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbstl", 2,	one(0xF0DF),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbtl", 2,	one(0xF0CF),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbueql", 2,	one(0xF0C9),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbugel", 2,	one(0xF0CB),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbugtl", 2,	one(0xF0CA),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbulel", 2,	one(0xF0CD),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbultl", 2,	one(0xF0CC),		one(0xF1FF), "IdBC", mfloat | cfloat },
{"fbunl", 2,	one(0xF0C8),		one(0xF1FF), "IdBC", mfloat | cfloat },

{"fjeq", 2,	one(0xF081),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjf", 2,	one(0xF080),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjge", 2,	one(0xF093),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjgl", 2,	one(0xF096),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjgle", 2,	one(0xF097),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjgt", 2,	one(0xF092),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjle", 2,	one(0xF095),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjlt", 2,	one(0xF094),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjne", 2,	one(0xF08E),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjnge", 2,	one(0xF09C),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjngl", 2,	one(0xF099),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjngle", 2,	one(0xF098),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjngt", 2,	one(0xF09D),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjnle", 2,	one(0xF09A),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjnlt", 2,	one(0xF09B),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjoge", 2,	one(0xF083),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjogl", 2,	one(0xF086),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjogt", 2,	one(0xF082),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjole", 2,	one(0xF085),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjolt", 2,	one(0xF084),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjor", 2,	one(0xF087),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjseq", 2,	one(0xF091),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjsf", 2,	one(0xF090),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjsne", 2,	one(0xF09E),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjst", 2,	one(0xF09F),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjt", 2,	one(0xF08F),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjueq", 2,	one(0xF089),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjuge", 2,	one(0xF08B),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjugt", 2,	one(0xF08A),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjule", 2,	one(0xF08D),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjult", 2,	one(0xF08C),		one(0xF1BF), "IdBc", mfloat | cfloat },
{"fjun", 2,	one(0xF088),		one(0xF1BF), "IdBc", mfloat | cfloat },

{"fcmpb", 4,	two(0xF000, 0x5838), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fcmpb", 4,	two(0xF000, 0x5838), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fcmpd", 4,	two(0xF000, 0x5438), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fcmpd", 4,	two(0xF000, 0x5438), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fcmpd", 4,	two(0xF000, 0x0038), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fcmpl", 4,	two(0xF000, 0x4038), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fcmpl", 4,	two(0xF000, 0x4038), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fcmpp", 4,	two(0xF000, 0x4C38), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fcmps", 4,	two(0xF000, 0x4438), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fcmps", 4,	two(0xF000, 0x4438), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fcmpw", 4,	two(0xF000, 0x5038), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fcmpw", 4,	two(0xF000, 0x5038), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fcmpx", 4,	two(0xF000, 0x0038), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fcmpx", 4,	two(0xF000, 0x4838), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },

{"fcosb", 4,	two(0xF000, 0x581D), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fcosd", 4,	two(0xF000, 0x541D), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fcosl", 4,	two(0xF000, 0x401D), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fcosp", 4,	two(0xF000, 0x4C1D), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fcoss", 4,	two(0xF000, 0x441D), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fcosw", 4,	two(0xF000, 0x501D), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fcosx", 4,	two(0xF000, 0x001D), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fcosx", 4,	two(0xF000, 0x481D), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"fcosx", 4,	two(0xF000, 0x001D), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"fcoshb", 4,	two(0xF000, 0x5819), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fcoshd", 4,	two(0xF000, 0x5419), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fcoshl", 4,	two(0xF000, 0x4019), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fcoshp", 4,	two(0xF000, 0x4C19), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fcoshs", 4,	two(0xF000, 0x4419), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fcoshw", 4,	two(0xF000, 0x5019), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fcoshx", 4,	two(0xF000, 0x0019), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fcoshx", 4,	two(0xF000, 0x4819), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"fcoshx", 4,	two(0xF000, 0x0019), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"fdbeq", 4,	two(0xF048, 0x0001), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbf", 4,	two(0xF048, 0x0000), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbge", 4,	two(0xF048, 0x0013), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbgl", 4,	two(0xF048, 0x0016), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbgle", 4,	two(0xF048, 0x0017), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbgt", 4,	two(0xF048, 0x0012), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdble", 4,	two(0xF048, 0x0015), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdblt", 4,	two(0xF048, 0x0014), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbne", 4,	two(0xF048, 0x000E), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbnge", 4,	two(0xF048, 0x001C), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbngl", 4,	two(0xF048, 0x0019), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbngle", 4,	two(0xF048, 0x0018), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbngt", 4,	two(0xF048, 0x001D), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbnle", 4,	two(0xF048, 0x001A), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbnlt", 4,	two(0xF048, 0x001B), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdboge", 4,	two(0xF048, 0x0003), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbogl", 4,	two(0xF048, 0x0006), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbogt", 4,	two(0xF048, 0x0002), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbole", 4,	two(0xF048, 0x0005), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbolt", 4,	two(0xF048, 0x0004), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbor", 4,	two(0xF048, 0x0007), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbseq", 4,	two(0xF048, 0x0011), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbsf", 4,	two(0xF048, 0x0010), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbsne", 4,	two(0xF048, 0x001E), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbst", 4,	two(0xF048, 0x001F), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbt", 4,	two(0xF048, 0x000F), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbueq", 4,	two(0xF048, 0x0009), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbuge", 4,	two(0xF048, 0x000B), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbugt", 4,	two(0xF048, 0x000A), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbule", 4,	two(0xF048, 0x000D), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbult", 4,	two(0xF048, 0x000C), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },
{"fdbun", 4,	two(0xF048, 0x0008), two(0xF1F8, 0xFFFF), "IiDsBw", mfloat },

{"fdivb", 4,	two(0xF000, 0x5820), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fdivb", 4,	two(0xF000, 0x5820), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdivd", 4,	two(0xF000, 0x0020), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fdivd", 4,	two(0xF000, 0x5420), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fdivd", 4,	two(0xF000, 0x5420), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fdivl", 4,	two(0xF000, 0x4020), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fdivl", 4,	two(0xF000, 0x4020), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdivp", 4,	two(0xF000, 0x4C20), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fdivs", 4,	two(0xF000, 0x4420), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fdivs", 4,	two(0xF000, 0x4420), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdivw", 4,	two(0xF000, 0x5020), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fdivw", 4,	two(0xF000, 0x5020), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdivx", 4,	two(0xF000, 0x0020), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fdivx", 4,	two(0xF000, 0x4820), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },

{"fsdivb", 4,	two(0xF000, 0x5860), two(0xF1C0, 0xFC7F), "Ii;bF7", m68040up },
{"fsdivb", 4,	two(0xF000, 0x5860), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsdivd", 4,	two(0xF000, 0x0060), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fsdivd", 4,	two(0xF000, 0x5460), two(0xF1C0, 0xFC7F), "Ii;FF7", m68040up },
{"fsdivd", 4,	two(0xF000, 0x5460), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fsdivl", 4,	two(0xF000, 0x4060), two(0xF1C0, 0xFC7F), "Ii;lF7", m68040up },
{"fsdivl", 4,	two(0xF000, 0x4060), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsdivp", 4,	two(0xF000, 0x4C60), two(0xF1C0, 0xFC7F), "Ii;pF7", m68040up },
{"fsdivs", 4,	two(0xF000, 0x4460), two(0xF1C0, 0xFC7F), "Ii;fF7", m68040up },
{"fsdivs", 4,	two(0xF000, 0x4460), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsdivw", 4,	two(0xF000, 0x5060), two(0xF1C0, 0xFC7F), "Ii;wF7", m68040up },
{"fsdivw", 4,	two(0xF000, 0x5060), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsdivx", 4,	two(0xF000, 0x0060), two(0xF1C0, 0xE07F), "IiF8F7", m68040up },
{"fsdivx", 4,	two(0xF000, 0x4860), two(0xF1C0, 0xFC7F), "Ii;xF7", m68040up },

{"fddivb", 4,	two(0xF000, 0x5864), two(0xF1C0, 0xFC7F), "Ii;bF7", m68040up },
{"fddivb", 4,	two(0xF000, 0x5864), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fddivd", 4,	two(0xF000, 0x0064), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fddivd", 4,	two(0xF000, 0x5464), two(0xF1C0, 0xFC7F), "Ii;FF7", m68040up },
{"fddivd", 4,	two(0xF000, 0x5464), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fddivl", 4,	two(0xF000, 0x4064), two(0xF1C0, 0xFC7F), "Ii;lF7", m68040up },
{"fddivl", 4,	two(0xF000, 0x4064), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fddivp", 4,	two(0xF000, 0x4C64), two(0xF1C0, 0xFC7F), "Ii;pF7", m68040up },
{"fddivs", 4,	two(0xF000, 0x4464), two(0xF1C0, 0xFC7F), "Ii;fF7", m68040up },
{"fddivs", 4,	two(0xF000, 0x4464), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fddivw", 4,	two(0xF000, 0x5064), two(0xF1C0, 0xFC7F), "Ii;wF7", m68040up },
{"fddivw", 4,	two(0xF000, 0x5064), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fddivx", 4,	two(0xF000, 0x0064), two(0xF1C0, 0xE07F), "IiF8F7", m68040up },
{"fddivx", 4,	two(0xF000, 0x4864), two(0xF1C0, 0xFC7F), "Ii;xF7", m68040up },

{"fetoxb", 4,	two(0xF000, 0x5810), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fetoxd", 4,	two(0xF000, 0x5410), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fetoxl", 4,	two(0xF000, 0x4010), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fetoxp", 4,	two(0xF000, 0x4C10), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fetoxs", 4,	two(0xF000, 0x4410), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fetoxw", 4,	two(0xF000, 0x5010), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fetoxx", 4,	two(0xF000, 0x0010), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fetoxx", 4,	two(0xF000, 0x4810), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"fetoxx", 4,	two(0xF000, 0x0010), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"fetoxm1b", 4,	two(0xF000, 0x5808), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fetoxm1d", 4,	two(0xF000, 0x5408), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fetoxm1l", 4,	two(0xF000, 0x4008), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fetoxm1p", 4,	two(0xF000, 0x4C08), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fetoxm1s", 4,	two(0xF000, 0x4408), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fetoxm1w", 4,	two(0xF000, 0x5008), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fetoxm1x", 4,	two(0xF000, 0x0008), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fetoxm1x", 4,	two(0xF000, 0x4808), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"fetoxm1x", 4,	two(0xF000, 0x0008), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"fgetexpb", 4,	two(0xF000, 0x581E), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fgetexpd", 4,	two(0xF000, 0x541E), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fgetexpl", 4,	two(0xF000, 0x401E), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fgetexpp", 4,	two(0xF000, 0x4C1E), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fgetexps", 4,	two(0xF000, 0x441E), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fgetexpw", 4,	two(0xF000, 0x501E), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fgetexpx", 4,	two(0xF000, 0x001E), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fgetexpx", 4,	two(0xF000, 0x481E), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"fgetexpx", 4,	two(0xF000, 0x001E), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"fgetmanb", 4,	two(0xF000, 0x581F), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fgetmand", 4,	two(0xF000, 0x541F), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fgetmanl", 4,	two(0xF000, 0x401F), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fgetmanp", 4,	two(0xF000, 0x4C1F), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fgetmans", 4,	two(0xF000, 0x441F), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fgetmanw", 4,	two(0xF000, 0x501F), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fgetmanx", 4,	two(0xF000, 0x001F), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fgetmanx", 4,	two(0xF000, 0x481F), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"fgetmanx", 4,	two(0xF000, 0x001F), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"fintb", 4,	two(0xF000, 0x5801), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fintb", 4,	two(0xF000, 0x5801), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fintd", 4,	two(0xF000, 0x0001), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fintd", 4,	two(0xF000, 0x0001), two(0xF1C0, 0xE07F), "IiFt", cfloat },
{"fintd", 4,	two(0xF000, 0x5401), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fintd", 4,	two(0xF000, 0x5401), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fintl", 4,	two(0xF000, 0x4001), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fintl", 4,	two(0xF000, 0x4001), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fintp", 4,	two(0xF000, 0x4C01), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fints", 4,	two(0xF000, 0x4401), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fints", 4,	two(0xF000, 0x4401), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fintw", 4,	two(0xF000, 0x5001), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fintw", 4,	two(0xF000, 0x5001), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fintx", 4,	two(0xF000, 0x0001), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fintx", 4,	two(0xF000, 0x4801), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"fintx", 4,	two(0xF000, 0x0001), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"fintrzb", 4,	two(0xF000, 0x5803), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fintrzb", 4,	two(0xF000, 0x5803), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fintrzd", 4,	two(0xF000, 0x0003), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fintrzd", 4,	two(0xF000, 0x0003), two(0xF1C0, 0xE07F), "IiFt",   cfloat },
{"fintrzd", 4,	two(0xF000, 0x5403), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fintrzd", 4,	two(0xF000, 0x5403), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fintrzl", 4,	two(0xF000, 0x4003), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fintrzl", 4,	two(0xF000, 0x4003), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fintrzp", 4,	two(0xF000, 0x4C03), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fintrzs", 4,	two(0xF000, 0x4403), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fintrzs", 4,	two(0xF000, 0x4403), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fintrzw", 4,	two(0xF000, 0x5003), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fintrzw", 4,	two(0xF000, 0x5003), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fintrzx", 4,	two(0xF000, 0x0003), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fintrzx", 4,	two(0xF000, 0x4803), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"fintrzx", 4,	two(0xF000, 0x0003), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"flog10b", 4,	two(0xF000, 0x5815), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"flog10d", 4,	two(0xF000, 0x5415), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"flog10l", 4,	two(0xF000, 0x4015), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"flog10p", 4,	two(0xF000, 0x4C15), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"flog10s", 4,	two(0xF000, 0x4415), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"flog10w", 4,	two(0xF000, 0x5015), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"flog10x", 4,	two(0xF000, 0x0015), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"flog10x", 4,	two(0xF000, 0x4815), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"flog10x", 4,	two(0xF000, 0x0015), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"flog2b", 4,	two(0xF000, 0x5816), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"flog2d", 4,	two(0xF000, 0x5416), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"flog2l", 4,	two(0xF000, 0x4016), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"flog2p", 4,	two(0xF000, 0x4C16), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"flog2s", 4,	two(0xF000, 0x4416), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"flog2w", 4,	two(0xF000, 0x5016), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"flog2x", 4,	two(0xF000, 0x0016), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"flog2x", 4,	two(0xF000, 0x4816), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"flog2x", 4,	two(0xF000, 0x0016), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"flognb", 4,	two(0xF000, 0x5814), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"flognd", 4,	two(0xF000, 0x5414), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"flognl", 4,	two(0xF000, 0x4014), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"flognp", 4,	two(0xF000, 0x4C14), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"flogns", 4,	two(0xF000, 0x4414), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"flognw", 4,	two(0xF000, 0x5014), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"flognx", 4,	two(0xF000, 0x0014), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"flognx", 4,	two(0xF000, 0x4814), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"flognx", 4,	two(0xF000, 0x0014), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"flognp1b", 4,	two(0xF000, 0x5806), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"flognp1d", 4,	two(0xF000, 0x5406), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"flognp1l", 4,	two(0xF000, 0x4006), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"flognp1p", 4,	two(0xF000, 0x4C06), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"flognp1s", 4,	two(0xF000, 0x4406), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"flognp1w", 4,	two(0xF000, 0x5006), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"flognp1x", 4,	two(0xF000, 0x0006), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"flognp1x", 4,	two(0xF000, 0x4806), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"flognp1x", 4,	two(0xF000, 0x0006), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"fmodb", 4,	two(0xF000, 0x5821), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fmodd", 4,	two(0xF000, 0x5421), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fmodl", 4,	two(0xF000, 0x4021), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fmodp", 4,	two(0xF000, 0x4C21), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fmods", 4,	two(0xF000, 0x4421), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fmodw", 4,	two(0xF000, 0x5021), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fmodx", 4,	two(0xF000, 0x0021), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fmodx", 4,	two(0xF000, 0x4821), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },

{"fmoveb", 4,	two(0xF000, 0x5800), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fmoveb", 4,	two(0xF000, 0x7800), two(0xF1C0, 0xFC7F), "IiF7bs", cfloat },
{"fmoveb", 4,	two(0xF000, 0x5800), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fmoveb", 4,	two(0xF000, 0x7800), two(0xF1C0, 0xFC7F), "IiF7$b", mfloat },
{"fmoved", 4,	two(0xF000, 0x5400), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fmoved", 4,	two(0xF000, 0x7400), two(0xF1C0, 0xFC7F), "IiF7~F", mfloat },
{"fmoved", 4,	two(0xF000, 0x0000), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fmoved", 4,	two(0xF000, 0x5400), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fmoved", 4,	two(0xF000, 0x7400), two(0xF1C0, 0xFC7F), "IiF7ws", cfloat },
{"fmovel", 4,	two(0xF000, 0x4000), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fmovel", 4,	two(0xF000, 0x6000), two(0xF1C0, 0xFC7F), "IiF7$l", mfloat },
/* FIXME: the next two variants should not permit moving an address
   register to anything but the floating point instruction register.  */
{"fmovel", 4,	two(0xF000, 0xA000), two(0xF1C0, 0xE3FF), "Iis8%s", mfloat },
{"fmovel", 4,	two(0xF000, 0x8000), two(0xF1C0, 0xE3FF), "Ii*ls8", mfloat },
{"fmovel", 4,	two(0xF000, 0x4000), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fmovel", 4,	two(0xF000, 0x6000), two(0xF1C0, 0xFC7F), "IiF7bs", cfloat },
  /* Move the FP control registers.  */
{"fmovel", 4,	two(0xF000, 0xA000), two(0xF1C0, 0xE3FF), "Iis8ps", cfloat },
{"fmovel", 4,	two(0xF000, 0x8000), two(0xF1C0, 0xE3FF), "Iibss8", cfloat },
{"fmovep", 4,	two(0xF000, 0x4C00), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fmovep", 4,	two(0xF000, 0x6C00), two(0xF1C0, 0xFC00), "IiF7~pkC", mfloat },
{"fmovep", 4,	two(0xF000, 0x7C00), two(0xF1C0, 0xFC0F), "IiF7~pDk", mfloat },
{"fmoves", 4,	two(0xF000, 0x4400), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fmoves", 4,	two(0xF000, 0x6400), two(0xF1C0, 0xFC7F), "IiF7$f", mfloat },
{"fmoves", 4,	two(0xF000, 0x4400), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fmoves", 4,	two(0xF000, 0x6400), two(0xF1C0, 0xFC7F), "IiF7qs", cfloat },
{"fmovew", 4,	two(0xF000, 0x5000), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fmovew", 4,	two(0xF000, 0x7000), two(0xF1C0, 0xFC7F), "IiF7$w", mfloat },
{"fmovew", 4,	two(0xF000, 0x5000), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fmovew", 4,	two(0xF000, 0x7000), two(0xF1C0, 0xFC7F), "IiF7qs", cfloat },
{"fmovex", 4,	two(0xF000, 0x0000), two(0xF1FF, 0xE07F), "IiF8F7", mfloat },
{"fmovex", 4,	two(0xF000, 0x4800), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"fmovex", 4,	two(0xF000, 0x6800), two(0xF1C0, 0xFC7F), "IiF7~x", mfloat },

{"fsmoveb", 4,	two(0xF000, 0x5840), two(0xF1C0, 0xFC7F), "Ii;bF7", m68040up },
{"fsmoveb", 4,	two(0xF000, 0x5840), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsmoveb", 4,	two(0xF000, 0x7840), two(0xF1C0, 0xFC7F), "IiF7qs", cfloat },
{"fsmoved", 4,	two(0xF000, 0x0040), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fsmoved", 4,	two(0xF000, 0x5440), two(0xF1C0, 0xFC7F), "Ii;FF7", m68040up },
{"fsmoved", 4,	two(0xF000, 0x5440), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fsmoved", 4,	two(0xF000, 0x7440), two(0xF1C0, 0xFC7F), "IiF7ws", cfloat },
{"fsmovel", 4,	two(0xF000, 0x4040), two(0xF1C0, 0xFC7F), "Ii;lF7", m68040up },
{"fsmovel", 4,	two(0xF000, 0x4040), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsmovel", 4,	two(0xF000, 0x6040), two(0xF1C0, 0xFC7F), "IiF7qs", cfloat },
{"fsmoves", 4,	two(0xF000, 0x4440), two(0xF1C0, 0xFC7F), "Ii;fF7", m68040up },
{"fsmoves", 4,	two(0xF000, 0x4440), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsmoves", 4,	two(0xF000, 0x6440), two(0xF1C0, 0xFC7F), "IiF7qs", cfloat },
{"fsmovew", 4,	two(0xF000, 0x5040), two(0xF1C0, 0xFC7F), "Ii;wF7", m68040up },
{"fsmovew", 4,	two(0xF000, 0x5040), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsmovew", 4,	two(0xF000, 0x7040), two(0xF1C0, 0xFC7F), "IiF7qs", cfloat },
{"fsmovex", 4,	two(0xF000, 0x0040), two(0xF1C0, 0xE07F), "IiF8F7", m68040up },
{"fsmovex", 4,	two(0xF000, 0x4840), two(0xF1C0, 0xFC7F), "Ii;xF7", m68040up },
{"fsmovep", 4,	two(0xF000, 0x4C40), two(0xF1C0, 0xFC7F), "Ii;pF7", m68040up },

{"fdmoveb", 4,	two(0xF000, 0x5844), two(0xF1C0, 0xFC7F), "Ii;bF7", m68040up },
{"fdmoveb", 4,	two(0xF000, 0x5844), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdmoveb", 4,	two(0xF000, 0x7844), two(0xF1C0, 0xFC7F), "IiF7qs", cfloat },
{"fdmoved", 4,	two(0xF000, 0x0044), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fdmoved", 4,	two(0xF000, 0x5444), two(0xF1C0, 0xFC7F), "Ii;FF7", m68040up },
{"fdmoved", 4,	two(0xF000, 0x5444), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fdmoved", 4,	two(0xF000, 0x7444), two(0xF1C0, 0xFC7F), "IiF7qs", cfloat },
{"fdmovel", 4,	two(0xF000, 0x4044), two(0xF1C0, 0xFC7F), "Ii;lF7", m68040up },
{"fdmovel", 4,	two(0xF000, 0x4044), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdmovel", 4,	two(0xF000, 0x6044), two(0xF1C0, 0xFC7F), "IiF7qs", cfloat },
{"fdmoves", 4,	two(0xF000, 0x4444), two(0xF1C0, 0xFC7F), "Ii;fF7", m68040up },
{"fdmoves", 4,	two(0xF000, 0x4444), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdmoves", 4,	two(0xF000, 0x6444), two(0xF1C0, 0xFC7F), "IiF7qs", cfloat },
{"fdmovew", 4,	two(0xF000, 0x5044), two(0xF1C0, 0xFC7F), "Ii;wF7", m68040up },
{"fdmovew", 4,	two(0xF000, 0x5044), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdmovew", 4,	two(0xF000, 0x7044), two(0xF1C0, 0xFC7F), "IiF7qs", cfloat },
{"fdmovex", 4,	two(0xF000, 0x0044), two(0xF1C0, 0xE07F), "IiF8F7", m68040up },
{"fdmovex", 4,	two(0xF000, 0x4844), two(0xF1C0, 0xFC7F), "Ii;xF7", m68040up },
{"fdmovep", 4,	two(0xF000, 0x4C44), two(0xF1C0, 0xFC7F), "Ii;pF7", m68040up },

{"fmovecrx", 4,	two(0xF000, 0x5C00), two(0xF1FF, 0xFC00), "Ii#CF7", mfloat },

{"fmovemd", 4,	two(0xF000, 0xD000), two(0xFFC0, 0xFF00), "Iizsl3", cfloat },
{"fmovemd", 4,	two(0xF000, 0xD000), two(0xFFC0, 0xFF00), "Iizs#3", cfloat },
{"fmovemd", 4,	two(0xF000, 0xF000), two(0xFFC0, 0xFF00), "Ii#3ys", cfloat },
{"fmovemd", 4,	two(0xF000, 0xF000), two(0xFFC0, 0xFF00), "Iil3ys", cfloat },

{"fmovemx", 4,	two(0xF000, 0xF800), two(0xF1C0, 0xFF8F), "IiDk&s", mfloat },
{"fmovemx", 4,	two(0xF020, 0xE800), two(0xF1F8, 0xFF8F), "IiDk-s", mfloat },
{"fmovemx", 4,	two(0xF000, 0xD800), two(0xF1C0, 0xFF8F), "Ii&sDk", mfloat },
{"fmovemx", 4,	two(0xF018, 0xD800), two(0xF1F8, 0xFF8F), "Ii+sDk", mfloat },
{"fmovemx", 4,	two(0xF000, 0xF000), two(0xF1C0, 0xFF00), "Idl3&s", mfloat },
{"fmovemx", 4,	two(0xF000, 0xF000), two(0xF1C0, 0xFF00), "Id#3&s", mfloat },
{"fmovemx", 4,	two(0xF000, 0xD000), two(0xF1C0, 0xFF00), "Id&sl3", mfloat },
{"fmovemx", 4,	two(0xF000, 0xD000), two(0xF1C0, 0xFF00), "Id&s#3", mfloat },
{"fmovemx", 4,	two(0xF020, 0xE000), two(0xF1F8, 0xFF00), "IdL3-s", mfloat },
{"fmovemx", 4,	two(0xF020, 0xE000), two(0xF1F8, 0xFF00), "Id#3-s", mfloat },
{"fmovemx", 4,	two(0xF018, 0xD000), two(0xF1F8, 0xFF00), "Id+sl3", mfloat },
{"fmovemx", 4,	two(0xF018, 0xD000), two(0xF1F8, 0xFF00), "Id+s#3", mfloat },

{"fmoveml", 4,	two(0xF000, 0xA000), two(0xF1C0, 0xE3FF), "Iis8%s", mfloat },
{"fmoveml", 4,	two(0xF000, 0xA000), two(0xF1C0, 0xE3FF), "IiL8~s", mfloat },
/* FIXME: In the next instruction, we should only permit %dn if the
   target is a single register.  We should only permit %an if the
   target is a single %fpiar.  */
{"fmoveml", 4,	two(0xF000, 0x8000), two(0xF1C0, 0xE3FF), "Ii*lL8", mfloat },

{"fmovem", 4,	two(0xF000, 0xD000), two(0xFFC0, 0xFF00), "IizsL3", cfloat },
{"fmovem", 4,	two(0xF000, 0xD000), two(0xFFC0, 0xFF00), "Iizs#3", cfloat },
{"fmovem", 4,	two(0xF000, 0xF000), two(0xFFC0, 0xFF00), "Ii#3ys", cfloat },
{"fmovem", 4,	two(0xF000, 0xF000), two(0xFFC0, 0xFF00), "IiL3ys", cfloat },

{"fmovem", 4,	two(0xF020, 0xE000), two(0xF1F8, 0xFF00), "IdL3-s", mfloat },
{"fmovem", 4,	two(0xF000, 0xF000), two(0xF1C0, 0xFF00), "Idl3&s", mfloat },
{"fmovem", 4,	two(0xF018, 0xD000), two(0xF1F8, 0xFF00), "Id+sl3", mfloat },
{"fmovem", 4,	two(0xF000, 0xD000), two(0xF1C0, 0xFF00), "Id&sl3", mfloat },
{"fmovem", 4,	two(0xF020, 0xE000), two(0xF1F8, 0xFF00), "Id#3-s", mfloat },
{"fmovem", 4,	two(0xF020, 0xE800), two(0xF1F8, 0xFF8F), "IiDk-s", mfloat },
{"fmovem", 4,	two(0xF000, 0xF000), two(0xF1C0, 0xFF00), "Id#3&s", mfloat },
{"fmovem", 4,	two(0xF000, 0xF800), two(0xF1C0, 0xFF8F), "IiDk&s", mfloat },
{"fmovem", 4,	two(0xF018, 0xD000), two(0xF1F8, 0xFF00), "Id+s#3", mfloat },
{"fmovem", 4,	two(0xF018, 0xD800), two(0xF1F8, 0xFF8F), "Ii+sDk", mfloat },
{"fmovem", 4,	two(0xF000, 0xD000), two(0xF1C0, 0xFF00), "Id&s#3", mfloat },
{"fmovem", 4,	two(0xF000, 0xD800), two(0xF1C0, 0xFF8F), "Ii&sDk", mfloat },
{"fmovem", 4,	two(0xF000, 0xA000), two(0xF1C0, 0xE3FF), "Iis8%s", mfloat },
{"fmovem", 4,	two(0xF000, 0x8000), two(0xF1C0, 0xE3FF), "Ii*ss8", mfloat },
{"fmovem", 4,	two(0xF000, 0xA000), two(0xF1C0, 0xE3FF), "IiL8~s", mfloat },
{"fmovem", 4,	two(0xF000, 0x8000), two(0xF2C0, 0xE3FF), "Ii*sL8", mfloat },

{"fmulb", 4,	two(0xF000, 0x5823), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fmulb", 4,	two(0xF000, 0x5823), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fmuld", 4,	two(0xF000, 0x0023), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fmuld", 4,	two(0xF000, 0x5423), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fmuld", 4,	two(0xF000, 0x5423), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fmull", 4,	two(0xF000, 0x4023), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fmull", 4,	two(0xF000, 0x4023), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fmulp", 4,	two(0xF000, 0x4C23), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fmuls", 4,	two(0xF000, 0x4423), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fmuls", 4,	two(0xF000, 0x4423), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fmulw", 4,	two(0xF000, 0x5023), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fmulw", 4,	two(0xF000, 0x5023), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fmulx", 4,	two(0xF000, 0x0023), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fmulx", 4,	two(0xF000, 0x4823), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },

{"fsmulb", 4,	two(0xF000, 0x5863), two(0xF1C0, 0xFC7F), "Ii;bF7", m68040up },
{"fsmulb", 4,	two(0xF000, 0x5863), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsmuld", 4,	two(0xF000, 0x0063), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fsmuld", 4,	two(0xF000, 0x5463), two(0xF1C0, 0xFC7F), "Ii;FF7", m68040up },
{"fsmuld", 4,	two(0xF000, 0x5463), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fsmull", 4,	two(0xF000, 0x4063), two(0xF1C0, 0xFC7F), "Ii;lF7", m68040up },
{"fsmull", 4,	two(0xF000, 0x4063), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsmulp", 4,	two(0xF000, 0x4C63), two(0xF1C0, 0xFC7F), "Ii;pF7", m68040up },
{"fsmuls", 4,	two(0xF000, 0x4463), two(0xF1C0, 0xFC7F), "Ii;fF7", m68040up },
{"fsmuls", 4,	two(0xF000, 0x4463), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsmulw", 4,	two(0xF000, 0x5063), two(0xF1C0, 0xFC7F), "Ii;wF7", m68040up },
{"fsmulw", 4,	two(0xF000, 0x5063), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsmulx", 4,	two(0xF000, 0x0063), two(0xF1C0, 0xE07F), "IiF8F7", m68040up },
{"fsmulx", 4,	two(0xF000, 0x4863), two(0xF1C0, 0xFC7F), "Ii;xF7", m68040up },

{"fdmulb", 4,	two(0xF000, 0x5867), two(0xF1C0, 0xFC7F), "Ii;bF7", m68040up },
{"fdmulb", 4,	two(0xF000, 0x5867), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdmuld", 4,	two(0xF000, 0x0067), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fdmuld", 4,	two(0xF000, 0x5467), two(0xF1C0, 0xFC7F), "Ii;FF7", m68040up },
{"fdmuld", 4,	two(0xF000, 0x5467), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fdmull", 4,	two(0xF000, 0x4067), two(0xF1C0, 0xFC7F), "Ii;lF7", m68040up },
{"fdmull", 4,	two(0xF000, 0x4067), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdmulp", 4,	two(0xF000, 0x4C67), two(0xF1C0, 0xFC7F), "Ii;pF7", m68040up },
{"fdmuls", 4,	two(0xF000, 0x4467), two(0xF1C0, 0xFC7F), "Ii;fF7", m68040up },
{"fdmuls", 4,	two(0xF000, 0x4467), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdmulw", 4,	two(0xF000, 0x5067), two(0xF1C0, 0xFC7F), "Ii;wF7", m68040up },
{"fdmulw", 4,	two(0xF000, 0x5067), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdmulx", 4,	two(0xF000, 0x0067), two(0xF1C0, 0xE07F), "IiF8F7", m68040up },
{"fdmulx", 4,	two(0xF000, 0x4867), two(0xF1C0, 0xFC7F), "Ii;xF7", m68040up },

{"fnegb", 4,	two(0xF000, 0x581A), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fnegb", 4,	two(0xF000, 0x581A), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fnegd", 4,	two(0xF000, 0x001A), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fnegd", 4,	two(0xF000, 0x001A), two(0xF1C0, 0xE07F), "IiFt",   cfloat },
{"fnegd", 4,	two(0xF000, 0x541A), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fnegd", 4,	two(0xF000, 0x541A), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fnegl", 4,	two(0xF000, 0x401A), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fnegl", 4,	two(0xF000, 0x401A), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fnegp", 4,	two(0xF000, 0x4C1A), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fnegs", 4,	two(0xF000, 0x441A), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fnegs", 4,	two(0xF000, 0x441A), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fnegw", 4,	two(0xF000, 0x501A), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fnegw", 4,	two(0xF000, 0x501A), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fnegx", 4,	two(0xF000, 0x001A), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fnegx", 4,	two(0xF000, 0x481A), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"fnegx", 4,	two(0xF000, 0x001A), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"fsnegb", 4,	two(0xF000, 0x585A), two(0xF1C0, 0xFC7F), "Ii;bF7", m68040up },
{"fsnegb", 4,	two(0xF000, 0x585A), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsnegd", 4,	two(0xF000, 0x005A), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fsnegd", 4,	two(0xF000, 0x005A), two(0xF1C0, 0xE07F), "IiFt",   cfloat },
{"fsnegd", 4,	two(0xF000, 0x545A), two(0xF1C0, 0xFC7F), "Ii;FF7", m68040up },
{"fsnegd", 4,	two(0xF000, 0x545A), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fsnegl", 4,	two(0xF000, 0x405A), two(0xF1C0, 0xFC7F), "Ii;lF7", m68040up },
{"fsnegl", 4,	two(0xF000, 0x405A), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsnegp", 4,	two(0xF000, 0x4C5A), two(0xF1C0, 0xFC7F), "Ii;pF7", m68040up },
{"fsnegs", 4,	two(0xF000, 0x445A), two(0xF1C0, 0xFC7F), "Ii;fF7", m68040up },
{"fsnegs", 4,	two(0xF000, 0x445A), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsnegw", 4,	two(0xF000, 0x505A), two(0xF1C0, 0xFC7F), "Ii;wF7", m68040up },
{"fsnegw", 4,	two(0xF000, 0x505A), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsnegx", 4,	two(0xF000, 0x005A), two(0xF1C0, 0xE07F), "IiF8F7", m68040up },
{"fsnegx", 4,	two(0xF000, 0x485A), two(0xF1C0, 0xFC7F), "Ii;xF7", m68040up },
{"fsnegx", 4,	two(0xF000, 0x005A), two(0xF1C0, 0xE07F), "IiFt",   m68040up },

{"fdnegb", 4,	two(0xF000, 0x585E), two(0xF1C0, 0xFC7F), "Ii;bF7", m68040up },
{"fdnegb", 4,	two(0xF000, 0x585E), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdnegd", 4,	two(0xF000, 0x005E), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fdnegd", 4,	two(0xF000, 0x005E), two(0xF1C0, 0xE07F), "IiFt",   cfloat },
{"fdnegd", 4,	two(0xF000, 0x545E), two(0xF1C0, 0xFC7F), "Ii;FF7", m68040up },
{"fdnegd", 4,	two(0xF000, 0x545E), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fdnegl", 4,	two(0xF000, 0x405E), two(0xF1C0, 0xFC7F), "Ii;lF7", m68040up },
{"fdnegl", 4,	two(0xF000, 0x405E), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdnegp", 4,	two(0xF000, 0x4C5E), two(0xF1C0, 0xFC7F), "Ii;pF7", m68040up },
{"fdnegs", 4,	two(0xF000, 0x445E), two(0xF1C0, 0xFC7F), "Ii;fF7", m68040up },
{"fdnegs", 4,	two(0xF000, 0x445E), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdnegw", 4,	two(0xF000, 0x505E), two(0xF1C0, 0xFC7F), "Ii;wF7", m68040up },
{"fdnegw", 4,	two(0xF000, 0x505E), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdnegx", 4,	two(0xF000, 0x005E), two(0xF1C0, 0xE07F), "IiF8F7", m68040up },
{"fdnegx", 4,	two(0xF000, 0x485E), two(0xF1C0, 0xFC7F), "Ii;xF7", m68040up },
{"fdnegx", 4,	two(0xF000, 0x005E), two(0xF1C0, 0xE07F), "IiFt",   m68040up },

{"fnop", 4,	two(0xF280, 0x0000), two(0xFFFF, 0xFFFF), "Ii", mfloat | cfloat },

{"fremb", 4,	two(0xF000, 0x5825), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fremd", 4,	two(0xF000, 0x5425), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"freml", 4,	two(0xF000, 0x4025), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fremp", 4,	two(0xF000, 0x4C25), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"frems", 4,	two(0xF000, 0x4425), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fremw", 4,	two(0xF000, 0x5025), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fremx", 4,	two(0xF000, 0x0025), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fremx", 4,	two(0xF000, 0x4825), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },

{"frestore", 2,	one(0xF140),		one(0xF1C0), "Id<s", mfloat },
{"frestore", 2,	one(0xF140),		one(0xF1C0), "Idys", cfloat },

{"fsave", 2,	one(0xF100),		one(0xF1C0), "Id>s", mfloat },
{"fsave", 2,	one(0xF100),		one(0xF1C0), "Idzs", cfloat },

{"fscaleb", 4,	two(0xF000, 0x5826), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fscaled", 4,	two(0xF000, 0x5426), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fscalel", 4,	two(0xF000, 0x4026), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fscalep", 4,	two(0xF000, 0x4C26), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fscales", 4,	two(0xF000, 0x4426), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fscalew", 4,	two(0xF000, 0x5026), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fscalex", 4,	two(0xF000, 0x0026), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fscalex", 4,	two(0xF000, 0x4826), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },

/* $ is necessary to prevent the assembler from using PC-relative.
   If @ were used, "label: fseq label" could produce "ftrapeq", 2,
   because "label" became "pc@label".  */
{"fseq", 4,	two(0xF040, 0x0001), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsf", 4,	two(0xF040, 0x0000), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsge", 4,	two(0xF040, 0x0013), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsgl", 4,	two(0xF040, 0x0016), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsgle", 4,	two(0xF040, 0x0017), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsgt", 4,	two(0xF040, 0x0012), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsle", 4,	two(0xF040, 0x0015), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fslt", 4,	two(0xF040, 0x0014), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsne", 4,	two(0xF040, 0x000E), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsnge", 4,	two(0xF040, 0x001C), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsngl", 4,	two(0xF040, 0x0019), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsngle", 4,	two(0xF040, 0x0018), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsngt", 4,	two(0xF040, 0x001D), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsnle", 4,	two(0xF040, 0x001A), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsnlt", 4,	two(0xF040, 0x001B), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsoge", 4,	two(0xF040, 0x0003), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsogl", 4,	two(0xF040, 0x0006), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsogt", 4,	two(0xF040, 0x0002), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsole", 4,	two(0xF040, 0x0005), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsolt", 4,	two(0xF040, 0x0004), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsor", 4,	two(0xF040, 0x0007), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsseq", 4,	two(0xF040, 0x0011), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fssf", 4,	two(0xF040, 0x0010), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fssne", 4,	two(0xF040, 0x001E), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsst", 4,	two(0xF040, 0x001F), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fst", 4,	two(0xF040, 0x000F), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsueq", 4,	two(0xF040, 0x0009), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsuge", 4,	two(0xF040, 0x000B), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsugt", 4,	two(0xF040, 0x000A), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsule", 4,	two(0xF040, 0x000D), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsult", 4,	two(0xF040, 0x000C), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },
{"fsun", 4,	two(0xF040, 0x0008), two(0xF1C0, 0xFFFF), "Ii$s", mfloat },

{"fsgldivb", 4,	two(0xF000, 0x5824), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fsgldivd", 4,	two(0xF000, 0x5424), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fsgldivl", 4,	two(0xF000, 0x4024), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fsgldivp", 4,	two(0xF000, 0x4C24), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fsgldivs", 4,	two(0xF000, 0x4424), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fsgldivw", 4,	two(0xF000, 0x5024), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fsgldivx", 4,	two(0xF000, 0x0024), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fsgldivx", 4,	two(0xF000, 0x4824), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"fsgldivx", 4,	two(0xF000, 0x0024), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"fsglmulb", 4,	two(0xF000, 0x5827), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fsglmuld", 4,	two(0xF000, 0x5427), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fsglmull", 4,	two(0xF000, 0x4027), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fsglmulp", 4,	two(0xF000, 0x4C27), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fsglmuls", 4,	two(0xF000, 0x4427), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fsglmulw", 4,	two(0xF000, 0x5027), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fsglmulx", 4,	two(0xF000, 0x0027), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fsglmulx", 4,	two(0xF000, 0x4827), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"fsglmulx", 4,	two(0xF000, 0x0027), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"fsinb", 4,	two(0xF000, 0x580E), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fsind", 4,	two(0xF000, 0x540E), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fsinl", 4,	two(0xF000, 0x400E), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fsinp", 4,	two(0xF000, 0x4C0E), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fsins", 4,	two(0xF000, 0x440E), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fsinw", 4,	two(0xF000, 0x500E), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fsinx", 4,	two(0xF000, 0x000E), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fsinx", 4,	two(0xF000, 0x480E), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"fsinx", 4,	two(0xF000, 0x000E), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"fsincosb", 4,	two(0xF000, 0x5830), two(0xF1C0, 0xFC78), "Ii;bF3F7", mfloat },
{"fsincosd", 4,	two(0xF000, 0x5430), two(0xF1C0, 0xFC78), "Ii;FF3F7", mfloat },
{"fsincosl", 4,	two(0xF000, 0x4030), two(0xF1C0, 0xFC78), "Ii;lF3F7", mfloat },
{"fsincosp", 4,	two(0xF000, 0x4C30), two(0xF1C0, 0xFC78), "Ii;pF3F7", mfloat },
{"fsincoss", 4,	two(0xF000, 0x4430), two(0xF1C0, 0xFC78), "Ii;fF3F7", mfloat },
{"fsincosw", 4,	two(0xF000, 0x5030), two(0xF1C0, 0xFC78), "Ii;wF3F7", mfloat },
{"fsincosx", 4,	two(0xF000, 0x0030), two(0xF1C0, 0xE078), "IiF8F3F7", mfloat },
{"fsincosx", 4,	two(0xF000, 0x4830), two(0xF1C0, 0xFC78), "Ii;xF3F7", mfloat },

{"fsinhb", 4,	two(0xF000, 0x5802), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fsinhd", 4,	two(0xF000, 0x5402), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fsinhl", 4,	two(0xF000, 0x4002), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fsinhp", 4,	two(0xF000, 0x4C02), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fsinhs", 4,	two(0xF000, 0x4402), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fsinhw", 4,	two(0xF000, 0x5002), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fsinhx", 4,	two(0xF000, 0x0002), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fsinhx", 4,	two(0xF000, 0x4802), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"fsinhx", 4,	two(0xF000, 0x0002), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"fsqrtb", 4,	two(0xF000, 0x5804), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fsqrtb", 4,	two(0xF000, 0x5804), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsqrtd", 4,	two(0xF000, 0x0004), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fsqrtd", 4,	two(0xF000, 0x0004), two(0xF1C0, 0xE07F), "IiFt",   cfloat },
{"fsqrtd", 4,	two(0xF000, 0x5404), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fsqrtd", 4,	two(0xF000, 0x5404), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fsqrtl", 4,	two(0xF000, 0x4004), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fsqrtl", 4,	two(0xF000, 0x4004), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsqrtp", 4,	two(0xF000, 0x4C04), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fsqrts", 4,	two(0xF000, 0x4404), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fsqrts", 4,	two(0xF000, 0x4404), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsqrtw", 4,	two(0xF000, 0x5004), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fsqrtw", 4,	two(0xF000, 0x5004), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsqrtx", 4,	two(0xF000, 0x0004), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fsqrtx", 4,	two(0xF000, 0x4804), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"fsqrtx", 4,	two(0xF000, 0x0004), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"fssqrtb", 4,	two(0xF000, 0x5841), two(0xF1C0, 0xFC7F), "Ii;bF7", m68040up },
{"fssqrtb", 4,	two(0xF000, 0x5841), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fssqrtd", 4,	two(0xF000, 0x0041), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fssqrtd", 4,	two(0xF000, 0x0041), two(0xF1C0, 0xE07F), "IiFt",   cfloat },
{"fssqrtd", 4,	two(0xF000, 0x5441), two(0xF1C0, 0xFC7F), "Ii;FF7", m68040up },
{"fssqrtd", 4,	two(0xF000, 0x5441), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fssqrtl", 4,	two(0xF000, 0x4041), two(0xF1C0, 0xFC7F), "Ii;lF7", m68040up },
{"fssqrtl", 4,	two(0xF000, 0x4041), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fssqrtp", 4,	two(0xF000, 0x4C41), two(0xF1C0, 0xFC7F), "Ii;pF7", m68040up },
{"fssqrts", 4,	two(0xF000, 0x4441), two(0xF1C0, 0xFC7F), "Ii;fF7", m68040up },
{"fssqrts", 4,	two(0xF000, 0x4441), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fssqrtw", 4,	two(0xF000, 0x5041), two(0xF1C0, 0xFC7F), "Ii;wF7", m68040up },
{"fssqrtw", 4,	two(0xF000, 0x5041), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fssqrtx", 4,	two(0xF000, 0x0041), two(0xF1C0, 0xE07F), "IiF8F7", m68040up },
{"fssqrtx", 4,	two(0xF000, 0x4841), two(0xF1C0, 0xFC7F), "Ii;xF7", m68040up },
{"fssqrtx", 4,	two(0xF000, 0x0041), two(0xF1C0, 0xE07F), "IiFt",   m68040up },

{"fdsqrtb", 4,	two(0xF000, 0x5845), two(0xF1C0, 0xFC7F), "Ii;bF7", m68040up },
{"fdsqrtb", 4,	two(0xF000, 0x5845), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdsqrtd", 4,	two(0xF000, 0x0045), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fdsqrtd", 4,	two(0xF000, 0x0045), two(0xF1C0, 0xE07F), "IiFt",   cfloat },
{"fdsqrtd", 4,	two(0xF000, 0x5445), two(0xF1C0, 0xFC7F), "Ii;FF7", m68040up },
{"fdsqrtl", 4,	two(0xF000, 0x4045), two(0xF1C0, 0xFC7F), "Ii;lF7", m68040up },
{"fdsqrtl", 4,	two(0xF000, 0x4045), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdsqrtp", 4,	two(0xF000, 0x4C45), two(0xF1C0, 0xFC7F), "Ii;pF7", m68040up },
{"fdsqrts", 4,	two(0xF000, 0x4445), two(0xF1C0, 0xFC7F), "Ii;fF7", m68040up },
{"fdsqrts", 4,	two(0xF000, 0x4445), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdsqrtw", 4,	two(0xF000, 0x5045), two(0xF1C0, 0xFC7F), "Ii;wF7", m68040up },
{"fdsqrtw", 4,	two(0xF000, 0x5045), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdsqrtx", 4,	two(0xF000, 0x0045), two(0xF1C0, 0xE07F), "IiF8F7", m68040up },
{"fdsqrtx", 4,	two(0xF000, 0x4845), two(0xF1C0, 0xFC7F), "Ii;xF7", m68040up },
{"fdsqrtx", 4,	two(0xF000, 0x0045), two(0xF1C0, 0xE07F), "IiFt",   m68040up },

{"fsubb", 4,	two(0xF000, 0x5828), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"fsubb", 4,	two(0xF000, 0x5828), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsubd", 4,	two(0xF000, 0x0028), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fsubd", 4,	two(0xF000, 0x5428), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"fsubd", 4,	two(0xF000, 0x5428), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fsubl", 4,	two(0xF000, 0x4028), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"fsubl", 4,	two(0xF000, 0x4028), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsubp", 4,	two(0xF000, 0x4C28), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"fsubs", 4,	two(0xF000, 0x4428), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"fsubs", 4,	two(0xF000, 0x4428), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsubw", 4,	two(0xF000, 0x5028), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"fsubw", 4,	two(0xF000, 0x5028), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fsubx", 4,	two(0xF000, 0x0028), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"fsubx", 4,	two(0xF000, 0x4828), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"fsubx", 4,	two(0xF000, 0x0028), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"fssubb", 4,	two(0xF000, 0x5828), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fssubb", 4,	two(0xF000, 0x5868), two(0xF1C0, 0xFC7F), "Ii;bF7", m68040up },
{"fssubd", 4,	two(0xF000, 0x0068), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fssubd", 4,	two(0xF000, 0x5468), two(0xF1C0, 0xFC7F), "Ii;FF7", m68040up },
{"fssubd", 4,	two(0xF000, 0x5468), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fssubl", 4,	two(0xF000, 0x4068), two(0xF1C0, 0xFC7F), "Ii;lF7", m68040up },
{"fssubl", 4,	two(0xF000, 0x4068), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fssubp", 4,	two(0xF000, 0x4C68), two(0xF1C0, 0xFC7F), "Ii;pF7", m68040up },
{"fssubs", 4,	two(0xF000, 0x4468), two(0xF1C0, 0xFC7F), "Ii;fF7", m68040up },
{"fssubs", 4,	two(0xF000, 0x4468), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fssubw", 4,	two(0xF000, 0x5068), two(0xF1C0, 0xFC7F), "Ii;wF7", m68040up },
{"fssubw", 4,	two(0xF000, 0x5068), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fssubx", 4,	two(0xF000, 0x0068), two(0xF1C0, 0xE07F), "IiF8F7", m68040up },
{"fssubx", 4,	two(0xF000, 0x4868), two(0xF1C0, 0xFC7F), "Ii;xF7", m68040up },
{"fssubx", 4,	two(0xF000, 0x0068), two(0xF1C0, 0xE07F), "IiFt",   m68040up },

{"fdsubb", 4,	two(0xF000, 0x586A), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdsubb", 4,	two(0xF000, 0x586c), two(0xF1C0, 0xFC7F), "Ii;bF7", m68040up },
{"fdsubd", 4,	two(0xF000, 0x006A), two(0xF1C0, 0xE07F), "IiF8F7", cfloat },
{"fdsubd", 4,	two(0xF000, 0x546A), two(0xF1C0, 0xFC7F), "IiwsF7", cfloat },
{"fdsubd", 4,	two(0xF000, 0x546c), two(0xF1C0, 0xFC7F), "Ii;FF7", m68040up },
{"fdsubl", 4,	two(0xF000, 0x406A), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdsubl", 4,	two(0xF000, 0x406c), two(0xF1C0, 0xFC7F), "Ii;lF7", m68040up },
{"fdsubp", 4,	two(0xF000, 0x4C6c), two(0xF1C0, 0xFC7F), "Ii;pF7", m68040up },
{"fdsubs", 4,	two(0xF000, 0x446A), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdsubs", 4,	two(0xF000, 0x446c), two(0xF1C0, 0xFC7F), "Ii;fF7", m68040up },
{"fdsubw", 4,	two(0xF000, 0x506A), two(0xF1C0, 0xFC7F), "IibsF7", cfloat },
{"fdsubw", 4,	two(0xF000, 0x506c), two(0xF1C0, 0xFC7F), "Ii;wF7", m68040up },
{"fdsubx", 4,	two(0xF000, 0x006c), two(0xF1C0, 0xE07F), "IiF8F7", m68040up },
{"fdsubx", 4,	two(0xF000, 0x486c), two(0xF1C0, 0xFC7F), "Ii;xF7", m68040up },
{"fdsubx", 4,	two(0xF000, 0x006c), two(0xF1C0, 0xE07F), "IiFt",   m68040up },

{"ftanb", 4,	two(0xF000, 0x580F), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"ftand", 4,	two(0xF000, 0x540F), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"ftanl", 4,	two(0xF000, 0x400F), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"ftanp", 4,	two(0xF000, 0x4C0F), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"ftans", 4,	two(0xF000, 0x440F), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"ftanw", 4,	two(0xF000, 0x500F), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"ftanx", 4,	two(0xF000, 0x000F), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"ftanx", 4,	two(0xF000, 0x480F), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"ftanx", 4,	two(0xF000, 0x000F), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"ftanhb", 4,	two(0xF000, 0x5809), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"ftanhd", 4,	two(0xF000, 0x5409), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"ftanhl", 4,	two(0xF000, 0x4009), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"ftanhp", 4,	two(0xF000, 0x4C09), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"ftanhs", 4,	two(0xF000, 0x4409), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"ftanhw", 4,	two(0xF000, 0x5009), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"ftanhx", 4,	two(0xF000, 0x0009), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"ftanhx", 4,	two(0xF000, 0x4809), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"ftanhx", 4,	two(0xF000, 0x0009), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"ftentoxb", 4,	two(0xF000, 0x5812), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"ftentoxd", 4,	two(0xF000, 0x5412), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"ftentoxl", 4,	two(0xF000, 0x4012), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"ftentoxp", 4,	two(0xF000, 0x4C12), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"ftentoxs", 4,	two(0xF000, 0x4412), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"ftentoxw", 4,	two(0xF000, 0x5012), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"ftentoxx", 4,	two(0xF000, 0x0012), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"ftentoxx", 4,	two(0xF000, 0x4812), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"ftentoxx", 4,	two(0xF000, 0x0012), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"ftrapeq", 4,	two(0xF07C, 0x0001), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapf", 4,	two(0xF07C, 0x0000), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapge", 4,	two(0xF07C, 0x0013), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapgl", 4,	two(0xF07C, 0x0016), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapgle", 4,	two(0xF07C, 0x0017), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapgt", 4,	two(0xF07C, 0x0012), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftraple", 4,	two(0xF07C, 0x0015), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftraplt", 4,	two(0xF07C, 0x0014), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapne", 4,	two(0xF07C, 0x000E), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapnge", 4,	two(0xF07C, 0x001C), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapngl", 4,	two(0xF07C, 0x0019), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapngle", 4,two(0xF07C, 0x0018), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapngt", 4,	two(0xF07C, 0x001D), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapnle", 4,	two(0xF07C, 0x001A), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapnlt", 4,	two(0xF07C, 0x001B), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapoge", 4,	two(0xF07C, 0x0003), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapogl", 4,	two(0xF07C, 0x0006), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapogt", 4,	two(0xF07C, 0x0002), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapole", 4,	two(0xF07C, 0x0005), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapolt", 4,	two(0xF07C, 0x0004), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapor", 4,	two(0xF07C, 0x0007), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapseq", 4,	two(0xF07C, 0x0011), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapsf", 4,	two(0xF07C, 0x0010), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapsne", 4,	two(0xF07C, 0x001E), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapst", 4,	two(0xF07C, 0x001F), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapt", 4,	two(0xF07C, 0x000F), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapueq", 4,	two(0xF07C, 0x0009), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapuge", 4,	two(0xF07C, 0x000B), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapugt", 4,	two(0xF07C, 0x000A), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapule", 4,	two(0xF07C, 0x000D), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapult", 4,	two(0xF07C, 0x000C), two(0xF1FF, 0xFFFF), "Ii", mfloat },
{"ftrapun", 4,	two(0xF07C, 0x0008), two(0xF1FF, 0xFFFF), "Ii", mfloat },

{"ftrapeqw", 4,	two(0xF07A, 0x0001), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapfw", 4,	two(0xF07A, 0x0000), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapgew", 4,	two(0xF07A, 0x0013), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapglw", 4,	two(0xF07A, 0x0016), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapglew", 4,two(0xF07A, 0x0017), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapgtw", 4,	two(0xF07A, 0x0012), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftraplew", 4,	two(0xF07A, 0x0015), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapltw", 4,	two(0xF07A, 0x0014), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapnew", 4,	two(0xF07A, 0x000E), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapngew", 4,two(0xF07A, 0x001C), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapnglw", 4,two(0xF07A, 0x0019), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapnglew", 4,two(0xF07A, 0x0018), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapngtw", 4,two(0xF07A, 0x001D), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapnlew", 4,two(0xF07A, 0x001A), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapnltw", 4,two(0xF07A, 0x001B), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapogew", 4,two(0xF07A, 0x0003), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapoglw", 4,two(0xF07A, 0x0006), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapogtw", 4,two(0xF07A, 0x0002), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapolew", 4,two(0xF07A, 0x0005), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapoltw", 4,two(0xF07A, 0x0004), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftraporw", 4,	two(0xF07A, 0x0007), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapseqw", 4,two(0xF07A, 0x0011), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapsfw", 4,	two(0xF07A, 0x0010), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapsnew", 4,two(0xF07A, 0x001E), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapstw", 4,	two(0xF07A, 0x001F), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftraptw", 4,	two(0xF07A, 0x000F), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapueqw", 4,two(0xF07A, 0x0009), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapugew", 4,two(0xF07A, 0x000B), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapugtw", 4,two(0xF07A, 0x000A), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapulew", 4,two(0xF07A, 0x000D), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapultw", 4,two(0xF07A, 0x000C), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },
{"ftrapunw", 4,	two(0xF07A, 0x0008), two(0xF1FF, 0xFFFF), "Ii^w", mfloat },

{"ftrapeql", 4,	two(0xF07B, 0x0001), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapfl", 4,	two(0xF07B, 0x0000), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapgel", 4,	two(0xF07B, 0x0013), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapgll", 4,	two(0xF07B, 0x0016), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapglel", 4,two(0xF07B, 0x0017), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapgtl", 4,	two(0xF07B, 0x0012), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftraplel", 4,	two(0xF07B, 0x0015), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapltl", 4,	two(0xF07B, 0x0014), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapnel", 4,	two(0xF07B, 0x000E), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapngel", 4,two(0xF07B, 0x001C), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapngll", 4,two(0xF07B, 0x0019), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapnglel", 4,two(0xF07B, 0x0018), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapngtl", 4,two(0xF07B, 0x001D), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapnlel", 4,two(0xF07B, 0x001A), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapnltl", 4,two(0xF07B, 0x001B), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapogel", 4,two(0xF07B, 0x0003), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapogll", 4,two(0xF07B, 0x0006), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapogtl", 4,two(0xF07B, 0x0002), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapolel", 4,two(0xF07B, 0x0005), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapoltl", 4,two(0xF07B, 0x0004), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftraporl", 4,	two(0xF07B, 0x0007), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapseql", 4,two(0xF07B, 0x0011), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapsfl", 4,	two(0xF07B, 0x0010), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapsnel", 4,two(0xF07B, 0x001E), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapstl", 4,	two(0xF07B, 0x001F), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftraptl", 4,	two(0xF07B, 0x000F), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapueql", 4,two(0xF07B, 0x0009), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapugel", 4,two(0xF07B, 0x000B), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapugtl", 4,two(0xF07B, 0x000A), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapulel", 4,two(0xF07B, 0x000D), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapultl", 4,two(0xF07B, 0x000C), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },
{"ftrapunl", 4,	two(0xF07B, 0x0008), two(0xF1FF, 0xFFFF), "Ii^l", mfloat },

{"ftstb", 4,	two(0xF000, 0x583A), two(0xF1C0, 0xFC7F), "Ii;b", mfloat },
{"ftstb", 4,	two(0xF000, 0x583A), two(0xF1C0, 0xFC7F), "Iibs", cfloat },
{"ftstd", 4,	two(0xF000, 0x003A), two(0xF1C0, 0xE07F), "IiF8", cfloat },
{"ftstd", 4,	two(0xF000, 0x543A), two(0xF1C0, 0xFC7F), "Ii;F", mfloat },
{"ftstd", 4,	two(0xF000, 0x543A), two(0xF1C0, 0xFC7F), "Iibs", cfloat },
{"ftstl", 4,	two(0xF000, 0x403A), two(0xF1C0, 0xFC7F), "Ii;l", mfloat },
{"ftstl", 4,	two(0xF000, 0x403A), two(0xF1C0, 0xFC7F), "Iibs", cfloat },
{"ftstp", 4,	two(0xF000, 0x4C3A), two(0xF1C0, 0xFC7F), "Ii;p", mfloat },
{"ftsts", 4,	two(0xF000, 0x443A), two(0xF1C0, 0xFC7F), "Ii;f", mfloat },
{"ftsts", 4,	two(0xF000, 0x443A), two(0xF1C0, 0xFC7F), "Iibs", cfloat },
{"ftstw", 4,	two(0xF000, 0x503A), two(0xF1C0, 0xFC7F), "Ii;w", mfloat },
{"ftstw", 4,	two(0xF000, 0x503A), two(0xF1C0, 0xFC7F), "Iibs", cfloat },
{"ftstx", 4,	two(0xF000, 0x003A), two(0xF1C0, 0xE07F), "IiF8", mfloat },
{"ftstx", 4,	two(0xF000, 0x483A), two(0xF1C0, 0xFC7F), "Ii;x", mfloat },

{"ftwotoxb", 4,	two(0xF000, 0x5811), two(0xF1C0, 0xFC7F), "Ii;bF7", mfloat },
{"ftwotoxd", 4,	two(0xF000, 0x5411), two(0xF1C0, 0xFC7F), "Ii;FF7", mfloat },
{"ftwotoxl", 4,	two(0xF000, 0x4011), two(0xF1C0, 0xFC7F), "Ii;lF7", mfloat },
{"ftwotoxp", 4,	two(0xF000, 0x4C11), two(0xF1C0, 0xFC7F), "Ii;pF7", mfloat },
{"ftwotoxs", 4,	two(0xF000, 0x4411), two(0xF1C0, 0xFC7F), "Ii;fF7", mfloat },
{"ftwotoxw", 4,	two(0xF000, 0x5011), two(0xF1C0, 0xFC7F), "Ii;wF7", mfloat },
{"ftwotoxx", 4,	two(0xF000, 0x0011), two(0xF1C0, 0xE07F), "IiF8F7", mfloat },
{"ftwotoxx", 4,	two(0xF000, 0x4811), two(0xF1C0, 0xFC7F), "Ii;xF7", mfloat },
{"ftwotoxx", 4,	two(0xF000, 0x0011), two(0xF1C0, 0xE07F), "IiFt",   mfloat },

{"halt", 2,	one(0045310),	one(0177777), "",     m68060 | mcfisa_a },

{"illegal", 2,	one(0045374),	one(0177777), "",     m68000up | mcfisa_a },
{"intouch", 2,	one(0xf428),	one(0xfff8), "As",    mcfisa_b },

{"jmp", 2,	one(0047300),	one(0177700), "!s", m68000up | mcfisa_a },

{"jra", 2,	one(0060000),	one(0177400), "Bg", m68000up | mcfisa_a },
{"jra", 2,	one(0047300),	one(0177700), "!s", m68000up | mcfisa_a },

{"jsr", 2,	one(0047200),	one(0177700), "!s", m68000up | mcfisa_a },

{"jbsr", 2,	one(0060400),	one(0177400), "Bg", m68000up | mcfisa_a },
{"jbsr", 2,	one(0047200),	one(0177700), "!s", m68000up | mcfisa_a },

{"lea", 2,	one(0040700),	one(0170700), "!sAd", m68000up | mcfisa_a },

{"lpstop", 6,	two(0174000,0000700),two(0177777,0177777),"#w", cpu32|m68060 },

{"linkw", 4,	one(0047120),	one(0177770), "As#w", m68000up | mcfisa_a },
{"linkl", 6,	one(0044010),	one(0177770), "As#l", m68020up | cpu32 },
{"link", 4,	one(0047120),	one(0177770), "As#W", m68000up | mcfisa_a },
{"link", 6,	one(0044010),	one(0177770), "As#l", m68020up | cpu32 },

{"lslb", 2,	one(0160410),	one(0170770), "QdDs", m68000up },
{"lslb", 2,	one(0160450),	one(0170770), "DdDs", m68000up },
{"lslw", 2,	one(0160510),	one(0170770), "QdDs", m68000up },
{"lslw", 2,	one(0160550),	one(0170770), "DdDs", m68000up },
{"lslw", 2,	one(0161700),	one(0177700), "~s",   m68000up },
{"lsll", 2,	one(0160610),	one(0170770), "QdDs", m68000up | mcfisa_a },
{"lsll", 2,	one(0160650),	one(0170770), "DdDs", m68000up | mcfisa_a },

{"lsrb", 2,	one(0160010),	one(0170770), "QdDs", m68000up },
{"lsrb", 2,	one(0160050),	one(0170770), "DdDs", m68000up },
{"lsrw", 2,	one(0160110),	one(0170770), "QdDs", m68000up },
{"lsrw", 2,	one(0160150),	one(0170770), "DdDs", m68000up },
{"lsrw", 2,	one(0161300),	one(0177700), "~s",   m68000up },
{"lsrl", 2,	one(0160210),	one(0170770), "QdDs", m68000up | mcfisa_a },
{"lsrl", 2,	one(0160250),	one(0170770), "DdDs", m68000up | mcfisa_a },

{"macw", 4,  	two(0xa080, 0x0000), two(0xf180, 0x0910), "uNuoiI4/Rn", mcfmac },
{"macw", 4,  	two(0xa080, 0x0200), two(0xf180, 0x0910), "uNuoMh4/Rn", mcfmac },
{"macw", 4,  	two(0xa080, 0x0000), two(0xf180, 0x0f10), "uNuo4/Rn", mcfmac },
{"macw", 4,  	two(0xa000, 0x0000), two(0xf1b0, 0x0900), "uMumiI", mcfmac },
{"macw", 4,  	two(0xa000, 0x0200), two(0xf1b0, 0x0900), "uMumMh", mcfmac },
{"macw", 4,  	two(0xa000, 0x0000), two(0xf1b0, 0x0f00), "uMum", mcfmac },

{"macw", 4,  	two(0xa000, 0x0000), two(0xf100, 0x0900), "uNuoiI4/RneG", mcfemac },/* Ry,Rx,SF,<ea>,accX.  */
{"macw", 4,  	two(0xa000, 0x0200), two(0xf100, 0x0900), "uNuoMh4/RneG", mcfemac },/* Ry,Rx,+1/-1,<ea>,accX.  */
{"macw", 4,  	two(0xa000, 0x0000), two(0xf100, 0x0f00), "uNuo4/RneG", mcfemac },/* Ry,Rx,<ea>,accX.  */
{"macw", 4,  	two(0xa000, 0x0000), two(0xf130, 0x0900), "uMumiIeH", mcfemac },/* Ry,Rx,SF,accX.  */
{"macw", 4,  	two(0xa000, 0x0200), two(0xf130, 0x0900), "uMumMheH", mcfemac },/* Ry,Rx,+1/-1,accX.  */
{"macw", 4,  	two(0xa000, 0x0000), two(0xf130, 0x0f00), "uMumeH", mcfemac }, /* Ry,Rx,accX.  */

{"macl", 4,  	two(0xa080, 0x0800), two(0xf180, 0x0910), "RNRoiI4/Rn", mcfmac },
{"macl", 4,  	two(0xa080, 0x0a00), two(0xf180, 0x0910), "RNRoMh4/Rn", mcfmac },
{"macl", 4,  	two(0xa080, 0x0800), two(0xf180, 0x0f10), "RNRo4/Rn", mcfmac },
{"macl", 4,  	two(0xa000, 0x0800), two(0xf1b0, 0x0b00), "RMRmiI", mcfmac },
{"macl", 4,  	two(0xa000, 0x0a00), two(0xf1b0, 0x0b00), "RMRmMh", mcfmac },
{"macl", 4,  	two(0xa000, 0x0800), two(0xf1b0, 0x0800), "RMRm", mcfmac },

{"macl", 4,  	two(0xa000, 0x0800), two(0xf100, 0x0900), "R3R1iI4/RneG", mcfemac },
{"macl", 4,  	two(0xa000, 0x0a00), two(0xf100, 0x0900), "R3R1Mh4/RneG", mcfemac },
{"macl", 4,  	two(0xa000, 0x0800), two(0xf100, 0x0f00), "R3R14/RneG", mcfemac },
{"macl", 4,  	two(0xa000, 0x0800), two(0xf130, 0x0900), "RMRmiIeH", mcfemac },
{"macl", 4,  	two(0xa000, 0x0a00), two(0xf130, 0x0900), "RMRmMheH", mcfemac },
{"macl", 4,  	two(0xa000, 0x0800), two(0xf130, 0x0f00), "RMRmeH", mcfemac },

/* NOTE: The mcf5200 family programmer's reference manual does not
   indicate the byte form of the movea instruction is invalid (as it
   is on 68000 family cpus).  However, experiments on the 5202 yield
   unexpected results.  The value is copied, but it is not sign extended
   (as is done with movea.w) and the top three bytes in the address
   register are not disturbed.  I don't know if this is the intended
   behavior --- it could be a hole in instruction decoding (Motorola
   decided not to trap all invalid instructions for performance reasons)
   --- but I suspect that it is not.

   I reported this to Motorola ISD Technical Communications Support,
   which replied that other coldfire assemblers reject movea.b.  For
   this reason I've decided to not allow moveab.

	jtc@cygnus.com - 97/01/24.  */

{"moveal", 2,	one(0020100),	one(0170700), "*lAd", m68000up | mcfisa_a },
{"moveaw", 2,	one(0030100),	one(0170700), "*wAd", m68000up | mcfisa_a },

{"movclrl", 2,	one(0xA1C0),	one(0xf9f0), "eFRs", mcfemac },

{"movec", 4,	one(0047173),	one(0177777), "R1Jj", m68010up | mcfisa_a },
{"movec", 4,	one(0047173),	one(0177777), "R1#j", m68010up | mcfisa_a },
{"movec", 4,	one(0047172),	one(0177777), "JjR1", m68010up },
{"movec", 4,	one(0047172),	one(0177777), "#jR1", m68010up },

{"movemw", 4,	one(0044200),	one(0177700), "Lw&s", m68000up },
{"movemw", 4,	one(0044240),	one(0177770), "lw-s", m68000up },
{"movemw", 4,	one(0044200),	one(0177700), "#w>s", m68000up },
{"movemw", 4,	one(0046200),	one(0177700), "<sLw", m68000up },
{"movemw", 4,	one(0046200),	one(0177700), "<s#w", m68000up },
{"moveml", 4,	one(0044300),	one(0177700), "Lw&s", m68000up },
{"moveml", 4,	one(0044340),	one(0177770), "lw-s", m68000up },
{"moveml", 4,	one(0044300),	one(0177700), "#w>s", m68000up },
{"moveml", 4,	one(0046300),	one(0177700), "<sLw", m68000up },
{"moveml", 4,	one(0046300),	one(0177700), "<s#w", m68000up },
/* FIXME: need specifier for mode 2 and 5 to simplify below insn patterns.  */
{"moveml", 4,	one(0044320),	one(0177770), "Lwas", mcfisa_a },
{"moveml", 4,	one(0044320),	one(0177770), "#was", mcfisa_a },
{"moveml", 4,	one(0044350),	one(0177770), "Lwds", mcfisa_a },
{"moveml", 4,	one(0044350),	one(0177770), "#wds", mcfisa_a },
{"moveml", 4,	one(0046320),	one(0177770), "asLw", mcfisa_a },
{"moveml", 4,	one(0046320),	one(0177770), "as#w", mcfisa_a },
{"moveml", 4,	one(0046350),	one(0177770), "dsLw", mcfisa_a },
{"moveml", 4,	one(0046350),	one(0177770), "ds#w", mcfisa_a },

{"movepw", 2,	one(0000410),	one(0170770), "dsDd", m68000up },
{"movepw", 2,	one(0000610),	one(0170770), "Ddds", m68000up },
{"movepl", 2,	one(0000510),	one(0170770), "dsDd", m68000up },
{"movepl", 2,	one(0000710),	one(0170770), "Ddds", m68000up },

{"moveq", 2,	one(0070000),	one(0170400), "MsDd", m68000up | mcfisa_a },
{"moveq", 2,	one(0070000),	one(0170400), "#BDd", m68000up | mcfisa_a },

/* The move opcode can generate the movea and moveq instructions.  */
{"moveb", 2,	one(0010000),	one(0170000), ";b$d", m68000up },
{"moveb", 2,	one(0010000),	one(0170070), "Ds$d", mcfisa_a },
{"moveb", 2,	one(0010020),	one(0170070), "as$d", mcfisa_a },
{"moveb", 2,	one(0010030),	one(0170070), "+s$d", mcfisa_a },
{"moveb", 2,	one(0010040),	one(0170070), "-s$d", mcfisa_a },
{"moveb", 2,	one(0010000),	one(0170000), "nsqd", mcfisa_a },
{"moveb", 2,	one(0010000),	one(0170700), "obDd", mcfisa_a },
{"moveb", 2,	one(0010200),	one(0170700), "obad", mcfisa_a },
{"moveb", 2,	one(0010300),	one(0170700), "ob+d", mcfisa_a },
{"moveb", 2,	one(0010400),	one(0170700), "ob-d", mcfisa_a },
{"moveb", 2,	one(0010000),	one(0170000), "obnd", mcfisa_b },

{"movew", 2,	one(0030000),	one(0170000), "*w%d", m68000up },
{"movew", 2,	one(0030000),	one(0170000), "ms%d", mcfisa_a },
{"movew", 2,	one(0030000),	one(0170000), "nspd", mcfisa_a },
{"movew", 2,	one(0030000),	one(0170000), "owmd", mcfisa_a },
{"movew", 2,	one(0030000),	one(0170000), "ownd", mcfisa_b },
{"movew", 2,	one(0040300),	one(0177700), "Ss$s", m68000up },
{"movew", 2,	one(0040300),	one(0177770), "SsDs", mcfisa_a },
{"movew", 2,	one(0041300),	one(0177700), "Cs$s", m68010up },
{"movew", 2,	one(0041300),	one(0177770), "CsDs", mcfisa_a },
{"movew", 2,	one(0042300),	one(0177700), ";wCd", m68000up },
{"movew", 2,	one(0042300),	one(0177700), "DsCd", mcfisa_a },
{"movew", 4,	one(0042374),	one(0177777), "#wCd", mcfisa_a },
{"movew", 2,	one(0043300),	one(0177700), ";wSd", m68000up },
{"movew", 2,	one(0043300),	one(0177700), "DsSd", mcfisa_a },
{"movew", 4,	one(0043374),	one(0177777), "#wSd", mcfisa_a },

{"movel", 2,	one(0070000),	one(0170400), "MsDd", m68000up | mcfisa_a },
{"movel", 2,	one(0020000),	one(0170000), "*l%d", m68000up },
{"movel", 2,	one(0020000),	one(0170000), "ms%d", mcfisa_a },
{"movel", 2,	one(0020000),	one(0170000), "nspd", mcfisa_a },
{"movel", 2,	one(0020000),	one(0170000), "olmd", mcfisa_a },
{"movel", 2,	one(0020000),	one(0170000), "olnd", mcfisa_b },
{"movel", 2,	one(0047140),	one(0177770), "AsUd", m68000up | mcfusp },
{"movel", 2,	one(0047150),	one(0177770), "UdAs", m68000up | mcfusp },
{"movel", 2,	one(0120600),	one(0177760), "EsRs", mcfmac },
{"movel", 2,	one(0120400),	one(0177760), "RsEs", mcfmac },
{"movel", 6,	one(0120474),	one(0177777), "#lEs", mcfmac },
{"movel", 2,	one(0124600),	one(0177760), "GsRs", mcfmac },
{"movel", 2,	one(0124400),	one(0177760), "RsGs", mcfmac },
{"movel", 6,	one(0124474),	one(0177777), "#lGs", mcfmac },
{"movel", 2,	one(0126600),	one(0177760), "HsRs", mcfmac },
{"movel", 2,	one(0126400),	one(0177760), "RsHs", mcfmac },
{"movel", 6,	one(0126474),	one(0177777), "#lHs", mcfmac },
{"movel", 2,	one(0124700),	one(0177777), "GsCs", mcfmac },

{"movel", 2,	one(0xa180),	one(0xf9f0), "eFRs", mcfemac }, /* ACCx,Rx.  */
{"movel", 2,	one(0xab80),	one(0xfbf0), "g]Rs", mcfemac }, /* ACCEXTx,Rx.  */
{"movel", 2,	one(0xa980),	one(0xfff0), "G-Rs", mcfemac }, /* macsr,Rx.  */
{"movel", 2,	one(0xad80),	one(0xfff0), "H-Rs", mcfemac }, /* mask,Rx.  */
{"movel", 2,	one(0xa110),	one(0xf9fc), "efeF", mcfemac }, /* ACCy,ACCx.  */
{"movel", 2,	one(0xa9c0),	one(0xffff), "G-C-", mcfemac }, /* macsr,ccr.  */
{"movel", 2,	one(0xa100),	one(0xf9f0), "RseF", mcfemac }, /* Rx,ACCx.  */
{"movel", 6,	one(0xa13c),	one(0xf9ff), "#leF", mcfemac }, /* #,ACCx.  */
{"movel", 2,	one(0xab00),	one(0xfbc0), "Rsg]", mcfemac }, /* Rx,ACCEXTx.  */
{"movel", 6,	one(0xab3c),	one(0xfbff), "#lg]", mcfemac }, /* #,ACCEXTx.  */
{"movel", 2,	one(0xa900),	one(0xffc0), "RsG-", mcfemac }, /* Rx,macsr.  */
{"movel", 6,	one(0xa93c),	one(0xffff), "#lG-", mcfemac }, /* #,macsr.  */
{"movel", 2,	one(0xad00),	one(0xffc0), "RsH-", mcfemac }, /* Rx,mask.  */
{"movel", 6,	one(0xad3c),	one(0xffff), "#lH-", mcfemac }, /* #,mask.  */

{"move", 2,	one(0030000),	one(0170000), "*w%d", m68000up },
{"move", 2,	one(0030000),	one(0170000), "ms%d", mcfisa_a },
{"move", 2,	one(0030000),	one(0170000), "nspd", mcfisa_a },
{"move", 2,	one(0030000),	one(0170000), "owmd", mcfisa_a },
{"move", 2,	one(0030000),	one(0170000), "ownd", mcfisa_b },
{"move", 2,	one(0040300),	one(0177700), "Ss$s", m68000up },
{"move", 2,	one(0040300),	one(0177770), "SsDs", mcfisa_a },
{"move", 2,	one(0041300),	one(0177700), "Cs$s", m68010up },
{"move", 2,	one(0041300),	one(0177770), "CsDs", mcfisa_a },
{"move", 2,	one(0042300),	one(0177700), ";wCd", m68000up },
{"move", 2,	one(0042300),	one(0177700), "DsCd", mcfisa_a },
{"move", 4,	one(0042374),	one(0177777), "#wCd", mcfisa_a },
{"move", 2,	one(0043300),	one(0177700), ";wSd", m68000up },
{"move", 2,	one(0043300),	one(0177700), "DsSd", mcfisa_a },
{"move", 4,	one(0043374),	one(0177777), "#wSd", mcfisa_a },

{"move", 2,	one(0047140),	one(0177770), "AsUd", m68000up },
{"move", 2,	one(0047150),	one(0177770), "UdAs", m68000up },

{"mov3ql", 2,	one(0120500),	one(0170700), "xd%s", mcfisa_b },
{"mvsb", 2,	one(0070400),	one(0170700), "*bDd", mcfisa_b },
{"mvsw", 2,	one(0070500),	one(0170700), "*wDd", mcfisa_b },
{"mvzb", 2,	one(0070600),	one(0170700), "*bDd", mcfisa_b },
{"mvzw", 2,	one(0070700),	one(0170700), "*wDd", mcfisa_b },

{"movesb", 4,	two(0007000, 0),     two(0177700, 07777), "~sR1", m68010up },
{"movesb", 4,	two(0007000, 04000), two(0177700, 07777), "R1~s", m68010up },
{"movesw", 4,	two(0007100, 0),     two(0177700, 07777), "~sR1", m68010up },
{"movesw", 4,	two(0007100, 04000), two(0177700, 07777), "R1~s", m68010up },
{"movesl", 4,	two(0007200, 0),     two(0177700, 07777), "~sR1", m68010up },
{"movesl", 4,	two(0007200, 04000), two(0177700, 07777), "R1~s", m68010up },

{"move16", 4,	two(0xf620, 0x8000), two(0xfff8, 0x8fff), "+s+1", m68040up },
{"move16", 2,	one(0xf600),		one(0xfff8), "+s_L", m68040up },
{"move16", 2,	one(0xf608),		one(0xfff8), "_L+s", m68040up },
{"move16", 2,	one(0xf610),		one(0xfff8), "as_L", m68040up },
{"move16", 2,	one(0xf618),		one(0xfff8), "_Las", m68040up },

{"msacw", 4,  	two(0xa080, 0x0100), two(0xf180, 0x0910), "uNuoiI4/Rn", mcfmac },
{"msacw", 4,  	two(0xa080, 0x0300), two(0xf180, 0x0910), "uNuoMh4/Rn", mcfmac },
{"msacw", 4,  	two(0xa080, 0x0100), two(0xf180, 0x0f10), "uNuo4/Rn", mcfmac },
{"msacw", 4,  	two(0xa000, 0x0100), two(0xf1b0, 0x0900), "uMumiI", mcfmac },
{"msacw", 4,  	two(0xa000, 0x0300), two(0xf1b0, 0x0900), "uMumMh", mcfmac },
{"msacw", 4,  	two(0xa000, 0x0100), two(0xf1b0, 0x0f00), "uMum", mcfmac },

{"msacw", 4,  	two(0xa000, 0x0100), two(0xf100, 0x0900), "uMumiI4/RneG", mcfemac },/* Ry,Rx,SF,<ea>,accX.  */
{"msacw", 4,  	two(0xa000, 0x0300), two(0xf100, 0x0900), "uMumMh4/RneG", mcfemac },/* Ry,Rx,+1/-1,<ea>,accX.  */
{"msacw", 4,  	two(0xa000, 0x0100), two(0xf100, 0x0f00), "uMum4/RneG", mcfemac },/* Ry,Rx,<ea>,accX.  */
{"msacw", 4,  	two(0xa000, 0x0100), two(0xf130, 0x0900), "uMumiIeH", mcfemac },/* Ry,Rx,SF,accX.  */
{"msacw", 4,  	two(0xa000, 0x0300), two(0xf130, 0x0900), "uMumMheH", mcfemac },/* Ry,Rx,+1/-1,accX.  */
{"msacw", 4,  	two(0xa000, 0x0100), two(0xf130, 0x0f00), "uMumeH", mcfemac }, /* Ry,Rx,accX.  */

{"msacl", 4,  	two(0xa080, 0x0900), two(0xf180, 0x0910), "RNRoiI4/Rn", mcfmac },
{"msacl", 4,  	two(0xa080, 0x0b00), two(0xf180, 0x0910), "RNRoMh4/Rn", mcfmac },
{"msacl", 4,  	two(0xa080, 0x0900), two(0xf180, 0x0f10), "RNRo4/Rn", mcfmac },
{"msacl", 4,  	two(0xa000, 0x0900), two(0xf1b0, 0x0b00), "RMRmiI", mcfmac },
{"msacl", 4,  	two(0xa000, 0x0b00), two(0xf1b0, 0x0b00), "RMRmMh", mcfmac },
{"msacl", 4,  	two(0xa000, 0x0900), two(0xf1b0, 0x0800), "RMRm", mcfmac },

{"msacl", 4,  	two(0xa000, 0x0900), two(0xf100, 0x0900), "R3R1iI4/RneG", mcfemac },
{"msacl", 4,  	two(0xa000, 0x0b00), two(0xf100, 0x0900), "R3R1Mh4/RneG", mcfemac },
{"msacl", 4,  	two(0xa000, 0x0900), two(0xf100, 0x0f00), "R3R14/RneG", mcfemac },
{"msacl", 4,  	two(0xa000, 0x0900), two(0xf130, 0x0900), "RMRmiIeH", mcfemac },
{"msacl", 4,  	two(0xa000, 0x0b00), two(0xf130, 0x0900), "RMRmMheH", mcfemac },
{"msacl", 4,  	two(0xa000, 0x0900), two(0xf130, 0x0f00), "RMRmeH", mcfemac },

{"mulsw", 2,	one(0140700),		one(0170700), ";wDd", m68000up|mcfisa_a },
{"mulsl", 4,	two(0046000,004000), two(0177700,0107770), ";lD1", m68020up|cpu32 },
{"mulsl", 4,	two(0046000,004000), two(0177700,0107770), "qsD1", mcfisa_a },
{"mulsl", 4,	two(0046000,006000), two(0177700,0107770), ";lD3D1",m68020up|cpu32 },

{"muluw", 2,	one(0140300),		one(0170700), ";wDd", m68000up|mcfisa_a },
{"mulul", 4,	two(0046000,000000), two(0177700,0107770), ";lD1", m68020up|cpu32 },
{"mulul", 4,	two(0046000,000000), two(0177700,0107770), "qsD1", mcfisa_a },
{"mulul", 4,	two(0046000,002000), two(0177700,0107770), ";lD3D1",m68020up|cpu32 },

{"nbcd", 2,	one(0044000),	one(0177700), "$s", m68000up },

{"negb", 2,	one(0042000),	one(0177700), "$s", m68000up },
{"negw", 2,	one(0042100),	one(0177700), "$s", m68000up },
{"negl", 2,	one(0042200),	one(0177700), "$s", m68000up },
{"negl", 2,	one(0042200),	one(0177700), "Ds", mcfisa_a},

{"negxb", 2,	one(0040000),	one(0177700), "$s", m68000up },
{"negxw", 2,	one(0040100),	one(0177700), "$s", m68000up },
{"negxl", 2,	one(0040200),	one(0177700), "$s", m68000up },
{"negxl", 2,	one(0040200),	one(0177700), "Ds", mcfisa_a},

{"nop", 2,	one(0047161),	one(0177777), "", m68000up | mcfisa_a},

{"notb", 2,	one(0043000),	one(0177700), "$s", m68000up },
{"notw", 2,	one(0043100),	one(0177700), "$s", m68000up },
{"notl", 2,	one(0043200),	one(0177700), "$s", m68000up },
{"notl", 2,	one(0043200),	one(0177700), "Ds", mcfisa_a},

{"orib", 4,	one(0000000),	one(0177700), "#b$s", m68000up },
{"orib", 4,	one(0000074),	one(0177777), "#bCs", m68000up },
{"oriw", 4,	one(0000100),	one(0177700), "#w$s", m68000up },
{"oriw", 4,	one(0000174),	one(0177777), "#wSs", m68000up },
{"oril", 6,	one(0000200),	one(0177700), "#l$s", m68000up },
{"oril", 6,	one(0000200),	one(0177700), "#lDs", mcfisa_a },
{"ori", 4,	one(0000074),	one(0177777), "#bCs", m68000up },
{"ori", 4,	one(0000100),	one(0177700), "#w$s", m68000up },
{"ori", 4,	one(0000174),	one(0177777), "#wSs", m68000up },

/* The or opcode can generate the ori instruction.  */
{"orb", 4,	one(0000000),	one(0177700), "#b$s", m68000up },
{"orb", 4,	one(0000074),	one(0177777), "#bCs", m68000up },
{"orb", 2,	one(0100000),	one(0170700), ";bDd", m68000up },
{"orb", 2,	one(0100400),	one(0170700), "Dd~s", m68000up },
{"orw", 4,	one(0000100),	one(0177700), "#w$s", m68000up },
{"orw", 4,	one(0000174),	one(0177777), "#wSs", m68000up },
{"orw", 2,	one(0100100),	one(0170700), ";wDd", m68000up },
{"orw", 2,	one(0100500),	one(0170700), "Dd~s", m68000up },
{"orl", 6,	one(0000200),	one(0177700), "#l$s", m68000up },
{"orl", 6,	one(0000200),	one(0177700), "#lDs", mcfisa_a },
{"orl", 2,	one(0100200),	one(0170700), ";lDd", m68000up | mcfisa_a },
{"orl", 2,	one(0100600),	one(0170700), "Dd~s", m68000up | mcfisa_a },
{"or", 4,	one(0000074),	one(0177777), "#bCs", m68000up },
{"or", 4,	one(0000100),	one(0177700), "#w$s", m68000up },
{"or", 4,	one(0000174),	one(0177777), "#wSs", m68000up },
{"or", 2,	one(0100100),	one(0170700), ";wDd", m68000up },
{"or", 2,	one(0100500),	one(0170700), "Dd~s", m68000up },

{"pack", 4,	one(0100500),	one(0170770), "DsDd#w", m68020up },
{"pack", 4,	one(0100510),	one(0170770), "-s-d#w", m68020up },

{"pbac", 2,	one(0xf087),	one(0xffbf), "Bc", m68851 },
{"pbacw", 2,	one(0xf087),	one(0xffff), "BW", m68851 },
{"pbas", 2,	one(0xf086),	one(0xffbf), "Bc", m68851 },
{"pbasw", 2,	one(0xf086),	one(0xffff), "BW", m68851 },
{"pbbc", 2,	one(0xf081),	one(0xffbf), "Bc", m68851 },
{"pbbcw", 2,	one(0xf081),	one(0xffff), "BW", m68851 },
{"pbbs", 2,	one(0xf080),	one(0xffbf), "Bc", m68851 },
{"pbbsw", 2,	one(0xf080),	one(0xffff), "BW", m68851 },
{"pbcc", 2,	one(0xf08f),	one(0xffbf), "Bc", m68851 },
{"pbccw", 2,	one(0xf08f),	one(0xffff), "BW", m68851 },
{"pbcs", 2,	one(0xf08e),	one(0xffbf), "Bc", m68851 },
{"pbcsw", 2,	one(0xf08e),	one(0xffff), "BW", m68851 },
{"pbgc", 2,	one(0xf08d),	one(0xffbf), "Bc", m68851 },
{"pbgcw", 2,	one(0xf08d),	one(0xffff), "BW", m68851 },
{"pbgs", 2,	one(0xf08c),	one(0xffbf), "Bc", m68851 },
{"pbgsw", 2,	one(0xf08c),	one(0xffff), "BW", m68851 },
{"pbic", 2,	one(0xf08b),	one(0xffbf), "Bc", m68851 },
{"pbicw", 2,	one(0xf08b),	one(0xffff), "BW", m68851 },
{"pbis", 2,	one(0xf08a),	one(0xffbf), "Bc", m68851 },
{"pbisw", 2,	one(0xf08a),	one(0xffff), "BW", m68851 },
{"pblc", 2,	one(0xf083),	one(0xffbf), "Bc", m68851 },
{"pblcw", 2,	one(0xf083),	one(0xffff), "BW", m68851 },
{"pbls", 2,	one(0xf082),	one(0xffbf), "Bc", m68851 },
{"pblsw", 2,	one(0xf082),	one(0xffff), "BW", m68851 },
{"pbsc", 2,	one(0xf085),	one(0xffbf), "Bc", m68851 },
{"pbscw", 2,	one(0xf085),	one(0xffff), "BW", m68851 },
{"pbss", 2,	one(0xf084),	one(0xffbf), "Bc", m68851 },
{"pbssw", 2,	one(0xf084),	one(0xffff), "BW", m68851 },
{"pbwc", 2,	one(0xf089),	one(0xffbf), "Bc", m68851 },
{"pbwcw", 2,	one(0xf089),	one(0xffff), "BW", m68851 },
{"pbws", 2,	one(0xf088),	one(0xffbf), "Bc", m68851 },
{"pbwsw", 2,	one(0xf088),	one(0xffff), "BW", m68851 },

{"pdbac", 4,	two(0xf048, 0x0007),	two(0xfff8, 0xffff), "DsBw", m68851 },
{"pdbas", 4,	two(0xf048, 0x0006),	two(0xfff8, 0xffff), "DsBw", m68851 },
{"pdbbc", 4,	two(0xf048, 0x0001),	two(0xfff8, 0xffff), "DsBw", m68851 },
{"pdbbs", 4,	two(0xf048, 0x0000),	two(0xfff8, 0xffff), "DsBw", m68851 },
{"pdbcc", 4,	two(0xf048, 0x000f),	two(0xfff8, 0xffff), "DsBw", m68851 },
{"pdbcs", 4,	two(0xf048, 0x000e),	two(0xfff8, 0xffff), "DsBw", m68851 },
{"pdbgc", 4,	two(0xf048, 0x000d),	two(0xfff8, 0xffff), "DsBw", m68851 },
{"pdbgs", 4,	two(0xf048, 0x000c),	two(0xfff8, 0xffff), "DsBw", m68851 },
{"pdbic", 4,	two(0xf048, 0x000b),	two(0xfff8, 0xffff), "DsBw", m68851 },
{"pdbis", 4,	two(0xf048, 0x000a),	two(0xfff8, 0xffff), "DsBw", m68851 },
{"pdblc", 4,	two(0xf048, 0x0003),	two(0xfff8, 0xffff), "DsBw", m68851 },
{"pdbls", 4,	two(0xf048, 0x0002),	two(0xfff8, 0xffff), "DsBw", m68851 },
{"pdbsc", 4,	two(0xf048, 0x0005),	two(0xfff8, 0xffff), "DsBw", m68851 },
{"pdbss", 4,	two(0xf048, 0x0004),	two(0xfff8, 0xffff), "DsBw", m68851 },
{"pdbwc", 4,	two(0xf048, 0x0009),	two(0xfff8, 0xffff), "DsBw", m68851 },
{"pdbws", 4,	two(0xf048, 0x0008),	two(0xfff8, 0xffff), "DsBw", m68851 },

{"pea", 2,	one(0044100),		one(0177700), "!s", m68000up|mcfisa_a },

{"pflusha", 2,	one(0xf518),		one(0xfff8), "", m68040up },
{"pflusha", 4,	two(0xf000,0x2400), two(0xffff,0xffff), "", m68030 | m68851 },

{"pflush", 4,   two(0xf000,0x3010), two(0xffc0,0xfe10), "T3T9", m68030|m68851 },
{"pflush", 4,   two(0xf000,0x3810), two(0xffc0,0xfe10), "T3T9&s", m68030|m68851 },
{"pflush", 4,   two(0xf000,0x3008), two(0xffc0,0xfe18), "D3T9", m68030|m68851 },
{"pflush", 4,   two(0xf000,0x3808), two(0xffc0,0xfe18), "D3T9&s", m68030|m68851 },
{"pflush", 4,   two(0xf000,0x3000), two(0xffc0,0xfe1e), "f3T9", m68030|m68851 },
{"pflush", 4,   two(0xf000,0x3800), two(0xffc0,0xfe1e), "f3T9&s", m68030|m68851 },
{"pflush", 2,	one(0xf508),		one(0xfff8), "as", m68040up },
{"pflush", 2,	one(0xf508),		one(0xfff8), "As", m68040up },

{"pflushan", 2,	one(0xf510),		one(0xfff8), "", m68040up },
{"pflushn", 2,	one(0xf500),		one(0xfff8), "as", m68040up },
{"pflushn", 2,	one(0xf500),		one(0xfff8), "As", m68040up },

{"pflushr", 4,	two(0xf000, 0xa000), two(0xffc0, 0xffff), "|s", m68851 },

{"pflushs", 4,	two(0xf000, 0x3410), two(0xfff8, 0xfe10), "T3T9", m68851 },
{"pflushs", 4,	two(0xf000, 0x3c10), two(0xfff8, 0xfe10), "T3T9&s", m68851 },
{"pflushs", 4,	two(0xf000, 0x3408), two(0xfff8, 0xfe18), "D3T9", m68851 },
{"pflushs", 4,	two(0xf000, 0x3c08), two(0xfff8, 0xfe18), "D3T9&s", m68851 },
{"pflushs", 4,	two(0xf000, 0x3400), two(0xfff8, 0xfe1e), "f3T9", m68851 },
{"pflushs", 4,	two(0xf000, 0x3c00), two(0xfff8, 0xfe1e), "f3T9&s", m68851 },

{"ploadr", 4,   two(0xf000,0x2210), two(0xffc0,0xfff0), "T3&s", m68030|m68851 },
{"ploadr", 4,   two(0xf000,0x2208), two(0xffc0,0xfff8), "D3&s", m68030|m68851 },
{"ploadr", 4,   two(0xf000,0x2200), two(0xffc0,0xfffe), "f3&s", m68030|m68851 },
{"ploadw", 4,   two(0xf000,0x2010), two(0xffc0,0xfff0), "T3&s", m68030|m68851 },
{"ploadw", 4,   two(0xf000,0x2008), two(0xffc0,0xfff8), "D3&s", m68030|m68851 },
{"ploadw", 4,   two(0xf000,0x2000), two(0xffc0,0xfffe), "f3&s", m68030|m68851 },

{"plpar", 2,	one(0xf5c8),		one(0xfff8), "as", m68060 },
{"plpaw", 2,	one(0xf588),		one(0xfff8), "as", m68060 },

{"pmove", 4,    two(0xf000,0x4000), two(0xffc0,0xffff), "*l08", m68030|m68851 },
{"pmove", 4,    two(0xf000,0x5c00), two(0xffc0,0xffff), "*w18", m68851 },
{"pmove", 4,    two(0xf000,0x4000), two(0xffc0,0xe3ff), "*b28", m68851 },
{"pmove", 4,    two(0xf000,0x4200), two(0xffc0,0xffff), "08%s", m68030|m68851 },
{"pmove", 4,    two(0xf000,0x5e00), two(0xffc0,0xffff), "18%s", m68851 },
{"pmove", 4,    two(0xf000,0x4200), two(0xffc0,0xe3ff), "28%s", m68851 },
{"pmove", 4,    two(0xf000,0x4000), two(0xffc0,0xe3ff), "|sW8", m68030|m68851 },
{"pmove", 4,    two(0xf000,0x4200), two(0xffc0,0xe3ff), "W8~s", m68030|m68851 },
{"pmove", 4,    two(0xf000,0x6200), two(0xffc0,0xe3e3), "*wX3", m68851 },
{"pmove", 4,    two(0xf000,0x6000), two(0xffc0,0xe3e3), "X3%s", m68851 },
{"pmove", 4,    two(0xf000,0x6000), two(0xffc0,0xffff), "*wY8", m68030|m68851 },
{"pmove", 4,    two(0xf000,0x6200), two(0xffc0,0xffff), "Y8%s", m68030|m68851 },
{"pmove", 4,    two(0xf000,0x6600), two(0xffc0,0xffff), "Z8%s", m68851 },
{"pmove", 4,    two(0xf000,0x0800), two(0xffc0,0xfbff), "*l38", m68030 },
{"pmove", 4,    two(0xf000,0x0a00), two(0xffc0,0xfbff), "38%s", m68030 },

{"pmovefd", 4,	two(0xf000, 0x4100),	two(0xffc0, 0xe3ff), "*l08", m68030 },
{"pmovefd", 4,	two(0xf000, 0x4100),	two(0xffc0, 0xe3ff), "|sW8", m68030 },
{"pmovefd", 4,	two(0xf000, 0x0900),	two(0xffc0, 0xfbff), "*l38", m68030 },

{"prestore", 2,	one(0xf140),		one(0xffc0), "<s", m68851 },

{"psave", 2,	one(0xf100),		one(0xffc0), ">s", m68851 },

{"psac", 4,	two(0xf040, 0x0007),	two(0xffc0, 0xffff), "$s", m68851 },
{"psas", 4,	two(0xf040, 0x0006),	two(0xffc0, 0xffff), "$s", m68851 },
{"psbc", 4,	two(0xf040, 0x0001),	two(0xffc0, 0xffff), "$s", m68851 },
{"psbs", 4,	two(0xf040, 0x0000),	two(0xffc0, 0xffff), "$s", m68851 },
{"pscc", 4,	two(0xf040, 0x000f),	two(0xffc0, 0xffff), "$s", m68851 },
{"pscs", 4,	two(0xf040, 0x000e),	two(0xffc0, 0xffff), "$s", m68851 },
{"psgc", 4,	two(0xf040, 0x000d),	two(0xffc0, 0xffff), "$s", m68851 },
{"psgs", 4,	two(0xf040, 0x000c),	two(0xffc0, 0xffff), "$s", m68851 },
{"psic", 4,	two(0xf040, 0x000b),	two(0xffc0, 0xffff), "$s", m68851 },
{"psis", 4,	two(0xf040, 0x000a),	two(0xffc0, 0xffff), "$s", m68851 },
{"pslc", 4,	two(0xf040, 0x0003),	two(0xffc0, 0xffff), "$s", m68851 },
{"psls", 4,	two(0xf040, 0x0002),	two(0xffc0, 0xffff), "$s", m68851 },
{"pssc", 4,	two(0xf040, 0x0005),	two(0xffc0, 0xffff), "$s", m68851 },
{"psss", 4,	two(0xf040, 0x0004),	two(0xffc0, 0xffff), "$s", m68851 },
{"pswc", 4,	two(0xf040, 0x0009),	two(0xffc0, 0xffff), "$s", m68851 },
{"psws", 4,	two(0xf040, 0x0008),	two(0xffc0, 0xffff), "$s", m68851 },

{"ptestr", 4, 	two(0xf000,0x8210), two(0xffc0, 0xe3f0), "T3&st8", m68030|m68851 },
{"ptestr", 4, 	two(0xf000,0x8310), two(0xffc0,0xe310), "T3&st8A9", m68030|m68851 },
{"ptestr", 4, 	two(0xf000,0x8208), two(0xffc0,0xe3f8), "D3&st8", m68030|m68851 },
{"ptestr", 4, 	two(0xf000,0x8308), two(0xffc0,0xe318), "D3&st8A9", m68030|m68851 },
{"ptestr", 4, 	two(0xf000,0x8200), two(0xffc0,0xe3fe), "f3&st8", m68030|m68851 },
{"ptestr", 4, 	two(0xf000,0x8300), two(0xffc0,0xe31e), "f3&st8A9", m68030|m68851 },
{"ptestr", 2,	one(0xf568),		one(0xfff8), "as", m68040 },

{"ptestw", 4, 	two(0xf000,0x8010), two(0xffc0,0xe3f0), "T3&st8", m68030|m68851 },
{"ptestw", 4, 	two(0xf000,0x8110), two(0xffc0,0xe310), "T3&st8A9", m68030|m68851 },
{"ptestw", 4, 	two(0xf000,0x8008), two(0xffc0,0xe3f8), "D3&st8", m68030|m68851 },
{"ptestw", 4, 	two(0xf000,0x8108), two(0xffc0,0xe318), "D3&st8A9", m68030|m68851 },
{"ptestw", 4, 	two(0xf000,0x8000), two(0xffc0,0xe3fe), "f3&st8", m68030|m68851 },
{"ptestw", 4, 	two(0xf000,0x8100), two(0xffc0,0xe31e), "f3&st8A9", m68030|m68851 },
{"ptestw", 2,	one(0xf548),		one(0xfff8), "as", m68040 },

{"ptrapacw", 6,	two(0xf07a, 0x0007),	two(0xffff, 0xffff), "#w", m68851 },
{"ptrapacl", 6,	two(0xf07b, 0x0007),	two(0xffff, 0xffff), "#l", m68851 },
{"ptrapac", 4,	two(0xf07c, 0x0007),	two(0xffff, 0xffff), "",   m68851 },

{"ptrapasw", 6,	two(0xf07a, 0x0006),	two(0xffff, 0xffff), "#w", m68851 },
{"ptrapasl", 6,	two(0xf07b, 0x0006),	two(0xffff, 0xffff), "#l", m68851 },
{"ptrapas", 4,	two(0xf07c, 0x0006),	two(0xffff, 0xffff), "",   m68851 },

{"ptrapbcw", 6,	two(0xf07a, 0x0001),	two(0xffff, 0xffff), "#w", m68851 },
{"ptrapbcl", 6,	two(0xf07b, 0x0001),	two(0xffff, 0xffff), "#l", m68851 },
{"ptrapbc", 4,	two(0xf07c, 0x0001),	two(0xffff, 0xffff), "",   m68851 },

{"ptrapbsw", 6,	two(0xf07a, 0x0000),	two(0xffff, 0xffff), "#w", m68851 },
{"ptrapbsl", 6,	two(0xf07b, 0x0000),	two(0xffff, 0xffff), "#l", m68851 },
{"ptrapbs", 4,	two(0xf07c, 0x0000),	two(0xffff, 0xffff), "",   m68851 },

{"ptrapccw", 6,	two(0xf07a, 0x000f),	two(0xffff, 0xffff), "#w", m68851 },
{"ptrapccl", 6,	two(0xf07b, 0x000f),	two(0xffff, 0xffff), "#l", m68851 },
{"ptrapcc", 4,	two(0xf07c, 0x000f),	two(0xffff, 0xffff), "",   m68851 },

{"ptrapcsw", 6,	two(0xf07a, 0x000e),	two(0xffff, 0xffff), "#w", m68851 },
{"ptrapcsl", 6,	two(0xf07b, 0x000e),	two(0xffff, 0xffff), "#l", m68851 },
{"ptrapcs", 4,	two(0xf07c, 0x000e),	two(0xffff, 0xffff), "",   m68851 },

{"ptrapgcw", 6,	two(0xf07a, 0x000d),	two(0xffff, 0xffff), "#w", m68851 },
{"ptrapgcl", 6,	two(0xf07b, 0x000d),	two(0xffff, 0xffff), "#l", m68851 },
{"ptrapgc", 4,	two(0xf07c, 0x000d),	two(0xffff, 0xffff), "",   m68851 },

{"ptrapgsw", 6,	two(0xf07a, 0x000c),	two(0xffff, 0xffff), "#w", m68851 },
{"ptrapgsl", 6,	two(0xf07b, 0x000c),	two(0xffff, 0xffff), "#l", m68851 },
{"ptrapgs", 4,	two(0xf07c, 0x000c),	two(0xffff, 0xffff), "",   m68851 },

{"ptrapicw", 6,	two(0xf07a, 0x000b),	two(0xffff, 0xffff), "#w", m68851 },
{"ptrapicl", 6,	two(0xf07b, 0x000b),	two(0xffff, 0xffff), "#l", m68851 },
{"ptrapic", 4,	two(0xf07c, 0x000b),	two(0xffff, 0xffff), "",   m68851 },

{"ptrapisw", 6,	two(0xf07a, 0x000a),	two(0xffff, 0xffff), "#w", m68851 },
{"ptrapisl", 6,	two(0xf07b, 0x000a),	two(0xffff, 0xffff), "#l", m68851 },
{"ptrapis", 4,	two(0xf07c, 0x000a),	two(0xffff, 0xffff), "",   m68851 },

{"ptraplcw", 6,	two(0xf07a, 0x0003),	two(0xffff, 0xffff), "#w", m68851 },
{"ptraplcl", 6,	two(0xf07b, 0x0003),	two(0xffff, 0xffff), "#l", m68851 },
{"ptraplc", 4,	two(0xf07c, 0x0003),	two(0xffff, 0xffff), "",   m68851 },

{"ptraplsw", 6,	two(0xf07a, 0x0002),	two(0xffff, 0xffff), "#w", m68851 },
{"ptraplsl", 6,	two(0xf07b, 0x0002),	two(0xffff, 0xffff), "#l", m68851 },
{"ptrapls", 4,	two(0xf07c, 0x0002),	two(0xffff, 0xffff), "",   m68851 },

{"ptrapscw", 6,	two(0xf07a, 0x0005),	two(0xffff, 0xffff), "#w", m68851 },
{"ptrapscl", 6,	two(0xf07b, 0x0005),	two(0xffff, 0xffff), "#l", m68851 },
{"ptrapsc", 4,	two(0xf07c, 0x0005),	two(0xffff, 0xffff), "",   m68851 },

{"ptrapssw", 6,	two(0xf07a, 0x0004),	two(0xffff, 0xffff), "#w", m68851 },
{"ptrapssl", 6,	two(0xf07b, 0x0004),	two(0xffff, 0xffff), "#l", m68851 },
{"ptrapss", 4,	two(0xf07c, 0x0004),	two(0xffff, 0xffff), "",   m68851 },

{"ptrapwcw", 6,	two(0xf07a, 0x0009),	two(0xffff, 0xffff), "#w", m68851 },
{"ptrapwcl", 6,	two(0xf07b, 0x0009),	two(0xffff, 0xffff), "#l", m68851 },
{"ptrapwc", 4,	two(0xf07c, 0x0009),	two(0xffff, 0xffff), "",   m68851 },

{"ptrapwsw", 6,	two(0xf07a, 0x0008),	two(0xffff, 0xffff), "#w", m68851 },
{"ptrapwsl", 6,	two(0xf07b, 0x0008),	two(0xffff, 0xffff), "#l", m68851 },
{"ptrapws", 4,	two(0xf07c, 0x0008),	two(0xffff, 0xffff), "",   m68851 },

{"pulse", 2,	one(0045314),		one(0177777), "", m68060 | mcfisa_a },

{"pvalid", 4,	two(0xf000, 0x2800),	two(0xffc0, 0xffff), "Vs&s", m68851 },
{"pvalid", 4,	two(0xf000, 0x2c00),	two(0xffc0, 0xfff8), "A3&s", m68851 },

  /* FIXME: don't allow Dw==Dx. */
{"remsl", 4,    two(0x4c40, 0x0800),    two(0xffc0, 0x8ff8), "qsD3D1", mcfhwdiv },
{"remul", 4,    two(0x4c40, 0x0000),    two(0xffc0, 0x8ff8), "qsD3D1", mcfhwdiv },

{"reset", 2,	one(0047160),		one(0177777), "", m68000up },

{"rolb", 2,	one(0160430),		one(0170770), "QdDs", m68000up },
{"rolb", 2,	one(0160470),		one(0170770), "DdDs", m68000up },
{"rolw", 2,	one(0160530),		one(0170770), "QdDs", m68000up },
{"rolw", 2,	one(0160570),		one(0170770), "DdDs", m68000up },
{"rolw", 2,	one(0163700),		one(0177700), "~s",   m68000up },
{"roll", 2,	one(0160630),		one(0170770), "QdDs", m68000up },
{"roll", 2,	one(0160670),		one(0170770), "DdDs", m68000up },

{"rorb", 2,	one(0160030),		one(0170770), "QdDs", m68000up },
{"rorb", 2,	one(0160070),		one(0170770), "DdDs", m68000up },
{"rorw", 2,	one(0160130),		one(0170770), "QdDs", m68000up },
{"rorw", 2,	one(0160170),		one(0170770), "DdDs", m68000up },
{"rorw", 2,	one(0163300),		one(0177700), "~s",   m68000up },
{"rorl", 2,	one(0160230),		one(0170770), "QdDs", m68000up },
{"rorl", 2,	one(0160270),		one(0170770), "DdDs", m68000up },

{"roxlb", 2,	one(0160420),		one(0170770), "QdDs", m68000up },
{"roxlb", 2,	one(0160460),		one(0170770), "DdDs", m68000up },
{"roxlw", 2,	one(0160520),		one(0170770), "QdDs", m68000up },
{"roxlw", 2,	one(0160560),		one(0170770), "DdDs", m68000up },
{"roxlw", 2,	one(0162700),		one(0177700), "~s",   m68000up },
{"roxll", 2,	one(0160620),		one(0170770), "QdDs", m68000up },
{"roxll", 2,	one(0160660),		one(0170770), "DdDs", m68000up },

{"roxrb", 2,	one(0160020),		one(0170770), "QdDs", m68000up },
{"roxrb", 2,	one(0160060),		one(0170770), "DdDs", m68000up },
{"roxrw", 2,	one(0160120),		one(0170770), "QdDs", m68000up },
{"roxrw", 2,	one(0160160),		one(0170770), "DdDs", m68000up },
{"roxrw", 2,	one(0162300),		one(0177700), "~s",   m68000up },
{"roxrl", 2,	one(0160220),		one(0170770), "QdDs", m68000up },
{"roxrl", 2,	one(0160260),		one(0170770), "DdDs", m68000up },

{"rtd", 4,	one(0047164),		one(0177777), "#w", m68010up },

{"rte", 2,	one(0047163),		one(0177777), "",   m68000up | mcfisa_a },

{"rtm", 2,	one(0003300),		one(0177760), "Rs", m68020 },

{"rtr", 2,	one(0047167),		one(0177777), "",   m68000up },

{"rts", 2,	one(0047165),		one(0177777), "",   m68000up | mcfisa_a },

{"satsl", 2,	one(0046200),		one(0177770), "Ds", mcfisa_b },

{"sbcd", 2,	one(0100400),		one(0170770), "DsDd", m68000up },
{"sbcd", 2,	one(0100410),		one(0170770), "-s-d", m68000up },

{"scc", 2,	one(0052300),	one(0177700), "$s", m68000up },
{"scc", 2,	one(0052300),	one(0177700), "Ds", mcfisa_a },
{"scs", 2,	one(0052700),	one(0177700), "$s", m68000up },
{"scs", 2,	one(0052700),	one(0177700), "Ds", mcfisa_a },
{"seq", 2,	one(0053700),	one(0177700), "$s", m68000up },
{"seq", 2,	one(0053700),	one(0177700), "Ds", mcfisa_a },
{"sf", 2,	one(0050700),	one(0177700), "$s", m68000up },
{"sf", 2,	one(0050700),	one(0177700), "Ds", mcfisa_a },
{"sge", 2,	one(0056300),	one(0177700), "$s", m68000up },
{"sge", 2,	one(0056300),	one(0177700), "Ds", mcfisa_a },
{"sgt", 2,	one(0057300),	one(0177700), "$s", m68000up },
{"sgt", 2,	one(0057300),	one(0177700), "Ds", mcfisa_a },
{"shi", 2,	one(0051300),	one(0177700), "$s", m68000up },
{"shi", 2,	one(0051300),	one(0177700), "Ds", mcfisa_a },
{"sle", 2,	one(0057700),	one(0177700), "$s", m68000up },
{"sle", 2,	one(0057700),	one(0177700), "Ds", mcfisa_a },
{"sls", 2,	one(0051700),	one(0177700), "$s", m68000up },
{"sls", 2,	one(0051700),	one(0177700), "Ds", mcfisa_a },
{"slt", 2,	one(0056700),	one(0177700), "$s", m68000up },
{"slt", 2,	one(0056700),	one(0177700), "Ds", mcfisa_a },
{"smi", 2,	one(0055700),	one(0177700), "$s", m68000up },
{"smi", 2,	one(0055700),	one(0177700), "Ds", mcfisa_a },
{"sne", 2,	one(0053300),	one(0177700), "$s", m68000up },
{"sne", 2,	one(0053300),	one(0177700), "Ds", mcfisa_a },
{"spl", 2,	one(0055300),	one(0177700), "$s", m68000up },
{"spl", 2,	one(0055300),	one(0177700), "Ds", mcfisa_a },
{"st", 2,	one(0050300),	one(0177700), "$s", m68000up },
{"st", 2,	one(0050300),	one(0177700), "Ds", mcfisa_a },
{"svc", 2,	one(0054300),	one(0177700), "$s", m68000up },
{"svc", 2,	one(0054300),	one(0177700), "Ds", mcfisa_a },
{"svs", 2,	one(0054700),	one(0177700), "$s", m68000up },
{"svs", 2,	one(0054700),	one(0177700), "Ds", mcfisa_a },

{"stop", 4,	one(0047162),	one(0177777), "#w", m68000up | mcfisa_a },

{"strldsr", 4, two(0040347,0043374), two(0177777,0177777), "#w", mcfisa_aa},

{"subal", 2,	one(0110700),	one(0170700), "*lAd", m68000up | mcfisa_a },
{"subaw", 2,	one(0110300),	one(0170700), "*wAd", m68000up },

{"subib", 4,	one(0002000),	one(0177700), "#b$s", m68000up },
{"subiw", 4,	one(0002100),	one(0177700), "#w$s", m68000up },
{"subil", 6,	one(0002200),	one(0177700), "#l$s", m68000up },
{"subil", 6,	one(0002200),	one(0177700), "#lDs", mcfisa_a },

{"subqb", 2,	one(0050400),	one(0170700), "Qd%s", m68000up },
{"subqw", 2,	one(0050500),	one(0170700), "Qd%s", m68000up },
{"subql", 2,	one(0050600),	one(0170700), "Qd%s", m68000up | mcfisa_a },

/* The sub opcode can generate the suba, subi, and subq instructions.  */
{"subb", 2,	one(0050400),	one(0170700), "Qd%s", m68000up },
{"subb", 4,	one(0002000),	one(0177700), "#b$s", m68000up },
{"subb", 2,	one(0110000),	one(0170700), ";bDd", m68000up },
{"subb", 2,	one(0110400),	one(0170700), "Dd~s", m68000up },
{"subw", 2,	one(0050500),	one(0170700), "Qd%s", m68000up },
{"subw", 4,	one(0002100),	one(0177700), "#w$s", m68000up },
{"subw", 2,	one(0110300),	one(0170700), "*wAd", m68000up },
{"subw", 2,	one(0110100),	one(0170700), "*wDd", m68000up },
{"subw", 2,	one(0110500),	one(0170700), "Dd~s", m68000up },
{"subl", 2,	one(0050600),	one(0170700), "Qd%s", m68000up | mcfisa_a },
{"subl", 6,	one(0002200),	one(0177700), "#l$s", m68000up },
{"subl", 6,	one(0002200),	one(0177700), "#lDs", mcfisa_a },
{"subl", 2,	one(0110700),	one(0170700), "*lAd", m68000up | mcfisa_a },
{"subl", 2,	one(0110200),	one(0170700), "*lDd", m68000up | mcfisa_a },
{"subl", 2,	one(0110600),	one(0170700), "Dd~s", m68000up | mcfisa_a },

{"subxb", 2,	one(0110400),	one(0170770), "DsDd", m68000up },
{"subxb", 2,	one(0110410),	one(0170770), "-s-d", m68000up },
{"subxw", 2,	one(0110500),	one(0170770), "DsDd", m68000up },
{"subxw", 2,	one(0110510),	one(0170770), "-s-d", m68000up },
{"subxl", 2,	one(0110600),	one(0170770), "DsDd", m68000up | mcfisa_a },
{"subxl", 2,	one(0110610),	one(0170770), "-s-d", m68000up },

{"swap", 2,	one(0044100),	one(0177770), "Ds", m68000up | mcfisa_a },

/* swbeg and swbegl are magic constants used on sysV68.  The compiler
   generates them before a switch table.  They tell the debugger and
   disassembler that a switch table follows.  The parameter is the
   number of elements in the table.  swbeg means that the entries in
   the table are word (2 byte) sized, and swbegl means that the
   entries in the table are longword (4 byte) sized.  */
{"swbeg", 4,	one(0045374),	one(0177777), "#w",   m68000up | mcfisa_a },
{"swbegl", 6,	one(0045375),	one(0177777), "#l",   m68000up | mcfisa_a },

{"tas", 2,	one(0045300),	one(0177700), "$s", m68000up | mcfisa_b},

#define TBL1(name,insn_size,signed,round,size)					\
  {name, insn_size, two(0174000, (signed<<11)|(!round<<10)|(size<<6)|0000400),	\
     two(0177700,0107777), "!sD1", cpu32 },				\
  {name, insn_size, two(0174000, (signed<<11)|(!round<<10)|(size<<6)),		\
     two(0177770,0107770), "DsD3D1", cpu32 }
#define TBL(name1, name2, name3, s, r) \
  TBL1(name1, 4, s, r, 0), TBL1(name2, 4, s, r, 1), TBL1(name3, 4, s, r, 2)
TBL("tblsb", "tblsw", "tblsl", 2, 1),
TBL("tblsnb", "tblsnw", "tblsnl", 2, 0),
TBL("tblub", "tbluw", "tblul", 0, 1),
TBL("tblunb", "tblunw", "tblunl", 0, 0),

{"trap", 2,	one(0047100),	one(0177760), "Ts", m68000up | mcfisa_a },

{"trapcc", 2,	one(0052374),	one(0177777), "", m68020up | cpu32 },
{"trapcs", 2,	one(0052774),	one(0177777), "", m68020up | cpu32 },
{"trapeq", 2,	one(0053774),	one(0177777), "", m68020up | cpu32 },
{"trapf", 2,	one(0050774),	one(0177777), "", m68020up | cpu32 | mcfisa_a },
{"trapge", 2,	one(0056374),	one(0177777), "", m68020up | cpu32 },
{"trapgt", 2,	one(0057374),	one(0177777), "", m68020up | cpu32 },
{"traphi", 2,	one(0051374),	one(0177777), "", m68020up | cpu32 },
{"traple", 2,	one(0057774),	one(0177777), "", m68020up | cpu32 },
{"trapls", 2,	one(0051774),	one(0177777), "", m68020up | cpu32 },
{"traplt", 2,	one(0056774),	one(0177777), "", m68020up | cpu32 },
{"trapmi", 2,	one(0055774),	one(0177777), "", m68020up | cpu32 },
{"trapne", 2,	one(0053374),	one(0177777), "", m68020up | cpu32 },
{"trappl", 2,	one(0055374),	one(0177777), "", m68020up | cpu32 },
{"trapt", 2,	one(0050374),	one(0177777), "", m68020up | cpu32 },
{"trapvc", 2,	one(0054374),	one(0177777), "", m68020up | cpu32 },
{"trapvs", 2,	one(0054774),	one(0177777), "", m68020up | cpu32 },

{"trapccw", 4,	one(0052372),	one(0177777), "#w", m68020up|cpu32 },
{"trapcsw", 4,	one(0052772),	one(0177777), "#w", m68020up|cpu32 },
{"trapeqw", 4,	one(0053772),	one(0177777), "#w", m68020up|cpu32 },
{"trapfw", 4,	one(0050772),	one(0177777), "#w", m68020up|cpu32|mcfisa_a},
{"trapgew", 4,	one(0056372),	one(0177777), "#w", m68020up|cpu32 },
{"trapgtw", 4,	one(0057372),	one(0177777), "#w", m68020up|cpu32 },
{"traphiw", 4,	one(0051372),	one(0177777), "#w", m68020up|cpu32 },
{"traplew", 4,	one(0057772),	one(0177777), "#w", m68020up|cpu32 },
{"traplsw", 4,	one(0051772),	one(0177777), "#w", m68020up|cpu32 },
{"trapltw", 4,	one(0056772),	one(0177777), "#w", m68020up|cpu32 },
{"trapmiw", 4,	one(0055772),	one(0177777), "#w", m68020up|cpu32 },
{"trapnew", 4,	one(0053372),	one(0177777), "#w", m68020up|cpu32 },
{"trapplw", 4,	one(0055372),	one(0177777), "#w", m68020up|cpu32 },
{"traptw", 4,	one(0050372),	one(0177777), "#w", m68020up|cpu32 },
{"trapvcw", 4,	one(0054372),	one(0177777), "#w", m68020up|cpu32 },
{"trapvsw", 4,	one(0054772),	one(0177777), "#w", m68020up|cpu32 },

{"trapccl", 6,	one(0052373),	one(0177777), "#l", m68020up|cpu32 },
{"trapcsl", 6,	one(0052773),	one(0177777), "#l", m68020up|cpu32 },
{"trapeql", 6,	one(0053773),	one(0177777), "#l", m68020up|cpu32 },
{"trapfl", 6,	one(0050773),	one(0177777), "#l", m68020up|cpu32|mcfisa_a},
{"trapgel", 6,	one(0056373),	one(0177777), "#l", m68020up|cpu32 },
{"trapgtl", 6,	one(0057373),	one(0177777), "#l", m68020up|cpu32 },
{"traphil", 6,	one(0051373),	one(0177777), "#l", m68020up|cpu32 },
{"traplel", 6,	one(0057773),	one(0177777), "#l", m68020up|cpu32 },
{"traplsl", 6,	one(0051773),	one(0177777), "#l", m68020up|cpu32 },
{"trapltl", 6,	one(0056773),	one(0177777), "#l", m68020up|cpu32 },
{"trapmil", 6,	one(0055773),	one(0177777), "#l", m68020up|cpu32 },
{"trapnel", 6,	one(0053373),	one(0177777), "#l", m68020up|cpu32 },
{"trappll", 6,	one(0055373),	one(0177777), "#l", m68020up|cpu32 },
{"traptl", 6,	one(0050373),	one(0177777), "#l", m68020up|cpu32 },
{"trapvcl", 6,	one(0054373),	one(0177777), "#l", m68020up|cpu32 },
{"trapvsl", 6,	one(0054773),	one(0177777), "#l", m68020up|cpu32 },

{"trapv", 2,	one(0047166),	one(0177777), "", m68000up },

{"tstb", 2,	one(0045000),	one(0177700), ";b", m68020up|cpu32|mcfisa_a },
{"tstb", 2,	one(0045000),	one(0177700), "$b", m68000up },
{"tstw", 2,	one(0045100),	one(0177700), "*w", m68020up|cpu32|mcfisa_a },
{"tstw", 2,	one(0045100),	one(0177700), "$w", m68000up },
{"tstl", 2,	one(0045200),	one(0177700), "*l", m68020up|cpu32|mcfisa_a },
{"tstl", 2,	one(0045200),	one(0177700), "$l", m68000up },

{"unlk", 2,	one(0047130),	one(0177770), "As", m68000up | mcfisa_a },

{"unpk", 4,	one(0100600),	one(0170770), "DsDd#w", m68020up },
{"unpk", 4,	one(0100610),	one(0170770), "-s-d#w", m68020up },

{"wddatab", 2,	one(0175400),   one(0177700), "~s", mcfisa_a },
{"wddataw", 2,	one(0175500),   one(0177700), "~s", mcfisa_a },
{"wddatal", 2,	one(0175600),   one(0177700), "~s", mcfisa_a },

{"wdebug", 4,	two(0175720, 03),	two(0177770, 0xffff), "as", mcfisa_a },
{"wdebug", 4,	two(0175750, 03),	two(0177770, 0xffff), "ds", mcfisa_a },
};

const int m68k_numopcodes = sizeof m68k_opcodes / sizeof m68k_opcodes[0];

/* These aliases used to be in the above table, each one duplicating
   all of the entries for its primary exactly.  This table was
   constructed by mechanical processing of the opcode table, with a
   small number of tweaks done by hand.  There are probably a lot more
   aliases above that could be moved down here, except for very minor
   differences.  */

const struct m68k_opcode_alias m68k_opcode_aliases[] =
{
  { "add",	"addw", },
  { "adda",	"addaw", },
  { "addi",	"addiw", },
  { "addq",	"addqw", },
  { "addx",	"addxw", },
  { "asl",	"aslw", },
  { "asr",	"asrw", },
  { "bhi",	"bhiw", },
  { "bls",	"blsw", },
  { "bcc",	"bccw", },
  { "bcs",	"bcsw", },
  { "bne",	"bnew", },
  { "beq",	"beqw", },
  { "bvc",	"bvcw", },
  { "bvs",	"bvsw", },
  { "bpl",	"bplw", },
  { "bmi",	"bmiw", },
  { "bge",	"bgew", },
  { "blt",	"bltw", },
  { "bgt",	"bgtw", },
  { "ble",	"blew", },
  { "bra",	"braw", },
  { "bsr",	"bsrw", },
  { "bhib",	"bhis", },
  { "blsb",	"blss", },
  { "bccb",	"bccs", },
  { "bcsb",	"bcss", },
  { "bneb",	"bnes", },
  { "beqb",	"beqs", },
  { "bvcb",	"bvcs", },
  { "bvsb",	"bvss", },
  { "bplb",	"bpls", },
  { "bmib",	"bmis", },
  { "bgeb",	"bges", },
  { "bltb",	"blts", },
  { "bgtb",	"bgts", },
  { "bleb",	"bles", },
  { "brab",	"bras", },
  { "bsrb",	"bsrs", },
  { "bhs",	"bccw" },
  { "bhss",	"bccs" },
  { "bhsb",	"bccs" },
  { "bhsw",	"bccw" },
  { "bhsl",	"bccl" },
  { "blo",	"bcsw" },
  { "blos",	"bcss" },
  { "blob",	"bcss" },
  { "blow",	"bcsw" },
  { "blol",	"bcsl" },
  { "br",	"braw", },
  { "brs",	"bras", },
  { "brb",	"bras", },
  { "brw",	"braw", },
  { "brl",	"bral", },
  { "jfnlt",	"bcc", },	/* Apparently a sun alias.  */
  { "jfngt",	"ble", },	/* Apparently a sun alias.  */
  { "jfeq",	"beqs", },	/* Apparently a sun alias.  */
  { "bchgb",	"bchg", },
  { "bchgl",	"bchg", },
  { "bclrb",	"bclr", },
  { "bclrl",	"bclr", },
  { "bsetb",	"bset", },
  { "bsetl",	"bset", },
  { "btstb",	"btst", },
  { "btstl",	"btst", },
  { "cas2",	"cas2w", },
  { "cas",	"casw", },
  { "chk2",	"chk2w", },
  { "chk",	"chkw", },
  { "clr",	"clrw", },
  { "cmp2",	"cmp2w", },
  { "cmpa",	"cmpaw", },
  { "cmpi",	"cmpiw", },
  { "cmpm",	"cmpmw", },
  { "cmp",	"cmpw", },
  { "dbccw",	"dbcc", },
  { "dbcsw",	"dbcs", },
  { "dbeqw",	"dbeq", },
  { "dbfw",	"dbf", },
  { "dbgew",	"dbge", },
  { "dbgtw",	"dbgt", },
  { "dbhiw",	"dbhi", },
  { "dblew",	"dble", },
  { "dblsw",	"dbls", },
  { "dbltw",	"dblt", },
  { "dbmiw",	"dbmi", },
  { "dbnew",	"dbne", },
  { "dbplw",	"dbpl", },
  { "dbtw",	"dbt", },
  { "dbvcw",	"dbvc", },
  { "dbvsw",	"dbvs", },
  { "dbhs",	"dbcc", },
  { "dbhsw",	"dbcc", },
  { "dbra",	"dbf", },
  { "dbraw",	"dbf", },
  { "tdivsl",	"divsl", },
  { "divs",	"divsw", },
  { "divu",	"divuw", },
  { "ext",	"extw", },
  { "extbw",	"extw", },
  { "extwl",	"extl", },
  { "fbneq",	"fbne", },
  { "fbsneq",	"fbsne", },
  { "fdbneq",	"fdbne", },
  { "fdbsneq",	"fdbsne", },
  { "fmovecr",	"fmovecrx", },
  { "fmovm",	"fmovem", },
  { "fsneq",	"fsne", },
  { "fssneq",	"fssne", },
  { "ftrapneq",	"ftrapne", },
  { "ftrapsneq", "ftrapsne", },
  { "fjneq",	"fjne", },
  { "fjsneq",	"fjsne", },
  { "jmpl",	"jmp", },
  { "jmps",	"jmp", },
  { "jsrl",	"jsr", },
  { "jsrs",	"jsr", },
  { "leal",	"lea", },
  { "lsl",	"lslw", },
  { "lsr",	"lsrw", },
  { "mac",	"macw" },
  { "movea",	"moveaw", },
  { "movem",	"movemw", },
  { "movml",	"moveml", },
  { "movmw",	"movemw", },
  { "movm",	"movemw", },
  { "movep",	"movepw", },
  { "movpw",	"movepw", },
  { "moves",	"movesw" },
  { "muls",	"mulsw", },
  { "mulu",	"muluw", },
  { "msac",	"msacw" },
  { "nbcdb",	"nbcd" },
  { "neg",	"negw", },
  { "negx",	"negxw", },
  { "not",	"notw", },
  { "peal",	"pea", },
  { "rol",	"rolw", },
  { "ror",	"rorw", },
  { "roxl",	"roxlw", },
  { "roxr",	"roxrw", },
  { "sats",	"satsl", },
  { "sbcdb",	"sbcd", },
  { "sccb",	"scc", },
  { "scsb",	"scs", },
  { "seqb",	"seq", },
  { "sfb",	"sf", },
  { "sgeb",	"sge", },
  { "sgtb",	"sgt", },
  { "shib",	"shi", },
  { "sleb",	"sle", },
  { "slsb",	"sls", },
  { "sltb",	"slt", },
  { "smib",	"smi", },
  { "sneb",	"sne", },
  { "splb",	"spl", },
  { "stb",	"st", },
  { "svcb",	"svc", },
  { "svsb",	"svs", },
  { "sfge",	"sge", },
  { "sfgt",	"sgt", },
  { "sfle",	"sle", },
  { "sflt",	"slt", },
  { "sfneq",	"sne", },
  { "suba",	"subaw", },
  { "subi",	"subiw", },
  { "subq",	"subqw", },
  { "sub",	"subw", },
  { "subx",	"subxw", },
  { "swapw",	"swap", },
  { "tasb",	"tas", },
  { "tpcc",	"trapcc", },
  { "tcc",	"trapcc", },
  { "tst",	"tstw", },
  { "jbra",	"jra", },
  { "jbhi",	"jhi", },
  { "jbls",	"jls", },
  { "jbcc",	"jcc", },
  { "jbcs",	"jcs", },
  { "jbne",	"jne", },
  { "jbeq",	"jeq", },
  { "jbvc",	"jvc", },
  { "jbvs",	"jvs", },
  { "jbpl",	"jpl", },
  { "jbmi",	"jmi", },
  { "jbge",	"jge", },
  { "jblt",	"jlt", },
  { "jbgt",	"jgt", },
  { "jble",	"jle", },
  { "movql",	"moveq", },
  { "moveql",	"moveq", },
  { "movl",	"movel", },
  { "movq",	"moveq", },
  { "moval",	"moveal", },
  { "movaw",	"moveaw", },
  { "movb",	"moveb", },
  { "movc",	"movec", },
  { "movecl",	"movec", },
  { "movpl",	"movepl", },
  { "movw",	"movew", },
  { "movsb",	"movesb", },
  { "movsl",	"movesl", },
  { "movsw",	"movesw", },
  { "mov3q",	"mov3ql", },

  { "tdivul",	"divul", },	/* For m68k-svr4.  */
  { "fmovb",	"fmoveb", },
  { "fsmovb",	"fsmoveb", },
  { "fdmovb",	"fdmoveb", },
  { "fmovd",	"fmoved", },
  { "fsmovd",	"fsmoved", },
  { "fmovl",	"fmovel", },
  { "fsmovl",	"fsmovel", },
  { "fdmovl",	"fdmovel", },
  { "fmovp",	"fmovep", },
  { "fsmovp",	"fsmovep", },
  { "fdmovp",	"fdmovep", },
  { "fmovs",	"fmoves", },
  { "fsmovs",	"fsmoves", },
  { "fdmovs",	"fdmoves", },
  { "fmovw",	"fmovew", },
  { "fsmovw",	"fsmovew", },
  { "fdmovw",	"fdmovew", },
  { "fmovx",	"fmovex", },
  { "fsmovx",	"fsmovex", },
  { "fdmovx",	"fdmovex", },
  { "fmovcr",	"fmovecr", },
  { "fmovcrx",	"fmovecrx", },
  { "ftestb",	"ftstb", },
  { "ftestd",	"ftstd", },
  { "ftestl",	"ftstl", },
  { "ftestp",	"ftstp", },
  { "ftests",	"ftsts", },
  { "ftestw",	"ftstw", },
  { "ftestx",	"ftstx", },

  { "bitrevl",  "bitrev", },
  { "byterevl", "byterev", },
  { "ff1l",     "ff1", },

};

const int m68k_numaliases =
  sizeof m68k_opcode_aliases / sizeof m68k_opcode_aliases[0];
/* **** End of m68k-opc.c */
/* **** floatformat.c from sourceware.org CVS 2005-08-14.  */
/* IEEE floating point support routines, for GDB, the GNU Debugger.
   Copyright (C) 1991, 1994, 1999, 2000, 2003 Free Software Foundation, Inc.

This file is part of GDB.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see <http://www.gnu.org/licenses/>.  */

/* This is needed to pick up the NAN macro on some systems.  */
//#define _GNU_SOURCE

#ifndef INFINITY
#ifdef HUGE_VAL
#define INFINITY HUGE_VAL
#else
#define INFINITY (1.0 / 0.0)
#endif
#endif

#ifndef NAN
#define NAN (0.0 / 0.0)
#endif

static unsigned long get_field (const unsigned char *,
                                enum floatformat_byteorders,
                                unsigned int,
                                unsigned int,
                                unsigned int);
static int floatformat_always_valid (const struct floatformat *fmt,
                                     const char *from);

static int
floatformat_always_valid (const struct floatformat *fmt ATTRIBUTE_UNUSED,
                          const char *from ATTRIBUTE_UNUSED)
{
  return 1;
}

/* The odds that CHAR_BIT will be anything but 8 are low enough that I'm not
   going to bother with trying to muck around with whether it is defined in
   a system header, what we do if not, etc.  */
#define FLOATFORMAT_CHAR_BIT 8

/* floatformats for IEEE single and double, big and little endian.  */
const struct floatformat floatformat_ieee_single_big =
{
  floatformat_big, 32, 0, 1, 8, 127, 255, 9, 23,
  floatformat_intbit_no,
  "floatformat_ieee_single_big",
  floatformat_always_valid
};
const struct floatformat floatformat_ieee_single_little =
{
  floatformat_little, 32, 0, 1, 8, 127, 255, 9, 23,
  floatformat_intbit_no,
  "floatformat_ieee_single_little",
  floatformat_always_valid
};
const struct floatformat floatformat_ieee_double_big =
{
  floatformat_big, 64, 0, 1, 11, 1023, 2047, 12, 52,
  floatformat_intbit_no,
  "floatformat_ieee_double_big",
  floatformat_always_valid
};
const struct floatformat floatformat_ieee_double_little =
{
  floatformat_little, 64, 0, 1, 11, 1023, 2047, 12, 52,
  floatformat_intbit_no,
  "floatformat_ieee_double_little",
  floatformat_always_valid
};

/* floatformat for IEEE double, little endian byte order, with big endian word
   ordering, as on the ARM.  */

const struct floatformat floatformat_ieee_double_littlebyte_bigword =
{
  floatformat_littlebyte_bigword, 64, 0, 1, 11, 1023, 2047, 12, 52,
  floatformat_intbit_no,
  "floatformat_ieee_double_littlebyte_bigword",
  floatformat_always_valid
};

static int floatformat_i387_ext_is_valid (const struct floatformat *fmt, const char *from);

static int
floatformat_i387_ext_is_valid (const struct floatformat *fmt, const char *from)
{
  /* In the i387 double-extended format, if the exponent is all ones,
     then the integer bit must be set.  If the exponent is neither 0
     nor ~0, the intbit must also be set.  Only if the exponent is
     zero can it be zero, and then it must be zero.  */
  unsigned long exponent, int_bit;
  const unsigned char *ufrom = (const unsigned char *) from;

  exponent = get_field (ufrom, fmt->byteorder, fmt->totalsize,
			fmt->exp_start, fmt->exp_len);
  int_bit = get_field (ufrom, fmt->byteorder, fmt->totalsize,
		       fmt->man_start, 1);

  if ((exponent == 0) != (int_bit == 0))
    return 0;
  else
    return 1;
}

const struct floatformat floatformat_i387_ext =
{
  floatformat_little, 80, 0, 1, 15, 0x3fff, 0x7fff, 16, 64,
  floatformat_intbit_yes,
  "floatformat_i387_ext",
  floatformat_i387_ext_is_valid
};
const struct floatformat floatformat_m68881_ext =
{
  /* Note that the bits from 16 to 31 are unused.  */
  floatformat_big, 96, 0, 1, 15, 0x3fff, 0x7fff, 32, 64,
  floatformat_intbit_yes,
  "floatformat_m68881_ext",
  floatformat_always_valid
};
const struct floatformat floatformat_i960_ext =
{
  /* Note that the bits from 0 to 15 are unused.  */
  floatformat_little, 96, 16, 17, 15, 0x3fff, 0x7fff, 32, 64,
  floatformat_intbit_yes,
  "floatformat_i960_ext",
  floatformat_always_valid
};
const struct floatformat floatformat_m88110_ext =
{
  floatformat_big, 80, 0, 1, 15, 0x3fff, 0x7fff, 16, 64,
  floatformat_intbit_yes,
  "floatformat_m88110_ext",
  floatformat_always_valid
};
const struct floatformat floatformat_m88110_harris_ext =
{
  /* Harris uses raw format 128 bytes long, but the number is just an ieee
     double, and the last 64 bits are wasted. */
  floatformat_big,128, 0, 1, 11,  0x3ff,  0x7ff, 12, 52,
  floatformat_intbit_no,
  "floatformat_m88110_ext_harris",
  floatformat_always_valid
};
const struct floatformat floatformat_arm_ext_big =
{
  /* Bits 1 to 16 are unused.  */
  floatformat_big, 96, 0, 17, 15, 0x3fff, 0x7fff, 32, 64,
  floatformat_intbit_yes,
  "floatformat_arm_ext_big",
  floatformat_always_valid
};
const struct floatformat floatformat_arm_ext_littlebyte_bigword =
{
  /* Bits 1 to 16 are unused.  */
  floatformat_littlebyte_bigword, 96, 0, 17, 15, 0x3fff, 0x7fff, 32, 64,
  floatformat_intbit_yes,
  "floatformat_arm_ext_littlebyte_bigword",
  floatformat_always_valid
};
const struct floatformat floatformat_ia64_spill_big =
{
  floatformat_big, 128, 0, 1, 17, 65535, 0x1ffff, 18, 64,
  floatformat_intbit_yes,
  "floatformat_ia64_spill_big",
  floatformat_always_valid
};
const struct floatformat floatformat_ia64_spill_little =
{
  floatformat_little, 128, 0, 1, 17, 65535, 0x1ffff, 18, 64,
  floatformat_intbit_yes,
  "floatformat_ia64_spill_little",
  floatformat_always_valid
};
const struct floatformat floatformat_ia64_quad_big =
{
  floatformat_big, 128, 0, 1, 15, 16383, 0x7fff, 16, 112,
  floatformat_intbit_no,
  "floatformat_ia64_quad_big",
  floatformat_always_valid
};
const struct floatformat floatformat_ia64_quad_little =
{
  floatformat_little, 128, 0, 1, 15, 16383, 0x7fff, 16, 112,
  floatformat_intbit_no,
  "floatformat_ia64_quad_little",
  floatformat_always_valid
};

/* Extract a field which starts at START and is LEN bits long.  DATA and
   TOTAL_LEN are the thing we are extracting it from, in byteorder ORDER.  */
static unsigned long
get_field (const unsigned char *data, enum floatformat_byteorders order,
           unsigned int total_len, unsigned int start, unsigned int len)
{
  unsigned long result;
  unsigned int cur_byte;
  int cur_bitshift;

  /* Start at the least significant part of the field.  */
  cur_byte = (start + len) / FLOATFORMAT_CHAR_BIT;
  if (order == floatformat_little)
    cur_byte = (total_len / FLOATFORMAT_CHAR_BIT) - cur_byte - 1;
  cur_bitshift =
    ((start + len) % FLOATFORMAT_CHAR_BIT) - FLOATFORMAT_CHAR_BIT;
  result = *(data + cur_byte) >> (-cur_bitshift);
  cur_bitshift += FLOATFORMAT_CHAR_BIT;
  if (order == floatformat_little)
    ++cur_byte;
  else
    --cur_byte;

  /* Move towards the most significant part of the field.  */
  while ((unsigned int) cur_bitshift < len)
    {
      if (len - cur_bitshift < FLOATFORMAT_CHAR_BIT)
	/* This is the last byte; zero out the bits which are not part of
	   this field.  */
	result |=
	  (unsigned long)(*(data + cur_byte)
			  & ((1 << (len - cur_bitshift)) - 1))
	    << cur_bitshift;
      else
	result |= (unsigned long)*(data + cur_byte) << cur_bitshift;
      cur_bitshift += FLOATFORMAT_CHAR_BIT;
      if (order == floatformat_little)
	++cur_byte;
      else
	--cur_byte;
    }
  return result;
}

/* Convert from FMT to a double.
   FROM is the address of the extended float.
   Store the double in *TO.  */

void
floatformat_to_double (const struct floatformat *fmt,
                       const char *from, double *to)
{
  const unsigned char *ufrom = (const unsigned char *)from;
  double dto;
  long exponent;
  unsigned long mant;
  unsigned int mant_bits, mant_off;
  int mant_bits_left;
  int special_exponent;		/* It's a NaN, denorm or zero */

  exponent = get_field (ufrom, fmt->byteorder, fmt->totalsize,
			fmt->exp_start, fmt->exp_len);

  /* If the exponent indicates a NaN, we don't have information to
     decide what to do.  So we handle it like IEEE, except that we
     don't try to preserve the type of NaN.  FIXME.  */
  if ((unsigned long) exponent == fmt->exp_nan)
    {
      int nan;

      mant_off = fmt->man_start;
      mant_bits_left = fmt->man_len;
      nan = 0;
      while (mant_bits_left > 0)
	{
          mant_bits = MIN(mant_bits_left, 32);

	  if (get_field (ufrom, fmt->byteorder, fmt->totalsize,
			 mant_off, mant_bits) != 0)
	    {
	      /* This is a NaN.  */
	      nan = 1;
	      break;
	    }

	  mant_off += mant_bits;
	  mant_bits_left -= mant_bits;
	}

      /* On certain systems (such as GNU/Linux), the use of the
	 INFINITY macro below may generate a warning that can not be
	 silenced due to a bug in GCC (PR preprocessor/11931).  The
	 preprocessor fails to recognise the __extension__ keyword in
	 conjunction with the GNU/C99 extension for hexadecimal
	 floating point constants and will issue a warning when
	 compiling with -pedantic.  */
      if (nan)
	dto = NAN;
      else
	dto = INFINITY;

      if (get_field (ufrom, fmt->byteorder, fmt->totalsize, fmt->sign_start, 1))
	dto = -dto;

      *to = dto;

      return;
    }

  mant_bits_left = fmt->man_len;
  mant_off = fmt->man_start;
  dto = 0.0;

  special_exponent = exponent == 0 || (unsigned long) exponent == fmt->exp_nan;

  /* Don't bias zero's, denorms or NaNs.  */
  if (!special_exponent)
    exponent -= fmt->exp_bias;

  /* Build the result algebraically.  Might go infinite, underflow, etc;
     who cares. */

  /* If this format uses a hidden bit, explicitly add it in now.  Otherwise,
     increment the exponent by one to account for the integer bit.  */

  if (!special_exponent)
    {
      if (fmt->intbit == floatformat_intbit_no)
	dto = ldexp (1.0, exponent);
      else
	exponent++;
    }

  while (mant_bits_left > 0)
    {
      mant_bits = MIN(mant_bits_left, 32);

      mant = get_field (ufrom, fmt->byteorder, fmt->totalsize,
			 mant_off, mant_bits);

      /* Handle denormalized numbers.  FIXME: What should we do for
	 non-IEEE formats?  */
      if (exponent == 0 && mant != 0)
	dto += ldexp ((double)mant,
		      (- fmt->exp_bias
		       - mant_bits
		       - (mant_off - fmt->man_start)
		       + 1));
      else
	dto += ldexp ((double)mant, exponent - mant_bits);
      if (exponent != 0)
	exponent -= mant_bits;
      mant_off += mant_bits;
      mant_bits_left -= mant_bits;
    }

  /* Negate it if negative.  */
  if (get_field (ufrom, fmt->byteorder, fmt->totalsize, fmt->sign_start, 1))
    dto = -dto;
  *to = dto;
}

static void put_field (unsigned char *, enum floatformat_byteorders,
                       unsigned int,
                       unsigned int,
                       unsigned int,
                       unsigned long);

/* Set a field which starts at START and is LEN bits long.  DATA and
   TOTAL_LEN are the thing we are extracting it from, in byteorder ORDER.  */
static void
put_field (unsigned char *data, enum floatformat_byteorders order,
           unsigned int total_len, unsigned int start, unsigned int len,
           unsigned long stuff_to_put)
{
  unsigned int cur_byte;
  int cur_bitshift;

  /* Start at the least significant part of the field.  */
  cur_byte = (start + len) / FLOATFORMAT_CHAR_BIT;
  if (order == floatformat_little)
    cur_byte = (total_len / FLOATFORMAT_CHAR_BIT) - cur_byte - 1;
  cur_bitshift =
    ((start + len) % FLOATFORMAT_CHAR_BIT) - FLOATFORMAT_CHAR_BIT;
  *(data + cur_byte) &=
    ~(((1 << ((start + len) % FLOATFORMAT_CHAR_BIT)) - 1) << (-cur_bitshift));
  *(data + cur_byte) |=
    (stuff_to_put & ((1 << FLOATFORMAT_CHAR_BIT) - 1)) << (-cur_bitshift);
  cur_bitshift += FLOATFORMAT_CHAR_BIT;
  if (order == floatformat_little)
    ++cur_byte;
  else
    --cur_byte;

  /* Move towards the most significant part of the field.  */
  while ((unsigned int) cur_bitshift < len)
    {
      if (len - cur_bitshift < FLOATFORMAT_CHAR_BIT)
	{
	  /* This is the last byte.  */
	  *(data + cur_byte) &=
	    ~((1 << (len - cur_bitshift)) - 1);
	  *(data + cur_byte) |= (stuff_to_put >> cur_bitshift);
	}
      else
	*(data + cur_byte) = ((stuff_to_put >> cur_bitshift)
			      & ((1 << FLOATFORMAT_CHAR_BIT) - 1));
      cur_bitshift += FLOATFORMAT_CHAR_BIT;
      if (order == floatformat_little)
	++cur_byte;
      else
	--cur_byte;
    }
}

/* The converse: convert the double *FROM to an extended float
   and store where TO points.  Neither FROM nor TO have any alignment
   restrictions.  */

void
floatformat_from_double (const struct floatformat *fmt,
                         const double *from, char *to)
{
  double dfrom;
  int exponent;
  double mant;
  unsigned int mant_bits, mant_off;
  int mant_bits_left;
  unsigned char *uto = (unsigned char *)to;

  dfrom = *from;
  memset (uto, 0, fmt->totalsize / FLOATFORMAT_CHAR_BIT);

  /* If negative, set the sign bit.  */
  if (dfrom < 0)
    {
      put_field (uto, fmt->byteorder, fmt->totalsize, fmt->sign_start, 1, 1);
      dfrom = -dfrom;
    }

  if (dfrom == 0)
    {
      /* 0.0.  */
      return;
    }

  if (dfrom != dfrom)
    {
      /* NaN.  */
      put_field (uto, fmt->byteorder, fmt->totalsize, fmt->exp_start,
		 fmt->exp_len, fmt->exp_nan);
      /* Be sure it's not infinity, but NaN value is irrelevant.  */
      put_field (uto, fmt->byteorder, fmt->totalsize, fmt->man_start,
		 32, 1);
      return;
    }

  if (dfrom + dfrom == dfrom)
    {
      /* This can only happen for an infinite value (or zero, which we
	 already handled above).  */
      put_field (uto, fmt->byteorder, fmt->totalsize, fmt->exp_start,
		 fmt->exp_len, fmt->exp_nan);
      return;
    }

  mant = frexp (dfrom, &exponent);
  if (exponent + fmt->exp_bias - 1 > 0)
    put_field (uto, fmt->byteorder, fmt->totalsize, fmt->exp_start,
	       fmt->exp_len, exponent + fmt->exp_bias - 1);
  else
    {
      /* Handle a denormalized number.  FIXME: What should we do for
	 non-IEEE formats?  */
      put_field (uto, fmt->byteorder, fmt->totalsize, fmt->exp_start,
		 fmt->exp_len, 0);
      mant = ldexp (mant, exponent + fmt->exp_bias - 1);
    }

  mant_bits_left = fmt->man_len;
  mant_off = fmt->man_start;
  while (mant_bits_left > 0)
    {
      unsigned long mant_long;
      mant_bits = mant_bits_left < 32 ? mant_bits_left : 32;

      mant *= 4294967296.0;
      mant_long = (unsigned long)mant;
      mant -= mant_long;

      /* If the integer bit is implicit, and we are not creating a
	 denormalized number, then we need to discard it.  */
      if ((unsigned int) mant_bits_left == fmt->man_len
	  && fmt->intbit == floatformat_intbit_no
	  && exponent + fmt->exp_bias - 1 > 0)
	{
	  mant_long &= 0x7fffffff;
	  mant_bits -= 1;
	}
      else if (mant_bits < 32)
	{
	  /* The bits we want are in the most significant MANT_BITS bits of
	     mant_long.  Move them to the least significant.  */
	  mant_long >>= 32 - mant_bits;
	}

      put_field (uto, fmt->byteorder, fmt->totalsize,
		 mant_off, mant_bits, mant_long);
      mant_off += mant_bits;
      mant_bits_left -= mant_bits;
    }
}

/* Return non-zero iff the data at FROM is a valid number in format FMT.  */

int
floatformat_is_valid (const struct floatformat *fmt, const char *from)
{
  return fmt->is_valid (fmt, from);
}


#ifdef IEEE_DEBUG

/* This is to be run on a host which uses IEEE floating point.  */

void
ieee_test (double n)
{
  double result;

  floatformat_to_double (&floatformat_ieee_double_little, (char *) &n,
			 &result);
  if ((n != result && (! isnan (n) || ! isnan (result)))
      || (n < 0 && result >= 0)
      || (n >= 0 && result < 0))
    printf ("Differ(to): %.20g -> %.20g\n", n, result);

  floatformat_from_double (&floatformat_ieee_double_little, &n,
			   (char *) &result);
  if ((n != result && (! isnan (n) || ! isnan (result)))
      || (n < 0 && result >= 0)
      || (n >= 0 && result < 0))
    printf ("Differ(from): %.20g -> %.20g\n", n, result);

#if 0
  {
    char exten[16];

    floatformat_from_double (&floatformat_m68881_ext, &n, exten);
    floatformat_to_double (&floatformat_m68881_ext, exten, &result);
    if (n != result)
      printf ("Differ(to+from): %.20g -> %.20g\n", n, result);
  }
#endif

#if IEEE_DEBUG > 1
  /* This is to be run on a host which uses 68881 format.  */
  {
    long double ex = *(long double *)exten;
    if (ex != n)
      printf ("Differ(from vs. extended): %.20g\n", n);
  }
#endif
}

int
main (void)
{
  ieee_test (0.0);
  ieee_test (0.5);
  ieee_test (256.0);
  ieee_test (0.12345);
  ieee_test (234235.78907234);
  ieee_test (-512.0);
  ieee_test (-0.004321);
  ieee_test (1.2E-70);
  ieee_test (1.2E-316);
  ieee_test (4.9406564584124654E-324);
  ieee_test (- 4.9406564584124654E-324);
  ieee_test (- 0.0);
  ieee_test (- INFINITY);
  ieee_test (- NAN);
  ieee_test (INFINITY);
  ieee_test (NAN);
  return 0;
}
#endif
/* **** End of floatformat.c  */
