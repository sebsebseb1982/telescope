
void printBignum (String name, BigNumber n) {
  Serial.print(name);
  Serial.print(F("="));
  char * s = n.toString ();
  Serial.println(s);
  free(s);
}

// https://www.instructables.com/Arduino-Star-Finder-for-Telescopes/

void log (String name, double val) {
  Serial.print(name);
  Serial.print(F("="));
  Serial.println(val, 10);
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

/**
   ===================================================================
   CACA Start
   ===================================================================
*/
//Converts UTC (Univeral Time) to GST (Greenwich Sidereal Time).
BigNumber julianDateToGSTOld(
  BigNumber julianDate,
  byte gpsHour,
  byte gpsMinute,
  byte gpsSecond
) {
  BigNumber nbCentury = (julianDate - BigNumber("2451545")) / BigNumber("36525");
  //printBignum("nbCentury old", nbCentury);
  BigNumber step1 = BigNumber("2400.051336") * nbCentury;
  BigNumber step2 = nbCentury.pow(2);
  BigNumber step3 = BigNumber("0.000025862") * step2;
  BigNumber to = BigNumber("6.697374558") + step1 + step3;
  BigNumber n1 = floorBigNumber(to / BigNumber(24));
  to = to - (n1 * BigNumber(24));
  BigNumber timenow =  BigNumber(gpsHour) + ((( BigNumber(gpsSecond) /  BigNumber(60)) +  BigNumber(gpsMinute)) /  BigNumber(60));
  BigNumber h1 = timenow * BigNumber("1.0027379093");
  BigNumber n2 = floorBigNumber ((to + h1) / BigNumber(24));
  BigNumber gst = (to + h1) - (n2 * BigNumber(24));
  return gst;
}
/**
  ===================================================================
  CACA Stop
  ===================================================================
*/

BigNumber julianDayToGST(BigNumber julianDay) {
  // https://www.webastro.net/forums/topic/149877-calculer-lheure-sid%C3%A9rale/?tab=comments#comment-2286131
  /*
    BigNumber nbCentury = (julianDay - BigNumber("2451545")) / BigNumber("36525");
    printBignum("nbCentury new", nbCentury);
    BigNumber sideralTimeInSeconds = BigNumber("24110.54841") + (BigNumber("8640184.812866") * nbCentury) + (BigNumber("0.093104") * nbCentury.pow(2)) - (BigNumber("0.0000062") * nbCentury.pow(3));
    printBignum("sideralTimeInSeconds", sideralTimeInSeconds);
    BigNumber sideralTimeInHours = sideralTimeInSeconds / BigNumber(3600);
    printBignum("sideralTimeInHours", sideralTimeInHours);

    BigNumber nbHoursInADay = BigNumber(24);
    BigNumber greenwichSideralTime = getBigNumberDecimals(sideralTimeInHours / nbHoursInADay) * nbHoursInADay;
    return greenwichSideralTime;
  */

  //https://www.astrochinon.fr/index.php/documents/nos-dossiers/95-le-temps-sideral-de-greenwich
  BigNumber nbCentury = (julianDay - BigNumber("2415020")) / BigNumber("36525");
  //printBignum("T", nbCentury);
  BigNumber sideralTimeInHours = BigNumber("0.276919398") + (BigNumber("100.0021359") * nbCentury) + (BigNumber("0.000001075") * nbCentury.pow(2));
  //printBignum("T1", sideralTimeInHours);
  BigNumber greenwichSideralTime = getBigNumberDecimals(sideralTimeInHours) * BigNumber(24);
  return greenwichSideralTime;
}

//Converts GST (Greenwich Sidereal Time) to LST (Local Sidereal Time).
BigNumber gstToLST(BigNumber gst, float gpsLongitude) {
  BigNumber diff = BigNumber(abs(gpsLongitude)) / BigNumber(15);
  BigNumber lst;
  if ((gpsLongitude * -1) > 0)  {
    gst = gst - diff;
  }  else  {
    gst = gst + diff;
  }

  if (gst > 24)  {
    lst = gst - BigNumber(24);
  }  else if (gst * BigNumber(-1) > 0) {
    lst = gst + BigNumber(24);
  }  else  {
    lst = gst;
  }

  return lst;
}

HorizontalCoordinate getHorizontalCoordinateFromEquatorialCoordinateLSTAndLatitude(EquatorialCoordinate equatorialCoordinate, BigNumber localSideralTime, BigNumber latitude) {
  BigNumber pi = BigNumber("3.1415926535897932384626433832795028841971693993751058209749445923078164062862");
  // https://astronomy.stackexchange.com/questions/13067/conversion-from-equatorial-coordinate-to-horizon-coordinates
  BigNumber rightAscensionInHours = BigNumber(equatorialCoordinate.rightAscension) / BigNumber(15);
  BigNumber declinationInRadians = degreesToRadians(BigNumber(equatorialCoordinate.declination));
  //printBignum("dec new", declinationInRadians);
  BigNumber hourAngleInRadians= degreesToRadians(BigNumber(15) * (localSideralTime - rightAscensionInHours));
  //Serial.print(F(" h : "));
  //Serial.print(h);
  BigNumber latitudeInRadians = degreesToRadians(latitude);
  BigNumber sinDeclination = sinus(declinationInRadians, precision);
  //printBignum("sinDeclination new", sinDeclination);
  //printBignum("latitude", latitude);
  BigNumber sinLatitude = sinus(latitudeInRadians, precision);
  //printBignum("sinLatitude new", sinLatitude);
  BigNumber cosDeclination = cosinus(declinationInRadians, precision);
  //printBignum("cosDeclination new", cosDeclination);
  BigNumber cosLatitude = cosinus(latitudeInRadians, precision);
  //printBignum("cosLatitude new", cosLatitude);
  BigNumber cosHourAngle = cosinus(hourAngleInRadians, precision);
  //printBignum("cosHourAngle new", cosHourAngle);
  BigNumber sinAltitude = (sinDeclination * sinLatitude) + (cosDeclination * cosLatitude * cosHourAngle);
  printBignum("sinAltitude new", sinAltitude);
  BigNumber altitudeInRadians = doubleToBigNumber(asin(bigNumberToDouble(sinAltitude)));
  printBignum("altitudeInRadians1", altitudeInRadians);
  BigNumber cosAltitude = cosinus(altitudeInRadians, precision);
  BigNumber cosAzimuth = (sinDeclination - (sinLatitude * sinAltitude)) / (BigNumber(cosLatitude) * BigNumber(cosAltitude));
  BigNumber azimuthInDegrees = radiansToDegrees(doubleToBigNumber(acos(bigNumberToDouble(cosAzimuth))));
  BigNumber sinHourAngle = sinus(hourAngleInRadians, precision);
  if (sinHourAngle * BigNumber(-1) > 0) {
    azimuthInDegrees = azimuthInDegrees;
  } else {
    azimuthInDegrees = BigNumber(360) - azimuthInDegrees;
  }

  return {
    bigNumberToDouble(radiansToDegrees(altitudeInRadians)),
    bigNumberToDouble(azimuthInDegrees)
  };
}

HorizontalCoordinate caca(EquatorialCoordinate equatorialCoordinate, BigNumber lstBn, TinyGPSPlus gps) {
  double ra; //These variables are used in the calculations, double/float/int/byte depending on the type of number needed.
  double dec;
  ra = (equatorialCoordinate.rightAscension / 15.0);

  float lst = bigNumberToDouble(lstBn);
  //log("lst caca", lst);
  double h = 15.0 * (lst - ra);
  //Serial.print(F(" h : "));
  //Serial.print(h);
  h = (h / 360) * (2 * PI);
  dec = ((equatorialCoordinate.declination / 360) * (2 * PI));
  //log("dec old", dec);
  double sindec = sin(dec);
  //log("sindec old", sindec);
  double sinlat = sin(gps.location.lat());
  //log("latitude old", gps.location.lat());
  //log("sinlat old", sinlat);
  double cosdec = cos(dec);
  //log("cosdec old", cosdec);
  double coslat = cos(gps.location.lat());
  //log("coslat old", coslat);
  double jeremy = cos(h);
  log("cosh old", jeremy);
  //Serial.print(F(" jeremy : "));
  //Serial.print(jeremy);
  double sinalt = (sindec * sinlat) + (cosdec * coslat * jeremy);
  printBignum("sinalt old", sinalt);
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

  return {
    alt,
    az
  };
}

HorizontalCoordinate getHorizontalCoordinateFromEquatorialCoordinate(EquatorialCoordinate equatorialCoordinate) {
  BigNumber julianDay = getJulianDay(
                          gps.date.day(),
                          gps.date.month(),
                          gps.date.year(),
                          gps.time.hour(),
                          gps.time.minute(),
                          gps.time.second()
                        );
  //printBignum("Julian day", julianDay);

  BigNumber gstOld = julianDateToGSTOld(
                       julianDay,
                       gps.time.hour(),
                       gps.time.minute(),
                       gps.time.second()
                     );
  //printBignum("GST old", gstOld);

  //  BigNumber gst = julianDayToGST(julianDay);
  //  printBignum("GST new", gst);

  // https://www.heavens-above.com/whattime.aspx?lat=44.8022&lng=-0.592&loc=Unnamed&alt=0&tz=CET
  BigNumber lst = gstToLST(
                    gstOld,
                    gps.location.lng()
                  );
  //printBignum("LST", lst);

  /*
  HorizontalCoordinate newHC = getHorizontalCoordinateFromEquatorialCoordinateLSTAndLatitude(
                                 equatorialCoordinate,
                                 lst,
                                 doubleToBigNumber(gps.location.lat())
                               );
                               */

  HorizontalCoordinate oldHC = caca(
                                 equatorialCoordinate,
                                 lst,
                                 gps
                               );

  log("alt old", oldHC.altitude);
  //log("alt new", newHC.altitude);
  log("az old", oldHC.azimuth);
  //log("az new", newHC.azimuth);
  return oldHC;

}
