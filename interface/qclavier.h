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

#ifndef QCLAVIER_H
#define QCLAVIER_H

/*****************************************************************************/
#include <QLabel>
#include <QMouseEvent>
#include <QKeyEvent>

#include "../types.h"
#include "../core/midi.h"
#include "../core/periph.h"

#include "../excep/midi_ex.h"

/*****************************************************************************/
class QClavier : public QLabel
{
    Q_OBJECT
public:
//Constantes
    #define CLAVIER_INTER_ACTU 100
    #define CLAVIER_NB_TOUCHE  24
//Disposition du clavier
    typedef enum {
        CLAVIER_AUCUNE = 0,
        CLAVIER_QWERTY,
        CLAVIER_AZERTY
    }CLAVIER_DISPO;
//Structure des touches
    typedef struct {
        char touche;
        bool etat;
    }ToucheStr;
//Constructeurs
    QClavier(QWidget * parent = 0, Qt::WindowFlags f = 0);
    ~QClavier();
//Paramêtres du clavier
    void ActiverClavier(const bool actif);
    void ChoisirClavier(const CLAVIER_DISPO dispo);
protected:
//Réimplémentation de la souris
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
//Actualisation du clavier
    void timerEvent(QTimerEvent *e);
private:
//Note en cours
    #define G_REF 36
    int noteSouris;
    bool clavierActif;
    CLAVIER_DISPO clavierDispo;
//Scan clavier
    int timer;
    ToucheStr touches[CLAVIER_NB_TOUCHE];
//Détermine la note
    int TrouverNoteSouris(const int x, const int y);
    int TrouverNoteClavier(const int index, const bool shift, const bool control);
};

#endif // QCLAVIER_H
