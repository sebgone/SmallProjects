
int WalkRequest = 0;         

int WalkButton = 2;          
int redPed = 7;
int greenPed = 6; 

int green_1 = 8;              
int yellow_1 = 9;
int red_1 = 10;

int green_2 = 13;             
int yellow_2 = 12;
int red_2 = 11;

int r =  1;                   
int yr = 2;
int g =  3;
int y =  4;


int TIME_R = 14000;                    
int TIME_Y = 2000;                        
int R_Value = TIME_R - 2 * TIME_Y;     
                                       
volatile int buttonState = 0;          

void setup() {
  pinMode(green_1, OUTPUT);              
  pinMode(yellow_1, OUTPUT);
  pinMode(red_1, OUTPUT);
  
  pinMode(green_2, OUTPUT);
  pinMode(yellow_2, OUTPUT);
  pinMode(red_2, OUTPUT);

  pinMode(redPed, OUTPUT);  
  pinMode(greenPed, OUTPUT);
  
  pinMode(WalkButton, INPUT_PULLUP);      

  attachInterrupt(0, pin_ISR, CHANGE);  
  
  for(int i=6; i<14; i++)                  
    {
      digitalWrite(i, HIGH);
      delay(200);
    }
    
  for(int i=6; i<14; i++)                 
    {
      digitalWrite(i, LOW);
      delay(200);
    }

     digitalWrite (redPed, HIGH);        
}

void loop() {
                                        
               //stage: 
  street_a(g);
  street_b(r);
  delay(R_Value);
               //stage: II
  street_a(y);
  street_b(r);
  delay(TIME_Y);
               //stage: III
  street_a(y);
  street_b(yr);
  delay(TIME_Y);

  if (WalkRequest == 1) 
  {                                     
     WalkCycle();                       
     goto etykieta;
  }
               //stage: IV
  street_a(r);
  street_b(g);
  delay(R_Value);
               //stage: V
  etykieta:  
             
  street_a(r);
  street_b(y);
  delay(TIME_Y);
               //stage: VI
  street_a(yr);
  street_b(y);
  delay(TIME_Y);
}

   void street_a(int light)
   {
      switch  (light)                             
      {
      case 1:                                           
      digitalWrite(red_1, HIGH);
      digitalWrite(yellow_1, LOW); 
      digitalWrite(green_1, LOW);
      break;
      
      case 2:                       
      digitalWrite(red_1, HIGH);
      digitalWrite(yellow_1, HIGH); 
      digitalWrite(green_1, LOW);
      break;
      
      case 3:                        
      digitalWrite(red_1, LOW);
      digitalWrite(yellow_1, LOW); 
      digitalWrite(green_1, HIGH);
      break;
      
      case 4:                        
      digitalWrite(red_1, LOW);
      digitalWrite(yellow_1, HIGH); 
      digitalWrite(green_1, LOW);
      break;
      default:                      
      digitalWrite(red_1, LOW);
      digitalWrite(yellow_1, LOW); 
      digitalWrite(green_1, LOW);
      break;
      } 
  }
  
   void street_b(int light)
   {
      switch  (light) 
      {
      case 1:                          
      digitalWrite(red_2, HIGH);
      digitalWrite(yellow_2, LOW); 
      digitalWrite(green_2, LOW);
      break;
      
      case 2:                         
      digitalWrite(red_2, HIGH);
      digitalWrite(yellow_2, HIGH); 
      digitalWrite(green_2, LOW);
      break;
      
      case 3:                         
      digitalWrite(red_2, LOW);
      digitalWrite(yellow_2, LOW); 
      digitalWrite(green_2, HIGH);
      break;
      
      case 4:                         
      digitalWrite(red_2, LOW);
      digitalWrite(yellow_2, HIGH); 
      digitalWrite(green_2, LOW);
      break;
      default:                        
      digitalWrite(red_2, LOW);
      digitalWrite(yellow_2, LOW); 
      digitalWrite(green_2, LOW);
      break;
      }
   } 
   
   void WalkCycle()                                         
   {
     street_a(r);
     street_b(g);
     delay(1000);                             
     digitalWrite (greenPed, HIGH); 
     digitalWrite (redPed, LOW);              
     delay (8000);                            
     digitalWrite (greenPed, LOW); 
     digitalWrite(WalkButton, LOW);                   
     delay(200);
     for (int x = 0; x < 5; x++) 
        {                                     
         digitalWrite(greenPed, HIGH);
         delay(200);
         digitalWrite(greenPed, LOW);
         delay(200);
        }
  
     digitalWrite(redPed, HIGH);
     WalkRequest = 0;                          
  } 

void pin_ISR()                                 
{
    buttonState  = digitalRead(WalkButton);    
   (WalkRequest = 1);                          
}