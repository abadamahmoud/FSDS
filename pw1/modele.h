#ifndef MODELE_H_INCLUDED
#define MODELE_H_INCLUDED
#define max_caractere 30 /// le nombre max de caractere que peut contenir le bloc

//=====================================TNOVC STRUCT=========================================================================

/// structure de l'entete ------------------------------------------------------------------------------------------------------
typedef struct S_Entete
{
    int adr_dernier_bloc;       /// @ du dernier bloc, pas besoin du 1er bloc puisque la structure est un tableau => contigee
    int pos_libre_dernier_bloc; /// necessaire aux decalages pour l'insertion ordonnee
    int nbr_caract_insert;      /// necessaire pour la comparaison avec nbr caracteres supprimes
    int nbr_caract_supp;        /// si > 50% => reorganisation du fichier
} S_Entete;
///-----------------------------------------------------------------------------------------------------------------------------

/// structure du bloc ----------------------------------------------------------------------------------------------------------
typedef struct Tbloc
{
    char tableau[max_caractere + 1]; /// puisque taille variable => (bloc = tableau de caractere)

} Tbloc;
///-----------------------------------------------------------------------------------------------------------------------------

/// structure du fichier de type TOVC ------------------------------------------------------------------------------------------
typedef struct TOVC
{
    FILE *f;
    S_Entete entete;
} TOVC;
///-----------------------------------------------------------------------------------------------------------------------------

//// structures du semi enregistrement ------------------------------------------------------------------------------------------
typedef char Semi_enreg[max_caractere + 1]; //// chaine de caractere qui contiendra l'information pour recup_chaine et ecrire_chaine
typedef struct Enregistrement
{
    //// longueur de l'info => 3 caracteres
    int cle;  /// 3 caracteres
    int supp; /// booleen : 1 caracteres
    char info[max_caractere - 6];
    /// la taille max de l'enregistrement est le bloc. ( 6 = taille longueur + taille cle + taille supp + 1)
} Enregistrement;
///----------------------------------------------------------------------------------------------------------------------------

/// TNOVC FUNCTIONS -----------------------------------------------------------------------------------------------------------------

// THE ABSTRUCT MACHINE

int Entete(TOVC *fichier, int i);
void Aff_Entete(TOVC *fichier, int i, int val);
TOVC *Ouvrir(char nom_fichier[30], char mode_ouverture);
void Fermer(TOVC *fichier);
void Ecriredir(TOVC *fichier, int i, Tbloc buf);
void Liredir(TOVC *fichier, int i, Tbloc *buf);
void Alloc_bloc(TOVC *fichier);

// USEFUL FUNCTION

void num_chaine(int num, int max, char *s);
void copier_chaine(char *s, int i, int max, char *r);
void couper_chaine(char *s, int i, int max);
void semi_to_enreg(Semi_enreg se, Enregistrement *en);
void enreg_to_semi(Enregistrement en, Semi_enreg se);
void recuperer_se(TOVC *fichier, int *i, int *j, Semi_enreg se);
void insertion_unordered(TOVC *fichier, Semi_enreg SE);
///----------------------------------------------------------------------------------------------------------------------------

/// l'affichage ---------------------------------------------------------------------------------------------------------------
void Affichage_fichier(TOVC *fichier);
void Affichage_Entete(TOVC *fichier);
void Affichage_bloc(TOVC *fichier);
void Affichage_chevauchement(TOVC *fichier);
///----------------------------------------------------------------------------------------------------------------------------

/// manipulation du fichier ---------------------------------------------------------------------------------------------------
void Recherche_TOVC(TOVC *fichier, int cle, int *i, int *j, int *trouv);
void Suppression_logique(TOVC *fichier, int cle);
void Suppression_physique(TOVC *fichier, int cle);
void insertion_TOVC(TOVC *fichier, Enregistrement E);

#endif /// MODELE_H_INCLUDED
