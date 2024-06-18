#include <Arduino.h>
#include <math.h>

// put function declarations here:
void myFunction(int x, int y, char method);
int num1, num2;
char method;
String inputString = "";
boolean stringComplete = false;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  inputString.reserve(200);
  Serial.println("Welcome to the calculator!");
  Serial.println("Please enter a number and a method");
  Serial.println("You can use +, -, *, /, %, ^, e, and for log use l, for sin use s, for cos use c, for tan use t, for square root use r");
}

void loop()
{
  if (stringComplete)
  {
    // Clear the string when COM receiving is completed
    inputString.trim(); // Remove any leading/trailing whitespace
    stringComplete = false;

    // Find the position of the operator
    int operatorPosition = -1;
    char operators[] = "+-*/%^!elscrt";
    for (int i = 0; i < sizeof(operators) - 1; i++)
    {
      operatorPosition = inputString.indexOf(operators[i]);
      if (operatorPosition != -1)
      {
        method = operators[i];
        break;
      }
    }

    if (operatorPosition != -1)
    {
      num1 = inputString.substring(0, operatorPosition).toInt();
      num2 = inputString.substring(operatorPosition + 1).toInt();
      myFunction(num1, num2, method);
    }
    else
    {
      Serial.println("Invalid input. Please enter in the format: number1 operator number2");
      Serial.println("If only one digit is needed, please add a 0 before the method");
    }

    // Clear the input string
    inputString = "";
  }

  // Check if there is data available
  if (Serial.available())
  {
    // Read the data:
    char inChar = (char)Serial.read();

    // add incoming byte to inputString
    inputString += inChar;

    // If the incoming character is a newline, set a flag
    if (inChar == '\n')
    {
      stringComplete = true;
    }
  }
}

// put function definitions here:
void myFunction(int x, int y, char method)
{
  double result;
  String outputMessage;
  // Get the method
  if (method == '+')
  {
    outputMessage = "The sum of " + String(x) + " and " + String(y) + " is ";
    result = x + y;
  }
  else if (method == '-')
  {
    outputMessage = "The difference of " + String(x) + " and " + String(y) + " is ";
    result = x - y;
  }
  else if (method == '*')
  {
    outputMessage = "The product of " + String(x) + " and " + String(y) + " is ";
    result = x * y;
  }
  else if (method == '/')
  {
    if (y != 0)
    { // Check for divide by zero
      outputMessage = "The quotient of " + String(x) + " and " + String(y) + " is ";
      result = x / y;
    }
    else
    {
      // Blink red rx LED and display error message
      outputMessage = "You can't divide by zero";
      result = NAN;
      for (int i = 0; i < 10; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
      }
    }
  }
  else if (method == '%')
  {
    outputMessage = "The remainder of " + String(x) + " and " + String(y) + " is ";
    result = x % y;
  }
  else if (method == '^')
  {
    outputMessage = "The power of " + String(x) + " and " + String(y) + " is ";
    result = round(pow(x, y));
  }
  else if (method == '!')
  {
    outputMessage = "We can't calculate factorials yet";
    result = NAN;
    for (int i = 0; i < 10; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
      }
  }
  else if (method == 'e')
  {
    outputMessage = "The exponential of " + String(y) + " is ";
    result = exp(y);
  }
  else if (method == 'l')
  {
    outputMessage = "The natural log of " + String(y) + " is ";
    result = log(y);
  }
  else if (method == 's')
  {
    outputMessage = "The sine of " + String(y) + " is ";
    result = sin(y);
  }
  else if (method == 'c')
  {
    outputMessage = "The cosine of " + String(y) + " is ";
    result = cos(y);
  }
  else if (method == 't')
  {
    outputMessage = "The tangent of " + String(y) + " is ";
    result = tan(y);
  }
  else if (method == 'r')
  {
    outputMessage = "The square root of " + String(y) + " is ";
    result = sqrt(y);
  }
  else
  {
    outputMessage = "Unknown method";
    result = NAN;
    for (int i = 0; i < 10; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
      }
  }
  Serial.println(outputMessage);
  Serial.println(result);
}