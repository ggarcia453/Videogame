#ifndef SETTINGS_HPP
#define SETTINGS_HPP

class Settings{
    private:
        bool musicOn;
        bool buffer;
    public:
        Settings();
        void check_changes();
        const bool playMusic() const;

};

#endif