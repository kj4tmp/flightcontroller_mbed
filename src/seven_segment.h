#include <stdio.h>
/*
10 9 8 7 6

    A  
  F    B
     G 
  E    C
    D     DP

1 2 3 4 5
Anodes:
A B C D E F G DP
7 6 4 2 1 9 10 5
Cathodes: 3,8
*/
char * seven_segment_float_to_command(float a) {
    const uint16_t A =   0b0000010000000000;
    const uint16_t B =   0b0000000010000000;
    const uint16_t C =   0b0000010000000000;
    const uint16_t D =   0b0000000000000001;
    const uint16_t E =   0b0000000100000000;
    const uint16_t F =   0b0000001000000000;
    const uint16_t G =   0b0000000000000100;
    const uint16_t DP =  0b0000000001000000;
    const uint16_t D_OFF =  D0+D1+D2+D3+D4+D5+D6+D7;
    const uint16_t D6 =  D_OFF - 0b0000000000000010;
    const uint16_t D5 =  D_OFF - 0b0000000000001000;
    const uint16_t D4 =  D_OFF - 0b0000000000010000;
    const uint16_t D0 =  D_OFF - 0b0000100000000000;
    const uint16_t D3 =  D_OFF - 0b0001000000000000;
    const uint16_t D7 =  D_OFF - 0b0010000000000000;
    const uint16_t D2 =  D_OFF - 0b0100000000000000;
    const uint16_t D1 =  D_OFF - 0b1000000000000000;
    const uint16_t DS[8] = {D0, D1, D2, D3, D4, D5, D6, D7};
    char char_buf[9];
    sprintf(char_buf, "%.8g", a);
    char command[16];
    uint8_t j;
    j = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        char character = char_buf[i];
        switch (character) {
            case '0':
                command[2*j] = (A+B+C+D+E+F+DS[j])&0xffff>>8;
                command[2*j+1] = (A+B+C+D+E+F+DS[j])&0xff;
                j++;
                break;
            case '1':
                command[2*j] = (B+C+DS[j])&0xffff>>8;
                command[2*j+1] = (B+C+DS[j])&0xff;
                j++;
                break;
            case '2':
                command[2*j] = (A+B+G+E+D+DS[j])&0xffff>>8;
                command[2*j+1] = (A+B+G+E+D+DS[j])&0xff;
                j++;
                break;
            case '3':
                    command[2*j] = (A+B+G+C+D+DS[j])&0xffff>>8;
                    command[2*j+1] =  (A+B+G+C+D+DS[j])&0xff;
                    j++;
                    break;
            case '4':
                command[2*j] = (F+G+B+C+DS[j])&0xffff>>8;
                command[2*j+1] =  (F+G+B+C+DS[j])&0xff;
                j++;
                break;
            case '5':
                command[2*j] = (A+F+G+C+D+DS[j])&0xffff>>8;
                command[2*j+1] = (A+F+G+C+D+DS[j])&0xff;
                j++;
                break;
            case '6':
                command[2*j] = (A+F+G+E+D+C+DS[j])&0xffff>>8;
                command[2*j+1] =(A+F+G+E+D+C+DS[j])&0xff;
                j++;
                break;
            case '7':
                command[2*j] = (A+B+C+DS[j])&0xffff>>8;
                command[2*j+1] =(A+B+C+DS[j])&0xff;
                j++;
                break;
            case '8':
                command[2*j] = (A+B+C+D+E+F+G+DS[j])&0xffff>>8;
                command[2*j+1] =(A+B+C+D+E+F+G+DS[j])&0xff;
                j++;
                break;
            case '9':
                command[2*j] = (A+B+C+F+G+DS[j])&0xffff>>8;
                command[2*j+1] =(A+B+C+F+G+DS[j])&0xff;
                j++;
                break;
            case '.':
                command[2*j] = (command[j*2] + (DP & 0xffff))>>8;
                command[2*j+1] = command[j*2+1] + (DP&0xff);
                break;
        }
    }
    
    
    return command;
}