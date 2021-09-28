#include <stdio.h>
#include <string.h>
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

#define A  0b0000010000000000
#define B  0b0000000010000000
#define C  0b0000000000100000
#define D  0b0000000000000001
#define E  0b0000000100000000
#define F  0b0000001000000000
#define G  0b0000000000000100
#define DP 0b0000000001000000
#define D6 0b0000000000000010
#define D5 0b0000000000001000
#define D4 0b0000000000010000
#define D0 0b0000100000000000
#define D3 0b0001000000000000
#define D7 0b0010000000000000
#define D2 0b0100000000000000
#define D1 0b1000000000000000
#define D_OFF D0+D1+D2+D3+D4+D5+D6+D7

std::array<char, 16> seven_segment_float_to_command(float a) {

    char d7 = (int(a)%1000000) / 100000 ;
    char d6 = (int(a)%100000) / 10000 ;
    char d5 = (int(a)%10000) / 1000 ;
    char d4 = (int(a)%1000)  / 100  ;
    char d3 = (int(a)%100)   / 10   ;
    char d2 = (int(a)%10)           ;
    char d1 = (int(a*10)  % 10)     ;
    char d0 = (int(a*100) % 10)      ;  
    
    const uint16_t DS[8] = {D_OFF-D0, 
                            D_OFF-D1, 
                            D_OFF-D2, 
                            D_OFF-D3, 
                            D_OFF-D4, 
                            D_OFF-D5, 
                            D_OFF-D6, 
                            D_OFF-D7};
    char char_buf[8] = {d7,d6,d5,d4,d3,d2,d1,d0};
    std::array<char, 16> command;
    uint8_t j;
    j = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        char character = char_buf[i];
        switch (character) {
            case 0:
                command[2*j] = (A+B+C+D+E+F+DS[j])>>8;
                command[2*j+1] = (A+B+C+D+E+F+DS[j])&0xff;
                j++;
                break;
            case 1:
                command[2*j] = (B+C+DS[j])>>8;
                command[2*j+1] = (B+C+DS[j])&0xff;
                j++;
                break;
            case 2:
                command[2*j] = (A+B+G+E+D+DS[j])>>8;
                command[2*j+1] = (A+B+G+E+D+DS[j])&0xff;
                j++;
                break;
            case 3:
                command[2*j] = (A+B+G+C+D+DS[j])>>8;
                command[2*j+1] =  (A+B+G+C+D+DS[j])&0xff;
                j++;
                break;
            case 4:
                command[2*j] = (F+G+B+C+DS[j])>>8;
                command[2*j+1] =  (F+G+B+C+DS[j])&0xff;
                j++;
                break;
            case 5:
                command[2*j] = (A+F+G+C+D+DS[j])>>8;
                command[2*j+1] = (A+F+G+C+D+DS[j])&0xff;
                j++;
                break;
            case 6:
                command[2*j] = (A+F+G+E+D+C+DS[j])>>8;
                command[2*j+1] =(A+F+G+E+D+C+DS[j])&0xff;
                j++;
                break;
            case 7:
                command[2*j] = (A+B+C+DS[j])>>8;
                command[2*j+1] =(A+B+C+DS[j])&0xff;
                j++;
                break;
            case 8:
                command[2*j] = (A+B+C+D+E+F+G+DS[j])>>8;
                command[2*j+1] =(A+B+C+D+E+F+G+DS[j])&0xff;
                j++;
                break;
            case 9:
                command[2*j] = (A+B+C+F+G+DS[j])>>8;
                command[2*j+1] =(A+B+C+F+G+DS[j])&0xff;
                j++;
                break;
            default:
                command[2*j] = D_OFF>>8;
                command[2*j+1] =  D_OFF&0xff;
                j++;
                 break;
        }
        
    }
    
    command[2*5] = command[2*5] + (DP>>8);
    command[2*5+1] =  command[2*5+1] + (DP&0xff);

        
    
    
    return command;
}