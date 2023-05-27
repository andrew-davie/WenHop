#ifndef __ATARIVOX_H
#define __ATARIVOX_H

#if _ENABLE_ATARIVOX

extern void sayWord(int word);
extern void processSpeech();

#define SAY(word) sayWord(word)

#else

#define SAY(word)

#endif

#endif
