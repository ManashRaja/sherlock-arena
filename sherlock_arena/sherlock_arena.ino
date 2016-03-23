/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * Created by Khaireddine Hlali to support multiple transmitters 
 */

#include "IRremote.h"
#define SEND_SONY


IRsend  irsend0;
IRsend1 irsend1;
IRsend2 irsend2;

int heading1 = 70;
int heading2 = 117;
int heading3 = 296;

void setup()
{
  Serial.begin(9600);
}

void loop() {
  String hex1 = encode_hex(heading1);
  String hex2 = encode_hex(heading2);
  String hex3 = encode_hex(heading3);
  
  Serial.println("\n\n\n");
  Serial.println(hex1);
  Serial.println(hex2);
  Serial.println(hex3);

  
  irsend0.sendNEC(0xff46b9, 32);
  irsend1.sendNEC(0x00ff758a, 32);
  irsend2.sendNEC(0x01fe28d7, 32);
  
  delay(500);
}

int decode_hex(String input)
{
  int zeros = 8-input.length();
  for(int i=0; i<zeros;i++)
  {
    input = "0" + input;    
  }
  String hex_data = input.substring(0,2) + input.substring(4,6);  
  Serial.print("Real Hex data: ");
  Serial.println(hex_data); 
  const char * c = hex_data.c_str();
  int output = (int) strtol(c, NULL, 16);
  return output;
}

String encode_hex(int input)
{
  String real_hex = String(input,HEX);
  int zeros = 4-real_hex.length();
  for(int i=0; i<zeros;i++)
  {
    real_hex = "0" + real_hex;    
  }
  
  char HEXADECIMAL[17] = "0123456789abcdef";
  
  String final_hex = real_hex.substring(0,2);
  for(int i = 0; i<2; i++)
  {
    for(int j = 0; j<16; j++)
    {
      if(real_hex.substring(0+i,1+i) == String(HEXADECIMAL[j]))
      {
        final_hex += String(HEXADECIMAL[15-j]);
      }
    }
  }
  
  final_hex += real_hex.substring(2);
  
  for(int i = 0; i<2; i++)
  {
    for(int j = 0; j<16; j++)
    {
      if(real_hex.substring(2+i,3+i) == String(HEXADECIMAL[j]))
      {
        final_hex += String(HEXADECIMAL[15-j]);
      }
    }
  }
  return final_hex;
   
}
