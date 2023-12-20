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

int main() {
    const char *filename = "/home/optimo911/CLionProjects/untitled/data_vols.csv"; // Replace with your file name
    struct Vol vols[100]; // Adjust the size accordingly
    int num_vols;

    // Read CSV and populate array of struct Vol
    read_csv(filename, vols, &num_vols);

    // Print the sorted and filtered flight information
    for (int i = 0; i < num_vols; i++) {
        print_flight_info(vols[i]);
    }


    return 0;
}
