#if defined _pp_va_included
    #endinput
#endif
#define _pp_va_included

#include <PawnPlus>

#define va_format format
#define va_printf printf
#define va_format_s str_format
#define va_print_s print_s

stock va_SendClientMessage(playerid, colour, const fmt_str[], {Float,_}:...)
{
    new buf[144];
    new n = numargs();
    switch (n)
    {
        case 3: format(buf, sizeof buf, fmt_str);
        case 4: format(buf, sizeof buf, fmt_str, getarg(3));
        case 5: format(buf, sizeof buf, fmt_str, getarg(3), getarg(4));
        case 6: format(buf, sizeof buf, fmt_str, getarg(3), getarg(4), getarg(5));
        case 7: format(buf, sizeof buf, fmt_str, getarg(3), getarg(4), getarg(5), getarg(6));
        case 8: format(buf, sizeof buf, fmt_str, getarg(3), getarg(4), getarg(5), getarg(6), getarg(7));
        case 9: format(buf, sizeof buf, fmt_str, getarg(3), getarg(4), getarg(5), getarg(6), getarg(7), getarg(8));
        default: format(buf, sizeof buf, fmt_str);
    }
    return SendClientMessage(playerid, colour, buf);
}

stock va_SendClientMessageToAll(colour, const fmt_str[], {Float,_}:...)
{
    new buf[144];
    new n = numargs();
    switch (n)
    {
        case 2: format(buf, sizeof buf, fmt_str);
        case 3: format(buf, sizeof buf, fmt_str, getarg(2));
        case 4: format(buf, sizeof buf, fmt_str, getarg(2), getarg(3));
        case 5: format(buf, sizeof buf, fmt_str, getarg(2), getarg(3), getarg(4));
        case 6: format(buf, sizeof buf, fmt_str, getarg(2), getarg(3), getarg(4), getarg(5));
        case 7: format(buf, sizeof buf, fmt_str, getarg(2), getarg(3), getarg(4), getarg(5), getarg(6));
        case 8: format(buf, sizeof buf, fmt_str, getarg(2), getarg(3), getarg(4), getarg(5), getarg(6), getarg(7));
        default: format(buf, sizeof buf, fmt_str);
    }
    return SendClientMessageToAll(colour, buf);
}