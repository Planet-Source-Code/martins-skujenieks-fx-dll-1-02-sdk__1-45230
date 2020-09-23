Attribute VB_Name = "modOnTop"

Option Explicit

    Private Const HWND_TOPMOST = -1
    Private Const HWND_NOTOPMOST = -2
    Private Const SWP_NOSIZE = &H1
    Private Const SWP_NOMOVE = &H2
    Private Const SWP_NOACTIVATE = &H10
    Private Const SWP_SHOWWINDOW = &H40
    
    Private Declare Sub SetWindowPos Lib "User32" (ByVal hWnd As Long, ByVal hWndInsertAfter As Long, ByVal X As Long, ByVal Y As Long, ByVal cx As Long, ByVal cy As Long, ByVal wFlags As Long)
    
    
Public Sub MakeTopMost(hWnd As Long)
On Error Resume Next
    SetWindowPos hWnd, HWND_TOPMOST, 0, 0, 0, 0, 3
End Sub


Public Sub MakeNormal(hWnd As Long)
On Error Resume Next
    SetWindowPos hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, 3
End Sub
