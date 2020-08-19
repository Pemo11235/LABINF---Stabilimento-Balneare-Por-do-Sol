/*
 * f_new_pren.h
 *  Created on: 04 set 2018
 *  Author: Matteo Luceri
 */


#ifndef F_NEW_PREN_H_
#define F_NEW_PREN_H_
/**
 * La procedura permetterà la prenotazione di un ombrellone in una determinata data
 * @param pren , array di strutture prenotazione
 * @param num_pren, numero di prenotazioni
 * @param cli,  array di strutture cliente
 * @param index , l'indice relativo al cliente che ha eseguito l'accesso
 */
void prenota_ombrellone(prenotazione_t [] , int ,cliente_t [] , int  );

/**
 * La funzione prima verifica che il numero di ombrellone e fila siano validi.
 * Dopo di che verifica che non esistano prenotazioni già effettuate con la stessa fila ed ombrellone.
 * Inoltre verifico il tipo di prenotazione. Infatti se tipo = 3 (giornata intera)  la prenotazione non potrà effettuarsi
 * @param pre , array di strutture prenotazione
 * @param ombr, struttura ombrellone ,data in input dall'utente
 * @return ritorno l'indice della prenotazione trovata, altrimenti 0.
 * 			Inoltre verifico il tipo, ritornando i valori mediante la struttura ombrellone
 */
int confronta_prenotazione_num_ombrellone_fila (prenotazione_t  [],ombrellone_t );

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
void stampa_nuova_prenotazione (cliente_t [], int , data_t, ombrellone_t, prenotazione_t [], int ,int , int , int , double) ;

/**
 * La funzione acquisisce e restituisce il tipo di prenotazione mediante l'input dell'utente
 * @return , ritorno il tipo di prenotazione
 */
int tipo_mpg ();

/**
 * La funzione acquisisce e restituisce il numero  di lettini oggetto di una nuova prenotazione mediante l'input dell'utente
 * @return , ritorno il numero di lettini
 */
int lettini ();

/**
 * La funzione acquisisce e restituisce il numero  di sedie oggetto di una nuova prenotazione mediante l'input dell'utente
 * @return , ritorno il numero di sedie
 */
int sedie ();

#endif /* F_NEW_PREN_H_ */
