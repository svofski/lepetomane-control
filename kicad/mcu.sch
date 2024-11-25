EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 2 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L as5600:AS5600 U?
U 1 1 61D9670E
P 2950 7550
AR Path="/61D9670E" Ref="U?"  Part="1" 
AR Path="/61D933FF/61D9670E" Ref="U5"  Part="1" 
F 0 "U5" H 3150 7050 50  0000 L CNN
F 1 "AS5600" H 3150 6950 50  0000 L CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 2950 7550 50  0001 C CNN
F 3 "" H 2950 7550 50  0001 C CNN
	1    2950 7550
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:STM32F103C4Tx-stm32 U4
U 1 1 61D96EF0
P 5050 3350
F 0 "U4" H 5400 5300 50  0000 C CNN
F 1 "STM32F103C4Tx" H 5650 5200 50  0000 C CNN
F 2 "Housings_QFP:LQFP-48_7x7mm_Pitch0.5mm" H 7550 5025 50  0001 R TNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00210843.pdf" H 5050 3350 50  0001 C CNN
	1    5050 3350
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:GND-power #PWR021
U 1 1 61D9C2E6
P 2950 8200
F 0 "#PWR021" H 2950 7950 50  0001 C CNN
F 1 "GND" H 2955 8027 50  0001 C CNN
F 2 "" H 2950 8200 50  0001 C CNN
F 3 "" H 2950 8200 50  0001 C CNN
	1    2950 8200
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:C_Small-device C9
U 1 1 61DA6E0F
P 3300 6850
F 0 "C9" H 3392 6896 50  0000 L CNN
F 1 "100nF" H 3392 6805 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 3300 6850 50  0001 C CNN
F 3 "~" H 3300 6850 50  0001 C CNN
	1    3300 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 6900 3050 6750
Wire Wire Line
	3050 6750 3300 6750
$Comp
L lepetocontrol-rescue:GND-power #PWR023
U 1 1 61DA7862
P 3300 6950
F 0 "#PWR023" H 3300 6700 50  0001 C CNN
F 1 "GND" H 3305 6777 50  0001 C CNN
F 2 "" H 3300 6950 50  0001 C CNN
F 3 "" H 3300 6950 50  0001 C CNN
	1    3300 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 6900 2850 6750
Wire Wire Line
	2850 6750 3050 6750
Connection ~ 3050 6750
$Comp
L lepetocontrol-rescue:GND-power #PWR017
U 1 1 61DAABF2
P 2400 7400
F 0 "#PWR017" H 2400 7150 50  0001 C CNN
F 1 "GND" H 2405 7227 50  0001 C CNN
F 2 "" H 2400 7400 50  0001 C CNN
F 3 "" H 2400 7400 50  0001 C CNN
	1    2400 7400
	0    1    1    0   
$EndComp
$Comp
L lepetocontrol-rescue:R-device R22
U 1 1 61DAB5EA
P 1900 6500
F 0 "R22" H 1970 6546 50  0000 L CNN
F 1 "2K7" H 1970 6455 50  0000 L CNN
F 2 "Resistors_SMD:R_0805" V 1830 6500 50  0001 C CNN
F 3 "~" H 1900 6500 50  0001 C CNN
	1    1900 6500
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:R-device R20
U 1 1 61DABD82
P 1750 6650
F 0 "R20" H 1681 6604 50  0000 R CNN
F 1 "2K7" H 1681 6695 50  0000 R CNN
F 2 "Resistors_SMD:R_0805" V 1680 6650 50  0001 C CNN
F 3 "~" H 1750 6650 50  0001 C CNN
	1    1750 6650
	1    0    0    1   
$EndComp
Wire Wire Line
	1750 6500 1750 6300
$Comp
L lepetocontrol-rescue:VCC-power #PWR?
U 1 1 61DAF613
P 2850 6700
AR Path="/61DAF613" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/61DAF613" Ref="#PWR019"  Part="1" 
F 0 "#PWR019" H 2850 6550 50  0001 C CNN
F 1 "VCC" V 2750 6700 50  0000 L CNN
F 2 "" H 2850 6700 50  0001 C CNN
F 3 "" H 2850 6700 50  0001 C CNN
	1    2850 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 6700 2850 6750
Connection ~ 2850 6750
$Comp
L lepetocontrol-rescue:VCC-power #PWR?
U 1 1 61DAF83F
P 1900 6050
AR Path="/61DAF83F" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/61DAF83F" Ref="#PWR015"  Part="1" 
F 0 "#PWR015" H 1900 5900 50  0001 C CNN
F 1 "VCC" V 1800 6050 50  0000 L CNN
F 2 "" H 1900 6050 50  0001 C CNN
F 3 "" H 1900 6050 50  0001 C CNN
	1    1900 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 6050 1900 6300
Wire Wire Line
	1750 6300 1900 6300
Connection ~ 1900 6300
Wire Wire Line
	1900 6300 1900 6350
Text Label 2000 7600 0    50   ~ 0
SDA
NoConn ~ 2400 7750
Wire Wire Line
	3500 7550 3800 7550
$Comp
L as5600:AS5600 U?
U 1 1 61DB6D44
P 5400 7550
AR Path="/61DB6D44" Ref="U?"  Part="1" 
AR Path="/61D933FF/61DB6D44" Ref="U7"  Part="1" 
F 0 "U7" H 5600 7050 50  0000 L CNN
F 1 "AS5600" H 5600 6950 50  0000 L CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 5400 7550 50  0001 C CNN
F 3 "" H 5400 7550 50  0001 C CNN
	1    5400 7550
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:GND-power #PWR029
U 1 1 61DB6D4A
P 5400 8200
F 0 "#PWR029" H 5400 7950 50  0001 C CNN
F 1 "GND" H 5405 8027 50  0001 C CNN
F 2 "" H 5400 8200 50  0001 C CNN
F 3 "" H 5400 8200 50  0001 C CNN
	1    5400 8200
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:C_Small-device C11
U 1 1 61DB6D50
P 5750 6850
F 0 "C11" H 5842 6896 50  0000 L CNN
F 1 "100nF" H 5842 6805 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5750 6850 50  0001 C CNN
F 3 "~" H 5750 6850 50  0001 C CNN
	1    5750 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 6900 5500 6750
Wire Wire Line
	5500 6750 5750 6750
$Comp
L lepetocontrol-rescue:GND-power #PWR031
U 1 1 61DB6D58
P 5750 6950
F 0 "#PWR031" H 5750 6700 50  0001 C CNN
F 1 "GND" H 5755 6777 50  0001 C CNN
F 2 "" H 5750 6950 50  0001 C CNN
F 3 "" H 5750 6950 50  0001 C CNN
	1    5750 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 6900 5300 6750
Wire Wire Line
	5300 6750 5500 6750
Connection ~ 5500 6750
$Comp
L lepetocontrol-rescue:GND-power #PWR025
U 1 1 61DB6D61
P 4850 7400
F 0 "#PWR025" H 4850 7150 50  0001 C CNN
F 1 "GND" H 4855 7227 50  0001 C CNN
F 2 "" H 4850 7400 50  0001 C CNN
F 3 "" H 4850 7400 50  0001 C CNN
	1    4850 7400
	0    1    1    0   
$EndComp
$Comp
L lepetocontrol-rescue:VCC-power #PWR?
U 1 1 61DB6D78
P 5300 6700
AR Path="/61DB6D78" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/61DB6D78" Ref="#PWR027"  Part="1" 
F 0 "#PWR027" H 5300 6550 50  0001 C CNN
F 1 "VCC" V 5200 6700 50  0000 L CNN
F 2 "" H 5300 6700 50  0001 C CNN
F 3 "" H 5300 6700 50  0001 C CNN
	1    5300 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 6700 5300 6750
Connection ~ 5300 6750
Text Label 4450 7600 0    50   ~ 0
SDA
NoConn ~ 4850 7750
Wire Wire Line
	5950 7550 6250 7550
Wire Wire Line
	4450 7600 4850 7600
$Comp
L as5600:AS5600 U?
U 1 1 61DB9A4C
P 7800 7550
AR Path="/61DB9A4C" Ref="U?"  Part="1" 
AR Path="/61D933FF/61DB9A4C" Ref="U9"  Part="1" 
F 0 "U9" H 8000 7050 50  0000 L CNN
F 1 "AS5600" H 8000 6950 50  0000 L CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 7800 7550 50  0001 C CNN
F 3 "" H 7800 7550 50  0001 C CNN
	1    7800 7550
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:GND-power #PWR037
U 1 1 61DB9A52
P 7800 8200
F 0 "#PWR037" H 7800 7950 50  0001 C CNN
F 1 "GND" H 7805 8027 50  0001 C CNN
F 2 "" H 7800 8200 50  0001 C CNN
F 3 "" H 7800 8200 50  0001 C CNN
	1    7800 8200
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:C_Small-device C13
U 1 1 61DB9A58
P 8150 6850
F 0 "C13" H 8242 6896 50  0000 L CNN
F 1 "100nF" H 8242 6805 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 8150 6850 50  0001 C CNN
F 3 "~" H 8150 6850 50  0001 C CNN
	1    8150 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 6900 7900 6750
Wire Wire Line
	7900 6750 8150 6750
$Comp
L lepetocontrol-rescue:GND-power #PWR039
U 1 1 61DB9A60
P 8150 6950
F 0 "#PWR039" H 8150 6700 50  0001 C CNN
F 1 "GND" H 8155 6777 50  0001 C CNN
F 2 "" H 8150 6950 50  0001 C CNN
F 3 "" H 8150 6950 50  0001 C CNN
	1    8150 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 6900 7700 6750
Wire Wire Line
	7700 6750 7900 6750
Connection ~ 7900 6750
$Comp
L lepetocontrol-rescue:GND-power #PWR033
U 1 1 61DB9A69
P 7250 7400
F 0 "#PWR033" H 7250 7150 50  0001 C CNN
F 1 "GND" H 7255 7227 50  0001 C CNN
F 2 "" H 7250 7400 50  0001 C CNN
F 3 "" H 7250 7400 50  0001 C CNN
	1    7250 7400
	0    1    1    0   
$EndComp
$Comp
L lepetocontrol-rescue:VCC-power #PWR?
U 1 1 61DB9A6F
P 7700 6700
AR Path="/61DB9A6F" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/61DB9A6F" Ref="#PWR035"  Part="1" 
F 0 "#PWR035" H 7700 6550 50  0001 C CNN
F 1 "VCC" V 7600 6700 50  0000 L CNN
F 2 "" H 7700 6700 50  0001 C CNN
F 3 "" H 7700 6700 50  0001 C CNN
	1    7700 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 6700 7700 6750
Connection ~ 7700 6750
Text Label 6850 7600 0    50   ~ 0
SDA
NoConn ~ 7250 7750
Wire Wire Line
	8350 7550 8650 7550
Text Label 8650 7550 2    50   ~ 0
SENSE3
Wire Wire Line
	6850 7600 7250 7600
$Comp
L as5600:AS5600 U?
U 1 1 61DBC588
P 10200 7550
AR Path="/61DBC588" Ref="U?"  Part="1" 
AR Path="/61D933FF/61DBC588" Ref="U11"  Part="1" 
F 0 "U11" H 10400 7050 50  0000 L CNN
F 1 "AS5600" H 10400 6950 50  0000 L CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 10200 7550 50  0001 C CNN
F 3 "" H 10200 7550 50  0001 C CNN
	1    10200 7550
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:GND-power #PWR045
U 1 1 61DBC58E
P 10200 8200
F 0 "#PWR045" H 10200 7950 50  0001 C CNN
F 1 "GND" H 10205 8027 50  0001 C CNN
F 2 "" H 10200 8200 50  0001 C CNN
F 3 "" H 10200 8200 50  0001 C CNN
	1    10200 8200
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:C_Small-device C15
U 1 1 61DBC594
P 10550 6850
F 0 "C15" H 10642 6896 50  0000 L CNN
F 1 "100nF" H 10642 6805 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 10550 6850 50  0001 C CNN
F 3 "~" H 10550 6850 50  0001 C CNN
	1    10550 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	10300 6900 10300 6750
Wire Wire Line
	10300 6750 10550 6750
$Comp
L lepetocontrol-rescue:GND-power #PWR047
U 1 1 61DBC59C
P 10550 6950
F 0 "#PWR047" H 10550 6700 50  0001 C CNN
F 1 "GND" H 10555 6777 50  0001 C CNN
F 2 "" H 10550 6950 50  0001 C CNN
F 3 "" H 10550 6950 50  0001 C CNN
	1    10550 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 6900 10100 6750
Wire Wire Line
	10100 6750 10300 6750
Connection ~ 10300 6750
$Comp
L lepetocontrol-rescue:GND-power #PWR041
U 1 1 61DBC5A5
P 9650 7400
F 0 "#PWR041" H 9650 7150 50  0001 C CNN
F 1 "GND" H 9655 7227 50  0001 C CNN
F 2 "" H 9650 7400 50  0001 C CNN
F 3 "" H 9650 7400 50  0001 C CNN
	1    9650 7400
	0    1    1    0   
$EndComp
$Comp
L lepetocontrol-rescue:VCC-power #PWR?
U 1 1 61DBC5AB
P 10100 6700
AR Path="/61DBC5AB" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/61DBC5AB" Ref="#PWR043"  Part="1" 
F 0 "#PWR043" H 10100 6550 50  0001 C CNN
F 1 "VCC" V 10000 6700 50  0000 L CNN
F 2 "" H 10100 6700 50  0001 C CNN
F 3 "" H 10100 6700 50  0001 C CNN
	1    10100 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 6700 10100 6750
Connection ~ 10100 6750
Text Label 9250 7600 0    50   ~ 0
SDA
NoConn ~ 9650 7750
Wire Wire Line
	10750 7550 11050 7550
Text Label 11050 7550 2    50   ~ 0
SENSE4
Wire Wire Line
	9250 7600 9650 7600
$Comp
L lepetocontrol-rescue:Crystal-device Y1
U 1 1 61DDB96C
P 1100 2750
F 0 "Y1" V 1054 2881 50  0000 L CNN
F 1 "8MHz" V 1145 2881 50  0000 L CNN
F 2 "Crystals:HC-49V" H 1100 2750 50  0001 C CNN
F 3 "~" H 1100 2750 50  0001 C CNN
	1    1100 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	1500 2900 1100 2900
$Comp
L lepetocontrol-rescue:C_Small-device C1
U 1 1 61DE0EBE
P 750 2650
F 0 "C1" H 658 2604 50  0000 R CNN
F 1 "20p" H 658 2695 50  0000 R CNN
F 2 "Capacitors_SMD:C_0805" H 750 2650 50  0001 C CNN
F 3 "~" H 750 2650 50  0001 C CNN
	1    750  2650
	1    0    0    1   
$EndComp
$Comp
L lepetocontrol-rescue:C_Small-device C2
U 1 1 61DE18A8
P 750 2850
F 0 "C2" H 658 2804 50  0000 R CNN
F 1 "20p" H 658 2895 50  0000 R CNN
F 2 "Capacitors_SMD:C_0805" H 750 2850 50  0001 C CNN
F 3 "~" H 750 2850 50  0001 C CNN
	1    750  2850
	1    0    0    1   
$EndComp
Wire Wire Line
	750  2950 1100 2950
Wire Wire Line
	1100 2950 1100 2900
Connection ~ 1100 2900
Wire Wire Line
	750  2550 1100 2550
Wire Wire Line
	1100 2550 1100 2600
Connection ~ 1100 2600
Wire Wire Line
	750  2750 900  2750
Wire Wire Line
	900  2750 900  2800
Connection ~ 750  2750
$Comp
L lepetocontrol-rescue:GND-power #PWR03
U 1 1 61DE9077
P 900 2800
F 0 "#PWR03" H 900 2550 50  0001 C CNN
F 1 "GND" H 905 2627 50  0001 C CNN
F 2 "" H 900 2800 50  0001 C CNN
F 3 "" H 900 2800 50  0001 C CNN
	1    900  2800
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:Conn_01x05-conn J4
U 1 1 61DEA4BA
P 1650 1050
F 0 "J4" H 1730 1092 50  0000 L CNN
F 1 "Conn_01x05" H 1730 1001 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x05" H 1650 1050 50  0001 C CNN
F 3 "~" H 1650 1050 50  0001 C CNN
	1    1650 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 850  800  850 
Wire Wire Line
	1450 950  800  950 
Wire Wire Line
	1450 1050 800  1050
Wire Wire Line
	1450 1150 800  1150
Wire Wire Line
	1450 1250 800  1250
$Comp
L lepetocontrol-rescue:GND-power #PWR02
U 1 1 61DF8F29
P 800 1050
F 0 "#PWR02" H 800 800 50  0001 C CNN
F 1 "GND" H 805 877 50  0001 C CNN
F 2 "" H 800 1050 50  0001 C CNN
F 3 "" H 800 1050 50  0001 C CNN
	1    800  1050
	0    1    1    0   
$EndComp
$Comp
L lepetocontrol-rescue:VCC-power #PWR?
U 1 1 61DF9AD6
P 800 850
AR Path="/61DF9AD6" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/61DF9AD6" Ref="#PWR01"  Part="1" 
F 0 "#PWR01" H 800 700 50  0001 C CNN
F 1 "VCC" V 700 850 50  0000 L CNN
F 2 "" H 800 850 50  0001 C CNN
F 3 "" H 800 850 50  0001 C CNN
	1    800  850 
	1    0    0    -1  
$EndComp
Text Label 800  950  0    50   ~ 0
SWCLK
Text Label 800  1150 0    50   ~ 0
SWDIO
Text Label 800  1250 0    50   ~ 0
~RESET
Wire Wire Line
	2450 2150 2000 2150
Wire Wire Line
	2450 1950 1600 1950
$Comp
L lepetocontrol-rescue:R-device R19
U 1 1 61E01EB4
P 2000 2300
F 0 "R19" H 2070 2346 50  0000 L CNN
F 1 "10K" H 2070 2255 50  0000 L CNN
F 2 "Resistors_SMD:R_0805" V 1930 2300 50  0001 C CNN
F 3 "~" H 2000 2300 50  0001 C CNN
	1    2000 2300
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:GND-power #PWR09
U 1 1 61E06675
P 2000 2450
F 0 "#PWR09" H 2000 2200 50  0001 C CNN
F 1 "GND" H 2005 2277 50  0001 C CNN
F 2 "" H 2000 2450 50  0001 C CNN
F 3 "" H 2000 2450 50  0001 C CNN
	1    2000 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 2600 2200 2550
Wire Wire Line
	2200 2550 2450 2550
Wire Wire Line
	1100 2600 2200 2600
Wire Wire Line
	2450 2650 1500 2650
Wire Wire Line
	1500 2650 1500 2900
$Comp
L lepetocontrol-rescue:R-device R17
U 1 1 61E10987
P 1600 1800
F 0 "R17" H 1670 1846 50  0000 L CNN
F 1 "10K" H 1670 1755 50  0000 L CNN
F 2 "Resistors_SMD:R_0805" V 1530 1800 50  0001 C CNN
F 3 "~" H 1600 1800 50  0001 C CNN
	1    1600 1800
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:VCC-power #PWR?
U 1 1 61E10BFA
P 1600 1500
AR Path="/61E10BFA" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/61E10BFA" Ref="#PWR05"  Part="1" 
F 0 "#PWR05" H 1600 1350 50  0001 C CNN
F 1 "VCC" V 1500 1500 50  0000 L CNN
F 2 "" H 1600 1500 50  0001 C CNN
F 3 "" H 1600 1500 50  0001 C CNN
	1    1600 1500
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:SW_Push-switches SW1
U 1 1 61E14E3E
P 1600 2250
F 0 "SW1" V 1646 2202 50  0000 R CNN
F 1 "SW" V 1555 2202 50  0000 R CNN
F 2 "Buttons_Switches_ThroughHole:SW_Tactile_SPST_Angled" H 1600 2450 50  0001 C CNN
F 3 "" H 1600 2450 50  0001 C CNN
	1    1600 2250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1600 1950 1600 2050
Connection ~ 1600 1950
$Comp
L lepetocontrol-rescue:GND-power #PWR06
U 1 1 61E18EB6
P 1600 2450
F 0 "#PWR06" H 1600 2200 50  0001 C CNN
F 1 "GND" H 1605 2277 50  0001 C CNN
F 2 "" H 1600 2450 50  0001 C CNN
F 3 "" H 1600 2450 50  0001 C CNN
	1    1600 2450
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:SW_Push-switches SW2
U 1 1 61E1926E
P 2000 1700
F 0 "SW2" V 2046 1652 50  0000 R CNN
F 1 "SW" V 1955 1652 50  0000 R CNN
F 2 "Buttons_Switches_ThroughHole:SW_Tactile_SPST_Angled" H 2000 1900 50  0001 C CNN
F 3 "" H 2000 1900 50  0001 C CNN
	1    2000 1700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2000 2150 2000 1900
Connection ~ 2000 2150
Wire Wire Line
	2000 1500 1600 1500
Wire Wire Line
	1600 1500 1600 1650
Connection ~ 1600 1500
$Comp
L lepetocontrol-rescue:C_Small-device C8
U 1 1 61E2407E
P 4350 1350
F 0 "C8" H 4442 1396 50  0000 L CNN
F 1 "100nF" H 4442 1305 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 4350 1350 50  0001 C CNN
F 3 "~" H 4350 1350 50  0001 C CNN
	1    4350 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 1550 4850 1200
Wire Wire Line
	4850 1200 4350 1200
Wire Wire Line
	4350 1200 4350 1250
Wire Wire Line
	4950 1550 4950 1200
Wire Wire Line
	4950 1200 4850 1200
Connection ~ 4850 1200
Wire Wire Line
	5050 1550 5050 1200
Wire Wire Line
	5050 1200 4950 1200
Connection ~ 4950 1200
Wire Wire Line
	5150 1550 5150 1200
Wire Wire Line
	5150 1200 5050 1200
Connection ~ 5050 1200
$Comp
L lepetocontrol-rescue:C_Small-device C7
U 1 1 61E34A84
P 3950 1350
F 0 "C7" H 4042 1396 50  0000 L CNN
F 1 "100nF" H 4042 1305 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 3950 1350 50  0001 C CNN
F 3 "~" H 3950 1350 50  0001 C CNN
	1    3950 1350
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:C_Small-device C6
U 1 1 61E35081
P 3500 1350
F 0 "C6" H 3592 1396 50  0000 L CNN
F 1 "100nF" H 3592 1305 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 3500 1350 50  0001 C CNN
F 3 "~" H 3500 1350 50  0001 C CNN
	1    3500 1350
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:C_Small-device C5
U 1 1 61E3558A
P 3050 1350
F 0 "C5" H 3142 1396 50  0000 L CNN
F 1 "100nF" H 3142 1305 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 3050 1350 50  0001 C CNN
F 3 "~" H 3050 1350 50  0001 C CNN
	1    3050 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 1200 3950 1200
Wire Wire Line
	3050 1200 3050 1250
Connection ~ 4350 1200
Wire Wire Line
	3500 1250 3500 1200
Connection ~ 3500 1200
Wire Wire Line
	3500 1200 3050 1200
Wire Wire Line
	3950 1250 3950 1200
Connection ~ 3950 1200
Wire Wire Line
	3950 1200 3500 1200
Wire Wire Line
	3050 1450 3500 1450
Connection ~ 3500 1450
Wire Wire Line
	3500 1450 3950 1450
Connection ~ 3950 1450
Wire Wire Line
	3950 1450 4350 1450
$Comp
L lepetocontrol-rescue:GND-power #PWR011
U 1 1 61E4FCA6
P 3050 1450
F 0 "#PWR011" H 3050 1200 50  0001 C CNN
F 1 "GND" H 3055 1277 50  0001 C CNN
F 2 "" H 3050 1450 50  0001 C CNN
F 3 "" H 3050 1450 50  0001 C CNN
	1    3050 1450
	1    0    0    -1  
$EndComp
Connection ~ 3050 1450
Wire Wire Line
	4850 5150 4950 5150
Connection ~ 4950 5150
Wire Wire Line
	4950 5150 5050 5150
Connection ~ 5050 5150
Wire Wire Line
	5050 5150 5150 5150
$Comp
L lepetocontrol-rescue:GND-power #PWR013
U 1 1 61E55318
P 4950 5150
F 0 "#PWR013" H 4950 4900 50  0001 C CNN
F 1 "GND" H 4955 4977 50  0001 C CNN
F 2 "" H 4950 5150 50  0001 C CNN
F 3 "" H 4950 5150 50  0001 C CNN
	1    4950 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 3250 8250 3250
Wire Wire Line
	7650 3350 8250 3350
Wire Wire Line
	7650 3450 8250 3450
Wire Wire Line
	7650 3550 8250 3550
Wire Wire Line
	7650 3650 8250 3650
Wire Wire Line
	7650 3750 8250 3750
Wire Wire Line
	7650 3850 8250 3850
Wire Wire Line
	7650 4450 8250 4450
Wire Wire Line
	7650 4350 8250 4350
Text Label 8250 4350 2    50   ~ 0
USB_DM
Text Label 8250 4450 2    50   ~ 0
USB_DP
Wire Wire Line
	7650 4650 8250 4650
Text Label 8250 4650 2    50   ~ 0
SWCLK
Wire Wire Line
	7650 4550 8250 4550
Text Label 8250 4550 2    50   ~ 0
SWDIO
Wire Wire Line
	7650 4150 8250 4150
Wire Wire Line
	7650 4250 8250 4250
Text Label 8250 4150 2    50   ~ 0
TXD
Text Label 8250 4250 2    50   ~ 0
RXD
$Comp
L lepetocontrol-rescue:USB_OTG-conn J3
U 1 1 61EB8D64
P 10700 2200
F 0 "J3" H 10757 2667 50  0000 C CNN
F 1 "USB_OTG" H 10757 2576 50  0000 C CNN
F 2 "Connect:USB_Mini-B" H 10850 2150 50  0001 C CNN
F 3 "" H 10850 2150 50  0001 C CNN
	1    10700 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	10600 2600 10700 2600
$Comp
L lepetocontrol-rescue:GND-power #PWR04
U 1 1 61EC23B7
P 10600 2600
F 0 "#PWR04" H 10600 2350 50  0001 C CNN
F 1 "GND" H 10605 2427 50  0001 C CNN
F 2 "" H 10600 2600 50  0001 C CNN
F 3 "" H 10600 2600 50  0001 C CNN
	1    10600 2600
	1    0    0    -1  
$EndComp
Connection ~ 10600 2600
Text Label 12300 2200 2    50   ~ 0
USB_DP
Text Label 12300 2300 2    50   ~ 0
USB_DM
$Comp
L lepetocontrol-rescue:R-device R18
U 1 1 61F25826
P 11550 1950
F 0 "R18" H 11620 1996 50  0000 L CNN
F 1 "1K5" H 11620 1905 50  0000 L CNN
F 2 "Resistors_SMD:R_0805" V 11480 1950 50  0001 C CNN
F 3 "~" H 11550 1950 50  0001 C CNN
	1    11550 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	11550 2100 11550 2200
Connection ~ 11550 2200
Wire Wire Line
	11550 2200 12300 2200
$Comp
L lepetocontrol-rescue:VCC-power #PWR?
U 1 1 61F2D0C5
P 11550 1750
AR Path="/61F2D0C5" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/61F2D0C5" Ref="#PWR08"  Part="1" 
F 0 "#PWR08" H 11550 1600 50  0001 C CNN
F 1 "VCC" V 11450 1750 50  0000 L CNN
F 2 "" H 11550 1750 50  0001 C CNN
F 3 "" H 11550 1750 50  0001 C CNN
	1    11550 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	11550 1750 11550 1800
$Comp
L lepetocontrol-rescue:LM1117-3.3-regul U3
U 1 1 61F3532C
P 11500 2950
F 0 "U3" H 11500 3192 50  0000 C CNN
F 1 "LM1117-3.3" H 11500 3101 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-223-3Lead_TabPin2" H 11500 2950 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm1117.pdf" H 11500 2950 50  0001 C CNN
	1    11500 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	11000 2000 11100 2000
Wire Wire Line
	11100 2000 11100 2950
Wire Wire Line
	11100 2950 11200 2950
$Comp
L lepetocontrol-rescue:GND-power #PWR07
U 1 1 61F5CEA6
P 11500 3250
F 0 "#PWR07" H 11500 3000 50  0001 C CNN
F 1 "GND" H 11505 3077 50  0001 C CNN
F 2 "" H 11500 3250 50  0001 C CNN
F 3 "" H 11500 3250 50  0001 C CNN
	1    11500 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	11800 2950 11950 2950
$Comp
L lepetocontrol-rescue:VCC-power #PWR?
U 1 1 61F64A0B
P 12350 2950
AR Path="/61F64A0B" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/61F64A0B" Ref="#PWR010"  Part="1" 
F 0 "#PWR010" H 12350 2800 50  0001 C CNN
F 1 "VCC" V 12250 2950 50  0000 L CNN
F 2 "" H 12350 2950 50  0001 C CNN
F 3 "" H 12350 2950 50  0001 C CNN
	1    12350 2950
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:C_Small-device C4
U 1 1 61F6508E
P 11950 3150
F 0 "C4" H 12042 3196 50  0000 L CNN
F 1 "100nF" H 12042 3105 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 11950 3150 50  0001 C CNN
F 3 "~" H 11950 3150 50  0001 C CNN
	1    11950 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	11950 2950 11950 3050
Connection ~ 11950 2950
Wire Wire Line
	11950 2950 12350 2950
Wire Wire Line
	11950 3250 11500 3250
Connection ~ 11500 3250
$Comp
L lepetocontrol-rescue:C_Small-device C3
U 1 1 61F751F8
P 11100 3150
F 0 "C3" H 11009 3104 50  0000 R CNN
F 1 "100nF" H 11009 3195 50  0000 R CNN
F 2 "Capacitors_SMD:C_0603" H 11100 3150 50  0001 C CNN
F 3 "~" H 11100 3150 50  0001 C CNN
	1    11100 3150
	1    0    0    1   
$EndComp
Wire Wire Line
	11100 3250 11500 3250
Wire Wire Line
	11100 3050 11100 2950
Connection ~ 11100 2950
Wire Wire Line
	11000 2300 12300 2300
Wire Wire Line
	11000 2200 11550 2200
Wire Wire Line
	7650 3950 8250 3950
Wire Wire Line
	2450 3750 1950 3750
Wire Wire Line
	2450 3550 1950 3550
Wire Wire Line
	2450 4750 1950 4750
Wire Wire Line
	2450 4650 1950 4650
Wire Wire Line
	2450 4550 1950 4550
Wire Wire Line
	2450 4450 1950 4450
Wire Wire Line
	2450 4350 1950 4350
Wire Wire Line
	2450 4250 1950 4250
Wire Wire Line
	2450 4150 1950 4150
Wire Wire Line
	2450 4050 1950 4050
Wire Wire Line
	2450 3950 1950 3950
$Comp
L lepetocontrol-rescue:Conn_01x03-conn J5
U 1 1 6205866F
P 13550 1950
F 0 "J5" H 13630 1992 50  0000 L CNN
F 1 "Conn_01x03" H 13630 1901 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 13550 1950 50  0001 C CNN
F 3 "~" H 13550 1950 50  0001 C CNN
	1    13550 1950
	1    0    0    -1  
$EndComp
Text Label 13200 1850 0    50   ~ 0
TXD
Text Label 13200 1950 0    50   ~ 0
RXD
Wire Wire Line
	13350 1950 13200 1950
Wire Wire Line
	13350 1850 13200 1850
$Comp
L lepetocontrol-rescue:GND-power #PWR014
U 1 1 6206C88F
P 13350 2050
F 0 "#PWR014" H 13350 1800 50  0001 C CNN
F 1 "GND" H 13355 1877 50  0001 C CNN
F 2 "" H 13350 2050 50  0001 C CNN
F 3 "" H 13350 2050 50  0001 C CNN
	1    13350 2050
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:VCC-power #PWR?
U 1 1 6206D1CD
P 4850 1100
AR Path="/6206D1CD" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/6206D1CD" Ref="#PWR012"  Part="1" 
F 0 "#PWR012" H 4850 950 50  0001 C CNN
F 1 "VCC" V 4750 1100 50  0000 L CNN
F 2 "" H 4850 1100 50  0001 C CNN
F 3 "" H 4850 1100 50  0001 C CNN
	1    4850 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 1100 4850 1200
$Comp
L lepetocontrol-rescue:Conn_01x05_Female-conn J?
U 1 1 61A2A0BE
P 13600 7150
AR Path="/61A2A0BE" Ref="J?"  Part="1" 
AR Path="/61D933FF/61A2A0BE" Ref="J6"  Part="1" 
F 0 "J6" H 13628 7176 50  0000 L CNN
F 1 "Conn_01x05_Female" H 13628 7085 50  0000 L CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x05" H 13600 7150 50  0001 C CNN
F 3 "~" H 13600 7150 50  0001 C CNN
	1    13600 7150
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:Conn_01x05_Female-conn J?
U 1 1 61A2A0C4
P 13600 7900
AR Path="/61A2A0C4" Ref="J?"  Part="1" 
AR Path="/61D933FF/61A2A0C4" Ref="J7"  Part="1" 
F 0 "J7" H 13628 7926 50  0000 L CNN
F 1 "Conn_01x05_Female" H 13628 7835 50  0000 L CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x05" H 13600 7900 50  0001 C CNN
F 3 "~" H 13600 7900 50  0001 C CNN
	1    13600 7900
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:GND-power #PWR?
U 1 1 61A2A0CA
P 13400 7700
AR Path="/61A2A0CA" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/61A2A0CA" Ref="#PWR051"  Part="1" 
F 0 "#PWR051" H 13400 7450 50  0001 C CNN
F 1 "GND" H 13405 7527 50  0001 C CNN
F 2 "" H 13400 7700 50  0001 C CNN
F 3 "" H 13400 7700 50  0001 C CNN
	1    13400 7700
	0    1    1    0   
$EndComp
$Comp
L lepetocontrol-rescue:VCC-power #PWR?
U 1 1 61A2A0D0
P 13100 7700
AR Path="/61A2A0D0" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/61A2A0D0" Ref="#PWR049"  Part="1" 
F 0 "#PWR049" H 13100 7550 50  0001 C CNN
F 1 "VCC" V 13000 7700 50  0000 L CNN
F 2 "" H 13100 7700 50  0001 C CNN
F 3 "" H 13100 7700 50  0001 C CNN
	1    13100 7700
	1    0    0    -1  
$EndComp
Text Label 12850 7900 0    50   ~ 0
LED_CLK
Wire Wire Line
	13400 7900 12850 7900
Wire Wire Line
	13400 8000 12850 8000
Wire Wire Line
	13400 8100 12850 8100
Text Label 12850 8100 0    50   ~ 0
LED_LATCH
Wire Wire Line
	13100 7800 13100 7700
Wire Wire Line
	13100 7800 13400 7800
Wire Wire Line
	2450 3850 1950 3850
Text Label 12850 8000 0    50   ~ 0
LED_DATA
Text Label 1950 3550 0    50   ~ 0
LED_CLK
Text Label 1950 3750 0    50   ~ 0
LED_DATA
Text Label 1950 3650 0    50   ~ 0
LED_LATCH
Text Label 2000 7500 0    50   ~ 0
SCL1
Text Label 4450 7500 0    50   ~ 0
SCL2
Text Label 6850 7500 0    50   ~ 0
SCL3
Text Label 9250 7500 0    50   ~ 0
SCL4
Wire Wire Line
	1950 3650 2450 3650
Wire Wire Line
	2450 3450 1350 3450
Wire Wire Line
	2450 3350 1800 3350
Wire Wire Line
	2450 3250 1350 3250
Wire Wire Line
	2450 3050 1800 3050
Wire Wire Line
	2450 2950 2150 2950
Wire Wire Line
	2450 2850 2000 2850
Wire Wire Line
	7650 4050 8250 4050
Wire Wire Line
	7650 4750 8250 4750
Text Label 1950 3850 0    50   ~ 0
SCL
Text Label 1950 3950 0    50   ~ 0
SDA
$Comp
L lepetocontrol-rescue:SW_Push-switches SW5
U 1 1 61BB893F
P 1600 3350
F 0 "SW5" V 1646 3302 50  0000 R CNN
F 1 "SW" V 1555 3302 50  0000 R CNN
F 2 "lepetocontrol:switch_6x6" H 1600 3550 50  0001 C CNN
F 3 "" H 1600 3550 50  0001 C CNN
	1    1600 3350
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:SW_Push-switches SW3
U 1 1 61BB999E
P 1150 3250
F 0 "SW3" V 1196 3202 50  0000 R CNN
F 1 "SW" V 1105 3202 50  0000 R CNN
F 2 "lepetocontrol:switch_6x6" H 1150 3450 50  0001 C CNN
F 3 "" H 1150 3450 50  0001 C CNN
	1    1150 3250
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:SW_Push-switches SW6
U 1 1 61BB9C96
P 1600 3050
F 0 "SW6" V 1646 3002 50  0000 R CNN
F 1 "SW" V 1555 3002 50  0000 R CNN
F 2 "lepetocontrol:switch_6x6" H 1600 3250 50  0001 C CNN
F 3 "" H 1600 3250 50  0001 C CNN
	1    1600 3050
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:SW_Push-switches SW4
U 1 1 61BB9F5C
P 1150 3450
F 0 "SW4" V 1196 3402 50  0000 R CNN
F 1 "SW" V 1105 3402 50  0000 R CNN
F 2 "lepetocontrol:switch_6x6" H 1150 3650 50  0001 C CNN
F 3 "" H 1150 3650 50  0001 C CNN
	1    1150 3450
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:GND-power #PWR053
U 1 1 61C21A17
P 650 3650
F 0 "#PWR053" H 650 3400 50  0001 C CNN
F 1 "GND" H 655 3477 50  0001 C CNN
F 2 "" H 650 3650 50  0001 C CNN
F 3 "" H 650 3650 50  0001 C CNN
	1    650  3650
	1    0    0    -1  
$EndComp
Text Label 1850 3050 0    50   ~ 0
BUTT1
Text Label 1850 3250 0    50   ~ 0
BUTT2
Text Label 1850 3350 0    50   ~ 0
BUTT3
Text Label 1850 3450 0    50   ~ 0
BUTT4
Wire Wire Line
	650  3050 650  3250
Wire Wire Line
	950  3450 650  3450
Connection ~ 650  3450
Wire Wire Line
	650  3450 650  3650
Wire Wire Line
	650  3350 1400 3350
Connection ~ 650  3350
Wire Wire Line
	650  3350 650  3450
Wire Wire Line
	950  3250 650  3250
Connection ~ 650  3250
Wire Wire Line
	650  3250 650  3350
Wire Wire Line
	650  3050 1400 3050
Text Label 6250 7550 2    50   ~ 0
SENSE2
Text Label 3800 7550 2    50   ~ 0
SENSE1
$Comp
L lepetocontrol-rescue:74HC595-74xx U?
U 1 1 61EF66D9
P 2650 9800
AR Path="/61EF66D9" Ref="U?"  Part="1" 
AR Path="/61D933FF/61EF66D9" Ref="U6"  Part="1" 
F 0 "U6" H 2900 10450 50  0000 C CNN
F 1 "74HC595" H 2850 10350 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-16_3.9x9.9mm_Pitch1.27mm" H 2650 9800 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 2650 9800 50  0001 C CNN
	1    2650 9800
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:GND-power #PWR?
U 1 1 61EF66DF
P 2650 10500
AR Path="/61EF66DF" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/61EF66DF" Ref="#PWR030"  Part="1" 
F 0 "#PWR030" H 2650 10250 50  0001 C CNN
F 1 "GND" H 2655 10327 50  0001 C CNN
F 2 "" H 2650 10500 50  0001 C CNN
F 3 "" H 2650 10500 50  0001 C CNN
	1    2650 10500
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:VCC-power #PWR?
U 1 1 61EF66E5
P 2650 9200
AR Path="/61EF66E5" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/61EF66E5" Ref="#PWR028"  Part="1" 
F 0 "#PWR028" H 2650 9050 50  0001 C CNN
F 1 "VCC" V 2550 9200 50  0000 L CNN
F 2 "" H 2650 9200 50  0001 C CNN
F 3 "" H 2650 9200 50  0001 C CNN
	1    2650 9200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 7500 4850 7500
Wire Wire Line
	6850 7500 7250 7500
Wire Wire Line
	9250 7500 9650 7500
$Comp
L lepetocontrol-rescue:TEST_1P-conn J10
U 1 1 61F5EDE1
P 3800 7550
F 0 "J10" H 3858 7668 50  0000 L CNN
F 1 "SENSE1" H 3858 7577 50  0000 L CNN
F 2 "wirepads:WIREPAD_SMD_TINY" H 4000 7550 50  0001 C CNN
F 3 "" H 4000 7550 50  0001 C CNN
	1    3800 7550
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:TEST_1P-conn J11
U 1 1 61F5FDD4
P 6250 7550
F 0 "J11" H 6308 7668 50  0000 L CNN
F 1 "SENSE2" H 6308 7577 50  0000 L CNN
F 2 "wirepads:WIREPAD_SMD_TINY" H 6450 7550 50  0001 C CNN
F 3 "" H 6450 7550 50  0001 C CNN
	1    6250 7550
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:TEST_1P-conn J13
U 1 1 61F60394
P 11050 7550
F 0 "J13" H 11108 7668 50  0000 L CNN
F 1 "SENSE4" H 11108 7577 50  0000 L CNN
F 2 "wirepads:WIREPAD_SMD_TINY" H 11250 7550 50  0001 C CNN
F 3 "" H 11250 7550 50  0001 C CNN
	1    11050 7550
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:TEST_1P-conn J12
U 1 1 61F60B84
P 8650 7550
F 0 "J12" H 8708 7668 50  0000 L CNN
F 1 "SENSE3" H 8708 7577 50  0000 L CNN
F 2 "wirepads:WIREPAD_SMD_TINY" H 8850 7550 50  0001 C CNN
F 3 "" H 8850 7550 50  0001 C CNN
	1    8650 7550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 7600 2400 7600
Wire Wire Line
	2000 7500 2400 7500
Wire Wire Line
	3050 9400 4050 9400
Wire Wire Line
	3050 9500 4050 9500
$Comp
L lepetocontrol-rescue:74HC4051-74xx U8
U 1 1 61F12B3E
P 4350 9500
AR Path="/61F12B3E" Ref="U8"  Part="1" 
AR Path="/61D933FF/61F12B3E" Ref="U8"  Part="1" 
F 0 "U8" H 4550 10150 50  0000 C CNN
F 1 "74HC4051" H 4700 10050 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-16_3.9x9.9mm_Pitch1.27mm" H 4350 9100 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd74hc4051.pdf" H 4350 9100 50  0001 C CNN
	1    4350 9500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 9600 3050 9600
Wire Wire Line
	4750 9200 5000 9200
Wire Wire Line
	4750 9300 5000 9300
Wire Wire Line
	4750 9400 5000 9400
Wire Wire Line
	4750 9500 5000 9500
Text Label 5000 9200 2    50   ~ 0
SCL1
Text Label 5000 9300 2    50   ~ 0
SCL2
Text Label 5000 9400 2    50   ~ 0
SCL3
Text Label 5000 9500 2    50   ~ 0
SCL4
NoConn ~ 4750 9600
NoConn ~ 4750 9700
NoConn ~ 4750 9800
NoConn ~ 4750 9900
$Comp
L lepetocontrol-rescue:GND-power #PWR?
U 1 1 620904AC
P 4050 9800
AR Path="/620904AC" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/620904AC" Ref="#PWR032"  Part="1" 
F 0 "#PWR032" H 4050 9550 50  0001 C CNN
F 1 "GND" H 4055 9627 50  0001 C CNN
F 2 "" H 4050 9800 50  0001 C CNN
F 3 "" H 4050 9800 50  0001 C CNN
	1    4050 9800
	1    0    0    -1  
$EndComp
Text Label 3800 9200 0    50   ~ 0
SCL
$Comp
L lepetocontrol-rescue:VCC-power #PWR?
U 1 1 620B2308
P 2250 9700
AR Path="/620B2308" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/620B2308" Ref="#PWR024"  Part="1" 
F 0 "#PWR024" H 2250 9550 50  0001 C CNN
F 1 "VCC" V 2150 9700 50  0000 L CNN
F 2 "" H 2250 9700 50  0001 C CNN
F 3 "" H 2250 9700 50  0001 C CNN
	1    2250 9700
	0    -1   -1   0   
$EndComp
$Comp
L lepetocontrol-rescue:GND-power #PWR?
U 1 1 620BD5DD
P 2250 10000
AR Path="/620BD5DD" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/620BD5DD" Ref="#PWR026"  Part="1" 
F 0 "#PWR026" H 2250 9750 50  0001 C CNN
F 1 "GND" H 2255 9827 50  0001 C CNN
F 2 "" H 2250 10000 50  0001 C CNN
F 3 "" H 2250 10000 50  0001 C CNN
	1    2250 10000
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:Conn_02x05_Odd_Even-conn J8
U 1 1 620C9394
P 1150 9600
F 0 "J8" H 1200 10017 50  0000 C CNN
F 1 "Conn_02x05_Odd_Even" H 1200 9926 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_2x05" H 1150 9600 50  0001 C CNN
F 3 "~" H 1150 9600 50  0001 C CNN
	1    1150 9600
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:Conn_02x05_Odd_Even-conn J9
U 1 1 620CA289
P 1150 10500
F 0 "J9" H 1200 10917 50  0000 C CNN
F 1 "Conn_02x05_Odd_Even" H 1200 10826 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Angled_2x05" H 1150 10500 50  0001 C CNN
F 3 "~" H 1150 10500 50  0001 C CNN
	1    1150 10500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 9400 2250 9400
Wire Wire Line
	3500 8800 3500 9200
Wire Wire Line
	3500 9200 4050 9200
$Comp
L lepetocontrol-rescue:VCC-power #PWR?
U 1 1 620FC212
P 4350 9000
AR Path="/620FC212" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/620FC212" Ref="#PWR034"  Part="1" 
F 0 "#PWR034" H 4350 8850 50  0001 C CNN
F 1 "VCC" V 4250 9000 50  0000 L CNN
F 2 "" H 4350 9000 50  0001 C CNN
F 3 "" H 4350 9000 50  0001 C CNN
	1    4350 9000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 9500 1700 9500
Wire Wire Line
	1700 9500 1700 9600
Wire Wire Line
	1700 9600 2250 9600
Wire Wire Line
	1650 9600 1650 9900
Wire Wire Line
	1650 9900 2250 9900
Wire Wire Line
	1450 9600 1650 9600
Wire Wire Line
	1450 10500 1650 10500
Wire Wire Line
	1650 10500 1650 9900
Connection ~ 1650 9900
Wire Wire Line
	1700 9600 1700 10400
Wire Wire Line
	1700 10400 1450 10400
Connection ~ 1700 9600
Wire Wire Line
	3050 10300 3100 10300
Wire Wire Line
	3100 10300 3100 10700
Wire Wire Line
	3100 10700 2150 10700
Wire Wire Line
	2150 10700 2150 10300
Wire Wire Line
	2150 10300 1450 10300
Wire Wire Line
	750  8800 1600 8800
Wire Wire Line
	1450 9700 1600 9700
Wire Wire Line
	1600 9700 1600 8800
Connection ~ 1600 8800
Wire Wire Line
	1600 8800 3500 8800
Wire Wire Line
	1450 9800 1550 9800
Wire Wire Line
	1550 9800 1550 8950
Wire Wire Line
	950  9400 950  9500
Connection ~ 950  9500
Wire Wire Line
	950  9500 950  9600
Wire Wire Line
	950  9500 700  9500
Wire Wire Line
	950  9700 950  9800
Wire Wire Line
	950  9800 700  9800
Connection ~ 950  9800
$Comp
L lepetocontrol-rescue:GND-power #PWR?
U 1 1 621A6866
P 700 9800
AR Path="/621A6866" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/621A6866" Ref="#PWR018"  Part="1" 
F 0 "#PWR018" H 700 9550 50  0001 C CNN
F 1 "GND" H 705 9627 50  0001 C CNN
F 2 "" H 700 9800 50  0001 C CNN
F 3 "" H 700 9800 50  0001 C CNN
	1    700  9800
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:VCC-power #PWR?
U 1 1 621A6C43
P 700 9500
AR Path="/621A6C43" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/621A6C43" Ref="#PWR016"  Part="1" 
F 0 "#PWR016" H 700 9350 50  0001 C CNN
F 1 "VCC" V 600 9500 50  0000 L CNN
F 2 "" H 700 9500 50  0001 C CNN
F 3 "" H 700 9500 50  0001 C CNN
	1    700  9500
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  10300 950  10400
Connection ~ 950  10400
Wire Wire Line
	950  10400 950  10500
Wire Wire Line
	950  10600 950  10700
Wire Wire Line
	950  10700 700  10700
Connection ~ 950  10700
$Comp
L lepetocontrol-rescue:GND-power #PWR?
U 1 1 621D1E0D
P 700 10700
AR Path="/621D1E0D" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/621D1E0D" Ref="#PWR022"  Part="1" 
F 0 "#PWR022" H 700 10450 50  0001 C CNN
F 1 "GND" H 705 10527 50  0001 C CNN
F 2 "" H 700 10700 50  0001 C CNN
F 3 "" H 700 10700 50  0001 C CNN
	1    700  10700
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:VCC-power #PWR?
U 1 1 621D21E7
P 700 10400
AR Path="/621D21E7" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/621D21E7" Ref="#PWR020"  Part="1" 
F 0 "#PWR020" H 700 10250 50  0001 C CNN
F 1 "VCC" V 600 10400 50  0000 L CNN
F 2 "" H 700 10400 50  0001 C CNN
F 3 "" H 700 10400 50  0001 C CNN
	1    700  10400
	1    0    0    -1  
$EndComp
Wire Wire Line
	700  10400 950  10400
Wire Wire Line
	1550 8950 750  8950
Text Label 750  8800 0    50   ~ 0
SCL
Text Label 750  8950 0    50   ~ 0
SDA
Connection ~ 1550 9800
Wire Wire Line
	1450 10700 1550 10700
Wire Wire Line
	1550 9800 1550 10700
Wire Wire Line
	1600 9700 1600 10600
Wire Wire Line
	1600 10600 1450 10600
Connection ~ 1600 9700
Text Label 1850 9900 0    50   ~ 0
MUXLATCH
Text Label 1850 9600 0    50   ~ 0
MUXCLK
Text Label 1850 9400 0    50   ~ 0
MUXDI
Text Label 1850 10300 0    50   ~ 0
MUXDO
Wire Wire Line
	11100 2000 11100 1500
Connection ~ 11100 2000
Text Label 11100 1500 0    50   ~ 0
VBUS
Wire Wire Line
	1750 6800 1750 6950
Wire Wire Line
	1900 6650 1900 6950
Text Label 1900 6950 1    50   ~ 0
SDA
Text Label 1750 6950 1    50   ~ 0
SCL
Text Label 1950 4550 0    50   ~ 0
MUXDI
Text Label 1950 4650 0    50   ~ 0
MUXCLK
Text Label 1950 4750 0    50   ~ 0
MUXLATCH
Wire Wire Line
	1600 1950 1050 1950
Text Label 1050 1950 0    50   ~ 0
~RESET
$Comp
L oled:oled-7pin U10
U 1 1 61A7CCEB
P 8700 10150
F 0 "U10" H 9078 10196 50  0000 L CNN
F 1 "oled-7pin" H 9078 10105 50  0000 L CNN
F 2 "lepetocontrol:oled_1.3_spi" H 8350 10300 50  0001 C CNN
F 3 "" H 8350 10300 50  0001 C CNN
	1    8700 10150
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:GND-power #PWR0119
U 1 1 61A8598D
P 8150 9850
F 0 "#PWR0119" H 8150 9600 50  0001 C CNN
F 1 "GND" H 8155 9677 50  0001 C CNN
F 2 "" H 8150 9850 50  0001 C CNN
F 3 "" H 8150 9850 50  0001 C CNN
	1    8150 9850
	0    1    1    0   
$EndComp
Wire Wire Line
	8150 10050 7600 10050
Wire Wire Line
	8150 10150 7600 10150
Wire Wire Line
	8150 10250 7600 10250
Wire Wire Line
	8150 10350 7600 10350
Wire Wire Line
	8150 10450 7600 10450
Text Label 7600 10050 0    50   ~ 0
OLED_SCK
Text Label 7600 10150 0    50   ~ 0
OLED_SDA
Text Label 7600 10250 0    50   ~ 0
~OLED_RES
Text Label 7600 10350 0    50   ~ 0
OLED_DC
Text Label 7600 10450 0    50   ~ 0
OLED_CS
$Comp
L lepetocontrol-rescue:VCC-power #PWR?
U 1 1 61B0EDD4
P 7800 9800
AR Path="/61B0EDD4" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/61B0EDD4" Ref="#PWR0120"  Part="1" 
F 0 "#PWR0120" H 7800 9650 50  0001 C CNN
F 1 "VCC" V 7700 9800 50  0000 L CNN
F 2 "" H 7800 9800 50  0001 C CNN
F 3 "" H 7800 9800 50  0001 C CNN
	1    7800 9800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 9950 7800 9950
Wire Wire Line
	7800 9950 7800 9800
Text Label 8250 3250 2    50   ~ 0
OLED_SCK
Text Label 8250 3350 2    50   ~ 0
OLED_SDA
Text Label 8250 3450 2    50   ~ 0
~OLED_RES
Text Label 8250 3550 2    50   ~ 0
OLED_DC
Text Label 8250 3650 2    50   ~ 0
OLED_CS
$Comp
L lepetocontrol-rescue:MountingHole-mechanical H5
U 1 1 61BA14F1
P 12850 5250
F 0 "H5" H 12950 5296 50  0000 L CNN
F 1 "MountingHole" H 12950 5205 50  0000 L CNN
F 2 "Mounting_Holes:MountingHole_2.5mm" H 12850 5250 50  0001 C CNN
F 3 "~" H 12850 5250 50  0001 C CNN
	1    12850 5250
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:MountingHole-mechanical H8
U 1 1 61BA1F02
P 13650 5450
F 0 "H8" H 13750 5496 50  0000 L CNN
F 1 "MountingHole" H 13750 5405 50  0000 L CNN
F 2 "Mounting_Holes:MountingHole_2.5mm" H 13650 5450 50  0001 C CNN
F 3 "~" H 13650 5450 50  0001 C CNN
	1    13650 5450
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:MountingHole-mechanical H7
U 1 1 61BA1F45
P 13650 5250
F 0 "H7" H 13750 5296 50  0000 L CNN
F 1 "MountingHole" H 13750 5205 50  0000 L CNN
F 2 "Mounting_Holes:MountingHole_2.5mm" H 13650 5250 50  0001 C CNN
F 3 "~" H 13650 5250 50  0001 C CNN
	1    13650 5250
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:MountingHole-mechanical H6
U 1 1 61BA1F77
P 12850 5450
F 0 "H6" H 12950 5496 50  0000 L CNN
F 1 "MountingHole" H 12950 5405 50  0000 L CNN
F 2 "Mounting_Holes:MountingHole_2.5mm" H 12850 5450 50  0001 C CNN
F 3 "~" H 12850 5450 50  0001 C CNN
	1    12850 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	13400 6950 13400 7050
Connection ~ 13400 7050
Wire Wire Line
	13400 7050 13400 7150
Connection ~ 13400 7150
Wire Wire Line
	13400 7150 13400 7250
Connection ~ 13400 7250
Wire Wire Line
	13400 7250 13400 7350
Wire Wire Line
	13400 7350 13400 7400
Connection ~ 13400 7350
$Comp
L lepetocontrol-rescue:GND-power #PWR?
U 1 1 61CCF42F
P 13400 7400
AR Path="/61CCF42F" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/61CCF42F" Ref="#PWR0121"  Part="1" 
F 0 "#PWR0121" H 13400 7150 50  0001 C CNN
F 1 "GND" H 13405 7227 50  0001 C CNN
F 2 "" H 13400 7400 50  0001 C CNN
F 3 "" H 13400 7400 50  0001 C CNN
	1    13400 7400
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:CP-device C10
U 1 1 61CD2DFF
P 6100 10050
F 0 "C10" H 6218 10096 50  0000 L CNN
F 1 "220uF" H 6218 10005 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:CP_Tantalum_Case-D_EIA-7343-31_Reflow" H 6138 9900 50  0001 C CNN
F 3 "~" H 6100 10050 50  0001 C CNN
	1    6100 10050
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:VCC-power #PWR?
U 1 1 61CD5FDE
P 6100 9900
AR Path="/61CD5FDE" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/61CD5FDE" Ref="#PWR036"  Part="1" 
F 0 "#PWR036" H 6100 9750 50  0001 C CNN
F 1 "VCC" V 6000 9900 50  0000 L CNN
F 2 "" H 6100 9900 50  0001 C CNN
F 3 "" H 6100 9900 50  0001 C CNN
	1    6100 9900
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:GND-power #PWR?
U 1 1 61CD65ED
P 6100 10200
AR Path="/61CD65ED" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/61CD65ED" Ref="#PWR038"  Part="1" 
F 0 "#PWR038" H 6100 9950 50  0001 C CNN
F 1 "GND" H 6105 10027 50  0001 C CNN
F 2 "" H 6100 10200 50  0001 C CNN
F 3 "" H 6100 10200 50  0001 C CNN
	1    6100 10200
	1    0    0    -1  
$EndComp
$Comp
L lepetocontrol-rescue:GND-power #PWR?
U 1 1 61CA6C23
P 4350 10200
AR Path="/61CA6C23" Ref="#PWR?"  Part="1" 
AR Path="/61D933FF/61CA6C23" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 4350 9950 50  0001 C CNN
F 1 "GND" H 4355 10027 50  0001 C CNN
F 2 "" H 4350 10200 50  0001 C CNN
F 3 "" H 4350 10200 50  0001 C CNN
	1    4350 10200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 10100 4350 10200
Wire Wire Line
	4350 10100 4450 10100
Connection ~ 4350 10100
$EndSCHEMATC
