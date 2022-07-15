/* -*- c++ -*- */
/*
 * Copyright 2022 Avery Moates.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ADSBTESTBLOCKS_POINTVEC_IMPL_H
#define INCLUDED_ADSBTESTBLOCKS_POINTVEC_IMPL_H

#include <adsbTestBlocks/pointVec.h>

namespace gr {
namespace adsbTestBlocks {

class pointVec_impl : public pointVec
{
private:
    const pmt::pmt_t outPort;

    float _refLat = 0.0f;
    float _refLon = 0.0f;
    int _refAltitude = 0;

    void recievePackage(const pmt::pmt_t& msg);

public:
    pointVec_impl(float refLat, float refLon, int refAltitude);
    ~pointVec_impl();
};

} // namespace adsbTestBlocks
} // namespace gr

#endif /* INCLUDED_ADSBTESTBLOCKS_POINTVEC_IMPL_H */
