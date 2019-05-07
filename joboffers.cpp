#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>

#define MAX 1000
#define parne ((i+1)%2 == 0)
#define neparne ((i+1)%2 != 0)
#define ANO ( c == 'a' || c == 'A' )
#define NIE ( c == 'n' || c == 'N' )


typedef struct 
{
	char *mesto;
	char *okres;
	char *PSC;
	char *ulica_cislo;
} ADRESA_FY;


typedef struct
{
	char *email;
	char *mobil;
} KONTAKT_FY;


typedef struct ponuka 
{
	char *lokalita;
	char *nazov_fy;
	ADRESA_FY adresa_fy;
	char *nastup;
	char *plat;
	KONTAKT_FY kontakt_fy;
	char *posobenie;
} PONUKA;


PONUKA *zoznam[MAX];


int pocet = 0;


void free_pamet( void )
{
	int i;

	for( i = 0; i < pocet; i++ )
	{ 
		free( zoznam[i]->lokalita ); 
		free( zoznam[i]->nazov_fy ); 
		free( zoznam[i]->adresa_fy.mesto ); 
		free( zoznam[i]->adresa_fy.okres ); 
		free( zoznam[i]->adresa_fy.PSC ); 
		free( zoznam[i]->adresa_fy.ulica_cislo );
		free( zoznam[i]->nastup );
		free( zoznam[i]->plat );
		free( zoznam[i]->kontakt_fy.email );
		free( zoznam[i]->kontakt_fy.mobil );
		free( zoznam[i]->posobenie );
		free( zoznam[i] );
	}

pocet = 0;

} 


char flush( void ) 
{ 
	char key; 

	do {
	} while(( key = getchar() ) == '\n' ); 

	return( key );
} 


int menu() 
{ 

	int volba; 
	
	system( "cls" );

	printf( "\n-----------[ EVIDENCIA PRACOVNYCH PONUK (JobOffers) ]-----------\n\n" );
	printf( "\n1. Pridat pracovnu ponuku" );
	printf( "\n2. Odstranit pracovnu ponuku\n" );
	printf( "\n3. Usporiadat podla lokality" ); 
	printf( "\n4. Usporiadat podla hlavnej oblasti posobenia\n" );
	printf( "\n5. Nacitat zoznam zo suboru" );
	printf( "\n6. Ulozit zoznam do suboru\n" );
	printf( "\n7. Vypisat zoznam pracovnych ponuk" );
	printf( "\n8. Vymazat cely zoznam\n" );
	printf( "\n9. Ukoncit program " ); 
	printf( "\n\n\n--------------------------------------------------------------\n" );
	printf( "Pocet zaznamov: %d", pocet );
	printf( "\n--------------------------------------------------------------\n" );
	printf( "Zadajte pozadovanu akciu> " ); 
	
	volba = getchar();
	
	return( volba );

} 


char *citat_ret() 
{ 
	char pom[1000] = "", ch, *ret; 
	int index = 1; 

	pom[0] = flush(); 

	do { 
		ch = getc( stdin );

		if( ch != '\n' ) pom[index] = ch; 
		else pom[index] = '\0'; 
		
		index++; 
		
	} while( ch != '\n' );

	ret = (char *) malloc( strlen( pom ) + 1 ); 
	strcpy( ret, pom ); 

	return( ret ); 
} 


char *fziskat_ret( FILE *subor ) 
{ 
	char pom[1000], ch, *ret; 
	int i = 0; 

	do { 
		ch = fgetc( subor ); 
		pom[i] = ch; 
		i++; 
		} while( ch != '\n' ); 

	pom[i-1] = '\0'; 
	
	ret = (char *) malloc( strlen( pom ) + 1 ); 
	strcpy( ret, pom ); 

	return( ret ); 
} 


void sort_lokalita( void ) 
{ 
	int i, j; 

	PONUKA *pom;

	for( i = 0; i < pocet; i++ )
	{ 
		for( j = 0; j < pocet-1; j++ ) 
		{
			if( strcmp( zoznam[j]->lokalita , zoznam[j+1]->lokalita ) > 0 )
			{ 

				pom = zoznam[j]; 
				zoznam[j] = zoznam[j+1]; 
				zoznam[j+1] = pom; 

			}
		}
	}

	system( "cls" );

	printf( "\nZoznam je usporiadany podla lokality...\n" );
	printf( "---------------------------------------------\n" );
	printf( "(Stlac lubovolny klaves)\n" );

	getch();
}


void sort_hop( void ) 
{ 
	int i, j; 

	PONUKA *pom;

	for( i = 0; i < pocet; i++ )
	{ 
		for( j = 0; j < pocet-1; j++ ) 
		{
			if( strcmp( zoznam[j]->posobenie ,  zoznam[j+1]->posobenie ) > 0 )
			{ 

				pom = zoznam[j]; 
				zoznam[j] = zoznam[j+1]; 
				zoznam[j+1] = pom; 

			}
		}
	}

	system( "cls" );

	printf( "\nZoznam je usporiadany podla hlavnej oblasti posobenia...\n" );
	printf( "--------------------------------------------------------------\n" );
	printf( "(Stlac lubovolny klaves)\n" );

	getch();
}


void pridat( void )
{ 
	PONUKA *p; 

	p = ( PONUKA * ) malloc( sizeof( PONUKA ) ); 

	printf( "\nPridanie novej pracovnej ponuky:\n" );
	printf( "---------------------------------------------\n" );

	printf( "\nZadajte lokalitu: " ); p->lokalita = citat_ret(); 

	printf( "\nZadajte nazov firmy: " ); p->nazov_fy = citat_ret(); 

	printf( "\nZadajte adresu firmy:\n" ); 
	printf( "\nUlica/cislo: " ); p->adresa_fy.ulica_cislo = citat_ret();
	
	printf( "\nPSC: " ); p->adresa_fy.PSC = citat_ret();

	printf( "\nMesto: " ); p->adresa_fy.mesto = citat_ret(); 
	
	printf( "\nOkres: " ); p->adresa_fy.okres = citat_ret(); 

	printf( "\nZadajte termin nastupu: " ); p->nastup = citat_ret(); 

	printf( "\nZadajte ponukany plat: " ); p->plat = citat_ret(); 

	printf( "\nZadajte kontakt na firmu:\n" );
	printf( "\nZadajte mobil: " ); p->kontakt_fy.mobil = citat_ret();
	
	printf( "\nZadajte e-mail: " ); p->kontakt_fy.email = citat_ret(); 
	
	printf( "\nZadajte hlavne posobenie firmy: " ); p->posobenie = citat_ret();

	zoznam[pocet] = p; 

	pocet++; 
} 


void odstranit( int id ) 
{ 
	int i; 

	if( id > 0 && id <= pocet )
	{ 
		free( zoznam[id-1]->lokalita ); 
		free( zoznam[id-1]->nazov_fy ); 
		free( zoznam[id-1]->adresa_fy.mesto ); 
		free( zoznam[id-1]->adresa_fy.okres ); 
		free( zoznam[id-1]->adresa_fy.PSC );
		free( zoznam[id-1]->adresa_fy.ulica_cislo );
		free( zoznam[id-1]->nastup );
		free( zoznam[id-1]->plat );
		free( zoznam[id-1]->kontakt_fy.email );
		free( zoznam[id-1]->kontakt_fy.mobil );
		free( zoznam[id-1]->posobenie );

	for( i = id; i < pocet; i++) 
		zoznam[i-1] = zoznam[i]; 
		pocet--; 
	} 
} 


void odstranit_all( void )
{
	int c;

	for( ; ; )
	{
		system( "cls" );

		printf( "\nSkutocne chcete odstranit cely zoznam ? [A/N] " );
		
		c = getchar();

		if( ANO )
		{ 
			free_pamet();
			break;

		}
		else if( NIE ) break; 
		else continue;
	}
} 


void ulozit( const char *nazov ) 
{ 
	FILE *subor; 
	
	int i; 

	if( ( subor = fopen( nazov, "wb" ) ) != NULL )
	{ 
		fprintf( subor, "%d\n", pocet ); 
		
		for( i = 0; i < pocet; i++ )
		{ 
			fprintf( subor, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", 
			zoznam[i]->lokalita,
			zoznam[i]->nazov_fy, 
			zoznam[i]->adresa_fy.mesto, 
			zoznam[i]->adresa_fy.okres, 
			zoznam[i]->adresa_fy.PSC, 
			zoznam[i]->adresa_fy.ulica_cislo,
			zoznam[i]->nastup, zoznam[i]->plat,
			zoznam[i]->kontakt_fy.email,
			zoznam[i]->kontakt_fy.mobil,
			zoznam[i]->posobenie ); 
		}
	}
    
    fclose(subor); 

} 
 

void nacitat( const char *nazov ) 
{ 
	int i; 

	free_pamet();

	PONUKA *p;

	FILE *subor; 

	if( ( subor = fopen( nazov, "rb" ) ) != NULL )	
	{ 
		//void free_pamat(); 

		fscanf( subor, "%d\n", &pocet);

		for( i = 0; i < pocet; i++ )
		{ 
			p = ( PONUKA* ) malloc( sizeof( PONUKA ) ); 
		
			p->lokalita = fziskat_ret( subor ); 
			p->nazov_fy = fziskat_ret( subor ); 
			p->adresa_fy.mesto = fziskat_ret( subor ); 
			p->adresa_fy.okres = fziskat_ret( subor ); 
			p->adresa_fy.PSC = fziskat_ret( subor ); 
			p->adresa_fy.ulica_cislo = fziskat_ret( subor );
			p->nastup = fziskat_ret( subor );
			p->plat = fziskat_ret( subor );
			p->kontakt_fy.email = fziskat_ret( subor );
			p->kontakt_fy.mobil = fziskat_ret( subor );
			p->posobenie = fziskat_ret( subor );
			
			zoznam[i] = p;
		}
	} 
} 


void vypis( void ) 
{ 
	int i; 

	printf( "\n-----------[ VYPIS EVIDENCIE PRACOVNYCH PONUK ]-----------\n" );                     

	for( i = 0; i < pocet; i++ )
	{			   
		printf( "\n---[Pracovna ponuka: #%d]----------------------------------\n", i + 1 ); 
		printf( "\nLokalita: %s", zoznam[i]->lokalita ); 
		printf( "\nFirma: %s", zoznam[i]->nazov_fy ); 
		printf( "\nAdresa firmy: %s, %s, %s, %s", zoznam[i]->adresa_fy.ulica_cislo, zoznam[i]->adresa_fy.PSC, zoznam[i]->adresa_fy.mesto, zoznam[i]->adresa_fy.okres );
		printf( "\nTermin nastupu: %s", zoznam[i]->nastup );
		printf( "\nPonukany plat: %s,- Sk\n", zoznam[i]->plat );
		printf( "\nKontakt:" );
		printf( "\nMobil: %s", zoznam[i]->kontakt_fy.mobil );
		printf( "\nE-mail: %s", zoznam[i]->kontakt_fy.email );
		printf( "\nHlavna oblast posobenia: %s", zoznam[i]->posobenie );
		printf( "\n----------------------------------------------------------\n\n" );

		if( parne )
		{
			if( (i+1) == pocet ) 
				printf( "\n---[koniec zoznamu]---------------------------------------\n\n" ); 
			
			printf( "\n(Stlacte klavesu pre pokracovanie...)" ); 
			getch();

			system( "cls" );

		} else if( neparne && ((i+1) == pocet) ) {

			printf( "\n---[koniec zoznamu]---------------------------------------\n\n" );

			printf( "\n(Stlacte klavesu pre pokracovanie...)" ); 
			getch();

			system( "cls" );
		}
	}
}


int main( void ) 
{ 
	int volba, id;
	
	char subor[50]; 


	while( ( volba = menu() ) != '9' )
	{

		system( "cls" );

		switch( volba )
		{ 

			case '1':	pridat(); 
						break; 

			case '2':	
						printf( "\nOdstranenie pracovnej ponuky:\n" );
						printf( "---------------------------------------------\n" );	
						printf( "\nZadajte ID pracovnej ponuky (pocet zaznamov: %d): ", pocet ); 
						scanf( "%d", &id ); 
						odstranit( id ); 
						break;

			case '3':	sort_lokalita(); 
						break;
			
			case '4':	sort_hop(); 
						break;

			case '5':	printf( "\nNacitanie suboru:\n" );
						printf( "---------------------------------------------\n" );	
						printf( "\nZadajte nazov suboru: " ); 
						scanf( "%s", subor ); 
						nacitat( subor ); 
						break; 

			case '6':	printf( "\nUlozenie suboru:\n" );
						printf( "---------------------------------------------\n" );	
						printf( "\nZadajte nazov suboru: " ); 
						scanf( "%s", subor ); 
						ulozit( subor ); 
						break; 
			
			case '7':	vypis(); 
						break;

			case '8':	odstranit_all(); 
						break;

		} 

	}

	free_pamet();  
  	
  return 0;
}
