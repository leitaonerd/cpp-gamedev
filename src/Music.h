#include <string.h>
#include <SDL3_mixer/SDL_mixer.h>

class Music{
    private:
        MIX_Audio* audio;
        MIX_Track* track;

    public:
        Music();
        Music(std::string file);
        ~Music();

        void Play(int times = -1);
        void Stop(int msToStop = 1500);
        void Open(std::string file);
        bool IsOpen();
};