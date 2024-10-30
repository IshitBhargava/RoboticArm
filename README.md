# RoboticArm

Build a robotic arm easily and control it using a Mobile App!

# Things Needed:

<pre>To make this, you need:
1x Arduino NANO
1x HC-05 OR HC-06
1x Breadboard (Or you can use the PCB)
3x SG90 Servo
3x MG995 Servo
1x USB Cable
4x Buttons (Optional)
3x 3 milimeter LEDs
</pre>

<pre>You will also need a Mechanical model of the arm. Sources are attached below:
If you do not have a 3D printer:</pre> https://amzn.in/d/92INVpi <pre>
If you do have a 3D printer: 
</pre>
__________________________________________________________________________________________

# Connections:

**Servo 1 (Grab):**
<pre>VCC: Vin
GND: GND
SIGNAL: D5
</pre>


**Servo 2 (Wrist Pitch):**
<pre>VCC: Vin
GND: GND
SIGNAL: D6
</pre>


**Servo 3 (Wrist Roll):**
<pre>VCC: Vin
GND: GND
SIGNAL: D3
</pre>


**Servo 4 (Elbow):**
<pre>VCC: Vin
GND: GND
SIGNAL: D9
</pre>


**Servo 5 (Shoulder):**
<pre>VCC: Vin
GND: GND
SIGNAL: D10
</pre>


**Servo 6 (Base):**
<pre>VCC: Vin
GND: GND
SIGNAL: D11
</pre>


**HC-05/ HC-06 (Bluetooth):**
<pre>VCC: Vin
GND: GND
TX: D2
RX: D4
</pre>

**LED 1:**
<pre>VCC: A0
GND: GND
</pre>

**LED 2:**
<pre>VCC: A1
GND: GND
</pre>

**LED 3:**
<pre>VCC: A2
GND: GND
</pre>

**Button 1:**
<pre>Terminal 1: 7
Terminal 2: GND
</pre>

**Button 2:**
<pre>Terminal 1: 8
Terminal 2: GND
</pre>

**Button 3:**
<pre>Terminal 1: 12
Terminal 2: GND
</pre>

**Button 4:**
<pre>Terminal 1: 13
Terminal 2: GND
</pre>

**Button 5:**
<pre>Terminal 1: RST
Terminal 2: GND
</pre>

**USB Cable:**
<pre>5V: Vin
Negative: GND
</pre>

__________________________________________________________

# Steps:

<pre>
Firstly, upload the code to the Arduino NANO board. Note that you have to connect extra power cable before you connect the arduino.
Second, Assemble the robotic arm using the User Manual. I suggest writing all Servos to 90 Debrees before assembling. You also may need to sand down the Servo horns. Using a rubber band in the shoulder servo will be quite helpful.
Third, Power it on and all servos should move.
Fourth, open the app and connect to the bluetooth module. Use the sliders to move and the 'Update Values' button to move Servos. The save positons and play movements buttons can be used for moving autonomously.
Fifth, enjoy the robotic arm!
</pre>

