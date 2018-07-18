#include <SoftwareSerial.h>

//---------Move to include file--------
#define NUM_MOD_KEYS 5
//                                    { CTRL, SHIFT, ALT, GUI,  ALTGR } 
static char modifiers[NUM_MOD_KEYS] = { (char)0x80, (char)0x81, (char)0x82, (char)0x83, (char)0x86 };
//----------------END------------------

SoftwareSerial receiver(14, 16); // (RX, TX)
int is_key_modifier(char value);
  
void setup()
{
  Keyboard.begin();
  receiver.begin(115200);
}

void loop()
{
  while (receiver.available()) {
    char c = receiver.read();
    if (is_key_modifier(c))
      Keyboard.press(c);
    else
      Keyboard.write(c);
  }
  Keyboard.releaseAll();
}

int is_key_modifier(char value)
{
  int i;
  if (value == 0)
    return 0;

  for (i = 0; i < NUM_MOD_KEYS; i++) {
    if(value == modifiers[i])
      return 1;
  }
  
  return 0;
}
