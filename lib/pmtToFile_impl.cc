/* -*- c++ -*- */
/*
 * Copyright 2022 Avery Moates.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "pmtToFile_impl.h"
#include <gnuradio/io_signature.h>
#include <iostream>
#include <fstream>

namespace gr {
namespace adsbTestBlocks {


pmtToFile::sptr pmtToFile::make(std::string& filename, bool test)
{
    return gnuradio::make_block_sptr<pmtToFile_impl>(filename, test);
}


/*
 * The private constructor
 */
pmtToFile_impl::pmtToFile_impl(std::string& filename, bool test)
    : gr::block("pmtToFile",
                gr::io_signature::make(0, 0, 0),
                gr::io_signature::make(0, 0, 0)),
                _filename(filename)
{
    _test = test;
    message_port_register_in(pmt::mp("Input"));
    set_msg_handler(pmt::mp("Input"),[this](const pmt::pmt_t& msg){this->writeToFile(msg);});

    _file = std::ofstream(_filename, std::ios::out);
}

/*
 * Our virtual destructor.
 */
pmtToFile_impl::~pmtToFile_impl() {
    _file.close();
}

void pmtToFile_impl::writeToFile(const pmt::pmt_t& msg){
    std::string info = pmt::symbol_to_string(msg);

    if(!_file.is_open() || !_test){

    }
    else{
        _file << info << std::endl;
    }
}



} /* namespace adsbTestBlocks */
} /* namespace gr */
