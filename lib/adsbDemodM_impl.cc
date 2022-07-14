/* -*- c++ -*- */
/*
 * Copyright 2022 Avery Moates.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "adsbDemodM_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace adsbTestBlocks {


adsbDemodM::sptr adsbDemodM::make()
{
    return gnuradio::make_block_sptr<adsbDemodM_impl>();
}


/*
 * The private constructor
 */
adsbDemodM_impl::adsbDemodM_impl()
    : gr::block("adsbDemodM",
                gr::io_signature::make(0, 0, 0),
                gr::io_signature::make(0, 0, 0)),
                outPort(pmt::mp("Demod"))
{
    message_port_register_out(outPort);

    message_port_register_in(pmt::mp("Package"));
    set_msg_handler(pmt::mp("Package"),[this](const pmt::pmt_t& msg) {this->recievePackage(msg);});
}

/*
 * Our virtual destructor.
 */
adsbDemodM_impl::~adsbDemodM_impl() {}

//Very simple Pulse Position Demodulation
void adsbDemodM_impl::demod(char *package, int size)
{
    char signal[size/2] = {};
    for(int i=0; i<size/2; ++i){
        //Check for a 0
        if(package[i*2] == 0 && package[i*2+1] == 1){
            signal[i] = 0;
        }
        //Check for a 1
        else if(package[i*2] == 1 && package[i*2+1] == 0){
            signal[i] = 1;
        }
    }

    //Debugging
    std::string info = "[";
    for(int i=0; i<size/2; ++i){
        info += std::to_string(signal[i]);
    }
    info += "]";
    message_port_pub(outPort, pmt::mp(info));

}

//Turning the polymorphic data type into a data type to be used
void adsbDemodM_impl::recievePackage(const pmt::pmt_t& msg)
{
    //Turning the pmt(polymorphic data type) into a string
    std::string s_packet = pmt::symbol_to_string(msg);

    //Creating the array to store the package
    char adsbPackage[sps] = {};

    //Storing the string into the adsbPackage array
    int s_packetIndex = 1;
    for(int i=0; i<sps; ++i){
        int temp = s_packet[s_packetIndex];
        if(temp == 48){
            adsbPackage[i] = 0;
        }
        else if(temp == 49){
            adsbPackage[i] = 1;
        }
        ++s_packetIndex;
    }

    //Call the demod function.
    demod(adsbPackage, sps);

}

} /* namespace adsbTestBlocks */
} /* namespace gr */
