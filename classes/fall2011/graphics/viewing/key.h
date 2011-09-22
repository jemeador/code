#define DVORAK 0

#if DVORAK
#define KEY_L 'a' /* Key bindings for DVORAK typists. */
#define KEY_R 'e'
#define KEY_D 'j'
#define KEY_U ' '
#define KEY_F ','
#define KEY_B 'o'
#else
#define KEY_L 'a' /* Key bindings for QWERTY typists. */
#define KEY_R 'd'
#define KEY_D 'c'
#define KEY_U ' '
#define KEY_F 'w'
#define KEY_B 's'
#endif
