# AT90S8515 or ATMEGA163 based digital clock

Firmware files for digital clock using a DS3231 RTC board.

This came about from my experiments with these two AVR chips I had lying around, described at https://hackaday.io/page/399337 and https://hackaday.io/page/399353 It is in fact mostly the same clock firmware as https://github.com/retiredfeline/89c52-clock It should work on the ATMEGA164 and more recent chip models with adjustment for a different clock frequency, but I have not tested (and don't intend to test) this. Have at it.

It uses the [Protothreads library](http://dunkels.com/adam/pt/) by Adam Dunkels. You should adjust the -I option to the sdcc compiler to where the include files are installed.

You also need the C runtime startup object files from the avr-gcc distribution. If you have installed the Arduino IDE, then you have a copy of the avr-gcc tools and libraries already.

If you are using the Minipro TL866 to program the ATMEGA163, use the entry for ATMEGA164A and ignore the signature discrepancy with the -y option. You need to also program the fuses to enable the crystal oscillator.

## Versioning

April 2025

## Notes

## Authors

* **Ken Yap**

## License

See the [LICENSE](LICENSE.md) file for license rights and limitations (MIT).
