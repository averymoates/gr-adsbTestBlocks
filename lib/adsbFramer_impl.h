/* -*- c++ -*- */
/*
 * Copyright 2022 Avery Moates.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ADSBTESTBLOCKS_ADSBFRAMER_IMPL_H
#define INCLUDED_ADSBTESTBLOCKS_ADSBFRAMER_IMPL_H

#include <adsbTestBlocks/adsbFramer.h>

namespace gr {
namespace adsbTestBlocks {

class adsbFramer_impl : public adsbFramer
{
private:
    //Samples per Symbol = sample rate / symbol rate
    int sps = (int)(2000000.0f / 1000000.0f);

    const pmt::pmt_t msgPort;
    bool contiunePackage;
    int storedPackInx;
    char storedArray[224] = {};
    
public:
    adsbFramer_impl();
    ~adsbFramer_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace adsbTestBlocks
} // namespace gr

#endif /* INCLUDED_ADSBTESTBLOCKS_ADSBFRAMER_IMPL_H */
