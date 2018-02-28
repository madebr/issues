int do_openal(int, char **);

int main(int argc, char **argv) {
    int res;

    res |= do_openal(argc, argv);
    return res;
}
