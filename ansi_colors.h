#ifndef ANSI_COLORS_H
#define ANSI_COLORS_H

//biblioteca criada para facilitar a utilização do ccódigo ANSI para colorir o terminal
//João Antônio Guerim Guasso
// baseado em https://gist.github.com/JBlond/2fea43a3049b38287e5e9cefc87b2124

// Cores de texto
#define TEXT_BLACK "\033[0;30m"
#define TEXT_RED "\033[0;31m"
#define TEXT_GREEN "\033[0;32m"
#define TEXT_YELLOW "\033[0;33m"
#define TEXT_BLUE "\033[0;34m"
#define TEXT_PURPLE "\033[0;35m"
#define TEXT_CYAN "\033[0;36m"
#define TEXT_WHITE "\033[0;37m"
/*high intensity*/
#define TEXT_H_BLACK "\033[0;90m"
#define TEXT_H_RED "\033[0;91m"
#define TEXT_H_GREEN "\033[0;92m"
#define TEXT_H_YELLOW "\033[0;93m"
#define TEXT_H_BLUE "\033[0;94m"
#define TEXT_H_PURPLE "\033[0;95m"
#define TEXT_H_CYAN "\033[0;96m"
#define TEXT_H_WHITE "\033[0;97m"

// Cores de fundo
#define BG_BLACK "\033[40m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_PURPLE "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"
/*high intensity*/
#define BG_H_BLACK "\033[100m"
#define BG_H_RED "\033[101m"
#define BG_H_GREEN "\033[102m"
#define BG_H_YELLOW "\033[103m"
#define BG_H_BLUE "\033[104m"
#define BG_H_PURPLE "\033[105m"
#define BG_H_CYAN "\033[106m"
#define BG_H_WHITE "\033[107m"

// Efeitos
#define TEXT_BOLD "\033[1m"
#define TEXT_FAINT "\033[2m"
#define TEXT_ITALIC "\033[3m"
#define TEXT_UNDERLINE "\033[4m"
#define TEXT_BLINK "\033[5m"
#define TEXT_BLINK_RAPID "\033[6m" //por enquanto ele piscou na mesma velocidade
#define TEXT_REVERSE "\033[7m"
#define TEXT_CONCEALED "\033[8m" //o texto some, não sei oq faz
#define TEXT_CROSSEDOUT "\033[9m"

// Reset
#define RESET "\033[0m"

#endif // ANSI_COLORS_H
