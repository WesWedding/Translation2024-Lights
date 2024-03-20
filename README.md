# Sample no. 43 (Lights Driver)
2024 NWACC SACF Entry w/ Tabitha Darrah

This is the code that drives the Lights in Tabitha Darrah and Weston Wedding's 2024 submission to the NWACC Spring Arts and Culture Festival.  This year's theme is Translation! This code can be (with some modification) run on any Arduino-like hardware but this project, as is, has been written with some underlying assumptions about Hardware and Software.  

This code requires another device running the sister code: [Sample no. 43 (Touch Driver)](https://github.com/WesWedding/Translation2024-Touch) or it won't really do much.

## Summary of Behavior
The lion's share of the codebase is devoted to animation of a single LED strand that is divided into several logical segments that animate differently.  An I2C child device is polled many times a second in order to evaluate the child's current state of activity, and as the child's state changes in response to user touches this Lights device will play an appropriate extended lights animation.

The child device reports its internal state with a single char, one of the following:

  - "0": The "attract" or "idle" waiting state.  This will gently pulse/throb the first segment of LEDs, positioned around a touch area used to activate the artwork.
  - "1": The "single touch" state, which pulses a light toward the beginning of LED segment 2 in order to encourage a 2nd touch to happen in an appropriate region of the ceramic work.
  - "2": The "fully active" state, which plays a long 30+ second animation that matches a mp3 audio file played by the Touch device.  Blips of random light matches the gentle rainfall, while blue and gold colors fade in and out to match 2 frogs that are calling out to eachother for the duration of the audio file.  It all culminates in a brilliant flash of light to match a rolling thunder that finishes the audio file.
  - "3": Pretty much a brief "do nothing" state entered into by the touch device, transitional between more active states.

## Usage
Without modifications, this codebase assumes that there is a a NeoPixel strip wired to a Huzzah on digital pin 12.  This NeoPixel strip is assumed to be 60 pixels long.

### NeoPixel strip length (LED count)

This code was developed using a much smaller strip of pixels; 16 LEDs.  This is hidden behind a preprocessor definition, `DEV_ENV`

If `#define DEV_ENV` is un-commented, this alternative development environment configuration is used instead.  This reduced the amount of lines the remote ceramics artist would have to maintain on her own, and have to keep track of every time they pulled a code update.

Modify the following defines to match your actual LED counts and corresponding "segments" to animate.

`#define LED_COUNT  16`

```cpp
#define STRIP_SEG1_START 0
#define STRIP_SEG1_END   5
#define STRIP_SEG2_START 7
#define STRIP_SEG2_END   12
```

## Expected Hardware
In addition to the usual wires, jumpers, breadboards, and solder common to any Arduino project this codebase was written explicitly with a few pieces of hardware in mind (take note of the HUZZAH, especially).

### [Adafruit Feather HUZZAH](https://www.adafruit.com/product/2821)
This project expects to run on a Feather Huzzah or equivalent; digital pins used may need to be modified and an explicit call to esp8266 PolledTimeout would need to be replaced in order to use a different board.  Something with a lot of extra RAM is probably necessary; sketch size is considerable and a lot of dynamically-allocated objects are generated to manage LED animation logic.

You may need to get additional drivers in order to use this hardware, as well as the ESP8266 package.  See Adafruit's [Using the Arduino IDE page](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide) for more information.

### [Adafruit NeoPixels](https://www.adafruit.com/category/168)
Any kind of NeoPixel string will work; the library is maintained and updated by Adafruit often.  The code assumes a GRB NeoPixel string, you may need to update the code to reflect your NeoPixels of choice (e.g. `Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800)`).

### I2C bi-directional logic level shifter
Any I2C-friendly bi-directional logic level shifter is required (assuming the Touch component is 5V logic like ours).  Either the [Adafruit BSS1388](https://www.adafruit.com/product/757) or [Sparkfun BOB-12009](https://www.sparkfun.com/products/12009) worked great during implemtation! 

## Expected Software or Libraries
In addition to using your IDE of choice (VSCode, Arduino IDE 2.0, etc) you'll need some libraries in order to successfully compile.  One of the libraries is not currently on the Arduino Library Manager (yet), and will require some additional steps.

### ESP8266 Board Package
This code uses a PolledTimeout class, available via the ESP8266 board library.  This class is available when compiling for the Adafruit Feather HUZZAH, but would require a replacement if you are trying to compile for another board.

### Adafruit_NeoPixel
The library to make the NeoPixels do their thing; not much explanation required.  Get it via the Arduino Library Manager or Github here: https://github.com/adafruit/Adafruit_NeoPixel.

### Tweenduino (manual install required)
This library enables the use of "Tweens" and series of Tweens called Timelines, to change values over time without the use of loops.  This is used to change colors, brightnesses, and other things in the LED animations. This requires a manual install (for now, see: [Review requirements to to add to library registry](https://github.com/WesWedding/TweenDuino/issues/30)) [in an appropriate directory on your filesystem](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries/#manual-installation).

### Easing
Tweenduino depends heavily on the Easing library.  Easings are the magic that drive tweens, and help determine the "curve" a value change follows between its current value and final value.  Get it via the Arduino Library Manager or Github here: https://github.com/hideakitai/Easing.

### Wire

I2C with the Touch board is a core feature of this driver, which requires the Wire library.

## Credits
This driver is written by Weston Wedding.

## License
This driver is free software; you can redistribute it and/or modify it under the terms of the the MIT License.  For full details, check out the [COPYING](COPYING.md) file in this sourcecode or the explanation of [MIT License here](https://tlo.mit.edu/understand-ip/exploring-mit-open-source-license-comprehensive-guide).

