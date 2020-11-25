#include <HID-Project.h>
#include <ClickEncoder.h>
#include <TimerOne.h>
#include "layout.h"

//change encoder[X] with the number of encoders that you have installed
ClickEncoder *encoder[2];
int16_t encoderLast, encoderValue;

void timerIsr()
{
	encoder[0]->service();
	encoder[1]->service();
}

//Customizable keyboard values
int longPressDelay = 350;
int spamSpeed = 15;

void setup()
{
	//Declaring all the outputs and setting them high
	for (int i = 0; i < outCount; i++)
	{
		pinMode(outputs[i], OUTPUT);
		digitalWrite(outputs[i], HIGH);
	}
	//Declaring all the inputs and activating the internal pullup resistor
	for (int i = 0; i < inCount; i++)
	{
		pinMode(inputs[i], INPUT_PULLUP);
	}

	//Begin Keyboard (uses normal char) and Consumer (used for media and shortcut stuff)
	Consumer.begin();
	Keyboard.begin();

	//Initializing the encoders
	encoder[0] = new ClickEncoder(15, 14, 9, 4);
	encoder[0]->setAccelerationEnabled(true);
	//In my case the second encoder button is used for resetting the MCU.
	//Since it's not used I declared a random unused pin to bypass that.
	encoder[1] = new ClickEncoder(16, 10, 99, 4);
	encoder[1]->setAccelerationEnabled(true);
	Timer1.initialize(1000);
	Timer1.attachInterrupt(timerIsr);
	encoderLast = -1;
}

void loop()
{
	for (int i = 0; i < outCount; i++)
	{
		digitalWrite(outputs[i], LOW);
		//Wait a bit for logic level change
		delayMicroseconds(5);

		for (int j = 0; j < inCount; j++)
		{
			//Check if any button is pressed
			if (digitalRead(inputs[j]) == LOW)
			{
				keyPressed(i, j);
			}
			//Reset key if not pressed anymore
			else if (keyDown[i][j] != 0)
			{
				resetKey(i, j);
			}
		}

		digitalWrite(outputs[i], HIGH);
		delayMicroseconds(350);
	}
	checkEncoder(0);
	checkEncoder(1);
}

//Send keystroke
void keyPressed(int row, int col)
{
	//First time press for this key
	if (keyDown[layoutSelect][row][col] == 0)
	{
		Keyboard.write(layout[layoutSelect][row][col]);
	}
	//set flag for future use in spam
	else if (keyLong[layoutSelect][row][col] && keyDown[layoutSelect][row][col] > spamSpeed)
	{
		Keyboard.write(layout[layoutSelect][row][col]);
		keyDown[layoutSelect][row][col] = 1;
	}
	//If a key held more than longPressDelay begin the spam
	else if (keyDown[layoutSelect][row][col] > longPressDelay)
	{
		keyLong[layoutSelect][row][col] = true;
	}

	keyDown[layoutSelect][row][col]++;
}

//Reset variables after key release
void resetKey(int row, int col)
{
	keyDown[layoutSelect][row][col] = 0;
	keyLong[layoutSelect][row][col] = false;
}

//Function to check if the encoder has been used, if yes, it sends appropriate keys
void checkEncoder(int select)
{
	encoderValue = encoder[select]->getValue();

	if (encoderValue != encoderLast)
	{
		encoderLast = encoderValue;
		if (encoderValue == 1)
		{
			//Keyboard.write(lEncoderChar);
			Consumer.write(rotary[select][layoutSelect][1]);
		}
		else if (encoderValue == -1)
		{
			//Keyboard.write(rEncoderChar);
			Consumer.write(rotary[select][layoutSelect][0]);
		}
	}

	ClickEncoder::Button b = encoder[select]->getButton();
	if (b != ClickEncoder::Open)
	{
#define VERBOSECASE(label)      \
	case label:                 \
		Serial.println(#label); \
		break;
		switch (b)
		{
			VERBOSECASE(ClickEncoder::Pressed);
			VERBOSECASE(ClickEncoder::Held)
			VERBOSECASE(ClickEncoder::Released)
		case ClickEncoder::Clicked:
			Consumer.write(rotary[select][layoutSelect][2]);
			break;
		case ClickEncoder::DoubleClicked:
			if (layoutSelect < 3)
			{
				layoutSelect++;
				Keyboard.print((String) "Layer No. " + layoutSelect);
			}
			else
			{
				layoutSelect = 0;
				Keyboard.print((String) "Layer No. " + layoutSelect);
			}
			break;
		}
	}
}