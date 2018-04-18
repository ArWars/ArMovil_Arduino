//---------------------------------------------------------------------->>
// Nombre      : Proyecto.ino
// Descripción : Proyecto automatizado con la utilización de un Arduino Uno R3.
// Autores     : Ariel Troncoso, Jacinta Naipayan y Sebastian Navarrete
// Fecha       : [14/11/2017]
//----------------------------------------------------------------------<<

#include "ArMovil.h"

// Constructor y Destructor de la clase ArMovil
ArMovil::ArMovil() {}
ArMovil::~ArMovil() {}

// Constructor y Destructor de la clase ArBluetooth
ArBluetooth::ArBluetooth() {}
ArBluetooth::~ArBluetooth() {}

// Constructor y Destructor de la clase ArSonido
ArSonido::ArSonido() {}
ArSonido::~ArSonido() {}

// Constructor y Destructor de la clase ArDistanciaULTRA
ArDistanciaULTRA::ArDistanciaULTRA() {}
ArDistanciaULTRA::~ArDistanciaULTRA() {}

// Inicializaciones de ArMovil
ArMovil M;
// Inicialización de ArBluetooth
ArBluetooth B;
// Inicialización de ArSonido
ArSonido S;
// Inicialización de ArDistanciaULTRA
ArDistanciaULTRA U;

// Funciones ArMovil
void ArMovil::inicio() {
    M.configurarMotorA1(motorA1);
    M.configurarMotorA2(motorA2);
    M.configurarMotorB1(motorB1);
    M.configurarMotorB2(motorB2);
    pinMode(M.obtenerMotorA1(), OUTPUT);
    pinMode(M.obtenerMotorA2(), OUTPUT);
    pinMode(M.obtenerMotorB1(), OUTPUT);
    pinMode(M.obtenerMotorB2(), OUTPUT);
    aParar();
}

void ArMovil::loop() {
      
}
void ArMovil::aAdelante() {
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, HIGH);
}
void ArMovil::aAtras() {
    digitalWrite(motorB2, LOW);
    digitalWrite(motorB1, HIGH);
}
void ArMovil::aIzquierda() {
    digitalWrite(motorA2, LOW);
    digitalWrite(motorA1, HIGH);
    delay(200);
    digitalWrite(motorA1, LOW);
}
void ArMovil::aDerecha() {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    delay(200);
    digitalWrite(motorA2, LOW);
}
void ArMovil::aParar() {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);
}

void ArMovil::explorar() {
    if ( distancia <= 30 ) {
        //estado = 0;
    }
}

// Funciones ArBluetooth
void ArBluetooth::inicio() {
     miBT.begin(tiempoEspera);
     miBT.println("AT+NAME"+nombre);
     miBT.println("AT+PIN"+pin);
     miBT.println("AT+BAUD4");
     Serial.println("Esperando comandos AT ...");
     
     //pinMode( pinTX, OUTPUT );
     //pinMode( pinRX, INPUT );
}

void ArBluetooth::loop() {
    if (miBT.available()) { estado = (char)miBT.read(); Serial.write(estado); }
    else if ( Serial.available() ) { miBT.write(Serial.read()); }
    switch(estado) {
        case '0': // Adelante
            M.aAdelante();
            delay(velocidad);
            estado = 'N';
            break; 
        case '1': // Atras
            M.aAtras();
            delay(velocidad);
            estado = 'N';
            break;
        case '2': // Derecha
            M.aDerecha();
            estado = 'N';
            break;
        case '3': // Izquierda
            M.aIzquierda();
            estado = 'N';
            break;
        default: // Parar
            M.aParar();
            break;
    }
}


// Funciones ArSonido
void ArSonido::inicio() {
  pinMode(pinSonido, OUTPUT);
}
void ArSonido::loop() {
}

// Funciones ArDistanciaULTRA
void ArDistanciaULTRA::inicio() {
    pinMode(tPin, OUTPUT);
    pinMode(ePin, INPUT);
}
void ArDistanciaULTRA::loop() {
    if ( U.activo() ) {
      long duracion;
      digitalWrite(tPin, LOW);
      delayMicroseconds(2);
      digitalWrite(tPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(tPin, LOW);
      duracion = pulseIn(ePin, HIGH);
      distancia = (duracion/2) / 29.1;
     
      //Serial.print(distancia);
      //Serial.println(" cm");
      delay(500);
    }
}

// Funciones Estandares de Arduino
void setup() {
  Serial.begin(tiempoEspera);
  M.inicio(); // Inicia el Sistema de Motores
  B.inicio(); // Inicia el Modulo Bluetooth
  S.inicio(); // Inicia el Parlante
  U.inicio(); // Inicia el Sensor de Ultra Sonido
}

void loop() {
  M.loop(); // Ejecuta el Loop del Sistema de Motores
  B.loop(); // Ejecuta el Loop del Modulo Bluetooth
  S.loop(); // Ejecuta el Loop del Parlante
  U.loop(); // Ejecuta el Loop del Sensor de Ultra Sonido
}                                                                                                                                                                                                                                              
