#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <algorithm> // Para usar .remove 
#include <bitset>    // Para los estados del personaje

using namespace std;

/* JUEGOS POR TURNOS
Los 3 héroes se van a enfrentar  de manera aleatoria al mismo tiempo con los enemigos.
Hay que usar estrategias para ganar.
*/

// Enum ---------------------------------------------------------------------------------------------
enum Estados{
	ENVENENADO,
	VULNERADO,
	DEBILITADO,
	FUERZA,
	FORTALEZA,
	MUERTO,
	CANTIDAD_ESTADOS
};

// Superclase ----------------------------------------------------------------------------------------
class Personaje{
		
	public:
		string nombre;
		int id;
		int vida;
		int ataque;
		int defensa;
		bitset<5> estado {0b0000}; // Extremo derecho (0 = Evenenado)
		
		// Constructor
		Personaje(int i, string n, int v, int a, int d){
			id = i;
			nombre = n;
			vida = v;
			ataque = a;
			defensa = d;
		}
		
		static void mostrarAcciones(){
			cout<<"\n[1] Atacar"<<endl;
			cout<<"[2] Habilidad especial"<<endl;
			cout<<"[3] Ver estado"<<endl;
		}
		
		void mostrarEstado(){
			cout<<"[1] Envenenado: "<<estado.test(0)<<endl;
			cout<<"[2] Vulnerado: "<<estado.test(1)<<endl;
			cout<<"[3] Debilitado: "<<estado.test(2)<<endl;
			cout<<"[4] Fuerza: "<<estado.test(3)<<endl;
			cout<<"[5] Fortaleza: "<<estado.test(4)<<endl;
		}
		
		virtual void activarHabilidad(Personaje& p) = 0;
		
		// Sobrecargar cout
		friend ostream& operator <<(ostream& cout, const Personaje& p){
			cout<<"\t\t\t.:"<<p.nombre<<":."<<endl;
			cout<<"Vida Base: "<<p.vida<<endl;
			cout<<"Ataque Base: "<<p.ataque<<endl;
			cout<<"Defensa Base: "<<p.defensa;
			return cout;
		}
		
};

// Prototipo de funciones--------------------------------------------------------------------------------
int menu();
int elejirEnemigo();
bool vidaHeroes();

void iniciarJuego();
void reestablecerEstadisticas();
void editarIndices();
void infoGeneral(int);
void combate();
void atacar(Personaje&, int);
void debuff(Personaje&, int);
void quitarDebuff(Personaje&);
void verificarVeneno(Personaje&, Personaje&, Personaje&);
void detalleHeroes();
void detalleEnemigos();


// HÉROES------------------------------------------------------------------------------------------------
class Arquero : public Personaje{
	
	public:
		Arquero(int i, string n, int v, int a, int d) : Personaje(i,n,v,a,d){ }
		
		void activarHabilidad(Personaje& p){
			p.ataque += 3;
			cout<<"\n"<<p.nombre<<" gano 3 puntos de ataque extra"<<endl;
		}
	
	
};

class Sacerdote : public Personaje{
	public:
		Sacerdote(int i, string n, int v, int a, int d) : Personaje(i,n,v,a,d){ }
		
		void activarHabilidad(Personaje& p){
			quitarDebuff(p);
			p.vida += 15;
			cout<<"\n"<<p.nombre<<" fue removido de todos los debuffs y se gano 15 de vida extra"<<endl;
		}
};

class Escudero : public Personaje{
	public:
		Escudero(int i, string n, int v, int a, int d) : Personaje(i,n,v,a,d){ }
		
		void activarHabilidad(Personaje& p){
			p.defensa += 3;
			cout<<"\n"<<p.nombre<<" gano 3 puntos de defensa extra"<<endl;
		}
};

// ENEMIGO----------------------------------------------------------------------------------------------

class DemonKing : public Personaje{
	public:
		DemonKing(int i, string n, int v, int a, int d) : Personaje(i,n,v,a,d){ }
		
		void activarHabilidad(Personaje& p){
		}
};


// Variables Globales---------------------------------------------------------------------------------------
bool flag = true;
Arquero arq(1, "ARQUERO", 50, 25, 10);
Sacerdote sac(2, "SACERDOTE", 60, 20, 10);
Escudero esc(3, "ESCUDERO", 80, 15, 15);
vector<Personaje*> heroes;
DemonKing dem(99, "DEMONG KING", 150, 20, 10);


int main(){
	
	do{
		system("cls");
		
		reestablecerEstadisticas();
		
		switch(menu()){
			case 1: iniciarJuego(); break;
			case 2: detalleHeroes(); break;
			case 3: detalleEnemigos(); break;
		}
		system("cls");
	}while(flag);
	
	system("pause");
	return 0;
}

void reestablecerEstadisticas(){
	arq.id = 1; arq.vida = 50; arq.ataque = 25; arq.defensa = 10;
	sac.id = 2; sac.vida = 60; sac.ataque = 20; sac.defensa = 10;
	esc.id = 3; esc.vida = 80; esc.ataque = 15; esc.defensa = 15;
	dem.vida = 150; dem.ataque = 20; dem.defensa = 10;
}

int menu(){
		int op;
		
		
		
		cout<<"======================================================"<<endl;
		cout<<"\t.:BIENVENIDO AL REINO DE LAS SOMBRAS:."<<endl;
		cout<<"======================================================"<<endl;
		cout<<"Juego por turnos, usa la mejor estrategia para ganar!"<<endl;
		cout<<"\n[1] Iniciar Juego"<<endl;
		cout<<"[2] Mostrar detalle de los heroes"<<endl;
		cout<<"[3] Mostrar detalle del enemigo"<<endl;
		cout<<"[4] Salir"<<endl;
		cout<<"\nIngrese una opcion: "; cin>>op;
		
		if(op == 4) flag = false;
		
		system("cls");
		
		return op;
}

void iniciarJuego(){
	
	combate();
	
	system("pause");
}

void detalleHeroes(){
	cout<<"------------------------------------------------------------------"<<endl;
	cout<<arq<<endl;
	cout<<"Habilidad: Otorga +3 puntos de ataque"<<endl;
	cout<<"------------------------------------------------------------------"<<endl;
	cout<<sac<<endl;
	cout<<"Habilidad: Remueve todos los debuffs y otorga +15 de vida"<<endl;
	cout<<"------------------------------------------------------------------"<<endl;
	cout<<esc<<endl;
	cout<<"Habilidad: Otorga +3 puntos de defensa"<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	system("pause");
}

void detalleEnemigos(){
	cout<<"------------------------------------------------------------------"<<endl;
	cout<<dem<<endl;
	cout<<"\nHabilidades"<<endl;
	cout<<"- Envenenar: 5 de puntos de dolor al final de cada turno"<<endl;
	cout<<"- Vulnerar: Reduce en 5 puntos la defensa"<<endl;
	cout<<"- Debilitar: Reduce en 5 puntos el ataque"<<endl;
	cout<<"------------------------------------------------------------------"<<endl;
	system("pause");
}


void combate(){
	
	heroes.clear();
	
	heroes.push_back(&arq);
	heroes.push_back(&sac);
	heroes.push_back(&esc);
	
	// El enemigo tendrá todos los turnos pares
	int turno = 1;
	int turnos_R = 60;
	int acc;
	int aux = 0;
	bool inner_flag = true;
	
	srand(time(NULL));
	
	do{
		
		infoGeneral(turnos_R);
		
		
		if((turno%2) == 0){
			aux = 0;
			cout<<"\nTurno "<<turno<<": "<<dem.nombre<<endl;
			// Numeros aleatorios
			int al1 = rand() % heroes.size(); // Escoger uno de los 3 heroes 
			double al2 = (double)rand() / RAND_MAX; // Atacar (60%) o aplicar Debuff (40%)
			int al3 = rand() % 3; // Escoger uno de los 3 debuff 
			
			if(al2 <= 0.60) atacar(*heroes[al1], turno);
			else debuff(*heroes[al1], al3);
			
			
		} else{	
			int alH = rand() % heroes.size(); // Escoge uno de los 3 heroes aleatoriamente
			int index;
			if(aux==0){
				index = alH;
				cout<<endl;
				verificarVeneno(arq, sac, esc);
			} 
			
			cout<<"\nTurno "<<turno<<": "<<(heroes[index])->nombre<<endl;;
			Personaje::mostrarAcciones();
			cout<<"\nEscoga una accion: "; cin>>acc;
			
			switch(acc){
				case 1: atacar(*heroes[index], turno); break;
				case 2: 
					int x;
					cout<<"\nSeleccione un heroe: "; cin>>x;
					(heroes[index])->activarHabilidad(*heroes[x-1]); 
					break;
				case 3: 
					cout<<"\n(0) Desactivado | (1) Activado"<<endl;
					(heroes[index])->mostrarEstado(); 
					turno--; // No se contara como turno ver el detalle
					turnos_R++;
					aux++;
					break;
				default: cout<<"\nValor fuera de rango"<<endl; turno--; break;
			}
			
			
		}
		
		turno++;
		turnos_R--;
		
		if(vidaHeroes() || (turnos_R == 0)){
			inner_flag = false;
			system("cls");
			cout<<"\t\t\t\t============================================="<<endl;
			cout<<"\t\t\t\t\t\t.:GAME OVER:."<<endl;
			cout<<"\t\t\t\t El Rey Demonio arraso con toda la humanidad"<<endl;
			cout<<"\t\t\t\t============================================="<<endl;
		} 
		
		if(dem.vida <= 0){
			inner_flag = false;
			system("cls");
			cout<<"\t\t\t\t==============================================="<<endl;
			cout<<"\t\t\t\t\t     .:VICTORIA MAGISTRAL:."<<endl;
			cout<<"\t\t\t\t Salvaste a la humanidad del peligro inminente"<<endl;
			cout<<"\t\t\t\t==============================================="<<endl;
		}
		
		cout<<"\n"<<endl;
		system("pause");
		system("cls");
		
	}while(inner_flag);
	
	
}

void infoGeneral(int turnos_R){
	cout<<"==================================================="<<endl;
	cout<<"\t.:HAZ DESAFIADO A "<<dem.nombre<<":."<<endl;
	cout<<"     | Vida: "<<dem.vida<<" | Ataque: "<<dem.ataque<<" | Defensa: "<<dem.defensa<<" |"<<endl;
	cout<<"==================================================="<<endl;	
	cout<<"Turnos Restantes: "<<turnos_R<<endl;
	cout<<"====================="<<endl;
	cout<<"\n["<<arq.id<<"] Arquero:   | Vida: "<<arq.vida<<" | Ataque: "<<arq.ataque<<" | Defensa: "<<arq.defensa<<" |"<<endl;
	cout<<"["<<sac.id<<"] Sacerdote: | Vida: "<<sac.vida<<" | Ataque: "<<sac.ataque<<" | Defensa: "<<sac.defensa<<" |"<<endl;
	cout<<"["<<esc.id<<"] Escudero:  | Vida: "<<esc.vida<<" | Ataque: "<<esc.ataque<<" | Defensa: "<<esc.defensa<<" |"<<endl;
}

void atacar(Personaje& he, int turno){
	int dolor;
	
	if((turno % 2) == 0){
		dolor = dem.ataque-he.defensa;
		he.vida -= dolor;
		cout<<"\n"<<dem.nombre<<" infligio "<<dolor<<" puntos de ataque a "<<he.nombre<<endl;
		
		if(he.vida == 0) he.vida = -1;
		
	} else{ 
		dolor = he.ataque-dem.defensa;
		dem.vida -= dolor;
		cout<<"\n"<<he.nombre<<" infligio "<<dolor<<" puntos de ataque a "<<dem.nombre<<endl;
	}
	cout<<"\n"<<endl;
	
}

void debuff(Personaje& he, int al3){
	string debuffs[] = {"Veneno", "Vulnerabilidad", "Debilidad"};
	
	cout<<"\n"<<dem.nombre<<" aplico debuff de "<<debuffs[al3]<<" a "<<he.nombre<<"\n"<<endl;
	
	he.estado.set(al3);
	
	switch(al3){
		case 0: break;
		case 1: he.defensa -= 5; break;
		case 2: he.ataque -= 5; break;
	}
		
}


void verificarVeneno(Personaje& arq, Personaje& sac, Personaje& esc){
	
	if(arq.estado[0] && arq.vida > 0){
		arq.vida -= 5;
		cout<<"- Arquero recibio 5 de dolor por veneno"<<endl;
	} 
	if(sac.estado[0] && sac.vida > 0){
		sac.vida -= 5;	
		cout<<"- Sacerdote recibio 5 de dolor por veneno"<<endl;
	} 
	if(esc.estado[0] && esc.vida > 0){
		esc.vida -= 5;
		cout<<"- Escudero recibio 5 de dolor por veneno"<<endl;
	}
}

bool vidaHeroes(){
	
	if(arq.vida<0){
		arq.vida = 0;
		arq.id = 0;
		heroes.erase(find(heroes.begin(), heroes.end(), &arq));
		editarIndices();
		cout<<"\nArquero ha perdido la vida en combate"<<endl;
		
	}
	
	if(sac.vida < 0){
		sac.vida = 0;
		sac.id = 0;
		heroes.erase(find(heroes.begin(), heroes.end(), &sac));
		editarIndices();
		cout<<"\nSacerdote ha perdido la vida en combate"<<endl;
	}
	
	if(esc.vida < 0){
		esc.vida = 0;
		esc.id = 0;
		heroes.erase(find(heroes.begin(), heroes.end(), &esc));
		editarIndices();
		cout<<"\nEscudero ha perdido la vida en combate"<<endl;
	}
	
	return (arq.vida<=0) && (sac.vida<=0) && (esc.vida<=0);
}

void quitarDebuff(Personaje& p){
	constexpr bitset<5> mask0 {0b1'1000};
	p.estado &= mask0;
	
	if(typeid(p) == typeid(Arquero)){
		if(p.ataque < 25) p.ataque = 25;
		if(p.defensa < 10) p.defensa = 10;
	}
	if(typeid(p) == typeid(Sacerdote)){
		if(p.ataque < 20) p.ataque = 20;
		if(p.defensa < 10) p.defensa = 10;
	}
	if(typeid(p) == typeid(Escudero)){
		if(p.ataque < 15) p.ataque = 15;
		if(p.defensa < 15) p.defensa = 15;
	}
}

void editarIndices(){	
	// GRACIAS GEMINI, me salvaste de hacer 40 lineas de código en esta función
    for (int i = 0; i < heroes.size(); i++) {
        heroes[i]->id = i + 1; 
    }
}

    
