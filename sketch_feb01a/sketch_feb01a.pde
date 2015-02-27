///////////////////////////////////////////////////////////////////////
// wiimote_blinkm.pde
//
// Copyright 2008 Ben Bleything <ben@bleything.net>
// Released under the terms of the MIT license
//
// This code enables you to read OSC messages coming from a wiimote
// and control a BlinkM on an Arduino.
///////////////////////////////////////////////////////////////////////

import oscP5.*;
import netP5.*;
import processing.serial.*;

Serial arduino;
//OscP5  osc_controller;
float  hue, brightness;
boolean fade_speed_set = false;

void setup() {
  // we don't actually care about these...
  size( 100, 100 );
  frameRate( 30 );

  // set up the serial link to the arduino
  arduino = new Serial( this, "/dev/tty.usbserial-A4001IWR", 19200 );
  println( "sleeping 2 seconds for the serial port..." );
  delay( 2000 );

  // start oscP5, listening for incoming messages at port 5600
  osc_controller = new OscP5( this, 5600 );

  // plug in to the nunchuck joystick
  osc_controller.plug( this, "set_joystick", "/nunchuk/joystick" );

  background(0);
}

void draw() {
  // gross hack to get around the fact that fade speed is initially
  // set to zero, preventing any fades from happening.
  if( fade_speed_set ) {
    fade_to( hue, brightness );
  } else {
    // this is fucking voodoo but it works.  Lame.
    delay( 500 );
    set_fade_speed();
    fade_speed_set = true;
  }
}

///////////////////////////////////////////////////////////////////////
// B L I N K M   C O M M U N I C A T I O N
///////////////////////////////////////////////////////////////////////

void set_fade_speed() {
  byte[] cmd = new byte[6];

  cmd[0] = (byte)0x01;
  cmd[1] = (byte)0x09;
  cmd[2] = (byte)0x02;
  cmd[3] = (byte)0x00;
  cmd[4] = (byte)'f';
  cmd[5] = (byte)0xFF;

  arduino.write( cmd );
}

void fade_to( float h, float b ) {
  println( "fading to hue " + h + " with brightness " + b );

  byte[] cmd = new byte[8];

  cmd[0] = (byte)0x01;
  cmd[1] = (byte)0x09;
  cmd[2] = (byte)0x04;
  cmd[3] = (byte)0x00;
  cmd[4] = (byte)'h';
  cmd[5] = (byte)h;
  cmd[6] = (byte)0xff;
  cmd[7] = (byte)b;

  arduino.write( cmd );
}

///////////////////////////////////////////////////////////////////////
// W I I M O T E   I N P U T   H A N D L E R S
///////////////////////////////////////////////////////////////////////

// full left:  ( -1.0208334  , 0.0 )
// full right: (  0.96875006 , 0.0 )
//
// full up:   ( 0.0,  1.03125   )
// full down: ( 0.0, -1.0104166 )

void set_joystick( float x, float y ) {
  // zero out the joystick
  float joystick_x = x - 0.052083332;
  float joystick_y = y - 0.072916664;

  // This is the 'r' side of the rectangular -> polar conversion described at
  // http://www.teacherschoice.com.au/Maths_Library/Coordinates/polar_-_rectangular_conversion.htm
  brightness = sqrt( (sq(joystick_x) + sq(joystick_y)) );

  // this is effectively the theta side of the rectangular -> polar conversion,
  // then converted to degrees and adding 180 to bring the whole thing into the
  // positive realm.
  hue = degrees( atan2( joystick_y, joystick_x ) ) + 180;

  // the HSB command for the BlinkM expects bytes, so we need to convert our
  // degrees (0-360) to byte range (0-255).  I *think* we can do this by
  // multiplying the degrees value by 0.7083 without losing any meaning...
  hue *= 0.7083;

  // the highest brightness value I was able to record was 1.075795.  This is
  // our upper ceiling, so we multiply by 237.034 to bring the brightness into
  // the byte range
  brightness *= 237.034;
}

