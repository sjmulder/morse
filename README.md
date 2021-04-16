morse
=====
Generate and parse morse code encoded as dots and dashes.

**morse** [**-d**]

Reads text from standard input, outputs dots and dashes on standard
output. The **-d** flag (for *decode*) reverses the process.

Un-encodable or un-decodable input is skipped. Words in morse are
separated with newlines.

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

Building
--------
`make`.

Legal
-----
By Sijmen J. Mulder (<ik@sjmulder.nl>). See LICENSE.md.
