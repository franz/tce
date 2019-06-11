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
 * @file DOMBuilderErrorHandler.cc
 *
 * Implementation of DOMBuilderErrorHandler class.
 *
 * @author Lasse Laasonen 2004 (lasse.laasonen-no.spam-tut.fi)
 */

#include <xercesc/dom/DOMLocator.hpp>

#include "DOMBuilderErrorHandler.hh"
#include "Conversion.hh"

using std::string;

/**
 * Constructor.
 */
DOMBuilderErrorHandler::DOMBuilderErrorHandler() :
    errorCount_(0), errorLog_("") {
}


/**
 * Destructor.
 */
DOMBuilderErrorHandler::~DOMBuilderErrorHandler() {
}


/**
 * Handler function to process errors that occur while building DOM
 * documents.
 *
 * Stores information to locate the error (URI, line number, column,
 * diagnostic message) passed by a DOM builder to an error log.  Called by
 * DOMBuilder::parseURI.
 *
 * @param domError Error generated by DOM builder.
 * @return Always Boolean value 'true'.
 */
bool
DOMBuilderErrorHandler::handleError(const DOMError& domError) {

    errorCount_++;
    DOMLocator* locator = domError.getLocation();

    errorLog_ += "Error at file ";
    errorLog_ += Conversion::XMLChToString(locator->getURI());
    errorLog_ += ", line ";
    errorLog_ += Conversion::toString(locator->getLineNumber());
    errorLog_ += ", column ";
    errorLog_ += Conversion::toString(locator->getColumnNumber());
    errorLog_ += "\n    Message: ";
    errorLog_ += Conversion::XMLChToString(domError.getMessage());
    errorLog_ += "\n";

    return true;
}


/**
 * Returns the number of errors handled.
 *
 * @return Number of errors handled.
 */
int
DOMBuilderErrorHandler::errorCount() const {
    return errorCount_;
}


/**
 * Returns the error log.
 *
 * @return The error log.
 */
string
DOMBuilderErrorHandler::errorLog() const {
    return errorLog_;
}
