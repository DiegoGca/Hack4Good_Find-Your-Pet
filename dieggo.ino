#include <SoftwareSerial.h>
SoftwareSerial BTSerial(4, 5); // RX | TX

#define BARK "bark"
#define NOBARK "nobark"
// #define LEDPIN  27  // numero del pin debe ser un int¿?

char character;
String mensaje;

bool blink = 0;     // estado parpadear
int ledState = LOW; // cambiar parpadeo

/////////////
// TIEMPO //
///////////
unsigned long previousMillis = 0;     // will store last time LED was updated
const long interval = 200;           // interval at which to blink (milliseconds)
const int ledPin =  7;



void setup() {
  BTSerial.begin(9600); 
  // pines leds
  pinMode(ledPin,OUTPUT);
  //Serial.begin(9600);
  
}

void loop() {

  
  while(BTSerial.available()){
    // TODO serial1 ¿?
    if ('\n' != (character = (char) Serial.read())){
      mensaje.concat(character);
      
      if( mensaje.equals("OK+CONN") ){
        // se ha hecho conexion

        mensaje = "";
      } else if (mensaje.equals("OK+LOST") ){  // ESTADO ?
        // se ha perdido la conexion -> luces on
        // blik();

        
        mensaje = "";
      } else if ( mensaje.equals("OK+CLEAR") ){
        // ?
        
        mensaje = "";
      } else if ( mensaje.equals(BARK) ){
        // desde la app se pide encender las luces
        blik();

        mensaje = "";
      } else if (mensaje.equals(NOBARK) ){
        // parar el parpadeo:
        digitalWrite(ledPin, LOW);

        mensaje = "";
      }
    }

  } // while bt available
} // end loop


void blik(){

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }
}
