#ifndef CREADER_H
#define CREADER_H

#pragma once

#include <Windows.h>
#include <stdio.h>
#include <string.h>

#define MAXLINES 25
#define MAXLINELENGHT 128

/** Our loved Class :D */
class cReader {

    private:
        /** Pointer to the FILE structure used to manipulate our file */
        FILE* File;
        /** The read content (The not commented lines) */
        char Content[MAXLINES][MAXLINELENGHT];

        /* FIXME: strtrim should change the string instead of creating a new one to avoid bad memory management? */
        /** Remove the spaces of a string and return the new one */
        char* strtrim ( const char* str );
        /** Get the Field value from a specific line. Used by GetFieldValue(). */
        char* GetValueFromLine ( int Line );
        /** Gets the decimal value from a Hex char (e.g. B = 11). Used by GetHexColorFromString(). */
        int HexToInt ( char c );

    public:
        /** Checks if the file (named by the FILENAME) exists. If yes, open it. */
        bool OpenFile(const char* FileName);
        /** Read the file. Skipping commented/empty lines */
        void ReadFile();
        /** Print what was read by ReadFile(). */
        void PrintReadContent();
        /** Returns the value of the specified field. */
        char* GetFieldValue ( const char* Field );
        /** Translates a Hex String (read from the file) to a Hex Number and returns it. */
        DWORD GetHexColorFromString ( const char* ColorString );
        /** Translates a Hex String (read from the file) to a Vec4 array. */
        void GetFloatColorFromString ( const char* ColorString, Color ColorRet );
        /** Same as GetFloatColorFromString() but uses a Hex Number instead of a string */
        void HexColorToFloat ( DWORD C, Color ColorRet );
        /** Create a new config file. Usage can be like if(!OpenFile()) CreateNewConfigFile(); */
        void CreateNewConfigFile(const char* FileName);
};

#endif // CREADER_H
