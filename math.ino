
void setupMath(int precision) {
  BigNumber::begin(precision);
}

BigNumber modulo(const BigNumber x, const BigNumber divider) {
  return getBigNumberDecimals(x / divider) * divider;
}

BigNumber sinus(const BigNumber x, int precision) {
  BigNumber bnPrecision = BigNumber(precision);
  BigNumber val = 1;
  const BigNumber one = 1, two = 2;
  while (bnPrecision > 0)
  {
    val = one - val * x * x / (two * bnPrecision) / (two * bnPrecision + one);
    bnPrecision--;
  }
  val = x * val;
  return val;
}

BigNumber cosinus(const BigNumber x, int precision) {
  BigNumber pi = BigNumber("3.1415926535897932384626433832795028841971693993751058209749445923078164062862");
  BigNumber modulo2Pi = modulo(x, BigNumber(2) * pi);

  BigNumber unisgnedCosinus = BigNumber(BigNumber(1) - sinus(x, precision).pow(2)).sqrt();

  if (modulo2Pi > pi / BigNumber(2) && modulo2Pi < (BigNumber(3)*pi) / BigNumber(2)) {
    return unisgnedCosinus * BigNumber(-1);
  } else {
    return unisgnedCosinus;
  }
}

BigNumber asinus(BigNumber x) {


  /*
    BigNumber asinusX = BigNumber(0);
    BigNumber t = BigNumber(0);

    while (t <= x) {
    asinusX += BigNumber(1) / BigNumber(BigNumber(1) - t.pow(2)).sqrt();
    t += x / BigNumber(3);
    }*/
  BigNumber asinusX = BigNumber(x);
  BigNumber coef = BigNumber(1);
  int i = 1;
  while (i < 100) {
    coef *= BigNumber(i) / BigNumber(i + 1);
    asinusX += coef * (x.pow(i + 2) / BigNumber(i + 2));
    i += 2;
  }

  return asinusX;
}

BigNumber acosinus(const BigNumber x) {
  BigNumber pi = BigNumber("3.1415926535897932384626433832795028841971693993751058209749445923078164062862");
  return (pi / BigNumber(2)) - asinus(x);
}

void testTrigo() {
  BigNumber pi = BigNumber("3.1415926535897932384626433832795028841971693993751058209749445923078164062862");
  printBignum("ℼ", pi);
  BigNumber test = sinus(pi, precision);
  printBignum("sinus ℼ", test);
  test = sinus(pi * BigNumber(2), precision);
  printBignum("sinus 2ℼ", test);
  test = sinus(pi / BigNumber(2), precision);
  printBignum("sinus ℼ/2", test);
  test = sinus((BigNumber(3) * pi) / BigNumber(2), precision);
  printBignum("sinus 3ℼ/2", test);

  test = cosinus(pi / BigNumber(3), precision);
  printBignum("cosinus ℼ/3", test);
  test = cosinus(pi, precision);
  printBignum("cosinus ℼ", test);
  test = cosinus(BigNumber(3) * pi, precision);
  printBignum("cosinus 3ℼ", test);
  test = cosinus(pi * BigNumber(2), precision);
  printBignum("cosinus 2ℼ", test);
  test = cosinus(pi / BigNumber(2), precision);
  printBignum("cosinus ℼ/2", test);

  test = asinus(BigNumber("0.966553"));
  printBignum("asinus(0.966553)", test);
  log("asin(0.966553)", asin(0.966553));
  test = asinus(sinus(pi, precision));
  printBignum("asinus(sinus(ℼ))", test);
  test = asinus(sinus(pi / BigNumber(2), precision));
  printBignum("asinus(sinus(ℼ/2))", test);
  test = asinus(sinus((BigNumber(3) * pi) / BigNumber(2), precision));
  printBignum("asinus(sinus(3ℼ/2))", test);


  test = getBigNumberDecimals(BigNumber("0.456"));
  printBignum("decimals(0.456)", test);
  test = getBigNumberDecimals(BigNumber("123.456"));
  printBignum("decimals(123.456)", test);

  test = floorBigNumber(BigNumber("0.456"));
  printBignum("floor(0.456)", test);
  test = floorBigNumber(BigNumber("123.456"));
  printBignum("floor(123.456)", test);

  test = modulo(BigNumber("123.456"), BigNumber(120));
  printBignum("modulo(123.456, 120)", test);
  test = modulo(BigNumber("0.456"), BigNumber(120));
  printBignum("modulo(0.456, 120)", test);

}

BigNumber floorBigNumber(BigNumber bigNumberToFloor) {
  char* tmp = bigNumberToFloor.toString();
  String bigNumberToFloorString = tmp;
  free(tmp);
  String bigNumberToFloorStringFloored = bigNumberToFloorString.substring(0, bigNumberToFloorString.indexOf("."));
  int str_len = bigNumberToFloorStringFloored.length() + 1;
  char char_array[str_len];
  bigNumberToFloorStringFloored.toCharArray(char_array, str_len);
  return BigNumber(char_array);
}

BigNumber getBigNumberDecimals(BigNumber bigNumber) {
  char* tmp = bigNumber.toString();
  String bigNumberString = tmp;
  free(tmp);
  String bigNumberDecimalsString = bigNumberString.substring(bigNumberString.indexOf("."), bigNumberString.length());
  int str_len = bigNumberDecimalsString.length() + 1;
  char char_array[str_len];
  bigNumberDecimalsString.toCharArray(char_array, str_len);
  return BigNumber(char_array);
}

double bigNumberToDouble(BigNumber bigNumber) {
  char * tmp = bigNumber.toString();
  float result = atof(tmp);
  free(tmp);
  return result;
}

BigNumber doubleToBigNumber(double d) {
  char doubleChar[precision * 3];
  dtostrf(d, precision * 3, precision, doubleChar);
  return BigNumber(doubleChar);
}

BigNumber degreesToRadians(BigNumber degrees) {
  BigNumber pi = BigNumber("3.1415926535897932384626433832795028841971693993751058209749445923078164062862");
  return degrees * (pi / BigNumber(180));
}

BigNumber radiansToDegrees(BigNumber radians) {
  BigNumber pi = BigNumber("3.1415926535897932384626433832795028841971693993751058209749445923078164062862");
  return radians * (BigNumber(180) / pi);
}
