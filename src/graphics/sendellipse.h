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
#ifndef SENDELLIPSE_H
#define SENDELLIPSE_H

#include <QGraphicsEllipseItem>

class sendEllipse : public QGraphicsEllipseItem
{
public:
    enum { noSendItem = 0 , oneSendItem = 1 };
    sendEllipse();
    void chooseOneDevice();
    void moving(QPointF p);
    void hideItem() { setPos(-100,-100); }
    bool hasUnderDevice() { return collidingItems().count(); }
    QGraphicsItem* underDevice() { return collidingItems().first(); }
};

#endif // SENDELLIPSE_H
