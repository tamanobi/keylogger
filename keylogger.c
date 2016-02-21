#include <stdio.h>
#include <time.h>
#include <ApplicationServices/ApplicationServices.h>

CGEventRef on_tap(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
  time_t now; time(&now);
  if (CGEventGetType(event) == kCGEventKeyDown) {
    CGKeyCode key = (CGKeyCode)CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
    printf("time:%d\ttype:%s\tcode:%d\n", (int)now, "key", key); fflush(stdout);
  } else if (type == kCGEventLeftMouseDown) {
    printf("time:%d\ttype:%s\tbutton:%s\n", (int)now, "mouse", "left"); fflush(stdout);
  } else if (type == kCGEventRightMouseDown) {
    printf("time:%d\ttype:%s\tbutton:%s\n", (int)now, "mouse", "right"); fflush(stdout);
  } else if (type == kCGEventMouseMoved) {
    int x = CGEventGetIntegerValueField(event, kCGMouseEventDeltaX);
    int y = CGEventGetIntegerValueField(event, kCGMouseEventDeltaY);
    printf("time:%d\ttype:%s\tcode:%s\tdx:%d\tdy:%d\n", (int)now, "mouse", "move", x, y); fflush(stdout);
  }
  return event;
}

int main(int argc, const char * argv[]) {
  CGEventFlags flags = CGEventSourceFlagsState(kCGEventSourceStateCombinedSessionState);
  // CGEventMask mask = CGEventMaskBit(kCGEventKeyDown);
  CGEventMask mask = 
    CGEventMaskBit(kCGEventKeyDown) | 
    CGEventMaskBit(kCGEventLeftMouseDown) | 
    CGEventMaskBit(kCGEventRightMouseDown) | 
    CGEventMaskBit(kCGEventMouseMoved);

  CFMachPortRef tap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, 0, mask, on_tap, &flags);
  if (!tap) {
    fprintf(stderr, "This program requires sudo.");
    return -1;
  }
  CFRunLoopSourceRef runloop = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, tap, 0);
  CFRunLoopAddSource(CFRunLoopGetCurrent(), runloop, kCFRunLoopCommonModes);
  CGEventTapEnable(tap, true);
  CFRunLoopRun();
  return 0;
}
