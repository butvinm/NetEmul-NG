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
#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

class device;

#include "ui_connectdialog.h"

class connectDialog : public QDialog , private Ui::connectDilog
{
    Q_OBJECT
    Q_DISABLE_COPY(connectDialog)
public:           
    explicit connectDialog(device *start,device *end);
public slots:
    void changeSelect();
    QString getStart() { return startList->currentItem()->text(); }
    QString getEnd() { return endList->currentItem()->text(); }
private:
    device *start;
    device *end;
protected:
    virtual void changeEvent(QEvent *e);
};

#endif // CONNECTDIALOG_H
