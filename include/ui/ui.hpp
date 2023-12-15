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

/** @brief a class who represent a button */
class Button {
protected:
  Coord m_coord;             /** position of the button */
  int m_width, m_height;     /** width and height of the button */
  function<void()> m_action; /** action of the button */

public:
  /** @brief default constructor */
  Button();

  /** @brief constructor with param */
  Button(int x, int y, int width, int height, function<void()> action);

  /** @brief a function who return true if the x and y is in the button
   * @param x the x coord (in pixel) a mouse for example
   * @param y the y coord (in pixel) a mouse for example
   */
  bool isInside(int x, int y);

  /** @brief a function who handle the button
   * @param mouseX the x coord (in pixel) a mouse for example
   * @param mouseY the y coord (in pixel) a mouse for example
   */
  void handle(int mouseX, int mouseY);
  /** @brief a vitrual function for the render */
  virtual void render(RenderWindow &window, int offSetX = 0,
                      int offSetY = 0) = 0;
};

/** @brief class who implement a text button (herite from button )*/
class TextButton : public Button {
protected:
  bool m_shadow; /** if the button have a shadow */
  /* color part */
  Color m_color;         /** current color of the button */
  Color m_standardColor; /** standard color of the button */
  Color m_hoverColor;    /** color when the mouse is hover the button */
  Color m_edgeColor;     /** color of the edge of the button */
  /* text part */
  string m_text;     /** text of the button */
  int m_textSize;    /** size of the text */
  string m_fontPath; /** path of the font */

public:
  /** @brief default constructor */
  TextButton();

  /** @brief constructor
   * @param x the x coord (in pixel) of the button
   * @param y the y coord (in pixel) of the button
   * @param action the action of the button
   * @param color the color of the button
   * @param hoverColor the color when the mouse is hover the button
   * @param edgeColor the color of the edge of the button
   * @param text the text of the button
   * @param shadow if the button have a shadow
   * @param textSize the size of the text
   * @param fontPath the path of the font
   */
  TextButton(int x, int y, function<void()> action, Color color,
             Color hoverColor, Color edgeColor, string text, bool shadow = true,
             int textSize = 30, string fontPath = MINECRAFT_FONT_PATH);

  /** @brief function when is called change the color to the hover color */
  void isHover();

  /** @brief function when is called change the color to the standard color */
  void isNotHover();

  /** @brief function who switch the color of the button */
  void switchColor();

  /** @brief a function who render the button (override from button)
   * @param window the window where the button is render
   * @param offSetX  x offset of the button (in pixel) (0 by default)
   * @param offSetY  y offset of the button (in pixel) (0 by default)
   */
  void render(RenderWindow &window, int offSetX, int offSetY) override;
};

/** @brief class who implement a sprite button (herite from button )*/
class OnOffButton : public Button {
protected:
  Sprite m_sprite;    /** current sprite of the button */
  Sprite m_spriteOn;  /** sprite when the button is on */
  Sprite m_spriteOff; /** sprite when the button is off */
  bool m_on;          /** if the button is on */

public:
  /** @brief default constructor */
  OnOffButton();

  /** @brief  constructor
   * @param x the x coord (in pixel) of the button
   * @param y the y coord (in pixel) of the button
   * @param width the width of the button
   * @param height the height of the button
   * @param action the action of the button
   * @param spriteOn the sprite when the button is on
   * @param spriteOff the sprite when the button is off
   * @param on if the button is on
   */
  OnOffButton(int x, int y, int width, int height, function<void()> action,
              Sprite spriteOn, Sprite spriteOff, bool on = true);

  /** @brief function who switch the state of the button */
  void switchSprite();

  /** @brief a function who render the button (override from button)
   * @param window the window where the button is render
   * @param offSetX the x offset of the button (in pixel) (0 by default)
   * @param offSetY the y offset of the button (in pixel) (0 by default)
   */
  void render(RenderWindow &window, int offSetX, int offSetY) override;
};

/** @brief class who represent a ui */
class Ui {
protected:
  RenderWindow &m_window; /**  the window where the ui is render */
  unordered_map<string, OnOffButton> m_OnOffButton; /** many OnOffButton */
  unordered_map<string, TextButton> m_textBouttons; /** many TextButton */

public:
  /** @brief constructor
   * @param window the window where the ui is render
   */
  Ui(RenderWindow &window);
};

#endif // UI_HPP