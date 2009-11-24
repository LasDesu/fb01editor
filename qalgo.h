/*
    FB01 : Sound editor
    Copyright Meslin Frédéric 2009
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

#ifndef QALGO_H
#define QALGO_H

    #include <QtGui/QLabel>
    #include <QtGui/QMouseEvent>

    class QAlgo : public QLabel
    {
    public:
    //Constructeurs
        QAlgo(QWidget * parent = 0, Qt::WindowFlags f = 0);
        ~QAlgo();
    //Accesseurs
        void  ChangerAlgo(uchar Algo);
        uchar RecupererAlgo();
    private:
    //Algo en cours
        uchar AlgoSel;
    //Réimplémentation de la souris
        virtual void mousePressEvent(QMouseEvent * event);
    };

#endif // QALGO_H
