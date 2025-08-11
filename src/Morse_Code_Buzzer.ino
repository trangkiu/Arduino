/*
 * Arduino Morse Code Buzzer
 * Converts text to Morse code and plays it through a buzzer
  * Board: 
   Passive buzzer : - G , pin 3
 */
const int buzzerPin = 3;
const int buzzerSound = 100;  // Duration in milliseconds
const int pauseBetweenChar = 200;
const int pauseBetweenWords = 500;
boolean isReading = false;

// Character map: 0 = dot, 1 = dash 
int a[] = {0,1,-1}; 
int b[] = {1,0,0,0,-1};
int c[] = {1,0,1,0,-1};
int d[] = {1,0,0,-1};
int e[] = {0,-1};
int f[] = {0,0,1,0,-1};
int g[] = {1,1,0,-1};
int h[] = {0,0,0,0,-1};
int i[] = {0,0,-1};
int j[] = {0,1,1,1,-1};
int k[] = {1,0,1,-1};
int l[] = {0,1,0,0,-1};
int m[] = {1,1,-1};
int n[] = {1,0,-1};
int o[] = {1,1,1,-1};
int p[] = {0,1,1,0,-1};
int q[] = {1,1,0,1,-1};
int r[] = {0,1,0,-1};
int s[] = {0,0,0,-1};
int t[] = {1,-1};
int u[] = {0,0,1,-1};
int v[] = {0,0,0,1,-1};
int w[] = {0,1,1,-1};
int x[] = {1,0,0,1,-1};
int y[] = {1,0,1,1,-1};
int z[] = {1,1,0,0,-1};

void setup() {
    pinMode(buzzerPin, OUTPUT);
    Serial.begin(9600);
}

void loop() {
   
  if (Serial.available() && !isReading) {
    isReading = true;  
    String input = Serial.readStringUntil('\n');
    input.trim();
    input.toLowerCase();
    
    Serial.println("Playing: " + input);
       for(int i = 0; i < input.length(); i++){
          if(input[i] == ' '){
            space();
            Serial.print(" ");
          } else {
            int* morseCode = mapChar(input[i]);
            if(morseCode != nullptr){
              convert(morseCode);
            }
          }
         Serial.print("/");
      }
    Serial.println();
    Serial.println("Finished playing");
    isReading = false;  
    delay(2000); 
  }

   
}

int* mapChar(char input){
  switch (input) {
      case 'a': case 'A': return a;
      case 'b': case 'B': return b;
      case 'c': case 'C': return c;
      case 'd': case 'D': return d;
      case 'e': case 'E': return e;
      case 'f': case 'F': return f;
      case 'g': case 'G': return g;
      case 'h': case 'H': return h;
      case 'i': case 'I': return i;
      case 'j': case 'J': return j;
      case 'k': case 'K': return k;
      case 'l': case 'L': return l;
      case 'm': case 'M': return m;
      case 'n': case 'N': return n;
      case 'o': case 'O': return o;
      case 'p': case 'P': return p;
      case 'q': case 'Q': return q;
      case 'r': case 'R': return r;
      case 's': case 'S': return s;
      case 't': case 'T': return t;
      case 'u': case 'U': return u;
      case 'v': case 'V': return v;
      case 'w': case 'W': return w;
      case 'x': case 'X': return x;
      case 'y': case 'Y': return y;
      case 'z': case 'Z': return z;
      default:
        return nullptr;  
  }
}

void convert(int* morseCode){
  int i = 0;
  while(morseCode[i] != -1){ 
    if(morseCode[i] == 0){
      dot();
      Serial.print(".");
    } else if(morseCode[i] == 1){
      dash();
      Serial.print("-");
    }
    i++;
  }
  delay(pauseBetweenChar);  // Pause between characters
}

void dot(){
  tone(buzzerPin, 1000, buzzerSound);  
  delay(buzzerSound);
  delay(50);  // Short pause after dot
}

void dash(){
  tone(buzzerPin, 1000, buzzerSound * 3);  // Dash is 3 times longer than dot
  delay(buzzerSound * 3);
  delay(50);  // Short pause after dash
}

void space(){
  delay(pauseBetweenWords);  // Pause between words
}
