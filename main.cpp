#include <windows.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string.h>
#include <mmsystem.h>

using std::ostringstream;
using std::ostream;


using namespace std;

static char g_szClassName[] = "MyWindowClass";
static HINSTANCE hInst = NULL;

const UINT idTimer1 = 1;
UINT nTimerDelay = 10;

HBITMAP hbmBall;
HBITMAP hbmMask;

BITMAP bm;

int ballX, ballY;
int deltaX, deltaY;

int deltaValue = 2;
int deltaYValue = 1;

void EraseBall(HDC hdc)
{
   RECT rc;
   rc.left = ballX;
   rc.top = ballY;
   rc.right = ballX + bm.bmWidth;
   rc.bottom = ballY + bm.bmHeight;
   FillRect(hdc, &rc, (HBRUSH) GetStockObject (BLACK_BRUSH));
}

void DrawBall(HDC hdc)
{
   HDC hdcMemory;
   hdcMemory = CreateCompatibleDC(hdc);

   SelectObject(hdcMemory, hbmMask);
   BitBlt(hdc, ballX, ballY, bm.bmWidth, bm.bmHeight, hdcMemory, 0, 0, SRCAND);

   SelectObject(hdcMemory, hbmBall);
   BitBlt(hdc, ballX, ballY, bm.bmWidth, bm.bmHeight, hdcMemory, 0, 0, SRCPAINT);

   DeleteDC(hdcMemory);
}

void UpdateBall(HWND hwnd)
{
   RECT rc;
   GetClientRect(hwnd, &rc);

   ballX += deltaX;
   ballY += deltaY;

   if(ballX < -800){
      ballX = 600;
      deltaX = deltaValue;
   }
   else if(ballX + bm.bmWidth > rc.right){
  //    ballX = rc.right - bm.bmWidth;
      deltaX = -deltaValue;
   }
   if(ballY < 308){
      ballY = 308;
      deltaY = deltaYValue;
   }
   else if(ballY > 315){
//      ballY = rc.bottom - bm.bmHeight;
      deltaY = -deltaYValue;
   }
}

LRESULT CALLBACK
WndProc (HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
 
static HWND dialbtn = 0;
static HWND mfdialbtn = 0;
            
static HWND DTMF1 = 0;
static HWND DTMF2 = 0;
static HWND DTMF3 = 0;
static HWND DTMF4 = 0;
static HWND DTMF5 = 0;
static HWND DTMF6 = 0;
static HWND DTMF7 = 0;
static HWND DTMF8 = 0;
static HWND DTMF9 = 0;
static HWND DTMF0 = 0;
static HWND DTMFstar = 0;
static HWND DTMFpound = 0;
static HWND DTMFA = 0;
static HWND DTMFB = 0;
static HWND DTMFC = 0;
static HWND DTMFD = 0;

static HWND CRUNCH = 0;
static HWND RINGFORWARD = 0;

static HWND MF1 = 0;
static HWND MF2 = 0;
static HWND MF3 = 0;
static HWND MF4 = 0;
static HWND MF5 = 0;
static HWND MF6 = 0;
static HWND MF7 = 0;
static HWND MF8 = 0;
static HWND MF9 = 0;
static HWND MF0 = 0;
static HWND MFKP = 0;
static HWND MFST = 0;

static HWND SF1 = 0;
static HWND SF2 = 0;
static HWND SF3 = 0;
static HWND SF4 = 0;
static HWND SF5 = 0;
static HWND SF6 = 0;
static HWND SF7 = 0;
static HWND SF8 = 0;
static HWND SF9 = 0;
static HWND SF0 = 0;

static HWND nickel = 0;
static HWND dime = 0;
static HWND quarter = 0;

static HWND nickel2 = 0;
static HWND dime2 = 0;
static HWND quarter2 = 0;

static HWND dtmftext = 0;
static HWND blueboxtext = 0;
static HWND blueboxtext2 = 0;
static HWND redboxtext = 0;
static HWND autodtmftext = 0;
static HWND automftext = 0;

static int cx, cy;/* Height and width of our button. */

HDC hdc = 0;    
PAINTSTRUCT ps;
RECT rc;/* A rectangle used during drawing */

switch (nMsg)
{
case WM_CREATE:
{
     //hbmBall = LoadBitmap(hInst, "ball.bmp");
     //hbmMask = LoadBitmap(hInst, "ballmask.bmp");
     hbmBall = (HBITMAP)LoadImage(NULL, "./assets/ball.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
     hbmMask = (HBITMAP)LoadImage(NULL, "./assets/ballmask.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

     if(!hbmBall || !hbmMask){
        MessageBox(hwnd, "Load of resources failed.", "Error",
           MB_OK | MB_ICONEXCLAMATION);
        return -1;
        }
        
        GetObject(hbmBall, sizeof(bm), &bm);
         SetTimer(hwnd, idTimer1, nTimerDelay, NULL);

         ballX = 600;
         ballY = 350;
         deltaX = deltaValue;
         deltaY = deltaValue;
        
/* The window is being created. Create our button window now. */
TEXTMETRIC tm;
/* First we use the system fixed font size and choose a nice button size. */
hdc = GetDC (hwnd);
SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT));
GetTextMetrics (hdc, &tm);
cx = 30;
cy = 30;
ReleaseDC (hwnd, hdc);

dialbtn = CreateWindow ("button",/* Builtin button class */ "Dial!", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
HWND dial = CreateWindow(TEXT("EDIT"),
        TEXT(""), ES_NUMBER | WS_VISIBLE | WS_CHILD | WS_BORDER,
        177,
        262,
        300,
        20,
        hwnd,
        HMENU(1104),
        (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
        NULL);
        
mfdialbtn = CreateWindow ("button",/* Builtin button class */ "Dial!", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
HWND mfdial = CreateWindow(TEXT("EDIT"),
        TEXT(""), ES_NUMBER | WS_VISIBLE | WS_CHILD | WS_BORDER,
        177,
        287,
        300,
        20,
        hwnd,
        HMENU(1103),
        (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
        NULL);
        
SendMessage(dial, WM_SETTEXT, 0, (LPARAM) "");

DTMF1 = CreateWindow ("button",/* Builtin button class */ "1", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
DTMF2 = CreateWindow ("button",/* Builtin button class */ "2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
DTMF3 = CreateWindow ("button",/* Builtin button class */ "3", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
DTMF4 = CreateWindow ("button",/* Builtin button class */ "4", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
DTMF5 = CreateWindow ("button",/* Builtin button class */ "5", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
DTMF6 = CreateWindow ("button",/* Builtin button class */ "6", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
DTMF7 = CreateWindow ("button",/* Builtin button class */ "7", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
DTMF8 = CreateWindow ("button",/* Builtin button class */ "8", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
DTMF9 = CreateWindow ("button",/* Builtin button class */ "9", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
DTMF0 = CreateWindow ("button",/* Builtin button class */ "0", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
DTMFstar = CreateWindow ("button",/* Builtin button class */ "*", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
DTMFpound = CreateWindow ("button",/* Builtin button class */ "#", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
DTMFA = CreateWindow ("button",/* Builtin button class */ "A", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
DTMFB = CreateWindow ("button",/* Builtin button class */ "B", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
DTMFC = CreateWindow ("button",/* Builtin button class */ "C", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
DTMFD = CreateWindow ("button",/* Builtin button class */ "D", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );

MF1 = CreateWindow ("button",/* Builtin button class */ "1", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
MF2 = CreateWindow ("button",/* Builtin button class */ "2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
MF3 = CreateWindow ("button",/* Builtin button class */ "3", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
MF4 = CreateWindow ("button",/* Builtin button class */ "4", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
MF5 = CreateWindow ("button",/* Builtin button class */ "5", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
MF6 = CreateWindow ("button",/* Builtin button class */ "6", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
MF7 = CreateWindow ("button",/* Builtin button class */ "7", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
MF8 = CreateWindow ("button",/* Builtin button class */ "8", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
MF9 = CreateWindow ("button",/* Builtin button class */ "9", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
MF0 = CreateWindow ("button",/* Builtin button class */ "0", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
MFKP = CreateWindow ("button",/* Builtin button class */ "KP", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
MFST = CreateWindow ("button",/* Builtin button class */ "ST", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );

SF1 = CreateWindow ("button",/* Builtin button class */ "1", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
SF2 = CreateWindow ("button",/* Builtin button class */ "2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
SF3 = CreateWindow ("button",/* Builtin button class */ "3", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
SF4 = CreateWindow ("button",/* Builtin button class */ "4", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
SF5 = CreateWindow ("button",/* Builtin button class */ "5", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
SF6 = CreateWindow ("button",/* Builtin button class */ "6", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
SF7 = CreateWindow ("button",/* Builtin button class */ "7", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
SF8 = CreateWindow ("button",/* Builtin button class */ "8", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
SF9 = CreateWindow ("button",/* Builtin button class */ "9", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
SF0 = CreateWindow ("button",/* Builtin button class */ "0", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );

CRUNCH = CreateWindow ("button",/* Builtin button class */ "2600 Hz", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );

RINGFORWARD = CreateWindow ("button",/* Builtin button class */ "RING FORWARD", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );

dtmftext = CreateWindow (TEXT("STATIC"), TEXT("DTMF Tones"), WS_VISIBLE | WS_CHILD, 50, 50, 100, 30, hwnd, NULL, NULL, NULL);
blueboxtext = CreateWindow (TEXT("STATIC"), TEXT("MF Tone Gen"), WS_VISIBLE | WS_CHILD, 50, 50, 100, 30, hwnd, NULL, NULL, NULL);
blueboxtext2 = CreateWindow (TEXT("STATIC"), TEXT("SF Tone Gen"), WS_VISIBLE | WS_CHILD, 50, 50, 100, 30, hwnd, NULL, NULL, NULL);
redboxtext = CreateWindow (TEXT("STATIC"), TEXT("CDT Gen"), WS_VISIBLE | WS_CHILD, 50, 50, 100, 30, hwnd, NULL, NULL, NULL);
autodtmftext = CreateWindow (TEXT("STATIC"), TEXT("DTMF"), WS_VISIBLE | WS_CHILD, 50, 50, 100, 30, hwnd, NULL, NULL, NULL);
automftext = CreateWindow (TEXT("STATIC"), TEXT("  MF"), WS_VISIBLE | WS_CHILD, 50, 50, 100, 30, hwnd, NULL, NULL, NULL);


nickel = CreateWindow ("button",/* Builtin button class */ "5¢", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
dime = CreateWindow ("button",/* Builtin button class */ "10¢", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
quarter = CreateWindow ("button",/* Builtin button class */ "25¢", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );

nickel2 = CreateWindow ("button",/* Builtin button class */ "3-slot 5", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
dime2 = CreateWindow ("button",/* Builtin button class */ "3-slot 10", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );
quarter2 = CreateWindow ("button",/* Builtin button class */ "3-slot 25", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, cx, cy, hwnd,/* Parent is this window. */ (HMENU) 1,/* Control ID: 1 */ ((LPCREATESTRUCT) lParam)->hInstance, NULL );


return 0;
break;
}

      case WM_TIMER:
         if(hbmBall && hbmMask)
         {
            HDC hdcWindow;
            hdcWindow = GetDC(hwnd);

            EraseBall(hdcWindow);
            UpdateBall(hwnd);
            DrawBall(hdcWindow);

            ReleaseDC(hwnd, hdcWindow);
         }
      return 0;
      break;
      case WM_PAINT:
         if(hbmBall && hbmMask)
         {
            PAINTSTRUCT ps;
            HDC hdcWindow;
            hdcWindow = BeginPaint(hwnd, &ps);

            DrawBall(hdcWindow);
            
            EndPaint(hwnd, &ps);
         }
      return 0;
      break;
      
case WM_CLOSE:
DestroyWindow(hwnd);
break;

case WM_DESTROY:
KillTimer(hwnd, idTimer1);        
DeleteObject(hbmBall);
DeleteObject(hbmMask);
PostQuitMessage(0);
return 0;
break;

case WM_SIZE:
/* place button in the window. */
if
(wParam == SIZEFULLSCREEN ||
 wParam == SIZENORMAL)
{
MoveWindow (DTMF1, 50, 30, cx, cy, TRUE);
MoveWindow (DTMF2, 80, 30, cx, cy, TRUE);
MoveWindow (DTMF3, 110, 30, cx, cy, TRUE);
MoveWindow (DTMFA, 140, 30, cx, cy, TRUE);
MoveWindow (DTMF4, 50, 60, cx, cy, TRUE);
MoveWindow (DTMF5, 80, 60, cx, cy, TRUE);
MoveWindow (DTMF6, 110, 60, cx, cy, TRUE);
MoveWindow (DTMFB, 140, 60, cx, cy, TRUE);
MoveWindow (DTMF7, 50, 90, cx, cy, TRUE);
MoveWindow (DTMF8, 80, 90, cx, cy, TRUE);
MoveWindow (DTMF9, 110, 90, cx, cy, TRUE);
MoveWindow (DTMFC, 140, 90, cx, cy, TRUE);
MoveWindow (DTMFstar, 50, 120, cx, cy, TRUE);
MoveWindow (DTMF0, 80, 120, cx, cy, TRUE);
MoveWindow (DTMFpound, 110, 120, cx, cy, TRUE);
MoveWindow (DTMFD, 140, 120, cx, cy, TRUE);

MoveWindow (dtmftext, 68, 10, 83, 15, TRUE);

MoveWindow (MF1, 180, 30, cx, cy, TRUE);
MoveWindow (MF2, 210, 30, cx, cy, TRUE);
MoveWindow (MF3, 240, 30, cx, cy, TRUE);
MoveWindow (MF4, 180, 60, cx, cy, TRUE);
MoveWindow (MF5, 210, 60, cx, cy, TRUE);
MoveWindow (MF6, 240, 60, cx, cy, TRUE);
MoveWindow (MF7, 180, 90, cx, cy, TRUE);
MoveWindow (MF8, 210, 90, cx, cy, TRUE);
MoveWindow (MF9, 240, 90, cx, cy, TRUE);
MoveWindow (MFKP, 180, 120, cx, cy, TRUE);
MoveWindow (MF0, 210, 120, cx, cy, TRUE);
MoveWindow (MFST, 240, 120, cx, cy, TRUE);

MoveWindow (SF1, 280, 30, cx, cy, TRUE);
MoveWindow (SF2, 310, 30, cx, cy, TRUE);
MoveWindow (SF3, 340, 30, cx, cy, TRUE);
MoveWindow (SF4, 280, 60, cx, cy, TRUE);
MoveWindow (SF5, 310, 60, cx, cy, TRUE);
MoveWindow (SF6, 340, 60, cx, cy, TRUE);
MoveWindow (SF7, 280, 90, cx, cy, TRUE);
MoveWindow (SF8, 310, 90, cx, cy, TRUE);
MoveWindow (SF9, 340, 90, cx, cy, TRUE);
MoveWindow (SF0, 280, 120, 90, cy, TRUE);

MoveWindow (CRUNCH, 180, 200, 190, cy, TRUE);
MoveWindow (RINGFORWARD, 180, 160, 190, cy, TRUE);

MoveWindow (nickel, 380, 30, 50, cy, TRUE);
MoveWindow (dime, 380, 60, 50, cy, TRUE);
MoveWindow (quarter, 380, 90, 50, cy, TRUE);

MoveWindow (nickel2, 430, 30, 60, cy, TRUE);
MoveWindow (dime2, 430, 60, 60, cy, TRUE);
MoveWindow (quarter2, 430, 90, 60, cy, TRUE);

MoveWindow (blueboxtext, 181, 10, 87, 15, TRUE);
MoveWindow (blueboxtext2, 282, 10, 86, 15, TRUE);

MoveWindow (redboxtext, 405, 10, 59, 15, TRUE);

MoveWindow (autodtmftext, 135, 264, 39, 15, TRUE);
MoveWindow (automftext, 135, 289, 39, 15, TRUE);

MoveWindow (dialbtn, 480, 263, 50, 18, TRUE);
MoveWindow (mfdialbtn, 480, 288, 50, 18, TRUE);
}
break;

case WM_COMMAND:
/* Check the control ID, notification code and control handle to see if this is a button click message from our child button. */
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == DTMF1)
{
PlaySound(TEXT("./assets/sounds/1.wav"), NULL, SND_FILENAME | SND_ASYNC);
//DestroyWindow (hwnd);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == DTMF2)
{
PlaySound(TEXT("./assets/sounds/2.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == DTMF3)
{
PlaySound(TEXT("./assets/sounds/3.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == DTMF4)
{
PlaySound(TEXT("./assets/sounds/4.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == DTMF5)
{
PlaySound(TEXT("./assets/sounds/5.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == DTMF6)
{
PlaySound(TEXT("./assets/sounds/6.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == DTMF7)
{
PlaySound(TEXT("./assets/sounds/7.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == DTMF8)
{
PlaySound(TEXT("./assets/sounds/8.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == DTMF9)
{
PlaySound(TEXT("./assets/sounds/9.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == DTMFA)
{
PlaySound(TEXT("./assets/sounds/A.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == DTMFB)
{
PlaySound(TEXT("./assets/sounds/B.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == DTMFC)
{
PlaySound(TEXT("./assets/sounds/C.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == DTMFD)
{
PlaySound(TEXT("./assets/sounds/D.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == DTMFstar)
{
PlaySound(TEXT("./assets/sounds/star.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == DTMF0)
{
PlaySound(TEXT("./assets/sounds/0.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == DTMFpound)
{
PlaySound(TEXT("./assets/sounds/pound.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == MF1)
{
PlaySound(TEXT("./assets/sounds/MF1.wav"), NULL, SND_FILENAME | SND_ASYNC);
//DestroyWindow (hwnd);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == MF2)
{
PlaySound(TEXT("./assets/sounds/MF2.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == MF3)
{
PlaySound(TEXT("./assets/sounds/MF3.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == MF4)
{
PlaySound(TEXT("./assets/sounds/MF4.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == MF5)
{
PlaySound(TEXT("./assets/sounds/MF5.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == MF6)
{
PlaySound(TEXT("./assets/sounds/MF6.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == MF7)
{
PlaySound(TEXT("./assets/sounds/MF7.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == MF8)
{
PlaySound(TEXT("./assets/sounds/MF8.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == MF9)
{
PlaySound(TEXT("./assets/sounds/MF9.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == MFKP)
{
PlaySound(TEXT("./assets/sounds/MFKP.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == MF0)
{
PlaySound(TEXT("./assets/sounds/MF0.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == MFST)
{
PlaySound(TEXT("./assets/sounds/MFST.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == SF1)
{
PlaySound(TEXT("./assets/sounds/SF1.wav"), NULL, SND_FILENAME | SND_ASYNC);
//DestroyWindow (hwnd);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == SF2)
{
PlaySound(TEXT("./assets/sounds/SF2.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == SF3)
{
PlaySound(TEXT("./assets/sounds/SF3.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == SF4)
{
PlaySound(TEXT("./assets/sounds/SF4.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == SF5)
{
PlaySound(TEXT("./assets/sounds/SF5.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == SF6)
{
PlaySound(TEXT("./assets/sounds/SF6.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == SF7)
{
PlaySound(TEXT("./assets/sounds/SF7.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == SF8)
{
PlaySound(TEXT("./assets/sounds/SF8.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == SF9)
{
PlaySound(TEXT("./assets/sounds/SF9.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == SF0)
{
PlaySound(TEXT("./assets/sounds/SF0.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == CRUNCH)
{
PlaySound(TEXT("./assets/sounds/2600.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == RINGFORWARD)
{
PlaySound(TEXT("./assets/sounds/ring.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == nickel2)
{
PlaySound(TEXT("./assets/sounds/gong5.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == dime2)
{
PlaySound(TEXT("./assets/sounds/gong10.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == quarter2)
{
PlaySound(TEXT("./assets/sounds/gong25.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == nickel)
{
PlaySound(TEXT("./assets/sounds/nickel.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == dime)
{
PlaySound(TEXT("./assets/sounds/dime.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == quarter)
{
PlaySound(TEXT("./assets/sounds/quarter.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == dialbtn)
{
char buf[1024] = {'\0'}; //buffer to store text-box input
char buf2[1024] = {'\0'}; //buffer to store each individual digit as needed
char int1[1024] = {1}; //buffers to store numbers to compare with buf2
GetDlgItemText(hwnd, 1104, buf, 100);

//play with the buffer
for (int i = 0; i < strlen(buf); i++){
    char single[2] = {0};
    single[0] = buf[i];
    int digit = atoi(single);
    sprintf(buf2,"%d\n",digit);
    //MessageBox(NULL,buf2,"INFO",MB_ICONEXCLAMATION);
    if (digit == 1){
              PlaySound(TEXT("./assets/sounds/1.wav"), NULL, SND_FILENAME | SND_ASYNC);
              Sleep(200);
              }
    if (digit == 2){
              PlaySound(TEXT("./assets/sounds/2.wav"), NULL, SND_FILENAME | SND_ASYNC);
              Sleep(200);
              }
    if (digit == 3){
              PlaySound(TEXT("./assets/sounds/3.wav"), NULL, SND_FILENAME | SND_ASYNC);
              Sleep(200);
              }
    if (digit == 4){
              PlaySound(TEXT("./assets/sounds/4.wav"), NULL, SND_FILENAME | SND_ASYNC);
              Sleep(200);
              }
    if (digit == 5){
              PlaySound(TEXT("./assets/sounds/5.wav"), NULL, SND_FILENAME | SND_ASYNC);
              Sleep(200);
              }
    if (digit == 6){
              PlaySound(TEXT("./assets/sounds/6.wav"), NULL, SND_FILENAME | SND_ASYNC);
              Sleep(200);
              }
    if (digit == 7){
              PlaySound(TEXT("./assets/sounds/7.wav"), NULL, SND_FILENAME | SND_ASYNC);
              Sleep(200);
              }
    if (digit == 8){
              PlaySound(TEXT("./assets/sounds/8.wav"), NULL, SND_FILENAME | SND_ASYNC);
              Sleep(200);
              }
    if (digit == 9){
              PlaySound(TEXT("./assets/sounds/9.wav"), NULL, SND_FILENAME | SND_ASYNC);
              Sleep(200);
              }
    if (digit == 0){
              PlaySound(TEXT("./assets/sounds/0.wav"), NULL, SND_FILENAME | SND_ASYNC);
              Sleep(200);
              }
    }
}

if (LOWORD(wParam) == 1 &&
    HIWORD(wParam) == BN_CLICKED &&
    (HWND) lParam == mfdialbtn)
{
PlaySound(TEXT("./assets/sounds/MFKP.wav"), NULL, SND_FILENAME | SND_ASYNC);
Sleep(600);
char buf[1024] = {'\0'}; //buffer to store text-box input
char buf2[1024] = {'\0'}; //buffer to store each individual digit as needed
char int1[1024] = {1}; //buffers to store numbers to compare with buf2
GetDlgItemText(hwnd, 1103, buf, 100);

//play with the buffer
for (int i = 0; i < strlen(buf); i++){
    char single[2] = {0};
    single[0] = buf[i];
    int digit = atoi(single);
    sprintf(buf2,"%d\n",digit);
    //MessageBox(NULL,buf2,"INFO",MB_ICONEXCLAMATION);
    if (digit == 1){
              PlaySound(TEXT("./assets/sounds/MF1.wav"), NULL, SND_FILENAME | SND_ASYNC);
              Sleep(200);
              }
    if (digit == 2){
              PlaySound(TEXT("./assets/sounds/MF2.wav"), NULL, SND_FILENAME | SND_ASYNC);
              Sleep(200);
              }
    if (digit == 3){
              PlaySound(TEXT("./assets/sounds/MF3.wav"), NULL, SND_FILENAME | SND_ASYNC);
              Sleep(200);
              }
    if (digit == 4){
              PlaySound(TEXT("./assets/sounds/MF4.wav"), NULL, SND_FILENAME | SND_ASYNC);
              Sleep(200);
              }
    if (digit == 5){
              PlaySound(TEXT("./assets/sounds/MF5.wav"), NULL, SND_FILENAME | SND_ASYNC);
              Sleep(200);
              }
    if (digit == 6){
              PlaySound(TEXT("./assets/sounds/MF6.wav"), NULL, SND_FILENAME | SND_ASYNC);
              Sleep(200);
              }
    if (digit == 7){
              PlaySound(TEXT("./assets/sounds/MF7.wav"), NULL, SND_FILENAME | SND_ASYNC);
              Sleep(200);
              }
    if (digit == 8){
              PlaySound(TEXT("./assets/sounds/MF8.wav"), NULL, SND_FILENAME | SND_ASYNC);
              Sleep(200);
              }
    if (digit == 9){
              PlaySound(TEXT("./assets/sounds/MF9.wav"), NULL, SND_FILENAME | SND_ASYNC);
              Sleep(200);
              }
    if (digit == 0){
              PlaySound(TEXT("./assets/sounds/MF0.wav"), NULL, SND_FILENAME | SND_ASYNC);
              Sleep(200);
              }
    }
PlaySound(TEXT("./assets/sounds/MFST.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
return 0;
break;
}
/* If we don't handle a message completely we hand it to the system provided default window function. */
return DefWindowProc (hwnd, nMsg, wParam, lParam);
}

int STDCALL
WinMain (HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nCmdShow)
{
HWND hwnd;/* Handle for the main window. */
MSG msg;/* A Win32 message structure. */
WNDCLASSEX WndClass;/* A window class structure. */
char*szMainWndClass = "PhreakBoxWin";
/* The name of the main window class */

/*
 * First we create a window class for our main window.
 */

/* Initialize the entire structure to zero. */
memset (&WndClass, 0, sizeof(WNDCLASSEX));

WndClass.style = CS_HREDRAW | CS_VREDRAW;
WndClass.cbClsExtra = 0;
WndClass.cbWndExtra = 0;
WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
WndClass.lpszMenuName = NULL;

/* This class is called WinTestWin */
WndClass.lpszClassName = szMainWndClass;

/* cbSize gives the size of the structure for extensibility. */
WndClass.cbSize = sizeof(WNDCLASSEX);

/* All windows of this class redraw when resized. */
WndClass.style = CS_HREDRAW | CS_VREDRAW;

/* All windows of this class use the WndProc window function. */
WndClass.lpfnWndProc = WndProc;

/* This class is used with the current program instance. */
WndClass.hInstance = hInst;

/* Use WndProc application icon and arrow cursor provided by the OS */
WndClass.hIcon = LoadIcon (NULL, IDI_APPLICATION);
WndClass.hIconSm = LoadIcon (NULL, IDI_ASTERISK);
WndClass.hCursor = LoadCursor (NULL, IDC_ARROW);

/* Color the background white */
//WndClass.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
WndClass.hbrBackground = CreatePatternBrush((HBITMAP)LoadImage(NULL, "./assets/bg.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE));
/*
 * Now register the window class for use.
 */
RegisterClassEx (&WndClass);

/*
 * Create our main window using that window class.
 */
hwnd = CreateWindow (
szMainWndClass,/* Class name */
"PhreakBox v1.3",/* Caption */
WS_SYSMENU,/* Styles: WS_CAPTION = no close button!!! HAHAHAHAHA!!! */
CW_USEDEFAULT,/* Initial x (use default) */
CW_USEDEFAULT,/* Initial y (use default) */
550,/* Initial x size (use default) */
372,/* Initial y size (use default) */
NULL,/* No parent window */
NULL,/* No menu */
hInst,/* This program instance */
NULL/* Creation parameters */
);

/*
 * Display the window which we just created (using the nCmdShow
 * passed by the OS, which allows for start minimized and that
 * sort of thing).
 */
ShowWindow (hwnd, nCmdShow);
UpdateWindow (hwnd);
//HWND background = CreateWindow("STATIC", "background", SS_BITMAP | WS_CHILD | WS_VISIBLE, 0, 0, 500, 500, hwnd, NULL, NULL, NULL);
//HBITMAP hBmp = (HBITMAP)LoadImage(NULL, "logo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//FSendMessage(background, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBmp);

/*
 * The main message loop. All messages being sent to the windows
 * of the application (or at least the primary thread) are retrieved
 * by the GetMessage call, then translated (mainly for keyboard
 * messages) and dispatched to the appropriate window procedure.
 * This is the simplest kind of message loop. More complex loops
 * are required for idle processing or handling modeless dialog
 * boxes. When one of the windows calls PostQuitMessage GetMessage
 * will return zero and the wParam of the message will be filled
 * with the argument to PostQuitMessage. The loop will end and
 * the application will close.
*/
while (GetMessage (&msg, NULL, 0, 0))
{
TranslateMessage (&msg);
DispatchMessage (&msg);
}
return msg.wParam;
}

