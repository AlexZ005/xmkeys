/* $XConsortium: xev.c,v 1.15 94/04/17 20:45:20 keith Exp $ */
/*

Copyright (c) 1988  X Consortium

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from the X Consortium.

*/
/* $XFree86: xc/programs/xev/xev.c,v 1.13 2003/10/24 20:38:17 tsi Exp $ */

/*
 * Author:  Jim Fulton, MIT X Consortium
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <X11/Xlocale.h>
#include <X11/Xos.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xproto.h>

#define INNER_WINDOW_WIDTH 50
#define INNER_WINDOW_HEIGHT 50
#define INNER_WINDOW_BORDER 4
#define INNER_WINDOW_X 10
#define INNER_WINDOW_Y 10
#define OUTER_WINDOW_MIN_WIDTH (INNER_WINDOW_WIDTH + \
                        2 * (INNER_WINDOW_BORDER + INNER_WINDOW_X))
#define OUTER_WINDOW_MIN_HEIGHT (INNER_WINDOW_HEIGHT + \
                        2 * (INNER_WINDOW_BORDER + INNER_WINDOW_Y))
#define OUTER_WINDOW_DEF_WIDTH (OUTER_WINDOW_MIN_WIDTH + 100)
#define OUTER_WINDOW_DEF_HEIGHT (OUTER_WINDOW_MIN_HEIGHT + 100)
#define OUTER_WINDOW_DEF_X 100
#define OUTER_WINDOW_DEF_Y 100
                        

typedef unsigned long Pixel;

const char *Yes = "YES";
const char *No = "NO";
const char *Unknown = "unknown";

const char *ProgramName;
Display *dpy;
int screen;

XIC xic = NULL;

static void
prologue (XEvent *eventp, char *event_name)
{
    XAnyEvent *e = (XAnyEvent *) eventp;

//    printf ("\n%s event, serial %ld, synthetic %s, window 0x%lx,\n",
//          event_name, e->serial, e->send_event ? Yes : No, e->window);
}

static void
dump (char *str, int len)
{
    printf("(");
    len--;
    while (len-- > 0)
        printf("%02x ", (unsigned char) *str++);
    printf("%02x)", (unsigned char) *str++);
}

static void
do_KeyPress (XEvent *eventp)
{
    XKeyEvent *e = (XKeyEvent *) eventp;
    KeySym ks;
    KeyCode kc = 0;
    Bool kc_set = False;
    char *ksname;
    int nbytes, nmbbytes = 0;
    char str[256+1];
    static char *buf = NULL;
    static int bsize = 8;
    Status status;

    if (buf == NULL)
      buf = malloc (bsize);

    nbytes = XLookupString (e, str, 256, &ks, NULL);

    /* not supposed to call XmbLookupString on a key release event */
    if (e->type == KeyPress && xic) {
        do {
            nmbbytes = XmbLookupString (xic, e, buf, bsize - 1, &ks, &status);
            buf[nmbbytes] = '\0';

            if (status == XBufferOverflow) {
                bsize = nmbbytes + 1;
                buf = realloc (buf, bsize);
            }
        } while (status == XBufferOverflow);
    }

    if (ks == NoSymbol)
      ksname = "NoSymbol";
    else {
      if (!(ksname = XKeysymToString (ks)))
          ksname = "(no name)";
      kc = XKeysymToKeycode(dpy, ks);
      kc_set = True;
    }
      
//    printf ("    state 0x%x, keycode %u (keysym 0x%lx, %s), same_screen %s,\n",
//          e->state, e->keycode, (unsigned long) ks, ksname,
//          e->same_screen ? Yes : No);
printf ("%u",   //remain \n if you want to use without exit!, so it would mantain loop, otherwise program breaks
          e->keycode);
exit(0);
}

static void
do_KeyRelease (XEvent *eventp)
{
    do_KeyPress (eventp);           /* since it has the same info */
}


static void
set_sizehints (XSizeHints *hintp, int min_width, int min_height,
             int defwidth, int defheight, int defx, int defy,
             char *geom)
{
    int geom_result;

    /* set the size hints, algorithm from xlib xbiff */

    hintp->width = hintp->min_width = min_width;
    hintp->height = hintp->min_height = min_height;
    hintp->flags = PMinSize;
    hintp->x = hintp->y = 0;
    geom_result = NoValue;
    if (geom != NULL) {
        geom_result = XParseGeometry (geom, &hintp->x, &hintp->y,
                              (unsigned int *)&hintp->width,
                              (unsigned int *)&hintp->height);
      if ((geom_result & WidthValue) && (geom_result & HeightValue)) {
#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b))
#endif
          hintp->width = max (hintp->width, hintp->min_width);
          hintp->height = max (hintp->height, hintp->min_height);
          hintp->flags |= USSize;
      }
      if ((geom_result & XValue) && (geom_result & YValue)) {
          hintp->flags += USPosition;
      }
    }
    if (!(hintp->flags & USSize)) {
      hintp->width = defwidth;
      hintp->height = defheight;
      hintp->flags |= PSize;
    }
/*
    if (!(hintp->flags & USPosition)) {
      hintp->x = defx;
      hintp->y = defy;
      hintp->flags |= PPosition;
    }
 */
    if (geom_result & XNegative) {
      hintp->x = DisplayWidth (dpy, DefaultScreen (dpy)) + hintp->x -
                hintp->width;
    }
    if (geom_result & YNegative) {
      hintp->y = DisplayHeight (dpy, DefaultScreen (dpy)) + hintp->y -
                hintp->height;
    }
}


#if defined(__GNUC__) && \
    ((__GNUC__ > 2) || ((__GNUC__ == 2) && (__GNUC_MINOR__ >= 7)))
static void usage (void) __attribute__((__noreturn__));
#endif
static void
usage (void)
{
    static const char *msg[] = {
"    -display displayname                X server to contact",
"    -geometry geom                      size and location of window",
"    -bw pixels                          border width in pixels",
"    -bs {NotUseful,WhenMapped,Always}   backingstore attribute",
"    -id windowid                        use existing window",
"    -s                                  set save-unders attribute",
"    -name string                        window name",
"    -rv                                 reverse video",
"",
NULL};
    const char **cpp;

    fprintf (stderr, "usage:  %s [-options ...]\n", ProgramName);
    fprintf (stderr, "where options include:\n");

    for (cpp = msg; *cpp; cpp++)
      fprintf (stderr, "%s\n", *cpp);

    exit (1);
}

static int
parse_backing_store (char *s)
{
    int len = strlen (s);
    char *cp;

    for (cp = s; *cp; cp++) {
      if (isascii (*cp) && isupper (*cp))
          *cp = tolower (*cp);
    }

    if (strncmp (s, "notuseful", len) == 0) return (NotUseful);
    if (strncmp (s, "whenmapped", len) == 0) return (WhenMapped);
    if (strncmp (s, "always", len) == 0) return (Always);

    usage ();
}

int
main (int argc, char **argv)
{
    char *displayname = NULL;
    char *geom = NULL;
    int i;
    XSizeHints hints;
    int borderwidth = 2;
    Window w, subw;
    XSetWindowAttributes attr;
    XWindowAttributes wattr;
    unsigned long mask = 0L;
    int done;
    char *name = "Event Tester";
    Bool reverse = False;
    unsigned long back, fore;
    XIM xim;
    XIMStyles *xim_styles;
    XIMStyle xim_style = 0;
    char *modifiers;
    char *imvalret;

    ProgramName = argv[0];

    if (setlocale(LC_ALL,"") == NULL) {
      fprintf(stderr, "%s: warning: could not set default locale\n",
            ProgramName);
    }

    w = 0;
    for (i = 1; i < argc; i++) {
      char *arg = argv[i];

      if (arg[0] == '-') {
          switch (arg[1]) {
            case 'd':               /* -display host:dpy */
            if (++i >= argc) usage ();
            displayname = argv[i];
            continue;
            case 'g':               /* -geometry geom */
            if (++i >= argc) usage ();
            geom = argv[i];
            continue;
            case 'b':
            switch (arg[2]) {
              case 'w':       /* -bw pixels */
                if (++i >= argc) usage ();
                borderwidth = atoi (argv[i]);
                continue;
              case 's':       /* -bs type */
                if (++i >= argc) usage ();
                attr.backing_store = parse_backing_store (argv[i]);
                mask |= CWBackingStore;
                continue;
              default:
                usage ();
            }
            case 'i':               /* -id */
            if (++i >= argc) usage ();
            sscanf(argv[i], "0x%lx", &w);
            if (!w)
                sscanf(argv[i], "%lu", &w);
            if (!w)
                usage ();
            continue;
            case 'n':               /* -name */
            if (++i >= argc) usage ();
            name = argv[i];
            continue;
            case 'r':               /* -rv */
            reverse = True;
            continue;
            case 's':               /* -s */
            attr.save_under = True;
            mask |= CWSaveUnder;
            continue;
            default:
            usage ();
          }                   /* end switch on - */
      } else 
        usage ();
    }                         /* end for over argc */

    dpy = XOpenDisplay (displayname);
    if (!dpy) {
      fprintf (stderr, "%s:  unable to open display '%s'\n",
             ProgramName, XDisplayName (displayname));
      exit (1);
    }

    /* we're testing the default input method */
    modifiers = XSetLocaleModifiers ("@im=none");
    if (modifiers == NULL) {
        fprintf (stderr, "%s:  XSetLocaleModifiers failed\n", ProgramName);
    }

    xim = XOpenIM (dpy, NULL, NULL, NULL);
    if (xim == NULL) {
        fprintf (stderr, "%s:  XOpenIM failed\n", ProgramName);
    }

    if (xim) {
        imvalret = XGetIMValues (xim, XNQueryInputStyle, &xim_styles, NULL);
        if (imvalret != NULL || xim_styles == NULL) {
            fprintf (stderr, "%s:  input method doesn't support any styles\n", ProgramName);
        }

        if (xim_styles) {
            xim_style = 0;
            for (i = 0;  i < xim_styles->count_styles;  i++) {
                if (xim_styles->supported_styles[i] ==
                    (XIMPreeditNothing | XIMStatusNothing)) {
                    xim_style = xim_styles->supported_styles[i];
                    break;
                }
            }

            if (xim_style == 0) {
                fprintf (stderr, "%s: input method doesn't support the style we support\n",
                         ProgramName);
            }
            XFree (xim_styles);
        }
    } 

    screen = DefaultScreen (dpy);

    /* select for all events */
    attr.event_mask = KeyPressMask | KeyReleaseMask | ButtonPressMask |
                     ButtonReleaseMask | EnterWindowMask |
                     LeaveWindowMask | PointerMotionMask |
                     Button1MotionMask |
                     Button2MotionMask | Button3MotionMask |
                     Button4MotionMask | Button5MotionMask |
                     ButtonMotionMask | KeymapStateMask |
                     ExposureMask | VisibilityChangeMask |
                     StructureNotifyMask | /* ResizeRedirectMask | */
                     SubstructureNotifyMask | SubstructureRedirectMask |
                     FocusChangeMask | PropertyChangeMask |
                     ColormapChangeMask | OwnerGrabButtonMask;

    if (w) {
      XGetWindowAttributes(dpy, w, &wattr);
      if (wattr.all_event_masks & ButtonPressMask)
          attr.event_mask &= ~ButtonPressMask;
      attr.event_mask &= ~SubstructureRedirectMask;
      XSelectInput(dpy, w, attr.event_mask);
    } else {
      set_sizehints (&hints, OUTER_WINDOW_MIN_WIDTH, OUTER_WINDOW_MIN_HEIGHT,
                   OUTER_WINDOW_DEF_WIDTH, OUTER_WINDOW_DEF_HEIGHT,
                   OUTER_WINDOW_DEF_X, OUTER_WINDOW_DEF_Y, geom);

      if (reverse) {
          back = BlackPixel(dpy,screen);
          fore = WhitePixel(dpy,screen);
      } else {
          back = WhitePixel(dpy,screen);
          fore = BlackPixel(dpy,screen);
      }

      attr.background_pixel = back;
      attr.border_pixel = fore;
      mask |= (CWBackPixel | CWBorderPixel | CWEventMask);

      w = XCreateWindow (dpy, RootWindow (dpy, screen), hints.x, hints.y,
                     hints.width, hints.height, borderwidth, 0,
                     InputOutput, (Visual *)CopyFromParent,
                     mask, &attr);

      XSetStandardProperties (dpy, w, name, NULL, (Pixmap) 0,
                        argv, argc, &hints);

      subw = XCreateSimpleWindow (dpy, w, INNER_WINDOW_X, INNER_WINDOW_Y,
                            INNER_WINDOW_WIDTH, INNER_WINDOW_HEIGHT,
                            INNER_WINDOW_BORDER,
                            attr.border_pixel, attr.background_pixel);

      XMapWindow (dpy, subw);       /* map before w so that it appears */
      XMapWindow (dpy, w);

//      printf ("Outer window is 0x%lx, inner window is 0x%lx\n", w, subw);
    }

    if (xim && xim_style) {
        xic = XCreateIC (xim,
                         XNInputStyle, xim_style,
                         XNClientWindow, w,
                         XNFocusWindow, w,
                         NULL);

        if (xic == NULL) {
            fprintf (stderr, "XCreateIC failed\n");
        }
    }

    for (done = 0; !done; ) {
      XEvent event;

      XNextEvent (dpy, &event);

      switch (event.type) {
        case KeyPress:
          prologue (&event, "KeyPress");
          do_KeyPress (&event);
          break;
      }
    }

    XCloseDisplay (dpy);
    return 0; 
}
