# Prova Finale di algoritmi e strutture dati 2020.
Il codice é consultabile [qui](/Code/progetto.c).  
Le specifiche complete sono consultabili [qui](/Doc/specifiche.pdf).
## edU, o ed con Undo multipli
Il progetto consiste in un editor di testo scritto in **C**, con la possibilità di effettuare undo e redo multipli, durante gli inserimenti, oltre a consueta stampa e eliminazione.   
La valutazione tiene conto dell'efficienza spazio-temporale del programma, oltre alla verifica di output corretto a fronte di alcuni test privati, con migliaia di righe di input.

Sono stati implementati i seguenti comandi:
  * **(ind1,ind2)c**: Change da ind1 a ind2 compresi.
  * **(ind1,ind2)d**: Delete da ind1 a ind2 compresi.
  * **(ind1,ind2)p**: Print da ind1 a ind2 compresi.
  * **(num)u**: Effettua l'undo di num operazioni.
  * **(num)r**: Effettua il redo di num operazioni.
  * **q**: Termina l'esecuzione.

Una riga di testo fornita in ingresso all'editor puó contenere al massimo 1024 caratteri.  
Viene inoltre assunto che i comandi siano inseriti sempre correttamente.

## Esempio:
**Input**  
1,2c  
prima riga  
seconda riga  
.  
2,3c  
nuova seconda riga  
terza riga  
.  
1,3p  
1,1c  
nuova prima riga  
.  
1,2p  
2,2d  
4,5p  
1,3p  
4,5d  
1,4p  
3u  
1,6p  
1r  
1,3p  
q  

**Output**:  
prima riga  
nuova seconda riga  
terza riga  
nuova prima riga  
nuova seconda riga  
.  
.  
nuova prima riga  
terza riga  
.  
nuova prima riga  
terza riga  
.  
.  
prima riga  
nuova seconda riga  
terza riga  
.  
.  
.  
nuova prima riga  
nuova seconda riga  
terza riga  

## Implementazione
Si é implementato l'intero algoritmo utilizzando principalmente:
  * **Una lista concatenata** contenente il testo corrente.
  * **Una pila per** effettuare le operazioni di **undo**.
  * **Una pila** per effettuare le operazioni di **redo**.  

Nella lista concatenata vengono salvate tutte le stringhe derivate dalle operazioni di **change**.    
Ogni volta che viene effettuata una operazione che puo essere annullata (**Change o Delete**), viene salvata coerentemente sulla pila degli undo.    
Quando vengono effettuati degli **undo** viene conseguentemente svuotata la pila di undo annullando le operazioni.    
In seguito agli **undo** viene coerentemente riempita la pila di redo.  
In caso in cui vengono effettuati dei **redo** viene svuotata la pila dei redo eseguendo di nuovo le operazioni precedentemente annullate.    
La pila dei redo viene svuotata nel caso in cui vengano eseguite delle operazioni annullabili (**Change o Delete**) dopo una successione di **undo** e **redo**.  

## Conclusione
L'implementazione si é rivelata corretta e adatta a livello di costo spazio-temporale, sia per i [casi di test pubblici](/Public_Tests) che per i casi di test privati.

