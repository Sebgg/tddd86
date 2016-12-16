/**********************************************************************
 *  M�nsterigenk�nning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga k�rtider i sekunder
 *  analys      n�r det k�nns vettigt att v�nta p� hela ber�kningen.
 *              Ge uppskattningar av k�rtiden i �vriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering
 ----------------------------------
    150       48,2ms	  33ms
    200	      111,1ms	  46ms
    300	      327,8ms	  99ms
    400	      783ms	  173ms
    800	      5843,9ms	  639ms
   1600	      46687,2ms	  2544ms
   3200	      375617ms	  10469ms	//Did not finish the computing process for brute
   6400	      TL;DC	  43740ms
  12800	      TL;DC	  183278ms


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck f�r v�rstafallstiden f�r programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: O(n^4)
fyra for-loopar som ligger n�stlade och i v�rsta fall l�per genom alla n g�nger.

Sortering: O(n^2log(n))

Vi har tv� for-loopar bredvid varandra (n+n) n�stlade i en for-loop (n(n+n)).
log(n) kommer ifr�n att l�gga till point i map.
