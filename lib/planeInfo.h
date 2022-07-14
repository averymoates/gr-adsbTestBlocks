#ifndef PLANE_INFO_HEADER
#define PLANE_INFO_HEADER

#include <cstdint>
#include <string>

class planeInfo
{
private:
    // Plane information
    std::string _ICAO;
    int _altitude;
    float _latitude;
    float _longitude;
    int _packagesRecieved;
    int _Vx;                //East-West velocity component
    int _Vy;                //North-South velocity component
    float _speed;

    float Nz = 15.0f;

    // Calculation information
    bool foundLat = false;
    int _evenFrame[2] = {};
    uint64_t _evenTimeStamp = 0;
    bool _filledEvenFrame = false;

    bool foundLon = false;
    int _oddFrame[2] = {};
    uint64_t _oddTimeStamp = 0;
    bool _filledOddFrame = false;


public:
    // constructor
    planeInfo();
    // destructor
    ~planeInfo();

    // mutators
    void setICAO(std::string& ICAO);
    void setAltitude(int altitude);
    void setEvenFrame(int lat, int lon, uint64_t timeStamp);
    void setOddFrame(int lat, int lon, uint64_t timeStamp);
    void setVx(int Vx);
    void setVy(int Vy);
    void setSpeed(float speed);
    void updatePackage();

    // accessors
    std::string getICAO();
    int getAltitude();
    float getLatitude();
    float getLongitude();
    float getSpeed();
    int getRecPack();

    int getEvenLat();
    int getOddLat();
    int getEvenLon();
    int getOddLon();

    uint64_t getEvenTimestamp();
    uint64_t getOddTimestamp();

    // other
    bool canCalcLatLon();
    bool foundLatLon();
    void calcLat();
    void calcLon();
    int NL(float number);
};

#endif