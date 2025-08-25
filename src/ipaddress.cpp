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
#include "ipaddress.h"
#include <QStringList>

ipAddress::ipAddress()
{
    for ( int i = 0 ; i < 4 ; i++ ) myIp[i] = 0;
}

ipAddress::ipAddress(const quint8 *cur)
{
    for ( int i = 0; i < 4 ; i++)
        myIp[i] = cur[i];
}

ipAddress::ipAddress(const QString str)
{
    QStringList s = str.split(".");
    for (int i = 0 ; i < 4 ; i++)
        myIp[i] = s.at(i).toInt();
}

ipAddress::ipAddress(const char *str)
{
    QString t(str);
    QStringList l = t.split(".");
    for ( int i = 0 ; i < 4 ; i++ )
        myIp[i] = l.at(i).toInt();
}

ipAddress::ipAddress(const ipAddress &other)
{
    for ( int i = 0; i < 4 ; i++)
        myIp[i] = other.myIp[i];
}

ipAddress::ipAddress(const quint32 intIp)
{
    myIp[0] = intIp >> 24;
    myIp[1] = intIp >> 16;
    myIp[2] = intIp >> 8;
    myIp[3] = intIp;
}

QString ipAddress::toString() const
{
    QString temp = QString().setNum(myIp[0]);
    for ( int i = 1 ; i <= 3 ; i++ )
        temp += QChar('.') + QString().setNum(myIp[i]);
    return temp;
}

void ipAddress::setIp(const quint8 *cur)
{
    for ( int i = 0; i < 4 ; i++)
        myIp[i] = cur[i];
}

ipAddress& ipAddress::operator=(const ipAddress &other)
{
    for ( int i = 0; i < 4 ; i++)
        myIp[i] = other.myIp[i];
    return (*this);
}

void ipAddress::setIp(const QString str)
{
    QStringList s = str.split(".");
    for (int i = 0 ; i < 4 ; i++)
        myIp[i] = s.at(i).toInt();
}

ipAddress ipAddress::operator&(const ipAddress &e1) const
{
    int i;
    ipAddress e3;
    for (i=0; i < 4; i++)
        e3.myIp[i] = this->myIp[i] & e1.myIp[i];
    return e3;
}

ipAddress ipAddress::operator |(const ipAddress &e1) const
{
    int i;
    ipAddress e3;
    for (i=0; i < 4; i++)
        e3.myIp[i] = this->myIp[i] | e1.myIp[i];
    return e3;
}

bool ipAddress::isEmpty() const
{
    int d = 0;
    for ( int i = 0 ; i < 4 ; i++ ) d += myIp[i];
    return !d;
}

bool ipAddress::isFull() const
{
    for ( int i = 0 ; i < 4 ; i++ )
        if ( myIp[i] != 255 ) return false;
    return true;
}

ipAddress ipAddress::operator ~() const
{
    ipAddress ip;
    for ( int i = 0; i < 4 ; i++)
        ip.myIp[i] = ~myIp[i];
    return ip;
}

