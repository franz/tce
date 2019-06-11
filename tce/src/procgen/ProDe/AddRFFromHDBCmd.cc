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
 * @file AddRFFromHDBCmd.cc
 *
 * Definition of AddRFFromHDBCmd class.
 *
 * @author Veli-Pekka Jääskeläinen 2006 (vjaaskel-no.spam-cs.tut.fi)
 * @note rating: red
 */

#include <wx/docview.h>

#include "AddRFFromHDBCmd.hh"
#include "ProDeConstants.hh"
#include "AddRFFromHDBDialog.hh"
#include "ProDe.hh"
#include "Model.hh"
#include "MDFDocument.hh"

using std::string;


/**
 * The Constructor.
 */
AddRFFromHDBCmd::AddRFFromHDBCmd():
    EditorCommand(ProDeConstants::CMD_NAME_ADD_RF_FROM_HDB) {
}


/**
 * The Destructor.
 */
AddRFFromHDBCmd::~AddRFFromHDBCmd() {}


/**
 * Executes the command.
 *
 * @return True, if the command was succesfully executed, false otherwise.
 */
bool
AddRFFromHDBCmd::Do() {

    assert(parentWindow() != NULL);
    assert(view() != NULL);

    Model* model = dynamic_cast<MDFDocument*>(
        view()->GetDocument())->getModel();


    AddRFFromHDBDialog dialog(parentWindow(), model);

    dialog.ShowModal();
    return true;
}


/**
 * Returns id of this command.
 */
int
AddRFFromHDBCmd::id() const {
    return ProDeConstants::COMMAND_ADD_RF_FROM_HDB;
}


/**
 * Creates and returns a new instance of this command.
 */
AddRFFromHDBCmd*
AddRFFromHDBCmd::create() const {
    return new AddRFFromHDBCmd();
}



/**
 * Returns path to the command's icon file.
 */
string
AddRFFromHDBCmd::icon() const {
    return ProDeConstants::CMD_ICON_DEFAULT;
}


/**
 * Returns short version of the command name.
 */
string
AddRFFromHDBCmd::shortName() const {
    return ProDeConstants::CMD_SNAME_ADD_RF_FROM_HDB;
}


/**
 * Returns true when the command is executable, false when not.
 *
 * This command is executable when a document is open.
 *
 * @return True, if a document is open.
 */
bool
AddRFFromHDBCmd::isEnabled() {
    wxDocManager* manager = wxGetApp().docManager();
    if (manager->GetCurrentView() != NULL) {
	return true;
    }
    return false;
}
