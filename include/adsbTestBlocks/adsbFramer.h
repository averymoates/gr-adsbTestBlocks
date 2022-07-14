/* -*- c++ -*- */
/*
 * Copyright 2022 Avery Moates.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ADSBTESTBLOCKS_ADSBFRAMER_H
#define INCLUDED_ADSBTESTBLOCKS_ADSBFRAMER_H

#include <gnuradio/sync_block.h>
#include <adsbTestBlocks/api.h>

namespace gr {
namespace adsbTestBlocks {

/*!
 * \brief <+description of block+>
 * \ingroup adsbTestBlocks
 *
 */
class ADSBTESTBLOCKS_API adsbFramer : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<adsbFramer> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of adsbTestBlocks::adsbFramer.
     *
     * To avoid accidental use of raw pointers, adsbTestBlocks::adsbFramer's
     * constructor is in a private implementation
     * class. adsbTestBlocks::adsbFramer::make is the public interface for
     * creating new instances.
     */
    static sptr make();
};

} // namespace adsbTestBlocks
} // namespace gr

#endif /* INCLUDED_ADSBTESTBLOCKS_ADSBFRAMER_H */
