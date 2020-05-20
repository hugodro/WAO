#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "commonData.h"

/***************************************
* Implementation: CurrencyValue.
****************************************/

CurrencyValue::CurrencyValue(char *aString)
{
  bool reset= false;

  if (aString != 0) {
    if (*aString != '\0') {
      char *tmpPtr;

      if (isalpha(*aString)) {
        unsigned int strLng;

        tmpPtr= aString;
        while (*tmpPtr != '\0') {
          if (!isalpha(*tmpPtr)) break;
          tmpPtr++;
        }


        strLng= tmpPtr - aString;
        // NOTE: {buffer overflow gard}.
        if (strLng > 79) strLng= 79;
        memcpy(currency, aString, strLng);
        currency[strLng]= '\0';

        if (*tmpPtr != '\0') {
          // Skip until a digit.
          while (*tmpPtr != '\0') {
            if (*tmpPtr == '(')
              negativity= true;
            if (isdigit(*tmpPtr)) break;
            tmpPtr++;
          }
          if (*tmpPtr != '\0') {
            makeIntoBigNumber(tmpPtr, value, decimal);
          }
          else {
            // couldn't find digits in the rest of the string.
            value= 0;
            decimal= 0;
          }
        }
        else {
          // Currency was the only data available.
          value= 0;
          decimal= 0;
          negativity= false;
        }

      }
      else {
        // No currency found at the beginning of the string.
        currency[0]= '\0';
      }

    }
    else
      reset= true;
  }
  else
    reset= true;

  if (reset) {
    currency[0]= '\0';
    value= 0;
    decimal= 0;
    negativity= false;
  }
  textBuffer= 0;
}


CurrencyValue::~CurrencyValue()
{
  delete[] textBuffer;
}


void CurrencyValue::makeIntoBigNumber(char *someText, unsigned long long &value, unsigned int &decimal)
{
  if (someText == 0) {
    value= 0;
    return;
  }

  char *aCursor, *bCursor;

  aCursor= bCursor= someText;
  while (*aCursor != '\0') {
    if (*aCursor == ',') {
    }
    else if (!isdigit(*aCursor))
      break;
    else
      *bCursor++= *aCursor;
    aCursor++;
  }


  if (*aCursor == '.') {
    *aCursor++= '\0';
    if (isdigit(*aCursor))
      decimal= atoi(aCursor);
  }
  else decimal= 0;
  *bCursor= '\0';

  value= strtoll(someText, 0, 10);
}


char *CurrencyValue::asText()
{
  if (textBuffer == 0) {
    unsigned int tmpLng;
    char tmpString[200], format[80];

    strcpy(tmpString, currency);
    if (*currency != '0') {
      strcat(tmpString, " ");
    }
    if (negativity)
      strcat(tmpString, "(");
    tmpLng= strlen(tmpString);
    sprintf(tmpString+tmpLng, "%lld", value);
    if (decimal != 0) {
      tmpLng= strlen(tmpString);
      sprintf(tmpString+tmpLng, ".%d", decimal);
    }
    if (negativity)
      strcat(tmpString, ")");
    tmpLng= strlen(tmpString) + 1;
    textBuffer= new char[tmpLng];
    memcpy(textBuffer, tmpString, tmpLng);
  }

  return textBuffer;
}


long long CurrencyValue::getNumber()
{
  if (negativity)
    return value * (long long)-1;
  else
    return value;
}


int CurrencyValue::getDecimal()
{
  if (negativity)
    return (int)decimal * (int)-1;
  else
    return decimal;
}


/***************************************
* SimpleDate: SimpleDate.
****************************************/

SimpleDate::SimpleDate(char *aString)
{
  fields[0]= fields[1]= fields[2]= 0;
  textBuffer= 0;

  do {
   if (isdigit(*aString)) break;
   aString++;
  } while (*aString != '\0');

  if (*aString == '\0') return;

  // Day:
  if (isdigit(*(aString+1))) {
    fields[0]= (unsigned int)(*aString - 0x030) * 10 + (unsigned int)(*(aString+1) - 0x030);
    aString+= 3;
  }
  else {
    fields[0]= (unsigned int)(*aString - 0x030);
    aString+= 2;
  }

  // Month:
  if (isdigit(*(aString+1))) {
    fields[1]= (unsigned int)(*aString - 0x030) * 10 + (unsigned int)(*(aString+1) - 0x030);
    aString+= 3;
  }
  else {
    fields[1]= (unsigned int)(*aString - 0x030);
    aString+= 2;
  }

  // Year:
  unsigned int nbrDigits= 0, multiplier= 1;

  if (isdigit(*aString)) {
    nbrDigits++;
    if (isdigit(*(aString+1))) {
      nbrDigits++;
      if (isdigit(*(aString+2))) {
        nbrDigits++;
        if (isdigit(*(aString+3))) {
          nbrDigits++;
        }
      }
    }
  }

  for (unsigned int i= 1; i < nbrDigits; i++)
    multiplier*= 10;

  fields[2]= 0;
  for (unsigned int i= nbrDigits; i > 0; i--) {
    fields[2]+= (unsigned int)(*aString - 0x030) * multiplier;
    aString++;
    multiplier/= 10;
  }
}


SimpleDate::~SimpleDate()
{
//TODO.
  delete[] textBuffer;
}


char *SimpleDate::asText()
{
  if (textBuffer == 0) {
    textBuffer= new char[11];
    if (fields[0] == 0) {
      strcpy(textBuffer, "null");
    }
    else
      sprintf(textBuffer, "%04d/%02d/%02d", fields[2], fields[1], fields[0]);
  }
  return textBuffer;
}


