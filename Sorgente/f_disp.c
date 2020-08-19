/*
 * Fun_sulla_disp.c
 *  Created on: 04 set 2018
 *  Author: Matteo Luceri
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "f_disp.h"
#include "f_all_shared.h"

//**************************************************************************************************************//
//									FUNZIONE OMBRELLONI DISPONIBILI FILA										//
//**************************************************************************************************************//
/**
 * La funzione verificherà la disponibilità  di quali ombrelloni sono liberi della fila specificata dal cliente in una certa data
 * @param prenotazioni_a , array di strutture prenotazione
 * @param num_p_a , numero di prenotazioni
 */
void ombrelloni_disponibili_fila (prenotazione_t prenotazioni_a [], int num_p_a) {

	data_t data_i;				/* Data presa in input dall'utente */
	ombrellone_t ombr_i;		/* Ombrellone preso in input dall'utente */
	pren_ombr_disponibile_t ombr_disp[max_file];/* ho dichiarato apposta una struttura contenente 10 file di 35 ombrelloni.*/
	int sel = 1,			/* variabile "interruttore" , per la funzione controllo_data*/
			uscita_a = 0,	/* varibiali di controllo-uscita dei cicli do-while */
			uscita_b = 0,
			ritorno = 0,	/* variabili di ritorno dai controlli su data e ombrellone*/
			ritorno_b = 0,
			i = 0,			/* varibili indice */
			j = 0,
			k = 0;

	do {
		printf("\n\t\tPrego, inserire la data in cui verificare la disponibilita' di ombrelloni di una certa fila :");
		/* Acquisisco la data */
		printf("\n\t\t\tGiorno : ");
		scanf("%d", &data_i.giorno);
		printf("\t\t\tMese : ");
		scanf("%d", &data_i.mese);
		printf("\t\t\tAnno : ");
		scanf("%d", &data_i.anno);
		if (controllo_data(sel,data_i) != 0){ /* verifico se è valida, ricordiamo che sel != 0 verificherà una data "odierna" */
			printf("\n\t\tInserire una data valida ! Riavvio . . .");
		} else { /*altriemnti */
			uscita_a++;
			ritorno = confronta_prenotazione_data_input (prenotazioni_a,num_p_a,data_i); /* controlla se esistono prenotazioni in quella data */

			do {
				printf("\n\t\tInserire la fila di ombrelloni di cui si vuole conoscere la disponibilita':\n"); /* acquisisco la fila di ombrelloni di cui voglio sapere la disponibilità */
				fflush(stdin);
				scanf("%d", &ombr_i.fila_o);
				if (ritorno != 0) { /* se non esiste una data fra le prenotazioni allora prosegui */
					ritorno_b = confronta_prenotazione_fila (prenotazioni_a,ombr_i,num_p_a);  /*controllo se esistono prenotazioni con la stessa fila in oggetto */

					if (ritorno_b == 999) { /* se ritorna 999 vuol dire che la fila inserita non è valida */
						uscita_b = 0;
					} else if (ritorno_b != 0) { /*Altrimenti se il controllo  sulla fila va a buon fine */
						uscita_b++;

						for (j = 0; j < max_ombrelloni; j++){ /*Credo una fila di array di strutture ombrellone "vergine" */
							ombr_disp[ombr_i.fila_o-1].ombrelloni[j].ombrellone = j+1; /*Fila -1 perchè lavoriamo con indice 0 */
							ombr_disp[ombr_i.fila_o-1].ombrelloni[j].doppia_prenotazione = 0;/* setto inoltre le mie variabili di controllo sulle doppie prenotazioni o sulle prenotazioni M+P*/
							ombr_disp[ombr_i.fila_o-1].ombrelloni[j].check = 0;
						}

						for (i = 0; i < num_p_a; i++) { /*Inizio un sistema di confronti in cui "oscuro" tutti campi della mia struttura rimarcando così le disponibilità  */
							if (prenotazioni_a[i].num_ombrellone.fila_o == ombr_i.fila_o) {/* il numero di fila della prenotazione è uguale all'input? */
								if (data_i.giorno == prenotazioni_a[i].data.giorno &&		/* se si, hanno anche la stessa data? */
										data_i.mese == prenotazioni_a[i].data.mese &&
										data_i.anno == prenotazioni_a[i].data.anno ) {
									for (k = 0; k < max_ombrelloni; k++) { /* si, allora confronto gli ombrelloni */
										if (prenotazioni_a[i].num_ombrellone.ombrellone == ombr_disp[ombr_i.fila_o-1].ombrelloni[k].ombrellone  ){ /* se sono uguali */
											ombr_disp[ombr_i.fila_o-1].ombrelloni[k].doppia_prenotazione++; /* incremento ogni volta il flag della doppia prenotazione per lo stesso giorno (max 2 per M + P) */

											/* ne verifico quindi il tipo di giornata rimarcando la disponibiltà. se per esempio  la prenotazione è di mattina marcherù come dispobile il pomeriggio */
											ombr_disp[ombr_i.fila_o-1].ombrelloni[k].check = controlla_tipo_giornata (prenotazioni_a[i].tipo, ombr_disp[ombr_i.fila_o-1].ombrelloni[k].doppia_prenotazione);

										}
									}
								}
							}
						}
					}
					else { /* se altrimenti la data inserita non è stata mai usata o non è valida */
						uscita_b++; /*esci */
						for (j = 0; j < max_ombrelloni; j++){ /*Credo una fila di array di strutture ombrellone "vergine" */
							ombr_disp[ombr_i.fila_o-1].ombrelloni[j].ombrellone = j+1; /*Fila -1 perchè lavoriamo con indice 0 */
							ombr_disp[ombr_i.fila_o-1].ombrelloni[j].doppia_prenotazione = 0;/* setto inoltre le mie variabili di controllo sulle doppie prenotazioni o sulle prenotazioni M+P*/
							ombr_disp[ombr_i.fila_o-1].ombrelloni[j].check = 0;
						}
					}
				} else {
					uscita_b++; /*esci */

					for (j = 0; j < max_ombrelloni; j++){ /*Credo una fila di array di strutture ombrellone "vergine" */
						ombr_disp[ombr_i.fila_o-1].ombrelloni[j].ombrellone = j+1; /*Fila -1 perchè lavoriamo con indice 0 */
						ombr_disp[ombr_i.fila_o-1].ombrelloni[j].doppia_prenotazione = 0;/* setto inoltre le mie variabili di controllo sulle doppie prenotazioni o sulle prenotazioni M+P*/
						ombr_disp[ombr_i.fila_o-1].ombrelloni[j].check = 0;
					}

				}
			}
			while (uscita_b == 0);
		}
	}
	while (uscita_a == 0);
	/* Infine stampo gli ombrelloni disponibili della fila e nella data scelta  */
	printf("\n\tGli ombrelloni disponibili nel giorno %d/%d/%d nella fila %d, sono:\n", data_i.giorno,data_i.mese,data_i.anno,ombr_i.fila_o);
	stampa_ombrelloni_liberi(ombr_disp[ombr_i.fila_o-1]); /* passo la struttura creata appositamente, ma della fila precedentemente richeista */
}

//**************************************************************************************************************//
//									FUNZIONE CONFRONTA PRENOTAZIONE FILA										//
//**************************************************************************************************************//
/**
 * Confronto il numero di fila dato input dall'utente con le file oggetto di una prenotazione
 * @param pre, array di strutture prenotazione
 * @param ombr , variabile di tipo ombrellone inserita dall'utente
 * @param num_p ,numero di prenotazioni
 * @return ritorno il valore di verifica, > 0 sse il confronto è positivo
 */
int confronta_prenotazione_fila (prenotazione_t pre[], ombrellone_t ombr ,int num_p) {
	int i = 0,
			verifica = 0;

	if ( ombr.fila_o > max_file || ombr.fila_o < 0) { /* prima verifico che l'input sia valido */
		printf("\n\t\tAttenzione! Limite fila superato. Massimo file : %d", max_file);
		verifica = 999;
	}
	else {
		for (i = 0; i < num_p ; i++) { /* verifico che la fila data in input non esista fra quelle oggetto di una prenotazione */
			if (pre[i].num_ombrellone.fila_o == ombr.fila_o) {
				verifica++;
			}
		}
	}

	return verifica;
}

//**************************************************************************************************************//
//									FUNZIONE OMBRELLONI DISPONIBILI FILA CRESC DECR								//
//**************************************************************************************************************//
/**
 * La funzione acquisita una data dall'utente restituisce la disponibilità ti tutti gli ombrelloni,
 * ordinando le file in ordine a scelta crescente o decrescente
 * @param prenotazioni_a, array di strutture prenotazione
 * @param num_p_a, numero di prenotazioni
 */
void ombrelloni_disponibili_fila_cresc_decr (prenotazione_t prenotazioni_a [], int num_p_a) {
	data_t data_i;		/* data in input */
	int sel = 1,		/*per il controllo della data "odierna" */
			uscita_a = 0, /* controllo-uscite dai cicli do-while */
			uscita_b = 0,
			crescornot = 0; /* crescente o decrescente */
	ombrellone_t ombr [max_ombrelloni]; /* array di strutture ombrellone */

	do {
		/* Acquisisco la data dall'utente */
		printf("\n\t\tPrego, inserire la data in cui verificare la disponibilita' di tutti gli ombrelloni :");
		fflush(stdin);
		printf("\n\t\t\tGiorno : ");
		scanf("%d", &data_i.giorno);
		printf("\t\t\tMese : ");
		scanf("%d", &data_i.mese);
		printf("\t\t\tAnno : ");
		scanf("%d", &data_i.anno);

		if (controllo_data(sel,data_i) != 0){ /* verifico se valida */
			printf("\n\t\tInserire una data valida ! Riavvio . . .");
		} else {
			uscita_a++;
			printf("\n\t\tData valida !");
			do { /* se la data è valida allora chiedo il tipo di ordinamenteo */
				printf("\n\t\tIntendi visualizzare le file di ombrelloni in ordine :\n\t\t\t1) Crescente,\n\t\t\t2) Decrescente.\n");
				scanf("%d", &crescornot);
				if (crescornot == 1 || crescornot == 2) { /* se l'input è corretto */
					uscita_b++;
					verifica_disp_tutti_ombrelloni (prenotazioni_a,data_i,num_p_a,crescornot,sel,ombr); /* verifico la disponibilità di tutti gli ombrelloni, sel sempre = 1*/
				} else {
					printf("\n\tErrore ! Inserire un numero valido fra 1 o 2. Riavvio ...");
				}
			}
			while (uscita_b == 0);
		}
	}
	while (uscita_a == 0);

}
//**************************************************************************************************************//
//									FUNZIONE MODIFICA PRENOTAZIONE TIPO OMBRELLONE								//
//**************************************************************************************************************//
/**
 * La funzione  permette di modificare il tipo di prenotazione e/o l'ombrellone, a scelta dell'utente
 *
 * @param prenotazione , array di strutture prenotazione
 * @param num_prenotazioni, numero di prenotazioni
 * @param indice , indice del cliente che ha fatto l'accesso
 * @param num_clienti , il numero di clienti
 * @param client , array di strutture cliente
 */
void modifica_prenotazione_tipo_ombrellone(prenotazione_t prenotazione[], int num_prenotazioni, int indice,int num_clienti,cliente_t client []) {
	int i = 0,	// indici di controllo-conteggio
			j = 0,
			k = 0,
			uscita_a = 0, // controlli-uscite dei cicli do-ehile
			uscita_b = 0,
			uscita_c = 0,
			x = 0; // variabile di controllo dell switch
	char risposta_a, // risposte iterative al sistema
	risposta_b;

	do {
		i++;
		printf("\n\tVuoi effetuare "); // Effettuare modifiche?
		if (i > 1) {
			printf("altre ");
		}
		printf("modifiche?\n\t(S) (N)");
		fflush(stdin);
		scanf("%c",&risposta_a);
		if (risposta_a == 'S' || risposta_a == 's') { // se si allora
			do { // scelta del tipo di modifica
				printf("\n\tPrego, digitare il numero relativo al campo che si vuole modificare :\n");
				printf("\t1) Tipo giornata prenotazione\n\t2) Numero ombrellone\n\t0) Termina e salva le modifiche.\n");
				fflush(stdin);
				scanf("%d", &x);

				switch(x){
				case 0: // se 0 esci
					uscita_a++;
					uscita_c++;
					break;
				case 1: // se 1
					for (j = 0; j < num_prenotazioni; j++ ){ // per ogni prenotazione
						if ( strncmp(prenotazione[j].email,client[indice].email ,40) == 0) { // se l'email della prenotazione è = a quella dell'utente acceduto
							do {
								printf("\n\tIntendi modificare la seguente prenotazione?"); // modifcare la prenotazione?
								stampa_a_video_prenotazione (prenotazione[j]);// stampo la prenotazione in esame
								printf("\n\t(S)(N)");
								fflush(stdin);
								scanf("%c",&risposta_b);
								if (risposta_b == 'S' || risposta_b == 's') { // si
									modifica_tipo_prenotazione (prenotazione,j,num_prenotazioni); //  modifica tipo
									uscita_b++;
									uscita_c++;
								}
								else {
									if  (risposta_b == 'N' || risposta_b == 'n') { // no, esci/ prossima prenotazione
										uscita_b++;
										uscita_c++;
									} else {
										printf("\n\t\tInput non valido ! Riavvio ...\n\n");
										uscita_b = 0;
									}
								}
							}
							while (uscita_b == 0);
						}
					}
					break;
				case 2 : // se 2
					for (j = 0; j < num_prenotazioni; j++ ){ // per ogni prenotazione
						if ( strncmp(prenotazione[j].email,client[indice].email ,40) == 0) { // se l'email della prenotazione è = a quella dell'utente acceduto
							do {
								printf("\n\tIntendi modificare la seguente prenotazione?"); // modifcare la prenotazione?
								stampa_a_video_prenotazione (prenotazione[j]); // stampo la prenotazione in esame
								printf("\n\t(S)(N)");
								fflush(stdin);
								scanf("%c",&risposta_b);
								if (risposta_b == 'S' || risposta_b == 's') { // si
									modifica_num_ombrellone_prenotazione (prenotazione,j,num_prenotazioni); // modifica numero di ombrellone
									uscita_b++;
									uscita_c++;
								}
								else {
									if  (risposta_b == 'N' || risposta_b == 'n') {// no, esci/ prossima prenotazione
										uscita_b++;
										uscita_c++;
									} else {
										printf("\n\t\tInput non valido ! Riavvio ...\n\n");
										uscita_b = 0;
									}
								}
							}
							while (uscita_b == 0);
						}
					}
					break;
				default :
					printf("\n\t\tInput non valido");
					break;
				}
			}
			while (uscita_c == 0);
		}
		else if (risposta_a == 'N' || risposta_a == 'n'){ // altrimenti esci ed aggiorna i costi e le prenotazioni
			printf("\n\t\tUscita ...\n\n");
			for (k = 0; k < num_prenotazioni; k++) {
				calcola_totale(client[indice].sconto,prenotazione[k].num_ombrellone,prenotazione[k].tipo,prenotazione[k].num_lettini,prenotazione[k].num_sedie);
			}
			stampa_prenotazione(prenotazione,num_prenotazioni);
			uscita_a++;
		} else {
			printf("\n\t\tInput non valido ...");
			uscita_a = 0;
		}
	}
	while ( uscita_a == 0);
}

//**************************************************************************************************************//
//									FUNZIONE MODIFICA  TIPO  PRENOTAZIONE										//
//**************************************************************************************************************//

/**
 * La funzione modifica il tipo di una prenotazione quando possibile
 * @param prenotazione , array di strutture prenotazione
 * @param indice , indice del cliente che ha fatto l'accesso
 * @param num_pren, numero di prenotazioni
 */
void modifica_tipo_prenotazione (prenotazione_t prenotazione[],int indice, int num_pren) {
	int crdecr = 0,
			nuovo_tipo = 0,
			uscita_a = 0,	// controlli-uscite dei cicli do-while
			uscita_b = 0,
			uscita_c = 0,
			tipo_a = 0;		// variabile di semplificazione
	data_t data_a;			// variabile di semplificazione
	ombrellone_t ombr [max_ombrelloni]; // array di strutture ombrellone

	data_a = prenotazione[indice].data;
	tipo_a = prenotazione[indice].tipo;

	verifica_disp_tutti_ombrelloni(prenotazione,data_a,num_pren, crdecr,indice,ombr); // verifico le disponibiltà
	controlla_tipo_giornata(tipo_a,prenotazione[indice].num_ombrellone.doppia_prenotazione); // "converto" le disponibilità
	if (prenotazione[indice].num_ombrellone.check == 3 ){ // se la prenotazione è di tutta la giornata
		if (prenotazione[indice].num_ombrellone.doppia_prenotazione < 2 ) { // se esiste una sola prenotazione in quel giorno
			printf("\n\t\tL'attuale tipo di prenotazione che si intende modificare: ");
			stampa_tipo(prenotazione[indice].tipo);
			do {
				printf("\n\t\tScegliere il numero relativo al nuovo tipo di prenotazione:\n"); /*posso modificare in M o P */
				printf("\t\t\t1) Mattina\t\t2)Pomeriggio\n");
				fflush(stdin);
				scanf("%d", &nuovo_tipo);

				if (nuovo_tipo == 1 || nuovo_tipo == 2) {
					prenotazione[indice].tipo = nuovo_tipo;
					printf("\n\t\tModifiche avvenute con successo !");
					uscita_a++;

				} else {
					printf("\n\t\tInput non valido. Inserire un numero valido.\n");
					uscita_a = 0;
				}
			}
			while(uscita_a == 0);
		} else { // altrimenti esistono già 2 prenotazioni
			printf("\n\t\tNel giorno %d/%d/%d e' prevista un altra prenotazione. Non e' quindi possibbile applicare modifiche.",
					prenotazione[indice].data.giorno,prenotazione[indice].data.mese,prenotazione[indice].data.anno);
			printf("\n\t\tSi ricorda l'attuale tipo di prenotazione: ");
			stampa_tipo(prenotazione[indice].tipo);
		}
	} else if (prenotazione[indice].num_ombrellone.check == 2) { // se la prenotazione è di pomeriggio
		/* posso modificarla in G o P */
		printf("\n\t\tL'attuale tipo di prenotazione che si intende modificare: ");
		stampa_tipo(prenotazione[indice].tipo);
		do {
			printf("\n\t\tScegliere il numero relativo al nuovo tipo di prenotazione:\n");
			printf("\t\t\t1) Pomeriggio\t\t2) Giornata intera\n");
			fflush(stdin);
			scanf("%d", &nuovo_tipo);

			if (nuovo_tipo == 1) {
				prenotazione[indice].tipo = 2;
				printf("\n\t\tModifiche avvenute con successo !");
				uscita_b++;
			} else if (nuovo_tipo == 2) {
				prenotazione[indice].tipo = 3;
				printf("\n\t\tModifiche avvenute con successo !");
				uscita_b++;
			} else {
				printf("\n\t\tInput non valido. Inserire un numero valido.\n");
				uscita_b = 0;
			}
		}
		while(uscita_b == 0);

	} else if (prenotazione[indice].num_ombrellone.check == 1) { // se la prenotazione è di mattina
		/* posso modificarla in G o M */
		printf("\n\t\tL'attuale tipo di prenotazione che si intende modificare: ");
		stampa_tipo(prenotazione[indice].tipo);
		do {
			printf("\n\t\tScegliere il numero relativo al nuovo tipo di prenotazione:\n");
			printf("\t\t\t1) Mattina\t\t2) Giornata intera\n");
			fflush(stdin);
			scanf("%d", &nuovo_tipo);

			if (nuovo_tipo == 1) {
				prenotazione[indice].tipo = nuovo_tipo;
				printf("\n\t\tModifiche avvenute con successo !");
				uscita_c++;
			} else  if (nuovo_tipo == 2) {
				prenotazione[indice].tipo = 3;
				printf("\n\t\tModifiche avvenute con successo !");
				uscita_c++;
			} else {
				printf("\n\t\tInput non valido. Inserire un nuomero valido.\n");
				uscita_c = 0;
			}
		}
		while(uscita_c == 0);
	}
}

//**************************************************************************************************************//
//									FUNZIONE MODIFICA NUM OMBRELLONE PRENOTAZIONE								//
//**************************************************************************************************************//

/**
 * La funzione modifica il numero di ombrellone qualora possibile
 * @param prenotazione , array di strutture prenotazione
 * @param indice , indice del cliente che ha fatto l'accesso
 * @param num_pren, numero di prenotazioni
 */
void modifica_num_ombrellone_prenotazione (prenotazione_t prenotazione[],int indice, int num_pren) {
	int crdecr = 0, 		// variabile di controllo dello switch
			j = 0,
			uscita = 0,		// controlli-uscite dei cicli do-while
			uscita_a = 0,
			uscita_b = 0,
			uscita_c = 0,
			nuovo_ombr = 0; // nuovo ombrellone
	data_t data_a;			// variabile di semplificazione
	ombrellone_t ombr_a [max_ombrelloni];// array di strutture ombrellone
	char risposta_a,		// risposte iterative al sistema
	risposta_b,
	risposta_c;

	data_a = prenotazione[indice].data;
	crdecr = 3; // = 3, potro così vedere la stampa della fila in cui cambiare ombrellone

	printf("\n\t\tDisponibilita' ombrelloni della fila %d per la prenotazione scelta: (Giorno - Prenotazione disponibile )",prenotazione[indice].num_ombrellone.fila_o);
	verifica_disp_tutti_ombrelloni(prenotazione,data_a,num_pren,crdecr,indice,ombr_a); // verifico la disponibilità



	do {
		printf("\n\t\tPrego, scegliere un numero di ombrellone valido tra quelli precedentemente mostrati:");
		fflush(stdin);
		scanf("%d", &nuovo_ombr); // acquisisco il nuovo ombrellone
		for (j = 0; j < max_ombrelloni; j++){ // per ogni ombrellone
			if (nuovo_ombr == ombr_a[j].ombrellone){ // se il nuovo ombrellone esiste
				if (ombr_a[j].check == 0){ // ed è disponibile
					/* posso calmbiarlo tranquillamente */
					prenotazione[indice].num_ombrellone.ombrellone = nuovo_ombr;
					uscita++;

				} else if (ombr_a[j].check == 1) { // altrimenti se la disponibilità = 1
					/*posso salvare solo per la mattina*/
					do {
						printf("\n\t\tOmbrellone disponibile, ma solo durante la mattina.\n\t\tIntendi proseguire con la modifica?(S)(N)");
						fflush(stdin);
						risposta_a = getchar();
						if (risposta_a == 'S' || risposta_a == 's') {
							prenotazione[indice].num_ombrellone.ombrellone = nuovo_ombr;
							uscita_a++;
							uscita++;
							printf("\n\t\tModifiche ed aggiornamento dei costi avvenuta con successo !\n");
						} else if (risposta_a == 'N' || risposta_a == 'n') {
							uscita_a++;
							uscita++;
						} else {
							printf("\n\t\tInput non valido !\n");
							uscita_a = 0;
						}
					}
					while(uscita_a == 0);
				} else if (ombr_a[j].check == 2) {  // altrimenti se la disponibilità = 2
					/* posso salvare solo per il pomeriggio*/
					do {
						printf("\n\t\tOmbrellone disponibile, ma solo durante il pomeriggio.\n\t\tIntendi proseguire con la modifica?(S)(N)");
						fflush(stdin);
						risposta_b = getchar();
						if (risposta_b == 'S' || risposta_b == 's') {
							prenotazione[indice].num_ombrellone.ombrellone = nuovo_ombr;
							uscita_b++;
							uscita++;
							printf("\n\t\tModifiche ed aggiornamento dei costi avvenuta con successo !\n");
						} else if (risposta_b == 'N' || risposta_b == 'n') {
							uscita_b++;
							uscita++;
						} else {
							printf("\n\t\tInput non valido !\n");
							uscita_b = 0;
						}
					}
					while(uscita_b== 0);
				} else if (ombr_a[j].check == 3) {  // altrimenti se la disponibilità = 3
					/* ombrellone occupato */
					do {
						printf("\n\t\tOmbrellone occupato o non disponibile.\n\t\tIntendi inserire un altro numero?(S)(N)");
						fflush(stdin);
						risposta_c = getchar();
						if (risposta_c == 'S' || risposta_c == 's') {
							uscita_c++;
							uscita = 0;

						} else if (risposta_c == 'N' || risposta_c == 'n') {
							uscita_c++;
							uscita++;
						} else {
							printf("\n\t\tInput non valido !\n");
							uscita_c = 0;
						}
					}
					while(uscita_c== 0);
				}
			}
		}
	}
	while(uscita == 0);

}
