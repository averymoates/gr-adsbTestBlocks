/* -*- c++ -*- */
/*
 * Copyright 2022 Avery Moates.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ADSBTESTBLOCKS_ADSBDECODE_H
#define INCLUDED_ADSBTESTBLOCKS_ADSBDECODE_H

#include <gnuradio/block.h>
#include <adsbTestBlocks/api.h>

namespace gr {
namespace adsbTestBlocks {

/*!
 * \brief <+description of block+>
 * \ingroup adsbTestBlocks
 *
 */
class ADSBTESTBLOCKS_API adsbDecode : virtual public gr::block
{
public:
    typedef std::shared_ptr<adsbDecode> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of adsbTestBlocks::adsbDecode.
     *
     * To avoid accidental use of raw pointers, adsbTestBlocks::adsbDecode's
     * constructor is in a private implementation
     * class. adsbTestBlocks::adsbDecode::make is the public interface for
     * creating new instances.
     */
    static sptr make();
};

} // namespace adsbTestBlocks
} // namespace gr

#endif /* INCLUDED_ADSBTESTBLOCKS_ADSBDECODE_H */
