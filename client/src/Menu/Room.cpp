#include "Room.hpp"
#include "TextSFML.hpp"
#include "ImageSFML.hpp"

static int num = 0;

void addItems(vector<shared_ptr<Button>> &roomlist) {
    roomlist.push_back(make_shared<Button>(sf::Vector2f(955 - 125, 250 + (num * 110)), sf::Vector2f(250, 100)));
    roomlist[num]->setColor(sf::Color::Black, sf::Color::White, 5);
    roomlist[num]->setText("./resources/fonts/2MASS.otf", "R. " + to_string(num + 1), 75, sf::Color::White);
    num += 1;
}

RoomMenu::RoomMenu(string name) {
    _name = "";
    isMenu = true;

    // A REMOVE -- POUR TEST
    addItems(roomlist);
    addItems(roomlist);
    addItems(roomlist);
    addItems(roomlist);
    addItems(roomlist);
    addItems(roomlist);
    // FIN DU REMOVE -- POUR TEST
}
RoomMenu::~RoomMenu() {}

string RoomMenu::loop(shared_ptr<sf::RenderWindow> _window) {
    ImageSFML back("./resources/sprites/mainbackground.png");
    TextSfml name_txt("Pseudo: " + _name, "./resources/fonts/2MASS.otf", sf::Color::White, 600, 25);

    _window->setFramerateLimit(60);
    while(_window->isOpen() && isMenu) {
        EventHandler(_window);

        name_txt.setString("Pseudo: " + _name);
        name_txt.setPosition(sf::Vector2f(875 - ((_name.length() / 2) * 14), 25));

        _window->draw(*back.getSprite());
        _window->draw(*name_txt.getData());
        for (size_t i = 0; i < roomlist.size(); i ++)
            roomlist[i]->drawButton(_window);
        _window->display();
        _window->clear();
    }
    return _name;
}

void RoomMenu::EventHandler(shared_ptr<sf::RenderWindow> _window) {
    sf::Event event;

    while(_window->pollEvent(event)) {
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == 59 && _name.length() > 0)
                _name = _name.substr(0, _name.length() - 1);
            else if (event.key.code < 26 && event.key.shift)
                _name = _name + (char)(event.key.code + 65);
            else if (event.key.code < 26)
                _name = _name + (char)(event.key.code + 97);
            else if (event.key.code == 57)
                _name = _name + " ";
        } for (size_t i = 0; i < roomlist.size(); i ++) {
            if (roomlist[i]->isClicked(event))
                cout << "Clicked on room " << i + 1 << endl;
        }
    }
}