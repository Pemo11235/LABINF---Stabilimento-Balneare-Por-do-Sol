/*
 * f_edit_client.h
 *  Created on: 04 set 2018
 *  Author: Matteo Luceri
 */

#ifndef F_EDIT_CLIENT_H_
#define F_EDIT_CLIENT_H_
/**
 * La funzione permette la modifica dei campi clienti , eccenzion fatta per email
 * @param cli, l'array di strutture clienti
 * @param indice, l'indice del cliente che vuole effettuare le modifiche
 * @param num_cli, il numero dei clienti
 */
void modifica_dati (cliente_t [], int , int );

/**
 * Stampo l'array di strutture cliente nel file clienti.csv
 * @param cli_a, l'array di strutture cliente
 * @param num_cli_a , il numero dei clienti
 */
void stampa_clienti ( cliente_t [], int );

#endif /* F_EDIT_CLIENT_H_ */
