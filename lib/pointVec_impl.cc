/* -*- c++ -*- */
/*
 * Copyright 2022 Avery Moates.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "pointVec_impl.h"
#include <gnuradio/io_signature.h>

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


void pointVec_impl::recievePackage(const pmt::pmt_t& msg){
    message_port_pub(outPort, msg);
}

} /* namespace adsbTestBlocks */
} /* namespace gr */
