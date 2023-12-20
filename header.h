#pragma once

struct Personne;
struct Vol;
void print_flight_info(struct Vol vol);
struct Vol parse_csv_line(char *line);
void read_csv(const char *filename, struct Vol *vols, int *num_vols);
