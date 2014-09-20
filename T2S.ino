/*
  
  T2S - a Text To Speech software module for the Emic 2 text-to-speech hardware module
                                                         
  Dan Ray antfriend@gmail.com

*/



void T2S_setup()  // Set up code called once on start-up
{
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  
  // set the data rate for the SoftwareSerial port
  t2s_serial.begin(9600);
  
  L_LED_off();
  
  /*
    When the Emic 2 powers on, it takes about 3 seconds for it to successfully
    intialize. It then sends a ":" character to indicate it's ready to accept
    commands. If the Emic 2 is already initialized, a CR will also cause it
    to send a ":"
  */
  t2s_serial.print('\n');             // Send a CR in case the system is already up
  while (t2s_serial.read() != ':');   // When the Emic 2 has initialized and is ready, it will send a single ':' character, so wait here until we receive it
  delay(10);                          // Short delay
  T2S_flush();                 // Flush the receive buffer
  set_voice(2);
  set_settings();
  //say("test 2");
  long random_seed = analogRead(5);
  randomSeed(random_seed);
  //saynumber(random_seed);
}

void set_settings()
{
  //set volume, rate, and language defaults
  speaking();
  L_LED_on();
  t2s_serial.print("V0"); //Volume: [-48 to 18] default=0
  t2s_serial.print('\n');
  t2s_serial.print("W100"); //speaking rate in words per minute [75 - 600] default=200
  t2s_serial.print('\n');
  t2s_serial.print(" ");//dont know why it wont start without this
  postspoke();  
}

void T2S_volume_max()
{
  speaking();
  t2s_serial.print("V10"); //Volume: [-48 to 18] default=0
  postspoke();
}

void T2S_volume_min()
{
  t2s_serial.print("V-48"); //Volume: [-48 to 18] default=0
  //postspoke();
}

void T2S_flush()
{
  t2s_serial.flush();
}

void prespreak()
{
  speaking();
  L_LED_on();
  t2s_serial.print('S');  
}

void postspoke()
{
  t2s_serial.print('\n');
  while (t2s_serial.read() != ':');   // Wait here until the Emic 2 responds with a ":" indicating it's ready to accept the next command
  t2s_serial.flush();
  L_LED_off();   
  listening(); 
}

void set_voice(int vnum)
{
  speaking();
  L_LED_on();
  t2s_serial.print('N' + String(vnum)); 
  t2s_serial.print('\n');
  t2s_serial.print(" ");//dont know why it wont start without this
  postspoke();
}

void say(String say_what)
{
  prespreak();
  t2s_serial.print(say_what);
  postspoke();  
}

void saynumber(int say_numb)
{
 //say(String(char(say_numb)));
 say(String(say_numb));
}

void T2S_yes()
{
  say("Yes?");  
}

void T2S_bridge_on()
{
  say("The bridge is on.");    
}

void T2S_error()
{
  L_LED_on();
  t2s_serial.print('S');
  t2s_serial.print("Error.");
  t2s_serial.print('\n');
  while (t2s_serial.read() != ':');   // Wait here until the Emic 2 responds with a ":" indicating it's ready to accept the next command
  L_LED_off();    
}

void T2S_times_up()
{
  say("Time's up."); 
}

void T2S_starting_vr()
{
  say("Starting voice recognition.");  
}

void T2S_vr_started()
{
  say("Voice recognition started.");
}

void T2S_starting()
{
  say("Starting.");
}

void T2S_action()
{
  say("Action.");
}

void T2S_hello()
{
  say("Hello.");
}

void T2S_all_voices()
{
  say("  :-)0 voice 0 :-)1 voice 1 :-)2 voice 2 :-)3 voice 3 :-)4 voice 4 :-)5 voice 5 :-)6 voice 6 :-)7 voice 7 :-)8 voice 8. :-)4");  
}

void T2S_use_voice(int voice)
{
  //voice can be an int from 0-8
  set_voice(voice);
  say("Now using voice number " + String(voice) + " of 0 through 8.");
  //say("  :-)" + String(voice) + "This is voice number." + String(voice) + ".  I am happy to be speaking to you now as voice number." + String(voice));  
}

void T2S_test()
{
  say("Outlook hazy.");  // Send the desired string to convert to speech
  say("Hello Lila!");  // Send the desired string to convert to speech
  say("Freakazoid robots, please report to the dance floor.");  // Send the desired string to convert to speech
  say("Hello. Yes!  Yes?  Yessir, right away sir.  Hi! sodez neigh!");  // Send the desired string to convert to speech
  say("I am a robot.");  // Send the desired string to convert to speech
}

void T2S_sing_daisy()
{
  L_LED_on();
  speaking();
  //t2s_serial.print("D1\n");
  t2s_serial.print("D1");
  postspoke();

  //while (t2s_serial.read() != ':');   // Wait here until the Emic 2 responds with a ":" indicating it's ready to accept the next command
  //L_LED_off();  
  //listening();
}


void T2S_random_response_for_robot()
{
  long randNumber = random(15);
    switch (randNumber) {
      case 0:
        say("Yes");        
        break;
      case 1:
        say("Human");
        break;
      case 2:
        say("What");
        break;
      case 3:
        say("That is my name, don't wear it out");
        break;
      case 4:
        say("Hi");
        break;
      case 5:
        say("Affirmative!");
        break;
      case 6:
        say("What do you want?");
        break;
      default: 
          say("I am not Stephen Hawking.");
          //saynumber(randNumber);
          break;
    }  
}

void T2S_random_8_ball_response()
{
  long randNumber = random(11);
    switch (randNumber) {
      case 0:
        say("Ask again laytur.");        
        break;
      case 1:
        say("It is certain.");
        break;
      case 2:
        say("No.");
        break;
      case 3:
        say("As I see it, yes.");
        break;
      case 4:
        say("Reply hayzee try again.");
        break;
      case 5:
        say("My sources say, no.");
        break;
      case 6:
        say("Concentrate, and ask again.");
        break;
      default: 
          say("Yes.");
          //saynumber(randNumber);
          break;
    }  
}
