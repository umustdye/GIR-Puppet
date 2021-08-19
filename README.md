# GIR-Puppet
Arduino Code for GIR Puppet. GIR is a character from the Nickledoen show Invader Zim, created by Jhonen Vasquez. Invader Zim was my favorite show growing up, so when I heard about the movie coming out in 2019, I decided to make a puppet of GIR to show my respect. The puppet has RGB LEDs that light up either red or blue based on if he is in slave mode or not. There is also a soundboard with eleven different GIR sayings from the show. When "GIR, reporting for duty is pressed" GIR goes into slave mode for the duration of the audio clip. The physical puppet can open its mouth and squint its eyes. All control is done inside his head. The head can be opened via he top of a zipper encloser in the back. The arms are controlled via arm rods. He has his dog costume which he can wear as well. I do have pictures of the puppet and a demonstration of the lights and soundboard which can be viewed using the link below. 

[See puppet development and the electronic-side demonstration](https://photos.app.goo.gl/zHn9fzXsvYNPt4DD8) 

## Software and hardware specifics ##

Includes one button library to change RGB LED from red to blue. Hold the botton down for three seconds to turn off the LEDs. 
Note: the LEDs used for this project were common cathode

Includes DF Player Mini to play up to ten GIR sound files. I have included a few edited GIR sounds from the show. I do not own the rights to the sound files. I am using this as personal use and I suggest you do the same. Each sound file can be played using a certain button. This is sort of like a sound board .
For the DF Player mini, make sure to have your sound files saved in the folder titled "mp3"
Each of the sound files you use must start with the numbering system 000-???. See the included mp3 file for reference.

For wiring, please refer to the code. There is also a wiring sheet diagram included [here](https://photos.app.goo.gl/krgFajUrMZVpeLBfA) as well. The board used is an Arduino Uno.
