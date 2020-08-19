/*
 * f_edit_client.c
 *  Created on: 04 set 2018
 *  Author: Matteo Luceri
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "f_edit_client.h"
#include "f_all_shared.h"

//**************************************************************************************************************//
//									FUNZIONE MODIFICA DATI														//
//**************************************************************************************************************//

/**
 * La funzione permette la modifica dei campi clienti , eccenzion fatta per email
 * @param cli, l'array di strutture clienti
 * @param indice, l'indice del cliente che vuole effettuare le modifiche
 * @param num_cli, il numero dei clienti
 */
void modifica_dati(cliente_t cli[], int indice, int num_cli) {

	int x = 0, /* variabile usata nello switch-case per individuare il campo della prenotazione da modificare*/
			y = 0, /* variabile usata nello switch-case per individuare quale campo della data modificare*/
			uscita = 0, /* controlli per l'uscita dal do-while*/
			uscita_b = 0;

	do { /* chiedo all'utente quale campo modificare*/
		printf("\n\tPrego, digitare il numero relativo al campo che si vuole modificare :\n"
				"\t1) Password\n\t2) Codice Fiscale\n\t3) Cognome\n\t4) Nome \n\t5) Data di nascita\n\t"
				"6) Sconto applicabile\n\t0) Termina e salva le modifiche.\n");
		fflush(stdin);
		scanf("%d", &x);
		switch(x){
		case 0:
			uscita = 0;
			break;
		case 1: /* Inserisci la nuova password*/
			printf("\n\t\tInserire la nuova password: ");
			fflush(stdin);
			gets(cli[indice].password);
			uscita++;
			printf("\n\t\tModifica avvenuta con successo !");
			break;
		case 2:
			printf("\n\t\tInserire il nuovo Codice Fiscale: ");
			fflush(stdin);
			gets(cli[indice].cod_fiscale);
			uscita++;
			printf("\n\t\tModifica avvenuta con successo !");
			break;
		case 3: /* inserisci il cognome*/
			printf("\n\t\tInserire il nuovo cognome: ");
			fflush(stdin);
			gets(cli[indice].cognome);
			uscita++;
			printf("\n\t\tModifica avvenuta con successo !");
			break;
		case 4: /* inserisci il nome*/
			printf("\n\t\tInserire il nuovo nome: ");
			fflush(stdin);
			gets(cli[indice].nome);
			uscita++;
			printf("\n\t\tModifica avvenuta con successo !");
			break;
		case 5 :
			uscita++;
			do { /* Permetto l'inserimento iterativo di tutti i campi della struttura data. Al termine dell'inserimento effettuo un controllo*/
				printf("\n\t\tSpecificare quale elemento della data intendi modificare:\n\t\t"
						"1) Giorno\n\t\t2) Mese\n\t\t3) Anno\n\t\t0) Verifica correttezza data e termina.\n");
				scanf("%d", &y);
				switch(y){
				case 0:
					if (controllo_data(y,cli[indice].nascita) == 0) { 					/* La funzione verificherà se la data è bene formata*/
						printf("\n\t\tModifiche avvenute con successo!\n\n\t\t\tData "  	/*il primo parametro della funzione (y = 0)*/
								"valida. Ritorno al menu' . . . ");						/* mi permetterà di evitare un controllo spefico non necessario*/
						uscita_b = 0;													/* la questione sarà sviscerata nel corpo della funzione 'controllo_data'*/
					} else {
						printf("\n\n\t\t\tPrego, inserire una data valida ! ");
						uscita_b++;
					}
					break;
				case 1:
					printf("\n\t\t\tInserire il nuovo giorno: ");
					fflush(stdin);
					scanf("%d",&cli[indice].nascita.giorno);
					uscita_b++;
					break;
				case 2:
					printf("\n\t\t\tInserire il nuovo mese: ");
					fflush(stdin);
					scanf("%d",&cli[indice].nascita.mese);
					uscita_b++;;
					break;
				case 3:
					printf("\n\t\t\tInserire il nuovo anno: ");
					fflush(stdin);
					scanf("%d",&cli[indice].nascita.anno);
					uscita_b++;
					break;
				default :
					printf("\n\t\t\tComando errato. Riprovare . . .");
					uscita_b++;
					break;
				}
			}
			while (uscita_b != 0);
			break;
		case 6 : /* Modifico lo sconto*/
			printf("\n\t\tInserire il nuovo sconto applicabile: ");
			fflush(stdin);
			scanf("%lf",&cli[indice].sconto);
			uscita++;
			printf("\n\t\tModifica avvenuta con successo !");
			break;
		default :
			printf("\n\t\t\tComando errato. Riprovare . . .");
			uscita++;
		}
	}
	while (uscita != 0);

	stampa_clienti(cli,num_cli); /* aggiorno il csv clienti*/
}
//**************************************************************************************************************//
//									FUNZIONE STAMPA CLIENTI														//
//**************************************************************************************************************//
/**
 * Stampo l'array di strutture cliente nel file clienti.csv
 * @param cli_a, l'array di strutture cliente
 * @param num_cli_a , il numero dei clienti
 */
void stampa_clienti (cliente_t cli_a [], int num_cli_a) {
	FILE *file;
	int i = 0;

	file = fopen("clienti.csv", "w");
	if( file == NULL ) {
		printf("Impossibile aprire il file\n");
	}
	else {
		for (i = 0; i < num_cli_a; i++) {
			if (i != 0) {
				fprintf(file,"\n");
			}

			fprintf(file, "%s,%s,%s,%s,%s,%d,%d,%d,%f;",
					cli_a[i].email,cli_a[i].password,
					cli_a[i].cod_fiscale,cli_a[i].cognome,
					cli_a[i].nome,cli_a[i].nascita.giorno,
					cli_a[i].nascita.mese,cli_a[i].nascita.anno,
					cli_a[i].sconto );
		}
	}

	fclose(file);
}


