/**
 * @file thpdfdbg.cxx
 */
  
/* Copyright (C) 2003 Martin Budaj
 * 
 * $Date: $
 * $RCSfile: $
 * $Revision: $
 *
 * -------------------------------------------------------------------- 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * --------------------------------------------------------------------
 */
 
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <iomanip>
#include <fmt/core.h>

#include <iostream>

#include "thpdfdbg.h"
#include "thpdfdata.h"
#include "thexception.h"

using namespace std;


string tex_Xname(string s) {return("THX"+s);}
string tex_Wname(string s) {return("THW"+s);}   // special = northarrow &c.

bool tex_refs_registers = true;

string tex_set_ref(string s, string t) {
  if (tex_refs_registers)
    return("\\newcount\\" + s + "\\" + s + "=" + t);   // use registers, legacy mode
  else
    return("\\setref{" + s + "}{\\the" + t + "}");     // use macros to store references
}

string tex_get_ref(string s) {
  if (tex_refs_registers)
    return("\\" + s);
  else
    return("\\getref{" + s + "}");
}

string u2str(unsigned u) {
  unsigned i=u;
  char c;
  string s="";
  while (i>0) {
    c = 'a' + ((i-1) % 26);
    s = c + s;
    i = (i-1) / 26;
  };
  return (s);
}

string rgb2svg(double r, double g, double b) {
  return fmt::format("#{:02x}{:02x}{:02x}",int(255*r) % 256,
                                           int(255*g) % 256,
                                           int(255*b) % 256);
}

