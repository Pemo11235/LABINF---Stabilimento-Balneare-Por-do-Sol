/*
 * Fun_Fondamentali&Condivise.c
 *  Created on: 04 set 2018
 *  Author: Matteo Luceri
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "f_all_shared.h"

//**************************************************************************************************************//
//									FUNZIONE LOGIN																//
//**************************************************************************************************************//
/**
 * La funzione permetterà mediante confronto di verificare l'accesso degli utenti registrati
 * @param cli   l'array della struttura clienti
 * @param num_cli  il numero dei clienti
 * @return ritornerà il l'indice del cliente o   -1
 * indicante un valore negativo che idicherà l'errore al sistema
 */
double login ( cliente_t cli [], int num_cli)
{
	/*uscita dei cicli di controllo per: */
	int controllo_e = 0,  /* 1) email*/
			controllo_p = 0, /*2) password*/
			uscita = 0, /* do-while*/
			uscita_anticipata = 0, /* do-while*/
			indice_c = 0;
	char email_input [40],
	password_input [10],
	risposta;

	printf("\n\n\n\t\tLOGIN\t\t\n\tPrego inserire credenziali di accesso :\n");

	do {
		/* se incremento controllo_p ,non permetto l'inserimento/reinserimento della password
			se incremento controllo_e,non permetto l'inserimento/reinserimento della e-mail
		 	se uscita anticipata = 1 oppure 2 esco in anticipo dal do-while
			se uscita = 1  esco dal ciclo do-while
		 	solo quando uscita = 1 e uscita_anticipata = 2 saprò che il login è avvenuto con successo
			altrimenti se uscita = 1 e uscita_anticipata= 1 saprò che il login  non è avvenuto con successo*/

		if (controllo_e == 0) {
			printf("\n\t\tInserire e-mail:\t"); /*Acquisisco in input le credenziali di accesso*/
			fflush(stdin);
			gets(email_input);

			if ( verifica_email(email_input,cli,num_cli,&indice_c) == 0 ) { /* richiamo la funziona che controlla l'email*/
				printf("\n\tE-mail errata o inesistente !"); /* se è sbagliata, chiedo se riprovare*/

				printf("\n\tRiprovare ad inserire l'e-mail?\n\t Si (S)\t No (N) ");
				fflush(stdin);
				risposta = getchar();

				if (risposta == 'S' || risposta == 's') { /* si, re inserisco l'email*/
					controllo_e = 0;
					controllo_p++;
				}
				else if (risposta == 'N' || risposta == 'n') { /* no ,esco in anticipo*/
					uscita_anticipata = 1;
					uscita = 1;
					controllo_e++;
					controllo_p++;
				}
				else {
					printf("\n\tInput non valido ! Riavvio ...\n\n");
					controllo_p++;
				}
			} else { /* altrimenti controllo_password = 0, passo successivo*/
				controllo_p = 0;
			}
		}

		if (controllo_p == 0) {
			printf("\n\t\tInserire password:\t"); /*Acquisisco la password*/
			fflush(stdin);
			gets(password_input);

			if ( verifica_password(password_input,cli,num_cli) == 0 ) { /* richiamo la funzione di verifica per la password*/
				printf("\n\tPassword errata o inesistente !");	/*Se sbagliata*/
				printf("\n\tRiprovare ad inserire la password?\n\t Si (S)\t No (N) ");
				fflush(stdin);
				risposta = getchar();
				if (risposta == 'S' || risposta == 's') { /*si, re inserisco la password*/
					controllo_p = 0;
					controllo_e++;
				}
				else if (risposta == 'N' || risposta == 'n') { /* no, esco in anticipato*/
					uscita_anticipata = 1;
					uscita = 1;
					controllo_e++;
					controllo_p++;
				}
				else {
					printf("\n\tInput non valido ! Riavvio ...\n\n");
					controllo_p = 0;
				}
			} else { /* posso uscire, uscita = 1 , uscita anticipata = 2*/
				uscita = 1;
				uscita_anticipata = 2;
			}
		}
	} while (uscita != 1 && (uscita_anticipata != 1 || uscita_anticipata != 2 ));

	/* solo al verificarsi delle seguenti condizioni ritorno l'indice del cliente altrimenti un numero negativo di errore*/
	if (uscita == 1 && uscita_anticipata == 2) {
		return (indice_c);
	} else {
		return (-1);
	}
}
//**************************************************************************************************************//
//									FUNZIONE LEGGI_CONTA_CSV_CLIENTI											//
//**************************************************************************************************************//
/**
 * Funzione di lettura da file del csv clienti. Inoltre ritorno il numero di righe
 * @param cli  l'array di strutture clienti
 * @return tighe il numero delle righe del file
 */
int leggi_conta_csv_clienti (cliente_t cli []) {

	FILE* file; /* puntatore al file*/
	char dati[200]; /* stringa di dati per l'acquisizione da file*/
	int i,
	righe = 0; /* conterà le righe e le ritornerà*/


	if( (file = fopen("clienti.csv", "r"))== NULL ) {     /* Aprò il file in lettura, Errore , se non riesco */
		printf("Impossibile aprire il file\n");
	}
	else { /* altrimenti, copio tutti i dati dal file nella mia variabile di appoggio
		    le virgole fungeranno da divisore fra le word*/
		i=0;
		while(fscanf(file,"%s",dati) == 1) {
			fflush(stdin);
			strcat(cli[i].email,strtok(dati, ",")); 		/* leggerà da token a token, e copierà i dati "catturati"*/
			strcat(cli[i].password, strtok(NULL, ","));		/* riponendoli nell'apposito campo della struttura*/
			strcat(cli[i].cod_fiscale, strtok(NULL, ","));
			strcat(cli[i].cognome, strtok(NULL, ","));
			strcat(cli[i].nome, strtok(NULL, ","));
			cli[i].nascita.giorno = atoi(strtok(NULL, ",")); /* per le variabile intere eseguirò una conversione*/
			cli[i].nascita.mese = atoi(strtok(NULL, ","));
			cli[i].nascita.anno = atoi(strtok(NULL, ","));
			cli[i].sconto = atof(strtok(NULL, ";")); /* per la varibile reale*/
			i++;
		}
		righe = i;/* salvo le righe grazie all'indice i*/
	}

	fclose(file);
	return (righe); /* chiudo il filo e ritorno il valore*/
}
//**************************************************************************************************************//
//									FUNZIONE LEGGI_CONTA_CSV_PRENOTAZIONI										//
//**************************************************************************************************************//
/**
 * Funzione di lettura da file del csv prenotazioni. Inoltre ritorno il numero di righe
 il procedimento è analogo a quello visto nella funzione precedente
 * @param pren, l'array di strutture prenotazione
 * @return il numero delle righe del file in oggetto
 */
int leggi_conta_csv_prenotazioni(prenotazione_t pren []) {
	FILE* file;
	char dati[200];
	int i, righe=0;

	if((file = fopen("prenotazioni.csv", "r"))==NULL) {
		printf("Impossibile aprire il file\n");
	}
	else {
		i=0;
		while(fscanf(file,"%s",dati) == 1) {
			fflush(stdin);
			pren[i].cod = atoi(strtok (dati, ","));
			strcpy(pren[i].email, strtok(NULL, ","));
			pren[i].data.giorno = atoi(strtok (NULL, ","));
			pren[i].data.mese = atoi(strtok (NULL, ","));
			pren[i].data.anno = atoi(strtok (NULL, ","));
			pren[i].tipo = atoi(strtok (NULL, ","));
			pren[i].num_ombrellone.ombrellone = atoi(strtok (NULL, ","));
			pren[i].num_ombrellone.fila_o = atoi(strtok (NULL, ","));
			pren[i].num_lettini = atoi(strtok (NULL, ","));
			pren[i].num_sedie = atoi(strtok (NULL, ","));
			pren[i].costo = atof(strtok (NULL, ";"));
			i++;
		}
		righe=i;
	}

	fclose(file);
	return (righe);
}
//**************************************************************************************************************//
//									FUNZIONE VERIFICA EMAIL														//
//**************************************************************************************************************//
/**
 * Confronta due stringhe email, ritorno quante prenotazioni effettua un cliente
 * @param strg_a, stringa a , corrisponderà all'e-mail da in input dal utente
 * @param strg_b , stringa b, sarà invece l'email in possesso al sistema mediante file
 * @param num_clienti , il numero dei clienti
 * @param indice, il puntatore permette di ritornare l'indice
 * @return ritorno verifica, se > 0, il confronto è avvenuto con successo
 */
int verifica_email (char strg_a [],cliente_t strg_b[],int num_clienti, int *indice) {

	int risultato = 0, /* il risultato del confronto tra stringhe , se sono identiche sarà = 0*/
			i = 0,
			verifica = 0;
	for (i = 0; i < num_clienti; i++) {
		if ((risultato = strncmp(strg_a,strg_b[i].email ,40))  == 0) { /* se le stringhe sono uguali allora*/
			verifica++; /* incremento verifica*/
			*indice = i; /* ritorno l'indice del cliente*/
		} /* altrimenti verifica rimmarrà = 0*/
	}

	return (verifica);
}

//**************************************************************************************************************//
//									FUNZIONE VERIFICA PASSWORD													//
//**************************************************************************************************************//
/**
 * Confornta due stringhe password. Il procedimento è analogo a quello visto nella funzione precedente
 * @param strg_a, stringa a , corrisponderà alla password data in input dal utente
 * @param strg_b , stringa b, sarà invece la password in possesso al sistema mediante file
 * @param num_clienti , , il numero dei clienti
 * @return ritorno verifica, se > 0, il confronto è avvenuto con successo
 */
int verifica_password(char strg_a [],cliente_t strg_b[],int num_clienti ) {

	int risultato = 0,
			i = 0,
			verifica = 0;

	for (i = 0; i < num_clienti; i++) {
		if ((risultato = strncmp(strg_a,strg_b[i].password ,10))  == 0) {
			verifica++;
		}
	}

	return (verifica);
}

//**************************************************************************************************************//
//									FUNZIONE CONTROLLO DATA 													//
//**************************************************************************************************************//
/**
 * La funzione verificherà se una data ricevuta in input dall'utente sarà ben formata
 * @param gma, benchè il nome poco significativo, la variabile ha lo scopo di "potenziare' la funzione.
 * 				Infatti grazie un ulteriore controllo potrò verificare o meno , anche date "odierne" e che quindi non saranno minori dell'anno corrente.
 *
 * @param data_gma , la data oggetto del controllo
 * @return errore, se errore sarà > 0 allora il controllo avrà esito negativo
 */
int controllo_data (int gma, data_t data_gma) {
	int errore = 0;

	if (gma != 0) { /* se riceverò 0 allora si tratterà di una data di nascita*/
		if (data_gma.anno < anno_corrente) {
			printf("\n\t\tErrore anno ! Siamo nel %d , inserire un numero maggiore dell'anno corrente !",anno_corrente);
			errore++;
		}
	}


	if (data_gma.mese > 12 || data_gma.mese < 1 ) { /* controllo prima il mese, se compreso fra 1 e 12*/
		printf("\n\t\tErrore mese ! Il mese deve essere compreso fra 1 e 12 !");
		errore++;
	} else if (data_gma.mese == 1 || data_gma.mese == 3 || /* controllo se è un mese da 31 giorni*/
			data_gma.mese == 5 || data_gma.mese == 7 ||
			data_gma.mese == 8 || data_gma.mese == 10 ||
			data_gma.mese == 12) {
		if (data_gma.giorno < 1 || data_gma.giorno > 31) { /* quindi verifico il giorno*/
			printf("\n\t\tErrore giorno ! Il mese selezionato ha al piu' 31 giorni !");
			errore++;
		}
	} else if (data_gma.mese == 2) { /* controllo se il mese è febbraio*/
		if ((data_gma.anno % 4 == 0 && data_gma.anno % 100 != 0) || data_gma.anno % 400 == 0) { /*verifico se l'anno è bisestile*/
			/* Un anno è bisestile se il suo numero è divisibile per 4, con l’eccezione che gli anni secolari
			   (quelli divisibili per 100) sono bisestili solo se divisibili per 400.*/
			if (data_gma.giorno < 1 || data_gma.giorno > 29) { /* se bisestile*/
				printf("\n\t\tErrore giorno ! Il %d e' un anno bisestile ! Il mese selezionato ha al piu' 29 giorni !" , data_gma.anno);
				errore++;
			}
		} else {
			if (data_gma.giorno < 1 || data_gma.giorno > 28) { // se non bisestile
				printf("\n\t\tErrore giorno ! Il %d non e' un anno bisestile ! Il mese selezionato ha al piu' 28 giorni !" , data_gma.anno);
				errore++;
			}
		}
	} else { // altrimenti è un mese da 30 giorni
		if (data_gma.giorno < 1 || data_gma.giorno > 30) {
			printf("\n\t\tErrore giorno ! Il mese selezionato ha al piu' 30 giorni !");
			errore++;
		}
	}
	return (errore);
}
//**************************************************************************************************************//
//									FUNZIONE CONFRONTA PRENOTAZIONE DATA INPUT									//
//**************************************************************************************************************//

/**
 * Funzione che confronta una data in input cone le date delle prenotazioni e
 * restituisce, all'avvenire della condizione, l'indice della prenotazione in oggetto
 * @param pre, array di strutture prenotazione
 * @param num_p, numero di prenotazioni
 * @param data_in , data in input dall'utente
 * @return , ritorna l'indice della prenotazione oppure 0
 */
int confronta_prenotazione_data_input (prenotazione_t pre[], int num_p, data_t data_in) {
	int i = 0,
			verifica = 0;


	for (i = 0; i < num_p; i++) { // confronto giorno,mese,anno per ogni prenotazione
		if (data_in.giorno == pre[i].data.giorno) {
			if (data_in.mese == pre[i].data.mese) {
				if (data_in.anno == pre[i].data.anno) {
					verifica++;
				}
			}
		}
	}

	return verifica;
}
//**************************************************************************************************************//
//									FUNZIONE STAMPA TIPO														//
//**************************************************************************************************************//
/**
 * La funzione stamperà a video l'equivalente numerico della tipologia di prenotazione
 * @param tipo_i , il tipo, oggetto di una prenotazione
 */
void stampa_tipo (int tipo_i) {
	if (tipo_i == 1) {
		printf("Mattina");
	} else if (tipo_i == 2) {
		printf("Pomeriggio");
	} else if (tipo_i == 3) {
		printf("Giornata intera");
	}
}

//**************************************************************************************************************//
//									FUNZIONE CONTROLLA TIPO GIORNATA											//
//**************************************************************************************************************//
/**
 * La funzione prende il tipo e il flag doppia prenotazione e calcola la disponibilità relativa ad essa
 * @param tipo_p , il tipo di prenotazione
 * @param doppia_p_a , flag, >1 se ho già due prenotazioni in quel giorno
 * @return
 */
int controlla_tipo_giornata(int tipo_p, int doppia_p_a) {
	int check;

	if (tipo_p == 3) { /* se giornata intera*/
		check = 3; /* allora disponibilità nulla (=3) */
	} else if (tipo_p == 1) { /* se mattina*/
		check = 2; /* allora  pomeriggio*/
	} else {
		check = 1; /* se pomeriggio , allora mattina */
	}
	if (doppia_p_a > 1) { /* se già esistono due prenotazioni */
		check = 3;
	}
	return (check); /* ritorno la disponibilità */
}

//**************************************************************************************************************//
//									FUNZIONE STAMPA OMBRELLONI LIBERI											//
//**************************************************************************************************************//
/**
 * La funzione acquisita la struttura contenente le disponibilità di una determinata fila, la stamperà a video
 * @param ombr_disp_a , struttura fila di ombrelloni
 */
void stampa_ombrelloni_liberi (pren_ombr_disponibile_t ombr_disp_a) {

	int w = 0;

	for (w = 0; w <  max_ombrelloni; w++) {
		if ( w % 5 == 0) {
			printf("\n");
		}
		if (ombr_disp_a.ombrelloni[w].check ==  0) { /* se 0 quindi invariato */
			printf("\t| %d G " , ombr_disp_a.ombrelloni[w].ombrellone); /*disponibile per la giornata */
		} else if  (ombr_disp_a.ombrelloni[w].check == 1) {  /* se 1 */
			printf("\t| %d M ", ombr_disp_a.ombrelloni[w].ombrellone); /*disponibile per la mattina */
		} else if (ombr_disp_a.ombrelloni[w].check == 2) { /* se 2 */
			printf("\t| %d P ",ombr_disp_a.ombrelloni[w].ombrellone);  /*disponibile per il pomeriggio */
		} else if (ombr_disp_a.ombrelloni[w].check == 3) { /* se 3 */
			printf("\t| // "); /* non disponibile */
		}
	}
	printf("\n");
}

//**************************************************************************************************************//
//									FUNZIONE VERIFICA DISPONIBILITA TUTTI OMBRELLONI							//
//**************************************************************************************************************//
/**
 * La funzione verifica la disponibilità di tutte le file e gli ombrelloni per una specifica data
 * @param prenotazioni_a , array di strutture prenotazione
 * @param data_i_a , data inserita dall'utente
 * @param num_p_a , numero di prenotazioni
 * @param crdecr , variabile di controllo per lo switch , oltre che stabilire l'ordinamente crescente o decrescente
 * @param indice , l'indice oggetto di una determinata prenotazione
 * @param ombr_a , l'ombrellone inserito
 */
void verifica_disp_tutti_ombrelloni (prenotazione_t prenotazioni_a [], data_t data_i_a, int num_p_a, int crdecr,int indice, ombrellone_t ombr_a []) {
	pren_ombr_disponibile_t ombr_disp_a [max_file]; /* creo la mia struttura delle disponibilità*/
	int i = 0,		/* gli incidi di cicli ed array */
			j = 0,
			k = 0,
			l = 0,
			m = 0,
			n = 0,
			o = 0,
			p = 0;

	for (l = 0; l < max_file; l++) {	//per ogni fila
		for (m = 0; m < max_ombrelloni; m++){ //per ogni ombrellone
			ombr_disp_a[l].ombrelloni[m].ombrellone = m+1; //resetta la mia struttura a parametri nulli
			ombr_disp_a[l].ombrelloni[m].doppia_prenotazione = 0;
			ombr_disp_a[l].ombrelloni[m].check = 0;
		}
	}

	for (i = 0; i < num_p_a; i++){ //per ogni prenotazione
		if (data_i_a.giorno == prenotazioni_a[i].data.giorno && // è uguale alla data inserita dall'utente?
				data_i_a.mese == prenotazioni_a[i].data.mese &&
				data_i_a.anno == prenotazioni_a[i].data.anno ) {
			for (k = 0; k < max_file; k++) { //se si, allora per ogni fila
				if (prenotazioni_a[i].num_ombrellone.fila_o == (k+1)) {  // verifica se il numero di fila è = a quello della prenotazione (k+1 perchè indice di array)
					for (j = 0; j < max_ombrelloni; j++) { //se si , allora per ogni ombrellone
						if (prenotazioni_a[i].num_ombrellone.ombrellone == ombr_disp_a[k].ombrelloni[j].ombrellone ){ // verifica se sono uguali a quello della prenotazione
							ombr_disp_a[k].ombrelloni[j].doppia_prenotazione++; //se si , allora aggiorna il flag
							ombr_disp_a[k].ombrelloni[j].check = controlla_tipo_giornata (prenotazioni_a[i].tipo, ombr_disp_a[k].ombrelloni[j].doppia_prenotazione); // e stabiliscine la disponibiltà
						}
					}
				}
			}
		}
	} //in questo modo avrò "segnato" tutte le mie prenotazioni sulla mia struttura

	// il"crescente o descrescente" lo userò anche per potenziare la funzione
	// infatti nello switch seguente si aggiungono i casi 0 : qualora volessi salvare nell'array di strutture prenotazione
	// 3: qualora volessi stampare una fila di ombrelloni
	switch (crdecr) {
	case 0:
		for (o = 0; o < max_file; o++){
			for(p = 0; p < max_ombrelloni; p++){
				if (prenotazioni_a[indice].num_ombrellone.fila_o == (o+1)){
					if (prenotazioni_a[indice].num_ombrellone.ombrellone ==  ombr_disp_a[o].ombrelloni[p].ombrellone){
						prenotazioni_a[indice].num_ombrellone.doppia_prenotazione = ombr_disp_a[o].ombrelloni[p].doppia_prenotazione;
						prenotazioni_a[indice].num_ombrellone.check = ombr_disp_a[o].ombrelloni[p].check;
					}
				}
			}
		}
		break;
	case 1: // stampa crescente
		for (n = 0; n < max_file; n++) {
			printf("\n\tFila numero: %d",n+1 );
			stampa_ombrelloni_liberi(ombr_disp_a[n]);
		}
		break;
	case 2: // stampa decrescente
		for ( n = max_file-1; n >= 0; n--) {
			printf("\n\tFila numero: %d",n+1 );
			stampa_ombrelloni_liberi(ombr_disp_a[n]);
		}
		break;
	case 3:
		stampa_ombrelloni_liberi(ombr_disp_a[prenotazioni_a[indice].num_ombrellone.fila_o-1]);
		for(p = 0; p < max_ombrelloni; p++){
			ombr_a[p].ombrellone =  ombr_disp_a[prenotazioni_a[indice].num_ombrellone.fila_o-1].ombrelloni[p].ombrellone;
			ombr_a[p].doppia_prenotazione = ombr_disp_a[prenotazioni_a[indice].num_ombrellone.fila_o-1].ombrelloni[p].doppia_prenotazione;
			ombr_a[p].check = ombr_disp_a[prenotazioni_a[indice].num_ombrellone.fila_o-1].ombrelloni[p].check;
		}

		break;
	}
}

//**************************************************************************************************************//
//									FUNZIONE STAMPA A VIDEO PRENOTAZIONE										//
//**************************************************************************************************************//
/**
 * La funzione stampa a video una prenotazione data per input
 * @param pren array di strutture prenotazione
 */
void stampa_a_video_prenotazione (prenotazione_t pren) {
	printf("\n\t\t\tCod. prenotazione: %d\n\t\t\tE-Mail cliente: %s\n\t\t\tData: %d/%d/%d\t\tTipo: ",
			pren.cod,pren.email,pren.data.giorno,pren.data.mese,pren.data.anno);
	stampa_tipo(pren.tipo);
	printf("\n\t\t\tNumero ombrellone: %d\t\tFila: %d\n\t\t\tLettini: %d\t\tSedie: %d\n\t\t\tTotale: %f euro",
			pren.num_ombrellone.ombrellone,pren.num_ombrellone.fila_o,pren.num_lettini,pren.num_sedie,pren.costo);
}
//**************************************************************************************************************//
//									FUNZIONE CALCOLA TOTALE    													//
//**************************************************************************************************************//
/**
 * La funzione calcola il totale oggetto di una nuova prenotazione
 * @param sconto_u  sconto da applicare alla prenotazione dell'utente
 * @param ombr_i varibile tipo ombrellone contente fila, ombrellone della nuova prenotazione
 * @param tipo_i , il tipo di prenotazione della nuova prenotazione
 * @param lettini_i  il numero di lettini della nuova prenotazione
 * @param sedie_i  il numero di sedie della nuova prenotazione
 * @return ritorno il costo totale
 */
double calcola_totale (double sconto_u, ombrellone_t ombr_i,int tipo_i, int lettini_i, int sedie_i) {
	double totale_a = 0,
			sconto_temp = 0;

	if (ombr_i.fila_o == 1 || ombr_i.fila_o == 2) { /* vedere la traccia o la documentazione per avere maggiori informazioni riguardo le costanti usate */
		totale_a = 25;
		totale_a = totale_a + (lettini_i * 10);
		totale_a = totale_a + (sedie_i * 7);
	} else if (ombr_i.fila_o == 3 || ombr_i.fila_o == 4) {
		totale_a = 20;
		totale_a = totale_a + (lettini_i * 8);
		totale_a = totale_a + (sedie_i * 5);
	} else  {
		totale_a = 15;
		totale_a = totale_a + (lettini_i * 5);
		totale_a = totale_a + (sedie_i * 3);
	}

	if ( tipo_i == 1 || tipo_i == 2) {
		totale_a = (totale_a / 2);
	}

	if (sconto_u > 0) {
		sconto_temp =  (sconto_u * totale_a) /100;
		totale_a = totale_a - sconto_temp;
	}

	return (totale_a);

}

//**************************************************************************************************************//
//									FUNZIONE STAMPA PRENOTAZIONE    											//
//**************************************************************************************************************//
/**
 * La funzione stamperà le prenotazioni dall'array di strutture prenotazione
 * @param pren_a   array di strutture prenotazione
 * @param num_pren_a   numero delle prenotazioni
 */
void stampa_prenotazione(prenotazione_t pren_a[], int num_pren_a){
	FILE *file;
	int i = 0;
	file = fopen("prenotazioni.csv", "w"); /* apro il file */
	if( file == NULL ) {
		printf("Impossibile aprire il file\n");
	} else {
		for (i = 0; i < num_pren_a; i++) {
			if (i != 0) {
				fprintf(file,"\n");
			}
			fprintf(file, "%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%f;", /* stampo le prenotazioni */
					pren_a[i].cod,pren_a[i].email,
					pren_a[i].data.giorno,pren_a[i].data.mese,pren_a[i].data.anno,
					pren_a[i].tipo,pren_a[i].num_ombrellone.ombrellone, pren_a[i].num_ombrellone.fila_o,
					pren_a[i].num_lettini,pren_a[i].num_sedie,pren_a[i].costo );
		}
	}
	fclose(file);
}
