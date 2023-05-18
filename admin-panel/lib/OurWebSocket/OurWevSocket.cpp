#include "OurWebSocket.h"

WebSocketsServer webSocket(81);

bool ws::InitWebSocketServer(){
    
    webSocket.begin();
    webSocket.onEvent(ws::HandleWebSocketServer);
    return true;
    
}

bool ws::WebSocketServerSendMessage(uint8_t num, uint8_t * payload){
    if(webSocket.sendTXT(num, payload)) return true;
        else return false;
}

void ws::HandleWebSocketLoop(){
    webSocket.loop();
}

void ws::HandleWebSocketServer(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght){
    switch (type)
    {
    case WStype_CONNECTED:
        Serial.printf("Conectado! %u \n", num);
        break;
    case WStype_DISCONNECTED:
        Serial.printf("Desconectado! %u \n", num);
        break;
    case WStype_TEXT:
        Serial.printf("%u: payload %s \n", num, payload);
        break;
    default:
        break;
    }
}