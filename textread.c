#include<stdio.h>
#include<ctype.h>
#include "textread.h"

int textread(char* filename, double werte[],int n ){
    
    int i=0,Anzahl=0,hilf,merk='\n';
    char c;
    
    FILE *name;
    name=fopen(filename,"r");              /*Datei oeffnen */
    if(name!=NULL){ 
      for(i=0;i<n;i++){
	while (((c=fgetc(name))!=EOF) &&(c!='=')&&(c!='*'))
	  /*Merke mir das vorherige Zeichen*/
	  merk=c;
	
	/*Komentar beginnend mit '*' wird ueberlesen*/
	if(c=='*'){
	  --i;
	  if(merk=='\n')
	  while((c=fgetc(name))!='\n')
	    ;
	}
	
	/*Werte einlesen */
	else if((c=='=')){
	  if(fscanf(name,"%lg",&werte[i])==0)
	    --i;
	  else
	    Anzahl++;
	}
	/*Ende der Datei*/
	else 
	  break;
      }
      hilf=Anzahl;
      fclose(name);
    }
    else
      hilf=(-1);                              
    return(hilf);
}






