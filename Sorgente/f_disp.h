/*
 * f_disp.h
 *  Created on: 04 set 2018
 *  Author: Matteo Luceri
 */

#ifndef F_DISP_H_
#define F_DISP_H_
/**
 * La funzione verificherà la disponibilità  di quali ombrelloni sono liberi della fila specificata dal cliente in una certa data
 * @param prenotazioni_a , array di strutture prenotazione
 * @param num_p_a , numero di prenotazioni
 */
void ombrelloni_disponibili_fila (prenotazione_t [], int );

/**
 * Confronto il numero di fila dato input dall'utente con le file oggetto di una prenotazione
 * @param pre, array di strutture prenotazione
 * @param ombr , variabile di tipo ombrellone inserita dall'utente
 * @param num_p ,numero di prenotazioni
 * @return ritorno il valore di verifica, > 0 sse il confronto è positivo
 */
int confronta_prenotazione_fila (prenotazione_t [], ombrellone_t , int );

/**
 * La funzione acquisita una data dall'utente restituisce la disponibilità ti tutti gli ombrelloni,
 * ordinando le file in ordine a scelta crescente o decrescente
 * @param prenotazioni_a, array di strutture prenotazione
 * @param num_p_a, numero di prenotazioni
 */
void ombrelloni_disponibili_fila_cresc_decr (prenotazione_t [], int );

/**
 * La funzione  permette di modificare il tipo di prenotazione e/o l'ombrellone, a scelta dell'utente
 *
 * @param prenotazione , array di strutture prenotazione
 * @param num_prenotazioni, numero di prenotazioni
 * @param indice , indice del cliente che ha fatto l'accesso
 * @param num_clienti , il numero di clienti
 * @param client , array di strutture cliente
 */
void modifica_prenotazione_tipo_ombrellone(prenotazione_t [], int , int , int , cliente_t [] );

/**
 * La funzione modifica il tipo di una prenotazione quando possibile
 * @param prenotazione , array di strutture prenotazione
 * @param indice , indice del cliente che ha fatto l'accesso
 * @param num_pren, numero di prenotazioni
 */
void modifica_tipo_prenotazione(prenotazione_t [], int , int );

/**
 * La funzione modifica il numero di ombrellone qualora possibile
 * @param prenotazione , array di strutture prenotazione
 * @param indice , indice del cliente che ha fatto l'accesso
 * @param num_pren, numero di prenotazioni
 */
void modifica_num_ombrellone_prenotazione (prenotazione_t [] , int, int);

#endif /* F_DISP_H_ */
