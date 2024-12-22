
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
    printf("Voici les tâches enregistrées :\n");
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

    printf("Nouvelles tâches (tapez 0 pour finir) :\n");
    while (1)
    {
        char nouvelleTache[100];
        scanf("%99s", nouvelleTache);  // Lecture de la tâche

        if (strcmp(nouvelleTache, "0") == 0) // Si l'utilisateur entre "0", on arrête la boucle
        {
            printf("Merci d'avoir renseigné vos tâches.\n");
            break;
        }

        fprintf(fichier, "%s\n", nouvelleTache); // Ajoute la tâche dans le fichier
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

    // Lire les tâches actuelles dans un tableau
    Tache taches[100];
    int i = 0;
    char ligne[100];
    
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        strcpy(taches[i].nomActivite, ligne);
        i++;
    }
    fclose(fichier);

    // Afficher les tâches
    printf("Voici les tâches enregistrées :\n");
    int j;
    for (j = 0; j < i; j++) {
        printf("%d. %s", j + 1, taches[j].nomActivite);
    }

    // Demander à l'utilisateur quelle tâche supprimer
    int choix;
    printf("\nEntrez le numéro de la tâche à supprimer : ");
    scanf("%d", &choix);

    if (choix < 1 || choix > i) {
        printf("Numéro de tâche invalide.\n");
        return;
    }

    // Ouvrir un fichier temporaire pour réécrire les tâches restantes
    FILE *fichierTemp = fopen("temp.txt", "w");
    if (fichierTemp == NULL) {
        perror("Erreur lors de la création du fichier temporaire");
        return;
    }

    for (j = 0; j < i; j++) {
        if (j != choix - 1) {  // Sauter la tâche choisie
            fprintf(fichierTemp, "%s", taches[j].nomActivite);
        }
    }

    fclose(fichierTemp);

    // Remplacer l'ancien fichier par le fichier temporaire
    remove(nomfichier);  // Supprimer l'ancien fichier
    rename("temp.txt", nomfichier);  // Renommer le fichier temporaire

    printf("La tâche %d a été supprimée avec succès.\n", choix);
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
    printf("Entrez vos tâches ici (tapez 0 pour finir) :\n");

    while (1)
    {
        scanf("%99s", MesTaches.nomActivite); // Lecture du nom de la tâche
        if (strcmp(MesTaches.nomActivite, "0") == 0) // Si l'utilisateur entre "0", on arrête
        {
            printf("Merci d'avoir renseigné vos tâches.\n");
            break;
        }

        fprintf(fichier, "%s\n", MesTaches.nomActivite); // Ajoute la tâche dans le fichier
    }

    fclose(fichier);

    int choix = 0;
    do {
        printf("\n===== Gestion de Tâches =====\n");
        printf("1. Ajouter une tâche\n");
        printf("2. Afficher les tâches\n");
        printf("3. Supprimer des tâches?\n");
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
                printf("Programme terminé. Au revoir!\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 0);

    return 0;
}










