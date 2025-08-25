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
#include "programmdialog.h"
#include "smartdevice.h"
#include "programm.h"
#include "installdialog.h"
#include <QCheckBox>

programmDialog::programmDialog(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

/*!
  Обновляет список программ.
*/
void programmDialog::updateList()
{
    list->clear();
    foreach ( programm i, s->programms() ){
        QListWidgetItem *item = new QListWidgetItem(i->name());
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
        item->setData( Qt::UserRole , i->id() );
        if ( i->isEnable() ) item->setCheckState(Qt::Checked);
        else item->setCheckState(Qt::Unchecked);
        list->addItem(item);
    }
}
//-------------------------------------------------
void programmDialog::programmChanged()
{
    btn_remove->setEnabled( list->currentItem() );
    btn_settings->setEnabled( list->currentItem() );
}

void programmDialog::stateChanged(QListWidgetItem *item)
{
    if ( !item ) return;
    s->programmAt( item->data( Qt::UserRole).toInt() )->setEnable( item->checkState() == Qt::Checked );
}

void programmDialog::setDevice( smartDevice *d )
{
    s = d;
    updateList();
}
/*!
  Слот, вызываемый при нажатии на кнопку Ok,
  выполняет все принятые изменения, закрывает диалог.
*/
void programmDialog::apply()
{
    for ( int i = 0; i < list->count(); i++) {
        QListWidgetItem *n = list->item(i);
        if (n->checkState() == Qt::Checked ) s->programmAt( n->data(Qt::UserRole).toInt() )->setEnable(true);
        else s->programmAt( n->data(Qt::UserRole).toInt() )->setEnable(false);
    }
    accept();
}
//----------------------------------------------------
/*!
  Слот вызывает диалог установки программ,
  обновляет список установленных программ.
*/
void programmDialog::add()
{
    installDialog *d = new installDialog;
    d->setDevice( s );
    d->exec();
    btn_ok->setFocus();
    updateList();
}
//-----------------------------------------------------
/*!
  Слот удаляет выделенную программу.
*/
void programmDialog::remove()
{
    QListWidgetItem *w = list->currentItem();
    s->removeProgramm( s->programmAt(w->data(Qt::UserRole).toInt() ) );
    updateList();
}

void programmDialog::settings()
{
    s->programmAt( list->currentItem()->data(Qt::UserRole).toInt() )->showProperty();
}

//-----------------------------------------------------
void programmDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}
