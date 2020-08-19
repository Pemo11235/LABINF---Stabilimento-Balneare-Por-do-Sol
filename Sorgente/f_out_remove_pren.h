/*
 * f_out_remove.pren.h
 *  Created on: 04 set 2018
 *  Author: Matteo Luceri
 */

#ifndef F_OUT_REMOVE_PREN_H_
#define F_OUT_REMOVE_PREN_H_
/**
 * La funzione rimuoverà una prenotazione a scelta fra quelle dell'utente
 * @param pren , array di strutture prenotazione
 * @param num_p, numero di prenotazioni
 * @param client , array di strutture cliente
 */
void rimuovi_prenotazione(prenotazione_t [], int , cliente_t );

/**
 * La funzione rimuove una prenotazione  non stampadola ed aggiorna il csv delle prenotazioni
 * @param pren_a, array di strutture prenotazione
 * @param num_p , numero delle prenotazioni
 * @param num_sel , il codice  della prenotazione da eliminare (proveniente dall'array di indici
 */
void stampa_rimuovi_prenotazione (prenotazione_t [], int , int);

/**
 * La funzione permette il salvataggio fisico, previo ordinamento, di tutte le prenotazioni divise per data
 * @param pren ,array di strutture prenotazione
 * @param num_p, numero delle prenotazioni
 */
void salva_prenotazioni_per_data();

/**
 * La funzione ordina le prenotazioni per data
 * @param pren , array di strutture prenotazione
 * @param num_p , numero di prenotazioni
 */
void ordinamento_prenotazioni_data (prenotazione_t [], int );

/**
 * La funzione transformera la struttura data in un unico campo intero
 * @param giorno , campi della struttura data
 * @param mese ,  		"
 * @param anno , 		"
 * @return ritorno la data per esteso (formato aaaammgg)
 */
int data_estesa (int , int , int );

#endif /* F_OUT_REMOVE_PREN_H_ */
