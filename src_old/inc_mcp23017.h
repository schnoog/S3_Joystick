#include <Adafruit_MCP23X17.h>

Adafruit_MCP23X17 mcp;


void mcp23017_setup(){
    int BP=0;
    mcp.begin_I2C(0x21);
    for(BP=0; BP < 16; BP++){

    mcp.pinMode(BP, INPUT_PULLUP);
    }
}

void mcp23017_loop(){
    int BP=0;
    int TMP=0;
    for(BP=0; BP < 16; BP++){
        TMP = mcp.digitalRead(BP);
        Serial.print(TMP);
    }
    Serial.println("");

}


/*
#include <MCP23017.h>

#define MCP23017_ADDR 0x21
MCP23017 mcp[8]; 



void mcp23017_setup(){
    mcp[0] = MCP23017(MCP23017_ADDR);
    mcp[0].init();
    mcp[0].portMode(MCP23017Port::A, 0b11111111 ,0b11111111 , 0b11111111);          //Port A as output
    mcp[0].portMode(MCP23017Port::B, 0b11111111 ,0b11111111); //Port B as input


}



void mcp23017_loop(){
    uint8_t currentA;
    uint8_t currentB;
    currentA = mcp[0].readPort(MCP23017Port::A);
    currentB = mcp[0].readPort(MCP23017Port::B);
    Serial.print("A/B: ");
    Serial.print(currentA,BIN);
    Serial.print("/");
    Serial.println(currentB,BIN);

}
*/