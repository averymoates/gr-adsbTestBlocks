/* -*- c++ -*- */
/*
 * Copyright 2022 Avery Moates.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ADSBTESTBLOCKS_POINTVEC_H
#define INCLUDED_ADSBTESTBLOCKS_POINTVEC_H

#include <gnuradio/block.h>
#include <adsbTestBlocks/api.h>

namespace gr {
namespace adsbTestBlocks {

/*!
 * \brief <+description of block+>
 * \ingroup adsbTestBlocks
 *
 */
class ADSBTESTBLOCKS_API pointVec : virtual public gr::block
{
public:
    typedef std::shared_ptr<pointVec> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of adsbTestBlocks::pointVec.
     *
     * To avoid accidental use of raw pointers, adsbTestBlocks::pointVec's
     * constructor is in a private implementation
     * class. adsbTestBlocks::pointVec::make is the public interface for
     * creating new instances.
     */
    static sptr make(float refLat = 0.0f, float refLon = 0.0f, int refAltitude = 0);
};

} // namespace adsbTestBlocks
} // namespace gr

#endif /* INCLUDED_ADSBTESTBLOCKS_POINTVEC_H */
