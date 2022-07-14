/* -*- c++ -*- */
/*
 * Copyright 2022 Avery Moates.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ADSBTESTBLOCKS_ADSBDECODE_IMPL_H
#define INCLUDED_ADSBTESTBLOCKS_ADSBDECODE_IMPL_H

#include <adsbTestBlocks/adsbDecode.h>
#include "planeInfo.h"

namespace gr {
namespace adsbTestBlocks {

class adsbDecode_impl : public adsbDecode
{
private:
    const pmt::pmt_t outPort;

    const int bits = 112;
    int vecUpdateIndex = 0;
    bool inVector = false;

    std::vector<planeInfo> planes;

    //Helper methods
    int charArrayToDec(char *package, int startIndex, int size);
    std::string charArrayToHex(char *package, int startIndex, int endIndex);
    void recievePackage(const pmt::pmt_t& msg);

    //ADS-B methods
    void decode(char *package, int size, uint64_t timeStamp);
    int calcAltitude(char *bits);

    //Vector methods
    void addToVector(std::string& ICAO, int planeAltitude, char frame, int lat, int lon, uint64_t timeStamp);
    void addToVector(std::string& ICAO, int Vx, int Vy, float speed);
    void updateVector(std::string& ICAO, int planeAltitude, char frame, int lat, int lon, uint64_t timeStamp, int index);
    void updateVector(std::string& ICAO, int Vx, int Vy, float speed, int index);
    void removeFromVector();

    //debug methods
    void displayVector();

public:
    adsbDecode_impl();
    ~adsbDecode_impl();
};

} // namespace adsbTestBlocks
} // namespace gr

#endif /* INCLUDED_ADSBTESTBLOCKS_ADSBDECODE_IMPL_H */
