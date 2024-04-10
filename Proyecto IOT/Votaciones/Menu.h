#ifndef Menu_h
#define Menu_h

//#include <LiquidCrystal_I2C.h>
#define pinup 16
#define pindown 17
#define pinleft 34
#define pinright 35
#define pinaccept 32
#define pincancel 12
#define buzzer 14

#define MAX_VOTOS 10

//initialize the library
//LiquidCrystal_I2C lcd(0x20,16,2);
struct Voto {
    String tipoCandidatura;
    String nombrePartido;
    String nombreCandidato;
};
class Menu {
  public:
    String nombrePartido;
    String tipoCandidatura;
    String nombreCandidato;

    String nombresTemp[3];

    int stateup = LOW,
        statedown = LOW,
        stateleft = LOW,
        stateright = LOW,
        stateaccept = LOW,
        statecancel=LOW;
    int option = 0, category = 0;
    char* menu[3][4];

  Voto votos[MAX_VOTOS]; // Array para almacenar los votos
    int numVotos = 0;      // Contador de votos

  public:
    void initMenu ( void );
    void menuActions ( void );
    void sound(int frequency); 
    void accept ( void );
    void agregarVoto(String tipoCandidatura, String nombrePartido, String nombreCandidato);
    void cancelarVotos();
};

void Menu :: initMenu ( void ) {
  //delcare the category and options for the menu
  menu[0][0] = "Presidencia";
  menu[1][0] = "Gobernatura";
  menu[2][0] = "Municipal";

  menu[0][1] = "PUP: Julieta Miramontes";
  menu[0][2] = "PFN: Maximiliano Ortiz";
  menu[0][3] = "PPC: Hiromi Mayoral";

  menu[1][1] = "PUP: Axel Mora";
  menu[1][2] = "PFN: Lina Diaz";
  menu[1][3] = "PPC: Victor Barboza ";

  menu[2][1] = "PUP: Federico Aguilar";
  menu[2][2] = "PFN: Teodoro Brambilia";
  menu[2][3] = "PPC: Gabriela Gallardo";


  //declare the pin mode
  //pinMode(buzzer, OUTPUT);
  pinMode(pinup, INPUT);
  pinMode(pindown, INPUT);
  pinMode(pinleft, INPUT);
  pinMode(pinright, INPUT);
  pinMode(pinaccept, INPUT);
  pinMode(pincancel, INPUT);
  
  //initialize the lcd
  ACT.lcd_init();
  //turn on the backlight
  //lcd.backlight();
  //write "menu"
  lcd.setCursor(0,0);
  lcd.print("Menu ");
  //display the custom icons
  //byte customone[] = {B10001,B01110,B01110,B10101,B01110,B01110,B01010,B01010};
  //byte customtwo[] = {B10001,B01110,B01110,B10101,B00100,B00100,B10101,B01110};
  //byte customthree[] = {B00100,B01110,B00100,B01110,B10101,B11111,B01110,B00100};
byte customone[] = {
  B01110,
  B10001,
  B10001,
  B10101,
  B10001,
  B10001,
  B01010,
  B00100
};

byte customtwo[] = {
  B10101,
  B10101,
  B11111,
  B01110,
  B00100,
  B00100,
  B00100,
  B00100
};

byte customthree[8] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B11111,
  B01110,
  B00100,
  B00100
};




  lcd.write(byte(0));
  lcd.write(byte(1));
  lcd.write(byte(2));
  lcd.createChar(0, customone);
  lcd.createChar(1, customtwo);
  lcd.createChar(2, customthree);
}



void Menu::sound(int frequency) {
  tone(buzzer, frequency);
  delay(100); // Ajusta este tiempo según lo que necesites para el sonido
  noTone(buzzer);
  delay(100);
}

void Menu::agregarVoto(String tipoCandidatura, String nombrePartido, String nombreCandidato) {
    if (numVotos < MAX_VOTOS) {
        votos[numVotos++] = {tipoCandidatura, nombrePartido, nombreCandidato};
    }
    // Aquí podrías añadir código para manejar el caso de que el array esté lleno
}

void Menu::cancelarVotos() {

    numVotos = 0;  // Simplemente resetea el contador de votos
    
}
void Menu :: menuActions ( void ) {
  //declare the state for buttons
  stateup = digitalRead(pinup);
  statedown = digitalRead(pindown);
  stateleft = digitalRead(pinleft);
  stateright = digitalRead(pinright);
  stateaccept = digitalRead(pinaccept);
  statecancel = digitalRead(pincancel);

  
  //right and left direction
  
  if(stateright == HIGH) {
    option = 1;
    sound(300);
  } else if (stateleft == HIGH) {
  	option = 0;
    sound(300);
  }
    //Si no jala borrar la condicion de abajo y descomentar esto
 /* 
    if(stateleft == HIGH ) {
   	 option--;
     sound(300);
  	} else if (stateright == HIGH  ) {
  	 option++;
     sound(300);
  	} 
   */

  //up and down direction for the options
  if(stateup == HIGH && option != 0 && option != 1) {
   	 option--;
     sound(900);
  	} else if (statedown == HIGH && option != 0 && option < 3) {
  	 option++;
     sound(900);
  	} 
    
    //up and down direction for the categories
    if(stateup == HIGH && option == 0 && category > 0) {
   	 category--;
     sound(900);
  	} else if (statedown == HIGH && option == 0 && category < 2) {
  	 category++;
     sound(900);
  	}

    /*if(stateup == HIGH && option == 0 && candidato > 0) {
   	 candidato--;
     sound(900);
  	} else if (statedown == HIGH && option == 0 && candidato < 2) {
  	 candidato++;
     sound(900);
  	}*/
  //print the current position in the menu
  //lcd.setCursor(0,1);

  ACT.imprimir(menu[category][option], 1);
      
      if(stateaccept == HIGH){   
      sound(700);       


      if (category == 0) {
      tipoCandidatura = "Presidencia";

      nombreCandidato = menu[category][option];
      nombreCandidato.remove(0,5);
      //Esto cambiaria si se logra añadir una tercer categoria
            if (option == 1) {
        nombrePartido = "PUP";
      } else if (option == 2) {
        nombrePartido = "PFN";
      } else if (option == 3) {
        nombrePartido = "PPC";
      }
      


    } else if (category == 1) {
      tipoCandidatura = "Gobernatura";
      nombreCandidato = menu[category][option];
      nombreCandidato.remove(0,5);
      //Esto cambiaria si se logra añadir una tercer categoria
            if (option == 1) {
        nombrePartido = "PUP";
      } else if (option == 2) {
        nombrePartido = "PFN";
      } else if (option == 3) {
        nombrePartido = "PPC";
      }


    } else if (category == 2) {
      tipoCandidatura = "Municipal";
      nombreCandidato = menu[category][option];
      nombreCandidato.remove(0,5);
      //Esto cambiaria si se logra añadir una tercer categoria
            if (option == 1) {
        nombrePartido = "PUP";
      } else if (option == 2) {
        nombrePartido = "PFN";
      } else if (option == 3) {
        nombrePartido = "PPC";
      }
    }      
      bool yaVotado = false;
    for (int i = 0; i < numVotos; i++) {
      if (votos[i].tipoCandidatura == tipoCandidatura) {
        yaVotado = true;
        break;
      }
    }

    if (!yaVotado) {
      myrtc.get_time();
      myrtc.format_time();
      agregarVoto(tipoCandidatura, nombrePartido, nombreCandidato);
    } else {
      // Mensaje o acción para indicar que ya se votó por esa candidatura
      ACT.imprimir("Voto Repetido", 2);
      delay(2000);
    }
  }

  if(statecancel == HIGH) {
    cancelarVotos();
    }
}


#endif