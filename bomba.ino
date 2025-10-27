  #include <LiquidCrystal_I2C.h>
  #include <Keypad.h>
  #include <Wire.h>

  #define lcd_Add 0x27

  #define BTN_PIN 3
  #define RED_PIN 2
  #define YEL_PIN 0
  #define GRE_PIN 1

  #define BUZ_PIN 5

  const byte LINHAS = 4;   // Linhas do teclado
  const byte COLUNAS = 4;  // Colunas do teclado

  const char TECLAS_MATRIZ[LINHAS][COLUNAS] = {  // Matriz de caracteres (mapeamento do teclado)
    { '1', '2', '3', 'A' },
    { '4', '5', '6', 'B' },
    { '7', '8', '9', 'C' },
    { '*', '0', '#', 'D' }
  };

  byte mult[8] = {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000
  };

  byte die[8] = {
    0b11111,
    0b10100,
    0b10100,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000
  };

  byte zero[8] = {
    0b00001,
    0b00001,
    0b00001,
    0b01101,
    0b00001,
    0b00001,
    0b00001,
    0b00001
  };
  byte one[8] = {
    0b00000,
    0b00000,
    0b00000,
    0b00111,
    0b00100,
    0b00100,
    0b00100,
    0b11111
  };
  byte two[8] = {
    0b11111,
    0b10001,
    0b10001,
    0b10111,
    0b10000,
    0b10000,
    0b10000,
    0b10000
  };
  byte three[8] = {
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00111,
    0b00100,
    0b00100,
    0b00100
  };
  byte four[8] = {
    0b11001,
    0b11001,
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b11111
  };
  byte five[8] = {
    0b00000,
    0b01110,
    0b00100,
    0b00100,
    0b11111,
    0b00100,
    0b00100,
    0b00100
  };

  byte six[8] = {
    0b11111,
    0b10001,
    0b10001,
    0b10111,
    0b10000,
    0b10000,
    0b10000,
    0b11100
  };

  byte seven[8] = {
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b00001
  };

  byte eight[8] = {
    0b01100,
    0b01100,
    0b01100,
    0b01100,
    0b01100,
    0b01100,
    0b01100,
    0b01100
  };

  byte nine[8] = {
    0b00000,
    0b00000,
    0b00000,
    0b01100,
    0b01100,
    0b00000,
    0b00000,
    0b11111
  };

  byte block[8] = {
    0b00011,
    0b01011,
    0b00000,
    0b01100,
    0b00100,
    0b10011,
    0b01000,
    0b00000
  };

  const char conversion1[] = {
    '0',
    '3',
    '6',
    '9',
    '2',
    '5',
    '8',
    '1',
    '4',
    '7'
  };

  const char conversion2[] = {
    '0',
    '7',
    '5',
    '1',
    '8',
    '5',
    '2',
    '9',
    '6',
    '3'
  };

bool modeLoaded = false;
int highscore_min = 0;
int highscore_sec = 0;
int highscore_raw = 600;

  const byte* numbers[] = {
    zero,
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine
  };

  enum bomb_state {
    mode_selection,
    active,
    exploded,
    disarmed
  };

  enum bomb_state state = mode_selection;

  char digit3[] = {'0', '0'};

  const byte PINOS_LINHAS[LINHAS] = { 13, 12, 11, 10 };  // Pinos de conexao com as linhas do teclado
  const byte PINOS_COLUNAS[COLUNAS] = { 9, 8, 7, 6 };    // Pinos de conexao com as colunas do teclado

  LiquidCrystal_I2C lcd(lcd_Add, 16, 2);
  Keypad keypad = Keypad(makeKeymap(TECLAS_MATRIZ), PINOS_LINHAS, PINOS_COLUNAS, LINHAS, COLUNAS);  //

  enum difficulty {
    Easy,
    Normal,
    Hard
  };

  bool global_pressed = false;

  String password = "";
  char passwordchar[5];  //5 is the max.

  String master_password = "14293255";
  String inputed_password = "";

  enum difficulty selected_dif = Easy;

  bool global_debounce = false;

  int* choices[] = { 0, 0, 0, 0, 0 };

void printArray(int arr[], int size) {
  Serial.print("[");
  for (int i = 0; i < size; i++) {
    Serial.print(arr[i]);
    if (i < size - 1) Serial.print(", ");
  }
  Serial.println("]");
}


  class Timer {
  private:
    int last;

    void display() {
      tone(BUZ_PIN, 1500, 100);

      if ((choices[0] == 2 || choices[0] == 3) && global_pressed) {
        return;
      }
      lcd.setCursor(0, 0);
      String secStr = String(seco);
      if (secStr.length() <= 1) {
        secStr = "0" + secStr;
      }
      if (choices[1] == 2) {
        lcd.print(String(minu) + ":" + secStr + "    " + String(speed, 2) + "y");
      } else {
        lcd.print(String(minu) + ":" + secStr + "    " + String(speed, 2) + "x");
      }
      lcd.setCursor(14,0);
      String help = String(digit3[0])+String(digit3[1]);
      //Serial.println(help);
      lcd.print(help);
    }

    void tickent() {
      seco -= 1;
      if (seco <= 0) {
        minu -= 1;
        seco = 59;
      }
      if (seco <= 0 && minu <= 0) {
        state = exploded;
        return;
      }
      display();
    }

  public:
    int minu;
    int seco;
    float speed;

    Timer(int minutes, int seconds)
      : minu(minutes), seco(seconds) {
      last = millis();
      speed = 1;
    }

    void tick() {
      int ti = millis();
      if ((ti - last) >= (1000 / speed)) {
        last = ti;
        tickent();
      }
    }
  };

  class Task {
  private:
    void (*callback)();      // Function to call
    unsigned long interval;  // Time between calls in milliseconds
    unsigned long lastRun;   // Last time the task ran
    bool enabled;            // Is the task active?
    bool autoDisable;

  public:
    // Constructor
    Task(void (*cb)(), unsigned long ms, bool selfDisable, bool starts)
      : callback(cb), interval(ms), lastRun(0), enabled(starts), autoDisable(selfDisable) {}

    // Call this every loop
    void update() {
      if (!enabled) return;
      unsigned long now = millis();
      if (now - lastRun >= interval) {
        lastRun = now;
        callback();
        if (autoDisable) {
          disable();
        }
      }
    }

    void setInterval(unsigned long ms) {
      interval = ms;
    }
    void enable() {
      enabled = true;
    }
    void disable() {
      enabled = false;
    }
  };

  Timer time = Timer(10, 10);

  void generate_password() {
    password = "";
    for (int i = 0; i < 4; i++) {
      int choice = random(0, 10);
      password += choice;
      passwordchar[i] = '0' + choice;
    }
    Serial.println(password);
    choices[2] = 3;
      choices[3] = int(passwordchar[2]);
      int a = abs(int(passwordchar[2]) - '0');
      int b = abs(int(passwordchar[3]) - '0');
      int result = ((a * 9) + b);
      String cokaine = String(result);
      Serial.println(result);
      digit3[0] = cokaine.charAt(0);
      digit3[1] = cokaine.charAt(1);
  }

  void reboot() {
    delay(100);
    modeLoaded = false;
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dificuldade: ");
    
    randomSeed(analogRead(0));
    time = Timer(3, 30);
    state = mode_selection;
    selected_dif = Easy;
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GRE_PIN, HIGH);
    digitalWrite(YEL_PIN, LOW);
    delay(300);
    lcd.setCursor(0, 1);
    lcd.print("Facil");
  }

  void setup() {
    Serial.begin(9600);
    Serial.println("Bomb boot.");

    pinMode(BTN_PIN, INPUT_PULLUP);
    pinMode(RED_PIN, OUTPUT);
    pinMode(GRE_PIN, OUTPUT);
    pinMode(YEL_PIN, OUTPUT);
    pinMode(BUZ_PIN, OUTPUT);

    digitalWrite(RED_PIN, LOW);
    digitalWrite(GRE_PIN, HIGH);
    digitalWrite(YEL_PIN, LOW);

    lcd.init();

    lcd.createChar(0, die);
    lcd.createChar(1, mult);
    lcd.createChar(7, block);

    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.write(byte(1));
    lcd.print(" Hello,");
    lcd.setCursor(0, 1);
    lcd.print("Moto!");

    delay(2000);

    lcd.clear();
    lcd.noBacklight();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Dificuldade: ");
    lcd.setCursor(0, 1);
    lcd.print("Facil");
    randomSeed(analogRead(0));
    time = Timer(3, 30);
  }

  void select_loop() {
    char key = keypad.getKey();

    if (key) {
      state = active;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Carregando...");
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(GRE_PIN, HIGH);
      digitalWrite(YEL_PIN, HIGH);
      tone(BUZ_PIN, 1000, 300);
      generate_password();
      delay(3000);
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GRE_PIN, LOW);
      digitalWrite(YEL_PIN, LOW);
      global_debounce = false;
      return;
    }

    bool pressed = (digitalRead(BTN_PIN) == LOW);

    if (!pressed) {
      global_debounce = false;
      return;
    }

    if (global_debounce) {
      return;
    }
    tone(BUZ_PIN, 2500, 100);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dificuldade: ");
    lcd.setCursor(0, 1);
    global_debounce = true;
    if (selected_dif == Easy) {
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GRE_PIN, LOW);
      digitalWrite(YEL_PIN, HIGH);
      time = Timer(2, 30);
      selected_dif = Normal;
      lcd.print("Normal");

    } else if (selected_dif == Normal) {
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(GRE_PIN, LOW);
      digitalWrite(YEL_PIN, LOW);
      time = Timer(1, 30);
      lcd.print("Dificil");
      selected_dif = Hard;

    } else {
      selected_dif = Easy;
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GRE_PIN, HIGH);
      digitalWrite(YEL_PIN, LOW);
      lcd.print("Facil");
      time = Timer(3, 30);
    }

    delay(200);
  }

  void succes() {
    state = mode_selection;
    tone(BUZ_PIN, 1500, 1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bomba desarmada!");
    lcd.setCursor(0, 1);
    delay(1000);
    tone(BUZ_PIN, 2300, 1000);
    lcd.print("Tenha um bom dia.");
    delay(2000);
    int current = (timer.min * 60) + timer.sec;
    if (highscore_raw < current) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("NOVO HIGHSCORE!");
      tone(BUZ_PIN, 1000, 300);
      delay(300);
      tone(BUZ_PIN, 2000, 500);
      delay(500);
      lcd.clear();
      lcd.print("Seu: "+timer.min+":"+timer.sec);
      lcd.setCursor(1,0);
      lcd.print("A: "+highscore_min+":"+highscore_sec);
      highscore_raw = current;
      highscore_min = timer.min;
      highscore_sec = timer.sec;
    } else {
      
    }
    reboot();
  }

  void admin_bypass() {
    state = disarmed;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Admin");
    tone(BUZ_PIN, 3000, 500);
    lcd.setCursor(0, 1);
    lcd.print("Bypass");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Code");
    tone(BUZ_PIN, 3000, 500);
    delay(1000);
    state = mode_selection;
    reboot();
  }

  void fail() {
    if (time.speed > 2) {
      state = exploded;
      return;
    }

    tone(BUZ_PIN, 1000, 400);
    if (selected_dif == Hard) {
      time.speed += 0.5;
    } else {
      time.speed += 0.25;
    }
  }

  bool written = false;

  void easy_clue() {
    written = false;
    choices[0] = random(1, 3);
    choices[1] = 1;
    choices[2] = random(1, 3);
    choices[3] = random(1, 3);
    choices[4] = random(1, 3);
  }

  void normal_clue() {
    written = false;
    choices[0] = random(1, 4);
    choices[1] = random(1, 3);
    choices[2] = random(1, 3);
    choices[3] = random(1, 3);
    choices[4] = random(1, 3);
  }

  void hard_clue() {
    written = false;
    choices[0] = random(2, 4);
    choices[1] = random(1, 3);
    choices[2] = random(1, 3);
    choices[3] = random(1, 3);
    choices[4] = random(1, 3);
  }

  void disableRed() {
    digitalWrite(RED_PIN, LOW);
  }

  Task disableRedTask(disableRed, 200, true, false);

  void disableGreen() {
    digitalWrite(GRE_PIN, LOW);
  }
  Task disableGreTask(disableGreen, 500, true, false);


  void clues() {
    global_pressed = (digitalRead(BTN_PIN) == LOW);

    if (choices[0] == 1) {
      if (!global_pressed) {
        disableRedTask.update();
        String temp = String(time.seco);
        if (temp.charAt(temp.length() - 1) == password.charAt(0)) {
          digitalWrite(RED_PIN, HIGH);
          disableRedTask.enable();
        }
      }
    } else if (choices[0] == 2) {
      disableGreTask.
      if (global_pressed) {
        if (global_debounce) {
          lcd.setCursor(0, 0);
          lcd.print("                ");
          lcd.setCursor(0, 0);
          lcd.write(byte(0));

          int Digit = passwordchar[0] - '0';  // Make sure is an INT >:(
          int ecrypted = Digit * 10 * 0.5;
          char result[2];
          String encryptedTxt = String(ecrypted);
          encryptedTxt.toCharArray(result, 3);

          if (!written) {
            lcd.createChar(3, (uint8_t*)numbers[int(result[0]) - '0']);
            lcd.createChar(4, (uint8_t*)numbers[int(result[1]) - '0']);
            written = true;
            delay(200);
          }

          lcd.setCursor(1, 0);
          lcd.write(byte(3));
          lcd.write(byte(4));

          global_debounce = false;
        }

      } else {
        global_debounce = true;
      }
    } else if (choices[0] == 3) {
      if (global_pressed) {
        if (global_debounce) {
          lcd.setCursor(0, 0);
          lcd.print("                ");
          lcd.setCursor(0, 0);
          lcd.write(byte(1));

          int Digit = passwordchar[0] - '0';  // Make sure is an INT >:(
          int ecrypted = Digit * 10 * 2;
          char result[3];
          String encryptedTxt = String(ecrypted);
          encryptedTxt.toCharArray(result, 4);

          if (!written) {
            lcd.createChar(3, (uint8_t*)numbers[int(result[0]) - '0']);
            lcd.createChar(4, (uint8_t*)numbers[int(result[1]) - '0']);
            lcd.createChar(5, (uint8_t*)numbers[int(result[2]) - '0']);
            written = true;
            delay(200);
          }

          lcd.setCursor(1, 0);
          lcd.write(byte(3));
          lcd.write(byte(4));
          lcd.write(byte(5));
          global_debounce = false;
        }
      } else {
        global_debounce = true;
      }
    }

    if (choices[1] == 1) {
      disableGreTask.update();
      int Digit = passwordchar[1] - '0';
      String temp = String(time.seco);
      char lastSecondDigit = temp.charAt(temp.length() - 1);
      if (lastSecondDigit == '0') {
        //Serial.print(Digit);
      }
      if (conversion1[Digit] == lastSecondDigit) {
        //Serial.println("Choice check 2 passed!");
        if (global_pressed) {
          lcd.setCursor(15, 1);
          digitalWrite(GRE_PIN, HIGH);
          lcd.write(byte(7));
        } else {
          lcd.setCursor(15, 1);
          lcd.print(" ");
        }
      } else {
        lcd.setCursor(15, 1);
        lcd.print(" ");
      }
    } else {
      disableGreTask.update();
      int Digit = int(passwordchar[1]);
      String temp = String(time.seco);
      if (conversion2[Digit] == temp.charAt(temp.length() - 1)) {
        if (global_pressed) {
          lcd.setCursor(16, 1);
          lcd.write(byte(7));
          digitalWrite(GRE_PIN, HIGH);
        } else {
          lcd.setCursor(16, 1);
          lcd.print(" ");
        }
      } else {
        lcd.setCursor(16, 1);
        lcd.print(" ");
      }
    }
  }

  void active_loop() {
    time.tick();

    clues();

    char key = keypad.getKey();

    if (!modeLoaded) {
      modeLoaded = true;
      switch (selected_dif) { 
        case 0: // Din't looked like it worked with the name so I swicthed to numbers, hope It works :pray:
          easy_clue();
          break;
        
        case 1:
          normal_clue();
          break;

        case 2:
          hard_clue();
          break;

        default:
          easy_clue();
          break;
      }
    }

    
    //printArray(choices, 4);

    if (!key) {
      return;
    }

    if (key == 'A' || key == 'B' || key == 'C' || key == 'D') {
      return;
    }

    if (key == '*') {
      inputed_password.remove(inputed_password.length() - 1);
    } else if (key == '#') {
      if (inputed_password == password) {
        succes();
      } else if (inputed_password == master_password) {
        admin_bypass();
      } else {
        fail();
      }
      inputed_password = "";
    } else {
      if (inputed_password.length() <= 8) {
        inputed_password += key;
      }
    }

    lcd.setCursor(0, 1);
    lcd.print("               ");
    lcd.setCursor(0, 1);
    lcd.print(inputed_password);
  }

void explode() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CABOOM!");
  tone(BUZ_PIN, 3000, 1000);
  delay(1000);
  reboot();
}

  void loop() {
    if (state == mode_selection) { select_loop(); }
    if (state == active) { active_loop(); }
    if (state == exploded) { explode(); }
  }