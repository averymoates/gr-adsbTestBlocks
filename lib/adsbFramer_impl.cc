/* -*- c++ -*- */
/*
 * Copyright 2022 Avery Moates.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "adsbFramer_impl.h"
#include <gnuradio/io_signature.h>

#include <cstdint>

namespace gr {
namespace adsbTestBlocks {

using input_type = unsigned char;
using output_type = float;

adsbFramer::sptr adsbFramer::make()
{
    return gnuradio::make_block_sptr<adsbFramer_impl>();
}


/*
 * The private constructor
 */
adsbFramer_impl::adsbFramer_impl()
    : gr::sync_block("adsbFramer",
                     gr::io_signature::make(1, 1, sizeof(input_type)),
                     gr::io_signature::make(1, 1, sizeof(output_type))),
                     msgPort(pmt::mp("Package"))
{
    contiunePackage = false;
    set_tag_propagation_policy(TPP_ALL_TO_ALL);
    message_port_register_out(msgPort);
}

/*
 * Our virtual destructor.
 */
adsbFramer_impl::~adsbFramer_impl() {}

int adsbFramer_impl::work(int noutput_items,
                          gr_vector_const_void_star& input_items,
                          gr_vector_void_star& output_items)
{
    const input_type* in = (const input_type*)(input_items[0]);
    output_type* out = (output_type*)(output_items[0]);

    //If there was a portion of a package that was in the previous work call
    if(contiunePackage){
        contiunePackage = false;
        int inIndex = 0;
        for(int i=storedPackInx; i<224; ++i){
            out[inIndex] = (float)(in[inIndex]);
            storedArray[i] = (int)(in[inIndex]);
            ++inIndex;
        }

        //Passing the skipped packet as a message
        std::string info = "[";
        for(int i=0; i<224; ++i){
            info += std::to_string(storedArray[i]);
        }
        info += "]";
        message_port_pub(msgPort,pmt::mp(info));

    }

    uint64_t start_N = nitems_read(0);
    uint64_t end_N = start_N + (uint64_t)(noutput_items);

    //Created the array to store the bits for the ads-b packet
    char package[112*sps] = {};

    //Store the tags in this current work call and find the size.
    std::vector<tag_t> all_tags;
    get_tags_in_range(all_tags, 0, start_N, end_N);
    int size = all_tags.size();

    //Goes through each of the tags in the all_tags vector array.
    int sop_Index, eop_Index;
    for(int i=0; i<size; ++i){
        const tag_t tag = all_tags[i];
        //Start of Package index
        sop_Index = tag.offset - nitems_read(0);
        //End of Package index
        eop_Index = tag.offset + (int)(112*sps) - nitems_read(0);

        //If a package is within this work call
        if(eop_Index < noutput_items){
            int packIndex = 0;

            //Storing the packet into the package array
            for(int index=sop_Index; index<eop_Index; ++index){
                out[index] = (float)(in[index]);
                package[packIndex] = (int)(in[index]);
                ++packIndex;
            }

            //This is for passing the packet as a message
            std::string info = "[";
            for(int index=0; index<packIndex; ++index){
                info += std::to_string(package[index]);
            }
            info += "]";
            message_port_pub(msgPort,pmt::mp(info));
        }

        //If the package is not within this current work call.
        //Store what it can, and then let the next work all do the rest.
        else{
            int packIndex = 0;

            for(int index=sop_Index; index<noutput_items; ++index){
                out[index] = (float)(in[index]);
                storedArray[packIndex] = (int)(in[index]);
                ++packIndex;
            }
            storedPackInx = packIndex;
            contiunePackage = true;
        }
    }
    
    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace adsbTestBlocks */
} /* namespace gr */
