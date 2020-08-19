/*
 *  Created on: 04 set 2018
 *  Author: Matteo Luceri
 */

/* Librerie usate */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "f_all_shared.h"
#include "f_disp.h"
#include "f_edit_client.h"
#include "f_new_pren.h"
#include "f_out_remove_pren.h"



/* Funzione Main */
int main(void)
{
	int 	num_clienti = 0,
			num_prenotazioni = 0,
			indice_cliente = 0,		/* indice del cliente che eseguirà l'accesso*/
			x = 0, 					/* usata nello switch del menu*/
			uscita = 0; 			/* variabile di controllo uscita del do-while*/
	cliente_t clienti[200]; 		/*variabili di appoggio per la lettura da file*/
	prenotazione_t prenotazioni[200];

	num_clienti = leggi_conta_csv_clienti(clienti); 					/*legge da file il numero dei clienti ed i loro dati*/
	num_prenotazioni = leggi_conta_csv_prenotazioni(prenotazioni);		/*analogamente per le prenotazioni*/

	printf("Benvenuto nel programma di gestione delle prenotazioni Lido 'Por do Sol' !\n");



	if ( ( indice_cliente = login(clienti,num_clienti) ) != -1 ) {	 /* -1 come valore in caso di errore
																		invece ci si aspetta un intero rappresentante
																		l'indice del cliente in questione */
		printf("\n\tAccesso avvenuto con successo ! \n\n\n");
		do { /*Menu' iterativo grazie cui si accede a tutte le funzioni del programma */
			printf("\n\n\n\t\t\t. . . MENU'. . .\t\t\t\n");
			printf("\tPrego, digitare il numero relativo all'istanza che si vuole eseguire :\n");
			printf("\t1) Modifica dati personali\n\t2) Prenota un ombrellone\n\t3) Mostra ombrelloni "
					"liberi in un dato giorno scelta una fila\n\t4) Mostra ombrelloni liberi in un dato "
					"giorno in ordine crescente/decrescente \n\t5) Modifica prenotazione\n\t6) Elimina prenotazione"
					"\n\t7) Salva le prenotazioni di un giorno in un file\n\t0) Termina e salva le modifiche.\n");
			scanf("%d", &x);
			fflush(stdin);

			switch (x) {
			case 1 : /* Permette di modificare tutti i campi cliente eccetto e-mail */
				modifica_dati(clienti,indice_cliente,num_clienti);
				printf("\n\t\t\tModifiche avvenute con successo !\n");
				uscita++;
				break;
			case 2 : /* Permette di effettuare una prenotazione */
				num_prenotazioni = leggi_conta_csv_prenotazioni(prenotazioni);
				prenota_ombrellone (prenotazioni,num_prenotazioni, clienti,indice_cliente);
				num_prenotazioni = leggi_conta_csv_prenotazioni(prenotazioni);
				uscita++;
				break;
			case 3 : /* Permette di verificare la disponibilità di una data fila di ombrelloni
					  Attenzione ! nelle successive funzioni verrà richiamata spesso la funzione leggi_conta_csv
					  Ciò per garantire il costante aggiornamento in real time dei file di i/o e dei dati ad essi associati */
				num_prenotazioni = leggi_conta_csv_prenotazioni(prenotazioni);
				ombrelloni_disponibili_fila(prenotazioni,num_prenotazioni);
				uscita++;
				break;
			case 4 :  /* Permette di verificare la disponibilità di tutte le file disponendo
				      le file in ordine crescente/decrescente */
				num_prenotazioni = leggi_conta_csv_prenotazioni(prenotazioni);
				ombrelloni_disponibili_fila_cresc_decr (prenotazioni, num_prenotazioni);
				uscita++;
				break;
			case 5 : /*Permette la modifica dei campi tipo e ombrellone di una prenotazione */
				num_prenotazioni = leggi_conta_csv_prenotazioni(prenotazioni);
				modifica_prenotazione_tipo_ombrellone(prenotazioni,num_prenotazioni, indice_cliente,num_clienti,clienti);
				uscita++;
				break;
			case 6 :/*Permette la rimozione di una prenotazione */
				num_prenotazioni = leggi_conta_csv_prenotazioni(prenotazioni);
				rimuovi_prenotazione(prenotazioni,num_prenotazioni,clienti[indice_cliente]);
				uscita++;
				break;
			case 7 : /*Permette la stampa su file di tutte le prenotazioni per ogni data*/
				num_prenotazioni = leggi_conta_csv_prenotazioni(prenotazioni);
				salva_prenotazioni_per_data(prenotazioni,num_prenotazioni);
				uscita++;
				break;
			case 0 : /* Salva/aggiorna i dati , termina il programma*/
				stampa_clienti(clienti,num_clienti);
				stampa_prenotazione(prenotazioni, num_prenotazioni);
				uscita = 0;
				break;
			}
		} while (uscita != 0);
	} else { /* Qualora ritornasse il famoso valore double (1.5) */
		printf("\nAccesso negato!\n");
	}


	return (0);
}
