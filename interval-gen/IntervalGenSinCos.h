#pragma STDC FENV_ACCESS ON

#include <cassert>
#include <fenv.h>
#include <map>
#include <queue>
#include <stdio.h>
#include <string>
#include <unistd.h>

#include "libm.h"

using namespace std;
int fileIndex = 0;

bool ComputeSpecialCase(float x); 

int RangeReduction(float x, double &xp);

int SinGuessInitialVal(double xp, double sinpiK, double cospiK, double& sinLB, double& sinUB);

int CosGuessInitialVal(double xp, double sinpiK, double cospiK, double& cosLB, double& cosUB);

int GetConsts(int N, double& sinpiK, double& cospiK);

double OutputCompensation(bool isOCLB, double sinpiK, double cospiK, double sinLB, double sinUB, double cosLB, double cosUB, bool useFMA);

int UpdateIntervals(bool isOCLB, double sinpiK, double cospiK, double newSinLB, double newSinUB, double newCosLB, double newCosUB, double& sinLB, double& sinUB, double& cosLB, double& cosUB);

uint64_t GetPredecessor(double_x y) {
  if (y.d == 0) {
    return 0x8000000000000001;
  } else if (y.d < 0) {
    return y.x + 1;
  } else {
    return y.x - 1;
  } 
}

uint64_t GetSuccessor(double_x y) {
  if (y.d == 0) {
    return 0x0000000000000001;
  } else if (y.d < 0) {
    return y.x - 1;
  } else {
    return y.x + 1;
  } 
}

double Calc34RNO(double y) {
  if ((y == 0.0) || (y == INFINITY) || (y == -INFINITY)) return y;
  if (y > 0x1.ffffffp+127) return 0x1.ffffff8p+127;
  if (y < -0x1.ffffffp+127) return -0x1.ffffff8p+127;
  double_x dY;
  dY.d = y;
  int s = (dY.d < 0) ? -1 : 1;
  dY.x &= 0x7FFFFFFFFFFFFFFF;
  int shift = 27;
  if (dY.d < ldexp(1.0f, -126)) {
    if (dY.d < ldexp(1.0f, -150)) {
      return ldexp(1.0f, -151)*s;
    }
    int e = dY.x >> 52L;
    e -= 1023;
    shift = -e - 99;
  }
  dY.d *= s;
  if (dY.x & ((1LL << shift) -1)) {
    dY.x |= ((1LL << shift) - 1);
    dY.x -= ((1LL << shift) - 1);
    dY.x |= (1LL << shift);
  }
  return dY.d;
}

int Calc34RNOInterval(double y, double& lb, double& ub) {
  double_x dY = {.d=y};
  int s = (dY.d < 0) ? -1 : 1;
  dY.x &= 0x7FFFFFFFFFFFFFFF;
  double_x lbx, ubx;
  if (dY.d == ldexp(1.0f, -151)) {
    lbx.d = 0.0f;
    ubx.d = ldexp(1.0f, -150);
  } else {
    int shift = 27;
    if (dY.d < ldexp(1.0f, -126)) {
      int e = dY.x >> 52L;
      e -= 1023;
      shift = -e - 99;
    }
    lbx.x = (dY.x - (1LL << shift));
    ubx.x = (dY.x + (1LL << shift));
  }
  if (s == -1) {
    double temp = ubx.d;
    ubx.d = -lbx.d;
    lbx.d = -temp;
  }
  lbx.x = GetSuccessor(lbx);
  ubx.x = GetPredecessor(ubx);
  lb = lbx.d;
  ub = ubx.d;
  return 0;
}  

bool CalcReducedInterval(float_x inputX, double xp, double sinpiK, double cospiK, double& sinLB, double& sinUB, double& cosLB, double& cosUB, double roundLB, double roundUB, bool multiRnd, bool useFMA) {
  double_x dx1, dx2, dx3, dx4; 
  unsigned long long step;
  int ogRnd = FE_TONEAREST;
  if (multiRnd) ogRnd = fegetround();
  if (multiRnd) fesetround(FE_DOWNWARD);
  if (OutputCompensation(true, sinpiK, cospiK, sinLB, sinUB, cosLB, cosUB, useFMA) < roundLB) {
    bool inBound = false;
    double test;
    step = 0x10000000000000llu;
    while (sinLB != -1.0e300 && sinUB != 1.0e300 && cosLB != -1.0e300 && cosUB != 1.0e300 && step > 0) {
      dx1.d = sinLB;
      dx2.d = sinUB;
      dx3.d = cosLB;
      dx4.d = cosUB;
      if (dx1.d >= 0.0) dx1.x += step;
      else dx1.x -= step;
      if (dx2.d >= 0.0) {
	if (dx2.x < step) dx2.x = 0x8000000000000000 + step - dx2.x;
	else dx2.x -= step;
      } else dx2.x += step;
      if (dx3.d >= 0.0) dx3.x += step;
      else dx3.x -= step; 
      if (dx4.d >= 0.0) {
	if (dx4.x < step) dx4.x = 0x8000000000000000 + step - dx4.x;
	else dx4.x -= step;
      } else dx4.x += step;
      test = OutputCompensation(true, sinpiK, cospiK, dx1.d, dx2.d, dx3.d, dx4.d, useFMA);
      if (roundLB <= test && test <= roundUB) {
	UpdateIntervals(true, sinpiK, cospiK, dx1.d, dx2.d, dx3.d, dx4.d, sinLB, sinUB, cosLB, cosUB);
	inBound = true;
	break;
      } else {
	step /= 2;
      }
    }
    if (!inBound) { 
      step = 0x10000000000000llu;
      while (cosLB != -1.0e300 && cosUB != 1.0e300 && step > 0) {
	dx3.d = cosLB;
	dx4.d = cosUB;
	if (dx3.d >= 0.0) dx3.x += step;
	else dx3.x -= step;	
	if (dx4.d >= 0.0) {
	  if (dx4.x < step) dx4.x = 0x8000000000000000 + step - dx4.x;
	  else dx4.x -= step;
	} else dx4.x += step;
	test = OutputCompensation(true, sinpiK, cospiK, sinLB, sinUB, dx3.d, dx4.d, useFMA);
	if (roundLB <= test && test <= roundUB) {
	  UpdateIntervals(true, sinpiK, cospiK, sinLB, sinUB, dx3.d, dx4.d, sinLB, sinUB, cosLB, cosUB);
	  inBound = true;
	  break;
	} else {
	  step /= 2;
	}
      }
    }
    if (!inBound) { 
      step = 0x10000000000000llu;
      while (sinLB != -1.0e300 && sinUB != 1.0e300 && step > 0) {
	dx1.d = sinLB;
	dx2.d = sinUB;
	if (dx1.d >= 0.0) dx1.x += step;
	else dx1.x -= step;	
	if (dx2.d >= 0.0) {
	  if (dx2.x < step) dx2.x = 0x8000000000000000 + step - dx2.x;
	  else dx2.x -= step;
	} else dx2.x += step;
	test = OutputCompensation(true, sinpiK, cospiK, dx1.d, dx2.d, cosLB, cosUB, useFMA);
	if (roundLB <= test && test <= roundUB) {
	  UpdateIntervals(true, sinpiK, cospiK, dx1.d, dx2.d, cosLB, cosUB, sinLB, sinUB, cosLB, cosUB);
	  inBound = true;
	  break;
	} else {
	  step /= 2;
	}
      }
    }
    if (!inBound) {
      printf("LB of reduced interval not within bounds post output compensation for count=%x\n", inputX.x); 
      return false;
    }
  }
  step = 0x10000000000000llu;
  while (sinLB != -1.0e300 && sinUB != 1.0e300 && cosLB != -1.0e300 && cosUB != 1.0e300 && step > 0) {
    dx1.d = sinLB;
    dx2.d = sinUB;
    dx3.d = cosLB;
    dx4.d = cosUB;
    if (dx1.d >= 0.0) {
      if (dx1.x < step) dx1.x = 0x8000000000000000 + step - dx1.x;
      else dx1.x -= step;
    } else dx1.x += step;
    if (dx2.d >= 0.0) dx2.x += step;
    else dx2.x -= step;
    if (dx3.d >= 0.0) {
      if (dx3.x < step) dx3.x = 0x8000000000000000 + step - dx3.x;
      else dx3.x -= step;
    } else dx3.x += step;
    if (dx4.d >= 0.0) dx4.x += step;
    else dx4.x -= step;
    if (OutputCompensation(true, sinpiK, cospiK, dx1.d, dx2.d, dx3.d, dx4.d, useFMA) >= roundLB) { 
      UpdateIntervals(true, sinpiK, cospiK, dx1.d, dx2.d, dx3.d, dx4.d, sinLB, sinUB, cosLB, cosUB);
    } else {
      step /= 2;
    }
  }
  step = 0x10000000000000llu;
  while (cosLB != -1.0e300 && cosUB != 1.0e300 && step > 0) {
    dx3.d = cosLB;
    dx4.d = cosUB;
    if (dx3.d >= 0.0) {
      if (dx3.x < step) dx3.x = 0x8000000000000000 + step - dx3.x;
      else dx3.x -= step;
    } else dx3.x += step;
    if (dx4.d >= 0.0) dx4.x += step;
    else dx4.x -= step;
    if (OutputCompensation(true, sinpiK, cospiK, sinLB, sinUB, dx3.d, dx4.d, useFMA) >= roundLB) {
      UpdateIntervals(true, sinpiK, cospiK, sinLB, sinUB, dx3.d, dx4.d, sinLB, sinUB, cosLB, cosUB);
    } else {
      step /= 2;
    }
  }
  step = 0x10000000000000llu;
  while (sinLB != -1.0e300 && sinUB != 1.0e300 && step > 0) {
    dx1.d = sinLB;
    dx2.d = sinUB;
    if (dx1.d >= 0.0) {
      if (dx1.x < step) dx1.x = 0x8000000000000000 + step - dx1.x;
      else dx1.x -= step;
    } else dx1.x += step; 
    if (dx2.d >= 0.0) dx2.x += step;
    else dx2.x -= step;
    if (OutputCompensation(true, sinpiK, cospiK, dx1.d, dx2.d, cosLB, cosUB, useFMA) >= roundLB) {
      UpdateIntervals(true, sinpiK, cospiK, dx1.d, dx2.d, cosLB, cosUB, sinLB, sinUB, cosLB, cosUB);
    } else {
      step /= 2;
    }
  }
  if (multiRnd) fesetround(FE_UPWARD);
  if (OutputCompensation(false, sinpiK, cospiK, sinLB, sinUB, cosLB, cosUB, useFMA) > roundUB) { 
    double test;
    bool inBound = false;
    step = 0x10000000000000llu;
    while (sinLB != -1.0e300 && sinUB != 1.e300 && cosLB != -1.0e300 && cosUB != 1.0e300 && step > 0) {
      dx1.d = sinLB;
      dx2.d = sinUB;
      dx3.d = cosLB;
      dx4.d = cosUB; 
      if (dx1.d >= 0.0) dx1.x += step;
      else dx1.x -= step;
      if (dx2.d >= 0.0) {
	if (dx2.x < step) dx2.x = 0x8000000000000000 + step - dx2.x;
	else dx2.x -= step;
      } else dx2.x += step;
      if (dx3.d >= 0.0) dx3.x += step;
      else dx3.x -= step; 
      if (dx4.d >= 0.0) {
	if (dx4.x < step) dx4.x = 0x8000000000000000 + step - dx4.x;
	else dx4.x -= step;
      } else dx4.x += step;
      test = OutputCompensation(false, sinpiK, cospiK, dx1.d, dx2.d, dx3.d, dx4.d, useFMA);
      if (roundLB <= test && test <= roundUB) {
	UpdateIntervals(false, sinpiK, cospiK, dx1.d, dx2.d, dx3.d, dx4.d, sinLB, sinUB, cosLB, cosUB);
	inBound = true;
	break;
      } else {
	step /= 2;
      }
    }
    if (!inBound) {
      step = 0x10000000000000llu;
      while (cosLB != -1.0e300 && cosUB != 1.0e300 && step > 0) {
	dx3.d = cosLB;
	dx4.d = cosUB;	
	if (dx3.d >= 0.0) dx3.x += step;
	else dx3.x -= step; 
	if (dx4.d >= 0.0) {
	  if (dx4.x < step) dx4.x = 0x8000000000000000 + step - dx4.x;
	  else dx4.x -= step;
	} else dx4.x += step;
	test = OutputCompensation(false, sinpiK, cospiK, sinLB, sinUB, dx3.d, dx4.d, useFMA);
	if (roundLB <= test && test <= roundUB) {
	  UpdateIntervals(false, sinpiK, cospiK, sinLB, sinUB, dx3.d, dx4.d, sinLB, sinUB, cosLB, cosUB);
	  inBound = true;
	  break;
	} else {
	  step /= 2;
	}
      }
    }
    if (!inBound) {
      step = 0x10000000000000llu;
      while (sinLB != -1.0e300 && sinUB != 1.0e300 && step > 0) {
	dx1.d = sinLB;
	dx2.d = sinUB;	
	if (dx1.d >= 0.0) dx1.x += step;
	else dx1.x -= step;
	if (dx2.d >= 0.0) {
	  if (dx2.x < step) dx2.x = 0x8000000000000000 + step - dx2.x;
	  else dx2.x -= step;
	} else dx2.x += step;
	test = OutputCompensation(false, sinpiK, cospiK, dx1.d, dx2.d, cosLB, cosUB, useFMA);
	if (roundLB <= test && test <= roundUB) {
	  UpdateIntervals(false, sinpiK, cospiK, dx1.d, dx2.d, cosLB, cosUB, sinLB, sinUB, cosLB, cosUB);
	  inBound = true;
	  break;
	} else {
	  step /= 2;
	}
      }
    }
    if (!inBound) {
      printf("UB of reduced interval not within bounds post output compensation for count=%x\n", inputX.x); 
      return false;
    }
  }
  step = 0x10000000000000llu;
  while (sinLB != -1.0e300 && sinUB != 1.0e300 && cosLB != -1.0e300 && cosUB != 1.0e300 && step > 0) {
    dx1.d = sinLB;
    dx2.d = sinUB;
    dx3.d = cosLB;
    dx4.d = cosUB;
    if (dx1.d >= 0.0) {
      if (dx1.x < step) dx1.x = 0x8000000000000000 + step - dx1.x;
      else dx1.x -= step;
    } else dx1.x += step; 
    if (dx2.d >= 0.0) dx2.x += step;
    else dx2.x -= step;
    if (dx3.d >= 0.0) {
      if (dx3.x < step) dx3.x = 0x8000000000000000 + step - dx3.x;
      else dx3.x -= step;
    } else dx3.x += step;
    if (dx4.d >= 0.0) dx4.x += step;
    else dx4.x -= step;
    if (OutputCompensation(false, sinpiK, cospiK, dx1.d, dx2.d, dx3.d, dx4.d, useFMA) <= roundUB) {
      UpdateIntervals(false, sinpiK, cospiK, dx1.d, dx2.d, dx3.d, dx4.d, sinLB, sinUB, cosLB, cosUB);
    } else {
      step /= 2;
    }
  }
  step = 0x10000000000000llu;
  while (cosLB != -1.0e300 && cosUB != 1.0e300 && step > 0) {
    dx3.d = cosLB;
    dx4.d = cosUB;
    if (dx3.d >= 0.0) {
      if (dx3.x < step) dx3.x = 0x8000000000000000 + step - dx3.x;
      else dx3.x -= step;
    } else dx3.x += step;
    if (dx4.d >= 0.0) dx4.x += step;
    else dx4.x -= step;
    if (OutputCompensation(false, sinpiK, cospiK, sinLB, sinUB, dx3.d, dx4.d, useFMA) <= roundUB) {
      UpdateIntervals(false, sinpiK, cospiK, sinLB, sinUB, dx3.d, dx4.d, sinLB, sinUB, cosLB, cosUB);
    } else {
      step /= 2;
    }
  }
  step = 0x10000000000000llu;
  while (sinLB != -1.0e300 && sinUB != 1.0e300 && step > 0) {
    dx1.d = sinLB;
    dx2.d = sinUB;
    if (dx1.d >= 0.0) {
      if (dx1.x < step) dx1.x = 0x8000000000000000 + step - dx1.x;
      else dx1.x -= step;
    } else dx1.x += step; 
    if (dx2.d >= 0.0) dx2.x += step;
    else dx2.x -= step;
    if (OutputCompensation(false, sinpiK, cospiK, dx1.d, dx2.d, cosLB, cosUB, useFMA) <= roundUB) {
      UpdateIntervals(false, sinpiK, cospiK, dx1.d, dx2.d, cosLB, cosUB, sinLB, sinUB, cosLB, cosUB);
    } else {
      step /= 2;
    }
  }
  if (sinLB > sinUB) {
    printf("LB of sin reduced interval greater than UB for count=%x\n", inputX.x); 
    return false;
  }
  if (cosLB > cosUB) {
    printf("LB of cos reduced interval greater than UB for count=%x\n", inputX.x); 
    return false;
  }
  if (multiRnd) fesetround(ogRnd);
  return true;
}

void ComputeReducedInterval(float_x inputX, double y, FILE* sinIntervals, FILE* cosIntervals, FILE* fdFail, bool multiRnd, bool useFMA) {
  if (ComputeSpecialCase(inputX.f)) return;
  double xp, sinpiK, cospiK;
  int N = RangeReduction(inputX.f, xp);
  GetConsts(N, sinpiK, cospiK);
  double roundLB, roundUB;
  Calc34RNOInterval(y, roundLB, roundUB);
  double sinIntLB, sinIntUB, cosIntLB, cosIntUB;
  SinGuessInitialVal(xp, sinpiK, cospiK, sinIntLB, sinIntUB);
  CosGuessInitialVal(xp, sinpiK, cospiK, cosIntLB, cosIntUB);
  bool success = CalcReducedInterval(inputX, xp, sinpiK, cospiK, sinIntLB, sinIntUB, cosIntLB, cosIntUB, roundLB, roundUB, multiRnd, useFMA);
  if (!success) {
    fprintf(fdFail, "Interval not generatable for count = %x with reduced input %a", inputX.x, xp);
    return;
  } else { 
    double_x intX, sinIntLBX, sinIntUBX, cosIntLBX, cosIntUBX;
    int ogRnd = FE_TONEAREST;
    if (multiRnd) ogRnd = fegetround();
    double finalLB, finalUB;
    if (multiRnd) fesetround(FE_DOWNWARD);
    double ogFinalLB = OutputCompensation(true, sinpiK, cospiK, sinIntLB, sinIntUB, cosIntLB, cosIntUB, useFMA);
    sinIntLBX.d = sinIntLB;
    if (sinIntLB > 0.0) {
      intX.x = sinIntLBX.x - 1;
    } else if (sinIntLB == 0.0) {
      intX.x = 0x80000001;
    } else {
      intX.x = sinIntLBX.x + 1;
    }
    finalLB = OutputCompensation(true, sinpiK, cospiK, intX.d, sinIntUB, cosIntLB, cosIntUB, useFMA);
    if (ogFinalLB != finalLB && roundLB <= finalLB) {
      printf("Sin LB not minimal for count=%x\n", inputX.x);
      exit(0);
    }
    sinIntUBX.d = sinIntUB; 
    if (sinIntUB >= 0.0) {
      intX.x = sinIntUBX.x + 1;
    } else {
      intX.x = sinIntUBX.x - 1;
    }
    finalLB = OutputCompensation(true, sinpiK, cospiK, sinIntLB, intX.d, cosIntLB, cosIntUB, useFMA);
    if (ogFinalLB != finalLB && roundLB <= finalLB) {
      printf("Sin UB not maximal for count=%x\n", inputX.x);
      exit(0);
    }
    cosIntLBX.d = cosIntLB;
    if (cosIntLB > 0.0) {
      intX.x = cosIntLBX.x - 1;
    } else if (cosIntLB == 0.0) {
      intX.x = 0x80000001;
    } else {
      intX.x = cosIntLBX.x + 1;
    }
    finalLB = OutputCompensation(true, sinpiK, cospiK, sinIntLB, sinIntUB, intX.d, cosIntUB, useFMA);
    if (ogFinalLB != finalLB && roundLB <= finalLB) {
      printf("Cos LB not minimal for count=%x\n", inputX.x);
      exit(0);
    }
    cosIntUBX.d = cosIntUB; 
    if (cosIntUB >= 0.0) {
      intX.x = cosIntUBX.x + 1;
    } else {
      intX.x = cosIntUBX.x - 1;
    }
    finalLB = OutputCompensation(true, sinpiK, cospiK, sinIntLB, sinIntUB, cosIntLB, intX.d, useFMA);
    if (ogFinalLB != finalLB && roundLB <= finalLB) {
      printf("Cos UB not maximal for count=%x\n", inputX.x);
      exit(0);
    }
    if (multiRnd) fesetround(FE_UPWARD);
    double ogFinalUB = OutputCompensation(false, sinpiK, cospiK, sinIntLB, sinIntUB, cosIntLB, cosIntUB, useFMA);
    sinIntLBX.d = sinIntLB;
    if (sinIntLB > 0.0) {
      intX.x = sinIntLBX.x - 1;
    } else if (sinIntLB == 0.0) {
      intX.x = 0x80000001;
    } else {
      intX.x = sinIntLBX.x + 1;
    }
    finalUB = OutputCompensation(false, sinpiK, cospiK, intX.d, sinIntUB, cosIntLB, cosIntUB, useFMA);
    if (ogFinalUB != finalUB && finalUB <= roundUB) {
      printf("Sin LB not minimal for count=%x\n", inputX.x);
      exit(0);
    }
    sinIntUBX.d = sinIntUB; 
    if (sinIntUB >= 0.0) {
      intX.x = sinIntUBX.x + 1;
    } else {
      intX.x = sinIntUBX.x - 1;
    }
    finalUB = OutputCompensation(false, sinpiK, cospiK, sinIntLB, intX.d, cosIntLB, cosIntUB, useFMA);
    if (ogFinalUB != finalUB && finalUB <= roundUB) {
      printf("Sin UB not maximal for count=%x\n", inputX.x);
      exit(0);
    }
    cosIntLBX.d = cosIntLB;
    if (cosIntLB > 0.0) {
      intX.x = cosIntLBX.x - 1;
    } else if (cosIntLB == 0.0) {
      intX.x = 0x80000001;
    } else {
      intX.x = cosIntLBX.x + 1;
    }
    finalUB = OutputCompensation(false, sinpiK, cospiK, sinIntLB, sinIntUB, intX.d, cosIntUB, useFMA);
    if (ogFinalUB != finalUB && finalUB <= roundUB) {
      printf("Cos LB not minimal for count=%x\n", inputX.x);
      exit(0);
    }
    cosIntUBX.d = cosIntUB; 
    if (cosIntUB >= 0.0) {
      intX.x = cosIntUBX.x + 1;
    } else {
      intX.x = cosIntUBX.x - 1;
    }
    finalUB = OutputCompensation(false, sinpiK, cospiK, sinIntLB, sinIntUB, cosIntLB, intX.d, useFMA);
    if (ogFinalUB != finalUB && finalUB <= roundUB) {
      printf("Cos UB not maximal for count=%x\n", inputX.x);
      exit(0);
    }
    if (multiRnd) fesetround(ogRnd);
    double data_entry[3];
    data_entry[0] = xp;
    data_entry[1] = sinIntLB;
    data_entry[2] = sinIntUB;
    fwrite(data_entry, sizeof(double), 3, sinIntervals);
    data_entry[0] = xp;
    data_entry[1] = cosIntLB;
    data_entry[2] = cosIntUB;
    fwrite(data_entry, sizeof(double), 3, cosIntervals);
  }
}

void CopyData(double dest[3], double source[3]) {
  for (int i = 0; i < 3; i++) dest[i] = source[i];
}

bool ReadData(FILE* f, double dest[3]) {
  size_t s = fread(dest, sizeof(double), 3, f);
  if (s == 0) return false;
  if (s == 3) return true;
  printf("ReadData needs to read 3 * double data. Seems like we couldn't.\n");
  exit(0);
}

void MergeFiles(string s1, string s2, string d) {
  FILE* f1 = fopen(s1.c_str(), "r");
  FILE* f2 = fopen(s2.c_str(), "r");
  FILE* fd = fopen(d.c_str(), "w");

  int f1Read = 0, f2Read = 0;
  double toAdd[3], f1data[3], f2data[3];
  bool f1More, f2More;

  // Initialize the data:
  f1More = ReadData(f1, f1data);
  f2More = ReadData(f2, f2data);

  if (f1data[0] < f2data[0]) CopyData(toAdd, f1data);
  else CopyData(toAdd, f2data);
  unsigned counter = 0;

  while(true) {
    counter++;
    if (counter >= 1000000) {
      printf("Working with lines %d, %d\r", f1Read, f2Read);
      counter = 0;
    }

    if (f1More && f1data[0] == toAdd[0]) {
      if (f1data[1] > toAdd[1]) toAdd[1] = f1data[1];
      if (f1data[2] < toAdd[2]) toAdd[2] = f1data[2];
      f1More = ReadData(f1, f1data);
      f1Read++;
      continue;
    }
    if (f2More && f2data[0] == toAdd[0]) {
      if (f2data[1] > toAdd[1]) toAdd[1] = f2data[1];
      if (f2data[2] < toAdd[2]) toAdd[2] = f2data[2];
      f2More = ReadData(f2, f2data);
      f2Read++;
      continue;
    }

    // At this point, both f1data[0] and f2data[0] > toAdd[0]. I need to
    // add toAdd[0] to fd file.
    fwrite(toAdd, sizeof(double), 3, fd);

    // Now we need to decide to add either f1data or f2data to toAdd:
    if (!f1More && !f2More) break;

    if (f1More && !f2More) {
      CopyData(toAdd, f1data);
      f1More = ReadData(f1, f1data);
      f1Read++;
    } else if (!f1More && f2More) {
      CopyData(toAdd, f2data);
      f2More = ReadData(f2, f2data);
      f2Read++;
    } else if (f1data[0] < f2data[0]) {
      CopyData(toAdd, f1data);
      f1More = ReadData(f1, f1data);
      f1Read++;
    } else {
      CopyData(toAdd, f2data);
      f2More = ReadData(f2, f2data);
      f2Read++;
    }
  }
  fclose(f1);
  fclose(f2);
  fclose(fd);
}

string GetNewFileName(string tfileName) {
  fileIndex++;
  return tfileName + "_temp" + to_string(fileIndex);
}

void SaveIntervalsToAFile(map<double, IntData> intervals, string newFileName) {
  map<double, IntData>::iterator it;
  printf("Creating file %s\n", newFileName.c_str());
  FILE* tf = fopen(newFileName.c_str(), "w+");
  for (it = intervals.begin(); it != intervals.end(); it++) {
    fwrite(&(it->first), sizeof(double), 1, tf);
    fwrite(&(it->second.lb), sizeof(double), 1, tf);
    fwrite(&(it->second.ub), sizeof(double), 1, tf);
  }
  fclose(tf);
}

void SortIntervalFile(string source, string dest) {
  map<double, IntData> intervals;
  map<double, IntData>::iterator it;
  queue<string> tempFiles;

  FILE* f = fopen(source.c_str(), "r+");
  if (!f) {
    printf("Could not open file\n");
  }
  double data[3];

  // Read intervals into sorted map. Output intervals to temp files, 40M
  // intervals at a time.
  unsigned long long int counter = 0;
  printf("Reading files and splitting to 40million intervals at a time\n");
  while (fread(data, sizeof(double), 3, f) == 3) {
    if (data[1] <= -1.0e300 && data[2] >= 1.0e300) {

    } else {
      /*
      printf("data[0] = %.100e\n", data[0]);
      printf("data[1] = %.100e\n", data[1]);
      printf("data[2] = %.100e\n", data[2]);
      */
      it = intervals.find(data[0]);
      if (it != intervals.end()) {
	  if (data[1] > it->second.lb) it->second.lb = data[1];
	  if (data[2] < it->second.ub) it->second.ub = data[2];
      } else {
	  IntData temp;
	  temp.lb = data[1];
	  temp.ub = data[2];
	  intervals[data[0]] = temp;
      }
    }

    counter++;
    if (counter % 1000000llu == 0llu) {
      printf("counter = %llu, interval.size() = %lu\r", counter, intervals.size());
      fflush(stdout);
    }

    // If there's 40M intervals, then save intervals to a temp file.
    if (intervals.size() == 40000000) {
      printf("Writing a new file\n");
      string newFileName = GetNewFileName(source);
      SaveIntervalsToAFile(intervals, newFileName);
      tempFiles.push(newFileName);
      intervals.clear();
      printf("Done writing a new file\n");
    }
  }

  fclose(f);

  // If there's anything else left, then save leftover to a temp file.
  if (intervals.size() > 0) {
    string newFileName = GetNewFileName(source);
    SaveIntervalsToAFile(intervals, newFileName);
    tempFiles.push(newFileName);
    intervals.clear();
  }

  // Once we created temp files, we read two files at a time from the queue,
  // and combine them. Delete the two old files. Add the new file to the queue.
  while (tempFiles.size() > 1) {
    string tempFile1 = tempFiles.front();
    tempFiles.pop();
    string tempFile2 = tempFiles.front();
    tempFiles.pop();
    string newFileName = GetNewFileName(source);
    MergeFiles(tempFile1, tempFile2, newFileName);
    remove(tempFile1.c_str());
    remove(tempFile2.c_str());

    tempFiles.push(newFileName);
    printf("Merged %s and %s to %s\n", tempFile1.c_str(), tempFile2.c_str(), newFileName.c_str());
  }

  // If there is only one file left in the queue, then we rename it to filename
  string tempFile1 = tempFiles.front();
  tempFiles.pop();
  rename(tempFile1.c_str(), dest.c_str());
}

void CreateIntervalFile(char* sinIntervalFile, char* cosIntervalFile, char* failFile, char* oracleFile, unsigned long countLow, unsigned long long countHigh, bool multiRnd, bool useFMA) {
  if(access(sinIntervalFile, F_OK ) == 0 ) {
    printf("Reduced interval file for sin already exists. Exiting to be safe\n");
    exit(0);
  }
  if(access(cosIntervalFile, F_OK ) == 0 ) {
    printf("Reduced interval file for cos already exists. Exiting to be safe\n");
    exit(0);
  }
  if(access(failFile, F_OK ) == 0 ) {
    printf("Out of bound inputs file already exists. Exiting to be safe\n");
    exit(0);
  }
  if(access(oracleFile, F_OK ) != 0 ) {
    printf("Oracle file does not exist\n");
    exit(0);
  }

  FILE* fd_sin_int = fopen(sinIntervalFile, "w+");
  FILE* fd_cos_int = fopen(cosIntervalFile, "w+");
  FILE* fd_fail = fopen(failFile, "w+");
  FILE* fd_oracle = fopen(oracleFile, "r");

  string sinIntervalFileName = sinIntervalFile;
  string sinIntervalFileUQName = sinIntervalFileName.append("_uq");
  string cosIntervalFileName = cosIntervalFile;
  string cosIntervalFileUQName = cosIntervalFileName.append("_uq");

  float_x inputX;
  double oracleResult;
  for (unsigned long count = 0; count<countLow; count++) { 
    size_t size = fread(&oracleResult, sizeof(double), 1, fd_oracle);
  }
  for (unsigned long count = countLow; count < countHigh; count++) {
    if (count % 0x100000 == 0) { 
      printf("count = %lx\r", count);
      fflush(stdout);
    }
   inputX.x = count;
    size_t size = fread(&oracleResult, sizeof(double), 1, fd_oracle);
    ComputeReducedInterval(inputX, oracleResult, fd_sin_int, fd_cos_int, fd_fail, multiRnd, useFMA);
  }
  printf("\n");
  fclose(fd_sin_int);
  fclose(fd_cos_int);
  fclose(fd_fail);
  fclose(fd_oracle);
  SortIntervalFile(sinIntervalFile, sinIntervalFileUQName);
  SortIntervalFile(cosIntervalFile, cosIntervalFileUQName);
}
