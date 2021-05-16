/******************************************************************
* Projekt: Algorithmen und Datenstrukturen
* Dateiname: main.c
* Beschreibung: Dieses Programm erstellt und verwaltet eine einfach
                verkettete Liste.
* Autor: Lukas Klink
* Matr.-Nr.: 937548
* Erstellt: 14.05.2021
******************************************************************/

/*********** Hinweis ***********/
/*
Einzelne Tests in CodeFreak können unerwartet fehlschlagen.
Das kann auch daran liegen, dass die Aufgabenstellung im Detail
unterschiedlich interpretiert werden kann. Beispielsweise setzen die
Tests voraus, dass bei einer leeren Liste immer ein Element an Position 1
eingefügt werden kann.

Funktioniert das Programm in Ihren Augen korrekt, fragen Sie gern nach,
warum ein bestimmter Test fehlschlägt.
*/


#include <stdio.h>
#include <stdlib.h>

// Hier Konstanten und Statuscodes definieren
#define NOT_IMPLEMENTED_ERROR -1000
#define LIST_IS_NOT_THAT_LONG -13
#define LIST_DOES_NOT_HAVE_THIS_ELEMENT -404
#define LISTS_START_AT_ZERO -1
#define EMPTY_LIST = -42
#define THERE_IS_NO_LIST -406
#define NOT_ENOUGH_STORAGE -507
#define UNKNOWN_ENUMERATION_KEYWORD -403
#define SUCCESS 0


// Hier Struktur und globale Variablen definieren
typedef struct liste {
    int daten;
    struct liste*pnext;
}
Liste;

Liste*pStart = NULL;
Liste*pElement = NULL;


// Vorgegebene Enumeration als Hilfestellung
enum DIRECTION { FORWARD, REVERSE } direction;


/* Vorgegebene Unterprogramme zur Verwaltung der verketteten Liste */
/* Die folgenden 6 Funktionen werden von CodeFreak erwartet.       */
/* Fehler sollten durch die Rückgabe eines negativen Statuscodes   */
/* kenntlich gemacht werden. */
int put_entry(int position, int aktdata);  /* Eintrag einfuegen */
int del_entry(int position);               /* Eintrag Loeschen  */
int find_entry(int value);                 /* Eintrag suchen    */
int del_list(void);                       /* Liste loeschen    */
int get_anzentries(void);                  /* Anzahl ermitteln  */
int printall(enum DIRECTION direction);    /* Liste ausgeben    */


int main(void)
{
   printf("START:\n");
   put_entry(1,0);
   put_entry(1,1);
   put_entry(2,2);
   put_entry(3,3);
   put_entry(2, 4);


   printf("DELETE: %d\n", del_list());
   put_entry(1, 1);
   del_list();
   put_entry(0,1);
   del_list();

   printf("Entries: %d\n", get_anzentries());

   put_entry(1, 1);
   put_entry(2, 2);
   put_entry(1, 0);


   printf("Put-Fail: %d\n", put_entry(13, 13));
   printf("Delete-Fail: %d\n", del_entry(42));
   printf("Find-Fail: %d\n", find_entry(404));

   del_list();

   printf("_______________________\n");
   put_entry(0, 10);
   put_entry(2, 42);
   put_entry(21, 42);
   put_entry(3, 21);
   put_entry(4, 4);
   printall(FORWARD);
   return 0;
}


/* Unterprogramm zum Einfuegen eines Nutzdatenelements
*  Parameter: position = Einfuegepos.; 0 = vor pStart
*             aktdata  = einzufuegende Zahl
*/
int put_entry(int position, int aktdata) /* Einfuegen */
{
   if (position < 1) {
      return LISTS_START_AT_ZERO;
   }

   Liste *pTemp;
   Liste *pNew = (Liste*)malloc(sizeof(Liste));
   Liste element;
   pElement = &element;
   int i = 1; //TODO: HERE IS DA ERROR AND I NEED TO FIND OUT HOW TO FIX IT!!

   if (pNew == NULL) {
      return NOT_ENOUGH_STORAGE;
   }

   pElement->pnext = pStart;
   pNew->daten = aktdata;

   if (pStart == NULL && position < 2) {
      pStart = pNew;
      pStart->pnext = NULL;
      return SUCCESS;
   }

   while (i < position && pElement->pnext != NULL) {
      pElement = pElement->pnext;
      i++;
   }
   if (i != position) {
      free(pNew);
      return LIST_IS_NOT_THAT_LONG;
   } else {
      pTemp = pElement->pnext;
      pElement->pnext = pNew;
      pNew->pnext = pTemp;
      if (position < 2) {
         pStart = pNew;
      }
   }

   return SUCCESS;
}


/* Unterprogramm zu Ausgabe aller Listenelemente
*  Parameter: direction  = FORWARD	vorwaerts
*                        = REVERSE	rueckwaerts
*  Return:    0          = alles OK
*         negative Werte = Fehler
*/
int printall(enum DIRECTION direction)
{  
   if(direction == FORWARD) {
      pElement = pStart->pnext;
      while (pElement != NULL){
         printf("%d, ", pElement->daten);
         pElement = pElement->pnext;
      }
      return SUCCESS;
   } else if (direction == REVERSE) {
      pElement = pStart;
      for (int i = get_anzentries(); i > 0; i--) {
         printf("%d, ", (pElement+i)->daten);
      }
      return SUCCESS;
   }

   return UNKNOWN_ENUMERATION_KEYWORD;
}


/* Unterprogramm zum Loeschen der gesamten Liste
*  Parameter: keine
*  Return:    0         = Loeschen OK
*         negative Werte = Fehler
*/
int del_list(void)
{
   Liste *pDelete;

   if(pStart == NULL) {
      return THERE_IS_NO_LIST;
   }

   pDelete = pStart;
   pStart = NULL;

   while (pDelete != NULL) {
      pElement = pDelete->pnext;
      free(pDelete);
      pDelete = pElement;
   }

   return SUCCESS;
}


/* Unterprogramm zum Loeschen eines Nutzdatenelements
*  Parameter: position   = Loeschpos.;
*  Return:    0          = Loeschen OK
*         negative Werte = Fehler
*/
int del_entry(int position) /* Loeschen (delete) */
{
   if (position < 0) {
      return LISTS_START_AT_ZERO;
   }

   int i = 0;
   Liste *pTemp;
   Liste element;
   pElement = &element;
   pElement->pnext = pStart;

   if(pStart == NULL) {
      return THERE_IS_NO_LIST;
   }

   while (i < position && pElement->pnext != NULL) {
      pElement = pElement->pnext;
      i++;
   }
   if (i != position) {
      return LIST_IS_NOT_THAT_LONG;
   } else {
      pTemp = pElement->pnext;
      pElement->pnext = pTemp->pnext;
      free(pTemp);
   }
   if (!position) {
      pStart = pElement->pnext;
   }

   return SUCCESS;
}


/* Unterprogramm zur Ermittlung der Elementanzahl
*  Parameter: keine
*  Return:    aktuelle Anzahl der Element
*/
int get_anzentries(void)      /* Anzahl ermitteln  */
{
   int anzahlElemente = 0;
   pElement = pStart;

   while (pElement != NULL){
      pElement = pElement->pnext;
      anzahlElemente++;
   }
   
   return anzahlElemente;
}


/* Unterprogramm zum Suchen eines Elementes
*  Parameter: value      = Zahl, nach der gesucht wird
*  Return:    -404          = nicht gefunden
*         negative Werte = Fehler
*/
int find_entry(int value)
{
   int position = 1;
   pElement = pStart;

   if(pStart == NULL) {
      return THERE_IS_NO_LIST;
   }
   
   while(pElement != NULL) {
      if(pElement->daten == value) {
         return position;
      }
      position ++;
      pElement = pElement->pnext;
   }

   return LIST_DOES_NOT_HAVE_THIS_ELEMENT;
}