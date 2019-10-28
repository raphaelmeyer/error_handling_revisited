#!/usr/bin/python

import evdev as ev
import sys

def find_gamepad():
  for dev in ev.list_devices():
    in_dev = ev.InputDevice(dev)
    if 'gamepad' in in_dev.name:
      return in_dev
  return None

def previous():
  with ev.uinput.UInput() as ui:
    ui.write(ev.ecodes.EV_KEY, ev.ecodes.KEY_LEFT)
    ui.syn()

def next():
  with ev.uinput.UInput() as ui:
    ui.write(ev.ecodes.EV_KEY, ev.ecodes.KEY_RIGHT)
    ui.syn()

def main():
  gamepad = find_gamepad()
  if gamepad is None:
    print('No gamepad found.')
    sys.exit(1)

  for event in gamepad.read_loop():
    if event.type == ev.ecodes.EV_ABS:
      abs_ev = ev.categorize(event)
      if ev.ecodes.bytype[abs_ev.event.type][abs_ev.event.code] == 'ABS_X':
        if abs_ev.event.value == 0:
          previous()
        elif abs_ev.event.value == 255:
          next()

if __name__ == "__main__":
  main()

