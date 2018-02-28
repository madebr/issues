int do_sdl2(int, char **);

int main(int argc, char **argv) {
    int res;

    res |= do_sdl2(argc, argv);
    return res;
}
