/*
    Copyright (c) 2002-2009 Tampere University.

    This file is part of TTA-Based Codesign Environment (TCE).

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
 */
/**
 * @file HWBlockArchitecture.cc
 *
 * Implementation of HWBlockArchitecture class.
 *
 * @author Lasse Laasonen 2006 (lasse.laasonen-no.spam-tut.fi)
 * @note rating: red
 */

#include "HWBlockArchitecture.hh"

/**
 * The constructor.
 */
HWBlockArchitecture::HWBlockArchitecture() :
    hasID_(false), id_(0) {
}


/**
 * The destructor.
 */
HWBlockArchitecture::~HWBlockArchitecture() {
}


/**
 * Tells whether the entry has an ID.
 *
 * @return True if the entry has an ID, otherwise false.
 */
bool
HWBlockArchitecture::hasID() const {
    return hasID_;
}


/**
 * Sets the ID for the entry.
 *
 * @param id The ID to set.
 */
void
HWBlockArchitecture::setID(RowID id) {
    hasID_ = true;
    id_ = id;
}


/**
 * Returns the ID of the entry.
 *
 * @return ID of the entry.
 */
RowID
HWBlockArchitecture::id() const 
    throw (NotAvailable) {

    if (!hasID()) {
        throw NotAvailable(__FILE__, __LINE__, __func__);
    } else {
        return id_;
    }
}
