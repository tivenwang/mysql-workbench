/* 
 * Copyright (c) 2007, 2014, Oracle and/or its affiliates. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of the
 * License.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301  USA
 */

#ifndef _STDAFX_H_
#define _STDAFX_H_

// This is the only stdafx header that is still shared on all platforms.
// It will go when the old parser is removed.

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <winsock2.h>

#define byte unsigned char

#include <direct.h>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <map>
#include <locale>

#include <glib.h>

#endif