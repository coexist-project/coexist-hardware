#pragma once

#include <Arduino.h>
#include <WebSocketsServer.h>

namespace ws {
    bool InitWebSocketServer();
    void HandleWebSocketServer(uint8_t, WStype_t, uint8_t *, size_t );
    bool WebSocketServerSendMessage(uint8_t, uint8_t *);
    void HandleWebSocketLoop();
}
