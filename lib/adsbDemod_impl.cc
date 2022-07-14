/* -*- c++ -*- */
/*
 * Copyright 2022 Avery Moates.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "adsbDemod_impl.h"
#include <gnuradio/io_signature.h>

#include <cstring>

namespace gr {
namespace adsbTestBlocks {

using input_type = float;
using output_type = float;

adsbDemod::sptr adsbDemod::make() 
{ 
    return gnuradio::make_block_sptr<adsbDemod_impl>(); 
    
}

/*
 * The private constructor
 */
adsbDemod_impl::adsbDemod_impl()
    : gr::sync_block("adsbDemod",
                     gr::io_signature::make(1, 1, sizeof(input_type)),
                     gr::io_signature::make(1, 1, sizeof(output_type))),
                     outPort(pmt::mp("Demod"))
{
    message_port_register_out(outPort);

    message_port_register_in(pmt::mp("Package"));
    set_msg_handler(pmt::mp("Package"),[this](const pmt::pmt_t& msg) {this->recievePackage(msg);});
}

/*
 * Our virtual destructor.
 */
adsbDemod_impl::~adsbDemod_impl() {}

//Very simple Pulse Position Demodulation
void adsbDemod_impl::demod(char *package, int size)
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
void adsbDemod_impl::recievePackage(const pmt::pmt_t& msg)
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

    //Debugging
    // std::string info = "[";
    // for(int i=0; i<sps; ++i){
    //     info += std::to_string(adsbPackage[i]);
    // }
    // info += "]";
    // message_port_pub(outPort, pmt::mp(info));

    //Call the demod function.
    demod(adsbPackage, sps);

}

//Need to find a way to get rid of this function/method
int adsbDemod_impl::work(int noutput_items,
                         gr_vector_const_void_star& input_items,
                         gr_vector_void_star& output_items)
{
    auto in = static_cast<const input_type*>(input_items[0]);
    auto out = static_cast<output_type*>(output_items[0]);

    // Do <+signal processing+>
    for(int i=0; i<noutput_items; ++i){
        out[i] = in[i];
    }
    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace adsbTestBlocks */
} /* namespace gr */
