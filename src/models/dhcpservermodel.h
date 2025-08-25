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
#ifndef DHCPSERVERMODEL_H
#define DHCPSERVERMODEL_H

#include <QAbstractTableModel>
#include "scenexmlwriter.h"
#include "scenexmlreader.h"
#include "macaddress.h"
#include "ipaddress.h"

struct staticDhcpRecord {
    macAddress chaddr;
    ipAddress yiaddr;
    ipAddress mask;
    ipAddress gateway;
    int time;
    void write(QDataStream &stream) const;
    void read(QDataStream &stream);
    void writeXml(sceneXmlWriter &stream) const;
    void readXml(sceneXmlReader &stream);
};

static const int COLUMN_COUNT = 5;

class dhcpServerModel : public QAbstractTableModel
{
public:
    dhcpServerModel(QObject *parent = 0) : QAbstractTableModel(parent) { }
    ~dhcpServerModel();
    int rowCount( const QModelIndex &r = QModelIndex() ) const;
    int columnCount( const QModelIndex &r = QModelIndex() ) const;
    QVariant headerData( int s , Qt::Orientation o, int role ) const;
    Qt::ItemFlags flags(const QModelIndex &r) const;
    QVariant data(const QModelIndex &r, int role = Qt::DisplayRole ) const;
    bool insertRow(int, const QModelIndex &parent = QModelIndex() );
    bool removeRow(int row, const QModelIndex &parent = QModelIndex() );
    bool setData(const QModelIndex &index,const QVariant &value, int role = Qt::EditRole);

    bool containRecord( staticDhcpRecord *rec) const;
    bool containRecord(ipAddress ip) const;
    staticDhcpRecord* recordWithMac(macAddress cha) const;
    void addStaticRecord(staticDhcpRecord *rec);
    void write(QDataStream &stream) const;
    void read(QDataStream &stream);
    void writeXml(sceneXmlWriter &stream) const;
    void readXml(sceneXmlReader &stream);
private:
    QList<staticDhcpRecord*> table;
};

#endif // DHCPSERVERMODEL_H
