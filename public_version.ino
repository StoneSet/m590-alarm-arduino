//Basé sur un émetteur M590E

#include <SoftwareSerial.h>
#include <String.h>

SoftwareSerial mySerial(7,8); //Pin 7 : TX ; Pin 8 : RX (Module M590E)

//button pin
int buttonPin = 3; //Defaut alarme : Ligne EDF
int buttonPin2 = 4; //Defaut alarme : Intrusion
int buttonPin3 = 5; //Pour plus tard

void setup()
{
  mySerial.begin(9600);    //Vitesse de communication
  Serial.begin(9600);    //Vitesse de communication
  delay(500);
  pinMode(buttonPin, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
}

void loop(){
  //Bouton intrusion
  int buttonVal = digitalRead(buttonPin);
  if(buttonVal == HIGH)
    SendIntrusion();
  //Bouton EDF
  int buttonVal2 = digitalRead(buttonPin2);
  if(buttonVal2 == HIGH)
    SendEDF();
  //Bouton Other
  int buttonVal3 = digitalRead(buttonPin3);
  if(buttonVal3 == HIGH)
    SendOther();
delay(500);
}

//Message intrusion
void SendIntrusion()
{
  mySerial.print("AT+CMGF=1\r");    //Emetteur mode SMS
  delay(100);
  mySerial.print("AT+CSCS=\"GSM\"\r");
  delay(100);
  mySerial.println("AT+CMGS=\"+33XXXXXXXXX\""); //Numéro de téléphone + la zone
  delay(100);
  mySerial.print("DEFAUT ALARME : Intrusion dans la maison");//Le message à envoyer
  delay(100);
  mySerial.print((char)26);//Code ASCII de CRTL+Z
  delay(100);
  mySerial.println();
}

//Message EDF
void SendEDF()
{
  mySerial.print("AT+CMGF=1\r");
  delay(100);
  mySerial.print("AT+CSCS=\"GSM\"\r");
  delay(100);
  mySerial.println("AT+CMGS=\"+33XXXXXXXXX\"");
  delay(100);
  mySerial.print("DEFAUT ALARME : Ligne EDF");
  delay(100);
  mySerial.print((char)26);
  delay(100);
  mySerial.println();
}

//En attente
void SendOther()
{
  mySerial.print("AT+CMGF=1\r");
  delay(100);
  mySerial.print("AT+CSCS=\"GSM\"\r");
  delay(100);
  mySerial.println("AT+CMGS=\"+33XXXXXXXXX\"");
  delay(100);
  mySerial.print("-----");
  delay(100);
  mySerial.print((char)26);
  delay(100);
  mySerial.println();
}
