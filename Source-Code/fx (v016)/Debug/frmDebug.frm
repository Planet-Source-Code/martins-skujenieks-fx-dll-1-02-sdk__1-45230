VERSION 5.00
Begin VB.Form frmDebug 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "FX.DLL 0.16 Debug"
   ClientHeight    =   8625
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   9855
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   575
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   657
   StartUpPosition =   2  'CenterScreen
   Begin VB.PictureBox Picture2 
      Height          =   8415
      Left            =   4800
      ScaleHeight     =   557
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   325
      TabIndex        =   3
      Top             =   120
      Width           =   4935
      Begin VB.PictureBox Picture3 
         Appearance      =   0  'Flat
         BorderStyle     =   0  'None
         ForeColor       =   &H80000008&
         Height          =   11640
         Left            =   30
         ScaleHeight     =   776
         ScaleMode       =   3  'Pixel
         ScaleWidth      =   305
         TabIndex        =   4
         Top             =   0
         Width           =   4575
         Begin VB.CommandButton Command7 
            Caption         =   "fxBlur"
            BeginProperty Font 
               Name            =   "Courier New"
               Size            =   9.75
               Charset         =   186
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   345
            Left            =   2280
            TabIndex        =   46
            Top             =   11220
            Width           =   2175
         End
         Begin VB.CommandButton Command1 
            Caption         =   "fxBitBlt"
            BeginProperty Font 
               Name            =   "Courier New"
               Size            =   9.75
               Charset         =   186
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   345
            Left            =   0
            TabIndex        =   45
            Top             =   11220
            Width           =   2175
         End
         Begin VB.CommandButton Command2 
            Caption         =   "fxStretchBlt"
            BeginProperty Font 
               Name            =   "Courier New"
               Size            =   9.75
               Charset         =   186
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   345
            Left            =   0
            TabIndex        =   44
            Top             =   10890
            Width           =   2175
         End
         Begin VB.CommandButton Command3 
            Caption         =   "fxTransparentBlt"
            BeginProperty Font 
               Name            =   "Courier New"
               Size            =   9.75
               Charset         =   186
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   345
            Left            =   0
            TabIndex        =   43
            Top             =   10560
            Width           =   2175
         End
         Begin VB.CommandButton Command5 
            Caption         =   "fxGreyscale"
            BeginProperty Font 
               Name            =   "Courier New"
               Size            =   9.75
               Charset         =   186
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   345
            Left            =   2280
            TabIndex        =   42
            Top             =   10890
            Width           =   2175
         End
         Begin VB.CommandButton Command4 
            Caption         =   "fxInvert"
            BeginProperty Font 
               Name            =   "Courier New"
               Size            =   9.75
               Charset         =   186
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   345
            Left            =   2280
            TabIndex        =   41
            Top             =   10560
            Width           =   2175
         End
         Begin VB.Frame Frame9 
            Caption         =   "fxScanlines"
            BeginProperty Font 
               Name            =   "Courier New"
               Size            =   9.75
               Charset         =   186
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   2055
            Left            =   0
            TabIndex        =   32
            Top             =   8400
            Width           =   4575
            Begin VB.HScrollBar HScroll13 
               Height          =   255
               Left            =   840
               Max             =   255
               TabIndex        =   37
               Top             =   360
               Width           =   3495
            End
            Begin VB.HScrollBar HScroll14 
               Height          =   255
               Left            =   840
               Max             =   255
               TabIndex        =   36
               Top             =   720
               Width           =   3495
            End
            Begin VB.HScrollBar HScroll15 
               Height          =   255
               Left            =   840
               Max             =   255
               TabIndex        =   35
               Top             =   1080
               Width           =   3495
            End
            Begin VB.CheckBox Check2 
               Caption         =   "Horizontal"
               Height          =   255
               Left            =   240
               TabIndex        =   34
               Top             =   1440
               Width           =   1455
            End
            Begin VB.CheckBox Check3 
               Caption         =   "Vertical"
               Height          =   255
               Left            =   240
               TabIndex        =   33
               Top             =   1680
               Width           =   975
            End
            Begin VB.Label Label4 
               Caption         =   "Red"
               BeginProperty Font 
                  Name            =   "Courier New"
                  Size            =   8.25
                  Charset         =   186
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   255
               Left            =   240
               TabIndex        =   40
               Top             =   360
               Width           =   615
            End
            Begin VB.Label Label10 
               Caption         =   "Green"
               BeginProperty Font 
                  Name            =   "Courier New"
                  Size            =   8.25
                  Charset         =   186
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   255
               Left            =   240
               TabIndex        =   39
               Top             =   720
               Width           =   615
            End
            Begin VB.Label Label11 
               Caption         =   "Blue"
               BeginProperty Font 
                  Name            =   "Courier New"
                  Size            =   8.25
                  Charset         =   186
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   255
               Left            =   240
               TabIndex        =   38
               Top             =   1080
               Width           =   615
            End
         End
         Begin VB.Frame Frame1 
            Caption         =   "fxAlphaBlend"
            BeginProperty Font 
               Name            =   "Courier New"
               Size            =   9.75
               Charset         =   186
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   1095
            Left            =   0
            TabIndex        =   29
            Top             =   0
            Width           =   4575
            Begin VB.HScrollBar HScroll1 
               Height          =   255
               Left            =   240
               Max             =   255
               TabIndex        =   31
               Top             =   360
               Width           =   4095
            End
            Begin VB.CheckBox Check1 
               Caption         =   "transparent color"
               BeginProperty Font 
                  Name            =   "Courier New"
                  Size            =   8.25
                  Charset         =   204
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   255
               Left            =   240
               TabIndex        =   30
               Top             =   720
               Width           =   2295
            End
         End
         Begin VB.Frame Frame2 
            Caption         =   "fxBrightness"
            BeginProperty Font 
               Name            =   "Courier New"
               Size            =   9.75
               Charset         =   186
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   855
            Left            =   0
            TabIndex        =   27
            Top             =   1200
            Width           =   4575
            Begin VB.HScrollBar HScroll2 
               Height          =   255
               Left            =   240
               Max             =   255
               Min             =   -255
               TabIndex        =   28
               Top             =   360
               Width           =   4095
            End
         End
         Begin VB.Frame Frame3 
            Caption         =   "fxAmbientLight"
            BeginProperty Font 
               Name            =   "Courier New"
               Size            =   9.75
               Charset         =   186
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   2055
            Left            =   0
            TabIndex        =   18
            Top             =   4080
            Width           =   4575
            Begin VB.HScrollBar HScroll3 
               Height          =   255
               Left            =   840
               Max             =   255
               TabIndex        =   22
               Top             =   360
               Width           =   3495
            End
            Begin VB.HScrollBar HScroll4 
               Height          =   255
               Left            =   840
               Max             =   255
               TabIndex        =   21
               Top             =   720
               Width           =   3495
            End
            Begin VB.HScrollBar HScroll5 
               Height          =   255
               Left            =   840
               Max             =   255
               TabIndex        =   20
               Top             =   1080
               Width           =   3495
            End
            Begin VB.HScrollBar HScroll7 
               Height          =   255
               Left            =   840
               Max             =   255
               TabIndex        =   19
               Top             =   1560
               Width           =   3495
            End
            Begin VB.Label Label1 
               Caption         =   "Red"
               BeginProperty Font 
                  Name            =   "Courier New"
                  Size            =   8.25
                  Charset         =   186
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   255
               Left            =   240
               TabIndex        =   26
               Top             =   360
               Width           =   615
            End
            Begin VB.Label Label2 
               Caption         =   "Green"
               BeginProperty Font 
                  Name            =   "Courier New"
                  Size            =   8.25
                  Charset         =   186
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   255
               Left            =   240
               TabIndex        =   25
               Top             =   720
               Width           =   615
            End
            Begin VB.Label Label3 
               Caption         =   "Blue"
               BeginProperty Font 
                  Name            =   "Courier New"
                  Size            =   8.25
                  Charset         =   186
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   255
               Left            =   240
               TabIndex        =   24
               Top             =   1080
               Width           =   615
            End
            Begin VB.Label Label5 
               Caption         =   "Intens"
               BeginProperty Font 
                  Name            =   "Courier New"
                  Size            =   8.25
                  Charset         =   186
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   255
               Left            =   240
               TabIndex        =   23
               Top             =   1560
               Width           =   615
            End
         End
         Begin VB.Frame Frame7 
            Caption         =   "fxGamma"
            BeginProperty Font 
               Name            =   "Courier New"
               Size            =   9.75
               Charset         =   186
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   855
            Left            =   0
            TabIndex        =   16
            Top             =   2160
            Width           =   4575
            Begin VB.HScrollBar HScroll8 
               Height          =   255
               Left            =   240
               Max             =   255
               TabIndex        =   17
               Top             =   360
               Value           =   100
               Width           =   4095
            End
         End
         Begin VB.Frame Frame8 
            Caption         =   "fxReplaceColor"
            BeginProperty Font 
               Name            =   "Courier New"
               Size            =   9.75
               Charset         =   186
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   2055
            Left            =   0
            TabIndex        =   7
            Top             =   6240
            Width           =   4575
            Begin VB.HScrollBar HScroll9 
               Height          =   255
               Left            =   840
               Max             =   255
               TabIndex        =   11
               Top             =   1560
               Width           =   3495
            End
            Begin VB.HScrollBar HScroll10 
               Height          =   255
               Left            =   840
               Max             =   255
               TabIndex        =   10
               Top             =   1080
               Width           =   3495
            End
            Begin VB.HScrollBar HScroll11 
               Height          =   255
               Left            =   840
               Max             =   255
               TabIndex        =   9
               Top             =   720
               Width           =   3495
            End
            Begin VB.HScrollBar HScroll12 
               Height          =   255
               Left            =   840
               Max             =   255
               TabIndex        =   8
               Top             =   360
               Width           =   3495
            End
            Begin VB.Label Label6 
               Caption         =   "Similarity"
               BeginProperty Font 
                  Name            =   "Courier New"
                  Size            =   8.25
                  Charset         =   186
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   255
               Left            =   240
               TabIndex        =   15
               Top             =   1560
               Width           =   615
            End
            Begin VB.Label Label7 
               Caption         =   "Blue"
               BeginProperty Font 
                  Name            =   "Courier New"
                  Size            =   8.25
                  Charset         =   186
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   255
               Left            =   240
               TabIndex        =   14
               Top             =   1080
               Width           =   615
            End
            Begin VB.Label Label8 
               Caption         =   "Green"
               BeginProperty Font 
                  Name            =   "Courier New"
                  Size            =   8.25
                  Charset         =   186
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   255
               Left            =   240
               TabIndex        =   13
               Top             =   720
               Width           =   615
            End
            Begin VB.Label Label9 
               Caption         =   "Red"
               BeginProperty Font 
                  Name            =   "Courier New"
                  Size            =   8.25
                  Charset         =   186
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   255
               Left            =   240
               TabIndex        =   12
               Top             =   360
               Width           =   615
            End
         End
         Begin VB.Frame Frame4 
            Caption         =   "fxReduceColors"
            BeginProperty Font 
               Name            =   "Courier New"
               Size            =   9.75
               Charset         =   186
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   855
            Left            =   0
            TabIndex        =   5
            Top             =   3120
            Width           =   4575
            Begin VB.HScrollBar HScroll6 
               Height          =   255
               Left            =   240
               Max             =   255
               TabIndex        =   6
               Top             =   360
               Value           =   100
               Width           =   4095
            End
         End
      End
      Begin VB.VScrollBar VScroll1 
         Height          =   8355
         Left            =   4620
         Max             =   776
         TabIndex        =   47
         Top             =   0
         Width           =   255
      End
   End
   Begin VB.PictureBox Picture1 
      AutoRedraw      =   -1  'True
      AutoSize        =   -1  'True
      Height          =   4215
      Left            =   120
      ScaleHeight     =   277
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   301
      TabIndex        =   1
      Top             =   4350
      Width           =   4575
      Begin VB.PictureBox picSrc 
         Appearance      =   0  'Flat
         AutoRedraw      =   -1  'True
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         BorderStyle     =   0  'None
         ClipControls    =   0   'False
         ForeColor       =   &H80000008&
         Height          =   5490
         Left            =   0
         ScaleHeight     =   366
         ScaleMode       =   3  'Pixel
         ScaleWidth      =   535
         TabIndex        =   2
         TabStop         =   0   'False
         Top             =   0
         Visible         =   0   'False
         Width           =   8025
      End
   End
   Begin VB.PictureBox picDest 
      AutoRedraw      =   -1  'True
      BackColor       =   &H00FF00FF&
      Height          =   4215
      Left            =   120
      Picture         =   "frmDebug.frx":0000
      ScaleHeight     =   277
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   301
      TabIndex        =   0
      Top             =   120
      Width           =   4575
   End
End
Attribute VB_Name = "frmDebug"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

    Private Declare Function fxGamma Lib "fx.dll" (ByVal DestDC As Long, _
                                                             ByVal DestX As Long, _
                                                             ByVal DestY As Long, _
                                                             ByVal DestWidth As Long, _
                                                             ByVal DestHeight As Long, _
                                                             ByVal SrcDC As Long, _
                                                             ByVal SrcX As Long, _
                                                             ByVal SrcY As Long, _
                                                             ByVal SrcWidth As Long, _
                                                             ByVal SrcHeight As Long, _
                                                             ByVal Gamma As Long) As Long
                                                             
    Private Declare Function fxAntiAlias Lib "fx.dll" (ByVal DestDC As Long, _
                                                             ByVal DestX As Long, _
                                                             ByVal DestY As Long, _
                                                             ByVal DestWidth As Long, _
                                                             ByVal DestHeight As Long, _
                                                             ByVal SrcDC As Long, _
                                                             ByVal SrcX As Long, _
                                                             ByVal SrcY As Long, _
                                                             ByVal SrcWidth As Long, _
                                                             ByVal SrcHeight As Long) As Long
                            
                            
    Private Declare Function fxBlur Lib "fx.dll" (ByVal DestDC As Long, _
                                                             ByVal DestX As Long, _
                                                             ByVal DestY As Long, _
                                                             ByVal DestWidth As Long, _
                                                             ByVal DestHeight As Long, _
                                                             ByVal SrcDC As Long, _
                                                             ByVal SrcX As Long, _
                                                             ByVal SrcY As Long, _
                                                             ByVal SrcWidth As Long, _
                                                             ByVal SrcHeight As Long) As Long
                            
    
    Private Declare Function fxAlphaBlend Lib "fx.dll" (ByVal DestDC As Long, _
                                                             ByVal DestX As Long, _
                                                             ByVal DestY As Long, _
                                                             ByVal DestWidth As Long, _
                                                             ByVal DestHeight As Long, _
                                                             ByVal SrcDC As Long, _
                                                             ByVal SrcX As Long, _
                                                             ByVal SrcY As Long, _
                                                             ByVal SrcWidth As Long, _
                                                             ByVal SrcHeight As Long, _
                                                             ByVal AlphaValue As Long, _
                                                             ByVal TransparentColor As Long) As Long
    
    Private Declare Function fxScanlines Lib "fx.dll" (ByVal DestDC As Long, _
                                                             ByVal DestX As Long, _
                                                             ByVal DestY As Long, _
                                                             ByVal DestWidth As Long, _
                                                             ByVal DestHeight As Long, _
                                                             ByVal SrcDC As Long, _
                                                             ByVal SrcX As Long, _
                                                             ByVal SrcY As Long, _
                                                             ByVal SrcWidth As Long, _
                                                             ByVal SrcHeight As Long, _
                                                             ByVal Color As Long, _
                                                             ByVal Flags As Long) As Long
    
    Private Declare Function fxBrightness Lib "fx.dll" (ByVal DestDC As Long, _
                                                             ByVal DestX As Long, _
                                                             ByVal DestY As Long, _
                                                             ByVal DestWidth As Long, _
                                                             ByVal DestHeight As Long, _
                                                             ByVal SrcDC As Long, _
                                                             ByVal SrcX As Long, _
                                                             ByVal SrcY As Long, _
                                                             ByVal SrcWidth As Long, _
                                                             ByVal SrcHeight As Long, _
                                                             ByVal Brightness As Long) As Long
                                                    
    Private Declare Function fxFilter Lib "fx.dll" (ByVal DestDC As Long, _
                                                             ByVal DestX As Long, _
                                                             ByVal DestY As Long, _
                                                             ByVal DestWidth As Long, _
                                                             ByVal DestHeight As Long, _
                                                             ByVal SrcDC As Long, _
                                                             ByVal SrcX As Long, _
                                                             ByVal SrcY As Long, _
                                                             ByVal SrcWidth As Long, _
                                                             ByVal SrcHeight As Long, _
                                                             ByVal Filter As Long, _
                                                             ByVal Color As Long, _
                                                             ByVal Flags As Long) As Long
                                                    
    Private Declare Function fxAmbientLight Lib "fx.dll" (ByVal DestDC As Long, _
                                                             ByVal DestX As Long, _
                                                             ByVal DestY As Long, _
                                                             ByVal DestWidth As Long, _
                                                             ByVal DestHeight As Long, _
                                                             ByVal SrcDC As Long, _
                                                             ByVal SrcX As Long, _
                                                             ByVal SrcY As Long, _
                                                             ByVal SrcWidth As Long, _
                                                             ByVal SrcHeight As Long, _
                                                             ByVal Color As Long, _
                                                             ByVal Intensity As Long) As Long
                                                             
    Private Declare Function fxReplaceColor Lib "fx.dll" (ByVal DestDC As Long, _
                                                             ByVal DestX As Long, _
                                                             ByVal DestY As Long, _
                                                             ByVal DestWidth As Long, _
                                                             ByVal DestHeight As Long, _
                                                             ByVal SrcDC As Long, _
                                                             ByVal SrcX As Long, _
                                                             ByVal SrcY As Long, _
                                                             ByVal SrcWidth As Long, _
                                                             ByVal SrcHeight As Long, _
                                                             ByVal Color As Long, _
                                                             ByVal ReplaceColor As Long, _
                                                             ByVal Similarity As Long) As Long
                                                             
                                                                                                    
    Private Declare Function fxBitBlt Lib "fx.dll" (ByVal DestDC As Long, _
                                                             ByVal DestX As Long, _
                                                             ByVal DestY As Long, _
                                                             ByVal DestWidth As Long, _
                                                             ByVal DestHeight As Long, _
                                                             ByVal SrcDC As Long, _
                                                             ByVal SrcX As Long, _
                                                             ByVal SrcY As Long, _
                                                             ByVal RasterOpt As Long) As Long
                                                                                         
    Private Declare Function fxStretchBlt Lib "fx.dll" (ByVal DestDC As Long, _
                                                             ByVal DestX As Long, _
                                                             ByVal DestY As Long, _
                                                             ByVal DestWidth As Long, _
                                                             ByVal DestHeight As Long, _
                                                             ByVal SrcDC As Long, _
                                                             ByVal SrcX As Long, _
                                                             ByVal SrcY As Long, _
                                                             ByVal SrcWidth As Long, _
                                                             ByVal SrcHeight As Long, _
                                                             ByVal RasterOpt As Long) As Long
                                                                                       
    Private Declare Function fxTransparentBlt Lib "fx.dll" (ByVal DestDC As Long, _
                                                             ByVal DestX As Long, _
                                                             ByVal DestY As Long, _
                                                             ByVal DestWidth As Long, _
                                                             ByVal DestHeight As Long, _
                                                             ByVal SrcDC As Long, _
                                                             ByVal SrcX As Long, _
                                                             ByVal SrcY As Long, _
                                                             ByVal SrcWidth As Long, _
                                                             ByVal SrcHeight As Long, _
                                                             ByVal TransparentColor As Long) As Long
                                                                                       
    Private Declare Function fxRGB Lib "fx.dll" (ByVal R As Long, _
                                                      ByVal G As Long, _
                                                      ByVal B As Long) As Long
    
    Private Declare Function fxShadeColors Lib "fx.dll" (ByVal DestPx As Long, _
                                                      ByVal SrcPx As Long, _
                                                      ByVal ShadeValue As Long) As Long
    
    Private Declare Function GetDC Lib "user32" (ByVal hwnd As Long) As Long
    Private Declare Function GetDesktopWindow Lib "user32" () As Long
    Private Declare Function GetTickCount Lib "kernel32" () As Long


Private Sub Check1_Click()
    HScroll1_Scroll
End Sub

Private Sub Check2_Click()
    HScroll15_Scroll
End Sub

Private Sub Check3_Click()
HScroll15_Scroll
End Sub

Private Sub Command1_Click()
    
    Dim sTmr As Long
    Dim eTmr As Long
    Dim X As Long
    
    sTmr = GetTickCount
    
    picDest.Cls
    fxBitBlt picDest.hDC, 0, 0, 250, 250, picSrc.hDC, 0, 0, vbSrcCopy
    picDest.Refresh
    
    eTmr = GetTickCount
    
    Me.Caption = "fxBitBlt (" & eTmr - sTmr & "ms)"

End Sub



Private Sub Command2_Click()

    Dim sTmr As Long
    Dim eTmr As Long
    Dim X As Long
    
    sTmr = GetTickCount
    
    picDest.Cls
    fxStretchBlt picDest.hDC, 0, 0, 250, 250, picSrc.hDC, 0, 0, 125, 125, vbSrcCopy
    picDest.Refresh
    
    eTmr = GetTickCount
    
    Me.Caption = "fxStretchBlt (" & eTmr - sTmr & "ms)"

End Sub


Private Sub Command3_Click()

    Dim sTmr As Long
    Dim eTmr As Long
    Dim X As Long
    
    sTmr = GetTickCount
    
    picDest.Cls
    fxTransparentBlt picDest.hDC, 0, 0, 250, 250, picSrc.hDC, 0, 0, 250, 250, vbWhite
    picDest.Refresh
    
    eTmr = GetTickCount
    
    Me.Caption = "fxTransparentBlt (" & eTmr - sTmr & "ms)"

End Sub


Private Sub Command4_Click()

    Dim sTmr As Long
    Dim eTmr As Long
    Dim X As Long
    
    sTmr = GetTickCount
    
    picDest.Cls
    fxFilter picDest.hDC, 0, 0, 250, 250, picDest.hDC, 0, 0, 250, 250, 1, 0, 0
    picDest.Refresh
    
    eTmr = GetTickCount
    
    Me.Caption = "fxFilter - Invert (" & eTmr - sTmr & "ms)"

End Sub

Private Sub Command5_Click()

    Dim sTmr As Long
    Dim eTmr As Long
    Dim X As Long
    
    sTmr = GetTickCount
    
    picDest.Cls
    fxFilter picDest.hDC, 0, 0, 250, 250, picDest.hDC, 0, 0, 250, 250, 2, 0, 0
    picDest.Refresh
    
    eTmr = GetTickCount
    
    Me.Caption = "fxFilter - Greyscale (" & eTmr - sTmr & "ms)"

End Sub


Private Sub Command7_Click()

    Dim sTmr As Long
    Dim eTmr As Long
    Dim MaskColor As Long
       
    sTmr = GetTickCount
    
    picDest.Cls
    fxBlur picDest.hDC, 0, 0, 250, 250, picSrc.hDC, 0, 0, 250, 250
    picDest.Refresh
    
    eTmr = GetTickCount
    
    Me.Caption = "fxBlur (" & eTmr - sTmr & "ms)"
    
End Sub


Private Sub Form_Load()

    VScroll1.Max = Picture3.ScaleHeight - Picture2.ScaleHeight
    
    fxBitBlt picSrc.hDC, 0, 0, 320, 320, GetDC(GetDesktopWindow), 0, 0, vbSrcCopy
    picSrc.Picture = picSrc.Image
    
    Me.Show
    DoEvents
    
End Sub

Private Sub HScroll1_Change()
    HScroll1_Scroll
End Sub


Private Sub HScroll1_Scroll()

    Dim sTmr As Long
    Dim eTmr As Long
    Dim Flag As Long
    
    If Check1.Value = vbChecked Then
        Flag = vbGreen
    Else
        Flag = -1
    End If
    
    sTmr = GetTickCount
    
    picDest.Cls
    fxAlphaBlend picDest.hDC, 0, 0, 300, 300, picSrc.hDC, 0, 0, 300, 300, HScroll1.Value, Flag
    picDest.Refresh
    
    eTmr = GetTickCount - sTmr
    
    Me.Caption = "fxAlphaBlend (" & eTmr & "ms)"

End Sub


Private Sub HScroll10_Change()
    HScroll9_Scroll
End Sub

Private Sub HScroll10_Scroll()
    HScroll9_Scroll
End Sub

Private Sub HScroll11_Change()
    HScroll9_Scroll
End Sub

Private Sub HScroll11_Scroll()
    HScroll9_Scroll
End Sub

Private Sub HScroll12_Change()
    HScroll9_Scroll
End Sub

Private Sub HScroll12_Scroll()
    HScroll9_Scroll
End Sub

Private Sub HScroll13_Change()
    HScroll15_Scroll
End Sub

Private Sub HScroll13_Scroll()
    HScroll15_Scroll
End Sub

Private Sub HScroll14_Change()
    HScroll15_Scroll
End Sub

Private Sub HScroll14_Scroll()
    HScroll15_Scroll
End Sub

Private Sub HScroll15_Change()
    HScroll15_Scroll
End Sub

Private Sub HScroll15_Scroll()

    Dim sTmr As Long
    Dim eTmr As Long
    Dim Flag As Long
    
    If (Check2.Value = vbChecked) And (Check3.Value <> vbChecked) Then Flag = 0
    If (Check2.Value <> vbChecked) And (Check3.Value = vbChecked) Then Flag = 1
    If (Check2.Value = vbChecked) And (Check3.Value = vbChecked) Then Flag = 2
              
    sTmr = GetTickCount
    
    picDest.Cls
    fxScanlines picDest.hDC, 0, 0, 250, 250, picDest.hDC, 0, 0, 250, 250, rgb(HScroll13.Value, HScroll14.Value, HScroll15.Value), Flag
    picDest.Refresh
    
    eTmr = GetTickCount - sTmr
    
    Me.Caption = "fxScanlines (" & eTmr & "ms)"
    
End Sub


Private Sub HScroll2_Change()
    HScroll2_Scroll
End Sub

Private Sub HScroll2_Scroll()

    Dim sTmr As Long
    Dim eTmr As Long
    Dim Flag As Long
       
    sTmr = GetTickCount
    
    picDest.Cls
    fxBrightness picDest.hDC, 0, 0, 250, 250, picDest.hDC, 0, 0, 250, 250, HScroll2.Value
    picDest.Refresh
    
    eTmr = GetTickCount - sTmr
    
    Me.Caption = "fxBrightness (" & eTmr & "ms)"

End Sub


Private Sub HScroll3_Change()
    HScroll3_Scroll
End Sub

Private Sub HScroll3_Scroll()

    Dim sTmr As Long
    Dim eTmr As Long
    
    sTmr = GetTickCount
    
    picDest.Cls
    fxAmbientLight picDest.hDC, 0, 0, 250, 250, picDest.hDC, 0, 0, 250, 250, rgb(HScroll3.Value, HScroll4.Value, HScroll5.Value), HScroll7.Value
    picDest.Refresh
    
    eTmr = GetTickCount
    
    Me.Caption = "fxAmbientLight (" & eTmr - sTmr & "ms)"

End Sub


Private Sub HScroll4_Change()
    HScroll3_Scroll
End Sub

Private Sub HScroll4_Scroll()
    HScroll3_Scroll
End Sub

Private Sub HScroll5_Change()
    HScroll3_Scroll
End Sub

Private Sub HScroll5_Scroll()
    HScroll3_Scroll
End Sub

Private Sub HScroll6_Change()
    HScroll6_Scroll
End Sub

Private Sub HScroll6_Scroll()

    Dim sTmr As Long
    Dim eTmr As Long
    
    sTmr = GetTickCount
    
    picDest.Cls
    fxFilter picDest.hDC, 0, 0, 250, 250, picSrc.hDC, 0, 0, 250, 250, 5, 0, HScroll6.Value
    picDest.Refresh
    
    eTmr = GetTickCount
    
    Me.Caption = "fxFilter - Bit-Reduce (" & eTmr - sTmr & "ms)"

End Sub

Private Sub HScroll7_Change()
    HScroll3_Scroll
End Sub

Private Sub HScroll7_Scroll()
    HScroll3_Scroll
End Sub

Private Sub HScroll8_Change()
    HScroll8_Scroll
End Sub


Private Sub HScroll8_Scroll()

    Dim sTmr As Long
    Dim eTmr As Long
    Dim Flag As Long
       
    sTmr = GetTickCount
    
    picDest.Cls
    fxGamma picDest.hDC, 0, 0, 100, 100, picDest.hDC, 0, 0, 100, 100, HScroll8.Value
    picDest.Refresh
    
    eTmr = GetTickCount - sTmr
    
    Me.Caption = "fxGamma (" & eTmr & "ms) " & Int(1000 / eTmr) & " FPS"

End Sub

Private Sub HScroll9_Change()
HScroll9_Scroll
End Sub

Private Sub HScroll9_Scroll()
    Dim sTmr As Long
    Dim eTmr As Long
    Dim MaskColor As Long
           
    sTmr = GetTickCount
    
    picDest.Cls
    fxReplaceColor picDest.hDC, 0, 0, 250, 250, picSrc.hDC, 0, 0, 250, 250, rgb(HScroll12.Value, HScroll11.Value, HScroll10.Value), vbBlack, HScroll9.Value
    picDest.Refresh
    
    eTmr = GetTickCount - sTmr
    
    Me.Caption = "fxReplaceColor (" & eTmr & "ms) " & Int(1000 / eTmr) & " FPS"

End Sub

Private Sub picDest_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)

    Dim COLORREF As Long
    COLORREF = picDest.Point(X, Y)
    
    MsgBox "COLORREF: " & COLORREF & vbCrLf & _
           "Red: " & (COLORREF And &HFF) & vbCrLf & _
           "Green: " & ((COLORREF And &HFF00&) / 256) & vbCrLf & _
           "Blue: " & ((COLORREF And &HFF0000) / 65536)
End Sub


Private Sub VScroll1_Change()
    VScroll1_Scroll
End Sub

Private Sub VScroll1_Scroll()
    Picture3.Top = VScroll1.Value * (-1)
End Sub
