#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#define charlen 50

struct Personne {
    char nom[charlen];
    char prenom[charlen];
    char date_n[11];
    int num_siege;
    float prix_billet;
    struct Personne* next;
};

struct Vol {
    int num_vol;
    char comp_vol[charlen];
    char dest[charlen];
    int num_cpt;
    int hdber;
    int hfiner;
    int s_emb;
    int hdfebem;
    int hfinem;
    int h_dec;
    char etat_vol[20];
    struct Personne* passagers;
};



void print_flight_info(struct Vol vol) {
    printf("Flight %d: %s to %s\n", vol.num_vol, vol.comp_vol, vol.dest);

    struct Personne *passenger = vol.passagers;
    while (passenger != NULL) {
        printf("Passenger: %s %s, Seat: %d, Price: %.2f\n",
               passenger->prenom, passenger->nom, passenger->num_siege, passenger->prix_billet);
        passenger = passenger->next;
    }

    printf("\n");
}

struct Vol parse_csv_line(char *line) {
    struct Vol vol;
    char *token = strtok(line, ",");

    vol.num_vol = atoi(token);
    strcpy(vol.comp_vol, strtok(NULL, ","));
    strcpy(vol.dest, strtok(NULL, ","));
    vol.num_cpt = atoi(strtok(NULL, ","));
    vol.hdber = atoi(strtok(NULL, ","));
    vol.hfiner = atoi(strtok(NULL, ","));
    vol.s_emb = atoi(strtok(NULL, ","));
    vol.hdfebem = atoi(strtok(NULL, ","));
    vol.hfinem = atoi(strtok(NULL, ","));
    vol.h_dec = atoi(strtok(NULL, ","));
    strcpy(vol.etat_vol, strtok(NULL, ","));

    vol.passagers = NULL;
    char *passenger_data = strtok(NULL, "");
    char *passenger_token = strtok(passenger_data, ";");
    while (passenger_token != NULL) {
        struct Personne *passenger = (struct Personne*)malloc(sizeof(struct Personne));
        sscanf(passenger_token, "%[^,],%[^,],%[^,],%d,%f",
               passenger->nom,
               passenger->prenom,
               passenger->date_n,
               &passenger->num_siege,
               &passenger->prix_billet);
        passenger->next = vol.passagers;
        vol.passagers = passenger;
        passenger_token = strtok(NULL, ";");
    }

    return vol;
}

void read_csv(const char *filename, struct Vol *vols, int *num_vols) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[1024];
    *num_vols = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        vols[*num_vols] = parse_csv_line(line);
        (*num_vols)++;
    }

    fclose(file);
}