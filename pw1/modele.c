
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modele.h"



/// TNOVC FUNCTIONS -----------------------------------------------------------------------------------------------------------------



/// Entete : retourne la caractèristique i du fichier TOVC -----------------------------------------------------------------------------
int Entete(TOVC * fichier, int i)
{
    if (i ==1) {return(fichier->entete.adr_dernier_bloc);}
    else if (i == 2) {return(fichier->entete.pos_libre_dernier_bloc);}
    else if (i== 3)  {return(fichier->entete.nbr_caract_insert);}
    else {return(fichier->entete.nbr_caract_supp);}
}
///-------------------------------------------------------------------------------------------------------------------------------------


/// Aff-Entete : permet d'affecter val à la caractéristique i choisie ------------------------------------------------------------------
void Aff_Entete(TOVC * fichier, int i, int val)
{
    if (i == 1) {fichier->entete.adr_dernier_bloc = val;}
    else if (i == 2) {fichier->entete.pos_libre_dernier_bloc = val;}
    else if (i == 3) {fichier->entete.nbr_caract_insert = val;}
    else {fichier->entete.nbr_caract_supp = val;}
}
///-------------------------------------------------------------------------------------------------------------------------------------


/// permet d'ouvrir un fichier un renvoyant un pointeur de type TOVC -------------------------------------------------------------------

TOVC * Ouvrir(char nom_fichier[30], char mode_ouverture) {
    TOVC *fichier = malloc(sizeof(TOVC));

    // Open new file (create it if it doesn't exist)
    if ((mode_ouverture == 'n') || (mode_ouverture == 'N')) {
        // Open in "wb+" to create a new file or overwrite if it exists
        fichier->f = fopen(nom_fichier, "wb+");
        if (fichier->f != NULL) {
            printf("Ouverture du fichier reussie (creation)\n\n");

            // Initialize the header of the new file
            fichier->entete.adr_dernier_bloc = 0;
            fichier->entete.pos_libre_dernier_bloc = 0;
            fichier->entete.nbr_caract_insert = 0;
            fichier->entete.nbr_caract_supp = 0;

            // Go back to the start of the file to write the header
            rewind(fichier->f);

            // Write the header
            fwrite(&(fichier->entete), sizeof(S_Entete), 1, fichier->f);
        } else {
            printf("Erreur lors de la creation du fichier\n");
        }
    }
    // Open existing file for reading and writing without overwriting (use "rb+" mode)
    else if ((mode_ouverture == 'a') || (mode_ouverture == 'A')) {
        fichier->f = fopen(nom_fichier, "rb+");  // Open the file for read-write without truncating
        if (fichier->f != NULL) {
            printf("Ouverture du fichier reussie (existant)\n");
            rewind(fichier->f);

            // Read the header of the existing file
            fread(&(fichier->entete), sizeof(S_Entete), 1, fichier->f);
            Affichage_Entete(fichier);  // Optional: display the header information
        } else {
            printf("Erreur lors de l'ouverture du fichier, creez le fichier d'abord.\n");
        }
    }

    return fichier;
}

///-------------------------------------------------------------------------------------------------------------------------------------


/// permet de fermer un fichier de type TOVC -------------------------------------------------------------------------------------------
void Fermer(TOVC * fichier)
{
    rewind(fichier->f);
    fwrite(&(fichier->entete),sizeof(S_Entete),1,fichier->f);
    fclose(fichier->f);
    free(fichier);
}
///-------------------------------------------------------------------------------------------------------------------------------------


/// permet d'écrire le Tbloc buf au i ème bloc du fichier de type TOVC -----------------------------------------------------------------
void Ecriredir(TOVC * fichier, int i, Tbloc buf)
{
    /// on se positionne au début du i ème bloc puis on écrit dans fichier->f
        fseek(fichier->f,sizeof(S_Entete)+(sizeof(Tbloc)*(i-1)),SEEK_SET);
        fwrite(&buf,sizeof(Tbloc),1,fichier->f);
}

///-------------------------------------------------------------------------------------------------------------------------------------


/// permet de lire le i ème bloc du fichier TOVC pointé par fichier dans le Tbloc buf --------------------------------------------------
void Liredir(TOVC * fichier, int i, Tbloc * buf)
{
    /// on se positionne au début du i ème bloc puis on le lit dans buf
        fseek(fichier->f,sizeof(S_Entete)+(sizeof(Tbloc)*(i-1)),SEEK_SET);
        fread(buf,sizeof(Tbloc),1,fichier->f);
}
///-------------------------------------------------------------------------------------------------------------------------------------


/// permet d'allouer un nouveau bloc ---------------------------------------------------------------------------------------------------
void Alloc_bloc(TOVC * fichier) {Aff_Entete(fichier,1,Entete(fichier,1)+1);}


///-------------------------------------------------------------------------------------------------------------------------------------


/* permet de transformer un int num en un string s de longueur max --------------------------------------------------------------------
   la difference est comblée par des zéros */
void num_chaine(int num, int max, char * s)
{
    char s_num[4]; /// on sait que l'int num est sur 3 positions

    sprintf(s_num,"%d",num);

    int j = max - strlen(s_num) ;
    sprintf(s,"%s","");
    while (j > 0) {sprintf(s,"%s0",s);j--;}
    sprintf(s,"%s%s",s,s_num);
}
///-------------------------------------------------------------------------------------------------------------------------------------


/* permet de copier de la chaine s à partir de la position i, ---------------------------------------------------------------------------
   une sous chaine r de longueur max */
void copier_chaine(char * s, int i, int max, char * r)
{
   /// if (i < 0 ) i = 0 ;
   sprintf(r,"%s","");
   while (i<strlen(s) && max>0)
   {
       sprintf(r,"%s%c",r,s[i]);
       i ++ ;
       max -- ;
   }
}
///-------------------------------------------------------------------------------------------------------------------------------------


/* permet de supprimer une partie de la chaine s --------------------------------------------------------------------------------------
   de longueur max à partir de la position i */
void couper_chaine(char * s, int i, int max)
{
   char partie_droite[max_caractere+1];
   char partie_gauche[max_caractere+1];

   copier_chaine(s,0,i,partie_gauche);
   copier_chaine(s,i+max,strlen(s),partie_droite);

   sprintf(s,"%s%s",partie_gauche,partie_droite);
}
///------------------------------------------------------------------------------------------------------------------------------------


/* permet de transformer un semi_enregistrement en un enregistrement -----------------------------------------------------------------
   utilité : facilité de manipulation des données*/
void semi_to_enreg (Semi_enreg se, Enregistrement * en)
{
    char chaine[max_caractere+1];

    /// la clé
    sprintf(chaine,"%s","");
    copier_chaine(se,3,3,chaine);
    en->cle = atoi(chaine);

    /// le booleen
    sprintf(chaine,"%c",se[6]);
    en->supp = atoi(chaine);

    ///l'info
    copier_chaine(se,7,strlen(se)-7,en->info);
}
///-------------------------------------------------------------------------------------------------------------------------------------


///permet de transformer un enregistrement en un semi_enregistrement  ------------------------------------------------------------------
void enreg_to_semi (Enregistrement en, Semi_enreg se)
{
    char chaine[4];
    int taille = strlen(en.info);


    sprintf(se,"%s","");

    /// écriture de la taille de l'info dans le semi enregistrement
    num_chaine(taille,3,chaine);
    sprintf(se,"%s%s",se,chaine);

    /// écriture de la clé dans le semi enregistrement
    num_chaine(en.cle,3,chaine);
    sprintf(se,"%s%s",se,chaine);

    /// écriture du booléen supp
    num_chaine(en.supp,1,chaine);
    sprintf(se,"%s%s",se,chaine);

    /// écriture de l'info
    sprintf(se,"%s%s",se,en.info);
}
/// semi_enreg se = |longueur de l'info|cle|supp|l'information|
///                  ------------------ --- ---- -------------
///-------------------------------------------------------------------------------------------------------------------------------------



/// permet de récupèrer un enregistrement du fichier et de le placer dans la variable se --
void recuperer_se(TOVC * fichier, int * i, int * j, Semi_enreg se)
{
    Tbloc buf ;
    char taille[4]; /// contiendra la taille de l'info
    int k ;

    sprintf(taille,"%s","");
    sprintf(se,"%s","");
    Liredir(fichier,(*i),&buf);

    /// récuperation de la taille de l'info, int dans taille, char dans se
    for (k=0; k<3; k++)
    {
        if ((*j)< max_caractere)
        {
            sprintf(taille,"%s%c",taille,buf.tableau[*j]);
            sprintf(se,"%s%c",se,buf.tableau[*j]);
            (*j)++;
        }
        else
        {
            (*i)++;
            Liredir(fichier,(*i),&buf);
            sprintf(taille,"%s%c",taille,buf.tableau[0]);
            sprintf(se,"%s%c",se,buf.tableau[0]);
            (*j)=1;
        }
    }

    /// recuperation de la clé, le booléen et l'info dans la variable se
    for (k=0; k<(atoi(taille)+4); k++)
    {
        if ((*j)<max_caractere) {sprintf(se,"%s%c",se,buf.tableau[*j]) ; (*j)++ ;}
        else
        {
            (*i)++;
            Liredir(fichier,(*i),&buf);
            sprintf(se,"%s%c",se,buf.tableau[0]);
            (*j)=1;
        }
    }
}
///-------------------------------------------------------------------------------------------------------------------------------------


/// affichage de l'Entete du fichier ---------------------------------------------------------------------------------------------------
void Affichage_Entete(TOVC * fichier)
{
    printf("\n Les caracteristiques du fichier ----------------------------------------\n\n");
    printf(" -> Adresse dernier bloc : %d\n",Entete(fichier,1));
    printf(" -> position libre dernier bloc : %d\n",Entete(fichier,2));
    printf(" -> Nombre caracteres inseres : %d\n",Entete(fichier,3));
    printf(" -> Nombre caracteres supprimes : %d\n",Entete(fichier,4));
}
///-------------------------------------------------------------------------------------------------------------------------------------


/// affichage d'un bloc i --------------------------------------------------------------------------------------------------------------
void Affichage_bloc(TOVC * fichier)
{
    Tbloc buf ; int i;
    printf("\n\n Le contenu des blocs ------------------------------------------------------\n");
    if (Entete(fichier,1)>0)
        {
            for (i=1; i<=Entete(fichier,1);i++)
            {
                Liredir(fichier,i,&buf);
                printf(" Le contenu du bloc %d : %s\n",i,buf.tableau);
            }
        }
}
///-------------------------------------------------------------------------------------------------------------------------------------


/// permet d'afficher les enregistrements du fichier -----------------------------------------------------------------------------------
/// enregistrements supprimés logiquement : non-affichés
void Affichage_fichier(TOVC * fichier)
{
    int i = 1;
    int j = 0;
    Enregistrement en ;
    Semi_enreg se ;
    char taille[4];

    printf("\n\n Les enregistrements --------------------------------------------------\n\n");
    while (i <= Entete(fichier,1))
    {
       recuperer_se(fichier,&i,&j,se);
       ///printf("se = %s   i = %d   j = %d\n",se,i,j);
       semi_to_enreg(se,&en);
       num_chaine(en.cle,3,taille);

       printf("  %s | %d | %s\n",taille,en.supp,en.info);
       if ((i == Entete(fichier,1)) && (j == Entete(fichier,2))) break ;
    }
}
///-------------------------------------------------------------------------------------------------------------------------------------


/// permet d'afficher les enregistrements en chevauchement------------------------------------------------------------------------------
void Affichage_chevauchement(TOVC * fichier)
{
    int i = 1; int i1 = 1;  /// i1 servira de comparaison avec i
    int j = 0; int j1 = 0;

    Enregistrement en ;
    Semi_enreg se ;
    char taille[4];

    printf("\n\nLes chevauchements:\n\n");
    while (i <= Entete(fichier,1))
    {
       recuperer_se(fichier,&i1,&j1,se); /// si i1 != i => changement de bloc donc chevauchement
       if (i1 != i)
       {
           semi_to_enreg(se,&en);        /// transformation de la chaine en enregistrement
           num_chaine(en.cle,3,taille);  /// géneration de la taille de l'info

           /// affichage que si l'enregistrement n'est pas supprimé logiquement
           if (en.supp == 0) {printf("entre bloc %d et %d : %s | %d | %s  \n", i, i1, taille, en.supp, en.info);}

           if (j1 == max_caractere) {i1++; j1=0;}
              ///i et j reçoient les valeurs de i1 et j1 pour pouvoir faire la comparaison au prochain enregistrement
              i=i1;
              j=j1;
       }
       if ((i == Entete(fichier,1)) && (j == Entete(fichier,2))) break ;
    }
}
///-------------------------------------------------------------------------------------------------------------------------------------


/// recherche dans le fichier ----------------------------------------------------------------------------------------------------------
 /// on parcourt notre fichier séquentielement et on compare la clé rechercher a tte les clés
void Recherche_TOVC(TOVC * fichier, int cle, int * i, int * j, int * trouv)
{
  (*trouv)=0;
  (*i)=1;
  (*j)=0;

  int i1=1, j1=0;

  Semi_enreg SE;
  Enregistrement E;

  if (Entete(fichier,1) > 0)  /// la recherche ne se fait que si le fichier est non-vide
  {
        sprintf(SE,"%s","");
        while (!(*trouv) && (*i)<= Entete(fichier,1))
        {
          recuperer_se(fichier, &i1, &j1, SE); /// on récuper l'enreg dans SE et on se place au début du l'enreg suivant
          semi_to_enreg(SE, &E);                   /// enreg chaine -> chaine

          if (!E.supp && E.cle >= cle) break;      /// c-à-d que soit la clé n'existe pas ou qu'on l'ait trouvé
          if (!(*trouv))
            {
              (*i)= i1;
              (*j)= j1;
            }
          if (((*i)== Entete(fichier,1)) && (*j)== Entete(fichier,2)) break;  /// arrivé à la fin sans rien trouver
        }
      if ((!E.supp) && (E.cle == cle)) {(*trouv)= 1;}
   }
}
///-------------------------------------------------------------------------------------------------------------------------------------


///permet la suppression logique d'un enregistrement, le champ supp est mis à 1 --------------------------------------------------------
void Suppression_logique(TOVC * fichier, int cle)
{
    Tbloc buf ;
    int i, j, trouv, k;
    char taille[4];

    Recherche_TOVC(fichier, cle, &i, &j, &trouv);
    if (trouv)
    {
        /// récuperation de la taille de l'info pour mettre à jour l'entête
        Liredir(fichier,i,&buf);
        sprintf(taille,"%s","");
        for (k=0; k<3; k++)
        {
            if (j< max_caractere)
            {
                    sprintf(taille,"%s%c",taille,buf.tableau[j]);
                     j++;
            }
            else
            {
                i++;
                Liredir(fichier,i,&buf);
                sprintf(taille,"%s%c",taille,buf.tableau[0]);
                j = 1;
            }
        }

        /// modification du champ supp, à ce moment j est positionné au 1er caractere de la clé,
        /// j+3 = la position du caractere supp
        if (j+3 < max_caractere )
        {
            buf.tableau[j+3]= '1';
            Ecriredir(fichier,i,buf);
        }
        else
        {
           ///incrémentation du i pour lecture du bloc suivant
           Liredir(fichier, i+1, &buf);
           buf.tableau[(j+3) % max_caractere] = '1';                  ///le modulo : afin de se repositionner au début du bloc
           Ecriredir(fichier, i+1, buf);
        }
        Aff_Entete(fichier, 4, Entete(fichier,4) + atoi(taille) + 7); /// atoi(taille) + 7  = longueur chaine supprimée logiquement
    }
}
///-------------------------------------------------------------------------------------------------------------------------------------

void Suppression_physique(TOVC * fichier, int cle)
{
    int i, j, i1, j1, trouv, stop, k;
    char taille[4];
    Semi_enreg se, partie1, partie2;
    Tbloc buf;

    // Search for the record with the given key
    Recherche_TOVC(fichier, cle, &i, &j, &trouv);
    if (!trouv) {
        printf("Record with key %d not found.\n", cle);
        return;
    }

    // Initialize pointers for shifting
    i1 = i;
    j1 = j;
    stop = 0;

    // Retrieve the record to be deleted
    recuperer_se(fichier, &i1, &j1, se);
    copier_chaine(se, 0, 3, taille); // Get the size of the info field
    printf("Deleting record with key %d, size %s.\n", cle, taille);

    while (!stop) {
        recuperer_se(fichier, &i1, &j1, se); // Retrieve the next record
        copier_chaine(se, 0, max_caractere - j, partie1);
        copier_chaine(se, strlen(partie1), strlen(se), partie2);

        // Shift the first part into the current block
        Liredir(fichier, i, &buf);
        sprintf(buf.tableau + j, "%s", partie1);
        Ecriredir(fichier, i, buf);

        // Adjust indices
        j += strlen(partie1);
        if (j >= max_caractere) {
            i++;
            j -= max_caractere;
        }

        // Handle the second part if it exists
        if (strlen(partie2) > 0) {
            i = i1;
            j = strlen(partie2);
            Liredir(fichier, i, &buf);
            for (k = 0; k < j; k++) {
                buf.tableau[k] = partie2[k];
            }
            Ecriredir(fichier, i, buf);
        }

        // Check if we've reached the end
        if (i1 > Entete(fichier, 1) || (i1 == Entete(fichier, 1) && j1 >= Entete(fichier, 2))) {
            stop = 1;
        }
    }

    // Update the header
    Aff_Entete(fichier, 1, i);
    Aff_Entete(fichier, 2, j);
    Aff_Entete(fichier, 3, Entete(fichier, 3) - (atoi(taille) + 7));

    printf("Physical deletion completed.\n");
}

///-------------------------------------------------------------------------------------------------------------------------------------


void insertion_unordered(TOVC *fichier, Semi_enreg SE) {
    Tbloc buf;
    int last_block = Entete(fichier, 1); // Last block address
    int pos_libre = Entete(fichier, 2);  // Free position in the last block
    int SE_length = strlen(SE);          // Length of the record to be inserted

    printf("Before insertion: Last Block = %d, Free Position = %d\n", last_block, pos_libre);

    // If the file is empty, allocate the first block
    if (last_block == 0) {
        Alloc_bloc(fichier); // Allocate the first block
        last_block = Entete(fichier, 1); // Update last block to 1
        pos_libre = 0;
        memset(buf.tableau, 0, sizeof(buf.tableau)); // Clear the buffer
        printf("Allocated new block: Last Block = %d\n", last_block);
    } else {
        // Read the last block
        Liredir(fichier, last_block, &buf);
        printf("Read last block %d\n", last_block);
    }

    // Check if the current block has enough space for the new record
    if (pos_libre + SE_length > max_caractere) {
        // If current block doesn't have enough space, write it back and allocate a new one
        Ecriredir(fichier, last_block, buf);
        printf("Current block full, writing it back and allocating a new block.\n");

        // Allocate a new block
        Alloc_bloc(fichier);
        last_block = Entete(fichier, 1); // Update last block to the newly allocated block
        pos_libre = 0; // Reset free position for the new block

        // Initialize the new block buffer
        memset(buf.tableau, 0, sizeof(buf.tableau)); // Clear the buffer before using it
        printf("Allocated new block: Last Block = %d\n", last_block);
    }

    // Insert the record into the current block
    strncpy(buf.tableau + pos_libre, SE, SE_length); // Safely copy the record into the buffer
    pos_libre += SE_length;  // Update the free position after insertion
    printf("Inserted record, new free position = %d\n", pos_libre);

    // Print out block contents for debugging
    printf("Block contents before writing back: ");
    for (int i = 0; i < max_caractere; i++) {
        printf("%c", buf.tableau[i]);
    }
    printf("\n");

    // Write the updated block back to the file
    Ecriredir(fichier, last_block, buf);

    // Update the file headers to reflect the new block and position
    Aff_Entete(fichier, 1, last_block);  // Update last block address
    Aff_Entete(fichier, 2, pos_libre);   // Update free position
    Aff_Entete(fichier, 3, Entete(fichier, 3) + SE_length); // Update total size

    printf("After insertion: Last Block = %d, Free Position = %d, Total Size = %d\n",
           last_block, pos_libre, Entete(fichier, 3));
}


///----------------------------------------------------------------------------------------------------

/// Insertion function for unordered records ----------------------------------------------------------
void insertion_TOVC(TOVC *fichier, Enregistrement E) {
    Semi_enreg SE;

    // Convert the record to a Semi_enreg format
    enreg_to_semi(E, SE);

    // Insert the Semi_enreg into the file without maintaining order
    insertion_unordered(fichier, SE);
}
///----------------------------------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////



