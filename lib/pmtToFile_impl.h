/* -*- c++ -*- */
/*
 * Copyright 2022 Avery Moates.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ADSBTESTBLOCKS_PMTTOFILE_IMPL_H
#define INCLUDED_ADSBTESTBLOCKS_PMTTOFILE_IMPL_H

#include <adsbTestBlocks/pmtToFile.h>
#include <fstream>

namespace gr {
namespace adsbTestBlocks {

class pmtToFile_impl : public pmtToFile
{
private:
    std::string _filename;
    std::ofstream _file;

    bool _test;

    void writeToFile(const pmt::pmt_t& msg);

public:
    pmtToFile_impl(std::string& filename, bool test);
    ~pmtToFile_impl();
};

} // namespace adsbTestBlocks
} // namespace gr

#endif /* INCLUDED_ADSBTESTBLOCKS_PMTTOFILE_IMPL_H */
