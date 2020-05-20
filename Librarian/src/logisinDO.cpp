/**************************************************
* File: logisinDO.cc.
* Desc: Implementation of the Logisin DataBase objects.
* Module: AkraLog : Logisin.
* Rev: 8 decembre 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#if defined(__linux__)
#include <string.h>
#endif
#include "logisinDO.h"


/**************************************************
* Implementation: Money.
**************************************************/
void Money::zero(void)
{
    principal= decimal= 0;
}


/**************************************************
* Implementation: StringLogi.
**************************************************/
StringLogi::StringLogi(void)
{
    refCount= 0;
    length= 0;
    content= NULL;
}


StringLogi::StringLogi(char *aValue)
{
    refCount= 0;
    if (aValue != NULL) {
	// TMPTMP:
	length= strlen(aValue);
	content= new char[length+1];
	memcpy(content, aValue, length+1);
    } else {
	length= 0;
	content= NULL;
    }
}


/**************************************************
* Implementation: DataObjectLogisin.
**************************************************/

DataObjectLogisin::DataObjectLogisin(void)
{
    uniqueID= 0;
    dirty= true;
}


DataObjectLogisin::DataObjectLogisin(unsigned int aUID)
{
    uniqueID= aUID;
    dirty= false;
}


DataObjectLogisin::~DataObjectLogisin(void)
{
// TODO.
}


unsigned int DataObjectLogisin::getUniqueID(void)
{
    return uniqueID;
}



void DataObjectLogisin::cloneFromDB(void *data)
{
    // TODO: Aller chercher le 'uid'.
    uniqueID= 0;	//TMPTMPTMP.
}


void DataObjectLogisin::addTo(DBManager *aDbm)
{
// TODO.
}


void DataObjectLogisin::addTo(DBManager *aDbm, unsigned int aUID)
{
// TODO.
}


void DataObjectLogisin::updateTo(DBManager *aDbm)
{
// TODO.
}


void DataObjectLogisin::deleteFrom(DBManager *aDbm)
{
// TODO.
}


void DataObjectLogisin::cloneFromDB(WAssociationTable *assocTable, WDataEngine *anEngine, void *data)
    : cloneFromDB(assocTable, anEngine, data)
{
    anEngine->getValue(assocTable->getPropAssoc("uid"), data, &uniqueID);
}


/**************************************************
* Implementation: Dossier.
**************************************************/

DataObject *Dossier::generateur(void)
{
    return new Dossier();
}


Dossier::Dossier(void)
{
    nbrRegions= 0;
    nbrPhotos= 0;
    cimetiere= regions= NULL;
    photos= NULL;
    client= NULL;
    location= NULL;
    assureur= NULL;
    ajusteur= NULL;
    memset(identInterne, 0, 15 * sizeof(char));
    valeurOfferte.zero();
    langues[0]= 1;
    langues[1]= 1;
    profit= 0.0;
    admin= 0.0;
    tauxTVQ= 0.0;
    tauxTPS= 0.0;
    entete[0]= entete[1]= NULL;
    postScriptum[0]= postScriptum[1]= NULL;
    objetTravaux[0]= objetTravaux[1]= NULL;
    categorieSinistre= NULL;
    dateSinistre= NULL;
    deductible.zero();
}


unsigned int Dossier::getClassID(void)
{
    return 1;	// TMPTMP.
}


void Dossier::cloneFromDB(WAssociationTable *assocTable, WDataEngine *anEngine, void *data)
{
    // TODO.
}

/**************************************************
* Implementation: BaseEvaluation.
**************************************************/

BaseEvaluation::BaseEvaluation(void)
{
    memset(idAssureur, 0, 30 * sizeof(char));
    memset(idAjusteur, 0, 30 * sizeof(char));
}


unsigned int BaseEvaluation::getClassID(void)
{
    return 1;	// TMPTMP.
}


/**************************************************
* Implementation: Evaluation.
**************************************************/

Evaluation::Evaluation(void)
{
    nbrOpers= 0;
    operSuivi= NULL;
    ouverture= NULL;
    derniereModif= NULL;
    dateApprobation= NULL;
    responsable= NULL;
    approbateur= NULL;
}


unsigned int Evaluation::getClassID(void)
{
    return 1;	// TMPTMP.
}


/**************************************************
* Implementation: ClientDemog.
**************************************************/
unsigned int ClientDemog::getClassID(void)
{
    return 1;
}


/**************************************************
* Implementation: LocationDesc.
**************************************************/
unsigned int LocationDesc::getClassID(void)
{
    return 1;
}


/**************************************************
* Implementation: AssureurDemog.
**************************************************/
unsigned int AssureurDemog::getClassID(void)
{
    return 1;
}


/**************************************************
* Implementation: AjusteurDesc.
**************************************************/

unsigned int AjusteurDesc::getClassID(void)
{
    return 1;
}


/**************************************************
* Implementation: Region.
**************************************************/

unsigned int Region::getClassID(void)
{
    return 1;
}


/**************************************************
* Implementation: Photo.
**************************************************/

unsigned int Photo::getClassID(void)
{
    return 1;
}


/**************************************************
* Implementation: OperationWF.
**************************************************/

unsigned int OperationWF::getClassID(void)
{
    return 1;
}


/**************************************************
* Implementation: UtilisateurInterne.
**************************************************/

DataObject *UtilisateurInterne::generateur(void)
{
    return new UtilisateurInterne();
}


UtilisateurInterne::UtilisateurInterne(void)
{
    nomCourt= NULL;
    motDePasse= NULL;
    prenom= NULL;
    nom= NULL;
    dernierAcces= NULL;
    nbrLogins= 0;
    privileges= NULL;
    adrEmail= NULL;
    prefixInterne[0]= prefixInterne[1]= 0;
    compteurDossiers= 0;
}


unsigned int UtilisateurInterne::getClassID(void)
{
    return 1;	// TMPTMP.
}


void UtilisateurInterne::cloneFromDB(WAssociationTable *assocTable, WDataEngine *anEngine, void *data)
    : cloneFromDB(assocTable, anEngine, data)
{
    anEngine->getValue(assocTable->getPropAssoc("appName"), data, &nomCourt);
    anEngine->getValue(assocTable->getPropAssoc("passwd"), data, &motDePasse);
    anEngine->getValue(assocTable->getPropAssoc("firstName"), data, &prenom);
    anEngine->getValue(assocTable->getPropAssoc("lastName"), data, &nom);
    anEngine->getValue(assocTable->getPropAssoc("lastAccess"), data, &dernierAcces);
    anEngine->getValue(assocTable->getPropAssoc("logCount"), data, &nbrLogins);
    anEngine->getValue(assocTable->getPropAssoc("rights"), data, &privileges);
    anEngine->getValue(assocTable->getPropAssoc("email"), data, &adrEmail);
    anEngine->getValue(assocTable->getPropAssoc("fileID"), data, &prefixInterne);
    anEngine->getValue(assocTable->getPropAssoc("fileCount"), data, &compteurDossiers);
}
