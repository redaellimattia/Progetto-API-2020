# Progetto di algoritmi e strutture dati.
Il progetto consiste in un editor di testo scritto in C, con la possibilità di effettuare undo e redo multipli, durante gli inserimenti, oltre a consueta stampa e eliminazione.

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

##Implementazione
La valutazione tiene conto dell'efficienza spazio-temporale del programma, oltre alla verifica di output corretto a fronte di alcuni test privati, con migliaia di righe di input.
