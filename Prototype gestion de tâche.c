
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nomActivite[100];
    int estTerminee;
} Tache;

void afficherTaches(const char *nomfichier)
{
    FILE *fichier = fopen(nomfichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    char ligne[100];
    printf("Voici les t�ches enregistr�es :\n");
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) 
    {
        printf("%s", ligne);
    }
    
    fclose(fichier);
}

void AjouterTaches(const char *nomfichier)
{
    FILE *fichier = fopen(nomfichier, "a");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    printf("Nouvelles t�ches (tapez 0 pour finir) :\n");
    while (1)
    {
        char nouvelleTache[100];
        scanf("%99s", nouvelleTache);  // Lecture de la t�che

        if (strcmp(nouvelleTache, "0") == 0) // Si l'utilisateur entre "0", on arr�te la boucle
        {
            printf("Merci d'avoir renseign� vos t�ches.\n");
            break;
        }

        fprintf(fichier, "%s\n", nouvelleTache); // Ajoute la t�che dans le fichier
    }

    fclose(fichier);
}

void supprimertache(const char *nomfichier)
{
    FILE *fichier = fopen(nomfichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    // Lire les t�ches actuelles dans un tableau
    Tache taches[100];
    int i = 0;
    char ligne[100];
    
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        strcpy(taches[i].nomActivite, ligne);
        i++;
    }
    fclose(fichier);

    // Afficher les t�ches
    printf("Voici les t�ches enregistr�es :\n");
    int j;
    for (j = 0; j < i; j++) {
        printf("%d. %s", j + 1, taches[j].nomActivite);
    }

    // Demander � l'utilisateur quelle t�che supprimer
    int choix;
    printf("\nEntrez le num�ro de la t�che � supprimer : ");
    scanf("%d", &choix);

    if (choix < 1 || choix > i) {
        printf("Num�ro de t�che invalide.\n");
        return;
    }

    // Ouvrir un fichier temporaire pour r��crire les t�ches restantes
    FILE *fichierTemp = fopen("temp.txt", "w");
    if (fichierTemp == NULL) {
        perror("Erreur lors de la cr�ation du fichier temporaire");
        return;
    }

    for (j = 0; j < i; j++) {
        if (j != choix - 1) {  // Sauter la t�che choisie
            fprintf(fichierTemp, "%s", taches[j].nomActivite);
        }
    }

    fclose(fichierTemp);

    // Remplacer l'ancien fichier par le fichier temporaire
    remove(nomfichier);  // Supprimer l'ancien fichier
    rename("temp.txt", nomfichier);  // Renommer le fichier temporaire

    printf("La t�che %d a �t� supprim�e avec succ�s.\n", choix);
}

int main()
{
    const char nomFichier[100] = "Taches.txt";
    FILE *fichier = fopen(nomFichier, "a");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    Tache MesTaches;
    printf("Entrez vos t�ches ici (tapez 0 pour finir) :\n");

    while (1)
    {
        scanf("%99s", MesTaches.nomActivite); // Lecture du nom de la t�che
        if (strcmp(MesTaches.nomActivite, "0") == 0) // Si l'utilisateur entre "0", on arr�te
        {
            printf("Merci d'avoir renseign� vos t�ches.\n");
            break;
        }

        fprintf(fichier, "%s\n", MesTaches.nomActivite); // Ajoute la t�che dans le fichier
    }

    fclose(fichier);

    int choix = 0;
    do {
        printf("\n===== Gestion de T�ches =====\n");
        printf("1. Ajouter une t�che\n");
        printf("2. Afficher les t�ches\n");
        printf("3. Supprimer des t�ches?\n");
        printf("0. Quitter\n");

        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                AjouterTaches(nomFichier);
                break;
            case 2:
                afficherTaches(nomFichier);
                break;
            case 3:
                supprimertache(nomFichier);
                break;
            case 0:
                printf("Programme termin�. Au revoir!\n");
                break;
            default:
                printf("Choix invalide. Veuillez r�essayer.\n");
        }
    } while (choix != 0);

    return 0;
}










