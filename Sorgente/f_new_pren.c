/*
 * f_new_pren.c
 *  Created on: 04 set 2018
 *  Author: Matteo Luceri
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "f_new_pren.h"
#include "f_all_shared.h"

//**************************************************************************************************************//
//									FUNZIONE PRENOTA OMBRELLONE													//
//**************************************************************************************************************//
/**
 * La procedura permetterà la prenotazione di un ombrellone in una determinata data
 * @param pren , array di strutture prenotazione
 * @param num_pren, numero di prenotazioni
 * @param cli,  array di strutture cliente
 * @param index , l'indice relativo al cliente che ha eseguito l'accesso
 */
void prenota_ombrellone (prenotazione_t pren[], int num_pren, cliente_t cli[], int index ){
	data_t data_input;  		// data in input a scelta dell'utente
	ombrellone_t ombr_input;	// ombrellone scelto dall'utente
	int tipo_numero = 1,  // mi garantisce il controllo in 'controllo_data' come data "odierna"
			risultato_a = 0, // risultato dei controlli  riguardo data ed ombrellone
			risultato_b = 0,
			uscita = 0,   // uscite relative ai do_while
			uscita_a = 0,
			close = 0,
			tipo_input = 0,
			lettini_input = 0, 	// lettini voluti dall'utente per la prenotazione
			sedie_input = 0;	//  sedie volute dall'utente per la prenotazione
	double sconto_utente = 0, 	// sconto e totale relativi sempre all prenotazione
			totale = 0;
	char risposta,		// risposte alle condizioni poste dal sistema
	risposta_a;

	do {
		// chiedo l'inserimento della data in cui effettuare la prenotazione
		printf("\n\t\tPrego, inserire la data in cui si vorrebbe effetuare la prenotazione :\n");
		printf("\n\t\t\tInserire il giorno :");
		fflush(stdin);
		scanf("%d",&data_input.giorno);
		printf("\n\t\t\tInserire il mese :");
		scanf("%d",&data_input.mese);
		printf("\n\t\t\tInserire l'anno :");
		scanf("%d",&data_input.anno);

		if (controllo_data(tipo_numero,data_input) != 0){ // verifico l'idonietà della data, se ben formata o meno
			printf("\n\t\tInserire una data valida !");
		} else {
			printf("\n\t\tE' stato scelto il giorno %d / %d / %d .\n\t\t"
					"Prego, scegliere scegliere un numero di ombrellone "
					"per verificarne la disponibilita :\n",data_input.giorno, data_input.mese, data_input.anno );
			printf("\n\t\t\tInserire il numero di ombrellone :"); // chiedo fila ed ombrellone
			scanf("%d", &ombr_input.ombrellone);
			printf("\n\t\t\tInserire il numero della fila :");
			scanf("%d", &ombr_input.fila_o);

			// verifico se esiste già una data uguale tra le prenotazioni già effettuate , 0 se non esiste
			if (( risultato_a = confronta_prenotazione_data_input( pren, num_pren,data_input)) != 0) {
				// successivamente verifico analogamente l'esistenza di una prenotazione con ombrellone e fila uguali all'input
				if ((risultato_b = confronta_prenotazione_num_ombrellone_fila ( pren,ombr_input)) != 0 ){
					if (risultato_a == risultato_b) { // se sono uguali allora esiste un doppione fra le prenotazioni
						// ripetere?
						printf("\n\tSpiacente, ombrellone gia' occupato. Cambiare data o numero di ombrellone per favore.");
						printf("\n\tRiprovare ad inserire data e numero di ombrellone?\n\t Si (S)\t No (N) ");
						fflush(stdin);
						risposta = getchar();
						if (risposta == 'S' || risposta == 's') { // si
							uscita = 0; // condizione di continuazione del do-while
						}
						else if (risposta == 'N' || risposta == 'n') { // no
							uscita++; // esci dal do-while
							close++;  // garantisce l'uscita dalla procedura
						}
						else {
							printf("\n\t\tInput non valido ! Riavvio ...\n\n");
							uscita = 0;
						}
					} else {
						uscita++;
					}
				} else { // se il secondo controllo da esito negativo (cioè l'ombrellone è libero) allora
					if (risultato_b < 0) { // ritorna negativo solo se si verifica una determinata condizione
						uscita = 0;
					} else {
						uscita++;
					}
				}

			} else { // se il primo controllo da esito negativo (cioè non esiste quella data fra le prenotazioni) allora prosegui
				uscita++;
			}

		}

	}
	while (uscita == 0);

	if (uscita != 0 && close == 0) { // condizioni
		do {
			printf("\n\t\tGiorno e ombrellone disponibile !");
			// seguono 3 funzioni per l'acquisizione del tipo di prenotazione, dei lettini e delle sedie
			// il campo check del tipo ombrellone_t in questo caso sarà usato
			//	come flag per sapere che tipo di prenotazione è disponibile
			if (ombr_input.check == 1) { // mattina? allora pomeriggio
				printf("\n\t\tLa prenotazione sarà effettuata per il pomeriggio in quanto la mattina e' gia' occupata.");
				tipo_input = 2;
			} else if (ombr_input.check == 2) { // pomeriggio? allora mattina
				printf("\n\t\tLa prenotazione sarà effettuata per la mattina in quanto il pomeriggio e' gia' occupato.");
				tipo_input = 1;
			} else { // altrimenti scelta dell'utente
				tipo_input = tipo_mpg();
			}
			lettini_input = lettini();
			sedie_input = sedie();

			sconto_utente = cli[index].sconto; // salvo lo sconto personale preso dal profilo del cliente
			totale = calcola_totale(sconto_utente,ombr_input,tipo_input,lettini_input,sedie_input ); // calcolo quindi il totale


			// Confermare?
			printf("\n\tConfermi la seguente prenotazione ?\n\t\t");
			printf("Data: %d / %d / %d\n\t\tFila: %d Ombrellone: %d\n\t\t\n\t\tTipo prenotazione: ",
					data_input.giorno, data_input.mese , data_input.anno , ombr_input.fila_o , ombr_input.ombrellone);
			stampa_tipo(tipo_input); // posso così stampare il tipo di prenotazione in lettere piuttosto che numeri
			printf("\n\t\tLettini aggiuntivi : %d Sedie aggiuntive: %d\n\t\tCosto totale: %f\n\t (S) (N)\n",
					lettini_input,sedie_input,totale);
			fflush(stdin);
			risposta_a = getchar();
			if (risposta_a == 'S' || risposta_a == 's') { // si
				uscita_a++;		// stampo
				stampa_nuova_prenotazione(cli,index, data_input, ombr_input, pren,num_pren,tipo_input,lettini_input,sedie_input,totale);
				printf("\n\t\tPrenotazione effettuata con successo!");
			}
			else if (risposta_a == 'N' || risposta_a == 'n') { // no, ritorno al menù
				uscita_a++;
				printf("\n\t\tRitorno al menu'\n");
			}
			else { // riavvio
				printf("\n\t\tInput non valido ! Riavvio ...\n\n");
				uscita_a = 0;
			}
		}
		while (uscita_a == 0);
	}
}
//**************************************************************************************************************//
//									FUNZIONE CONFRONTA PRENOTAZIONE NUM OMBRELLONE FILA							//
//**************************************************************************************************************//
/**
 * La funzione prima verifica che il numero di ombrellone e fila siano validi.
 * Dopo di che verifica che non esistano prenotazioni già effettuate con la stessa fila ed ombrellone.
 * Inoltre verifico il tipo di prenotazione. Infatti se tipo = 3 (giornata intera)  la prenotazione non potrà effettuarsi
 * @param pre , array di strutture prenotazione
 * @param ombr, struttura ombrellone ,data in input dall'utente
 * @return ritorno l'indice della prenotazione trovata, altrimenti 0.
 * 			Inoltre verifico il tipo, ritornando i valori mediante la struttura ombrellone
 */
int confronta_prenotazione_num_ombrellone_fila (prenotazione_t pre[],ombrellone_t ombr) {
	int i = 0,
			j = 0,
			verifica = 0;

	// verifico che l'input sia valido e restituisco immediatamente l'errore
	if (ombr.ombrellone > max_ombrelloni || ombr.ombrellone < 0 || ombr.fila_o > max_file || ombr.fila_o < 0) {
		printf("\n\t\tAttenzione! Limite fila/ombrellone superato. Massimo file : %d\t\tMassimo ombrelloni per fila: %d", max_file,max_ombrelloni);
		verifica--;
	} else {
		for (i = 0; i < max_file ; i++) {
			if (ombr.fila_o == pre[i].num_ombrellone.fila_o) {
				for (j = 0; j < max_ombrelloni; j++) {
					if (ombr.ombrellone == pre[j].num_ombrellone.ombrellone) {
						if (pre[j].tipo == 3) {
							verifica = j;
						} else if (pre[j].tipo == 1 || pre[j].tipo == 2) {
							ombr.check = pre[j].tipo;
						}
					}
				}
			}

		}
	}

	return verifica;

}
//**************************************************************************************************************//
//									FUNZIONE STAMPA NUOVA PRENOTAZIONE											//
//**************************************************************************************************************//
/**
 * La funzione stamperà insieme alle vecchie prenotazioni anche una nuova prenotazione
 * @param cli_a , array di strurre cliente
 * @param index_a, indice del cliente che ha eseguito l'acesso
 * @param data_a , data della nuova prenotazione
 * @param ombr_a , ombrellone della nuova prenotazione
 * @param pren_a, array di strutture prenotazione (acquisito da file)
 * @param num_pren_a, numero deelle prenotazioni
 * @param tipo_a, tipo di prenotazione della nuova prenotazione
 * @param lettini_a , lettini della nuova prenotazione
 * @param sedie_a , sedie della nuova prenotazione
 * @param totale, costo totale della nuova prenotazione
 */
void stampa_nuova_prenotazione (cliente_t cli_a[], int index_a, data_t  data_a, ombrellone_t ombr_a ,
		prenotazione_t pren_a[],int num_pren_a, int tipo_a, int lettini_a, int sedie_a, double totale) {
	FILE *file;
	file = fopen("prenotazioni.csv", "a"); // apro il file delle prenotazioni
	if( file == NULL ) {
		printf("Impossibile aprire il file\n");
	} else {
		fprintf(file,"\n%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%f;", /* stampo la nuova prenotazione */
				num_pren_a+1,cli_a[index_a].email, data_a.giorno,
				data_a.mese ,data_a.anno ,tipo_a, ombr_a.ombrellone, ombr_a.fila_o,
				lettini_a,sedie_a,totale);
	}
	fclose(file);
}

//**************************************************************************************************************//
//									FUNZIONE TIPO MPG															//
//**************************************************************************************************************//
/**
 * La funzione acquisisce e restituisce il tipo di prenotazione mediante l'input dell'utente
 * @return , ritorno il tipo di prenotazione
 */
int tipo_mpg() {

	int uscita = 0,
			tipo_a = 0;
	do {
		printf("\n\t\tPrego, inserire il numero relativo al periodo della prenotazione:"
				"\n\t\t\t1) Mattina,\n\t\t\t2) Pomeriggio,\n\t\t\t3) Giornata intera.\n\t\t");
		fflush(stdin);
		scanf("%d", &tipo_a);
		if (tipo_a == 1 || tipo_a == 2 || tipo_a == 3) {
			uscita++;
		} else {
			printf("\n\t\tInput non valido. Inserire un numero compreso fra 1 e 3. Riavvio . . .");
			uscita = 0;
		}
	} while (uscita == 0);

	return tipo_a;

}
//**************************************************************************************************************//
//									FUNZIONE LETTINI															//
//**************************************************************************************************************//
/**
 * La funzione acquisisce e restituisce il numero  di lettini oggetto di una nuova prenotazione mediante l'input dell'utente
 * @return , ritorno il numero di lettini
 */
int lettini () {
	char risposta_a;
	int uscita_a = 0,
			lettini_a = 0;
	do {
		printf("\n\tVuoi aggiungere ulteriori lettini oltre ai due gia' inclusi?\n\t(S) (N)");
		fflush(stdin);
		risposta_a = getchar();
		if (risposta_a == 'S' || risposta_a == 's') {
			printf("\n\tInserire quanti lettini si desidera aggiungere:\n\t\t");
			fflush(stdin);
			scanf("%d",&lettini_a);
			uscita_a++;
		}
		else if (risposta_a == 'N' || risposta_a == 'n') {
			uscita_a ++;

		}
		else {
			printf("\n\t\tInput non valido ! Riavvio ...\n\n");
			uscita_a = 0;
		}
	}
	while ( uscita_a == 0);


	return lettini_a;
}

//**************************************************************************************************************//
//									FUNZIONE SEDIE																//
//**************************************************************************************************************//
/**
 * La funzione acquisisce e restituisce il numero  di sedie oggetto di una nuova prenotazione mediante l'input dell'utente
 * @return , ritorno il numero di sedie
 */
int sedie () {
	char risposta_b;
	int uscita_b = 0,
			sedie_a = 0;
	do {
		printf("\n\tVuoi aggiungere delle sedie alla prenotazione?\n\t(S) (N)");
		fflush(stdin);
		risposta_b = getchar();
		if (risposta_b == 'S' || risposta_b == 's') {
			printf("\n\tInserire quante sedie si desidera aggiungere:\n\t\t");
			fflush(stdin);
			scanf("%d",&sedie_a);
			uscita_b++;
		}
		else if (risposta_b == 'N' || risposta_b == 'n') {
			uscita_b ++;

		}
		else {
			printf("\n\t\tInput non valido ! Riavvio ...\n\n");
			uscita_b = 0;
		}
	}
	while ( uscita_b == 0);


	return sedie_a;
}

