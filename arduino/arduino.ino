// see instructions here for uploading the html files to spiffs info:
// http://esp8266.github.io/Arduino/versions/2.0.0/doc/filesystem.html

int appState = 0;
int bootPhase = 0;

void setup()
{
  // startup delay, prevents overcurrent from preventing programming
    delay(1000);

  // intentionally left empty. 
  // ESP8266 / ESP32 chips don't like delays 
  // ( they will reset if anything takes too long before a yield / delay / etc. ) 
  // so I'm using a boot sequence instead.
}

void loop()
{
  switch(appState) {

    case 0:
      boot_Update();
      break;
      
    case 1: 
      Webserver_Update();
      break;
  }
}

void boot_Update() {

  switch(bootPhase) {

    case 0: 
      pinMode(0, OUTPUT);
      digitalWrite(0, LOW);

      pinMode(2, OUTPUT);
      digitalWrite(2, LOW);
      
      bootPhase = 1;
      break;

     case 1:
      Webserver_Init();
      bootPhase = 2;
      appState = 1;
      break;
  }
}

void leftStart() 
{
  digitalWrite(0, HIGH);
}

void leftStop() 
{
  digitalWrite(0, LOW);
}

void rightStart() 
{
  digitalWrite(2, HIGH);
}

void rightStop() 
{
  digitalWrite(2, LOW);
}
