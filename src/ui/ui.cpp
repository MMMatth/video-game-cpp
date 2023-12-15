#include "../../include/ui/ui.hpp"

Button::Button() {
  m_coord = Coord(0, 0);
  m_width = 0;
  m_height = 0;
}

Button::Button(int x, int y, int width, int height, function<void()> action)
    : m_coord(x, y), m_action(action) {
  m_width = width;
  m_height = height;
}

bool Button::isInside(int x, int y) {
  if (x >= m_coord.getX() && x <= m_coord.getX() + m_width &&
      y >= m_coord.getY() && y <= m_coord.getY() + m_height) {
    return true;
  }
  return false;
}

void Button::handle(int mouseX, int mouseY) {
  if (isInside(mouseX, mouseY)) {
    m_action();
  }
}

TextButton::TextButton() : Button() {
  m_color = Color::White;
  m_standardColor = Color::White;
  m_hoverColor = Color::White;
  m_edgeColor = Color::White;
  m_text = "";
  m_textSize = 0;
  m_fontPath = "";
  m_shadow = false;
}

TextButton::TextButton(int x, int y, function<void()> action, Color color,
                       Color hoverColor, Color edgeColor, string text,
                       bool shadow, int textSize, string fontPath)
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
  /* shadow */
  m_shadow = shadow;
}

void TextButton::isHover() { m_color = m_hoverColor; }

void TextButton::isNotHover() { m_color = m_standardColor; }

void TextButton::switchColor() {
  if (m_color == m_standardColor) {
    m_color = m_hoverColor;
  } else {
    m_color = m_standardColor;
  }
}

void TextButton::render(RenderWindow &window, int offSetX, int offSetY) {
  if (m_shadow) {
    drawText(offSetX + m_coord.getX() * WINDOW_WIDTH / CAM_WIDTH + 5,
             offSetY + m_coord.getY() * WINDOW_HEIGHT / CAM_HEIGHT + 5, m_text,
             &window, m_textSize, Color::Black, m_fontPath);
  }
  drawTextWithEdge(offSetX + m_coord.getX() * WINDOW_WIDTH / CAM_WIDTH,
                   offSetY + m_coord.getY() * WINDOW_HEIGHT / CAM_HEIGHT,
                   m_text, &window, m_textSize, m_color, m_edgeColor,
                   m_fontPath);
}

OnOffButton::OnOffButton() : Button() {
  m_sprite = Sprite();
  m_spriteOn = Sprite();
  m_spriteOff = Sprite();
  m_on = false;
}

OnOffButton::OnOffButton(int x, int y, int width, int height,
                         function<void()> action, Sprite spriteOn,
                         Sprite spriteOff, bool on)
    : Button(x, y, width, height, action) {
  m_sprite = spriteOn;
  m_spriteOn = spriteOn;
  m_spriteOff = spriteOff;
  m_on = on;
}

void OnOffButton::switchSprite() { m_on = !m_on; }

void OnOffButton::render(RenderWindow &window, int offSetX, int offSetY) {
  if (m_on)
    m_sprite = m_spriteOn;
  else
    m_sprite = m_spriteOff;
  drawSprites(offSetX + m_coord.getX() * WINDOW_WIDTH / CAM_WIDTH,
              offSetY + m_coord.getY() * WINDOW_HEIGHT / CAM_HEIGHT, m_sprite,
              &window, m_width, m_height);
}

Ui::Ui(RenderWindow &window) : m_window(window) {}