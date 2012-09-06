#ifndef FM27984_h
#define FM27984_h

#if ARDUINO >= 100
#include "Arduino.h"       // for delayMicroseconds, digitalPinToBitMask, etc
#else
#include "WProgram.h"      // for delayMicroseconds
#include "pins_arduino.h"  // for digitalPinToBitMask, etc
#endif



// device ID 
#define SLAVE_ID   0x20 >> 1

#define CONFIG_WORDS 5
#define STATUS_WORDS 4

// config 0 register 02
#define DHIZ 15
#define DMUTE 14
#define MONO 13
#define BASS 12
#define CLK32_INPUT_ENB 10
#define SEEK 8
#define CLK_MODE 4
#define SOFT_RESET 1
#define ENABLE 0
#define CLK_MODE_MASK (7 << CLK_MODE)
#define SEEK_MASK (3 << SEEK)
#define SEEK_UP (3 << SEEK)
#define SEEK_DOWN (1 << SEEK)

// config 1 register 03
#define CHAN 6
#define TUNE 4
#define BAND 2
#define SPACE 0
#define CHAN_MASK (0xff << CHAN)
#define BAND_MASK ( 3 << CHAN)
#define SPACE_MASK ( 3 << SPACE)

// config 2 register 04
#define STCEIN 14
#define DE 11
#define I2S_ENABLED 6
#define GPIO3 4
#define GPIO2 2
#define GPIO1 0
#define GPIO3_MASK ( 3 << GPIO3)
#define GPIO2_MASK ( 3 << GPIO2)
#define GPIO1_MASK ( 3 << GPIO1)

// config 3 register 05
#define INT_MODE 15
#define SEEKTH 8
#define LNA_PORT_SEL 6
#define LNA_ICSEL_BIT 4
#define VOLUME 0
#define SEEKTH_MASK (0x7f << SEEKTH)
#define LNA_PORT_MASK (2 << LNA_PORT_SEL)
#define LNA_ICSEL_MASK (2 << LNA_ICSEL_BIT)
#define VOLUME_MASK (0x0f << VOLUME)
	
// status regs
// status 0  register 0a
#define STC 14
#define SF 13
#define ST 10
#define READCHAN 0
#define READCHAN_MASK (0xff << READCHAN)

// status 1  register 0b
#define RSS 9
#define FM_TRUE 8
#define FM_READY 7
#define RSS_MASK (0x7f << RSS)

// assume band 0   760 for other   spacing .1 MHz
#define MAX_FREQ 1080
#define MIN_FREQ 870
#define MAX_SST  127
#define MAX_VOL  15


class FM27984
{
  public:
  	FM27984();
  	FM27984(int _chan, int _vol, int _sst);
	void reset();
	void tune_enable();
	void tune_disable();
	bool tune_done();
	void seek_off();
	void seek_up();
	void seek_down();
	bool vol_update(int val);
	bool chan_update(int val);
	bool chan_set(int val);
	int chan_get();
	bool sst_update(int val);
	void setConfig();
	void getStatus();
	void printConfig();
	void printStatus();

  private:
	void init(int _chan, int _vol, int _sst);
	static const uint16_t Config0[CONFIG_WORDS];
	uint16_t Config[CONFIG_WORDS], Status[STATUS_WORDS];
	uint16_t vol, chan ;   // channel spacing 100KHz
	uint16_t rss, readchan,sst,st,fmtrue,fmready,stc,sf;
	uint16_t seekchan;
	uint16_t chan0, vol0, sst0;   // reset values
};

#endif
