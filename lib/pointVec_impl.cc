/* -*- c++ -*- */
/*
 * Copyright 2022 Avery Moates.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "pointVec_impl.h"
#include <gnuradio/io_signature.h>

#include <cmath>

namespace gr {
namespace adsbTestBlocks {

pointVec::sptr pointVec::make(float refLat, float refLon, int refAltitude)
{
    return gnuradio::make_block_sptr<pointVec_impl>(refLat, refLon, refAltitude);
}


/*
 * The private constructor
 */
pointVec_impl::pointVec_impl(float refLat, float refLon, int refAltitude)
    : gr::block("pointVec",
                gr::io_signature::make(0, 0, 0),
                gr::io_signature::make(0, 0, 0)),
                outPort(pmt::mp("Output"))
{

    _refLat = refLat;
    _refLon = refLon;
    _refAltitude = refAltitude;

    message_port_register_out(outPort);

    message_port_register_in(pmt::mp("Input"));
    set_msg_handler(pmt::mp("Input"),[this](const pmt::pmt_t& msg) { this->recievePackage(msg); });

}

/*
 * Our virtual destructor.
 */
pointVec_impl::~pointVec_impl() {}

float pointVec_impl::getBearing(float lat, float lon){
    float rlat = lat*(M_PI/180.0f);
    float rlon = lon*(M_PI/180.0f);
    float rrefLat = _refLat*(M_PI/180.0f);
    float rrefLon = _refLon*(M_PI/180.0f);
    float deltaLon = rlon - rrefLon;
    float y = sin(deltaLon)*cos(rlat);
    float x = cos(rrefLat)*sin(rlat)-sin(rrefLat)*cos(rlat)*cos(deltaLon);
    float bearing = atan2(y,x)*(180.0f/M_PI) + 360.0f;
    return bearing;
}

void pointVec_impl::recievePackage(const pmt::pmt_t& msg){

    std::stringstream package(pmt::symbol_to_string(msg));
    std::string segment;
    std::vector<std::string> planeInfo;

    while(std::getline(package, segment, ',')){
        planeInfo.push_back(segment);
    }
    std::string ICAO = planeInfo[0];
    int altitude = std::stoi(planeInfo[1]);
    float lat = std::stof(planeInfo[2]);
    float lon = std::stof(planeInfo[3]);

    float bearing = 0.0f;
    bool hasBearing = false;
    if(lat >= (_refLat + 2.0f) || lon >= (_refLon + 2.0f) || lat < (_refLat - 2.0f) || lon < (_refLon - 2.0f)){
        hasBearing = false;
    }
    else{
        hasBearing = true;
        bearing = getBearing(lat, lon);
    }
    
    if(hasBearing){
        std::string info = ICAO;
        info += "\nBearing :";
        info += std::to_string(bearing);
    

        message_port_pub(outPort, pmt::mp(info));
    }

    
}

} /* namespace adsbTestBlocks */
} /* namespace gr */
