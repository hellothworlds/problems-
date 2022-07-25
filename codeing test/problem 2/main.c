#include <stdio.h>
#include <math.h>
/*Declaration of main function, it declares each Function, that calculates range, bearing. Both from initial and final longitude and latitude.
And final latitude and longitude, from initial longitude, latitude, range and bearing. */
int main()
{
    double glonint = 0, glatint = 0, glonfin = 0, glatfin = 0, bearing = 0, range = 0;    //declaration of variables and functions
    double GID2RadarRange(double glonint, double glatint, double glonfin, double glatfin);
    double GID2RadarBearing(double glonint, double glatint, double glonfin, double glatfin);
    double RtoGlon(double range, double bearing, double glonint, double glatint);
    double RtoGlat(double range, double bearing, double glonint, double glatint);//declaration of variables and functions
    double D = GID2RadarRange(180, 0, 0, 0);
    double An = GID2RadarBearing(180, 0, 0, 0);
    printf("Value of range in m= %f\n", D);
    printf("Value of Bearing in Degrees= %f\n", An);
    double lat = RtoGlat(D, An, 0, 0);
    double lon = RtoGlon(D, An, 0, 0);
    printf("Value of lat in degrees= %f\n", lat);
    printf("Value of lon in Degrees= %f\n", lon);
}
/*this function calculates the range in meters given an initial and final latitude and longitude using the haversine formula */
double GID2RadarRange(double glonint, double glatint, double glonfin, double glatfin) { //range in meters and bearing in degrees, longitude and latitude in degrees.
    double pi = 3.14159265359;
    double lori = glonint * pi / 180;//converting to radians 
    double lorf = glonfin * pi / 180;
    double lati = glatint * pi / 180;
    double latf = glatfin * pi / 180;  //converting to radians 
    double dlon = lori - lorf; //change in longitude 
    double dlat = lati - lati; //change in latitude 
    double R = 6371000; //radius of the earth in meters, change this to earths radius in different unit for other distances
    double a = pow(sin(dlat / 2), 2) + cos(lati) * cos(latf) * pow(sin(dlon / 2), 2); //intermediate to calculate haversine formula
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double range = R * c;  //intermediate to calculate haversine formula
    return(range);
}
/*this function calculates the bearing in meters given an initial and final latitude and longitude using the haversine formula*/
double GID2RadarBearing(double glonint, double glatint, double glonfin, double glatfin) { // final and initial longitude and latitude in degrees. 
    double pi = 3.14159265359;
    double lori = glonint * pi / 180;//converting to radians  
    double lorf = glonfin * pi / 180;
    double lati = glatint * pi / 180;
    double latf = glatfin * pi / 180;  //converting to radians  
    double dlon = lori - lorf; //change in longitude
    double dlat = lati - lati; //change in latitude
    double y = cos(lati) * sin(latf) - sin(lati) * cos(latf) * cos(dlon); //intermediate to calculate haversine formula
    double x = sin(dlon) * cos(latf);
    double bearing = atan2(x, y) * 180 / pi; //intermediate to calculate haversine formula
    return(bearing);
}
/*this function calculates the final longitude in degrees given an initial latitude, longitude, range and bearing.*/
double RtoGlon(double range, double bearing, double glonint, double glatint) { //range in meaters and bearing in degrees, longitude and latitude in degrees.
    double pi = 3.14159265359;
    double R = 6371000; //radius of the earth in meters, change this to earths radius in different unit for other distances
    double loni = glonint * pi / 180;  //converting to radians 
    double lati = glatint * pi / 180;
    double berrad = bearing * pi / 180; //converting to radians  
    double ang = range / R;
    double latf = sin(sin(lati) * cos(ang) + cos(lati) * sin(ang) * cos(berrad));
    double glonfin = loni + atan2(sin(berrad) * sin(ang) * cos(lati), cos(ang) - sin(lati) * sin(latf)) * 180 / pi;
    return(glonfin);
}
/*this function calculates the final latitude in degrees given an initial latitude, longitude, range and bearing.*/
double RtoGlat(double range, double bearing, double glonint, double glatint) { //range in meters (change to different units in order to change output, as well as radius of the earth) and bearing in degrees, longitude and latitude in degrees.
    double pi = 3.14159265359;
    double R = 6371000; //radius of the earth in meters, change this to earths radius in different unit for other distances
    double loni = glonint * pi / 180;  //converting to radians 
    double lati = glatint * pi / 180;
    double berrad = bearing * pi / 180; //converting to radians  
    double ang = range / R; // dividing by radius of the earth in meters, change this to earths radius in different unit for other distances
    double latf = sin(sin(lati) * cos(ang) + cos(lati) * sin(ang) * cos(berrad));
    double glatfin = latf * 180 / pi;
    return(glatfin);
};