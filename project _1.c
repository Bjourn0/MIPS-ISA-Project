/* 
Class Project: The logical conclusion
CSCI-2500 Spring 2023
Prof. Slota 
*/

/******************************************************************************/
/* Usual suspects to include  */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define BIT type as a char (i.e., one byte)
typedef char BIT;
#define TRUE 1
#define FALSE 0
#define UNDEF -1

// useful constants
BIT ONE[32] = {TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE};
BIT ZERO[32] = {FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE};
BIT REG_THIRTY_ONE[5] = {TRUE, TRUE, TRUE, TRUE, TRUE};
BIT THIRTY_TWO[32] = {FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, 
  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE};


/******************************************************************************/
/* Function prototypes */
/******************************************************************************/
BIT not_gate(BIT A);
BIT or_gate(BIT A, BIT B);
BIT or_gate3(BIT A, BIT B, BIT C);
BIT and_gate(BIT A, BIT B);
BIT and_gate3(BIT A, BIT B, BIT C);
BIT xor_gate(BIT A, BIT B);
BIT nor_gate(BIT A, BIT B);
BIT nand_gate(BIT A, BIT B);

void decoder2(BIT I0, BIT I1, BIT* O0, BIT* O1, BIT* O2, BIT* O3);
BIT multiplexor2(BIT S, BIT I0, BIT I1);
void multiplexor2_32(BIT S, BIT* I0, BIT* I1, BIT* Output);
BIT multiplexor4(BIT S0, BIT S1, BIT I0, BIT I1, BIT I2, BIT I3);

void copy_bits(BIT* A, BIT* B);
void print_binary(BIT* A);
void convert_to_binary(int a, BIT* A, int length);
void convert_to_binary_char(int a, char* A, int length);
int binary_to_integer(BIT* A);

int get_instructions(BIT Instructions[][32]);

void Instruction_Memory(BIT* ReadAddress, BIT* Instruction);
void Control(BIT* OpCode, BIT* RegDst, BIT* Jump, BIT* Branch, BIT* MemRead, BIT* MemToReg,
  BIT* ALUOp, BIT* MemWrite, BIT* ALUSrc, BIT* RegWrite);
void Read_Register(BIT* ReadRegister1, BIT* ReadRegister2,
  BIT* ReadData1, BIT* ReadData2);
void Write_Register(BIT RegWrite, BIT* WriteRegister, BIT* WriteData);
void ALU_Control(BIT* ALUOp, BIT* funct, BIT* ALUControl);
void ALU(BIT* ALUControl, BIT* Input1, BIT* Input2, BIT* Zero, BIT* Result);
void Data_Memory(BIT MemWrite, BIT MemRead, 
  BIT* Address, BIT* WriteData, BIT* ReadData);
void Extend_Sign16(BIT* Input, BIT* Output);
void updateState();
  
/******************************************************************************/
/* Functions provided for your convenience */
/******************************************************************************/
BIT not_gate(BIT A)
{
  return (!A);
}

BIT or_gate(BIT A, BIT B)
{
  return (A || B);
}

BIT or_gate3(BIT A, BIT B, BIT C)
{
  return or_gate(A, or_gate(B, C));
}

// ***Abdul ALU_Control Helper Function***
BIT or_gate8(BIT A, BIT B, BIT C, BIT D, BIT E, BIT F, BIT G, BIT H) 
{
   BIT result = or_gate(A, B);
   result = or_gate(result, C);
   result = or_gate(result, D);
   result = or_gate(result, E);
   result = or_gate(result, F);
   result = or_gate(result, G);
   result = or_gate(result, H);
   return result;
}

//***Our Addition***
BIT or_gate32(BIT I0, BIT I1, BIT I2, BIT I3, BIT I4, BIT I5, BIT I6, BIT I7, BIT I8, 
  BIT I9, BIT I10, BIT I11, BIT I12, BIT I13, BIT I14, BIT I15, BIT I16, BIT I17, BIT I18, 
  BIT I19, BIT I20, BIT I21, BIT I22, BIT I23, BIT I24, BIT I25, BIT I26, BIT I27, 
  BIT I28, BIT I29, BIT I30, BIT I31)
{
  BIT result = or_gate(I0, I1);
  result = or_gate(result, I2);
  result = or_gate(result, I3);
  result = or_gate(result, I4);
  result = or_gate(result, I5);
  result = or_gate(result, I6);
  result = or_gate(result, I7);
  result = or_gate(result, I8);
  result = or_gate(result, I9);
  result = or_gate(result, I10);
  result = or_gate(result, I11);
  result = or_gate(result, I12);
  result = or_gate(result, I13);
  result = or_gate(result, I14);
  result = or_gate(result, I15);
  result = or_gate(result, I16);
  result = or_gate(result, I17);
  result = or_gate(result, I18);
  result = or_gate(result, I19);
  result = or_gate(result, I20);
  result = or_gate(result, I21);
  result = or_gate(result, I22);
  result = or_gate(result, I23);
  result = or_gate(result, I24);
  result = or_gate(result, I25);
  result = or_gate(result, I26);
  result = or_gate(result, I27);
  result = or_gate(result, I28);
  result = or_gate(result, I29);
  result = or_gate(result, I30);
  result = or_gate(result, I31);
  return result;
}

//***Our Addition***
BIT or_gate64(BIT I0, BIT I1, BIT I2, BIT I3, BIT I4, BIT I5, BIT I6, BIT I7, BIT I8, 
  BIT I9, BIT I10, BIT I11, BIT I12, BIT I13, BIT I14, BIT I15, BIT I16, BIT I17, BIT I18, 
  BIT I19, BIT I20, BIT I21, BIT I22, BIT I23, BIT I24, BIT I25, BIT I26, BIT I27, 
  BIT I28, BIT I29, BIT I30, BIT I31, BIT I32, BIT I33, BIT I34, BIT I35, BIT I36, BIT I37, 
  BIT I38, BIT I39, BIT I40, BIT I41, BIT I42, BIT I43, BIT I44, BIT I45, BIT I46, BIT I47, 
  BIT I48, BIT I49, BIT I50, BIT I51, BIT I52, BIT I53, BIT I54, BIT I55, BIT I56, BIT I57, 
  BIT I58, BIT I59, BIT I60, BIT I61, BIT I62, BIT I63) 
{
  BIT result = or_gate(I0, I1);
  result = or_gate(result, I2);
  result = or_gate(result, I3);
  result = or_gate(result, I4);
  result = or_gate(result, I5);
  result = or_gate(result, I6);
  result = or_gate(result, I7);
  result = or_gate(result, I8);
  result = or_gate(result, I9);
  result = or_gate(result, I10);
  result = or_gate(result, I11);
  result = or_gate(result, I12);
  result = or_gate(result, I13);
  result = or_gate(result, I14);
  result = or_gate(result, I15);
  result = or_gate(result, I16);
  result = or_gate(result, I17);
  result = or_gate(result, I18);
  result = or_gate(result, I19);
  result = or_gate(result, I20);
  result = or_gate(result, I21);
  result = or_gate(result, I22);
  result = or_gate(result, I23);
  result = or_gate(result, I24);
  result = or_gate(result, I25);
  result = or_gate(result, I26);
  result = or_gate(result, I27);
  result = or_gate(result, I28);
  result = or_gate(result, I29);
  result = or_gate(result, I30);
  result = or_gate(result, I31);
  result = or_gate(result, I32);
  result = or_gate(result, I33);
  result = or_gate(result, I34);
  result = or_gate(result, I35);
  result = or_gate(result, I36);
  result = or_gate(result, I37);
  result = or_gate(result, I38);
  result = or_gate(result, I39);
  result = or_gate(result, I40);
  result = or_gate(result, I41);
  result = or_gate(result, I42);
  result = or_gate(result, I43);
  result = or_gate(result, I44);
  result = or_gate(result, I45);
  result = or_gate(result, I46);
  result = or_gate(result, I47);
  result = or_gate(result, I48);
  result = or_gate(result, I49);
  result = or_gate(result, I50);
  result = or_gate(result, I51);
  result = or_gate(result, I52);
  result = or_gate(result, I53);
  result = or_gate(result, I54);
  result = or_gate(result, I55);
  result = or_gate(result, I56);
  result = or_gate(result, I57);
  result = or_gate(result, I58);
  result = or_gate(result, I59);
  result = or_gate(result, I60);
  result = or_gate(result, I61);
  result = or_gate(result, I62);
  result = or_gate(result, I63);
  return result;
}

BIT and_gate(BIT A, BIT B)
{
  return (A && B);
}

BIT and_gate3(BIT A, BIT B, BIT C)
{
  return and_gate(A, and_gate(B, C));
}

// ***Abdul ALU_Control Helper Function***
BIT and_gate4(BIT A, BIT B, BIT C, BIT D) 
{
   BIT result = and_gate(A, B);
   result = and_gate(result, C);
   result = and_gate(result, D);
   return result;
}

// ***Our Addition***
BIT and_gate6(BIT A, BIT B, BIT C, BIT D, BIT E, BIT F)
{
   BIT G = and_gate3(A, B, C);
   BIT H = and_gate3(D, E, F);
  return and_gate(G,H);
}

// ***Our addition***
BIT and_gate7(BIT A, BIT B, BIT C, BIT D, BIT E, BIT F, BIT G) 
{
   BIT result = and_gate(A, B);
   result = and_gate(result, C);
   result = and_gate(result, D);
   result = and_gate(result, E);
   result = and_gate(result, F);
   result = and_gate(result, G);
   return result;
}

BIT xor_gate(BIT A, BIT B)
{
  BIT nA = not_gate(A);
  BIT nB = not_gate(B);
  BIT x0 = and_gate(A, nB);
  BIT x1 = and_gate(nA, B);
  return or_gate(x0, x1);
}

BIT nor_gate(BIT A, BIT B)
{
  return not_gate(or_gate(A, B));
}

BIT nand_gate(BIT A, BIT B)
{
  return not_gate(and_gate(A, B));
}

void decoder2(BIT I0, BIT I1, BIT* O0, BIT* O1, BIT* O2, BIT* O3)
{
  BIT nI1 = not_gate(I1);
  BIT nI0 = not_gate(I0);
  *O0 = and_gate(nI1, nI0);
  *O1 = and_gate(nI1, I0);
  *O2 = and_gate(I1, nI0);
  *O3 = and_gate(I1,  I0);
  
  return;
}

//***Our Addition from Lab 6***
void decoder3(BIT* I, BIT EN, BIT* O)
{
  O[0] = and_gate3(not_gate(I[2]), not_gate(I[1]), not_gate(I[0]));
  O[1] = and_gate3(not_gate(I[2]), not_gate(I[1]), I[0]);
  O[2] = and_gate3(not_gate(I[2]), I[1], not_gate(I[0]));
  O[3] = and_gate3(not_gate(I[2]), I[1], I[0]);
  O[4] = and_gate3(I[2], not_gate(I[1]), not_gate(I[0]));
  O[5] = and_gate3(I[2], not_gate(I[1]), I[0]);
  O[6] = and_gate3(I[2], I[1], not_gate(I[0]));
  O[7] = and_gate3(I[2], I[1], I[0]);
  
  for (int i = 0; i < 8; ++i)
    O[i] = and_gate(EN, O[i]);
  
  return;
}

// ***Our Addition***
void decoder5(BIT* I, BIT EN, BIT* O)
{
   BIT EN_0 = {FALSE};
   BIT EN_1 = {FALSE};
   BIT EN_2 = {FALSE};
   BIT EN_3 = {FALSE};
   decoder2(I[3],I[4], &EN_0, &EN_1, &EN_2, &EN_3);
   decoder3(I, EN_3, &O[24]);
   decoder3(I, EN_2, &O[16]);
   decoder3(I, EN_1, &O[8]);
   decoder3(I, EN_0, &O[0]);
   for (int i = 0; i < 32; ++i)
      O[i] = and_gate(EN, O[i]); 
}

BIT multiplexor2(BIT S, BIT I0, BIT I1)
{
  BIT nS = not_gate(S);
  BIT x0 = and_gate(nS, I0);
  BIT x1 = and_gate(S,  I1);
  return or_gate(x0, x1);
}

void multiplexor2_32(BIT S, BIT* I0, BIT* I1, BIT* Output)
{
  for (int i = 0; i < 32; ++i) {
    BIT nS = not_gate(S);
    BIT x0 = and_gate(nS, I0[i]);
    BIT x1 = and_gate(S, I1[i]);
    Output[i] = or_gate(x0, x1);
  }
}

BIT multiplexor4(BIT S0, BIT S1, BIT I0, BIT I1, BIT I2, BIT I3)
{
  BIT x0, x1, x2, x3 = FALSE;
  decoder2(S0, S1, &x0, &x1, &x2, &x3);
  
  BIT y0 = and_gate(x0, I0);
  BIT y1 = and_gate(x1, I1);
  BIT y2 = and_gate(x2, I2);
  BIT y3 = and_gate(x3, I3);
  
  BIT z0 = or_gate(y0, y1);
  BIT z1 = or_gate(y2, y3);
  
  return or_gate(z0, z1);
}

//***Abdul ALU_Control Helper Function***
BIT multiplexor8(BIT S0, BIT S1, BIT S2, BIT I0, BIT I1, BIT I2, 
  BIT I3, BIT I4, BIT I5, BIT I6, BIT I7) 
{
   BIT result1 = and_gate4(not_gate(S0), not_gate(S1), not_gate(S2), I0);
   
   BIT result2 = and_gate4(S0, not_gate(S1), not_gate(S2), I1);
   
   BIT result3 = and_gate4(not_gate(S0), S1, not_gate(S2), I2);
   
   BIT result4 = and_gate4(S0, S1, not_gate(S2), I3);
   
   BIT result5 = and_gate4(not_gate(S0), not_gate(S1), S2, I4);
   
   BIT result6 = and_gate4(S0, not_gate(S1), S2, I5);
   
   BIT result7 = and_gate4(not_gate(S0), S1, S2, I6);
   
   BIT result8 = and_gate4(S0, S1, S2, I7);
   
   BIT result = or_gate8(result1, result2, result3, result4, result5, result6, result7, result8);
   return result;
}

//***Our Addition***
BIT multiplexor64(BIT S0, BIT S1, BIT S2, BIT S3, BIT S4, BIT S5, BIT I0, BIT I1, BIT I2, 
  BIT I3, BIT I4, BIT I5, BIT I6, BIT I7, BIT I8, BIT I9, BIT I10, BIT I11, BIT I12, 
  BIT I13, BIT I14, BIT I15, BIT I16, BIT I17, BIT I18, BIT I19, BIT I20, BIT I21, BIT I22, 
  BIT I23, BIT I24, BIT I25, BIT I26, BIT I27, BIT I28, BIT I29, BIT I30, BIT I31, BIT I32, 
  BIT I33, BIT I34, BIT I35, BIT I36, BIT I37, BIT I38, BIT I39, BIT I40, BIT I41, BIT I42, 
  BIT I43, BIT I44, BIT I45, BIT I46, BIT I47, BIT I48, BIT I49, BIT I50, BIT I51, BIT I52, 
  BIT I53, BIT I54, BIT I55, BIT I56, BIT I57, BIT I58, BIT I59, BIT I60, BIT I61, BIT I62, 
  BIT I63) {
  BIT result0 = and_gate7(not_gate(S0), not_gate(S1), not_gate(S2), not_gate(S3), not_gate(S4), not_gate(S5), I0);

  BIT result1 = and_gate7(S0, not_gate(S1), not_gate(S2), not_gate(S3), not_gate(S4), not_gate(S5), I1);

  BIT result2 = and_gate7(not_gate(S0), S1, not_gate(S2), not_gate(S3), not_gate(S4), not_gate(S5), I2);

  BIT result3 = and_gate7(S0, S1, not_gate(S2), not_gate(S3), not_gate(S4), not_gate(S5), I3);

  BIT result4 = and_gate7(not_gate(S0), not_gate(S1), S2, not_gate(S3), not_gate(S4), not_gate(S5), I4);

  BIT result5 = and_gate7(S0, not_gate(S1), S2, not_gate(S3), not_gate(S4), not_gate(S5), I5);

  BIT result6 = and_gate7(not_gate(S0), S1, S2, not_gate(S3), not_gate(S4), not_gate(S5), I6);

  BIT result7 = and_gate7(S0, S1, S2, not_gate(S3), not_gate(S4), not_gate(S5), I7);

  BIT result8 = and_gate7(not_gate(S0), not_gate(S1), not_gate(S2), S3, not_gate(S4), not_gate(S5), I8);

  BIT result9 = and_gate7(S0, not_gate(S1), not_gate(S2), S3, not_gate(S4), not_gate(S5), I9);

  BIT result10 = and_gate7(not_gate(S0), S1, not_gate(S2), S3, not_gate(S4), not_gate(S5), I10);

  BIT result11 = and_gate7(S0, S1, not_gate(S2), S3, not_gate(S4), not_gate(S5), I11);

  BIT result12 = and_gate7(not_gate(S0), not_gate(S1), S2, S3, not_gate(S4), not_gate(S5), I12);

  BIT result13 = and_gate7(S0, not_gate(S1), S2, S3, not_gate(S4), not_gate(S5), I13);

  BIT result14 = and_gate7(not_gate(S0), S1, S2, S3, not_gate(S4), not_gate(S5), I14);

  BIT result15 = and_gate7(S0, S1, S2, S3, not_gate(S4), not_gate(S5), I15);

  BIT result16 = and_gate7(not_gate(S0), not_gate(S1), not_gate(S2), not_gate(S3), S4, not_gate(S5), I16);

  BIT result17 = and_gate7(S0, not_gate(S1), not_gate(S2), not_gate(S3), S4, not_gate(S5), I17);

  BIT result18 = and_gate7(not_gate(S0), S1, not_gate(S2), not_gate(S3), S4, not_gate(S5), I18);

  BIT result19 = and_gate7(S0, S1, not_gate(S2), not_gate(S3), S4, not_gate(S5), I19);

  BIT result20 = and_gate7(not_gate(S0), not_gate(S1), S2, not_gate(S3), S4, not_gate(S5), I20);

  BIT result21 = and_gate7(S0, not_gate(S1), S2, not_gate(S3), S4, not_gate(S5), I21);

  BIT result22 = and_gate7(not_gate(S0), S1, S2, not_gate(S3), S4, not_gate(S5), I22);

  BIT result23 = and_gate7(S0, S1, S2, not_gate(S3), S4, not_gate(S5), I23);

  BIT result24 = and_gate7(not_gate(S0), not_gate(S1), not_gate(S2), S3, S4, not_gate(S5), I24);

  BIT result25 = and_gate7(S0, not_gate(S1), not_gate(S2), S3, S4, not_gate(S5), I25);

  BIT result26 = and_gate7(not_gate(S0), S1, not_gate(S2), S3, S4, not_gate(S5), I26);

  BIT result27 = and_gate7(S0, S1, not_gate(S2), S3, S4, not_gate(S5), I27);

  BIT result28 = and_gate7(not_gate(S0), not_gate(S1), S2, S3, S4, not_gate(S5), I28);

  BIT result29 = and_gate7(S0, not_gate(S1), S2, S3, S4, not_gate(S5), I29);

  BIT result30 = and_gate7(not_gate(S0), S1, S2, S3, S4, not_gate(S5), I30);

  BIT result31 = and_gate7(S0, S1, S2, S3, S4, not_gate(S5), I31);

  BIT result32 = and_gate7(not_gate(S0), not_gate(S1), not_gate(S2), not_gate(S3), not_gate(S4), S5, I32);

  BIT result33 = and_gate7(S0, not_gate(S1), not_gate(S2), not_gate(S3), not_gate(S4), S5, I33);

  BIT result34 = and_gate7(not_gate(S0), S1, not_gate(S2), not_gate(S3), not_gate(S4), S5, I34);

  BIT result35 = and_gate7(S0, S1, not_gate(S2), not_gate(S3), not_gate(S4), S5, I35);

  BIT result36 = and_gate7(not_gate(S0), not_gate(S1), S2, not_gate(S3), not_gate(S4), S5, I36);

  BIT result37 = and_gate7(S0, not_gate(S1), S2, not_gate(S3), not_gate(S4), S5, I37);

  BIT result38 = and_gate7(not_gate(S0), S1, S2, not_gate(S3), not_gate(S4), S5, I38);

  BIT result39 = and_gate7(S0, S1, S2, not_gate(S3), not_gate(S4), S5, I39);

  BIT result40 = and_gate7(not_gate(S0), not_gate(S1), not_gate(S2), S3, not_gate(S4), S5, I40);

  BIT result41 = and_gate7(S0, not_gate(S1), not_gate(S2), S3, not_gate(S4), S5, I41);

  BIT result42 = and_gate7(not_gate(S0), S1, not_gate(S2), S3, not_gate(S4), S5, I42);

  BIT result43 = and_gate7(S0, S1, not_gate(S2), S3, not_gate(S4), S5, I43);

  BIT result44 = and_gate7(not_gate(S0), not_gate(S1), S2, S3, not_gate(S4), S5, I44);

  BIT result45 = and_gate7(S0, not_gate(S1), S2, S3, not_gate(S4), S5, I45);

  BIT result46 = and_gate7(not_gate(S0), S1, S2, S3, not_gate(S4), S5, I46);

  BIT result47 = and_gate7(S0, S1, S2, S3, not_gate(S4), S5, I47);

  BIT result48 = and_gate7(not_gate(S0), not_gate(S1), not_gate(S2), not_gate(S3), S4, S5, I48);

  BIT result49 = and_gate7(S0, not_gate(S1), not_gate(S2), not_gate(S3), S4, S5, I49);

  BIT result50 = and_gate7(not_gate(S0), S1, not_gate(S2), not_gate(S3), S4, S5, I50);

  BIT result51 = and_gate7(S0, S1, not_gate(S2), not_gate(S3), S4, S5, I51);

  BIT result52 = and_gate7(not_gate(S0), not_gate(S1), S2, not_gate(S3), S4, S5, I52);

  BIT result53 = and_gate7(S0, not_gate(S1), S2, not_gate(S3), S4, S5, I53);

  BIT result54 = and_gate7(not_gate(S0), S1, S2, not_gate(S3), S4, S5, I54);

  BIT result55 = and_gate7(S0, S1, S2, not_gate(S3), S4, S5, I55);

  BIT result56 = and_gate7(not_gate(S0), not_gate(S1), not_gate(S2), S3, S4, S5, I56);

  BIT result57 = and_gate7(S0, not_gate(S1), not_gate(S2), S3, S4, S5, I57);

  BIT result58 = and_gate7(not_gate(S0), S1, not_gate(S2), S3, S4, S5, I58);

  BIT result59 = and_gate7(S0, S1, not_gate(S2), S3, S4, S5, I59);

  BIT result60 = and_gate7(not_gate(S0), not_gate(S1), S2, S3, S4, S5, I60);

  BIT result61 = and_gate7(S0, not_gate(S1), S2, S3, S4, S5, I61);

  BIT result62 = and_gate7(not_gate(S0), S1, S2, S3, S4, S5, I62);

  BIT result63 = and_gate7(S0, S1, S2, S3, S4, S5, I63);

  BIT result = or_gate64(result0, result1, result2, result3, result4, result5, result6, result7, result8, 
    result9, result10, result11, result12, result13, result14, result15, result16, 
    result17, result18, result19, result20, result21, result22, result23, result24, 
    result25, result26, result27, result28, result29, result30, result31, result32, 
    result33, result34, result35, result36, result37, result38, result39, result40, 
    result41, result42, result43, result44, result45, result46, result47, result48, 
    result49, result50, result51, result52, result53, result54, result55, result56, 
    result57, result58, result59, result60, result61, result62, result63);

  return result;
}

/******************************************************************************/
/* Helper functions */
/******************************************************************************/
void copy_bits(BIT* A, BIT* B)
{
  for (int i = 0; i < 32; ++i)
    B[i] = A[i]; 
}

void print_binary(BIT* A)
{
  for (int i = 31; i >= 0; --i)
    printf("%d", A[i]); 
}

void convert_to_binary_char(int a, char* A, int length)
{
  // TODO: perform conversion of integer to binary representation as char array
  // This uses the same logic as your HW5 implementation. However, you're 
  // converting to a character array instead of a BIT array.
  // This might be useful in your get_instructions() function, if you use the
  // same approach that I use. It also might not be needed if you directly
  // convert the instructions to the proper BIT format.
  if (a >= 0) {
    for (int i = 0; i < length; ++i) {
      A[i] = (a % 2 == 1 ? '1' : '0');
      a /= 2;
    }
  } 
  else {
    a += 1;
    for (int i = 0; i < length; ++i) {
      A[i] = (a % 2 == 0 ? '1' : '0');
      a /= 2;
    }
  }
}
  
int binary_to_integer(BIT* A)
{
  unsigned a = 0;
  unsigned mult = 1;
  
  for (int i = 0; i < 32; ++i) {
    a += A[i]*mult;
    mult *= 2;
  }
  
  return (int)a;
}

//***Our Addition from Lab 6***
void set_register(char* input, char* output)
{
  if (strcmp(input, "t0") == 0)
    memcpy(output, "00010", 5);
  else if (strcmp(input, "s0") == 0)
    memcpy(output, "00001", 5);
  else if (strcmp(input, "zero") == 0)
    memcpy(output, "00000", 5);
  else if (strcmp(input, "v0") == 0)
    memcpy(output, "01000", 5);
  else if (strcmp(input, "a0") == 0) 
    memcpy(output, "00100", 5);
  else if (strcmp(input, "t1") == 0)
    memcpy(output, "10010", 5);
  else if (strcmp(input, "s1") == 0)
    memcpy(output, "10001", 5);
  else if (strcmp(input, "sp") == 0)
    memcpy(output, "10111", 5);
  else if (strcmp(input, "ra") == 0)
    memcpy(output, "11111", 5);
}

/******************************************************************************/
/* Parsing functions */
/******************************************************************************/

// TODO: Implement any helper functions to assist with parsing

int get_instructions(BIT Instructions[][32])
{
  char line[256] = {0};
  int instruction_count = 0;
  while (fgets(line, 256, stdin) != NULL) {        
    // TODO: perform conversion of instructions to binary
    // Input: coming from stdin via: ./a.out < input.txt
    // Output: Convert instructions to binary in the instruction memory
    // Return: Total number of instructions
    // Note: you are free to use if-else and external libraries here
    // Note: you don't need to implement circuits for saving to inst. mem.
    // My approach:
    // - Use sscanf on line to get strings for instruction and registers
    // - Use instructions to determine op code, funct, and shamt fields
    // - Convert immediate field and jump address field to binary
    // - Use registers to get rt, rd, rs fields
    // Note: I parse everything as strings, then convert to BIT array at end
  
    char inst[256] = {0};
    char op1[256] = {0};
    char op2[256] = {0};
    char op3[256] = {0};
    sscanf(line, "%s %s %s %s", inst, op1, op2, op3);
    
    char temp_output[33] = {0};
    char rs[6] = {0};
    char rt[6] = {0};
    char rd[6] = {0};
    char imm[17] = {0};
    char address[27] = {0};
    
    // I TYPE
    if (strcmp(inst, "lw") == 0) {
      convert_to_binary_char(atoi(op3), imm, 16);
      set_register(op1, rt);
      set_register(op2, rs);
      memcpy(&temp_output[0], imm, 16);
      memcpy(&temp_output[16], rt, 5);
      memcpy(&temp_output[21], rs, 5);
      memcpy(&temp_output[26], "110001", 6);      
    // R TYPE
    } else if (strcmp(inst, "add") == 0) {
      set_register(op1, rd);
      set_register(op2, rs);
      set_register(op3, rt);
      memcpy(&temp_output[0], "000001", 6);
      memcpy(&temp_output[6], "00000", 5);
      memcpy(&temp_output[11], rd, 5);
      memcpy(&temp_output[16], rt, 5);
      memcpy(&temp_output[21], rs, 5);
      memcpy(&temp_output[26], "000000", 6);      
    // J TYPE
    } else if (strcmp(inst, "j") == 0) {
      convert_to_binary_char(atoi(op1), address, 26);
      memcpy(&temp_output[0], address, 26);
      memcpy(&temp_output[26], "010000", 6);      
    // I TYPE
    } else if (strcmp(inst, "sw") == 0) {
      convert_to_binary_char(atoi(op3), imm, 16);
      set_register(op1, rt);
      set_register(op2, rs);
      memcpy(&temp_output[0], imm, 16);
      memcpy(&temp_output[16], rt, 5);
      memcpy(&temp_output[21], rs, 5);
      memcpy(&temp_output[26], "110101", 6); 
    // I TYPE
    } else if (strcmp(inst, "beq") == 0) {
      convert_to_binary_char(atoi(op3), imm, 16);
      set_register(op1, rt);
      set_register(op2, rs);
      memcpy(&temp_output[0], imm, 16);
      memcpy(&temp_output[16], rs, 5);
      memcpy(&temp_output[21], rt, 5);
      memcpy(&temp_output[26], "001000", 6); 
    // I TYPE
    } else if (strcmp(inst, "addi") == 0) {
      convert_to_binary_char(atoi(op3), imm, 16);
      set_register(op1, rt);
      set_register(op2, rs);
      memcpy(&temp_output[0], imm, 16);
      memcpy(&temp_output[16], rt, 5);
      memcpy(&temp_output[21], rs, 5);
      memcpy(&temp_output[26], "000100", 6); 
    // R TYPE
    } else if (strcmp(inst, "and") == 0) {
      set_register(op1, rd);
      set_register(op2, rs);
      set_register(op3, rt);
      memcpy(&temp_output[0], "001001", 6);
      memcpy(&temp_output[6], "00000", 5);
      memcpy(&temp_output[11], rd, 5);
      memcpy(&temp_output[16], rt, 5);
      memcpy(&temp_output[21], rs, 5);
      memcpy(&temp_output[26], "000000", 6);
    // R TYPE
    } else if (strcmp(inst, "or") == 0) {
      set_register(op1, rd);
      set_register(op2, rs);
      set_register(op3, rt);
      memcpy(&temp_output[0], "101001", 6);
      memcpy(&temp_output[6], "00000", 5);
      memcpy(&temp_output[11], rd, 5);
      memcpy(&temp_output[16], rt, 5);
      memcpy(&temp_output[21], rs, 5);
      memcpy(&temp_output[26], "000000", 6);
    // R TYPE
    } else if (strcmp(inst, "sub") == 0) {
      set_register(op1, rd);
      set_register(op2, rs);
      set_register(op3, rt);
      memcpy(&temp_output[0], "010001", 6);
      memcpy(&temp_output[6], "00000", 5);
      memcpy(&temp_output[11], rd, 5);
      memcpy(&temp_output[16], rt, 5);
      memcpy(&temp_output[21], rs, 5);
      memcpy(&temp_output[26], "000000", 6);
    // R TYPE
    } else if (strcmp(inst, "slt") == 0) {
      set_register(op1, rd);
      set_register(op2, rs);
      set_register(op3, rt);
      memcpy(&temp_output[0], "010101", 6);
      memcpy(&temp_output[6], "00000", 5);
      memcpy(&temp_output[11], rd, 5);
      memcpy(&temp_output[16], rt, 5);
      memcpy(&temp_output[21], rs, 5);
      memcpy(&temp_output[26], "000000", 6);
    // J TYPE
    } else if (strcmp(inst, "jal") == 0) {
      convert_to_binary_char(atoi(op1), address, 26);
      memcpy(&temp_output[0], address, 26);
      memcpy(&temp_output[26], "110000", 6);
    // R TYPE
    } else if (strcmp(inst, "jr") == 0) {
      set_register(op1, rd);
      set_register(op2, rs);
      set_register(op3, rt);
      memcpy(&temp_output[0], "000100", 6);
      memcpy(&temp_output[6], "00000", 5);
      memcpy(&temp_output[11], rs, 5);
      memcpy(&temp_output[16], rt, 5);
      memcpy(&temp_output[21], rd, 5);
      memcpy(&temp_output[26], "000010", 6);
    }
    for (int j = 0; j < 32; j++)
      Instructions[instruction_count][j] = (temp_output[j] == '1' ? TRUE : FALSE);
    ++instruction_count;
  }
  return instruction_count;
}


/******************************************************************************/
/* Program state - memory spaces, PC, and control */
/******************************************************************************/
BIT PC[32]                  = {FALSE};
BIT MEM_Instruction[32][32] = {FALSE};
BIT MEM_Data[32][32]        = {FALSE};
BIT MEM_Register[32][32]    = {FALSE};

BIT RegDst[2] = {FALSE};
BIT Jump[2]   = {FALSE};
BIT Branch    = FALSE;
BIT MemRead   = FALSE;
BIT MemToReg  = FALSE;
BIT ALUOp[2]  = {FALSE};
BIT MemWrite  = FALSE;
BIT ALUSrc    = FALSE;
BIT RegWrite  = FALSE;
BIT Zero      = FALSE;
BIT ALUControl[4] = {FALSE};

void print_instruction()
{
  unsigned pc = binary_to_integer(PC);
  printf("PC: %d\n", pc);
  printf("Instruction: ");
  print_binary(MEM_Instruction[pc]);
  printf("\n");
}

void print_state()
{
  printf("Data: ");
  for (int i = 0; i < 32; ++i) {
    printf("%d ", binary_to_integer(MEM_Data[i]));
  } 
  printf("\n");  
  
  printf("Register: ");
  for (int i = 0; i < 32; ++i) {
    printf("%d ", binary_to_integer(MEM_Register[i]));
  } 
  printf("\n");
}


/******************************************************************************/
/* Functions that you will implement */
/******************************************************************************/
void Instruction_Memory(BIT* ReadAddress, BIT* Instruction)
{
  // TODO: Implement instruction memory
  // Input: 32-bit instruction address
  // Output: 32-bit binary instruction
  // Note: Useful to use a 5-to-32 decoder here
  
  BIT Output[32] = {FALSE};
  BIT Input[5] = {FALSE};
  Input[0] = ReadAddress[0];
  Input[1] = ReadAddress[1];
  Input[2] = ReadAddress[2];
  Input[3] = ReadAddress[3];
  Input[4] = ReadAddress[4];
  decoder5(Input,TRUE,Output);
  
  for(int i = 0; i < 32; ++i){
    for(int j = 0; j < 32; ++j){
      Instruction[j] = multiplexor2(Output[i], Instruction[j], MEM_Instruction[i][j]);
    }
  } 
}

void Control(BIT* OpCode,
  BIT* RegDst, BIT* Jump, BIT* Branch, BIT* MemRead, BIT* MemToReg,
  BIT* ALUOp, BIT* MemWrite, BIT* ALUSrc, BIT* RegWrite) {
  // TODO: Set control bits for everything
  // Input: opcode field from the instruction
  // OUtput: all control lines get set 
  // Note: Can use SOP or similar approaches to determine bits
  
  BIT I0 = 0;
  BIT I1 = 0;
  BIT I2 = 0;
  BIT I3 = 0;
  BIT I4 = 0;
  BIT I5 = 0;
  BIT I6 = 0;
  BIT I7 = 0;
  BIT I8 = 0;
  BIT I9 = 0;
  BIT I10 = 0;
  BIT I11 = 0;
  BIT I12 = 0;
  BIT I13 = 0;
  BIT I14 = 0;
  BIT I15 = 0;
  BIT I16 = 0;
  BIT I17 = 0;
  BIT I18 = 0;
  BIT I19 = 0;
  BIT I20 = 0;
  BIT I21 = 0;
  BIT I22 = 0;
  BIT I23 = 0;
  BIT I24 = 0;
  BIT I25 = 0;
  BIT I26 = 0;
  BIT I27 = 0;
  BIT I28 = 0;
  BIT I29 = 0;
  BIT I30 = 0;
  BIT I31 = 0;
  BIT I32 = 0;
  BIT I33 = 0;
  BIT I34 = 0;
  BIT I35 = 0;
  BIT I36 = 0;
  BIT I37 = 0;
  BIT I38 = 0;
  BIT I39 = 0;
  BIT I40 = 0;
  BIT I41 = 0;
  BIT I42 = 0;
  BIT I43 = 0;
  BIT I44 = 0;
  BIT I45 = 0;
  BIT I46 = 0;
  BIT I47 = 0;
  BIT I48 = 0;
  BIT I49 = 0;
  BIT I50 = 0;
  BIT I51 = 0;
  BIT I52 = 0;
  BIT I53 = 0;
  BIT I54 = 0;
  BIT I55 = 0;
  BIT I56 = 0;
  BIT I57 = 0;
  BIT I58 = 0;
  BIT I59 = 0;
  BIT I60 = 0;
  BIT I61 = 0;
  BIT I62 = 0;
  BIT I63 = 0;
   
  //Set RegDst Control Line
  I0 = 0;
  I35 = 0;
  I43 = 0;
  I4 = 0;
  I3 = 1;
  I2 = 0;
  I8 = 0;
  I16 = 0;
  RegDst[1] = multiplexor64(OpCode[5], OpCode[4], OpCode[3], OpCode[2], OpCode[1], OpCode[0], I0, I1, I2, I3, I4, I5, 
  I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, I16, I17, I18, I19, I20, I21, I22, I23, I24, I25, I26, I27, 
  I28, I29, I30, I31, I32, I33, I34, I35, I36, I37, I38, I39, I40, I41, I42, I43, I44, I45, I46, I47, I48, 
  I49, I50, I51, I52, I53, I54, I55, I56, I57, I58, I59, I60, I61, I62, I63);
  
  //Set ALUSrc Control Line
  I0 = 0;
  I35 = 1;
  I43 = 1;
  I4 = 0;
  I3 = 0;
  I2 = 0;
  I8 = 1;
  I16 = 0;
    
  *ALUSrc = multiplexor64(OpCode[5], OpCode[4], OpCode[3], OpCode[2], OpCode[1], OpCode[0], I0, I1, I2, I3, I4, I5, 
  I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, I16, I17, I18, I19, I20, I21, I22, I23, I24, I25, I26, I27, 
  I28, I29, I30, I31, I32, I33, I34, I35, I36, I37, I38, I39, I40, I41, I42, I43, I44, I45, I46, I47, I48, 
  I49, I50, I51, I52, I53, I54, I55, I56, I57, I58, I59, I60, I61, I62, I63);
  
  //Set MemToReg Control Line
  I0 = 0;
  I35 = 1;
  I43 = 0;
  I4 = 0;
  I3 = 0;
  I2 = 0;
  I8 = 0;
  I16 = 1;
  *MemToReg = multiplexor64(OpCode[5], OpCode[4], OpCode[3], OpCode[2], OpCode[1], OpCode[0], I0, I1, I2, I3, I4, I5, 
  I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, I16, I17, I18, I19, I20, I21, I22, I23, I24, I25, I26, I27, 
  I28, I29, I30, I31, I32, I33, I34, I35, I36, I37, I38, I39, I40, I41, I42, I43, I44, I45, I46, I47, I48, 
  I49, I50, I51, I52, I53, I54, I55, I56, I57, I58, I59, I60, I61, I62, I63);
  
  //Set RegWrite Control Line
  I0 = 1;
  I35 = 1;
  I43 = 0;
  I4 = 0;
  I3 = 1;
  I2 = 0;
  I8 = 1;
  I16 = 1;
  *RegWrite = multiplexor64(OpCode[5], OpCode[4], OpCode[3], OpCode[2], OpCode[1], OpCode[0], I0, I1, I2, I3, I4, I5, 
  I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, I16, I17, I18, I19, I20, I21, I22, I23, I24, I25, I26, I27, 
  I28, I29, I30, I31, I32, I33, I34, I35, I36, I37, I38, I39, I40, I41, I42, I43, I44, I45, I46, I47, I48, 
  I49, I50, I51, I52, I53, I54, I55, I56, I57, I58, I59, I60, I61, I62, I63);
  
  //Set MemRead Control Line
  I0 = 0;
  I35 = 1;
  I43 = 0;
  I4 = 0;
  I3 = 0;
  I2 = 0;
  I8 = 0;
  I16 = 0;
  *MemRead = multiplexor64(OpCode[5], OpCode[4], OpCode[3], OpCode[2], OpCode[1], OpCode[0], I0, I1, I2, I3, I4, I5, 
  I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, I16, I17, I18, I19, I20, I21, I22, I23, I24, I25, I26, I27, 
  I28, I29, I30, I31, I32, I33, I34, I35, I36, I37, I38, I39, I40, I41, I42, I43, I44, I45, I46, I47, I48, 
  I49, I50, I51, I52, I53, I54, I55, I56, I57, I58, I59, I60, I61, I62, I63);
  
  //Set MemWrite Control Line
  I0 = 0;
  I35 = 0;
  I43 = 1;
  I4 = 0;
  I3 = 0;
  I2 = 0;
  I8 = 0;
  I16 = 0;
  *MemWrite = multiplexor64(OpCode[5], OpCode[4], OpCode[3], OpCode[2], OpCode[1], OpCode[0], I0, I1, I2, I3, I4, I5, 
  I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, I16, I17, I18, I19, I20, I21, I22, I23, I24, I25, I26, I27, 
  I28, I29, I30, I31, I32, I33, I34, I35, I36, I37, I38, I39, I40, I41, I42, I43, I44, I45, I46, I47, I48, 
  I49, I50, I51, I52, I53, I54, I55, I56, I57, I58, I59, I60, I61, I62, I63);
  
  //Set Branch Control Line
  I0 = 0;
  I35 = 0;
  I43 = 0;
  I4 = 1;
  I3 = 0;
  I2 = 0;
  I8 = 0;
  I16 = 0;
  *Branch = multiplexor64(OpCode[5], OpCode[4], OpCode[3], OpCode[2], OpCode[1], OpCode[0], I0, I1, I2, I3, I4, I5, 
  I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, I16, I17, I18, I19, I20, I21, I22, I23, I24, I25, I26, I27, 
  I28, I29, I30, I31, I32, I33, I34, I35, I36, I37, I38, I39, I40, I41, I42, I43, I44, I45, I46, I47, I48, 
  I49, I50, I51, I52, I53, I54, I55, I56, I57, I58, I59, I60, I61, I62, I63);
  
  //Set ALUOp 1
  I0 = 1;
  I35 = 0;
  I43 = 0;
  I4 = 0;
  I3 = 0;
  I2 = 0;
  I8 = 0;
  I16 = 0;
  ALUOp[1] = multiplexor64(OpCode[5], OpCode[4], OpCode[3], OpCode[2], OpCode[1], OpCode[0], I0, I1, I2, I3, I4, I5, 
  I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, I16, I17, I18, I19, I20, I21, I22, I23, I24, I25, I26, I27, 
  I28, I29, I30, I31, I32, I33, I34, I35, I36, I37, I38, I39, I40, I41, I42, I43, I44, I45, I46, I47, I48, 
  I49, I50, I51, I52, I53, I54, I55, I56, I57, I58, I59, I60, I61, I62, I63);
  
  //Set ALUOp 2
  I0 = 0;
  I35 = 0;
  I43 = 0;
  I4 = 1;
  I3 = 0;
  I2 = 0;
  I8 = 0;
  I16 = 0;
  ALUOp[0] = multiplexor64(OpCode[5], OpCode[4], OpCode[3], OpCode[2], OpCode[1], OpCode[0], I0, I1, I2, I3, I4, I5, 
  I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, I16, I17, I18, I19, I20, I21, I22, I23, I24, I25, I26, I27, 
  I28, I29, I30, I31, I32, I33, I34, I35, I36, I37, I38, I39, I40, I41, I42, I43, I44, I45, I46, I47, I48, 
  I49, I50, I51, I52, I53, I54, I55, I56, I57, I58, I59, I60, I61, I62, I63);
  
  //Set Jump Control Line
  I0 = 1;
  I35 = 0;
  I43 = 0;
  I4 = 0;
  I3 = 0;
  I2 = 0;
  I8 = 0;
  I16 = 0;
  RegDst[0] = multiplexor64(OpCode[5], OpCode[4], OpCode[3], OpCode[2], OpCode[1], OpCode[0], I0, I1, I2, I3, I4, I5, 
  I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, I16, I17, I18, I19, I20, I21, I22, I23, I24, I25, I26, I27, 
  I28, I29, I30, I31, I32, I33, I34, I35, I36, I37, I38, I39, I40, I41, I42, I43, I44, I45, I46, I47, I48, 
  I49, I50, I51, I52, I53, I54, I55, I56, I57, I58, I59, I60, I61, I62, I63);
  
  //Set Jump Control Line
  I0 = 0;
  I35 = 0;
  I43 = 0;
  I4 = 0;
  I3 = 0;
  I2 = 0;
  I8 = 0;
  I16 = 1;
  Jump[1] = multiplexor64(OpCode[5], OpCode[4], OpCode[3], OpCode[2], OpCode[1], OpCode[0], I0, I1, I2, I3, I4, I5, 
  I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, I16, I17, I18, I19, I20, I21, I22, I23, I24, I25, I26, I27, 
  I28, I29, I30, I31, I32, I33, I34, I35, I36, I37, I38, I39, I40, I41, I42, I43, I44, I45, I46, I47, I48, 
  I49, I50, I51, I52, I53, I54, I55, I56, I57, I58, I59, I60, I61, I62, I63);
  
  I0 = 0;
  I35 = 0;
  I43 = 0;
  I4 = 0;
  I3 = 1;
  I2 = 1;
  I8 = 0;
  I16 = 0;
  Jump[0] = multiplexor64(OpCode[5], OpCode[4], OpCode[3], OpCode[2], OpCode[1], OpCode[0], I0, I1, I2, I3, I4, I5, 
  I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, I16, I17, I18, I19, I20, I21, I22, I23, I24, I25, I26, I27, 
  I28, I29, I30, I31, I32, I33, I34, I35, I36, I37, I38, I39, I40, I41, I42, I43, I44, I45, I46, I47, I48, 
  I49, I50, I51, I52, I53, I54, I55, I56, I57, I58, I59, I60, I61, I62, I63);
}

void Read_Register(BIT* ReadRegister1, BIT* ReadRegister2,
  BIT* ReadData1, BIT* ReadData2)
{
  // TODO: Implement register read functionality
  // Input: two 5-bit register addresses
  // Output: the values of the specified registers in ReadData1 and ReadData2
  // Note: Implementation will be very similar to instruction memory circuit
  
  BIT Output[32] = {FALSE};
  BIT Input[5] = {FALSE};
  Input[0] = ReadRegister1[0];
  Input[1] = ReadRegister1[1];
  Input[2] = ReadRegister1[2];
  Input[3] = ReadRegister1[3];
  Input[4] = ReadRegister1[4];
  decoder5(Input,TRUE,Output);

  for(int i = 0; i < 32; ++i){
    for(int j = 0; j < 32; ++j){
      ReadData1[j] = multiplexor2(Output[i], ReadData1[j], MEM_Register[i][j]);
    }
  }

  BIT Output1[32] = {FALSE};
  BIT Input1[5] = {FALSE};
  Input1[0] = ReadRegister2[0];
  Input1[1] = ReadRegister2[1];
  Input1[2] = ReadRegister2[2];
  Input1[3] = ReadRegister2[3];
  Input1[4] = ReadRegister2[4];
  decoder5(Input1,TRUE,Output1);
  for(int i = 0; i < 32; ++i){
    for(int j = 0; j < 32; ++j){
      ReadData2[j] = multiplexor2(Output1[i], ReadData2[j], MEM_Register[i][j]);
    }
  }
}

void Write_Register(BIT RegWrite, BIT* WriteRegister, BIT* WriteData)
{
  // TODO: Implement register write functionality
  // Input: one 5-bit register address, data to write, and control bit
  // Output: None, but will modify register file
  // Note: Implementation will again be similar to those above
  
  BIT Output[32] = {FALSE};
  BIT Input[5] = {FALSE};
  Input[0] = WriteRegister[0];
  Input[1] = WriteRegister[1];
  Input[2] = WriteRegister[2];
  Input[3] = WriteRegister[3];
  Input[4] = WriteRegister[4];
  decoder5(Input,RegWrite,Output);

  for (int i = 0; i < 32; ++i) {
    for (int j = 0; j < 32; ++j) {
      MEM_Register[i][j] = multiplexor2(Output[i],MEM_Register[i][j],WriteData[j]);
    }
  }
}

void ALU_Control(BIT* ALUOp, BIT* funct, BIT* ALUControl)
{
  // TODO: Implement ALU Control circuit
  // Input: 2-bit ALUOp from main control circuit, 6-bit funct field from the
  //        binary instruction
  // Output:4-bit ALUControl for input into the ALU
  // Note: Can use SOP or similar approaches to determine bits
  
  BIT add = and_gate6((funct[5]), not_gate(funct[4]), not_gate(funct[3]), not_gate(funct[2]), not_gate(funct[1]), not_gate(funct[0]));
  BIT sub = and_gate6((funct[5]), not_gate(funct[4]), not_gate(funct[3]), not_gate(funct[2]),         (funct[1]),  not_gate(funct[0]));
  BIT or =  and_gate6((funct[5]), not_gate(funct[4]), not_gate(funct[3]),         (funct[2]), not_gate(funct[1]),        (funct[0]));
  BIT slt = and_gate6((funct[5]), not_gate(funct[4]),         (funct[3]), not_gate(funct[2]),         (funct[1]),  not_gate(funct[0]));
  
  ALUControl[0] = 0;
  ALUControl[1] = or_gate3(sub, slt, ALUOp[0]);
  ALUControl[2] = or_gate(or_gate3(add, sub, slt), not_gate(ALUOp[1]));
  ALUControl[3] = or_gate(slt, or);
}

//***Our Addition***
void adder1(BIT A, BIT B, BIT CarryIn, BIT* CarryOut, BIT* Sum)
{  
  BIT x0 = xor_gate(A, B);
  *Sum = xor_gate(CarryIn, x0);
  
  BIT y0 = and_gate(x0, CarryIn);
  BIT y1 = and_gate(A, B);
  *CarryOut = or_gate(y0, y1);
}

//***Our Addition***
void ALU1(BIT A, BIT B, BIT Binvert, BIT CarryIn, BIT Less, 
  BIT Op0, BIT Op1, BIT* Result, BIT* CarryOut, BIT* Set)
{ 
  BIT notB = not_gate(B);
  B = multiplexor2(Binvert, B, notB);

  BIT AandB = and_gate(A,B);
  BIT AorB = or_gate(A,B);

  BIT addAB;
  BIT cout;
  adder1(A, B, CarryIn, &cout, &addAB);
  *CarryOut = cout;
  *Set = addAB;

  *Result = multiplexor4(Op1, Op0, AandB, AorB, addAB, Less);
}

void ALU32(BIT* A, BIT* B, BIT Binvert, BIT CarryIn, 
  BIT Op0, BIT Op1, BIT* Result, BIT* CarryOut)
{
  // TODO: implement a 32-bit ALU
  // You'll need to essentially implement a 32-bit ripple addder here
  // See slide 31 in Chapter-3d
  int i=0;
  BIT Set[1];
  BIT temp = CarryIn;
  
  for (i=0; i<32; i++) {
    ALU1(A[i], B[i], Binvert, CarryIn, 0, Op0, Op1, &(Result[i]), &(CarryOut[0]), &(Set[0]));
    CarryIn = CarryOut[0];
  }
  BIT set = Set[0];
  ALU1(A[0], B[0], Binvert, temp, set, Op0, Op1, &(Result[0]), &(CarryOut[0]), &(Set[0]));
  
}

void ALU(BIT* ALUControl, BIT* Input1, BIT* Input2, BIT* Zero, BIT* Result)
{   
  // TODO: Implement 32-bit ALU
  // Input: 4-bit ALUControl, two 32-bit inputs
  // Output: 32-bit result, and zero flag big
  // Note: Can re-use prior implementations (but need new circuitry for zero)
 
  *Zero = FALSE;
  // and
  BIT andResult[32];
  
  for (int i=0; i<32; i++) {
   andResult[i] = and_gate(Input1[i], Input2[i]);
  }
  
  //or
  BIT orResult[32];
  
  for (int i=0; i<32; i++) {
   orResult[i] = or_gate(Input1[i], Input2[i]);
  }
  
  //add
  BIT addResult[32];
  BIT CarryOutAdd[1];
  ALU32(Input1, Input2, 0, 0, 1, 0, addResult, &(CarryOutAdd[0]));
  
  //sub
  BIT subResult[32];
  BIT CarryOutSub[1];
  ALU32(Input1, Input2, 1, 1, 1, 0, subResult, &(CarryOutSub[0]));
  
  //slt
  BIT sltResult[32];
  BIT CarryOutSlt[0];
  ALU32(Input1, Input2, 1, 1, 1, 1, sltResult, &(CarryOutSlt[0]));
  
  for (int i=0; i<32; i++) {
   Result[i] = multiplexor8(ALUControl[2], ALUControl[1], ALUControl[0], andResult[i], orResult[i], addResult[i], subResult[i], orResult[i], 0, 0, sltResult[i]);
   
   *Zero = not_gate(or_gate32(Result[0], Result[1], Result[2], Result[3], Result[4], Result[5], 
    Result[6], Result[7], Result[8], Result[9], Result[10], Result[11], Result[12], Result[13], 
    Result[14], Result[15], Result[16], Result[17], Result[18], Result[19], Result[20], 
    Result[21], Result[22], Result[23], Result[24], Result[25], Result[26], Result[27], 
    Result[28], Result[29], Result[30], Result[31]));
  }

}

void Data_Memory(BIT MemWrite, BIT MemRead, 
  BIT* Address, BIT* WriteData, BIT* ReadData)
{
  // TODO: Implement data memory
  // Input: 32-bit address, control flags for read/write, and data to write
  // Output: data read if processing a lw instruction
  // Note: Implementation similar as above
  
  BIT temp[32] = {FALSE};
  decoder5(Address,TRUE, temp);
  for(int i = 0; i < 32; ++i) {
   multiplexor2_32(and_gate(temp[i], MemWrite), MEM_Data[i], WriteData, MEM_Data[i]);
   multiplexor2_32(and_gate(temp[i], MemRead),ReadData, MEM_Data[i],ReadData);
  }
  
}

void Extend_Sign16(BIT* Input, BIT* Output)
{
  // TODO: Implement 16-bit to 32-bit sign extender
  // Copy Input to Output, then extend 16th Input bit to 17-32 bits in Output
  
  BIT Selector = Input[31];
  BIT Output1[32] = {TRUE};
  
  for (int i=0; i<32; i++) {
   Output1[i] = TRUE;
  }
  
  BIT Output2[32] = {FALSE}; 
  
  for (int i=0; i<32; i++) {
   Output2[i] = FALSE;
  }
  
  for (int i = 0; i < 16; ++i) {
   Output1[i] = Input[i];
  }
  
  for (int i = 0; i<16; ++i) {
   Output2[i] = Input[i];
  }
  
  for (int i = 0; i < 32; ++i) {
   Output[i] = multiplexor2(Selector, Output2[i], Output1[i]);
  }
}

void updateState() 
{
  BIT Instruction[32] = {FALSE};
  Instruction_Memory(PC, Instruction);
  
  BIT ControlOp[6] = {FALSE};
  ControlOp[0] = Instruction[31];
  ControlOp[1] = Instruction[30];
  ControlOp[2] = Instruction[29];
  ControlOp[3] = Instruction[28];
  ControlOp[4] = Instruction[27];
  ControlOp[5] = Instruction[26];
  
  //Set Control Lines
  Control(ControlOp, RegDst, Jump, &Branch, &MemRead, &MemToReg, ALUOp, &MemWrite, &ALUSrc, &RegWrite);
  
  //Set Bits for Read Register 1
  BIT ReadReg1[5] = {FALSE}; 
  ReadReg1[0] = Instruction[21];
  ReadReg1[1] = Instruction[22];
  ReadReg1[2] = Instruction[23];
  ReadReg1[3] = Instruction[24]; 
  ReadReg1[4] = Instruction[25];
  
  //Set Bits for Read Register 2
  BIT ReadReg2[5] = {FALSE};
  ReadReg2[0] = Instruction[16];
  ReadReg2[1] = Instruction[17];
  ReadReg2[2] = Instruction[18];
  ReadReg2[3] = Instruction[19];
  ReadReg2[4] = Instruction[20];
  
  //Create the variables for Storing the data read from the registers
  BIT ReadData1[32] = {FALSE},
  ReadData2[32] = {FALSE};
  
  //Read Registers
  Read_Register(ReadReg1, ReadReg2, ReadData1, ReadData2);
  
  //NOTE: Read Register 2 = Write Register 1
  //Set Bits for the WriteRegister2 (5 bits)
  BIT WriteRegister2[5] = {FALSE};
  WriteRegister2[0] = Instruction[11];
  WriteRegister2[1] = Instruction[12];
  WriteRegister2[2] = Instruction[13];
  WriteRegister2[3] = Instruction[14];
  WriteRegister2[4] = Instruction[15];
  
  //Determine which Register to Write using 2-mux
  //Inputs for 2-mux: ReadReg2 -> 0, WriteRegister2 -> 1
  //Selector Bit for 2-mux: RegDst
  BIT WriteRegister[5] = {FALSE};
  
  //Create Register31
  BIT Register31[5] = {TRUE};
  for (int i=0; i<5; i++) {
   Register31[i] = TRUE;
  }
  
  for (int i=0; i<5; i++) {
   WriteRegister[i] = multiplexor4(RegDst[0], RegDst[1], ReadReg2[i], WriteRegister2[i], Register31[i], 0);
  }
  
  //Set Bits for Sign Extension
  BIT InputSignInstruction[16] = {FALSE};
  for (int i=15; i>=0; i--) {
   InputSignInstruction[i] = Instruction[i];
  }
  
  //Extend the Bits
  BIT ExtendedInstruction[32] = {FALSE};
  Extend_Sign16(InputSignInstruction, ExtendedInstruction);
  
  //Send Inputs to 2 mux
  BIT ALUInput2[32] = {FALSE};
  for (int i=0; i<32; i++) {
   ALUInput2[i] = multiplexor2(ALUSrc, ReadData2[i], ExtendedInstruction[i]);
  }
  
  //Get OP Bits from ALUControl for ALU
  BIT funct[6] = {FALSE};
  funct[0] = Instruction[0];
  funct[1] = Instruction[1];
  funct[2] = Instruction[2];
  funct[3] = Instruction[3];
  funct[4] = Instruction[4];
  funct[5] = Instruction[5];
  
  BIT FINAL[4] = {FALSE};
  
  ALU_Control(ALUOp, funct, FINAL);
  BIT ALUControl[4] = {FINAL[3], FINAL[2], FINAL[1], FINAL[0]};
  
  BIT ALUResult[32] = {FALSE};
  
  ALU(ALUControl, ReadData1, ALUInput2, &Zero, ALUResult);
  
  //Access Data Memory
  BIT WriteData[32] = {FALSE};
  Data_Memory(MemWrite, MemRead, ALUResult, ReadData2, WriteData);
  
  
  //Write data to the register
  //Inputs for 2-mux: ReadDataMemory -> 1, ALUResult -> 0
  //Selector Bit for 2-mux: MemtoReg
  BIT WriteDataOriginal[32] = {FALSE};
  for (int i=0; i<32; i++) {
   WriteDataOriginal[i] = multiplexor2(MemToReg, ALUResult[i], WriteData[i]);
  }
  
  //Write Data to Register
  Write_Register(RegWrite, WriteRegister, WriteDataOriginal);
  
  //PC Incrementation Stuff
  BIT ALUControlAdd[4] = {FALSE, TRUE, FALSE, FALSE};
  BIT RESULT1[32] = {FALSE};
  BIT RESULT2[32] = {FALSE};
  BIT RESULT3[32] = {FALSE};
  BIT RESULT4[32] = {FALSE};
  BIT fakeZero = FALSE;
  
  ALU(ALUControlAdd, ONE, PC, &fakeZero, RESULT1);
  
  //Write Data to Register
  BIT WriteDataOutputMux[32] = {FALSE};
  for (int i=0; i<32; i++) {
   WriteDataOutputMux[i] = multiplexor2(Jump[0], WriteDataOriginal[i], RESULT1[i]);
  }
  
  Write_Register(RegWrite, WriteRegister, WriteDataOutputMux);
  
  ALU(ALUControlAdd, RESULT1, ExtendedInstruction, &fakeZero, RESULT2);
  
  BIT branchResult = and_gate(Branch, Zero);
  
  for (int i=0; i<32; i++) {
   RESULT3[i] = multiplexor2(branchResult, RESULT1[i], RESULT2[i]);
  }
  
  BIT ExtendedInstruction2[32] = {FALSE};
  for (int i=25, j=0; i>=0; i--, j++) {
   ExtendedInstruction2[i] = Instruction[i];
  }
  
  for (int i=0; i<32; i++) {
   RESULT4[i] = multiplexor4(Jump[0], Jump[1], RESULT3[i], ExtendedInstruction2[i], ReadData1[i],0);
  }
  
  copy_bits(RESULT4, PC);
}

/******************************************************************************/
/* Main */
/******************************************************************************/

int main()
{
  setbuf(stdout, NULL);
  // parse instructions into binary format
  int counter = get_instructions(MEM_Instruction);
  
  // load program and run
  copy_bits(ZERO, PC);
  copy_bits(THIRTY_TWO, MEM_Register[29]);
  
  
  while (binary_to_integer(PC) < counter) {
    print_instruction();
    updateState();
    print_state();
  }
  
  return 0;
}

