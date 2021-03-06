/*
    FB01 : Sound editor
    Copyright Meslin Frédéric 2009 - 2010
    fredericmeslin@hotmail.com

    This file is part of FB01 SE

    FB01 SE is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FB01 SE is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FB01 SE.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef QARPEGIATEUR_H
#define QARPEGIATEUR_H

#include <QWidget>

#include "ui_qarpegiateur.h"

#include "../core/midi.h"
#include "../core/arpegiateur.h"

#include "../excep/midi_ex.h"

namespace Ui {
    class QArpegiateur;
}

/*****************************************************************************/
class QArpegiateur : public QWidget {
    Q_OBJECT
public:
    QArpegiateur(QWidget *parent = 0);
    ~QArpegiateur();
protected:
    void changeEvent(QEvent *e);
private:
    Ui::QArpegiateur *ui;
};

#endif // QARPEGIATEUR_H
