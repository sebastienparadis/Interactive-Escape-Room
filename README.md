#Interactive-Escape-Room

**Uploaded from GitLab as part of ECE198 **

The video presentation of this project demonstrating it fully implemented is available at: https://youtu.be/9e6BA2XxBbc

October 2021 - November 2021

Hardware : STM32 Nucleo-64 development board with STM32F401RE MCU, WS2812B Individually Addressable LED Strip, magnetic reed switches, photoresistor, 7-Segment display, joystick

**Overview **

Includes a game-board which presents a University of Waterloo campus map with many locations, all beginning with different letters. The game is activated when the user places a magnet on the proper first location on the game board using magnetic reed switches. This displays the following location on a 7-segment display. The second, third, and fourth locations require the user to complete LED-based challenges to reveal their next location. These challenges are a reaction time challenge, pattern matching challenge, and "guitar hero" challenge, respectively.

Finally, the fifth pin is not explicitly present a challenge to the player. Instead, the player is required to spell out the last location, E7, in morse code by flashing a provided flashlight towards the map board. This is detected by a photoresistor built into the map at the final location.

The code is designed to continuously loop, detect the right pin positions, and call the proper helper functions to run each challenge. It waits for each challenge to be successfully completed before reading and reacting to the next placement of magnetic pins.

Digital inputs include the reed switches and the joystick's button which only require an “on” or “off,”. Respective GPIO pins are initialized to input mode. For the joystick and photoresistor, a precise input voltage is required. The built-in ADC (analog-digital converter) reads the pins and acquires readable input.

The output of the board is focused around the individually addressable LED strip and the 7 segement display. The 7 segements display is used only to output the first letter of the next location that must be pinned. The led strip is responsable for all other output to the user. The LEDs are driven using a pwm timer which is configured to be run by the DMA controller in order to make the operation of the LEDs non-blocking.

**Reation Time **

After the proper placement of the first two magnets, the reaction-time function is be called. In this challenge, all the LEDs on the strip are flashed, and any input on the joystick is checked for to see the user's reaction time. This is done by comparing the time of the LED flash and the user-input, using the SysTick. The software loops and continues flashing at arbitrary instances, checking if the user's reaction time is within a given interval.

**Pattern Matching **

Once the reaction-time challenge is completed, the software continuously checks for the third pin configuration. It then calls the pattern matching function. A random sequence of flashes of the four sides of the map occurs, with the user expected to repeat the pattern by poiting the joystick in the proper sequence directions. Each of the four sides of the game-board are given integer values. The rand function is called to create a random array of integers from 1 to 4 and is used as an argument to a function that flashes the approriate sides of the board. Next, it reads for user input, storing each direction input as the respective integer. Lastly, the two arrays are compared to veriy if they are identical.

**Guitar Hero **

Once the pattern-matching challenge is complete, the fourth pin locations are checked, and with the correct input, the guitar hero challenge function is be called. This challenge sends a random sequence of moving LEDs from the top of the map to the user, who must press the joystick when the LED is at the joystick. Using hardware timer fired interupts, the movement of the LEDs and the reading of the joystick input can both be done simultaneously. Once the user completes this challenge to 80% accuracy, the final location letter is displayed on the 7-segment.

**Photoresistor Morse Code **

The correct final pin placement is checked. Once this is placed, the morse code challenge function is called. This checks the photoresistor for the correct input of E7 as morse code. By setting an initial "room-light" base-value to the photoresistor, the photoresistor can detect when light is shone and when it ceases being shone. Once additional light is detected, the time value is recorded, and another time value is recorded once the additional light ceases. Taking the difference in these times, the code can determine whether the user shined a "dot" or a "dash". If the user's input corresponds with the desired input, then the system reads for the following member of the morse code of "E7". Otherwise, the morse code challenge restarts.

Once the user completes the morse code challenge successfull, the puzzle ends.
