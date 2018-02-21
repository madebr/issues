int do_boost(int, char **);
int do_bullet(int, char **);
int do_ffmpeg(int, char **);
int do_openal(int, char **);
int do_sdl2(int, char **);

int main(int argc, char **argv) {
    int res;

    res |= do_boost(argc, argv);
    res |= do_bullet(argc, argv);
    res |= do_ffmpeg(argc, argv);
    res |= do_openal(argc, argv);
    res |= do_sdl2(argc, argv);
    return res;
}
