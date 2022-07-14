/*
 * Copyright 2022 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/***********************************************************************************/
/* This file is automatically generated using bindtool and can be manually edited  */
/* The following lines can be configured to regenerate this file during cmake      */
/* If manual edits are made, the following tags should be modified accordingly.    */
/* BINDTOOL_GEN_AUTOMATIC(0)                                                       */
/* BINDTOOL_USE_PYGCCXML(0)                                                        */
/* BINDTOOL_HEADER_FILE(adsbDemod.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(f6a37c00d718d1c1ab6f16c2c448758e)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <adsbTestBlocks/adsbDemod.h>
// pydoc.h is automatically generated in the build directory
#include <adsbDemod_pydoc.h>

void bind_adsbDemod(py::module& m)
{

    using adsbDemod    = gr::adsbTestBlocks::adsbDemod;


    py::class_<adsbDemod, gr::sync_block, gr::block, gr::basic_block,
        std::shared_ptr<adsbDemod>>(m, "adsbDemod", D(adsbDemod))

        .def(py::init(&adsbDemod::make),
           D(adsbDemod,make)
        )
        



        ;




}







