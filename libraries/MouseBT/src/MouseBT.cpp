/*
    MouseBT.cpp

    Copyright (c) 2015, Arduino LLC
    Original code (pre-library): Copyright (c) 2011, Peter Barrett

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "MouseBT.h"
#include <PicoBluetoothHID.h>

MouseBT_::MouseBT_(void) {
    /* noop */
}

#define REPORT_ID 0x01
const uint8_t desc_mouse[] = {TUD_HID_REPORT_DESC_MOUSE(HID_REPORT_ID(REPORT_ID))};
void MouseBT_::begin(void) {
    PicoBluetoothHID.startHID("PicoW Mouse 00:00:00:00:00:00", "PicoW HID Mouse", 0x2580, 33, desc_mouse, sizeof(desc_mouse));
}

void MouseBT_::end(void) {
    PicoBluetoothHID.end();
}

void MouseBT_::move(int x, int y, signed char wheel) {
    hid_mouse_report_t data;
    data.buttons = _buttons;
    data.x = limit_xy(x);
    data.y = limit_xy(y);
    data.wheel = wheel;
    data.pan = 0;
    PicoBluetoothHID.send(REPORT_ID, &data, sizeof(data));
}

MouseBT_ MouseBT;
