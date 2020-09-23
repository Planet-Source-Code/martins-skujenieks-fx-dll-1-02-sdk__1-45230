Attribute VB_Name = "Base"

    Public fxIndex As Long
    
    Public fxX As Long
    Public fxY As Long
    
    Public fxColor As Long
    Public fxMaskColor As Long
    
    Public Declare Function GetTickCount Lib "kernel32" () As Long
    
    
Public Sub Update()

    Dim Ticks As Long

    With frmMain
    
        DoEvents
    
        .picDest.Cls
        
        Ticks = GetTickCount
    
        Select Case fxIndex
            Case 1000   'Alpha Blending
                fxAlphaBlend .picDest.hDC, 0, 0, 320, 240, .picSrc.hDC, 0, 0, 320, 240, .HScroll1(0).Value, fxMaskColor
            
            Case 1010   'Ambient Light
                fxAmbientLight .picDest.hDC, 0, 0, 320, 240, .picDest.hDC, 0, 0, 320, 240, fxColor, .HScroll1(0).Value
                
            Case 1020   'Blur
                fxBlur .picDest.hDC, 0, 0, 320, 240, .picDest.hDC, 0, 0, 320, 240
            
            Case 1030   'Brightness
                fxBrightness .picDest.hDC, 0, 0, 320, 240, .picDest.hDC, 0, 0, 320, 240, .HScroll1(0).Value
            
            Case 1040
            
            Case 1050   'Emboss
                fxEmboss .picDest.hDC, 0, 0, 320, 240, .picDest.hDC, 0, 0, 320, 240, .HScroll1(0).Value / 100
                
            Case 1060   'Engrave
                fxEngrave .picDest.hDC, 0, 0, 320, 240, .picDest.hDC, 0, 0, 320, 240, .HScroll1(0).Value / 100
                
            Case 1070   'Gamma
                fxGamma .picDest.hDC, 0, 0, 320, 240, .picDest.hDC, 0, 0, 320, 240, .HScroll1(0).Value / 100
                
            Case 1080   'Greyscale
                fxGreyscale .picDest.hDC, 0, 0, 320, 240, .picDest.hDC, 0, 0, 320, 240
                
            Case 1090   'Gridelines
                fxGridelines .picDest.hDC, 0, 0, 320, 240, .picDest.hDC, 0, 0, 320, 240, fxColor, .HScroll1(0).Value, .HScroll1(1).Value
        
            Case 1100   'Hue
                fxHue .picDest.hDC, 0, 0, 320, 240, .picDest.hDC, 0, 0, 320, 240, .HScroll1(0).Value / 100
        
            Case 1110   'Inversion
                fxInversion .picDest.hDC, 0, 0, 320, 240, .picDest.hDC, 0, 0, 320, 240, .HScroll1(0).Value
        
            Case 1120   'Invert
                fxInvert .picDest.hDC, 0, 0, 320, 240, .picDest.hDC, 0, 0, 320, 240
        
            Case 1130   'Light
                fxLight .picDest.hDC, 160, 120, fxColor, 90, .HScroll1(0).Value, .HScroll1(1).Value, 1
        
            Case 1140   'Mosaic
                fxMosaic .picDest.hDC, 0, 0, 320, 240, .picDest.hDC, 0, 0, 320, 240, .HScroll1(0).Value
        
            Case 1150   'Reduce Colors
                fxReduceColors .picDest.hDC, 0, 0, 320, 240, .picDest.hDC, 0, 0, 320, 240, .HScroll1(0).Value
        
            Case 1160   'Relief
                fxRelief .picDest.hDC, 0, 0, 320, 240, .picDest.hDC, 0, 0, 320, 240
                
            Case 1170   'Render
                fxRender .picDest.hDC, fxX, fxY, .picSrc2.hDC, 0, 0, 64, 64, .HScroll1(2).Value, .HScroll1(0).Value, .HScroll1(1).Value / 100, vbMagenta
            
            Case 1180   'Replace Color
                fxReplaceColor .picDest.hDC, 0, 0, 320, 240, .picDest.hDC, 0, 0, 320, 240, fxColor, vbBlack
                    
            Case 1190   'Replace Colors
                fxReplaceColors .picDest.hDC, 0, 0, 320, 240, .picDest.hDC, 0, 0, 320, 240, fxColor, vbBlack, .HScroll1(0).Value

            Case 1200   'Rotate
                fxRotate .picDest.hDC, fxX, fxY, .picSrc2.hDC, 0, 0, 64, 64, .HScroll1(0).Value, vbMagenta

            Case 1210   'Saturation
                fxSaturation .picDest.hDC, 0, 0, 320, 240, .picDest.hDC, 0, 0, 320, 240, .HScroll1(0).Value
       
            Case 1220   'Scanlines
                fxScanlines .picDest.hDC, 0, 0, 320, 240, .picDest.hDC, 0, 0, 320, 240, fxColor, .HScroll1(0).Value, .HScroll1(1).Value, True, False

            Case 1250   'Tone
                fxTone .picDest.hDC, 0, 0, 320, 240, .picDest.hDC, 0, 0, 320, 240, fxColor, .HScroll1(0).Value

            Case 1260   'Zoom
                fxZoom .picDest.hDC, fxX, fxY, .picSrc2.hDC, 0, 0, 64, 64, .HScroll1(0).Value / 100, vbMagenta

        End Select
        
        Ticks = GetTickCount - Ticks
        
        .picDest.Refresh
        
        frmMain.Label5.Caption = Ticks & " ms/frame"
            
        DoEvents
        
    End With

End Sub

    
    

