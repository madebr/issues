int do_boost(int, char **);

int main(int argc, char **argv) {
    int res;

    res |= do_boost(argc, argv);
    return res;
}
