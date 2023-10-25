#ifndef APP_H
#define APP_H

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_FT6206.h>

// These are for the screen connection
#define TFT_DC 2
#define TFT_CS 4

#include "utils.cpp"
#include "env.cpp"

// Reserva test
static utils::Reserva reservaInProgress = {
    "Bautista D.",
    "10:00",
    "11:20",
    "Clase de Ingles",
    {
        "A1",
        34
    },
    2
};

class App
{
private:
    utils::WiFi *m_WiFi = nullptr;
    utils::Reserva *m_reserva = &reservaInProgress;
    utils::Screen m_screen;
    utils::Evento m_events;
    utils::Time m_time;
    List<utils::Button> m_buttons;
    utils::Statement m_statement;
    void (App::*m_stateFunction)() = &App::s_WaitingForConnection;

public:
    App(){};
    ~App(){};

    // Pricipal functions
    void p_run();
    bool p_init();

    // Events
    void e_handleEvents();
    bool e_onTouch();
    bool e_onConnection();
    bool e_onButtonPressedByIndex(const int);
    bool e_onAnyButtonPressed();

    // Statements
    void s_AlwaysOnDisplay();
    void s_WaitingForConnection();
    void s_Menu();

    // Actions
    void a_checkStateApp();
    void a_changeState(utils::States);
};

#endif