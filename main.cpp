/*!
 * @file      main.cpp
 * @brief     Class to manage a stepper motor
 * @details
 * @author    Boyan Bonev
 * @version   0.1
 * @date      02.Nov.2016
 *
 * @copyright
 ******************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "./inc/Std_Types.h"
#include "./inc/CSequenceReader.h"

#define GCODE_FILE              "./examples/simple_form1.rou"
#define TEST_LINE_PATH          "./Test/"

static CSequenceReader parser;

int main()
{
    FILE *fGCodeFileHandle;
    char buff[255];
    uint16 idxLine;

    fGCodeFileHandle = fopen(GCODE_FILE, "r");

    if ( fGCodeFileHandle )
    {
        parser.init();
        printf("FILE: %s\n\n", GCODE_FILE );

        idxLine = 0;
        while ( fgets(buff, sizeof(buff), fGCodeFileHandle) != NULL )
        {
            idxLine++;
            printf("%d: %s\n", idxLine, buff );

            parser.process((uint8*)buff, strlen(buff));
        }

        fclose(fGCodeFileHandle);
        printf("File parsed successfully!!!\n");
    }


    return 0;
}
