/*
 * main.h
 *  Created on: 04 set 2018
 *  Author: Matteo Luceri
 */

#ifndef MAIN_H_
#define MAIN_H_
/**
 * Var globale, indica il numero massimo di ombrelloni
 */
#define max_ombrelloni 35

/**
 * Var globale, indica il numero massimo di file
 */
#define max_file 10

/**
 * Var globale, indica l'anno corrente
 */
#define anno_corrente 2018

/* Strutture usate */

/**
 * Struttura data
 */
typedef struct
{
	int giorno;
	int mese;
	int anno;
} data_t;

/**
 *  Struttura cliente (comprende anche data_t)
*/
typedef struct
{
	char email [40];
	char password [20];
	char cod_fiscale [20];
	char nome [20];
	char cognome [20];
	data_t nascita;
	double sconto; /*sconto applicato al totale */
} cliente_t;

/**
 *  Struttura tipo ombrellone.
*/
typedef struct
{
	int ombrellone;
	int fila_o; /* fila di ombrellone */
	int doppia_prenotazione; /* la useremo per segnalare l'eventualità di doppie prenotazioni durante la giornata
	(per esempio: una la mattina, un altra il pomeriggio)*/
	int check; /* verifica la disponibilità dell'ombrellone */
} ombrellone_t;

/**
 *  Struttura prenotazione
*/
typedef struct
{
	int cod;
	char email [40];
	data_t data;
	int tipo;
	ombrellone_t num_ombrellone;
	int num_lettini;
	int num_sedie;
	double costo;
} prenotazione_t;

/**
 *  Struttura array di tipo ombrellone
 *  rappresenta una fila
*/
typedef struct
{
	ombrellone_t ombrelloni[max_ombrelloni];
} pren_ombr_disponibile_t;

#endif /* MAIN_H_ */
