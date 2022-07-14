/* -*- c++ -*- */
/*
 * Copyright 2022 Avery Moates.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ADSBTESTBLOCKS_ADSBDEMODM_IMPL_H
#define INCLUDED_ADSBTESTBLOCKS_ADSBDEMODM_IMPL_H

#include <adsbTestBlocks/adsbDemodM.h>

namespace gr {
namespace adsbTestBlocks {

class adsbDemodM_impl : public adsbDemodM
{
private:
    const pmt::pmt_t outPort;
    const int sps = 224;

    void recievePackage(const pmt::pmt_t& msg);
    void demod(char *package, int size);


public:
    adsbDemodM_impl();
    ~adsbDemodM_impl();

};

} // namespace adsbTestBlocks
} // namespace gr

#endif /* INCLUDED_ADSBTESTBLOCKS_ADSBDEMODM_IMPL_H */
