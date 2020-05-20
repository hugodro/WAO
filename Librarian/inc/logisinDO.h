#ifndef _LOGISIN_DATAOBJ_H_
#define _LOGISIN_DATAOBJ_H_
/**************************************************
* File: logisinDO.h.
* Desc: Definitions of the Logisin DataBase objects.
* Module: AkraLog : Logisin.
* Rev: 8 decembre 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>
#include "dbObject.h"


class DBManager;

class DataAssociation;

class ClientDemog;
class LocationDesc;
class AssureurDemog;
class AjusteurDesc;
class Region;
class Photo;
class OperationWF;
class UtilisateurInterne;


class Money : public AkObject {
  protected:
    int principal, decimal;

  public:
    void zero(void);
};


class StringLogi : public AkObject {
  protected:
    unsigned int refCount;
    unsigned int length;
    char *content;

  public:
    StringLogi(void);
    StringLogi(char *aValue);
};


class DateLogi : public AkObject {
  protected:
    unsigned int year;
    unsigned char month, day, hour, minute, second;

  public:
};


class AdresseDesc : public AkObject {
  protected:

  public:
    StringLogi *numero;
    StringLogi *rue;
    StringLogi *sousNum;
    StringLogi *ville;
    StringLogi *province;
    char codePostal[6];
    char pays[3];
};


class DataObjectLogisin : public DataObject {

  protected:
    unsigned int uniqueID;
    bool dirty;

  public:
    DataObjectLogisin(void);
    DataObjectLogisin(unsigned int aUID);
    virtual ~DataObjectLogisin(void);
    unsigned int getUniqueID(void);
    virtual unsigned int getClassID(void)= 0;

    virtual void cloneFromDB(void *data);
    virtual void addTo(DBManager *aDbm);
    virtual void addTo(DBManager *aDbm, unsigned int aUID);
    virtual void updateTo(DBManager *aDbm);
    virtual void deleteFrom(DBManager *aDbm);
};


class Dossier : public DataObjectLogisin {
  public:		// Methodes de classe.
    static DataObject *generateur(void);

  protected:
    unsigned int nbrRegions;
    Region *regions;
    Region *cimetiere;
    unsigned int nbrPhotos;
    Photo *photos;

  public:		// Variables d'instance.
    ClientDemog *client;
    LocationDesc *location;
    AssureurDemog *assureur;
    AjusteurDesc *ajusteur;
    char identInterne[15];
    Money valeurOfferte;
    unsigned int langues[2];
    double profit;
    double admin;
    double tauxTVQ;
    double tauxTPS;
    StringLogi *entete[2];
    StringLogi *postScriptum[2];
    StringLogi *objetTravaux[2];
    StringLogi *categorieSinistre;
    DateLogi *dateSinistre;
    Money deductible;

  public:		// Methodes d'instance.
    Dossier(void);
    virtual unsigned int getClassID(void);
    virtual void cloneFromDB(DataAssociation *assocTable, WDataEngine *anEngine, void *data);
};


class BaseEvaluation : public Dossier {
  protected:

  public:		// Variables d'instance.
    char idAssureur[30];
    char idAjusteur[30];

  public:		// Methodes d'instance.
    BaseEvaluation(void);
     virtual unsigned int getClassID(void);
};


class Evaluation : public BaseEvaluation {
  protected:		// Variables d'instance.
    unsigned int nbrOpers;
    OperationWF *operSuivi;

  public:		// Variables d'instance.
    DateLogi *ouverture;
    DateLogi *derniereModif;
    DateLogi *dateApprobation;
    UtilisateurInterne *responsable;
    UtilisateurInterne *approbateur;

  public:		// Methodes d'instance.
    Evaluation(void);
     virtual unsigned int getClassID(void);
};


class ClientDemog : public DataObjectLogisin {
  protected:

  public:
    unsigned char statutSocial;
    StringLogi *prenom;
    StringLogi *nom;
    StringLogi *telephones[3];
    StringLogi *fax;
    unsigned int categorie;
    AdresseDesc adresse;
    StringLogi *adrElectro;

  public:	// Methodes d'instance.
     virtual unsigned int getClassID(void);
};


class LocationDesc : public DataObjectLogisin {
  protected:
    ClientDemog *owner;

  public:
    unsigned int categorie;
    AdresseDesc adresse;
    bool dupliqueClient;
    StringLogi *personneContact;

  public:	// Methodes d'instance.
    virtual unsigned int getClassID(void);
};


class AssureurDemog : public DataObjectLogisin {
  protected:

  public:
    StringLogi *nomination[3];
    StringLogi *telephones[3];
    StringLogi *fax[2];
    AdresseDesc adresse;
    StringLogi *numTPS;
    StringLogi *numTVQ;
    StringLogi *numIntervenant;
    StringLogi *siteWeb;
    StringLogi *adrElectro;
    double tauxProfit;
    double tauxAdmin;

  public:	// Methodes d'instance.
     virtual unsigned int getClassID(void);
};


class AjusteurDesc : public DataObjectLogisin {
  protected:
    AssureurDemog *owner;

  public:
    unsigned char statutSocial;
    StringLogi *cieNom[2];
    StringLogi *prenom;
    StringLogi *nom;
    AdresseDesc adresse;
    StringLogi *telephones[3];
    StringLogi *fax;
    StringLogi *adrElectro;

  public:	// Methodes d'instance.
     virtual unsigned int getClassID(void);
};


class DataObjChaine : public DataObjectLogisin {
  protected:
    DataObjChaine *prev;
    DataObjChaine *next;
    DataObjectLogisin *owner;

  public:

  public:	// Methodes d'instance.
};


class Region : public DataObjChaine {
  protected:
  public:

  public:	// Methodes d'instance.
     virtual unsigned int getClassID(void);
};


class Photo : public DataObjChaine {
  protected:
  public:

  public:	// Methodes d'instance.
     virtual unsigned int getClassID(void);
};


class OperationWF : public DataObjChaine {
  protected:
  public:

  public:	// Methodes d'instance.
     virtual unsigned int getClassID(void);
};


class UtilisateurInterne : public DataObjectLogisin {
  public:		// Methodes de classe.
    static DataObject *generateur(void);

  protected:

  public:		// Variables d'instance.
    StringLogi *nomCourt;
    StringLogi *motDePasse;
    StringLogi *prenom;
    StringLogi *nom;
    DateLogi *dernierAcces;
    unsigned int nbrLogins;
    StringLogi *privileges;
    StringLogi *adrEmail;
    char prefixInterne[2];
    unsigned int compteurDossiers;

  public:		// Methodes d'instance.
    UtilisateurInterne(void);
    virtual unsigned int getClassID(void);
    virtual void cloneFromDB(DataAssociation *assocTable, WDataEngine *anEngine, void *data);
};


#endif		/* _LOGISIN_DATAOBJ_H_ */
