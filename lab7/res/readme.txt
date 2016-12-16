/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
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
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: O(n^4)
fyra for-loopar som ligger nästlade och i värsta fall löper genom alla n gånger.

Sortering: O(n^2log(n))

Vi har två for-loopar bredvid varandra (n+n) nästlade i en for-loop (n(n+n)).
log(n) kommer ifrån att lägga till point i map.
