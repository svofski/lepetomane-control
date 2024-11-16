/*
    Copyright 2001, 2002 Georges Menie (www.menie.org)
    stdarg version contributed by Christian Ettinger

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/*
    putchar is the only external dependency for this file,
    if you have a working putchar, leave it commented out.
    If not, uncomment the define below and
    replace outbyte(c) by your own function call.

#define putchar(c) outbyte(c)
*/

#include <stdarg.h>

#if 1

#include "xprintf.h"

#ifdef HAL_USART
#include "usrat.h"
// HAL callbacks
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

}

#define BUFFER_SIZE 32

volatile static int TxPPActive = 0;
volatile static uint8_t TxBufferPP[2][BUFFER_SIZE];
volatile static int TxSizePP[2];

static UART_HandleTypeDef* DebugUART;

void xprintf_uart(UART_HandleTypeDef *huart) 
{
    DebugUART = huart;
    TxPPActive = 0;
    TxSizePP[0] = TxSizePP[1] = 0;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    TxSizePP[TxPPActive] = 0;
    int next = TxPPActive + 1;
    if (next == 2) {
        next = 0;
    }
    if (TxSizePP[next]) {
        TxPPActive = next;
        HAL_UART_Transmit_IT(huart, TxBufferPP[TxPPActive], TxSizePP[TxPPActive]);
    }
}

// #define ENTER_CRITICAL() __HAL_UART_DISABLE_IT(huart, UART_IT_TXE); __HAL_UART_DISABLE_IT(huart, UART_IT_TC);
// #define EXIT_CRITICAL() __HAL_UART_ENABLE_IT(huart, UART_IT_TXE); __HAL_UART_ENABLE_IT(huart, UART_IT_TC);
#define ENTER_CRITICAL() __disable_irq()
#define EXIT_CRITICAL() __enable_irq()

static void uputchar(UART_HandleTypeDef *huart, char c) 
{
    int next = TxPPActive;

    uint32_t state = huart->State;

    for(;;) {
        if (TxSizePP[next] == 0) {
            TxBufferPP[next][0] = (uint8_t) c;
            TxSizePP[next] = 1;
            HAL_UART_Transmit_IT(huart, TxBufferPP[next], 1);
        } else {
            next = TxPPActive + 1;
            if (next == 2) {
                next = 0;
            }
            // if room available, put char in the buffer and exit
            ENTER_CRITICAL();
            if (TxSizePP[next] < BUFFER_SIZE) {
                TxBufferPP[next][TxSizePP[next]] = (uint8_t) c;
                TxSizePP[next]++;
                EXIT_CRITICAL();
            } else {
                EXIT_CRITICAL();
                // if not, wait until the currently active buffer is purged and use it
                next = TxPPActive;
                while(TxSizePP[next] > 0); // block until TX completion
                continue;
            }
        }
        break;
    }
}

#endif

static void printchar(char **str, int c)
{
    extern int cdc_putchar(int ch);

    if (str) {
        **str = c;
        ++(*str);
    } else {
        #ifdef HAL_USART
        uputchar(DebugUART, c);
        #else
        //xputchar(c);
        cdc_putchar(c);
        //if (c == '\n') {
        //    cdc_putchar('\r');
        //}
        #endif
    }
}

#define PAD_RIGHT 1
#define PAD_ZERO 2
#define PAD_PLUS 4

static int prints(char **out, const char *string, int width, int pad)
{
    register int pc = 0, padchar = ' ';

    if (width > 0) {
        register int len = 0;
        register const char *ptr;
        for (ptr = string; *ptr; ++ptr) ++len;
        if (len >= width) width = 0;
        else width -= len;
        if (pad & PAD_ZERO) padchar = '0';
    }
    if (!(pad & PAD_RIGHT)) {
        for ( ; width > 0; --width) {
            printchar (out, padchar);
            ++pc;
        }
    }
    for ( ; *string ; ++string) {
        printchar (out, *string);
        ++pc;
    }
    for ( ; width > 0; --width) {
        printchar (out, padchar);
        ++pc;
    }

    return pc;
}

/* the following should be enough for 32 bit int */
#define PRINT_BUF_LEN 12

static int printi(char **out, int i, int b, int sg, int width, int pad, int letbase)
{
    char print_buf[PRINT_BUF_LEN];
    register char *s;
    register int t, neg = 0, pc = 0;
    register unsigned int u = i;

    if (i == 0) {
        print_buf[0] = '0';
        print_buf[1] = '\0';
        return prints (out, print_buf, width, pad);
    }

    if (sg && b == 10 && i < 0) {
        neg = 1;
        u = -i;
    }

    s = print_buf + PRINT_BUF_LEN-1;
    *s = '\0';

    while (u) {
        t = u % b;
        if( t >= 10 )
            t += letbase - '0' - 10;
        *--s = t + '0';
        u /= b;
    }

    if (neg) {
        if( width && (pad & PAD_ZERO) ) {
            printchar (out, '-');
            ++pc;
            --width;
        }
        else {
            *--s = '-';
        }
    } else {
        if (pad & PAD_PLUS) {
            *--s = '+';
        }
    }

    return pc + prints (out, s, width, pad);
}

static int print(char **out, const char *format, va_list args )
{
    register int width, pad;
    register int pc = 0;
    char scr[2];

    for (; *format != 0; ++format) {
        if (*format == '%') {
            ++format;
            width = pad = 0;
            if (*format == '\0') break;
            if (*format == '%') goto out;
            if (*format == '-') {
                ++format;
                pad = PAD_RIGHT;
            }
            if (*format == '+') {
                ++format;
                pad |= PAD_PLUS;
            }
            while (*format == '0') {
                ++format;
                pad |= PAD_ZERO;
            }
            for ( ; *format >= '0' && *format <= '9'; ++format) {
                width *= 10;
                width += *format - '0';
            }
            if( *format == 's' ) {
                register char *s = (char *)va_arg( args, int );
                pc += prints (out, s?s:"(null)", width, pad);
                continue;
            }
            if( *format == 'd' ) {
                pc += printi (out, va_arg( args, int ), 10, 1, width, pad, 'a');
                continue;
            }
            if( *format == 'x' ) {
                pc += printi (out, va_arg( args, int ), 16, 0, width, pad, 'a');
                continue;
            }
            if( *format == 'X' ) {
                pc += printi (out, va_arg( args, int ), 16, 0, width, pad, 'A');
                continue;
            }
            if( *format == 'u' ) {
                pc += printi (out, va_arg( args, int ), 10, 0, width, pad, 'a');
                continue;
            }
            if( *format == 'c' ) {
                /* char are converted to int then pushed on the stack */
                scr[0] = (char)va_arg( args, int );
                scr[1] = '\0';
                pc += prints (out, scr, width, pad);
                continue;
            }
        }
        else {
        out:
            printchar (out, *format);
            ++pc;
        }
    }
    if (out) **out = '\0';
    va_end( args );
    return pc;
}

int xprintf(const char *format, ...)
{
        va_list args;
        
        va_start( args, format );
        return print( 0, format, args );
}

int xsprintf(char *out, const char *format, ...)
{
        va_list args;
        
        va_start( args, format );
        return print( &out, format, args );
}

#endif
