/* -*- c++ -*- */
/*
 * Copyright 2022 Avery Moates.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "adsbDecode_impl.h"
#include "planeInfo.h"
#include <gnuradio/io_signature.h>
#include <chrono>
#include <cmath>
#include <string>

namespace gr {
namespace adsbTestBlocks {

adsbDecode::sptr adsbDecode::make()
{
    return gnuradio::make_block_sptr<adsbDecode_impl>();
}


/*
 * The private constructor
 */
adsbDecode_impl::adsbDecode_impl()
    : gr::block(
          "adsbDecode",
            gr::io_signature::make(0, 0, 0),
            gr::io_signature::make(0, 0, 0)),
            outPort(pmt::mp("Output"))
{
    message_port_register_out(outPort);

    message_port_register_in(pmt::mp("Input"));
    set_msg_handler(pmt::mp("Input"),
                    [this](const pmt::pmt_t& msg) { this->recievePackage(msg); });
}

/*
 * Our virtual destructor.
 */
adsbDecode_impl::~adsbDecode_impl() {}

int adsbDecode_impl::charArrayToDec(char* package, int startIndex, int endIndex)
{
    int decimal = 0;
    int packageIndex = endIndex;
    int size = (endIndex - startIndex) + 1;
    for (int i = 0; i < size; ++i) {
        if (package[packageIndex] == 1) {
            decimal += pow(2, i);
        }
        --packageIndex;
    }
    return decimal;
}

std::string adsbDecode_impl::charArrayToHex(char* package, int startIndex, int endIndex)
{
    std::string ICAO = "";
    int stop = endIndex;

    for (int i = startIndex; i < stop; i += 4) {
        // 0000 = 0
        if (package[i] == 0 && package[i + 1] == 0 && package[i + 2] == 0 &&
            package[i + 3] == 0) {
            ICAO += "0";
        }
        // 0001 = 1
        else if (package[i] == 0 && package[i + 1] == 0 && package[i + 2] == 0 &&
                 package[i + 3] == 1) {
            ICAO += "1";
        }
        // 0010 = 2
        else if (package[i] == 0 && package[i + 1] == 0 && package[i + 2] == 1 &&
                 package[i + 3] == 0) {
            ICAO += "2";
        }
        // 0011 = 3
        else if (package[i] == 0 && package[i + 1] == 0 && package[i + 2] == 1 &&
                 package[i + 3] == 1) {
            ICAO += "3";
        }
        // 0100 = 4
        else if (package[i] == 0 && package[i + 1] == 1 && package[i + 2] == 0 &&
                 package[i + 3] == 0) {
            ICAO += "4";
        }
        // 0101 = 5
        else if (package[i] == 0 && package[i + 1] == 1 && package[i + 2] == 0 &&
                 package[i + 3] == 1) {
            ICAO += "5";
        }
        // 0110 = 6
        else if (package[i] == 0 && package[i + 1] == 1 && package[i + 2] == 1 &&
                 package[i + 3] == 0) {
            ICAO += "6";
        }
        // 0111 = 7
        else if (package[i] == 0 && package[i + 1] == 1 && package[i + 2] == 1 &&
                 package[i + 3] == 1) {
            ICAO += "7";
        }
        // 1000 = 8
        else if (package[i] == 1 && package[i + 1] == 0 && package[i + 2] == 0 &&
                 package[i + 3] == 0) {
            ICAO += "8";
        }
        // 1001 = 9
        else if (package[i] == 1 && package[i + 1] == 0 && package[i + 2] == 0 &&
                 package[i + 3] == 1) {
            ICAO += "9";
        }
        // 1010 = A
        else if (package[i] == 1 && package[i + 1] == 0 && package[i + 2] == 1 &&
                 package[i + 3] == 0) {
            ICAO += "A";
        }
        // 1011 = B
        else if (package[i] == 1 && package[i + 1] == 0 && package[i + 2] == 1 &&
                 package[i + 3] == 1) {
            ICAO += "B";
        }
        // 1100 = C
        else if (package[i] == 1 && package[i + 1] == 1 && package[i + 2] == 0 &&
                 package[i + 3] == 0) {
            ICAO += "C";
        }
        // 1101 = D
        else if (package[i] == 1 && package[i + 1] == 1 && package[i + 2] == 0 &&
                 package[i + 3] == 1) {
            ICAO += "D";
        }
        // 1110 = E
        else if (package[i] == 1 && package[i + 1] == 1 && package[i + 2] == 1 &&
                 package[i + 3] == 0) {
            ICAO += "E";
        }
        // 1111 = F
        else if (package[i] == 1 && package[i + 1] == 1 && package[i + 2] == 1 &&
                 package[i + 3] == 1) {
            ICAO += "F";
        }
    }

    return ICAO;
}

int adsbDecode_impl::calcAltitude(char* bits)
{
    char ALT[11] = {};
    int index = 0;
    for (int i = 40; i < 52; ++i) {
        if (i != 47) {
            ALT[index] = bits[i];
            ++index;
        }
    }
    int n = charArrayToDec(ALT, 0, 10);
    int altitude = 0;
    if (n == 0) {
        altitude = 0;
    } else if (bits[47] == 1) {
        altitude = 25 * n - 1000;
    } else if (bits[47] == 0) {
        altitude = 100 * n - 1000;
    }
    return altitude;
}

void adsbDecode_impl::addToVector(std::string& ICAO,
                                  int planeAltitude,
                                  char frame,
                                  int lat,
                                  int lon,
                                  uint64_t timeStamp)
{
    planeInfo plane;

    plane.updatePackage();
    plane.setICAO(ICAO);
    plane.setAltitude(planeAltitude);
    // Even frame
    if (frame == 0) {
        plane.setEvenFrame(lat, lon, timeStamp);
    }
    // Odd frame
    else if (frame == 1) {
        plane.setOddFrame(lat, lon, timeStamp);
    }

    planes.push_back(plane);
}

void adsbDecode_impl::addToVector(std::string& ICAO, int Vx, int Vy, float speed)
{
    planeInfo plane;

    plane.updatePackage();
    plane.setVx(Vx);
    plane.setVy(Vy);
    plane.setSpeed(speed);

    planes.push_back(plane);
}

void adsbDecode_impl::updateVector(std::string& ICAO,
                                   int planeAltitude,
                                   char frame,
                                   int lat,
                                   int lon,
                                   uint64_t timeStamp,
                                   int index)
{
    planes[index].updatePackage();
    planes[index].setICAO(ICAO);
    planes[index].setAltitude(planeAltitude);
    // Even frame
    if (frame == 0) {
        planes[index].setEvenFrame(lat, lon, timeStamp);
    }
    // Odd frame
    else if (frame == 1) {
        planes[index].setOddFrame(lat, lon, timeStamp);
    }

    // Checks if both frames are filled
    if (planes[index].canCalcLatLon()) {
        planes[index].calcLat();
        planes[index].calcLon();
    }
}

void adsbDecode_impl::updateVector(
    std::string& ICAO, int Vx, int Vy, float speed, int index)
{
    planes[index].updatePackage();
    planes[index].setICAO(ICAO);
    planes[index].setVx(Vx);
    planes[index].setVy(Vy);
    planes[index].setSpeed(speed);
}

void adsbDecode_impl::removeFromVector() { planes.erase(planes.begin()); }

void adsbDecode_impl::displayVector()
{

    for (int i = 0; i < planes.size(); ++i) {
        
        if (planes[i].foundLatLon()) {
            std::string info = "";
            info += planes[i].getICAO();
            info += ",";
            info += std::to_string(planes[i].getAltitude());

            if (planes[i].canCalcLatLon()) {

                // info += "\nEven frame: ";
                // info += std::to_string(planes[i].getEvenLat());
                // info += ", ";
                // info += std::to_string(planes[i].getEvenLon());
                // info += "\nEven timestamp: ";
                // info += std::to_string(planes[i].getEvenTimestamp());

                // info += "\nOdd frame: ";
                // info += std::to_string(planes[i].getOddLat());
                // info += ", ";
                // info += std::to_string(planes[i].getOddLon());
                // info += "\nOdd timestamp: ";
                // info += std::to_string(planes[i].getOddTimestamp());

                info += ",";
                info += std::to_string(planes[i].getLatitude());
                info += ",";
                info += std::to_string(planes[i].getLongitude());
                info += ",";
                info += std::to_string(planes[i].getSpeed());
            }
            message_port_pub(outPort, pmt::mp(info));

        }
    }

}

void adsbDecode_impl::decode(char* package, int size, uint64_t timeStamp)
{
    // Downlink format
    int DF = charArrayToDec(package, 0, 4);

    // When downlink format is 17
    if (DF == 17) {
        std::string ICAO = charArrayToHex(package, 8, 31);
        for (int i = 0; i < planes.size(); ++i) {
            if (planes[i].getICAO() == ICAO) {
                inVector = true;
                vecUpdateIndex = i;
                break;
            } else {
                inVector = false;
            }
        }

        // Find the type code
        int TC = charArrayToDec(package, 32, 36);

        // TC = 1-4 Aircraft identification *This will be worked on later

        // TC = 9-18 barometric altitude.
        if (TC >= 9 && TC <= 18) {

            int altitude = calcAltitude(package);

            char frame = package[53];
            int encodedLat = charArrayToDec(package, 54, 70);
            int encodedLon = charArrayToDec(package, 71, 87);

            if (inVector) {
                updateVector(ICAO,
                             altitude,
                             frame,
                             encodedLat,
                             encodedLon,
                             timeStamp,
                             vecUpdateIndex);

            } else {
                addToVector(ICAO, altitude, frame, encodedLat, encodedLon, timeStamp);
            }
        }

        // TC = 19 Airborne velocity
        if (TC == 19) {
            int subType = charArrayToDec(package, 37, 39);

            if (subType == 1) {
                bool Dew = package[45];
                bool Dns = package[56];

                int Vew = charArrayToDec(package, 46, 55);
                int Vns = charArrayToDec(package, 57, 66);

                int Vx, Vy;

                if (Dew == 0) {
                    Vx = Vew - 1;
                } else if (Dew == 1) {
                    Vx = -1 * (Vew - 1);
                }

                if (Dns == 0) {
                    Vy = Vns - 1;
                } else if (Dns == 1) {
                    Vy = -1 * (Vns - 1);
                }

                float speed = sqrt(pow(Vx, 2) + pow(Vy, 2));

                if (inVector) {
                    updateVector(ICAO, Vx, Vy, speed, vecUpdateIndex);
                } else {
                    addToVector(ICAO, Vx, Vy, speed);
                }
            }
        }

        // This is to cap the size of the vector
        if (planes.size() > 30) {
            removeFromVector();
        }

        displayVector();
    }
}

// Turning the polymorphic data type into a data type to be used
void adsbDecode_impl::recievePackage(const pmt::pmt_t& msg)
{
    std::chrono::high_resolution_clock m_clock;
    uint64_t timeStamp = std::chrono::duration_cast<std::chrono::nanoseconds>(
                                     m_clock.now().time_since_epoch())
                                     .count();
    // Turning the pmt(polymorphic data type) into a string
    std::string s_packet = pmt::symbol_to_string(msg);

    // Creating the array to store the package
    char adsbPackage[bits] = {};

    // Storing the string into the adsbPackage array
    int s_packetIndex = 1;
    for (int i = 0; i < bits; ++i) {
        int temp = s_packet[s_packetIndex];
        if (temp == 48) {
            adsbPackage[i] = 0;
        } else if (temp == 49) {
            adsbPackage[i] = 1;
        }
        ++s_packetIndex;
    }

    decode(adsbPackage, bits, timeStamp);
}

} /* namespace adsbTestBlocks */
} /* namespace gr */
