#include "app.h"

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_FT6206.h>
#include <WiFi.h>
#include "utils.cpp"
#include "env.cpp"

const char *ssid = "Wokwi-GUEST";
const char *password = "";

/*  PRINCIPAL FUNCTIONS   */
bool App::p_init()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password, 6);
    // Initialize variables
    // Screen
    this->m_screen.touch = new Adafruit_FT6206();
    this->m_screen.surface = new Adafruit_ILI9341(TFT_CS, TFT_DC);

    {
        this->m_screen.surface->begin();
        this->m_screen.touch->begin(40);

        this->m_screen.surface->setRotation(this->m_screen.rotation);
        this->m_screen.surface->setTextColor(ILI9341_WHITE);
        this->m_screen.surface->setTextSize(2);

        this->m_screen.width = new unsigned int(this->m_screen.surface->width());
        this->m_screen.height = new unsigned int(this->m_screen.surface->height());

#if DEBUG_MODE == 1
        this->m_screen.surface->print(this->m_screen.surface->width());
        this->m_screen.surface->print("\n");
        this->m_screen.surface->print(this->m_screen.surface->height());
        delay(5000);
#endif
    }

    // Init Buttons
    {
        for (int row = 0; row < CANT_BUTTONS / 2; row++)
        {
            for (int col = 0; col < 2; col++)
            {
                int index = row * 2 + col;
                utils::Button button(String(index), 500, 200, 34);
                button.methods.initButtonUL(
                    m_screen.surface,
                    col * button.width ,
                    row * button.height + (index < 2? 80 : (button.height + 80)),
                    button.width, button.height,
                    ILI9341_WHITE, button.color, button.textColor, button.label, PARAGRAPH);
                m_buttons.append(button);
            }
        }
    }

    // TODO
    /*
      El archivo va a guardar la SSID y password del wifi que se ingreso.
      Si el archivo esta vacio, el m_statement.state pasa a ser WatingForConnection.
      ReadFile();
    */

    this->a_checkStateApp();
    return true;
}

void App::p_run()
{
    // handle events
    this->e_handleEvents();

    // Check if state must change
    this->a_checkStateApp();

    // do state
    (this->*this->m_stateFunction)();
}

/*  EVENT FUNCTIONS   */
// FIND BUTTON BY INDEX
bool App::e_onButtonPressedByIndex(const int index)
{
    if (index > m_buttons.getSize() || index < 0)
        return false;

    if (m_buttons[index].methods.contains(m_events.touchPoint.x, m_events.touchPoint.y))
        return true;

    return false;
}

bool App::e_onAnyButtonPressed()
{
    for (int i = 0; i < m_buttons.getSize(); i++)
        if (this->m_events.buttonByIndex[i])
            return true;
    return false;
}

void App::e_handleEvents()
{
    this->m_events.connection = this->e_onConnection();
    this->m_events.touched = this->e_onTouch();

    if (!this->m_events.touched)
        return;

    for (int i = 0; i < m_buttons.getSize(); i++)
    {
        this->m_events.buttonByIndex[i] = this->e_onButtonPressedByIndex(i);
    }
    this->m_events.button = this->e_onAnyButtonPressed();
#if DEBUG_MODE == 1
    if (this->m_events.buttonByIndex[0])
        Serial.print("Button index 0 pressed");
#endif
}

bool App::e_onConnection()
{
    if (WiFi.status() == WL_CONNECTED)
        return true;
    else
        return false;
}

bool App::e_onTouch()
{
    if (this->m_screen.touch->touched())
    {
        this->m_events.touchPoint = this->m_screen.touch->getPoint();
        if (this->m_screen.rotation % 2)
            this->m_events.touchPoint = {this->m_events.touchPoint.y, *this->m_screen.height - this->m_events.touchPoint.x, this->m_events.touchPoint.z};
        else
            this->m_events.touchPoint = {this->m_events.touchPoint.x, this->m_events.touchPoint.y, this->m_events.touchPoint.z};
#if DEBUG_MODE == 1
        // Si esto pasa debo invertir las coordenadas
        Serial.print("x: ");
        Serial.println(this->m_events.touchPoint.x);
        Serial.print("y: ");
        Serial.println(*this->m_screen.height - this->m_events.touchPoint.x);

        // Draw rect to debug
        if (this->m_screen.rotation % 2)
            this->m_screen.surface->fillRect(this->m_events.touchPoint.y, *this->m_screen.height - this->m_events.touchPoint.x, 10, 10, ILI9341_WHITE);
        else
            this->m_screen.surface->fillRect(this->m_events.touchPoint.x, this->m_events.touchPoint.y, 10, 10, ILI9341_WHITE);
#endif
        return true;
    }

    this->m_events.touchPoint = {0, 0, 0};
    return false;
}

/*  ACTIONS FUNCTIONS   */

void App::a_changeState(utils::States _state)
{
    this->m_statement.actualState = _state;
    switch (_state)
    {
    case utils::WAITING:
        this->m_stateFunction = &App::s_WaitingForConnection;
        break;
    case utils::ALWAYS:
        this->m_stateFunction = &App::s_AlwaysOnDisplay;
        break;
    case utils::MENU:
        this->m_stateFunction = &App::s_Menu;
    default:
        break;
    }
    this->m_statement.alreadyDisplayed = false;
}

void App::a_checkStateApp()
{
    switch (this->m_statement.actualState)
    {
    case utils::WAITING:
        if (m_events.connection)
            this->a_changeState(utils::CONNECTED);
        break;
    case utils::CONNECTED:
        this->m_screen.surface->print("\nConnected!");
        delay(500);
        this->a_changeState(utils::ALWAYS);
        break;
    case utils::ALWAYS:
        if (m_events.touched)
        {
            this->a_changeState(utils::MENU);
            this->m_time.milliseconds = millis();
        }
        break;
    case utils::MENU:
        // Reinicio el conteo
        if (this->m_events.touched)
            this->m_time.milliseconds = millis();

        // Chequeo si ya paso el tiempo de inactividad
        if (millis() >= this->m_time.milliseconds + TIME_ON_MENU * 1000)
        {
            this->a_changeState(utils::ALWAYS);
        }
        break;
    default:
        break;
    }
}

/*  STATES FUNCTIONS   */

void App::s_AlwaysOnDisplay()
{
    if (this->m_statement.alreadyDisplayed)
        return;

    this->m_screen.clear();
    this->m_screen.surface->setCursor(0, 100);
    this->m_screen.surface->setTextSize(TITLE);
    this->m_screen.surface->print(this->m_reserva->espacio.name);
    this->m_screen.surface->drawFastHLine(0, 140, *this->m_screen.width, ILI9341_WHITE);

    // Si la reserva tiene una cantidad de bloques distinta a cero
    // Significa que el espacio tiene una reserva.
    if (this->m_reserva->bloques != 0)
    {
        this->m_screen.surface->setCursor(0, 150);
        this->m_screen.surface->setTextSize(PARAGRAPH);
        this->m_screen.surface->println(this->m_reserva->owner);
        this->m_screen.surface->println(this->m_reserva->propuesta);
        this->m_screen.surface->print(this->m_reserva->t_start);
        this->m_screen.surface->print(" -> ");
        this->m_screen.surface->print(this->m_reserva->t_end);
        this->m_screen.surface->print(" | ");
        this->m_screen.surface->println(this->m_reserva->bloques);
    }
    else
    {
        this->m_screen.surface->setCursor(0, 150);
        this->m_screen.surface->setTextSize(PARAGRAPH);
        this->m_screen.surface->print("Actualmente el espacio no posee ninguna reserva.");
    }

    this->m_statement.alreadyDisplayed = true;
}

void App::s_Menu()
{
    if (this->m_statement.alreadyDisplayed)
        return;

    String title = "MENU";

    this->m_screen.clear();
    this->m_screen.surface->setCursor(((*m_screen.width) / 2) - title.length() * PARAGRAPH * 5, 10);
    this->m_screen.surface->print(title);
    this->m_screen.surface->drawFastHLine(0, 40, *m_screen.width, ILI9341_WHITE);

    for (int i = 0; i < this->m_buttons.getSize(); i++)
        m_buttons[i].methods.drawButton();

    this->m_statement.alreadyDisplayed = true;
}

void App::s_WaitingForConnection()
{
    if (this->m_statement.alreadyDisplayed)
        return;

    this->m_screen.surface->setCursor(0, 0);
    this->m_screen.surface->println("Waiting for connection..");
    this->m_statement.alreadyDisplayed = true;
}