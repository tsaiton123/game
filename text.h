#ifndef TEXT
#define TEXT

#include <string>

class Text{
protected:

    TTF_Font *font;
    LTexture textTexture;
    SDL_Color textColor;
    int size;

public:
    Text();
    Text(std::string, std::string, int size, SDL_Color);
    ~Text();
    std::string textString;

    void renderText(int, int);
    void editSize(int);
    void editColor(SDL_Color);
    void editString(std::string);
    Text& operator+(Text&);
    Text& operator+(std::string);
};

Text::Text()
{
    font = NULL;
    textString = "";
}

Text::Text(std::string fontType, std::string textString, int size, SDL_Color textColor)
{
    this->font = TTF_OpenFont( fontType.c_str(), size );
    this->size = size;
    this->textString = textString;
    this->textColor = textColor;
    textTexture.loadFromRenderedText(textString, textColor, font);
}

Text::~Text()
{
    TTF_CloseFont(font);
    textTexture.free();
    font = NULL;
}

void Text::renderText(int x, int y)
{
    textTexture.render(x, y);
}

void Text::editSize(int size)
{
    this->size = size;
}

void Text::editColor(SDL_Color color)
{
    textColor = color;
}

void Text::editString(std::string str)
{
    textString = str;
}

Text& Text::operator+(Text& textToAdd)
{
    this->textString = this->textString + textToAdd.textString;
    textTexture.loadFromRenderedText(textString, textColor, font);
    return *this;
}

Text& Text::operator+(std::string str)
{
    this->textString = this->textString + str;
    textTexture.loadFromRenderedText(textString, textColor, font);
    return *this;
}

#endif // TEXT
