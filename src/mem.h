#ifndef MEM_H_INCLUDED
#define MEM_H_INCLUDED

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void     *Malloc          (size_t);
void     *Calloc          (size_t, size_t);
void     *Realloc         (void *, size_t, size_t);
void     Free             (void *, size_t);
void     RemovePiece      (size_t);
size_t   CurrMem          (void);
size_t   PeakMem          (void);
void     RestartPeak      (void);
void     RestartPeakAndRS (void);
void     PrintHRBytes     (int64_t);
void     PrintCurrMem     (void);
void     PrintRAM         (int64_t);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#endif

