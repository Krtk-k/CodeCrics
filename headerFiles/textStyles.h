#pragma once // Prevents multiple inclusions

// ANSI escape sequences for text styles
// Reset
#define RESET          "\033[0m"

// Text Styles
#define BOLD          "\033[1m"
#define DIM           "\033[2m"
#define ITALIC        "\033[3m"   // Not supported in some terminals
#define UNDERLINE     "\033[4m"
#define BLINK         "\033[5m"
#define FAST_BLINK    "\033[6m"
#define REVERSE       "\033[7m"
#define HIDDEN        "\033[8m"
#define STRIKETHROUGH "\033[9m"
#define DOUBLE_UNDERLINE "\033[1m\033[4m"
#define OVERLINE      "\033[53m"

// Text Colors
#define BLACK        "\033[30m"
#define RED          "\033[31m"
#define GREEN        "\033[32m"
#define YELLOW       "\033[33m"
#define BLUE         "\033[34m"
#define MAGENTA      "\033[35m"
#define CYAN         "\033[36m"
#define WHITE        "\033[37m"

// Bright Text Colors
#define BRIGHT_BLACK   "\033[90m"
#define BRIGHT_RED     "\033[91m"
#define BRIGHT_GREEN   "\033[92m"
#define BRIGHT_YELLOW  "\033[93m"
#define BRIGHT_BLUE    "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN    "\033[96m"
#define BRIGHT_WHITE   "\033[97m"

// 256-Color Text
#define ORANGE       "\033[38;5;214m"
#define PINK         "\033[38;5;206m"
#define PURPLE       "\033[38;5;129m"
#define GOLD         "\033[38;5;220m"
#define TEAL         "\033[38;5;31m"

// Background Colors
#define BG_BLACK     "\033[40m"
#define BG_RED       "\033[41m"
#define BG_GREEN     "\033[42m"
#define BG_YELLOW    "\033[43m"
#define BG_BLUE      "\033[44m"
#define BG_MAGENTA   "\033[45m"
#define BG_CYAN      "\033[46m"
#define BG_WHITE     "\033[47m"

// Bright Background Colors
#define BG_BRIGHT_BLACK   "\033[100m"
#define BG_BRIGHT_RED     "\033[101m"
#define BG_BRIGHT_GREEN   "\033[102m"
#define BG_BRIGHT_YELLOW  "\033[103m"
#define BG_BRIGHT_BLUE    "\033[104m"
#define BG_BRIGHT_MAGENTA "\033[105m"
#define BG_BRIGHT_CYAN    "\033[106m"
#define BG_BRIGHT_WHITE   "\033[107m"

// Default Text & Background
#define DEFAULT_TEXT   "\033[39m"   // Reset to default text color
#define DEFAULT_BG     "\033[49m"   // Reset to default background color