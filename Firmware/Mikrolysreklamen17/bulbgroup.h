/*
 * bulbgroup.h
 *
 * Created: 2019-01-27 15:07:12
 *  Author: Oystein
 */ 


#ifndef BULBGROUP_H_
#define BULBGROUP_H_

#include <avr/io.h>

uint8_t allBulbs[83] = {82, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
							20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,
							40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,
							60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,
							80,81};

uint8_t letter_A[13] = {12, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
uint8_t letter_B[8] = {7, 12, 13, 14, 15, 16, 17, 18};
uint8_t letter_C[3] = {2, 19, 20};
uint8_t letter_D[15] = {14, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34};
uint8_t letter_E[11] = {10, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44};
uint8_t letter_F[3] = {2, 45, 46};
uint8_t letter_G[15] = {14, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60};
uint8_t letter_H[11] = {10, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70};
uint8_t letter_I[12] = {11, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81};
uint8_t numletters = 9;
uint8_t* letters[10] = {&numletters, &letter_A, &letter_B, &letter_C, &letter_D, &letter_E, &letter_F, &letter_G, &letter_H, &letter_I};

uint8_t digit_A[8] = {7, 0, 1, 2, 3, 4, 5, 6};
uint8_t digit_B[11] = {10, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34};
uint8_t digit_C[11] = {10, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60};
uint8_t numdigits = 3;
uint8_t* digits[4] = {&numdigits, &digit_A, &digit_B, &digit_C};

uint8_t col_01[2] = {1, 5};
uint8_t col_02[4] = {3, 0, 2, 4};
uint8_t col_03[4] = {3, 1, 3, 6};
uint8_t col_04[5] = {4, 7, 8, 9, 10};
uint8_t col_05[3] = {2, 11, 12};
uint8_t col_06[3] = {2, 14, 15};
uint8_t col_07[3] = {2, 12, 17};
uint8_t col_08[2] = {1, 16};
uint8_t col_09[2] = {1, 13};
uint8_t col_10[3] = {2, 19, 20};
uint8_t col_11[5] = {4, 21, 22, 23, 24};
uint8_t col_12[7] = {6, 25, 26, 27, 28, 29, 30};
uint8_t col_13[3] = {2, 31, 34};
uint8_t col_14[3] = {2, 32, 33};
uint8_t col_15[5] = {4, 35, 36, 37, 38}; //TBD
uint8_t col_16[5] = {4, 39, 40, 41, 42}; //TBD
uint8_t col_17[3] = {3, 43, 44}; // TBD
uint8_t col_18[3] = {3, 45, 46};
uint8_t col_19[5] = {4, 47, 48, 49, 50};
uint8_t col_20[7] = {6, 51, 52, 53, 54, 55, 56};
uint8_t col_21[3] = {2, 57, 60};
uint8_t col_22[3] = {2, 58, 59};
uint8_t col_23[4] = {3, 61, 62, 63};
uint8_t col_24[4] = {3, 68, 69, 70};
uint8_t col_25[2] = {1, 64}; // check
uint8_t col_26[4] = {3, 65, 66, 67};
uint8_t col_27[6] = {5, 71, 72, 73, 74, 75};
uint8_t col_28[2] = {1, 81};
uint8_t col_29[6] = {5, 76, 77, 78, 79, 80};
uint8_t numcols = 29;
uint8_t *columns[] = {&numcols, col_01, col_02, col_03, col_04, col_05, col_06, col_07, col_08, col_09,
						col_10, col_11, col_12, col_13, col_14, col_15, col_16, col_17, col_18, col_19,
						col_20,	col_21, col_22, col_23, col_24, col_25, col_26, col_27, col_28, col_29};


#endif /* BULBGROUP_H_ */