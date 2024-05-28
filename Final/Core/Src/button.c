	#include "button.h"

	// Define the Button struct
	/*struct Button {
		GPIO_TypeDef* GPIOx;
		uint16_t GPIO_Pin;
		int KeyReg0;
		int KeyReg1;
		int KeyReg2;
		int KeyReg3;
		int TimeOutForKeyPress;
		int button1_flag;
	};*/

	// Function to initialize the button struct
	void initButton(Button* button) {
		// Check if the pointer is valid
		if (button != NULL) {
			// Initialize button variables
			button->KeyReg0 = NORMAL_STATE;
			button->KeyReg1 = NORMAL_STATE;
			button->KeyReg2 = NORMAL_STATE;
			button->KeyReg3 = NORMAL_STATE;
			button->TimeOutForKeyPress = 500;
			button->button1_flag = 0;
			 button->pressDuration = 0; // Initialize press duration

		}
	}

	// Function to check if button 1 is pressed
	int isButtonPressed( Button* button) {
		if (button->button1_flag == 1) {
			button->button1_flag = 0;
			return 1;
		}
		return 0;
	}


	// Function to handle button press
	void subKeyProcess(Button* button) {
	    // TODO: Handle button press
	    button->button1_flag = 1;
	}

	// Function to read button input
	void getKeyInput(Button* button) {
	    button->KeyReg2 = button->KeyReg1;
	    button->KeyReg1 = button->KeyReg0;
	    button->KeyReg0 = HAL_GPIO_ReadPin(button->GPIOx, button->GPIO_Pin);
	    if ((button->KeyReg1 == button->KeyReg0) && (button->KeyReg1 == button->KeyReg2)) {
	        if (button->KeyReg2 != button->KeyReg3) {
	            button->KeyReg3 = button->KeyReg2;
	            if (button->KeyReg3 == PRESSED_STATE) {
	                button->TimeOutForKeyPress = 500;
	                button->pressDuration = 0; // Reset press duration
	                subKeyProcess(button);
	            }
	        } else {
	            button->TimeOutForKeyPress--;
	            if (button->TimeOutForKeyPress == 0) {
	                button->KeyReg3 = NORMAL_STATE;
	            }
	            if (button->KeyReg3 == PRESSED_STATE) {
	                           button->pressDuration++;
	                           if (button->pressDuration >= 300) { // 300 * 10ms = 3 seconds
	                               // Handle long press
	                               button->button1_flag = 2; // Use a different flag for long press
	                               button->pressDuration = 0; // Reset duration to prevent repeated triggers
	                               //button->TimeOutForKeyPress = 500;
	                           }
	                       }
	        }
	    }
	}
