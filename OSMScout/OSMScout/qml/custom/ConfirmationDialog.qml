/*
 * Copyright 2013-2014 Canonical Ltd.
 *
 * This file is part of webbrowser-app.
 *
 * webbrowser-app is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * webbrowser-app is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.0
import Ubuntu.Components 1.1
import Ubuntu.Components.Popups 1.0 as Popups

Popups.Dialog {
    title: qsTr("JavaScript Confirmation")

    Button {
        text: qsTr("OK")
        onClicked: model.accept()
    }

    Button {
        text: qsTr("Cancel")
        onClicked: model.reject()
    }
    text: title

    // Set the parent at construction time, instead of letting show()
    // set it later on, which for some reason results in the size of
    // the dialog not being updated.
    //parent: QuickUtils.rootItem(this)

    /*Component.onCompleted: {
        show();

    }*/
}
