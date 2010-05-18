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

#ifndef QENVELOPPE_H
#define QENVELOPPE_H

#include <QtGui/QLabel>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>

/*****************************************************************************/
class QEnveloppe : public QLabel
{
public:
    QEnveloppe(QWidget * parent = 0, Qt::WindowFlags f = 0);
    ~QEnveloppe();
//Fonctions publiques
    void DefinirEnveloppe(int AR, int DR1, int SL, int DR2, int RR);
private:
    QPoint Points[5];
    virtual void paintEvent (QPaintEvent * event);
};

#endif // QENVELOPPE_H