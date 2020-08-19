/*
 * f_out_remove_pren.c
 *  Created on: 04 set 2018
 *  Author: Matteo Luceri
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "f_out_remove_pren.h"
#include "f_all_shared.h"

//**************************************************************************************************************//
//									FUNZIONE RIMUOVI PRENOTAZIONE    											//
//**************************************************************************************************************//
/**
 * La funzione rimuoverà una prenotazione a scelta fra quelle dell'utente
 * @param pren , array di strutture prenotazione
 * @param num_p, numero di prenotazioni
 * @param client , array di strutture cliente
 */
void rimuovi_prenotazione( prenotazione_t pren [], int num_p, cliente_t client) {
	int i = 0, // indice
			num_p_out, // conta le prenotazioni dell'utente
			k = 0,	// indice
			indici [num_p], // array di indici delle prenotazioni, lo useremo per garantire la relazione fra codice univoco di prenotazione e numero selezionato nella rimozione
			num_sel = 0, // numero selezionato relativo alla prenotazione da eliminare
			uscita = 0,	// controlli-uscite dei cicli do-while
			uscita_a = 0,
			uscita_b = 0;
	char risposta_a, // risposte iterative al sistema
	risposta_b;

	do {
		printf("\n\t\tSelezionare il numero relativo alla prenotazione che si intende eliminare:");
		num_p_out = 1; //numero 1, all'inizio del do-while
		for (i = 0; i < num_p; i++) { // per ogni prenotazione
			if ( strncmp(pren[i].email,client.email ,40) == 0) { // l'email è uguale a quella del cliente chiamate?
				printf("\n\t\t%d. ", num_p_out); //si, allora stampo il numero progressivo di stampa delle prenotazioni
				stampa_a_video_prenotazione (pren[i]); // stampo la prenotazione
				indici[num_p_out] = pren[i].cod; // salvo il codice della prenotazione nel mio array di indici
				num_p_out++; // incremento
			}
		}
		printf("\n");
		if (num_p_out != 1) { // se ho stampato più di una prenotazione
			fflush(stdin);
			if (scanf("%d", &num_sel) == 0 )  { // acquisico il numero della prenotazione da eliminare
				printf("\n\t\tInput non valido !\n\n");
			} else {
				if ( (num_sel <= num_p_out ) && (num_sel > 0) ){ // se il numero è valido, cioè è tra quelli stampati ed è maggiore di zero
					for (k = 1; k <= num_p_out; k++) { // per ogni numero di stampa
						if (num_sel == (k) ){ // se il numero inserito è uguale a quello di stampa
							do {
								printf("\n\t\tIntendi rimuovere la prenotazione cod. %d ?(S)(N)",indici[k]); // intedi rimuoverla?
								fflush(stdin);
								risposta_a = getchar();

								if (risposta_a == 'S' || risposta_a == 's'){ // si
									/*elimina*/
									stampa_rimuovi_prenotazione (pren,num_p,indici[k]); // rimuovo
									num_p = leggi_conta_csv_prenotazioni(pren); // aggiorno
									printf("\n\t\tPrenotazione scelta eliminata !");
									uscita_a++;
								} else if (risposta_a == 'N' || risposta_a == 'n'){ // no, esci
									uscita_a++;
								} else {
									printf("\n\t\tInput non valido ! Inserire un input valido.");
									uscita_a = 0;
								}
							}
							while (uscita_a == 0);
						}
					}
				} else {
					printf("\n\t\tInput non valido !");
				}
			}

			do {
				printf("\n\t\tVuoi effettuare altre modifiche ?(S)(N)"); // codizione di riutilizzo
				fflush(stdin);
				risposta_b = getchar();

				if (risposta_b == 'S' || risposta_b == 's'){
					uscita_b++;
					uscita = 0;
				} else if (risposta_b == 'N' || risposta_b == 'n'){
					uscita++;
					uscita_b++;
					printf("\n\t\tUscita . . .");
				} else {
					printf("\n\t\tInput non valido ! Inserire un input valido.");
					uscita_b = 0;
				}
			}
			while (uscita_b == 0);

		} else { // altirmenti  non esistono prenotazioni a nome dell'utente
			printf("\n\t\tNon esistono prenotazioni a nome dell'utente: %s %s\n\t\tUscita . . .", client.nome, client.cognome);
			uscita++;
		}
	}
	while (uscita == 0);
	stampa_prenotazione(pren,num_p); // aggiorna prenotazioni
}

//**************************************************************************************************************//
//									FUNZIONE STAMPA RIMUOVI PRENOTAZIONE    									//
//**************************************************************************************************************//
/**
 * La funzione rimuove una prenotazione  non stampadola ed aggiorna il csv delle prenotazioni
 * @param pren_a, array di strutture prenotazione
 * @param num_p , numero delle prenotazioni
 * @param num_sel , il codice  della prenotazione da eliminare (proveniente dall'array di indici
 */
void stampa_rimuovi_prenotazione (prenotazione_t pren_a [], int num_p, int num_sel) {
	FILE *file;
	int i = 0;
	file = fopen("prenotazioni.csv", "w");
	if( file == NULL ) {
		printf("Impossibile aprire il file\n");
	} else {
		for (i = 0; i < num_p; i++) { // per ogni prenotazione
			if (i != 0 && pren_a[i].cod != num_sel) {  // vai a capo se i > 0 e la prenotazione non è da rimuovere
				fprintf(file,"\n");
			}
			if (pren_a[i].cod != num_sel) { // se il codice della prenotazione è diverso da quello da rimuovere
				fprintf(file, "%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%f;", //stampa
						pren_a[i].cod,pren_a[i].email,
						pren_a[i].data.giorno,pren_a[i].data.mese,pren_a[i].data.anno,
						pren_a[i].tipo,pren_a[i].num_ombrellone.ombrellone, pren_a[i].num_ombrellone.fila_o,
						pren_a[i].num_lettini,pren_a[i].num_sedie,pren_a[i].costo );
			}
		}
	}
	fclose(file);
}
//**************************************************************************************************************//
//									FUNZIONE SALVA  PRENOTAZIONE  PER DATA										//
//**************************************************************************************************************//
/**
 * La funzione permette il salvataggio fisico, previo ordinamento, di tutte le prenotazioni divise per data
 * @param pren ,array di strutture prenotazione
 * @param num_p, numero delle prenotazioni
 */
void salva_prenotazioni_per_data (prenotazione_t pren[],int num_p) {
	FILE*file;
	int i = 0,
			j = 0,
			uscita = 0,
			data_e [num_p]; // array di strutture data per ogni prenotazione
	char titolo[15], //stringa  titolo del csv per ogni data
	risposta;

	do {
		printf("\n\t\tVuoi davvero salvare un file di output contenente tutte le prenotazioni per ogni data?\n(S)(N)");
		fflush(stdin);
		scanf("%c",&risposta);
		if (risposta == 'S' || risposta == 's') {
			uscita++;
			ordinamento_prenotazioni_data (pren,num_p); // ordino le prenotazioni per data
			for (int k = 0; k < num_p; k++) { // per ogni prenotazione
				data_e[k] = data_estesa(pren[k].data.giorno,pren[k].data.mese,pren[k].data.anno); // richiamo la funzione data estesa per convertire le date
				//in numeri estesi e quindi effettuare confronti agilmente
			}

			for (i = 0; i < num_p; i++) { // per ogni prenotazione
				if (i == 0) {	// se i = 0
					sprintf (titolo,"%d_%d_%d.csv",pren[i].data.giorno,pren[i].data.mese,pren[i].data.anno); // scrivo il titolo del csv

					if ((file = fopen (titolo,"w"))==NULL) {
						printf("\n\tImpossibile creare un nuovo csv con i dati dei file di questa prenotazione !\n");
					} else {
						fprintf(file,"\n");// stampo
						fprintf(file, "%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%f;",
								pren[i].cod,pren[i].email,
								pren[i].data.giorno,pren[i].data.mese,pren[i].data.anno,
								pren[i].tipo,pren[i].num_ombrellone.ombrellone, pren[i].num_ombrellone.fila_o,
								pren[i].num_lettini,pren[i].num_sedie,pren[i].costo );
					}
					fclose(file);
				} else { // se i > 0
					j = i - 1 ; // punto al precedente di i
					if (data_e[i] == data_e[j]){ // se le due date sono uguali
						if ((file = fopen (titolo,"a"))==NULL) { // stampo nel file csv precedente
							printf("\n\tImpossibile creare un nuovo csv con i dati dei file di questa prenotazione !\n");
						} else {
							fprintf(file,"\n");
							fprintf(file, "%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%f;",
									pren[i].cod,pren[i].email,
									pren[i].data.giorno,pren[i].data.mese,pren[i].data.anno,
									pren[i].tipo,pren[i].num_ombrellone.ombrellone, pren[i].num_ombrellone.fila_o,
									pren[i].num_lettini,pren[i].num_sedie,pren[i].costo );
						}
						fclose(file);
					} else { // altriemnti
						sprintf (titolo,"%d_%d_%d.csv",pren[i].data.giorno,pren[i].data.mese,pren[i].data.anno); // creo un nuovo file csv
						if ((file = fopen (titolo,"w"))==NULL) {
							printf("\n\tImpossibile creare un nuovo csv con i dati dei file di questa prenotazione !\n");
						} else {
							fprintf(file,"\n"); // stampo
							fprintf(file, "%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%f;",
									pren[i].cod,pren[i].email,
									pren[i].data.giorno,pren[i].data.mese,pren[i].data.anno,
									pren[i].tipo,pren[i].num_ombrellone.ombrellone, pren[i].num_ombrellone.fila_o,
									pren[i].num_lettini,pren[i].num_sedie,pren[i].costo );
						}
						fclose(file);
					}
				}
			}
			printf("\n\t\tSalvataggio avvenuto con successo !\n");
		} else if (risposta == 'N' || risposta == 'n') {
			uscita++;
		} else {
			printf("\n\t\tInput non valido ! Riavvio ...");
		}
	} while (uscita == 0);
}
//**************************************************************************************************************//
//									FUNZIONE ORDINAMENTO PRENOTAZIONI DATA										//
//**************************************************************************************************************//
/**
 * La funzione ordina le prenotazioni per data
 * @param pren , array di strutture prenotazione
 * @param num_p , numero di prenotazioni
 */
void ordinamento_prenotazioni_data (prenotazione_t pren [], int num_p) {
	int g = 0,
			i = 0,
			j = 0,
			data_ex [num_p], // array di date per ogni prenotazione
			temp_num = 0; // variabile temporale
	prenotazione_t *temp ; // struttura prenotazione di appoggio

	temp=(prenotazione_t*)malloc(sizeof(prenotazione_t)*100); // allocoa temp le stesse grandezze del tipo prenotazione_t

	for (g = 0; g < num_p; g++) { // trasformo in esteso tutte le date, tramite la funzione apposita
		data_ex[g] = data_estesa(pren[g].data.giorno,pren[g].data.mese,pren[g].data.anno);
	}
	for (i = 0; i < num_p; i++) {  // eseguo l'ordinamento , il più piccolo a "sinistra"
		for(j = num_p-2; j >= i; j--) {
			if (data_ex[j] > data_ex[j+1]) {
				*temp = pren[j];		// eseguo lo scambio sia nella struttura
				pren[j] = pren[j+1];
				pren[j+1] = *temp;

				temp_num = data_ex[j];  // che nell'array di date
				data_ex[j] = data_ex[j+1];
				data_ex[j+1] = temp_num;
			}
		}
	}
	free(temp); // discloco la memoria
}
//**************************************************************************************************************//
//									FUNZIONE DATA ESTESA														//
//**************************************************************************************************************//
/**
 * La funzione transformera la struttura data in un unico campo intero
 * @param giorno , campi della struttura data
 * @param mese ,  		"
 * @param anno , 		"
 * @return ritorno la data per esteso (formato aaaammgg)
 */
int data_estesa(int giorno, int mese, int anno){
	int data_confronto = 0;

	data_confronto = (anno*10000) + (mese*100) + (giorno);

	return (data_confronto);
}
