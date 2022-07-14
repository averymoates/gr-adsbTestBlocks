/* -*- c++ -*- */
/*
 * Copyright 2022 Avery Moates.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ADSBTESTBLOCKS_ADSBDEMOD_IMPL_H
#define INCLUDED_ADSBTESTBLOCKS_ADSBDEMOD_IMPL_H

#include <adsbTestBlocks/adsbDemod.h>

namespace gr {
namespace adsbTestBlocks {

class adsbDemod_impl : public adsbDemod
{
private:
    const pmt::pmt_t outPort;
    const int sps = 224;

    void recievePackage(const pmt::pmt_t& msg);
    void demod(char *package, int size);


public:
    adsbDemod_impl();
    ~adsbDemod_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace adsbTestBlocks
} // namespace gr

#endif /* INCLUDED_ADSBTESTBLOCKS_ADSBDEMOD_IMPL_H */
