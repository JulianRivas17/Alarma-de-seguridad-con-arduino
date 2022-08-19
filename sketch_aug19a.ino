//Programación del Módulo GSM GPRS SIM900 más el módulo RTC, añadiendo un contador que muestra la cantidad de veces que el sensor PIR fue activado
#include <ThreeWire.h>  
#include <RtcDS1302.h>
#include <SoftwareSerial.h>
SoftwareSerial SIM900 (7, 8); // pines que utiliza el GSM GPRS SIM900 para la comunicación 
ThreeWire myWire(4,5,2); // IO, SCLK, CE (Pines usados en el arduino)
RtcDS1302<ThreeWire> Rtc(myWire);
int pin = 12; //salida pir
int led = 13; //definimos el LED
int conta=0; //definimos “conta” como variable con valor de 0 ya que almacenara nuestro contador
void setup () 
{
   Serial.begin(19200);//Configuramos la velocidad del puerto serial 
   pinMode(12,INPUT);
   pinMode(pin, INPUT);
   pinMode(led, OUTPUT);
   digitalWrite(pin,LOW);
   digitalWrite(led,LOW);
 ;
Serial.println("calibracion completa satisfactoriamente.");//Imprimir en el monitor serial
Serial.println(" SENSOR ACTIVO ");//Imprimir en el monitor serial
delay(50);
SIM900.begin(19200);//velocidad del puerto serie SIM900
Serial.begin(19200);//velocidad del puerto serie del arduino Serial.println("OK"); 
delay (1000);
SIM900.println("AT + CPIN = \"1111\"");  //Comando AT para introducir el PIN de la tarjeta


    
delay(25000);
    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);
 Rtc.Begin();
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();
    if (!Rtc.IsDateTimeValid()) 
    {
        Serial.println("RTC lost confidence in the DateTime!");
        Rtc.SetDateTime(compiled);
    }
    if (Rtc.GetIsWriteProtected())
    {
        Serial.println("RTC was write protected, enabling writing now");
        Rtc.SetIsWriteProtected(false);
    }
    if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }
    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) 
    {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }
else if (now > compiled) 
    {
        Serial.println("RTC is newer than compile time. (this is expected)");
    }
    else if (now == compiled) 

    {
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }
}
  void hacerLlamada()//Void donde se guarda la funcion de llamar
   {
    SIM900.print("ATD");
SIM900.print("3876113240");//Definimos el número de teléfono 
SIM900.println(";");
Serial.println("llamando...");//Imprimir en el monitor serial
delay(25000);
SIM900.println("ATH");
Serial.println("Llamada finalizada");//Imprimir en el monitor serial
   }
void loop () 
{
  if (digitalRead(12) == HIGH)//cuando el sensor este HIGH entonces se activara la variable conta
  {
   if (digitalRead(12)== true)
    {
    conta++;
    Serial.println(conta);
    delay(1);
    }
}
  if(digitalRead(pin) == HIGH)
    {
      digitalWrite(led, HIGH);// definimos: si el sensor esta encendido, se prenderá el diodo led 
      
delay(1000);
      Serial.println("** MOVIMIENTO DETECTADO **");
      Serial.println("");
      delay(1000);
      hacerLlamada(); //envia sms
    }
    else
    {
      digitalWrite(led, LOW);
    }
    RtcDateTime now = Rtc.GetDateTime();
    printDateTime(now);
    Serial.println();
    if (!now.IsValid())
{
        Serial.println("RTC lost confidence in the DateTime!");
    }
    delay(10000); // ten seconds
}
#define countof(a) (sizeof(a) / sizeof(a[0]))
void printDateTime(const RtcDateTime& dt)
{
    char datestring[25];
    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u   %02u:%02u:%02u"),
            dt.Month(),// definimos mes
            dt.Day(),//definimos día
            dt.Year(),//definimos año
            dt.Hour(),//definimos hora
            dt.Minute(),//definimos minutos
            dt.Second() );//definimos segundos
    Serial.print(datestring);
}
