#ifndef __SCORE_H
#define __SCORE_H

#define DIGIT_SIZE 20 /* displayed lines */
#define SCOREVISIBLETIME                                                                           \
    150 /* # frames to show changed scoreline item before reverting to defaults */

#define DIGIT_SPACE (DIGIT_ALPHABET + 26)

#define DIGIT_PLUS 10
#define DIGIT_DOGE 11
#define DIGIT_CAVE 18
#define DIGIT_LEVEL 25
#define DIGIT_ALPHABET 12

#define IDLE_TIME 30

enum SCORE_MODE {
    SCORELINE_CAVELEVEL,
    SCORELINE_SPEEDRUN,
    SCORELINE_LIVES,
    SCORELINE_START,
    SCORELINE_TIME = SCORELINE_START,
    SCORELINE_SCORE,
    SCORELINE_END,
};

#define LETTER(a) ((a) - 'A' + DIGIT_ALPHABET)

extern enum SCORE_MODE scoreCycle;
extern unsigned char timeString[];

extern int actualScore;
extern int partialScore;

void drawBigDigit(int digit, int pos, int offset, int colour, bool tape);
void drawLives();
void drawTheScore(int score);
void drawScore();
void addScore(int score);
void setScoreCycle(enum SCORE_MODE scoreCycle);
enum SCORE_MODE getScoreCycle();
void setScore(int score);
void drawTime2(int value);
void doubleSizeScore(int x, int y, int letter, int col);
unsigned char *drawDecimal2(unsigned char *buffer, unsigned char *colour_buffer,
                            unsigned int colour, int cvt);

#endif