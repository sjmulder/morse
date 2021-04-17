morse
=====
Generate and parse morse code encoded as dots and dashes

**morse** [**-d**]

Reads text from standard input, outputs dots and dashes on standard
output. The **-d** flag (for *decode*) reverses the process.

Un-encodable or un-decodable input is skipped. Words in morse are
separated with newlines.

morse-pwmplay
-------------
Output morse on a passive buzzer with PWM

**morse-pwmplay** [*chip* [**channel**]]

On Linux only, with boards such as the Raspberry Pi, this utility can
play the morse output on a passive buzzer.

It reads dots, dashes, spaces and newlines (as wod separators) from
standard input and interfaces with the sysfs interface at
*/sys/class/pwm/pwmchipN/pwmN*. Other input characters are ignored.
The chip and channel numbers default to 0. The dot length is fixed at
50 ms.

For the Raspberry Pi, sample set up is as follows:

 1. Add `dtoverlay=pwm` to */boot/config.txt* and reboot.
 2. Connect GPIO 18 to one pin of a passive buzzer.
 3. Connect GND to the other pin of the buzzer.

Examples
--------
    $ echo 'Hello, World! What a day to be alive.' | morse
    .... . .-.. .-.. ---
    .-- --- .-. .-.. -..
    .-- .... .- -
    .-
    -.. .- -.--
    - ---
    -... .
    .- .-.. .. ...- .

    $ echo 'Hello, World! What a day to be alive.' | morse >msg.txt
    $ morse -d <msg.txt
    HELLO WORLD WHAT A DAY TO BE ALIVE
    
    $ morse-pwmplay <msg.txt
    <Noise from buzzer>

Building
--------
Should build on any Unix (but *morse-pwmplay* will only work on Linux).
See the Makefile for more variables.

    make
    make install   [PREFIX=/usr/local]
    make uninstall [PREFIX=/usr/local]

Legal
-----
By Sijmen J. Mulder (<ik@sjmulder.nl>). See LICENSE.md.
