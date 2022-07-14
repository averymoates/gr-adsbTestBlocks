#include "planeInfo.h"
#include <math.h>
#include <algorithm>
#include <string>

planeInfo::planeInfo()
{
    _ICAO = "";
    _altitude = 0;
    _latitude = 0.0f;
    _longitude = 0.0f;
    _packagesRecieved = 0;
    _Vx = 0;
    _Vy = 0;
    _speed = 0.0f;
}

planeInfo::~planeInfo() {}

// Mutators
void planeInfo::setICAO(std::string& ICAO) { _ICAO = ICAO; }

void planeInfo::setAltitude(int altitude) { _altitude = altitude; }

void planeInfo::setEvenFrame(int lat, int lon, uint64_t timeStamp)
{
    _evenFrame[0] = lat;
    _evenFrame[1] = lon;
    _evenTimeStamp = timeStamp;
    _filledEvenFrame = true;
}

void planeInfo::setOddFrame(int lat, int lon, uint64_t timeStamp)
{
    _oddFrame[0] = lat;
    _oddFrame[1] = lon;
    _oddTimeStamp = timeStamp;
    _filledOddFrame = true;
}

void planeInfo::setVx(int Vx) { _Vx = Vx; }

void planeInfo::setVy(int Vy) { _Vy = Vy; }

void planeInfo::setSpeed(float speed) { _speed = speed; }

void planeInfo::updatePackage() { ++_packagesRecieved; }

// Accessors
std::string planeInfo::getICAO() { return _ICAO; }

int planeInfo::getAltitude() { return _altitude; }

float planeInfo::getLatitude() { return _latitude; }

float planeInfo::getLongitude() { return _longitude; }

float planeInfo::getSpeed() { return _speed; }

int planeInfo::getEvenLat() { return _evenFrame[0]; }

int planeInfo::getOddLat() { return _oddFrame[0]; }

int planeInfo::getEvenLon() { return _evenFrame[1]; }

int planeInfo::getOddLon() { return _oddFrame[1]; }

uint64_t planeInfo::getEvenTimestamp() { return _evenTimeStamp; }

uint64_t planeInfo::getOddTimestamp() { return _oddTimeStamp; }

int planeInfo::getRecPack() { return _packagesRecieved; }

// Other
bool planeInfo::canCalcLatLon()
{
    if (_filledEvenFrame == true && _filledOddFrame == true) {
        return true;
    } else {
        return false;
    }
}

bool planeInfo::foundLatLon()
{
    if (foundLat == true && foundLon == true) {
        return true;
    } else {
        return false;
    }
}

int planeInfo::NL(float number)
{
    float a = 2.0f * M_PI;
    float c = 1.0f - ((float)cos(M_PI / (2.0f * Nz)));
    float d = (float)pow(cos(((M_PI) / (180.0f)) * number), 2.0f);
    float b = acos(1.0f - (c) / (d));

    return std::floor((a) / (b));
}

void planeInfo::calcLat()
{
    int seventeenBits = 131072;

    float latCPREven = ((float)_evenFrame[0]) / ((float)seventeenBits);
    float latCPROdd = ((float)_oddFrame[0]) / ((float)seventeenBits);

    float dLatEven = 360.0f / (4.0f * Nz);
    float dLatOdd = 360.0f / (4.0f * Nz - 1.0f);

    int j = std::floor(59.0f * latCPREven - 60.0f * latCPROdd + (1.0f / 2.0f));

    float latEven = dLatEven * (((float)(j % 60)) + latCPREven);
    float latOdd = dLatOdd * (((float)(j % 59)) + latCPROdd);

    if (latEven >= 270.0f) {
        latEven = latEven - 360.0f;
    }

    if (latOdd >= 270.0f) {
        latOdd = latOdd - 360.0f;
    }

    if (NL(latEven) == NL(latOdd)) {
        foundLat = true;
        if (_evenTimeStamp >= _oddTimeStamp) {
            _latitude = latEven;
        } else if (_oddTimeStamp > _evenTimeStamp) {
            _latitude = latOdd;
        }
    }

    else if (NL(latEven) != NL(latOdd)) {
        foundLat = false;
        foundLon = false;
    }
}

void planeInfo::calcLon()
{
    if (foundLat) {
        int seventeenBits = 131072;

        float lonCPREven = ((float)_evenFrame[1]) / ((float)seventeenBits);
        float lonCRPOdd = ((float)_oddFrame[1]) / ((float)seventeenBits);

        int m = std::floor(lonCPREven * (((float)NL(_latitude)) - 1.0f) -
                           lonCRPOdd * (((float)NL(_latitude))) + (1.0f / 2.0f));

        int nEven = std::max(NL(_latitude), 1);
        int nOdd = std::max(NL(_latitude - 1.0f), 1);

        float dLonEven = 360.0f / ((float)nEven);
        float dLonOdd = 360.0f / ((float)nOdd);

        float lonEven = dLonEven * (((float)(m % nEven)) + lonCPREven);
        float lonOdd = dLonEven * (((float)(m % nOdd)) + lonCRPOdd);

        if (_evenTimeStamp >= _oddTimeStamp) {
            _longitude = lonEven;
        } else {
            _longitude = lonOdd;
        }

        if (_longitude >= 180.0f) {
            _longitude = _longitude - 360.0f;
        }
        foundLon = true;
    } else {
        foundLon = false;
    }
}