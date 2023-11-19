#ifndef STEXT
#define STEXT

class streamText : public Text
{
public:
    streamText();
    streamText(std::string, std::string, int size, SDL_Color);
    ~streamText();
    std::stringstream stream;

    template <typename T>
    streamText& operator<<(T inString);
};

streamText::streamText() : Text(){}

streamText::streamText(std::string fontType, std::string initString, int size, SDL_Color textColor)
: Text(fontType, initString, size, textColor)
{
    stream.str(initString);
}

streamText::~streamText()
{
    TTF_CloseFont(font);
    textTexture.free();
    font = NULL;
}

template <typename T>
streamText& streamText::operator<<(T inString)
{
    stream.str("");
    stream << textString << inString;
    textTexture.loadFromRenderedText(stream.str().c_str(), textColor, font);
}
#endif // STEXT
