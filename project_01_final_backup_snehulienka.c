// projekt1.c -- Projekt1 - Snehulienka
// Fedor Bozik, 1.3.2017 13:11:30
/* POPIS:
1.Prva funkcia nam zistuje id daneho ovocia, prejde rolkaA az po koniec a ak zisti ze sa id 
nachadza tak vypise dane najdene id, ak nie tak ho zapise a prida na koniec nulovy znak(znak 
ukoncenia), id a meno si davam aj do pamate(strukt.) ak sa v nej nenachadza. 
2. Druha funkcia vytvara sklad ako dynamicke dvojrozmerne pole alokovane pomocou calloc. 
Tiez v cykloch pamati(strukt.) a rolkaB nastavujem zaciatocne/zakl..
3. Tretia funkcia v cykle vypisuje znaky od pozicie id v rolkaA po nulty znak.
4.Stvrta funkcia vklada ovocia podla rozmerov ovocia a kusov do skladu,  na zaciatku zistime 
ci je miesto volne o danej velkosti a zistujeme dalej v cykle kolko ks sa zmesti do skladu. 
Ak sa najde volne miesto tak ho pripocitame k pocitadlu pre volne miesta a ak sa zhoduje s 
velkostou ovocia, tak do tychto miest zapiseme ovocie. Tiez pomocou glob.Pocitadla zapisujeme
ovocie aj do rolkaB a pamate(strukt.). Koncime funkcou na zapisanie id ovocia do skladu.
5. Piata funkcia najprv zistuje ci sa pozadovane ovocie nachadza v sklade, ak ano, ziskame 
miesto kde sa prve ovocie nachadza, v cykle, kt. sa opakuje az kym nenajdeme urceny pocet 
ov. alebo kym nevycerpame mnozstvo vyzadovaneho ov. Pomocou ziskanej hodnoty miesta v sklade 
skontrolujeme sklad a z daneho miesta ovocie vymazeme. Nasledne urcime dalsie ov. a z rolkaB 
vymazeme ten kus ovocia, ktory bol vybraty aj zo skladu. Pri kazdej takejto 
operacii(vyberani) pocitame pocet tychto ukonov, ktory aj funkcia vracia aby sme vedeli 
kolko ovocia sme vybrali.
6. Siesta funkcia ma dva cykly, z kt. jeden je vnoreny a v nich je podmienka podla kt. sa 
vypise id(zaplnene miesto) alebo „-“(prazdne miesto).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct OVOCIE 
{
  char meno[20]; // nazov ovocia
  int id; // id ovocia
  int prve; // prve ovocie 
  int posledne; // posledne ovocie 
} ovocie[100];

//deklaracie globalnych premennych
int n = 50, m = 20, dlzka_rolkaA = 0, m_b=0;
char rolkaA[10000] = {0};
int rolkaB[10000] = {0};
int **sklad;


int zisti_id(char *meno)
{
    int i, pocitadlo, id;
  	int dlzka_mena = strlen(meno); // dlzka ovocia
  	for (i = 1; i < 10000; i++) // prejdeme celu rolkaA
    {
      // nachadza sa na rolkaA  pismeno rovnake ako prve p. ov.?
      if (rolkaA[i] == meno[0])
        // je pred 1. a poslednym znakom nula(nul. znak)?
        if (rolkaA[i - 1] == 0 && rolkaA[dlzka_mena + dlzka_rolkaA] == 0)
      	{
            //po pismenkach zistujeme zhodu
        	for (pocitadlo = 0; pocitadlo < dlzka_mena; pocitadlo++)
              //ukoncenie cyklu ak sa nenajde zhoda
              if (rolkaA[i + pocitadlo] != meno[pocitadlo])
              	break;
              // nasla za zhoda, vypisem ID ovocia
              if (pocitadlo == dlzka_mena && rolkaA[i + pocitadlo] == 0)
              	return id = i;
         }
    }
  	pocitadlo=0;
    id = dlzka_rolkaA + 1; // id nastavime na hodnotu prvej nuly od zaciatku rolkyA
    //ovocie po pismenkach pridame to rolkyA
	for (i = dlzka_rolkaA + 1;i <= dlzka_rolkaA + dlzka_mena; i++)
           rolkaA[i] = meno[pocitadlo++];
    dlzka_rolkaA += dlzka_mena + 1;
  	rolkaA[dlzka_rolkaA + 1] = 0; //nulovy znak na koniec

    // nove ovocie sme pridali takze si ho musime ulozit v pamati(strukture)
    for (i=0;i<100;i++)
    {
    	if (ovocie[i].meno[0] == 0)  // najdeme prve volne miesto v pamati
     	{
       		strcpy(ovocie[i].meno,meno); // nakopirujeme meno
       		ovocie[i].id = id; // zapiseme ID
       		break;
     	}
    }
  	return id;
}

void novy_sklad(int n, int m)
{
    int i = 0, k = 0;
	//alokujeme dvojrozmerne pole velkosti n*m
  	sklad = (int**) calloc(n , sizeof(int*));
  	for (i = 0; i < n; i++)
    	sklad[i] = (int*) calloc(m , sizeof(int));
  
  	for (i = 0; i < 100; i++); // pamat(strukt.) nastavime na pociatocne hodnoty
  	{
    	ovocie[i].prve= -1;
    	ovocie[i].posledne = -1;
    	ovocie[i].id= -1;
  		for(k = 0; k < 20; k++) // kazdy char meno nastavime na 0
   			ovocie[i].meno[k] = 0;
  	}
  	for (i=0;i<10000;i++) //rolkuB nastavime na pociatocnu hodnotu
    	rolkaB[i] = -2;    
}

void vypis_id(int id)
{
    int poc = id;
  	printf("Nazov: ");
  	while(rolkaA[poc] != 0) // kym sa meno nekonci(nul. znakom) od pozicie ID++ tak
  	  printf("%c", rolkaA[poc++]); // vypisujeme jednotlive pismena a zvysime pocitadlo
  	printf(" id: %d \n", id);
}

int prijem_ovocia(char *meno, int ks, int velkost)
{
    // pomocou funkcie zisti_id zistim id ovocia
    int i, j, k, l, kus_navrat = 0, volne_miesto, id = zisti_id(meno);
    //opakujeme vo for cykle az kym nevlozime max pocet kusov
  	for (i = 0; i < ks; i++)
  	{
   		l = 0; // pocitadlo na pocet riadkov
   		if(velkost > m) //nemozeme pridat ov. ak je sa uz nezmesti a je sirsie ako riadok
     		break;
    	while(l < n) // while cyklus pokial sme v riadkoch
    	{
      		volne_miesto = 0;
      		for (j = 0; j < m; j++) // prechadzame riadok az do konca
      		{
                // volne_miesto zvacsime ak je sklad prazdny na danej pozicii
        		if(sklad[l][j] == 0)
          			volne_miesto++;
                // znova vynulujeme ak nie je prazdne
        		else volne_miesto = 0;
                //ak sme nasli dostatocny pocet volnych miest tak koncime cyklus
              	if (volne_miesto == velkost)
          			break;
      		}
    		if(volne_miesto == velkost)  //ak je najdene volne miesto
    		{
      			for(k = 0; k <= m_b; k += 4)  // pozicia v rolkaB s identickym ID
                    ///moze sa tu nachadzat -2 pri vyberani
        			if(rolkaB[k + 1] != -2 && rolkaB[k + 2] != -2)
        				if(sklad[rolkaB[k + 1]][rolkaB[k + 2]] == id && rolkaB[k + 3] == -2)
        					rolkaB[k + 3] = m_b;
        		rolkaB[m_b] = velkost; //do rolkaB ulozime velkost(prve zo 4 dost. miest)

        		for(k = 0; k < 100; k++)
    			{
       			 	if(ovocie[k].id == id) //nachadza sa id v pamati(strukt.)?
        			{
         				if(ovocie[k].prve == -1) //ak je to prvy vyskyt
            				ovocie[k].prve = m_b;
                        //ulozime posledny vyskyt kedze je to posledne pridane ovocie
          				ovocie[k].posledne = m_b;
         				break;
        			}
                    //ak sa ovocie v pamati nenachadza tak si ho tam zapamatame
       				else if (ovocie[k].id == -1)
        			{
          				ovocie[k].id = id;
          				ovocie[k].prve = m_b;
          				ovocie[k].posledne=m_b;
          				strcpy(ovocie[k].meno,meno);
          				break;
           			}
      			}

     			rolkaB[m_b+1] = l; // v rolkaB nastavime pozicie
     			rolkaB[m_b+2] = j-velkost+1;
    			m_b+=4; //rolkaB posunieme na miesto pre dalsie ovocie (preto o 4)
     			for(k=j-velkost+1;k<j+1;k++)
       				sklad[l][k] = id; //zapiseme ID do skladu
    		}

     		if(volne_miesto == velkost)
       			break; //splnili sme to, potom koncime cyklus
    		else l++; //ak nesplnime podmienku ideme na dalsi riadok
    	}
    	kus_navrat++; //zvysime pocet kusov o 1 
    }
  return kus_navrat;
}

int vydaj_ovocia(char *meno, int ks, int velkost_aspon)
{
    int id = zisti_id(meno), i, j, k, l, pom, pocet=0; // zisti_id nam zisti id ovocia
  	for (i = 0; i < 100; i++) //pre prvy vyskyt zisteho ovocia prehladavame strukturu
    if(ovocie[i].id == id)
  	{	
    	l = ovocie[k].prve; //polohu ovocia si zapamatame ak je najdene
    	break;
  	}
    // ak je nenajdene(nie je v sklade) vratime nulu
    else return 0;
    // while cykl. po zvoleny pocet ks
  	while (pocet < ks)
  	{
        //splna najstarsie ovocie pozadovany rozmer(velkost)?
    	if(rolkaB[l] >= velkost_aspon)
    	{
            //ak splna odstranime ho zo skl.
      		for(i = 0; i <= rolkaB[l]; i++)
        		sklad[rolkaB[l + 1]][rolkaB[l + 2] + i] = -1;
      		pocet++; //pocet zvysime o jedna

            //najdeme koniec ovocia v rolkaB a zistime ci je tam dalsie
      		if(rolkaB[l + 3] != -1)
      		{
        		pom = l; //ak najdeme ovocie tak ulozime povod. miesto
        		l = rolkaB[l + 3]; //miesto nasl. ovocia ulozime nasledne

				//nastavime novu hodnotu 1. ks ovocia(najdeme 1. ks)
        		for(j = 0; j <= l - 4; j += 4)
          			if(rolkaB[j + 1] != -1 && rolkaB[j + 2] != -1)
          				if(sklad[rolkaB[j + 1]][rolkaB[j + 2]] == id)
          					if(sklad[rolkaB[pom + 1]][rolkaB[pom + 2]] == -1)
        					{
								//na 1. ks nastavime dalsie ov.
          						ovocie[k].prve = j;
          						break;
        					}

        		rolkaB[pom]= -1; //ov, kt. sme vybrali vymazeme z rolkaB
        		rolkaB[pom + 1] = -1;
        		rolkaB[pom + 2] = -1;
        		rolkaB[pom + 3] = -1;

        		for(j = l - 4; j >= 0; j -= 4) //najdeme posledny ks
          		if (rolkaB[j + 1] != -1 && rolkaB[j + 2] != -1)
          			if(sklad[rolkaB[j + 1]][rolkaB[j + 2]] == id)
        			{
          				ovocie[k].posledne = j;
          				break;
        			}
      			}
      			else
      			{
					//znova prejdeme rolku po hodnotu, z kt. sme vybrali
        			for (j = 0; j <= l; j += 4)
        			{
          				if (rolkaB[j + 1] != -1 && rolkaB[j + 2] != -1)
            				if (sklad[rolkaB[j + 1]][rolkaB[j + 2]] == id)
            					break;
						//nastavime pociatocne hodnoty znova
            			ovocie[k].posledne = -1;
          				ovocie[k].prve = -1;
        			}
       	 			break; //cyklus konci ak sa tu nenajde dalsie ov.
      			}		
    	}	
    	else//prehladavame dalej ak velkost nevyhovuje
      		if(rolkaB[l + 3] != -1)
      			l = rolkaB[l + 3];
      		else break; // cuklus konci ak nenajdeme dalsi
    }
	return pocet; 
}

void vypis_sklad()
{
  int i, j;
  for (i = 0; i < n; i++)
  {
    for(j = 0; j < m; j++)
  		{
		  //vypis skladu, ak je v sklade na [i][j] hodnota tak ju vypisem
    	  if (sklad[i][j] > 0 ) 
            printf("%d ",sklad[i][j]);
	      // ak tam nie je hodnota tak do skladu ulozim "-"
    	  else sklad[i][j]= '-'; 
    		printf("%c " ,sklad[i][j]); //a vypisem zvysne policka skladu
 		}
    printf("\n");//novy riadok
  }
}


int main()
{
  // sem napis svoje riesenie
  
  return 0;
  
  
  
  
  
  
  
  
  
  
  /* DEBUG
  int ks, velkost, i;
  char meno[50];
  novy_sklad(n, m);
  while(scanf("%s %d %d", meno, &ks, &velkost) > 0)
  {
    vypis_id(zisti_id(meno));
    prijem_ovocia(meno, ks, velkost);
  }
  printf("ROLKA A:");
  for(i = 0; i < dlzka_rolkaA; i++)
    printf("%c", rolkaA[i]);
  printf("\n");
  vypis_sklad();
  
  INPUT:
  mango 3 3
kiwi 2 6
mango 3 3
wiki 2 6
mamango 3 3
kiwi 2 6
namanngo 3 3
kiwi 2 6
mango 3 3
banan 2 6
jablko 3 3
hruska 2 6
  */

}