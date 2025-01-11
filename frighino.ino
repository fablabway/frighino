/*
  fablabway.com
  file:         frighino.ino
  project:      replace Ariston Hotpoint controller 
  description:  replace Ariston Hotpoint controller 
  author:       Mauro Rossolato
  licence:      Creative Commons BY-NC-ND
  when        who   what
  -----------------------------------
  19.05.2016  mr    creates

*/

// include
//#include <RTClib.h>

// pins assignment
#define MPCOMPRES  2
#define MPLUCEINT  4
#define MPFANFRZE  10
#define MPFANFRIG  11
#define MPBZALARM  8
#define MPLDALARM  7

// register
#define MRCONDENS 0					// allarme per temp condensatore critica
#define MRCOMPRES 1					// allarme per temp compressore critica
#define MRFRIGIDE 2					// superata temp soglia per frigo
#define MRFRIZEER 3					// superata temp soglia per freezer
#define MRTMRCOMP 4					// flag per timer del compressore (durata 3 min)

// literal kostants
#define MPGMID "FLW,2024 - frighino - replace Ariston Hotpoint controller"

// global vars
unsigned long wtmcompres;

// objects
//RTC_DS1307 RTC;

void setup() {
Serial.begin(9600);
}


void loop () {
	// leggo temp freezer
	// leggo temp frigidr
	// leggo temp compres
	// leggo temp condens
//----------------------------------------
	// imposto 
	if ( wtmcompres >= wstptmcompres ) {		// temp compressore maggiore di setpoint
		// superato livello temp compressore
		bitSet(wregone, MRCOMPRES);
//		bitClear(wregone, MRCOPRENA);		// disabilito compressore
	}
	else {
//		bitSet(wregone, MRCOPRENA);			// abilito compressore	
		bitClear(wregone, MRCOPRESS);
	}
//----------------------------------------
	if ( wtmcondens >= wstptmcondens ) { 	// temp condensatore maggiore di setpoint
		// superato livello temp condensatore
		bitSet(wregone, MRCONDENS);
//		bitClear(wregone, MRCOPRENA);		// disabilito compressore
	}
	else {
//		bitSet(wregone, MRCOPRENA);			// abilito compressore	
		bitClear(wregone, MRCONDENS);
	}
//----------------------------------------	
	if ( wtmfrigidr >= wstptmfrigidr ) { 
		// superato livello temp frigorifero
		bitSet (wregone,MRFRIGIDE); 
	else {
		bitClear (wregone,MRFRIGIDE); 
	}
	
	if ( wtmfreezer >= wstptmfreezer ) { 
		// superato livello temp freezer
		bitSet (wregone,MRFREEZER); 
	}
	else {
		bitClear (wregone,MRFRIGIDE); 		
	}
	if ( wdoorop == 1 ) { 
		// porta aperta
		bitSet (wregone,MRDOOROP); 
	}
	else {
		bitClear (wregone,MRDOOROP); 				
	}
//----------------------------------------
	if ( 
		(bitRead(wregone, MRCOMPRES) == 0x0 ) &&
		(bitRead(wregone, MRCONDENS) == 0x0 )  && 
		(bitRead(wregone, MRFREEZER) == 0x1 ) &&
		(bitRead(wregtwo, MRFREEZER) == 0x0 ) &&
		(bitRead(wregone, MRTMRCOMP) == 0x0 )			// timer compressore esaurito
		) {
		digitalWrite(MPCOMPRES, HIGH);
	}	
	else {
		digitalWrite(MPCOMPRES, LOW);	
//		wtmcompres = millis();		
	}
//----------------------------------------
	if ( (bitRead(wregone, MRDOOROP) == 0x1 ) ) {
		digitalWrite(MPLUCEINT, HIGH);
	}
	else {
		digitalWrite(MPLUCEINT, LOW);
	}
//----------------------------------------
	if ( (bitRead(wregone, MRFRIGIDE) == 0x1 ) ) {
		digitalWrite(MPFANFRZE, HIGH);
	}
	else {
		digitalWrite(MPFANFRZEfan , LOW);
	}
//----------------------------------------	
}
