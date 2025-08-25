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
#include <QtGui/QTabBar>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QCheckBox>
#include <QtGui/QMessageBox>
#include "adapterproperty.h"
#include "smartdevice.h"
#include "ipedit.h"

/*!
  Конструктор создает основной интерфейс диалога.
*/
adapterProperty::adapterProperty(adapterSetting *s)
{
    setWindowTitle(tr("Netcard"));
    sd = s;
    QVBoxLayout *all = new QVBoxLayout;
    tab_interfaces = new QTabBar;
    for ( int i = 0 ; i < sd->socketsCount() ; i++ ) {
        sd->setCurrent(i);
        tab_interfaces->addTab( sd->isConnectSocketIcon() , sd->name() );
    }
    all->addWidget(tab_interfaces);

    QHBoxLayout *temp = new QHBoxLayout;
    QLabel *lbl_temp = new QLabel(tr("Netcard name: "));
    le_name = new QLineEdit;
    le_name->setMaxLength(10);
    le_name->setReadOnly(true);
    temp->addWidget(lbl_temp);
    temp->addWidget(le_name);
    all->addLayout(temp);
    connect(le_name, SIGNAL(textChanged(QString)), SLOT(applyEnable()));

    temp = new QHBoxLayout;
    lbl_temp = new QLabel(tr("Mac-address: "));
    le_mac = new QLineEdit;
    le_mac->setInputMask("HH:HH:HH:HH:HH:HH;_");
    le_mac->setDragEnabled(true);
    temp->addWidget(lbl_temp);
    temp->addWidget(le_mac);
    all->addLayout(temp);
    connect(le_mac, SIGNAL(textChanged(QString)), SLOT(applyEnable()));

    le_ip = new ipEdit(this,tr("Ip-address: "));    
    all->addWidget(le_ip);
    connect(le_ip, SIGNAL(textChanged(QString)), SLOT(applyEnable()));

    le_mask = new ipEdit(this,tr("Mask: "));
    all->addWidget(le_mask);

    lb_statics = new QLabel;
    connect(le_mask, SIGNAL(textChanged(QString)), SLOT(applyEnable()));

    all->addWidget(lb_statics);

    all->addStretch(1);
    QHBoxLayout *b = new QHBoxLayout;
    b->addStretch(1);
    cb_auto = new QCheckBox(tr("Receive settings automatically"));
    connect( cb_auto , SIGNAL(clicked(bool)) , SLOT(onAutoClicked(bool)) );
    connect( cb_auto , SIGNAL(clicked()) , SLOT(applyEnable()) );
    all->addWidget( cb_auto );
    cb_auto->setEnabled( sd->hasDhcpClient() );
    if ( sd->canManageInterface() ) {
        btn_add = new QPushButton(QIcon(":/im/images/edit_add.png") , tr("Add") );
        btn_del = new QPushButton(QIcon(":/im/images/edit_remove.png") , tr("Delete") );
        connect( btn_add , SIGNAL(clicked()) , SLOT(addInterface()) );
        connect( btn_del , SIGNAL(clicked()) , SLOT(deleteInterface()) );
        b->addWidget(btn_add, 0 , Qt::AlignRight);
        b->addWidget(btn_del, 0 , Qt::AlignRight);
    }
    QPushButton *btn_reset = new QPushButton(QIcon(":/im/images/refresh.png"),tr("Reset statistics"));
    connect( btn_reset , SIGNAL(clicked()) , SLOT(reset()));
    b->addWidget(btn_reset, 0 , Qt::AlignRight);
    all->addLayout(b);
    all->addLayout(lay);
    setLayout(all);
    connect( le_ip , SIGNAL(maskChanged(quint8)) , le_mask , SLOT(setDefaultMask(quint8)));
    connect( tab_interfaces , SIGNAL(currentChanged(int)) , SLOT(changeTab(int)));
    btn_apply->setEnabled(false);
    updateTab(0);
    setAttribute(Qt::WA_DeleteOnClose);
}
//-----------------------------------------------------------
/*!
  Деструктор снимает выделение определенного интерфейса у устройства, тем самым когда мы
  выходим из дилога у нас нет выделенного кабеля.
*/
adapterProperty::~adapterProperty()
{
    sd->setCheckedSocket("");
    delete sd;
}
//--------------------------------------------------
/*!
  При смене вкладки вызывает обновление содержимого.
  @param n - Номер выбранной вкладки.
*/
void adapterProperty::changeTab(int n)
{
    updateTab(n);
}
//--------------------------------------------------------
/*!
  Обновляет содержимое диалога в зависимости от выбранного адапетра.
  @param d - указатель на сокет выбранного интерфейса.
*/
void adapterProperty::updateTab(int n)
{
    sd->setCurrent(n);
    le_name->setText( sd->name() );
    le_mac->setText( sd->mac() );
    le_ip->setText( sd->ip() );
    le_mask->setText( sd->mask() );
    lb_statics->setText( sd->statics() );
    cb_auto->setChecked(false);
    if ( sd->hasDhcpClient() ) {
        onAutoClicked( sd->isUnderDhcpControl() );
        cb_auto->setChecked( sd->isUnderDhcpControl() );
    }
    if (sd) sd->setCheckedSocket( sd->name() );
}
//-----------------------------------------------------
/*!
  Применить сделанные изменения.
  */
void adapterProperty::apply()
{
    sd->setMac( le_mac->text() );
    sd->setIp( le_ip->text() );
    sd->setMask( le_mask->text() );
    sd->connectedNet();
    sd->setCurrent( tab_interfaces->currentIndex() );
    if ( sd->hasDhcpClient() ) {
        sd->setUnderDhcpControl( cb_auto->isChecked() );
    }
    if ( sd->isConnect() ) sd->sendArpRequest(le_ip->text());
    if ( sender() == btn_ok ) accept();
}
//------------------------------------------------------------
/*!
    Слот сбрасывает всю статистику у адаптера.
*/
void adapterProperty::reset()
{
    sd->resetStatics();
    updateTab(tab_interfaces->currentIndex());
}
//------------------------------------------------------------
void adapterProperty::addInterface()
{
    sd->addInterface();
    sd->setCurrent( tab_interfaces->count() );
    tab_interfaces->addTab(  sd->isConnectSocketIcon() , sd->name() );
    tab_interfaces->setCurrentIndex( tab_interfaces->count() - 1);
    updateTab( tab_interfaces->count() - 1 );
}

void adapterProperty::deleteInterface()
{
    if ( sd->isConnect() ) {
        QMessageBox::warning(this,tr("Error") ,
                             tr("First, remove the cable!") , QMessageBox::Ok,
                             QMessageBox::Ok );
        return;
    }

    if ( tab_interfaces->count() == 1 ) {
        QMessageBox::warning(this,tr("Error") , tr("At least a netcard must exist") ,
                             QMessageBox::Ok , QMessageBox::Ok );
        return;
    }
    sd->deleteInterface( le_name->text() );
    tab_interfaces->removeTab( sd->current() );
    tab_interfaces->setCurrentIndex(0);
    updateTab(0);
}

void adapterProperty::onAutoClicked(bool isAuto)
{
    le_ip->setEnabled( !isAuto );
    le_mask->setEnabled( !isAuto );
}
