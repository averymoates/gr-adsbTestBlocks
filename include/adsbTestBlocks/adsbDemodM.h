/* -*- c++ -*- */
/*
 * Copyright 2022 Avery Moates.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ADSBTESTBLOCKS_ADSBDEMODM_H
#define INCLUDED_ADSBTESTBLOCKS_ADSBDEMODM_H

#include <gnuradio/block.h>
#include <adsbTestBlocks/api.h>

namespace gr {
namespace adsbTestBlocks {

/*!
 * \brief <+description of block+>
 * \ingroup adsbTestBlocks
 *
 */
class ADSBTESTBLOCKS_API adsbDemodM : virtual public gr::block
{
public:
    typedef std::shared_ptr<adsbDemodM> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of adsbTestBlocks::adsbDemodM.
     *
     * To avoid accidental use of raw pointers, adsbTestBlocks::adsbDemodM's
     * constructor is in a private implementation
     * class. adsbTestBlocks::adsbDemodM::make is the public interface for
     * creating new instances.
     */
    static sptr make();
};

} // namespace adsbTestBlocks
} // namespace gr

#endif /* INCLUDED_ADSBTESTBLOCKS_ADSBDEMODM_H */
