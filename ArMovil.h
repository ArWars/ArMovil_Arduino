//---------------------------------------------------------------------->>
// Nombre      : ArMovil.h
// Descripción : Archivo de encabezamiento.
// Autores     : Ariel Troncoso, Jacinta Naipayan y Sebastian Navarrete
// Fecha       : [14/11/2017]
//----------------------------------------------------------------------<<

#include <SoftwareSerial.h>

// Configuración Global del Modulo ArMovil
#define DEBUG true
#define tiempoEspera 9600
#define pinSonido 8 // Sonido
#define pinSensor 9 // Sensor PI
char estado = 'N';
int velocidad = 1000;

// Definiciones para el sistema de Motores
int motorA1 = 3; // Motor Izquierda
int motorA2 = 2; // Motor Derecha
int motorB1 = 4; // Motor Atras
int motorB2 = 5; // Motor Adelante

// Definiciones para el ULTRA Sonido
#define ePin 10 // Echo
#define tPin 11 // Trigger
long distancia = 999;

// Inicialización del Modulo Bluetooth HC-06
#define pinRX 6
#define pinTX 7
String nombre = "ArMovil", pin = "9484";
SoftwareSerial miBT(pinRX, pinTX); // RX, TX
boolean estaConectado = false;

// ----------------------------------------------------------------------------
// Nombre      : ArMovil
// Descripción : Encabezamiento de ArMovil
// ----------------------------------------------------------------------------
class ArMovil
{
  private:
    int MOTOR_A1;
    int MOTOR_A2;
    int MOTOR_B1;
    int MOTOR_B2;
    
  public:
    ArMovil();
    virtual ~ArMovil();
    void inicio();
    void loop();
    
    int obtenerMotorA1() { return { MOTOR_A1 }; }
    int obtenerMotorA2() { return { MOTOR_A2 }; }
    int obtenerMotorB1() { return { MOTOR_B1 }; }
    int obtenerMotorB2() { return { MOTOR_B2 }; }
    
    void configurarMotorA1(int pin) { MOTOR_A1 = pin; }
    void configurarMotorA2(int pin) { MOTOR_A2 = pin; }
    void configurarMotorB1(int pin) { MOTOR_B1 = pin; }
    void configurarMotorB2(int pin) { MOTOR_B2 = pin; }

    void aAtras();
    void aAdelante();
    void aIzquierda();
    void aDerecha();
    void aParar();
    void explorar();
    
};

// Clase para el Sistema de Bluetooth
class ArBluetooth
{
    public:
      ArBluetooth();
      virtual ~ArBluetooth();
      void inicio();
      void loop();
      String obtenerString();
};

// Clase para el Sistema de Sonido
class ArSonido
{
    public:
      ArSonido();
      virtual ~ArSonido();
      void inicio();
      void loop();
};

// Clase para el Sistema de Distancia Ultrasonido
class ArDistanciaULTRA
{
    private:
      boolean ultraActivo;
      
    public:
      ArDistanciaULTRA();
      virtual ~ArDistanciaULTRA();
      void inicio();
      void loop();
      void activar() { ultraActivo = true; };
      void desactivar() { ultraActivo = false; };
      boolean activo() { return ultraActivo; };
      
};

