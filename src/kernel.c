void kernel_main() {
    const char *str = "Hello from Inicium!";
    char *video_memory = (char *) 0xb8000;

    // Limpa a tela (80x25 = 2000 bytes → 1000 caracteres)
    for (int i = 0; i < 80 * 25; i++) {
        video_memory[i * 2] = ' ';     // caractere
        video_memory[i * 2 + 1] = 0x07; // cor: cinza claro em fundo preto
    }

    // Escreve a string
    for (int i = 0; str[i] != '\0'; i++) {
        video_memory[i * 2] = str[i];
        video_memory[i * 2 + 1] = 0x07;
    }

    while (1);
}
