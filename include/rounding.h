#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "libm.h"

enum RoundMode {RNE, RNN, RNP, RNZ};

float ConvertBinToFP(unsigned binary, int numExpBit, unsigned bitlen) {
  unsigned numMantissa = bitlen - numExpBit - 1;
  int bias = (1 << (numExpBit - 1)) - 1;
  
  unsigned signBit = binary & (1 << (bitlen - 1));
  unsigned mantissa = binary & ((1 << numMantissa) - 1);
  unsigned expBits = binary - signBit - mantissa;
  expBits >>= numMantissa;
  
  // First check for special cases:
  // zero:
  if (binary == 0) return 0.0;
  if (binary == (1 << (bitlen - 1))) return -0.0;
  // infinity and nan:
  if (expBits == (1 << (unsigned)numExpBit) - 1) {
    if (mantissa == 0) {
      if (signBit == 0) return 1.0 / 0.0;
      else return -1.0 / 0.0;
    }
    
    return 0.0 / 0.0;
  }
  
  if (numExpBit == 8) {
    // Then just need to shift left/right
    float_x fX;
    fX.x = binary << (32 - bitlen);
    return fX.f;
  }
  
  // Take care of denormal value
  if (expBits == 0) {
    // Guaranteed to be normal value in FP32
    
    int expVal = 1 - bias;
    
    // Get position of the first 1 from the left:
   
    unsigned mantissaCopy = mantissa;
    mantissaCopy |= mantissaCopy >> 16;
    mantissaCopy |= mantissaCopy >> 8;
    mantissaCopy |= mantissaCopy >> 4;
    mantissaCopy |= mantissaCopy >> 2;
    mantissaCopy |= mantissaCopy >> 1;
    int first1Pos = __builtin_popcount(mantissaCopy);
    unsigned numZeroInMantissa = numMantissa - first1Pos;
    //unsigned numZeroInMantissa = __builtin_clz(mantissa) - 9;
    //int first1Pos = numMantissa - numZeroInMantissa;

    expVal -= 1 + numZeroInMantissa;
    mantissa <<= (24 - first1Pos);
    mantissa &= 0x7FFFFF;
    
    float_x fX;
    fX.x = (signBit == 0) ? 0x0 : 0x80000000;
    fX.x |= mantissa;
    expVal += 127;
    unsigned floatExpBit = (unsigned)expVal << 23u;
    fX.x |= floatExpBit;
    return fX.f;
  }
  
  int expVal = (int)expBits - bias;
  expVal += 127;
  unsigned floatExpBit = (unsigned)expVal << 23u;
  mantissa <<= (23 - numMantissa);
  
  float_x fX;
  fX.x = (signBit == 0) ? 0x0 : 0x80000000;
  fX.x |= mantissa;
  fX.x |= floatExpBit;
  return fX.f;
}

float RoundDoubleToF8N(double v, int bitlength, enum RoundMode rnd) {
  unsigned numMantissa = bitlength - 9;

  double_x temp;
  temp.d = v;
  // Take care of NaN and infinity
  if ((temp.x & 0x7FF0000000000000) == 0x7FF0000000000000) return v;

  // Take care of zero
  if ((temp.x & 0x7FFFFFFFFFFFFFFF) == 0) return v;

  unsigned sign = (temp.x >= 0x8000000000000000) ? 0x80000000 : 0x0;
  temp.x &= 0x7FFFFFFFFFFFFFFF;

  // Otherwise it's a number that rounds to a real value.
  long exp = (temp.x >> 52lu) & 0x7FF;
  exp -= 1023l;
  unsigned long mantissa = temp.x & 0x000FFFFFFFFFFFFF;

  unsigned vminus = 0;
  unsigned roundBit = 0;
  unsigned sticky = 0;

  if (exp < -150) {
    vminus = 0;
    roundBit = 0;
    sticky = 1;
  } else if (exp >= 128) {
    vminus = (1u << ((unsigned)bitlength - 1lu)) - 1u;
    vminus -= (1u << numMantissa);
    roundBit = 1;
    sticky = 1;
  } else {
    // double value is normal. Exp >= -150
    if ((mantissa & 0x000000000FFFFFFF) != 0) sticky = 1;
    mantissa &= 0xFFFFFFFFF0000000;
    mantissa <<= 3lu;

    if (exp < -126l) {
      long offset = -126l - exp;
      mantissa |= 0x0080000000000000;
      mantissa >>= (unsigned long)offset;
      exp = 0l;
    } else {
      exp += 127l;
    }

    unsigned long infExt = ((unsigned long)exp << 55lu) | mantissa;

    // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
    // xxxx xxxx xxxx xxxx rsss ssss ssss ssss ssss ssss ssss ssss ssss ssss ssss ssss
    if ((infExt & ((1lu << (63lu - (unsigned long)bitlength)) - 1lu)) != 0) sticky = 1;
    infExt >>= (63lu - (unsigned long)bitlength);
    roundBit = infExt & 0x1;
    vminus = (unsigned)(infExt >> 1lu);
  }

  unsigned lastBit = vminus & 0x1;
  unsigned roundDecision = 0;
  switch (rnd) {
    case RNE:
      roundDecision = (lastBit & roundBit) | (roundBit & sticky);
      break;
    case RNZ:
      roundDecision = 0;
      break;
    case RNP:
      if (!sign) roundDecision = roundBit | sticky;
      break;
    case RNN:
      if (sign) roundDecision = roundBit | sticky;
      break;
  }

  vminus += roundDecision;
  float_x res;
  res.x = vminus;
  if (bitlength < 32) res.x <<= 32 - bitlength;
  res.x |= sign;
  return res.f;
}
