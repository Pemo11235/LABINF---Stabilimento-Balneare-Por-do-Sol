/*
 *  f_all_shared.h
 *  Created on: 04 set 2018
 *  Author: Matteo Luceri
 */


#ifndef F_ALL_SHARED_H_
#define F_ALL_SHARED_H_
/**
 * La funzione permetterà mediante confronto di verificare l'accesso degli utenti registrati
 * @param cli , l'array della struttura clienti
 * @param num_cli, il numero dei clienti
 * @return ritornerà il l'indice del cliente o , -1
 * indicante un valore negativo che idicherà l'errore al sistema
 */
double login ( cliente_t [], int );

/**
 * Funzione di lettura da file del csv clienti. Inoltre ritorno il numero di righe
 * @param cli , l'array di strutture clienti
 * @return il numero delle righe del file
 */
int leggi_conta_csv_clienti (cliente_t []);

/**
 * Funzione di lettura da file del csv prenotazioni. Inoltre ritorno il numero di righe
 il procedimento è analogo a quello visto nella funzione precedente
 * @param pren, l'array di strutture prenotazione
 * @return il numero delle righe del file in oggetto
 */
int leggi_conta_csv_prenotazioni (prenotazione_t [] );

/**
 * Confronta due stringhe email, ritorno quante prenotazioni effettua un cliente
 * @param strg_a, stringa a , corrisponderà all'e-mail da in input dal utente
 * @param strg_b , stringa b, sarà invece l'email in possesso al sistema mediante file
 * @param num_clienti , il numero dei clienti
 * @param indice, il puntatore permette di ritornare l'indice
 * @return ritorno verifica, se > 0, il confronto è avvenuto con successo
 */
int verifica_email(char [],cliente_t [], int  , int *);

/**
 * Confornta due stringhe password. Il procedimento è analogo a quello visto nella funzione precedente
 * @param strg_a, stringa a , corrisponderà alla password data in input dal utente
 * @param strg_b , stringa b, sarà invece la password in possesso al sistema mediante file
 * @param num_clienti , , il numero dei clienti
 * @return ritorno verifica, se > 0, il confronto è avvenuto con successo
 */
int verifica_password (char [],cliente_t [], int );

/**
 * La funzione verificherà se una data ricevuta in input dall'utente sarà ben formata
 * @param gma, benchè il nome poco significativo, la variabile ha lo scopo di "potenziare' la funzione.
 * 	Infatti grazie un ulteriore controllo potrò verificare o meno , anche date "odierne" e che quindi non saranno minori dell'anno corrente.
 *
 * @param data_gma , la data oggetto del controllo
 * @return errore, se errore sarà > 0 allora il controllo avrà esito negativo
 */
int controllo_data (int , data_t );

/**
 * La funzione stamperà le prenotazioni dall'array di strutture prenotazione
 * @param pren_a , array di strutture prenotazione
 * @param num_pren_a , numero delle prenotazioni
 */
void stampa_prenotazione(prenotazione_t [], int );

/**
 * La funzione calcola il totale oggetto di una nuova prenotazione
 * @param sconto_u , sconto da applicare alla prenotazione dell'utente
 * @param ombr_i, varibile tipo ombrellone contente fila, ombrellone della nuova prenotazione
 * @param tipo_i , il tipo di prenotazione della nuova prenotazione
 * @param lettini_i, il numero di lettini della nuova prenotazione
 * @param sedie_i, il numero di sedie della nuova prenotazione
 * @return ritorno il costo totale
 */
double calcola_totale (double , ombrellone_t ,int , int , int  );

/**
 * La funzione stamperà a video l'equivalente numerico della tipologia di prenotazione
 * @param tipo_i , il tipo, oggetto di una prenotazione
 */
void stampa_tipo(int );

/**
 * Funzione che confronta una data in input cone le date delle prenotazioni e
 * restituisce, all'avvenire della condizione, l'indice della prenotazione in oggetto
 * @param pre, array di strutture prenotazione
 * @param num_p, numero di prenotazioni
 * @param data_in , data in input dall'utente
 * @return , ritorna l'indice della prenotazione oppure 0
 */
int confronta_prenotazione_data_input (prenotazione_t [], int , data_t );

/**
 * La funzione prende il tipo e il flag doppia prenotazione e calcola la disponibilità relativa ad essa
 * @param tipo_p , il tipo di prenotazione
 * @param doppia_p_a , flag, >1 se ho già due prenotazioni in quel giorno
 * @return
 */
int controlla_tipo_giornata ( int , int );

/**
 * La funzione acquisita la struttura contenente le disponibilità di una determinata fila, la stamperà a video
 * @param ombr_disp_a , struttura fila di ombrelloni
 */
void stampa_ombrelloni_liberi (pren_ombr_disponibile_t );

/**
 * La funzione verifica la disponibilità di tutte le file e gli ombrelloni per una specifica data
 * @param prenotazioni_a , array di strutture prenotazione
 * @param data_i_a , data inserita dall'utente
 * @param num_p_a , numero di prenotazioni
 * @param crdecr , variabile di controllo per lo switch , oltre che stabilire l'ordinamente crescente o decrescente
 * @param indice , l'indice oggetto di una determinata prenotazione
 * @param ombr_a , l'ombrellone inserito
 */
void verifica_disp_tutti_ombrelloni (prenotazione_t  [], data_t , int ,int ,int ,ombrellone_t [] );

/**
 * La funzione stampa a video una prenotazione data per input
 * @param pren, array di strutture prenotazione
 */
void stampa_a_video_prenotazione(prenotazione_t);

#endif /* F_ALL_SHARED_H_ */
