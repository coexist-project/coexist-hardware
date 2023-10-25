#ifndef UTILS_CPP
#define UTILS_CPP

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_FT6206.h>
#include "env.cpp"

#define TITLE 4
#define PARAGRAPH 2
#define SUBTITLE 2

// ENDPOINT ../espacios/{espacio.name}/?now=true | now > 0
#define ENDPOINT "HTTPS://api.coexist.website/api/v2/espacios/"

#define CANT_BUTTONS 4
#define WIDTH_BUTTON 100
#define HEIGHT_BUTTON 40

namespace utils
{
  typedef unsigned int uint_4;

  class Button
  {
  public:
    Adafruit_GFX_Button methods;
    unsigned width = WIDTH_BUTTON;
    unsigned height = HEIGHT_BUTTON;
    unsigned color;
    unsigned textColor;
    unsigned colorOnPressed;
    char *label = nullptr;

    Button(String _label, uint_4 _color, uint_4 _textColor, uint_4 _colorOnPressed)
    {
      label = (char *)malloc((_label.length() + 1) * sizeof(char));
      strcpy(label, _label.c_str());
      color = _color;
      colorOnPressed = _colorOnPressed;
      textColor = _textColor;
    };

    Button()
    {
      color = 20;
      textColor = 54;
      colorOnPressed = 42;
      label = "asd";
    };
  };

  enum States
  {
    WAITING = 0,
    CONNECTED,
    ALWAYS,
    MENU,
  };

  typedef struct
  {
    String name;
    int capacidad;
  } Espacio;

  typedef struct
  {
    String owner;
    String t_start;
    String t_end;
    String propuesta;
    Espacio espacio;
    int bloques;
  } Reserva;

  typedef struct
  {
    String SSID;
    String password;
  } WiFi;

  typedef struct
  {
    Adafruit_FT6206 *touch = nullptr;
    Adafruit_ILI9341 *surface = nullptr;
    uint_4 *width;
    uint_4 *height;
    uint_4 rotation = 1;

    void clear()
    {
      this->surface->fillScreen(ILI9341_BLACK);
    }

  } Screen;

  typedef struct
  {
    bool connection;
    bool touched;
    bool button;
    bool buttonByIndex[CANT_BUTTONS];
    TS_Point touchPoint;
  } Evento;

  typedef struct
  {
    unsigned long int milliseconds;
  } Time;

  typedef struct
  {
    States actualState = WAITING;
    bool alreadyDisplayed = false;
  } Statement;

}

// Hecha por mi, lo se, soy un capo.
template <typename T>
class List
{
private:
  T *_arr = nullptr;
  unsigned int _size = 0;

public:
  List() : _size(0), _arr(nullptr){};
  List(const int number) : _size(number), _arr(new T[number]){};

  ~List()
  {
    delete[] _arr;
  };

  void resize(int newSize)
  {
    delete[] _arr;
    _arr = new T[newSize];
    _size = newSize;
  };

  unsigned int getSize()
  {
    return _size;
  };

  T &operator[](int index)
  {
    return _arr[index];
  };

  void append(T value)
  {
    T *temp = new T[_size + 1];
    for (int i = 0; i < _size; i++)
    {
      temp[i] = _arr[i];
    }
    temp[_size] = value;
    delete[] _arr;
    _arr = temp;
    _size += 1;
  };
};

#endif