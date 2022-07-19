/* -*- c++ -*- */
/*
 * Copyright 2022 Avery Moates.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ADSBTESTBLOCKS_PMTTOFILE_H
#define INCLUDED_ADSBTESTBLOCKS_PMTTOFILE_H

#include <gnuradio/block.h>
#include <adsbTestBlocks/api.h>

namespace gr {
namespace adsbTestBlocks {

/*!
 * \brief <+description of block+>
 * \ingroup adsbTestBlocks
 *
 */
class ADSBTESTBLOCKS_API pmtToFile : virtual public gr::block
{
public:
    typedef std::shared_ptr<pmtToFile> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of adsbTestBlocks::pmtToFile.
     *
     * To avoid accidental use of raw pointers, adsbTestBlocks::pmtToFile's
     * constructor is in a private implementation
     * class. adsbTestBlocks::pmtToFile::make is the public interface for
     * creating new instances.
     */
    static sptr make(std::string& filename);
};

} // namespace adsbTestBlocks
} // namespace gr

#endif /* INCLUDED_ADSBTESTBLOCKS_PMTTOFILE_H */
