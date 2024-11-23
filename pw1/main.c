#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "modele.h"

int main()
{

  char nom_fichier[30];

  system("title manipulation fichiers de type TOVC");
  int k;
  Tbloc buf;
  TOVC *fichier;

  int i, j, cle, trouv;
  Enregistrement en;
  Semi_enreg se;

  int choix, choix1;

menuprincipal:
  system("cls");
  printf("\n\n\n ______________________________________________________________________________\n");
  printf("\n  LE MENU PRINCIPAL");
  printf("\n ______________________________________________________________________________\n\n\n");
  printf(" [1] : creation d'un fichier;\n");
  printf(" [2] : ouverture d'un fichier existant;\n");
  printf(" [0] : quitter programme;\n");
  printf("\n\n Votre choix : ");

  scanf("%d", &choix);
  switch (choix)
  {
  case 0: // fin programme ;
  {
    goto end;
  }
  case 1: // nouveau fichier
  {

    system("cls");
    printf("\n\n\n ______________________________________________________________________________\n");
    printf("\n  CREATION FICHIER :");
    printf("\n ______________________________________________________________________________\n\n\n");
    printf(" Veuillez donner le nom de votre fichier : ");
    scanf("%s", nom_fichier);
    fichier = Ouvrir(nom_fichier, 'N');

  manipulation_fichier:
    printf("\n\n [1] : Insertion;\n");
    printf(" [2] : Recherche;\n");
    printf(" [3] : Suppression logique;\n");
    printf(" [4] : Suppression physique;\n");
    printf(" [5] : Affichage;\n");
    printf(" [0] : menu principal;\n");

    printf("\n\n Votre choix : ");
    scanf("%d", &choix1);

    switch (choix1)
    {
    case 0: // retour au menu principal
    {
      Fermer(fichier);
      goto menuprincipal;
    }
    case 1: // insertion
    {
      system("cls");
      printf("\n\n\n ______________________________________________________________________________\n");
      printf("\n  INSERTION :");
      printf("\n ______________________________________________________________________________\n\n\n");

      sprintf(en.info, "%s", ""); // Clear the info buffer
      printf("\n (max pour tester : cle  3 caractere  , info  6 caractere) ");
      // Prompt for the record's key
      printf("\n\n\n Cle = ");
      scanf("%d", &(en.cle));

      // Prompt for the record's info
      printf(" Info = ");
      scanf("%s", en.info);

      // Mark the record as not deleted
      en.supp = 0;

      // Insert the record into the file
      insertion_TOVC(fichier, en);

      printf("\n Record inserted successfully!\n");

      printf("\n");
      system("pause");
      system("cls");
      goto manipulation_fichier;
    }
    case 2: // recherche
    {
      system("cls");
      printf("\n\n\n ______________________________________________________________________________\n");
      printf("\n  RECHERCHE :");
      printf("\n ______________________________________________________________________________\n\n\n");
      printf(" La cle a chercher : ");
      scanf("%d", &cle);
      Recherche_TOVC(fichier, cle, &i, &j, &trouv);
      if (!trouv)
      {
        printf("Resultat: La cle %d n'existe pas dans le fichier", cle);
      }
      else
      {
        printf(" Resultat : bloc %d, position %d\n", i, j);
      }

      printf("\n");
      system("pause");
      system("cls");
      goto manipulation_fichier;
    }
    case 3: // suppression logique
    {
      system("cls");
      printf("\n\n\n ______________________________________________________________________________\n");
      printf("\n  SUPPRESSION LOGIQUE :");
      printf("\n ______________________________________________________________________________\n\n\n");
      printf(" La cle a supprimer logiquement : ");
      scanf("%d", &cle);
      Suppression_logique(fichier, cle);

      printf("\n");
      system("pause");
      system("cls");
      goto manipulation_fichier;
    }
    case 4: // suppression physique
    {
      system("cls");
      printf("\n\n\n ______________________________________________________________________________\n");
      printf("\n  SUPPRESSION PHYSIQUE :");
      printf("\n ______________________________________________________________________________\n\n\n");
      printf(" La cle a supprimer physiquement : ");
      scanf("%d", &cle);
      Suppression_physique(fichier, cle);
      printf("\n");
      system("pause");
      system("cls");
      goto manipulation_fichier;
    }
    case 5: // Affichage
    {
      system("cls");
      printf("\n\n\n ______________________________________________________________________________\n");
      printf("\n  AFFICHAGE :");
      printf("\n ______________________________________________________________________________\n\n");
      Affichage_Entete(fichier);
      Affichage_fichier(fichier);
      Affichage_bloc(fichier);
      Affichage_chevauchement(fichier);

      printf("\n");
      system("pause");
      system("cls");
      goto manipulation_fichier;
    }
    }
  }
  case 2: // ancien fichier
  {
    system("cls");
    printf("\n\n\n ______________________________________________________________________________\n");
    printf("\n  OUVERTURE FICHIER :");
    printf("\n ______________________________________________________________________________\n\n\n");
    printf(" Veuillez donner le nom de votre fichier : ");
    scanf("%s", nom_fichier);
    fichier = Ouvrir(nom_fichier, 'A');
    goto manipulation_fichier;
  }
  }

end:
  return 0;
}
