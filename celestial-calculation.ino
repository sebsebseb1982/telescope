
// https://www.instructables.com/Arduino-Star-Finder-for-Telescopes/

double timenow;

float utcToJulianDate(
  byte gpsDay,
  byte gpsMonth,
  int gpsYear,
  byte gpsHour,
  byte gpsMinute,
  byte gpsSecond
) {
  timenow = ((double)gpsHour + ((((double)gpsSecond / 60.0) + (double)gpsMinute) / 60.0));
  /*
    Serial.print(F("Timenow : "));
    Serial.println(timenow);
  */
  float thisday = ((gpsDay - 1.0) + (timenow / 24.0));
  if (gpsMonth == 1 || gpsMonth == 2) {
    gpsMonth = gpsMonth + 12;
    gpsYear = gpsYear - 1;
  }
  int a = floor ((double)gpsYear / 100);
  int b = 2 - a + floor (a / 4);
  long c = (365.25 * (double)gpsYear);
  float d = floor (30.6001 * ((double)gpsMonth + 1));
  float jd = b + c + d + (double)thisday + 1720994.5;
  return jd;
}

//Converts UTC (Univeral Time) to GST (Greenwich Sidereal Time).
float julianDateToGST(float julianDate) {
  double s = julianDate - 2451545.0;
  double t = s / 36525.0;
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
   /* Serial.print(F("Centisecond : "));
    Serial.println(gps.time.centisecond());*/
  
  float julianDate = utcToJulianDate(
                       gps.date.day(),
                       gps.date.month(),
                       gps.date.year(),
                       gps.time.hour(),
                       gps.time.minute(),
                       gps.time.second()
                     );
  

  

  float gst = julianDateToGST(julianDate);
  Serial.print(F("GST : "));
  Serial.print(gst, 4);

  // https://www.heavens-above.com/whattime.aspx?lat=44.8022&lng=-0.592&loc=Unnamed&alt=0&tz=CET
  float lst = gstToLST(
                gst,
                gps.location.lng()
              );
  Serial.print(F(" LST : "));
  Serial.print(lst, 4);

// https://astronomy.stackexchange.com/questions/13067/conversion-from-equatorial-coordinate-to-horizon-coordinates
  double ra; //These variables are used in the calculations, double/float/int/byte depending on the type of number needed.
  double dec;
  ra = (equatorialCoordinate.rightAscension / 15);
  double h = 15.0 * (lst - ra);
    Serial.print(F(" h : "));
  Serial.print(h);
  h = (h / 360) * (2 * PI);
  dec = ((equatorialCoordinate.declination / 360) * (2 * PI));
  double sindec = sin(dec);
  double sinlat = sin(gps.location.lat());
  double cosdec = cos(dec);
  double coslat = cos(gps.location.lat());
  double jeremy = cos(h);
      Serial.print(F(" jeremy : "));
  Serial.print(jeremy);
  double sinalt = (sindec * sinlat) + (cosdec * coslat * jeremy);
  double alt = asin(sinalt);
  double cosalt = cos(alt);
  alt = ((alt / (2 * PI)) * 360);
  double cosaz = (sindec - (sinlat * sinalt)) / (coslat * cosalt);
  double az = ((acos(cosaz)) * 4068) / 71;
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
