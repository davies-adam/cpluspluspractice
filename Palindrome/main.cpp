#include <cctype>
#include <iostream>

void copy(char *destination, char *origin, int start, int end)
{
    for (int i = 0; i < end; i++)
    {
        destination[i + start] = origin[i];
    }
    return;
}

void encode_letter(char input, char *output, int head, int size)
{
    switch (input)
    {
    case 'a':
    {
        char result[] = {'0', '.', '.', '.', '.', '.'};
        copy(output, result, head, size);
        break;
    }
    case 'b':
    {
        char result[] = {'0', '0', '.', '.', '.', '.'};
        copy(output, result, head, size);
        break;
    }
    case 'c':
    {
        char result[] = {'0', '.', '.', '0', '.', '.'};
        copy(output, result, head, size);
        break;
    }
    case 'd':
    {
        char result[] = {'0', '.', '.', '0', '0', '.'};
        copy(output, result, head, size);
        break;
    }
    case 'e':
    {
        char result[] = {'0', '.', '.', '.', '0', '.'};
        copy(output, result, head, size);
        break;
    }
    case 'f':
    {
        char result[] = {'0', '0', '.', '0', '.', '.'};
        copy(output, result, head, size);
        break;
    }
    case 'g':
    {
        char result[] = {'0', '0', '.', '0', '0', '.'};
        copy(output, result, head, size);
        break;
    }
    case 'h':
    {
        char result[] = {'0', '0', '.', '.', '0', '.'};
        copy(output, result, head, size);
        break;
    }
    case 'i':
    {
        char result[] = {'.', '0', '.', '0', '.', '.'};
        copy(output, result, head, size);
        break;
    }
    case 'j':
    {
        char result[] = {'.', '0', '.', '0', '0', '.'};
        copy(output, result, head, size);
        break;
    }
    case 'k':
    {
        char result[] = {'0', '.', '0', '.', '.', '.'};
        copy(output, result, head, size);
        break;
    }
    case 'l':
    {
        char result[] = {'0', '0', '0', '.', '.', '.'};
        copy(output, result, head, size);
        break;
    }
    case 'm':
    {
        char result[] = {'0', '.', '0', '0', '.', '.'};
        copy(output, result, head, size);
        break;
    }
    case 'n':
    {
        char result[] = {'0', '.', '0', '0', '0', '.'};
        copy(output, result, head, size);
        break;
    }
    case 'o':
    {
        char result[] = {'0', '.', '0', '.', '0', '.'};
        copy(output, result, head, size);
        break;
    }
    case 'p':
    {
        char result[] = {'0', '0', '0', '0', '.', '.'};
        copy(output, result, head, size);
        break;
    }
    case 'q':
    {
        char result[] = {'0', '0', '0', '0', '0', '.'};
        copy(output, result, head, size);
        break;
    }
    case 'r':
    {
        char result[] = {'0', '0', '0', '.', '0', '.'};
        copy(output, result, head, size);
        break;
    }
    case 's':
    {
        char result[] = {'.', '0', '0', '0', '.', '.'};
        copy(output, result, head, size);
        break;
    }
    case 't':
    {
        char result[] = {'.', '0', '0', '0', '0', '.'};
        copy(output, result, head, size);
        break;
    }
    case 'u':
    {
        char result[] = {'0', '.', '0', '.', '.', '0'};
        copy(output, result, head, size);
        break;
    }
    case 'v':
    {
        char result[] = {'0', '0', '0', '.', '.', '0'};
        copy(output, result, head, size);
        break;
    }
    case 'w':
    {
        char result[] = {'.', '0', '.', '0', '0', '0'};
        copy(output, result, head, size);
        break;
    }
    case 'x':
    {
        char result[] = {'0', '.', '0', '0', '.', '0'};
        copy(output, result, head, size);
        break;
    }
    case 'y':
    {
        char result[] = {'0', '.', '0', '0', '0', '0'};
        copy(output, result, head, size);
        break;
    }
    case 'z':
    {
        char result[] = {'0', '.', '0', '.', '0', '0'};
        copy(output, result, head, size);
        break;
    }
    }
}

int encode_character(char input, char *output)
{

    int size = 6;
    int head = 0;
    if (isalpha(input))
    {
        if (isupper(input))
        {
            char capital_sign[] = {'.', '.', '.', '.', '.', '0'};
            copy(output, capital_sign, head, size);
            size = 12;
            head = 6;
            input = tolower(input);
        }
        encode_letter(input, output, head, size);
    }
    else if (isdigit(input))
    {
        char number_sign[] = {'.', '.', '0', '0', '0', '0'};
        copy(output, number_sign, head, size);
        size = 12;
        head = 6;
        if (input == '0')
        {
            encode_letter('j', output, head, size);
        }
        else
        {
            char letter_equiv = static_cast<char>(input - '0' + 'a' - 1);
            encode_letter(letter_equiv, output, head, size);
        }
    }
    else if (ispunct(input))
    {
        switch (input)
        {
        case ('.'):
        {
            char result[] = {'.', '0', '.', '.', '0', '0'};
            copy(output, result, head, size);
            break;
        }
        case (','):
        {
            char result[] = {'.', '0', '.', '.', '.', '.'};
            copy(output, result, head, size);
            break;
        }
        case (';'):
        {
            char result[] = {'.', '0', '0', '.', '.', '.'};
            copy(output, result, head, size);
            break;
        }
        case ('-'):
        {
            char result[] = {'.', '.', '0', '.', '.', '0'};
            copy(output, result, head, size);
            break;
        }
        case ('!'):
        {
            char result[] = {'.', '0', '0', '.', '0', '.'};
            copy(output, result, head, size);
            break;
        }
        case ('?'):
        {
            char result[] = {'.', '0', '0', '.', '.', '0'};
            copy(output, result, head, size);
            break;
        }
        case ('('):
        case (')'):
        {
            char result[] = {'.', '0', '0', '.', '0', '0'};
            copy(output, result, head, size);
            break;
        }
        }
    }
    else
    {
        return 0;
    }
    return size;
}

bool encode(const char *str, char *output, int offset = 0)
{
    if (*str == '\0')
    {
        return true;
    }
    int size = encode_character(*str, output + offset);
    return encode(str + 1, output, offset + size);
}

void print_braille(const char *plaintext, std::ostream &output)
{
    char toprint[4][100] = {};
    int text_index = 0;
    int out_index = 0;
    int label_index = 0;
    while(plaintext[text_index] != '\0')
    {
        char coded[12];
        int size = encode_character(plaintext[text_index], coded);
        for(int i = 0; i < size; i++)
        {
            if(i != 0 && (i % 3) == 0)
            {
                out_index++;
            }
            std::cout << "(" << i % 3 << ", " << out_index << ") " << coded[i] << std::endl;
            toprint[i % 3][out_index] = coded[i];
        }
        if(size == 12) 
        {
            toprint[3][label_index] = ' ';
            label_index++;
            toprint[3][label_index] = ' ';
            label_index++;
            toprint[3][label_index] = ' ';
            label_index++;
        }
        toprint[3][label_index] = plaintext[text_index];
        out_index++;
        label_index++;
        toprint[3][label_index] = ' ';
        label_index++;
        toprint[3][label_index] = ' ';
        text_index++;
    }
    for(int row = 0; row < 4; row++) 
    {
        for(int column = 0; column < 100; column++)
        {
            output << toprint[row][column];
            if(column % 2) {
                output << " ";
            }
        }
        output << std::endl;
    }
}

int main()
{
    print_braille("Hello!", std::cout);
    return 0;
}