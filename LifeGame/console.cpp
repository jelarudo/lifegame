#include <stdio.h>
#include <string>


namespace Console {
    namespace Display
    {
        static void setPosition(int x, int y)
        {
            printf("\033[%d;%dH", y, x);
        }

        static void flush()
        {
            fflush(stdout);
        }

        static void clear()
        {
            printf("\033\[2J");
        }

        static void write(const char * outPutString)
        {
            printf("%s", outPutString);
        }

        static void writeLine(const char * outPutString)
        {
            write((std::string(outPutString) + "\n").c_str());
        }
    }
}
