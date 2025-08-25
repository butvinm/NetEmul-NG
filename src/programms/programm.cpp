/****************************************************************************************
** NetEmul - program for simulating computer networks.
** Copyright © 2009 Semenov Pavel and Omilaeva Anastasia
**
** NetEmul is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or (at your option) any later version.
**
** NetEmul is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public
** License along with the NetEmul; if not, write to the Free
** Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
** 02111-1307 USA.
****************************************************************************************/
#include "programm.h"
#include "ripprogramm.h"
#include "dhcpserverprogramm.h"
#include "dhcpclientprogramm.h"

static const int MAGIC_PROGRAMM_NUMBER = 50;

programm::programm(int n)
{
    createImpl(n);
}

programm::programm(QDataStream &stream)
{
    int n;
    stream >> n;
    createImpl(n);
    rep->read(stream);    
}

void programm::createImpl(int n)
{
    switch (n%MAGIC_PROGRAMM_NUMBER) {
        case RIP: rep = new ripProgramm; break;
        case DHCPClient : rep = new dhcpClientProgramm; break;
        case DHCPServer : rep = new dhcpServerProgramm; break;
        default: break;
    }
    rep->countRef = 1;
}

programm::programm(const programm &other)
{
    rep = other.rep;
    rep->countRef++;
}

programm::~programm()
{
    if ( --rep->countRef <= 0 ) delete rep;
}

programm& programm::operator=(const programm &other)
{
    other.rep->countRef++;
    if ( --rep->countRef <= 0 ) delete rep;
    rep = other.rep;
    return *this;
}

