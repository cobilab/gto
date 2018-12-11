#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#include <stdint.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#if defined(_MSC_VER)
  #include <io.h>
#else
  #include <unistd.h>
#endif

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// ATTENTION: UNCOMMENT ONLY ONE!!!
//#define PREC32B // UNCOMMENT: CONTEXTS UP TO 28 (IT WILL USE HIGH MEMORY!)
#define PREC16B // UNCOMMENT: CONTEXTS UP TO 20 (IT WILL USE MEDIUM MEMORY!)

//#THE FOLLOWING IS AN UNTESTED VERSION: 
//#define PREC8B  // UNCOMMENT: CONTEXTS UP TO 16 (IT WILL USE LOW MEMORY!)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef uint64_t ULL;
typedef uint64_t U64;
typedef uint32_t U32;
typedef uint16_t U16;
typedef uint8_t  U8;
typedef int64_t  I64;
typedef int32_t  I32;
typedef int16_t  I16;
typedef int8_t   I8;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define RELEASE                1
#define VERSION                1

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define DEF_VERSION            0
#define DEF_EXAMPLE            0
#define DEFAULT_HELP           0
#define DEFAULT_VERBOSE        0
#define DEFAULT_FORCE          0
#define DEFAULT_LEVEL          15
#define DEFAULT_INDEX          2
#define DEFAULT_THREADS        2
#define DEFAULT_FILTERSIZE     500
#define DEFAULT_MINBLOCK       100
#define DEFAULT_SAMPLE         1
#define DEFAULT_IR             0
#define DEFAULT_CTX            13
#define DEFAULT_GAMMA          0.90
#define DEFAULT_THRESHOLD      1.85
#define DEFAULT_SUBSAMPLE      -1
#define DEFAULT_SAMPLE_RATIO   50000 // 10000
#define DEFAULT_MAX_COUNT      ((1 << (sizeof(ACC) * 8)) - 1)

#define MIN_SAP                1
#define MAX_SAP                99999999
#define MAX_LEV                44
#define MIN_LEV                1
#define DEF_TOP                20
#define MIN_TOP                1
#define MAX_TOP                99999999
#define MAX_NAME               5000
#define MIN_THREADS            1
#define MAX_THREADS            65535
#define MAX_CTX                31
#define MIN_CTX                1
#define MAX_DEN                1000000
#define MIN_DEN                1
#define MIN_INDEX              2
#define MAX_HISTORYSIZE        1000000
#define MAX_STR                2048
#define MAX_ALPHABET           256
#define MAX_LABEL              1024

#define EXTRA_MOD_DEN          1
#define EXTRA_MOD_CTX          3
#define EXTRA_BIN_DEN          1
#define EXTRA_BIN_CTX          8
#define EXTRA_N_DEN            1
#define EXTRA_N_CTX            8
#define EXTRA_L_DEN            1
#define EXTRA_L_CTX            8

#define BGUARD                 32
#define MX_PMODEL              65535
#define ALPHABET_SIZE          4
#define CHECKSUMGF             1073741824
#define WATERMARK              16042014
#define REFERENCE              1
#define TARGET                 0

#define BUFFER_SIZE            65535
#define BUFFER_SIZE_WS         512
#define PROGRESS_MIN           1000000
#define MATCH_SYMBOL           48 //88
#define UNIQUE_SYMBOL          49 //45
#define N_SYMBOL               78 //'N'
#define NO_MATCH_REGION        0             
#define MATCHED_REGION         1               

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

uint32_t garbage;

#endif

