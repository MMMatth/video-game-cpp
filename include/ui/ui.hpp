#ifndef UI_HPP
#define UI_HPP

#include "../utils/coord.hpp"
#include "../utils/draw.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <unordered_map>

using namespace std;
using namespace sf;

class Button {
protected:
  /* position */
  Coord m_coord;
  int m_width, m_height;
  /* action */
  function<void()> m_action;

public:
  Button() {
    m_coord = Coord(0, 0);
    m_width = 0;
    m_height = 0;
  }
  Button(int x, int y, int width, int height, function<void()> action)
      : m_coord(x, y), m_action(action) {
    m_width = width;
    m_height = height;
  }

  bool isInside(int mouseX, int mouseY) {
    if (mouseX >= m_coord.getX() && mouseX <= m_coord.getX() + m_width &&
        mouseY >= m_coord.getY() && mouseY <= m_coord.getY() + m_height) {
      return true;
    }
    return false;
  }

  void handle(int mouseX, int mouseY) {
    if (isInside(mouseX, mouseY)) {
      m_action();
    }
  }

  virtual void render(RenderWindow &window, int camTopX, int camTopY) = 0;
};

class TextButton : public Button {
protected:
  bool m_shadow;
  /* color part */
  Color m_color;
  Color m_standardColor;
  Color m_hoverColor;
  Color m_edgeColor;
  /* text part */
  string m_text;
  int m_textSize;
  string m_fontPath;

public:
  TextButton() : Button() {
    m_shadow = true;
    m_color = Color::White;
    m_standardColor = Color::White;
    m_hoverColor = Color::White;
    m_edgeColor = Color::Black;

    m_text = "";
    m_textSize = 0;
    m_fontPath = "";
  }
  TextButton(int x, int y, function<void()> action, Color color,
             Color hoverColor, Color edgeColor, string text, bool shadow = true,
             int textSize = 30, string fontPath = MINECRAFT_FONT_PATH)
      : Button(x, y, 0, 0, action) {
    /* color */
    m_color = color;
    m_standardColor = color;
    m_hoverColor = hoverColor;
    m_edgeColor = edgeColor;
    /* text */
    m_text = text;
    m_textSize = textSize;
    m_fontPath = fontPath;
    /* width and height */
    m_width = getTextWidth(m_text, m_textSize, m_fontPath) * 1.5;
    m_height = getTextHeight(m_text, m_textSize, m_fontPath) * 2;
  }

  void isHover() { m_color = m_hoverColor; }

  void isNotHover() { m_color = m_standardColor; }

  void switchColor() {
    if (m_color == m_standardColor) {
      m_color = m_hoverColor;
    } else {
      m_color = m_standardColor;
    }
  }

  void render(RenderWindow &window, int camTopX, int camTopY) override {
    if (m_shadow) {
      drawText(camTopX + m_coord.getX() * WINDOW_WIDTH / CAM_WIDTH + 5,
               camTopY + m_coord.getY() * WINDOW_HEIGHT / CAM_HEIGHT + 5,
               m_text, &window, m_textSize, Color::Black, m_fontPath);
    }
    drawTextWithEdge(camTopX + m_coord.getX() * WINDOW_WIDTH / CAM_WIDTH,
                     camTopY + m_coord.getY() * WINDOW_HEIGHT / CAM_HEIGHT,
                     m_text, &window, m_textSize, m_color, m_edgeColor,
                     m_fontPath);
  }
};

class SpriteButton : public Button {
protected:
  Sprite m_sprite;

public:
  SpriteButton() { m_sprite = Sprite(); }
  SpriteButton(int x, int y, int width, int height, function<void()> action,
               Sprite sprite)
      : Button(x, y, width, height, action) {
    m_sprite = sprite;
  }

  void render(RenderWindow &window, int camTopX, int camTopY) override {
    //   m_sprite.setPosition(m_coord.getX(), m_coord.getY());
    //   window.draw(m_sprite);
  }
};

class Ui {
protected:
  RenderWindow &m_window;
  unordered_map<string, SpriteButton> m_spriteButton;
  unordered_map<string, TextButton> m_textBouttons;

public:
  Ui(RenderWindow &window) : m_window(window) {}

  //   virtual void initButtons() = 0;

  //   virtual void handleEvent(Event &event) = 0;

  //   virtual void update() = 0;

  //   virtual void render() = 0;
};

#endif // UI_HPP