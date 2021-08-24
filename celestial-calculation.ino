
void setupCelestialCalculation() {
  BigNumber::begin(30);
}

// https://www.instructables.com/Arduino-Star-Finder-for-Telescopes/

double timenow;

void printBignum (String name, BigNumber & n)
{
  Serial.print(name);
  Serial.print(F(" : "));
  char * s = n.toString ();
  Serial.println(s);
  free(s);
}

void log (String name, double val){
  Serial.print(name);
  Serial.print(F(" : "));
  Serial.println(val, 10);
}

BigNumber floorBigNumber(BigNumber bigNumberToFloor) {
  String bigNumberToFloorString = bigNumberToFloor.toString();
  String bigNumberToFloorStringFloored = bigNumberToFloorString.substring(0, bigNumberToFloorString.indexOf("."));
  int str_len = bigNumberToFloorStringFloored.length() + 1;
  char char_array[str_len];
  bigNumberToFloorStringFloored.toCharArray(char_array, str_len);
  return BigNumber(char_array);
}

void setTimenow(
  byte gpsDay,
  byte gpsMonth,
  int gpsYear,
  byte gpsHour,
  byte gpsMinute,
  byte gpsSecond
) {
  timenow = ((double)gpsHour + ((((double)gpsSecond / 60.0) + (double)gpsMinute) / 60.0));
}

BigNumber getJulianDay(
  byte day,
  byte month,
  int year,
  byte hour,
  byte minute,
  byte second
) {
  int a = year / 100;
  int b = a / 4;
  long c = 2 - a + b; // -13
  BigNumber e = floorBigNumber(BigNumber("365.25") * BigNumber(year + 4716));
  BigNumber f = floorBigNumber(BigNumber("30.6001") * BigNumber(month + 1));
  return BigNumber(c) + BigNumber(day) + e + f - BigNumber("1524.5") + julianDayFraction(hour, minute, second);
}

BigNumber julianDayFraction(
  byte hour,
  byte minute,
  byte second
) {
  return (BigNumber(hour) / BigNumber(24)) + (BigNumber(minute) / BigNumber(1440)) + (BigNumber(second) / BigNumber(86400));
}

//Converts UTC (Univeral Time) to GST (Greenwich Sidereal Time).
double julianDateToGSTOld(BigNumber julianDate) {
  double s = julianDate - BigNumber("2451545.0");
  double t = s / 36525.0;
  log("t",t);
  double step1 = (2400.051336 * t);
  double step2 = (t * t);
  double step3 = (0.000025862 * step2);
  double to = (6.697374558 + step1 + step3);
  double n1 = floor (to / 24);
  to = to - (n1 * 24);
  double h1 = (timenow * 1.002737909);
  double n2 = floor ((to + h1) / 24.0);
  double gst = (to + h1) - (n2 * 24.0);
  return gst;
}

// https://www.webastro.net/forums/topic/149877-calculer-lheure-sid%C3%A9rale/?tab=comments#comment-2286131
BigNumber julianDayToGST(BigNumber julianDay) {
  BigNumber nbCentury = (julianDay - BigNumber("2451545")) / BigNumber("36525");
  printBignum("nbCentury", nbCentury);
  BigNumber sideralTimeInSeconds = BigNumber("24110.54841") + (BigNumber("8640184.812866") * nbCentury) + (BigNumber("0.093104") * nbCentury.pow(2)) - (BigNumber("0.0000062") * nbCentury.pow(3));
  printBignum("sideralTimeInSeconds", sideralTimeInSeconds);
  BigNumber sideralTimeInHours = sideralTimeInSeconds / BigNumber(3600);
  printBignum("sideralTimeInHours", sideralTimeInHours);

  BigNumber greenwichSideralTime = ((sideralTimeInHours / BigNumber(24)) - floorBigNumber(sideralTimeInHours / BigNumber(24))) * BigNumber(24);
  return greenwichSideralTime;
}

//Converts GST (Greenwich Sidereal Time) to LST (Local Sidereal Time).
float gstToLST(float gst, float gpsLongitude) {
  float gstResult = gst;
  double diff = abs(gpsLongitude);
  diff = (diff / 15);
  double lst;
  if ((gpsLongitude * -1) > 0)
  {
    gstResult = gstResult - diff;
  }
  else
  {
    gstResult = gstResult + diff;
  }
  if (gstResult > 24)
  {
    lst = gstResult - 24;
  }
  else if ((gstResult * -1) > 0) {
    lst = gstResult + 24;
  }
  else
  {
    lst = gstResult;
  }
  return lst;
}

HorizontalCoordinate getHorizontalCoordinateFromEquatorialCoordinate(EquatorialCoordinate equatorialCoordinate, TinyGPSPlus gps) {

  setTimenow(
    gps.date.day(),
    gps.date.month(),
    gps.date.year(),
    gps.time.hour(),
    gps.time.minute(),
    gps.time.second()
  );

  // Serial.print(F("Julian date 1 : "));
  // Serial.print(julianDate, 10);

  BigNumber julianDay = getJulianDay(
                          gps.date.day(),
                          gps.date.month(),
                          gps.date.year(),
                          gps.time.hour(),
                          gps.time.minute(),
                          gps.time.second()
                        );
  printBignum("Julian day", julianDay);

  float gst = julianDateToGSTOld(julianDay);
  Serial.print(F("GST old : "));
  Serial.println(gst, 8);

  BigNumber gstNew = julianDayToGST(julianDay);
  printBignum("GST new", gstNew);

  // https://www.heavens-above.com/whattime.aspx?lat=44.8022&lng=-0.592&loc=Unnamed&alt=0&tz=CET
  float lst = gstToLST(
                gst,
                gps.location.lng()
              );
  //Serial.print(F(" LST : "));
  //Serial.print(lst, 4);

  // https://astronomy.stackexchange.com/questions/13067/conversion-from-equatorial-coordinate-to-horizon-coordinates
  double ra; //These variables are used in the calculations, double/float/int/byte depending on the type of number needed.
  double dec;
  ra = (equatorialCoordinate.rightAscension / 15.0);
  double h = 15.0 * (lst - ra);
  //Serial.print(F(" h : "));
  //Serial.print(h);
  h = (h / 360) * (2 * PI);
  dec = ((equatorialCoordinate.declination / 360) * (2 * PI));
  double sindec = sin(dec);
  double sinlat = sin(gps.location.lat());
  double cosdec = cos(dec);
  double coslat = cos(gps.location.lat());
  double jeremy = cos(h);
  //Serial.print(F(" jeremy : "));
  //Serial.print(jeremy);
  double sinalt = (sindec * sinlat) + (cosdec * coslat * jeremy);
  double alt = asin(sinalt);
  double cosalt = cos(alt);
  alt = ((alt / (2.0 * PI)) * 360);
  double cosaz = (sindec - (sinlat * sinalt)) / (coslat * cosalt);
  double az = ((acos(cosaz)) * 4068.0) / 71.0;
  double sinhh = sin(h);
  if ((sinhh * -1) > 0) {
    az = az;
  } else {
    az = 360.0 - az;
  }



  //GST : 19.8827 LST : 19.8437 h : 95.19 jeremy : -0.09 Altitude : 13.497975349426269531250000000000 Azimuth : 0.823711490631103515625000000000
  //GST : 3.5623 LST : 3.5233 h : -149.62 jeremy : -0.86 Altitude : 13.497975349426269531250000000000 Azimuth : 0.823711490631103515625000000000

  return {
    alt,
    az
  };
}
