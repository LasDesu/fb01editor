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

#include "automation.h"

/*****************************************************************************/
Automation::CallBackStr Automation::callbacks[AUTO_MAX_CBS];
Automation::AutomationStr Automation::automations[AUTO_NB_CCS][AUTO_NB_CBS];
uint Automation::nbCallbacks = 0;
uint Automation::nbAutomations = 0;

/*****************************************************************************/
uchar Automation::dernierCC = -1;
uchar Automation::derniereValeur = -1;

/*****************************************************************************/
void Automation::AjouterCallback(Automated * automated, const uint index, const char * nom)
{
//Manque de place
    if (nbCallbacks == AUTO_MAX_CBS)
        throw Automation_ex("Too much callbacks registrated !");
//Enregistre la callback
    int len = min(strlen(nom), AUTO_LEN_NOM);
    callbacks[nbCallbacks].automated = automated;
    callbacks[nbCallbacks].index = index;
    strncpy(callbacks[nbCallbacks].nom, nom, len);
 //Passe à la suivante
    nbCallbacks ++;
}

/*****************************************************************************/
uint Automation::NbCallbacks()
{
    return nbCallbacks;
}

char * Automation::NomCallback(const uint index)
{
    return callbacks[index].nom;
}

/*****************************************************************************/
void Automation::Ajouter(const uchar CC, const uchar inFrom, const uchar inTo,
                         const uint indexCB, const uchar outFrom, const uchar outTo)
{
//Vérifie si déjà associée
    for (uint i = 0; i < AUTO_NB_CBS; i ++)
        if (automations[CC][i].callback == &callbacks[indexCB])
            throw Automation_ex("This automation already exist !");
//Ajoute l'automation si place disponible
    for (uint i = 0; i < AUTO_NB_CBS; i ++)
        if (automations[CC][i].callback == NULL) {
        //Configure l'automation
            automations[CC][i].CC = CC;
            automations[CC][i].inFrom = inFrom;
            automations[CC][i].inTo = inTo;
            automations[CC][i].outFrom = outFrom;
            automations[CC][i].outTo = outTo;
            automations[CC][i].callback = &callbacks[indexCB];
            nbAutomations ++;
            return;
        }
//Signale le manque de place
    throw Automation_ex("Too much automations associated to the same CC !");
}

void Automation::Enlever(const uint indexAuto)
{
    AutomationStr * au = TrouverAuto(indexAuto);
    if (au == NULL) return;
    au->callback = NULL;
    nbAutomations --;
}

uint Automation::NbAutomations()
{
    return nbAutomations;
}

char * Automation::DescAutomation(const uint indexAuto)
{
    static char desc[AUTO_LEN_DESC]; desc[0] = 0;
//Retrouve l'automation
    AutomationStr * au = TrouverAuto(indexAuto);
    if (au == NULL) return desc;
//Génère un texte descriptif
    sprintf(desc, "CC#%i from %i to %i : %s from %i to %i",
            au->CC, au->inFrom, au->inTo, au->callback->nom, au->outFrom, au->outTo);
    return desc;
}

/*****************************************************************************/
void Automation::ReagirCC(const uchar CC, const uchar valeur)
{
    uint calcul;
    AutomationStr * au;
//Enregistre l'évènement
    dernierCC = CC;
    derniereValeur = valeur;
//Execute les callbacks
    for (uint i = 0; i < AUTO_NB_CBS; i ++) {
        au = &automations[CC][i];
        if (au->callback != NULL) {
            if (valeur <= au->inFrom) {
                au->callback->automated->AppelerCallback(au->callback->index, au->outFrom);
            }else if (valeur >= au->inTo) {
                au->callback->automated->AppelerCallback(au->callback->index, au->outTo);
            }else{
                calcul = (uint) valeur - au->inFrom;
                calcul = (calcul * (au->outTo - au->outFrom + 1)) / (au->inTo - au->inFrom + 1);
                calcul = calcul + au->outFrom;
                au->callback->automated->AppelerCallback(au->callback->index, (uchar) calcul);
            }
        }else return;
    }
}

/*****************************************************************************/
uchar Automation::DernierCC()
{
    return dernierCC;
}

uchar Automation::DerniereValeur()
{
    return derniereValeur;
}

/*****************************************************************************/
Automation::AutomationStr * Automation::TrouverAuto(const uint indexAuto)
{
    uint index = 0;
    for (uint i = 0; i < AUTO_NB_CCS; i ++)
    for (uint j = 0; j < AUTO_NB_CBS; j ++)
        if (automations[i][j].callback != NULL) {
            if (index == indexAuto) return &automations[i][j];
            else index ++;
        }
    return NULL;
}
