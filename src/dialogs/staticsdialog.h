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
#ifndef STATICSDIALOG_H
#define STATICSDIALOG_H

#include "ui_staticsdialog.h"

class myCanvas;
class statisticsScene;

class staticsDialog : public QDialog, private Ui::staticsDialog {
    Q_OBJECT
    Q_DISABLE_COPY(staticsDialog)
public:
    staticsDialog(statisticsScene *statistics, QWidget *parent = 0);
protected:
    void changeEvent(QEvent *e);
};

#endif // STATICSDIALOG_H
