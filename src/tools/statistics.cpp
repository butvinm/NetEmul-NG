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
#include "statistics.h"

statistics::statistics()
{
    clear();
}

void statistics::clear()
{
    myReceiveFrames = 0 ;
    myReceivePackets = 0 ;
    mySendFrames = 0;
    mySendPackets = 0;
}

statistics::statistics(const statistics &other)
{
    myReceiveFrames = other.myReceiveFrames ;
    myReceivePackets = other.myReceivePackets ;
    mySendFrames = other.mySendFrames ;
    mySendPackets = other.mySendPackets ;
}

statistics statistics::operator=(const statistics &other)
{
    myReceiveFrames = other.myReceiveFrames ;
    myReceivePackets = other.myReceivePackets ;
    mySendFrames = other.mySendFrames ;
    mySendPackets = other.mySendPackets ;
    return *this;
}

statistics statistics::operator+(const statistics &other)
{
    statistics temp;
    temp.myReceiveFrames = myReceiveFrames + other.myReceiveFrames ;
    temp.myReceivePackets = myReceivePackets + other.myReceivePackets ;
    temp.mySendFrames = mySendFrames + other.mySendFrames ;
    temp.mySendPackets = mySendPackets + other.mySendPackets ;
    return temp;
}

statistics statistics::operator+=(const statistics &other)
{
    *this = *this + other;
    return *this;
}

QString statistics::toString() const
{
    QString t;
    t += QObject::tr("Received frames: %1\n").arg( myReceiveFrames ) +
    QObject::tr("Received packets: %1\n").arg( myReceivePackets ) +
    QObject::tr("Sent frames: %1\n").arg( mySendFrames ) +
    QObject::tr("Sent packets: %1\n").arg( mySendPackets ) ;
    return t;
}

